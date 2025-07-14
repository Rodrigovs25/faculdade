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

    ip, port = addr_port.split(':')
    port = int(port)

    # Conectar ao servidor
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        print(f"[INFO] Conectando em {ip}:{port}...")
        sock.connect((ip, port))
        print("[INFO] Conectado.")

        # Montar e enviar frame DCCNET com o GAS
        #payload = (gas + '\n').encode('utf-8')
        payload = gas.encode('utf-8')  
        frame = DCCNetFrame(payload=payload, frame_id=0)
        built_frame = frame.build()
        
        print(f"[INFO] Enviando frame com GAS (payload='{gas}')")
        print(f"[DEBUG] Tamanho do frame montado: {len(built_frame)} bytes")
        sock.sendall(built_frame)

        buffer = b""
        
        # Receber frames em loop
        while True:
            data = sock.recv(1024)
            if not data:
                print("[INFO] Conexão fechada pelo servidor.")
                break

            buffer += data

            # Tentar encontrar e processar frame
            while True:
                sync_index = buffer.find(b'\xdc\xc0#\xc2\xdc\xc0#\xc2')
                if sync_index == -1 or len(buffer) - sync_index < 16:
                    break  # Não temos frame completo ainda

                try:
                    frame_data = buffer[sync_index:]
                    if len(frame_data) < 16:
                        break  # Frame incompleto ainda

                    # Pegar o tamanho do payload (posição 10-11 do header: length)
                    length = int.from_bytes(frame_data[10:12], 'big')
                    total_frame_size = 16 + length

                    print(f"[DEBUG] Encontrado SYNC em {sync_index}, length={length}, total_frame_size={total_frame_size}, buffer={len(buffer)} bytes")

                    if len(frame_data) < total_frame_size:
                        break  # Frame incompleto ainda

                    # Parsear frame completo
                    full_frame = frame_data[:total_frame_size]
                    frame, is_valid = DCCNetFrame.parse(full_frame)
                    print(f"[INFO] Frame recebido: {frame}")
                    print(f"[INFO] Checksum válido? {is_valid}")
                    print(f"[INFO] Payload: {frame.payload}")

                    # Cortar o frame processado do buffer
                    buffer = buffer[sync_index + total_frame_size:]
                except Exception as e:
                    print(f"[ERRO] Falha ao parsear frame: {e}")
                    buffer = buffer[sync_index + 1:]

if __name__ == "__main__":
    main()
