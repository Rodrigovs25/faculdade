def recv_all(sock, n):
    """
    Garante que exatamente n bytes sejam recebidos.
    """
    data = b''
    while len(data) < n:
        chunk = sock.recv(n - len(data))
        if not chunk:
            raise ConnectionError("Conexão encerrada prematuramente.")
        data += chunk
    return data
