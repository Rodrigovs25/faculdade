import socket
import struct
import sys

def pad_id(student_id):
    return student_id.ljust(12).encode("ascii")

def send_udp_message(server, port, message):
    sock = socket.socket(socket.AF_INET6 if ':' in server else socket.AF_INET, socket.SOCK_DGRAM)
    sock.settimeout(2)
    try:
        sock.sendto(message, (server, int(port)))
        response, _ = sock.recvfrom(1024)
        return response
    except socket.timeout:
        print("Error: Request timed out.")
    finally:
        sock.close()

def individual_token_request(server, port, student_id, nonce):
    message = struct.pack('!H12sI', 1, pad_id(student_id), int(nonce))
    response = send_udp_message(server, port, message)
    if response:
        _, student_id, nonce, token = struct.unpack('!H12sI64s', response)
        print(f"{student_id.decode().strip()}:{nonce}:{token.decode()}")

def individual_token_validation(server, port, sas):
    parts = sas.split(":")
    if len(parts) != 3:
        print("Invalid SAS format.")
        return
    student_id, nonce, token = parts
    message = struct.pack('!H12sI64s', 3, pad_id(student_id), int(nonce), token.encode("ascii"))
    response = send_udp_message(server, port, message)
    if response:
        status = struct.unpack('!B', response[-1:])[0]
        print(status)

def group_token_request(server, port, sas_list):
    n = len(sas_list)
    if n < 1 or n > 15:
        print("Invalid number of SAS (must be between 1 and 15).")
        return
    
    message = struct.pack('!HH', 5, n)
    for sas in sas_list:
        parts = sas.split(":")
        if len(parts) != 3:
            print("Invalid SAS format.")
            return
        student_id, nonce, token = parts
        message += struct.pack('!12sI64s', pad_id(student_id), int(nonce), token.encode("ascii"))
    
    response = send_udp_message(server, port, message)
    if response:
        _, n = struct.unpack('!HH', response[:4])
        sas_tokens = []
        offset = 4
        for _ in range(n):
            student_id, nonce, token = struct.unpack('!12sI64s', response[offset:offset+80])
            sas_tokens.append(f"{student_id.decode().strip()}:{nonce}:{token.decode()}")
            offset += 80
        group_token = response[offset:].decode()
        print("+".join(sas_tokens) + "+" + group_token)

def group_token_validation(server, port, gas):
    message = struct.pack('!H', 7) + gas.encode("ascii")
    response = send_udp_message(server, port, message)
    if response:
        status = struct.unpack('!B', response[-1:])[0]
        print(status)

def main():
    if len(sys.argv) < 4:
        print("Usage: client.py <host> <port> <command> [args...]")
        return
    
    server, port, command = sys.argv[1], sys.argv[2], sys.argv[3]
    
    if command == "itr" and len(sys.argv) == 6:
        individual_token_request(server, port, sys.argv[4], sys.argv[5])
    elif command == "itv" and len(sys.argv) == 5:
        individual_token_validation(server, port, sys.argv[4])
    elif command == "gtr" and len(sys.argv) >= 6:
        group_token_request(server, port, sys.argv[4:])
    elif command == "gtv" and len(sys.argv) == 5:
        group_token_validation(server, port, sys.argv[4])
    else:
        print("Invalid command or missing arguments.")

if __name__ == "__main__":
    main()
