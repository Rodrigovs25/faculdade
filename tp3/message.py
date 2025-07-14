import struct
import socket

def encode_peer_request():
    return struct.pack('!B', 0x1)

def encode_peer_list(peers):
    data = struct.pack('!BI', 0x2, len(peers))
    for ip in peers:
        data += socket.inet_aton(ip)
    return data

def decode_peer_list(data):
    count = struct.unpack('!I', data[1:5])[0]
    peers = []
    for i in range(count):
        ip_bytes = data[5 + i*4 : 9 + i*4]
        peers.append(socket.inet_ntoa(ip_bytes))
    return peers

def encode_notification(msg):
    encoded = msg.encode('ascii')
    return struct.pack('!BB', 0x5, len(encoded)) + encoded
