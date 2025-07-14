import socket
from dccnet_frame import DCCNetFrame

def main():
    HOST = '127.0.0.1'  # IP local
    PORT = 51001        # Porta de teste

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
        server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        server.bind((HOST, PORT))
        server.listen(1)
        print(f"[FAKE SERVER] Aguardando conexão em {HOST}:{PORT}...")

        conn, addr = server.accept()
        with conn:
            print(f"[FAKE SERVER] Conectado por {addr}")

            data = conn.recv(1024)
            print(f"[FAKE SERVER] Recebido {len(data)} bytes")

            # Parse do frame recebido (opcional)
            try:
                frame, valid = DCCNetFrame.parse(data)
                print(f"[FAKE SERVER] Frame recebido: {frame}")
                print(f"[FAKE SERVER] Checksum válido? {valid}")
                print(f"[FAKE SERVER] Payload recebido: {frame.payload.decode()}")
            except Exception as e:
                print(f"[ERRO] Frame inválido recebido: {e}")
                return

            # Simular MD5 como payload de resposta
            md5_result = "fakemd5hash1234567890abcdef"
            response_frame = DCCNetFrame(payload=md5_result.encode(), frame_id=1, ack=True, end=True)
            response_data = response_frame.build()
            conn.sendall(response_data)
            print(f"[FAKE SERVER] Frame de resposta enviado.")

if __name__ == "__main__":
    main()
