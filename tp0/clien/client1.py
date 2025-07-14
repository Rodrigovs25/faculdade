import socket
import struct
import sys
import time

# Constantes
TIMEOUT = 2  # Tempo limite em segundos
RETRY_LIMIT = 3  # Número de tentativas

# Tipos de Mensagem
INDIVIDUAL_TOKEN_REQUEST = 1
INDIVIDUAL_TOKEN_RESPONSE = 2
INDIVIDUAL_TOKEN_VALIDATION = 3
INDIVIDUAL_TOKEN_STATUS = 4
GROUP_TOKEN_REQUEST = 5
GROUP_TOKEN_RESPONSE = 6
GROUP_TOKEN_VALIDATION = 7
GROUP_TOKEN_STATUS = 8
ERROR_MESSAGE = 256

# Função para resolver o nome do host e suportar IPv4/IPv6
def resolve_host(host, port):
    endereco = socket.getaddrinfo(host, port, socket.AF_UNSPEC, socket.SOCK_DGRAM)
    for family, _, _, _, address in endereco:
        return family, address
    raise ValueError("Não foi possível resolver o host")
    

# Função para enviar e receber mensagens UDP
def send_udp_message(sock, server_address, message):
    for attempt in range(RETRY_LIMIT):
        try:
            print(f"Enviando mensagem (tentativa {attempt + 1}/{RETRY_LIMIT})...")
            sock.sendto(message, server_address)
            sock.settimeout(TIMEOUT)
            response, _ = sock.recvfrom(4096)
            return response
        except socket.timeout:
            continue
    print("Falha ao receber resposta do servidor.")
    sys.exit(1)

# Função para solicitar um token individual
def individual_token_request(sock, server_address, student_id, nonce):
    student_id_padded = student_id.ljust(12).encode("ascii")
    message = struct.pack("!H12sI", INDIVIDUAL_TOKEN_REQUEST, student_id_padded, nonce)
    response = send_udp_message(sock, server_address, message)
    
    if len(response) != 82:
        print("Resposta inválida do servidor.")
        sys.exit(1)
    
    msg_type, received_id, received_nonce, token = struct.unpack("!H12sI64s", response)
    
    received_id = received_id.decode("ascii").strip()
    token = token.decode("ascii")
    print(f"{received_id}:{received_nonce}:{token}")

# Função para validar um token individual
def individual_token_validation(sock, server_address, sas):
    parts = sas.split(":")
    if len(parts) != 3:
        print("Formato de SAS inválido.")
        sys.exit(1)
    
    student_id, nonce, token = parts
    student_id_padded = student_id.ljust(12).encode("ascii")
    nonce = int(nonce)
    token_bytes = token.encode("ascii")
    
    message = struct.pack("!H12sI64s", INDIVIDUAL_TOKEN_VALIDATION, student_id_padded, nonce, token_bytes)
    response = send_udp_message(sock, server_address, message)
    
    msg_type, received_id, received_nonce, received_token, status = struct.unpack("!H12sI64sB", response)
    if msg_type != INDIVIDUAL_TOKEN_STATUS:
        print("Resposta inválida do servidor.")
        sys.exit(1)
    
    print(status)

# Function to request a group token
def group_token_request(sock, server_address, sas_list, N):
    n = len(sas_list)
    if not (1 <= n <= 15):
        print("Número inválido de SAS na solicitação de token de grupo.")
        sys.exit(1)
    
    message = struct.pack("!HH", GROUP_TOKEN_REQUEST, n)
    for sas in sas_list:
        parts = sas.split(":")
        student_id, nonce, token = parts
        student_id_padded = student_id.ljust(12).encode("ascii")
        nonce = int(nonce)
        token_bytes = token.encode("ascii")
        message += struct.pack("!12sI64s", student_id_padded, nonce, token_bytes)
    
    response = send_udp_message(sock, server_address, message)
    
    offset = 0
    msg_type, received_n = struct.unpack("!HH", response[offset:offset+4])
    offset += 4
    if msg_type != GROUP_TOKEN_RESPONSE or received_n != n:
        print("Resposta inválida do servidor.")
        sys.exit(1)
    
    received_sas_list = []
    for _ in range(N):
        student_id, nonce, token = struct.unpack("!12sI64s", response[offset:offset+80])
        student_id = student_id.decode("ascii").strip()
        token = token.decode('ascii')
        received_sas_list.append(f"{student_id}:{nonce}:{token}")
        offset += 80
    
    group_token = response[offset:offset+64].decode("ascii")
    print("+".join(received_sas_list) + "+" + group_token)

# Função para validar um token de grupo
def group_token_validation(sock, server_address, gas):
    *sas_list, group_token = gas.split("+")
    
    n = len(sas_list)
    message = struct.pack("!HH", GROUP_TOKEN_VALIDATION, n)
    for sas in sas_list:
        student_id, nonce, token = sas.split(":")
        student_id_padded = student_id.ljust(12).encode("ascii")
        nonce = int(nonce)
        token_bytes = token.encode("ascii")
        message += struct.pack("!12sI64s", student_id_padded, nonce, token_bytes)
    
    message += group_token.encode("ascii")
    response = send_udp_message(sock, server_address, message)
    
    msg_type, received_n = struct.unpack("!HH", response[:4])
    if msg_type != GROUP_TOKEN_STATUS or received_n != n:
        print("Resposta inválida do servidor.")
        sys.exit(1)
    
    status = response[-1]
    print(status)

# Função principal para lidar com argumentos da linha de comando
def main():
    if len(sys.argv) < 4:
        print("Uso: client.py <host> <porta> <comando> <argumentos>")
        sys.exit(1)
    
    host = sys.argv[1]
    port = int(sys.argv[2])
    command = sys.argv[3]
    
    family, server_address = resolve_host(host, port)
    
    with socket.socket(family, socket.SOCK_DGRAM) as sock:
        if command == "itr":
            student_id = sys.argv[4]
            nonce = int(sys.argv[5])
            individual_token_request(sock, server_address, student_id, nonce)
        elif command == "itv":
            sas = sys.argv[4]
            individual_token_validation(sock, server_address, sas)
        elif command == "gtr":
            sas_list = sys.argv[5:]
            N = int(sys.argv[4])
            group_token_request(sock, server_address, sas_list, N)
        elif command == "gtv":
            gas = sys.argv[4]
            group_token_validation(sock, server_address, gas)
        else:
            print("Comando não suportado.")
            sys.exit(1)

if __name__ == "__main__":
    main()