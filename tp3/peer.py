import socket
import struct
import threading
from chat import Chat, ChatHistory
from utils import recv_all


PORT = 51511

class Peer:
    def __init__(self, own_ip, chat_history: ChatHistory):
        self.own_ip = own_ip
        self.peers = set()
        self.lock = threading.Lock()
        self.chat_history = chat_history

    def start_server(self):
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server.bind((self.own_ip, PORT))
        server.listen()
        print(f"Listening on port {PORT}...")

        while True:
            conn, addr = server.accept()
            threading.Thread(target=self.handle_peer, args=(conn, addr[0]), daemon=True).start()

    def handle_peer(self, conn, addr_ip):
        with conn:
            self.peers.add(addr_ip)
            while True:
                try:
                    msg_type = conn.recv(1)
                    if not msg_type:
                        break
                    msg_type = msg_type[0]

                    if msg_type == 0x1:  # PeerRequest
                        print(f"Received PeerRequest from {addr_ip}")
                        self.send_peer_list(conn)
                    elif msg_type == 0x2:  # PeerList
                        count_bytes = recv_all(conn, 4)
                        count = struct.unpack("!I", count_bytes)[0]
                        data = recv_all(conn, 4 * count)

                        for i in range(count):
                            ip_bytes = data[4 * i: 4 * (i + 1)]
                            ip_str = socket.inet_ntoa(ip_bytes)
                            try:
                                ip_resolved = socket.gethostbyname(ip_str)
                            except socket.gaierror:
                                print(f"Falha ao resolver o IP de {ip_str}, ignorando.")
                                continue
                            if ip_resolved != self.own_ip and ip_resolved not in self.peers:
                                self.connect_to_peer(ip_resolved)
                    elif msg_type == 0x3:  # ArchiveRequest
                        print(f"Recebido ArchiveRequest de {addr_ip}")
                        self.send_archive(conn)
                    elif msg_type == 0x4:  # ArchiveResponse
                        data = recv_all(conn, 4)
                        count = struct.unpack("!I", data)[0]
                        chats_data = b""
                        for _ in range(count):
                            n_bytes = recv_all(conn, 1)
                            n = n_bytes[0]
                            chat_len = 1 + n + 32
                            chat_data = recv_all(conn, chat_len)
                            chats_data += n_bytes + chat_data

                        new_history = ChatHistory()
                        new_history.from_bytes(count, chats_data)
                        if new_history.is_valid() and new_history.size() > self.chat_history.size():
                            self.chat_history = new_history
                            print("Histórico atualizado com nova versão válida.")
                        else:
                            print("Histórico rejeitado (inválido ou menor).")
                    elif msg_type == 0x5:  # Notification (opcional)
                        size = conn.recv(1)[0]
                        msg = conn.recv(size).decode('ascii', errors='ignore')
                        print(f"[Notificação de {addr_ip}]: {msg}")
                    else:
                        print(f"Mensagem desconhecida recebida de {addr_ip}")
                except Exception as e:
                    print(f"Connection lost with {addr_ip}: {e}")
                    break

    def connect_to_peer(self, ip):
        try:
            conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            conn.connect((ip, PORT))
            self.peers.add(ip)
            threading.Thread(target=self.handle_peer, args=(conn, ip), daemon=True).start()

            # envia PeerRequest
            conn.send(bytes([0x1]))
        except Exception as e:
            print(f"Erro ao conectar ao peer {ip}: {e}")

    def send_peer_list(self, conn):
        with self.lock:
            conn.send(bytes([0x2]))
            conn.send(struct.pack("!I", len(self.peers)))
            for ip in self.peers:
                try:
                    ip_resolved = socket.gethostbyname(ip)
                    conn.send(socket.inet_aton(ip_resolved))
                except:
                    continue

    def send_archive(self, conn):
        data = self.chat_history.to_bytes()
        conn.send(bytes([0x4]))
        conn.send(struct.pack("!I", self.chat_history.size()))
        conn.send(data)

    def request_archive(self):
        for ip in list(self.peers):
            try:
                s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                s.connect((ip, PORT))
                s.send(bytes([0x3]))
                s.close()
            except Exception as e:
                print(f"Erro ao solicitar histórico de {ip}: {e}")

    def send_chat(self, message):
        chat = Chat(message)
        chat.mine(self.chat_history.last_20_bytes())
        self.chat_history.append(chat)

        data = self.chat_history.to_bytes()
        for ip in list(self.peers):
            try:
                s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                s.connect((ip, PORT))
                s.send(bytes([0x4]))
                s.send(struct.pack("!I", self.chat_history.size()))
                s.send(data)
                s.close()
            except Exception as e:
                print(f"Erro ao enviar chat para {ip}: {e}")
