import socket
import struct
import hashlib

PORT = 51001
MAX_SIZE = 4096

type_itr = 1
type_itv = 3
type_gtr = 5
type_gtv = 7

response_itr = 2
response_itv = 4
response_gtr = 6
response_gtv = 8

error_msg = 256
INVALID_MESSAGE_CODE = 1
INCORRECT_MESSAGE_LENGTH = 2
INVALID_PARAMETER = 3
INVALID_SINGLE_TOKEN = 4
ASCII_DECODE_ERROR = 5

# Armazena tokens válidos
token_db = {}

def generate_token(id, nonce):
    base = f"{id}:{nonce}".encode("ascii")
    return hashlib.sha256(base).hexdigest()

def handle_itr(data):
    if len(data) != 18:
        return struct.pack("!HH", error_msg, INCORRECT_MESSAGE_LENGTH)
    try:
        _, id_bytes, nonce = struct.unpack("!H12sI", data)
        id = id_bytes.decode("ascii").strip()
    except UnicodeDecodeError:
        return struct.pack("!HH", error_msg, ASCII_DECODE_ERROR)

    token = generate_token(id, nonce)
    token_db[(id, nonce)] = token
    return struct.pack("!H12sI64s", response_itr, id_bytes, nonce, token.encode("ascii"))

def handle_itv(data):
    if len(data) != 82:
        return struct.pack("!HH", error_msg, INCORRECT_MESSAGE_LENGTH)
    try:
        _, id_bytes, nonce, token_bytes = struct.unpack("!H12sI64s", data)
        id = id_bytes.decode("ascii").strip()
        token = token_bytes.decode("ascii")
    except UnicodeDecodeError:
        return struct.pack("!HH", error_msg, ASCII_DECODE_ERROR)

    valid = token_db.get((id, nonce))
    status = 0 if valid == token else 1
    return struct.pack("!H12sI64sB", response_itv, id_bytes, nonce, token_bytes, status)

def extract_sas(offset, data, N):
    sas_list = []
    for _ in range(N):
        segment = data[offset:offset+80]
        if len(segment) != 80:
            return None
        id_bytes, nonce, token_bytes = struct.unpack("!12sI64s", segment)
        try:
            id = id_bytes.decode("ascii").strip()
            token = token_bytes.decode("ascii")
        except UnicodeDecodeError:
            return ASCII_DECODE_ERROR
        sas_list.append((id_bytes, id, nonce, token_bytes, token))
        offset += 80
    return sas_list

def handle_gtr(data):
    if len(data) < 4:
        return struct.pack("!HH", error_msg, INCORRECT_MESSAGE_LENGTH)
    _, N = struct.unpack("!HH", data[:4])
    if N < 1 or N >= 16:
        return struct.pack("!HH", error_msg, INVALID_PARAMETER)

    expected_len = 4 + 80 * N
    if len(data) != expected_len:
        return struct.pack("!HH", error_msg, INCORRECT_MESSAGE_LENGTH)

    sas_list = extract_sas(4, data, N)
    if sas_list == ASCII_DECODE_ERROR:
        return struct.pack("!HH", error_msg, ASCII_DECODE_ERROR)
    if sas_list is None:
        return struct.pack("!HH", error_msg, INCORRECT_MESSAGE_LENGTH)

    for _, id, nonce, _, token in sas_list:
        valid = token_db.get((id, nonce))
        if valid != token:
            return struct.pack("!HH", error_msg, INVALID_SINGLE_TOKEN)

    combined = b''.join([id_b + struct.pack("!I", nonce) + token_b for id_b, _, nonce, token_b, _ in sas_list])
    group_token = hashlib.sha256(combined).hexdigest().encode("ascii")
    response = struct.pack("!HH", response_gtr, N)
    for id_b, _, nonce, token_b, _ in sas_list:
        response += struct.pack("!12sI64s", id_b, nonce, token_b)
    response += group_token
    return response

def handle_gtv(data):
    if len(data) < 4:
        return struct.pack("!HH", error_msg, INCORRECT_MESSAGE_LENGTH)
    _, N = struct.unpack("!HH", data[:4])
    if N < 1 or N >= 16:
        return struct.pack("!HH", error_msg, INVALID_PARAMETER)
    expected_len = 4 + 80*N + 64
    if len(data) != expected_len:
        return struct.pack("!HH", error_msg, INCORRECT_MESSAGE_LENGTH)

    sas_list = extract_sas(4, data, N)
    if sas_list == ASCII_DECODE_ERROR:
        return struct.pack("!HH", error_msg, ASCII_DECODE_ERROR)
    if sas_list is None:
        return struct.pack("!HH", error_msg, INCORRECT_MESSAGE_LENGTH)

    token_offset = 4 + 80 * N
    received_token = data[token_offset:token_offset+64].decode("ascii")

    for _, id, nonce, _, token in sas_list:
        valid = token_db.get((id, nonce))
        if valid != token:
            return struct.pack("!HH", error_msg, INVALID_SINGLE_TOKEN)

    combined = b''.join([id_b + struct.pack("!I", nonce) + token_b for id_b, _, nonce, token_b, _ in sas_list])
    expected_token = hashlib.sha256(combined).hexdigest()
    status = 0 if expected_token == received_token else 1

    response = struct.pack("!HH", response_gtv, N)
    for id_b, _, nonce, token_b, _ in sas_list:
        response += struct.pack("!12sI64s", id_b, nonce, token_b)
    response += received_token.encode("ascii") + struct.pack("!B", status)
    return response

def process_request(data):
    if len(data) < 2:
        return struct.pack("!HH", error_msg, INCORRECT_MESSAGE_LENGTH)
    message_type = struct.unpack("!H", data[:2])[0]

    if message_type == type_itr:
        return handle_itr(data)
    elif message_type == type_itv:
        return handle_itv(data)
    elif message_type == type_gtr:
        return handle_gtr(data)
    elif message_type == type_gtv:
        return handle_gtv(data)
    else:
        return struct.pack("!HH", error_msg, INVALID_MESSAGE_CODE)

def start_udp_server(host='::', port=PORT):
    sock = socket.socket(socket.AF_INET6, socket.SOCK_DGRAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.bind((host, port))
    print(f"Servidor escutando em {host}:{port} (UDP IPv6, compatível com IPv4)...")

    while True:
        try:
            data, addr = sock.recvfrom(MAX_SIZE)
            print(f"Recebido de {addr}: {len(data)} bytes")
            response = process_request(data)
            sock.sendto(response, addr)
        except Exception as e:
            print(f"Erro ao processar requisição: {e}")

if __name__ == "__main__":
    start_udp_server()