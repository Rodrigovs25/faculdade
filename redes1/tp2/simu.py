import socket
import json

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
message = {
    "type": "trace",
    "source": "127.0.1.1",
    "destination": "127.0.1.5",
    "routers": ["127.0.1.1"]
}
sock.sendto(json.dumps(message).encode(), ("127.0.1.2", 55151))
