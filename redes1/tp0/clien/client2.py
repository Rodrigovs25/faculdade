import argparse
import socket
import struct
import sys

def send_udp_message(server_address, port, message, retries=3, timeout=2):
    """Send a UDP message and wait for a response, with retries."""
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.settimeout(timeout)
        
        for attempt in range(retries):
            try:
                sock.sendto(message, (server_address, port))
                response, _ = sock.recvfrom(1024)
                return response
            except socket.timeout:
                print(f"Attempt {attempt + 1}: No response, retrying...")
        
        print("Server did not respond after multiple attempts.")
    finally:
        sock.close()
    return None

def handle_itr(server_address, port, user_id, nonce):
    """Send an Individual Token Request (ITR)"""
    message = struct.pack("!HHII", 1, 12, user_id, nonce)
    response = send_udp_message(server_address, port, message)
    
    if response:
        code, length, sas = struct.unpack("!HH10s", response)
        if code == 257:
            print(f"Received SAS: {sas.decode().strip()}")
        else:
            print(f"Error: {code}")

def handle_itv(server_address, port, sas):
    """Send an Individual Token Validation (ITV)"""
    sas = sas.encode().ljust(10, b' ')
    message = struct.pack("!HH10s", 2, 12, sas)
    response = send_udp_message(server_address, port, message)
    
    if response:
        code, length = struct.unpack("!HH", response[:4])
        if code == 258:
            print("ITV successful")
        else:
            print(f"Error: {code}")

def handle_gtr(server_address, port, sas_list):
    """Send a Group Token Request (GTR)"""
    n = len(sas_list)
    sas_data = b''.join([s.encode().ljust(10, b' ') for s in sas_list])
    message = struct.pack(f"!HHI{n * 10}s", 3, 8 + n * 10, n, sas_data)
    response = send_udp_message(server_address, port, message)
    
    if response:
        code, length, gas = struct.unpack("!HH10s", response)
        if code == 259:
            print(f"Received GAS: {gas.decode().strip()}")
        else:
            print(f"Error: {code}")

def handle_gtv(server_address, port, gas):
    """Send a Group Token Validation (GTV)"""
    gas = gas.encode().ljust(10, b' ')
    message = struct.pack("!HH10s", 4, 12, gas)
    response = send_udp_message(server_address, port, message)
    
    if response:
        code, length = struct.unpack("!HH", response[:4])
        if code == 260:
            print("GTV successful")
        else:
            print(f"Error: {code}")

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("server_address", type=str, help="Server IP address")
    parser.add_argument("port", type=int, help="Server port")
    parser.add_argument("command", type=str, choices=["itr", "itv", "gtr", "gtv"], help="Command to execute")
    parser.add_argument("args", nargs="*", help="Arguments for the command")
    args = parser.parse_args()
    
    if args.command == "itr" and len(args.args) == 2:
        handle_itr(args.server_address, args.port, int(args.args[0]), int(args.args[1]))
    elif args.command == "itv" and len(args.args) == 1:
        handle_itv(args.server_address, args.port, args.args[0])
    elif args.command == "gtr" and len(args.args) >= 1:
        handle_gtr(args.server_address, args.port, args.args)
    elif args.command == "gtv" and len(args.args) == 1:
        handle_gtv(args.server_address, args.port, args.args[0])
    else:
        print("Invalid command or arguments")
        sys.exit(1)

if __name__ == "__main__":
    main()
