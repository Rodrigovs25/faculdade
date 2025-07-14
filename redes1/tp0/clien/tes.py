import socket
import struct
import sys
import time

# Configurações globais
PORT = 51001
TIMEOUT = 2  # Tempo limite em segundos
RETRY_LIMIT = 3  # Número de tentativas antes de desistir

# Tipos de mensagens
INDIVIDUAL_TOKEN_REQUEST = 1
INDIVIDUAL_TOKEN_RESPONSE = 2
INDIVIDUAL_TOKEN_VALIDATION = 3
INDIVIDUAL_TOKEN_STATUS = 4
GROUP_TOKEN_REQUEST = 5
GROUP_TOKEN_RESPONSE = 6
GROUP_TOKEN_VALIDATION = 7
GROUP_TOKEN_STATUS = 8
ERROR_MESSAGE = 256

# Função para resolver endereços suportando IPv4 e IPv6
def resolve_host(host, port):
    addr_info = socket.getaddrinfo(host, port, proto=socket.IPPROTO_UDP)
    return addr_info[0][0], addr_info[0][4]

# Função genérica para enviar e receber mensagens UDP com reenvio automático
def send_udp_message(sock, server_address, message, expected_length):
    for attempt in range(RETRY_LIMIT):
        try:
            print(f"Enviando mensagem (tentativa {attempt + 1}/{RETRY_LIMIT})...")
            sock.sendto(message, server_address)
            sock.settimeout(TIMEOUT)
            response, _ = sock.recvfrom(expected_length)
            return response
        except socket.timeout:
            print(f"Timeout, tentando novamente ({attempt + 1}/{RETRY_LIMIT})...")
            time.sleep(1)
    print("Erro: o servidor não respondeu após várias tentativas.")
    sys.exit(1)

# Função para codificar um pedido de token individual
def encode_itr(student_id, nonce):
    student_id_padded = student_id.ljust(12).encode("ascii")
    return struct.pack("!H12sI", INDIVIDUAL_TOKEN_REQUEST, student_id_padded, nonce)

# Função para decodificar a resposta de um pedido de token individual
def decode_itr_response(response):
    if len(response) != 82:
        print("Resposta com tamanho incorreto")
        sys.exit(1)
    tipo, student_id, nonce, token = struct.unpack("!H12sI64s", response)
    return f"{student_id.decode('ascii').strip()}:{nonce}:{token.hex()}"

# Função para codificar a validação de token individual
def encode_itv(sas):
    parts = sas.split(":")
    if len(parts) != 3:
        print("Formato SAS inválido.")
        sys.exit(1)
    student_id, nonce, token = parts
    student_id_padded = student_id.ljust(12).encode("ascii")
    nonce = int(nonce)
    token_bytes = bytes.fromhex(token)
    return struct.pack("!H12sI64s", INDIVIDUAL_TOKEN_VALIDATION, student_id_padded, nonce, token_bytes)

# Função para decodificar a resposta de status
def decode_status_response(response):
    if len(response) < 83:
        print("Resposta de status inválida.")
        sys.exit(1)
    return response[-1]

# Função para codificar um pedido de token de grupo
def encode_gtr(sas_list):
    N = len(sas_list)
    if not (1 <= N <= 15):
        print("Número inválido de SAS no pedido de grupo.")
        sys.exit(1)
    msg = struct.pack("!HH", GROUP_TOKEN_REQUEST, N)
    for sas in sas_list:
        student_id, nonce, token = sas.split(":")
        msg += struct.pack("!12sI64s", student_id.ljust(12).encode("ascii"), int(nonce), bytes.fromhex(token))
    return msg

# Função para decodificar a resposta do pedido de token de grupo
def decode_gtr_response(response, N):
    offset = 4
    sas_list = []
    for _ in range(N):
        student_id, nonce, token = struct.unpack("!12sI64s", response[offset:offset+80])
        sas_list.append(f"{student_id.decode('ascii').strip()}:{nonce}:{token.hex()}")
        offset += 80
    group_token = response[offset:].hex()
    return "+".join(sas_list) + "+" + group_token

# Função para codificar a validação de um token de grupo
def encode_gtv(gas):
    parts = gas.split("+")
    sas_list, group_token = parts[:-1], parts[-1]
    N = len(sas_list)
    msg = struct.pack("!HH", GROUP_TOKEN_VALIDATION, N)
    for sas in sas_list:
        student_id, nonce, token = sas.split(":")
        msg += struct.pack("!12sI64s", student_id.ljust(12).encode("ascii"), int(nonce), bytes.fromhex(token))
    msg += bytes.fromhex(group_token)
    return msg

# Função principal para lidar com argumentos da linha de comando
def main():
    if len(sys.argv) < 5:
        print("Uso: client.py <host> <port> <command> <args>")
        sys.exit(1)
    
    host, port, command = sys.argv[1], int(sys.argv[2]), sys.argv[3]
    family, server_address = resolve_host(host, port)
    
    with socket.socket(family, socket.SOCK_DGRAM) as sock:
        sock.settimeout(TIMEOUT)
        
        if command == "itr":
            student_id = sys.argv[4]
            nonce = int(sys.argv[5])
            msg = encode_itr(student_id, nonce)
            response = send_udp_message(sock, server_address, msg, 82)
            print(decode_itr_response(response))
            
        elif command == "itv":
            sas = sys.argv[4]
            msg = encode_itv(sas)
            response = send_udp_message(sock, server_address, msg, 83)
            print(decode_status_response(response))
            
        elif command == "gtr":
            sas_list = sys.argv[5:]
            msg = encode_gtr(sas_list)
            response = send_udp_message(sock, server_address, msg, 4 + (80 * len(sas_list)) + 64)
            print(decode_gtr_response(response, len(sas_list)))
            
        elif command == "gtv":
            gas = sys.argv[4]
            msg = encode_gtv(gas)
            response = send_udp_message(sock, server_address, msg, 69 + 80 * len(gas.split("+")[:-1]))
            print(decode_status_response(response))
        
        else:
            print("Comando desconhecido.")
            sys.exit(1)

if __name__ == "__main__":
    main()
