import socket
import struct
import sys
import time
import logging

# Configuração do logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

# Constants
PORT = 51001
TIMEOUT = 2  # Timeout in seconds
RETRY_LIMIT = 3  # Number of retries

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

# Function to resolve hostname and support IPv4/IPv6
def resolve_host(host, port):
    try:
        addr_info = socket.getaddrinfo(host, port, socket.AF_UNSPEC, socket.SOCK_DGRAM)
        for family, _, _, _, address in addr_info:
            return family, address
    except socket.gaierror:
        logging.error("Could not resolve host: %s", host)
        sys.exit(1)
    
    raise ValueError("Could not resolve host")

# Function to send and receive UDP messages
def send_udp_message(sock, server_address, message, expected_length):
    for attempt in range(RETRY_LIMIT):
        try:
            logging.info("Sending message (attempt %d/%d)...", attempt + 1, RETRY_LIMIT)
            sock.sendto(message, server_address)
            sock.settimeout(TIMEOUT)
            response, _ = sock.recvfrom(expected_length)
            
            msg_type = struct.unpack("!H", response[:2])[0]
            if msg_type == ERROR_MESSAGE:
                logging.error("Received error message from server.")
                return None
            
            return response
        except socket.timeout:
            logging.warning("Timeout, retrying %d/%d...", attempt + 1, RETRY_LIMIT)
            time.sleep(1)
    
    logging.error("Failed to receive a response from the server.")
    return None

# Function to request an individual token
def individual_token_request(sock, server_address, student_id, nonce):
    student_id_padded = student_id.ljust(12)[:12].encode("ascii")
    message = struct.pack("!H12sI", INDIVIDUAL_TOKEN_REQUEST, student_id_padded, nonce)
    response = send_udp_message(sock, server_address, message, 82)
    
    if not response:
        return
    
    msg_type, received_id, received_nonce, token = struct.unpack("!H12sI64s", response)
    if msg_type != INDIVIDUAL_TOKEN_RESPONSE:
        logging.error("Invalid response from server.")
        return
    
    received_id = received_id.decode("ascii").strip()
    token = token.hex()
    logging.info("%s:%d:%s", received_id, received_nonce, token)

# Main function to handle command-line arguments
def main():
    if len(sys.argv) < 2 or sys.argv[1] in ('-h', '--help'):
        print("""
Usage: client.py <host> <port> <command> <args>

Commands:
  itr <student_id> <nonce>       Request an individual token
  itv <sas>                      Validate an individual token
  gtr <sas_list>                 Request a group token
  gtv <gas>                      Validate a group token
        """)
        sys.exit(0)
    
    if len(sys.argv) < 5:
        logging.error("Invalid number of arguments. Use --help for usage details.")
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
        else:
            logging.error("Unsupported command.")
            sys.exit(1)

if __name__ == "__main__":
    main()
