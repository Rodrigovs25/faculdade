import socket
import struct
import sys
import time

# Constants
PORT = 51001
TIMEOUT = 2  # Timeout in seconds
RETRY_LIMIT = 3

# Message Types
INDIVIDUAL_TOKEN_REQUEST = 1
INDIVIDUAL_TOKEN_RESPONSE = 2
INDIVIDUAL_TOKEN_VALIDATION = 3
INDIVIDUAL_TOKEN_STATUS = 4
GROUP_TOKEN_REQUEST = 5
GROUP_TOKEN_RESPONSE = 6
GROUP_TOKEN_VALIDATION = 7
GROUP_TOKEN_STATUS = 8
ERROR_MESSAGE = 256

# Function to send and receive UDP messages
def send_udp_message(sock, server_address, message, expected_length):
    for attempt in range(RETRY_LIMIT):
        try:
            sock.sendto(message, server_address)
            sock.settimeout(TIMEOUT)
            response, _ = sock.recvfrom(expected_length)
            return response
        except socket.timeout:
            print(f"Timeout, retrying {attempt + 1}/{RETRY_LIMIT}...")
    print("Failed to receive a response from the server.")
    sys.exit(1)

# Function to request an individual token
def individual_token_request(sock, server_address, student_id, nonce):
    student_id_padded = student_id.ljust(12)[:12].encode("ascii")
    message = struct.pack("!H12sI", INDIVIDUAL_TOKEN_REQUEST, student_id_padded, nonce)
    response = send_udp_message(sock, server_address, message, 82)
    
    msg_type, received_id, received_nonce, token = struct.unpack("!H12sI64s", response)
    if msg_type != INDIVIDUAL_TOKEN_RESPONSE:
        print("Invalid response from server.")
        sys.exit(1)
    
    received_id = received_id.decode("ascii").strip()
    token = token.hex()
    print(f"{received_id}:{received_nonce}:{token}")

# Function to validate an individual token
def individual_token_validation(sock, server_address, sas):
    parts = sas.split(":")
    if len(parts) != 3:
        print("Invalid SAS format.")
        sys.exit(1)
    
    student_id, nonce, token = parts
    student_id_padded = student_id.ljust(12)[:12].encode("ascii")
    nonce = int(nonce)
    token_bytes = bytes.fromhex(token)
    
    message = struct.pack("!H12sI64s", INDIVIDUAL_TOKEN_VALIDATION, student_id_padded, nonce, token_bytes)
    response = send_udp_message(sock, server_address, message, 83)
    
    msg_type, received_id, received_nonce, received_token, status = struct.unpack("!H12sI64sB", response)
    if msg_type != INDIVIDUAL_TOKEN_STATUS:
        print("Invalid response from server.")
        sys.exit(1)
    
    print(status)

# Function to request a group token
def group_token_request(sock, server_address, sas_list):
    n = len(sas_list)
    if not (1 <= n <= 15):
        print("Invalid number of SAS in group token request.")
        sys.exit(1)
    
    message = struct.pack("!HH", GROUP_TOKEN_REQUEST, n)
    for sas in sas_list:
        parts = sas.split(":")
        student_id, nonce, token = parts
        student_id_padded = student_id.ljust(12)[:12].encode("ascii")
        nonce = int(nonce)
        token_bytes = bytes.fromhex(token)
        message += struct.pack("!12sI64s", student_id_padded, nonce, token_bytes)
    
    expected_length = 4 + (80 * n) + 64
    response = send_udp_message(sock, server_address, message, expected_length)
    
    msg_type, received_n = struct.unpack("!HH", response[:4])
    if msg_type != GROUP_TOKEN_RESPONSE or received_n != n:
        print("Invalid response from server.")
        sys.exit(1)
    
    received_sas_list = []
    offset = 4
    for _ in range(n):
        student_id, nonce, token = struct.unpack("!12sI64s", response[offset:offset+80])
        student_id = student_id.decode("ascii").strip()
        token = token.hex()
        received_sas_list.append(f"{student_id}:{nonce}:{token}")
        offset += 80
    
    group_token = response[offset:].hex()
    print("+".join(received_sas_list) + "+" + group_token)

# Function to validate a group token
def group_token_validation(sock, server_address, gas):
    parts = gas.split("+")
    sas_list = parts[:-1]
    group_token = parts[-1]
    
    n = len(sas_list)
    message = struct.pack("!HH", GROUP_TOKEN_VALIDATION, n)
    for sas in sas_list:
        student_id, nonce, token = sas.split(":")
        student_id_padded = student_id.ljust(12)[:12].encode("ascii")
        nonce = int(nonce)
        token_bytes = bytes.fromhex(token)
        message += struct.pack("!12sI64s", student_id_padded, nonce, token_bytes)
    
    message += bytes.fromhex(group_token)
    response = send_udp_message(sock, server_address, message, 69 + 80 * n)
    
    msg_type, received_n = struct.unpack("!HH", response[:4])
    if msg_type != GROUP_TOKEN_STATUS or received_n != n:
        print("Invalid response from server.")
        sys.exit(1)
    
    status = response[-1]
    print(status)

# Main function to handle command-line arguments
def main():
    if len(sys.argv) < 5:
        print("Usage: client.py <host> <port> <command> <args>")
        sys.exit(1)
    
    host = sys.argv[1]
    port = int(sys.argv[2])
    command = sys.argv[3]
    
    server_address = (host, port)
    
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        if command == "itr":
            student_id = sys.argv[4]
            nonce = int(sys.argv[5])
            individual_token_request(sock, server_address, student_id, nonce)
        elif command == "itv":
            sas = sys.argv[4]
            individual_token_validation(sock, server_address, sas)
        elif command == "gtr":
            sas_list = sys.argv[5:]
            group_token_request(sock, server_address, sas_list)
        elif command == "gtv":
            gas = sys.argv[4]
            group_token_validation(sock, server_address, gas)
        else:
            print("Unsupported command.")
            sys.exit(1)

if __name__ == "__main__":
    main()
