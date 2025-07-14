import sys
import socket
from dccnet_frame import DCCNetFrame

def main():
    if len(sys.argv) != 3:
        print("Uso: python dccnet_md5.py <IP>:<PORT> <GAS>")
        sys.exit(1)

    addr_port = sys.argv[1]
    gas = sys.argv[2]

    if ':' not in addr_port:
        print("Formato do endereço inválido. Use IP:PORT")
        sys.exit(1)

    # Suporte a IPv6: divide apenas no último ':'
    ip, port = addr_port.rsplit(':', 1)
    port = int(port)

    # Conectar ao servidor
    with socket.socket(socket.AF_INET6 if ':' in ip else socket.AF_INET, socket.SOCK_STREAM) as sock:
        print(f"[INFO] Conectando em {ip}:{port}...")
        sock.connect((ip, port))
        print("[INFO] Conectado.")

        # Montar e enviar frame DCCNET com o GAS
        payload = gas.encode('utf-8')
        frame = DCCNetFrame(payload=payload, frame_id=0)
        built_frame = frame.build()

        print(f"[INFO] Enviando frame com GAS (payload='{gas}')")
        sock.sendall(built_frame)

        buffer = b""

        while True:
            data = sock.recv(1024)
            if not data:
                print("[INFO] Conexão fechada pelo servidor.")
                break

            buffer += data

            while True:
                sync_index = buffer.find(b'\xdc\xc0#\xc2\xdc\xc0#\xc2')
                if sync_index == -1 or len(buffer) - sync_index < 16:
                    break

                try:
                    frame_data = buffer[sync_index:]
                    if len(frame_data) < 16:
                        break

                    length = int.from_bytes(frame_data[10:12], 'big')
                    total_frame_size = 16 + length

                    if len(frame_data) < total_frame_size:
                        break

                    full_frame = frame_data[:total_frame_size]
                    frame, is_valid = DCCNetFrame.parse(full_frame)

                    print(f"[INFO] Frame recebido: {frame}")
                    print(f"[INFO] Checksum válido? {is_valid}")
                    print(f"[INFO] Payload: {frame.payload}")

                    # Verifica se é o último frame
                    if frame.end:
                        print("[INFO] Flag END recebida. Encerrando recepção.")
                        print(f"[RESULTADO] MD5: {frame.payload.decode()}")
                        return

                    buffer = buffer[sync_index + total_frame_size:]
                except Exception as e:
                    print(f"[ERRO] Falha ao parsear frame: {e}")
                    buffer = buffer[sync_index + 1:]

if __name__ == "__main__":
    main()
