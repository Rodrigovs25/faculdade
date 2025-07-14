import sys
import socket
import threading
from dccnet_frame import DCCNetFrame

CHUNK_SIZE = 512

def send_file(sock, filename, role):
    with open(filename, 'rb') as f:
        frame_id = 0
        while True:
            chunk = f.read(CHUNK_SIZE)
            if not chunk:
                break
            end = f.peek(1) == b''  # Checa se é o último chunk
            frame = DCCNetFrame(payload=chunk, frame_id=frame_id, end=end)
            sock.sendall(frame.build())
            print(f"[{role.upper()}] Enviado frame {frame_id} ({len(chunk)} bytes)")
            frame_id += 1
        # Se nada foi enviado com END, envia frame vazio com END
        if chunk:
            frame = DCCNetFrame(payload=b'', frame_id=frame_id, end=True)
            sock.sendall(frame.build())
            print(f"[{role.upper()}] Enviado frame final vazio com END")

def receive_file(sock, filename, role):
    buffer = b""
    end_received = False
    with open(filename, 'wb') as f:
        while not end_received:
            data = sock.recv(1024)
            if not data:
                break
            buffer += data
            while True:
                sync_index = buffer.find(b'\xdc\xc0#\xc2\xdc\xc0#\xc2')
                if sync_index == -1 or len(buffer) - sync_index < 16:
                    break
                length = int.from_bytes(buffer[sync_index+10:sync_index+12], 'big')
                total_len = 16 + length
                if len(buffer) < sync_index + total_len:
                    break
                try:
                    frame_data = buffer[sync_index:sync_index+total_len]
                    frame, valid = DCCNetFrame.parse(frame_data)
                    if not valid:
                        print(f"[{role.upper()}] Frame inválido, ignorado")
                    else:
                        f.write(frame.payload)
                        print(f"[{role.upper()}] Recebido frame {frame.frame_id} ({len(frame.payload)} bytes)")
                        if frame.end:
                            end_received = True
                    buffer = buffer[sync_index + total_len:]
                except Exception as e:
                    print(f"[{role.upper()}] Erro ao parsear frame: {e}")
                    buffer = buffer[sync_index + 1:]

def run_server(port, input_file, output_file):
    with socket.socket(socket.AF_INET6, socket.SOCK_STREAM) as server:
        server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        # Para suportar IPv4 + IPv6 no Windows, desliga IPV6_V6ONLY (não disponível em todos OS)
        try:
            server.setsockopt(socket.IPPROTO_IPV6, socket.IPV6_V6ONLY, 0)
        except (AttributeError, OSError):
            pass  # Ignora se não existir

        server.bind(("::", port))
        server.listen(1)
        print(f"[SERVER] Aguardando conexão na porta {port}...")
        conn, addr = server.accept()
        with conn:
            print(f"[SERVER] Conectado a {addr}")
            t_send = threading.Thread(target=send_file, args=(conn, input_file, 'server'))
            t_recv = threading.Thread(target=receive_file, args=(conn, output_file, 'server'))
            t_send.start()
            t_recv.start()
            t_send.join()
            t_recv.join()
            print("[SERVER] Transferência finalizada.")

def run_client(ip, port, input_file, output_file):
    # Retira os colchetes do IPv6, se existirem
    if ip.startswith('[') and ip.endswith(']'):
        ip = ip[1:-1]

    with socket.socket(socket.AF_INET6 if ':' in ip else socket.AF_INET, socket.SOCK_STREAM) as client:
        print(f"[CLIENT] Conectando a {ip}:{port}...")
        client.connect((ip, port))
        print("[CLIENT] Conectado.")
        t_send = threading.Thread(target=send_file, args=(client, input_file, 'client'))
        t_recv = threading.Thread(target=receive_file, args=(client, output_file, 'client'))
        t_send.start()
        t_recv.start()
        t_send.join()
        t_recv.join()
        print("[CLIENT] Transferência finalizada.")

def main():
    if len(sys.argv) < 5:
        print("Uso:\n  Servidor: python3 dccnet_xfer.py -s <PORT> <INPUT> <OUTPUT>\n"
              "  Cliente:  python3 dccnet_xfer.py -c <IP>:<PORT> <INPUT> <OUTPUT>")
        sys.exit(1)

    mode = sys.argv[1]

    if mode == '-s':
        port = int(sys.argv[2])
        input_file = sys.argv[3]
        output_file = sys.argv[4]
        run_server(port, input_file, output_file)

    elif mode == '-c':
        ip_port = sys.argv[2]
        if ip_port.startswith('['):  # IPv6 com colchetes
            ip_end = ip_port.find(']')
            ip = ip_port[1:ip_end]
            port = int(ip_port[ip_end+2:])
        else:
            ip, port = ip_port.rsplit(':', 1)
            port = int(port)
        input_file = sys.argv[3]
        output_file = sys.argv[4]
        run_client(ip, port, input_file, output_file)
    else:
        print("Modo inválido. Use -s para servidor ou -c para cliente.")
        sys.exit(1)

if __name__ == "__main__":
    main()
