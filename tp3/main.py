import socket
import threading
from peer import Peer
from chat import ChatHistory
import time

PORT = 51511

def peer_request_loop(peer):
    while True:
        with peer.lock:
            for ip in list(peer.peers):
                try:
                    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                    s.connect((ip, PORT))
                    s.send(bytes([0x1]))
                    s.close()
                except Exception as e:
                    print(f"Erro ao enviar PeerRequest para {ip}: {e}")
        time.sleep(5)

def main():
    own_ip = input("Digite o seu IP (ex: 127.0.0.2): ").strip()
    initial_peer = input("Digite o IP do peer inicial (ou deixe vazio para nenhum): ").strip()

    chat_history = ChatHistory()
    chat_history.load()
    peer = Peer(own_ip, chat_history)
    threading.Thread(target=peer_request_loop, args=(peer,), daemon=True).start()

    if initial_peer:
        try:
            resolved_ip = socket.gethostbyname(initial_peer)
            peer.connect_to_peer(resolved_ip)
            peer.peers.add(resolved_ip)
        except Exception as e:
            print(f"Erro ao conectar ao peer inicial: {e}")

    while True:
        try:
            msg = input("Digite uma mensagem ou comando (/sync, /exit): ").strip()
            if msg == "/sync":
                peer.request_archive()
            elif msg == "/exit":
                print("Encerrando programa.")
                chat_history.save()
                break
            elif msg:
                peer.send_chat(msg)
        except KeyboardInterrupt:
            print("\nInterrompido. Encerrando.")
            chat_history.save()
            break

if __name__ == "__main__":
    main()
