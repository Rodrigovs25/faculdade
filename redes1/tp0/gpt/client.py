import socket
import struct
import sys

TIMEOUT = 2  # segundos
MAX_RETRIES = 3

# Constantes de mensagem
type_itr = 1
type_itv = 3
type_gtr = 5
type_gtv = 7
type_error = 256

def resolve_host(host, port):
    addr_info = socket.getaddrinfo(host, port, proto=socket.IPPROTO_UDP)
    return addr_info[0][0], addr_info[0][4]

def send_and_receive(sock, msg, server_addr):
    for _ in range(MAX_RETRIES):
        try:
            sock.sendto(msg, server_addr)
            response, _ = sock.recvfrom(4096)
            return response
        except socket.timeout:
            continue
    print("Erro: servidor não respondeu após várias tentativas.")
    sys.exit(1)

def encode_itr(student_id, nonce):
    student_id = student_id.ljust(12)
    return struct.pack("!H12sI", type_itr, student_id.encode("ascii"), nonce)

def decode_itr_response(response):
    if len(response) != 82:
        print("Resposta com tamanho incorreto")
        sys.exit(1)
    tipo, student_id, nonce, token = struct.unpack("!H12sI64s", response)
    student_id = student_id.decode("ascii").strip()
    token = token.decode("ascii")
    return f"{student_id}:{nonce}:{token}"

def encode_itv(sas):
    id, nonce, token = sas.split(":")
    id = id.ljust(12).encode("ascii")
    nonce = int(nonce)
    token = token.encode("ascii")
    return struct.pack("!H12sI64s", type_itv, id, nonce, token)

def decode_status_response(response):
    if len(response) < 83:
        print("Resposta de status inválida.")
        sys.exit(1)
    status = response[-1]
    return status

def encode_gtr(sas_list):
    N = len(sas_list)
    if not (1 <= N < 16):
        print("Número inválido de SAS.")
        sys.exit(1)
    msg = struct.pack("!HH", type_gtr, N)
    for sas in sas_list:
        id, nonce, token = sas.split(":")
        msg += struct.pack("!12sI64s", id.ljust(12).encode("ascii"), int(nonce), token.encode("ascii"))
    return msg

def decode_gtr_response(response, N):
    offset = 0
    tipo, count = struct.unpack("!HH", response[offset:offset+4])
    offset += 4
    sas_list = []
    for _ in range(N):
        id, nonce, token = struct.unpack("!12sI64s", response[offset:offset+80])
        sas_list.append(f"{id.decode('ascii').strip()}:{nonce}:{token.decode('ascii')}")
        offset += 80
    group_token = response[offset:offset+64].decode("ascii")
    return "+".join(sas_list) + "+" + group_token

def encode_gtv(gas):
    *sas_parts, token = gas.split("+")
    N = len(sas_parts)
    msg = struct.pack("!HH", type_gtv, N)
    for sas in sas_parts:
        id, nonce, sas_token = sas.split(":")
        msg += struct.pack("!12sI64s", id.ljust(12).encode("ascii"), int(nonce), sas_token.encode("ascii"))
    msg += token.encode("ascii")
    return msg

def main():
    if len(sys.argv) < 4:
        print("Uso: ./client.py <host> <port> <command> ...")
        sys.exit(1)

    host, port, command = sys.argv[1], int(sys.argv[2]), sys.argv[3]
    family, server_addr = resolve_host(host, port)

    with socket.socket(family, socket.SOCK_DGRAM) as sock:
        sock.settimeout(TIMEOUT)

        if command == "itr":
            if len(sys.argv) != 6:
                print("Uso: itr <id> <nonce>")
                sys.exit(1)
            student_id = sys.argv[4]
            nonce = int(sys.argv[5])
            msg = encode_itr(student_id, nonce)
            resp = send_and_receive(sock, msg, server_addr)
            print(decode_itr_response(resp))

        elif command == "itv":
            if len(sys.argv) != 5:
                print("Uso: itv <id:nonce:token>")
                sys.exit(1)
            sas = sys.argv[4]
            msg = encode_itv(sas)
            resp = send_and_receive(sock, msg, server_addr)
            print(decode_status_response(resp))

        elif command == "gtr":
            if len(sys.argv) < 6:
                print("Uso: gtr <N> <SAS-1> <SAS-2> ... <SAS-N>")
                sys.exit(1)
            N = int(sys.argv[4])
            sas_list = sys.argv[5:5+N]
            msg = encode_gtr(sas_list)
            resp = send_and_receive(sock, msg, server_addr)
            print(decode_gtr_response(resp, N))

        elif command == "gtv":
            if len(sys.argv) != 5:
                print("Uso: gtv <GAS>")
                sys.exit(1)
            gas = sys.argv[4]
            msg = encode_gtv(gas)
            resp = send_and_receive(sock, msg, server_addr)
            print(decode_status_response(resp))

        else:
            print("Comando desconhecido")
            sys.exit(1)

if __name__ == "__main__":
    main()