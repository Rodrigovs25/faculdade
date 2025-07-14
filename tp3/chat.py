import hashlib
import os
import struct

class Chat:
    def __init__(self, message, verifier=None, md5=None):
        self.message = message
        self.verifier = verifier if verifier else b'\x00' * 16
        self.md5 = md5 if md5 else b'\x00' * 16

    def to_bytes(self):
        msg_bytes = self.message.encode('ascii')
        n = len(msg_bytes)
        return struct.pack('!B', n) + msg_bytes + self.verifier + self.md5

    @classmethod
    def from_bytes(cls, data):
        n = data[0]
        msg = data[1:1+n].decode('ascii')
        verifier = data[1+n:1+n+16]
        md5 = data[1+n+16:1+n+32]
        return cls(msg, verifier, md5)

    def mine(self, context_bytes):
        """
        Gera código verificador até que o hash MD5 do contexto com nova mensagem
        comece com dois bytes zero.
        """
        msg_bytes = self.message.encode('ascii')
        n = len(msg_bytes)
        base = struct.pack('!B', n) + msg_bytes

        attempt = 0
        while True:
            verifier = os.urandom(16)
            full = context_bytes + base + verifier
            md5 = hashlib.md5(full).digest()
            attempt += 1
            if md5.startswith(b'\x00\x00'):
                self.verifier = verifier
                self.md5 = md5
                print(f"Novo chat minerado e adicionado após {attempt} tentativas.")
                break
            if attempt % 10000 == 0:
                print(f"Minerando... {attempt} tentativas")

class ChatHistory:
    def __init__(self):
        self.chats = []

    def append(self, chat: Chat):
        self.chats.append(chat)

    def size(self):
        return len(self.chats)

    def to_bytes(self):
        result = b''
        for chat in self.chats:
            result += chat.to_bytes()
        return result

    def from_bytes(self, count, data):
        self.chats = []
        offset = 0
        for _ in range(count):
            n = data[offset]
            length = 1 + n + 32
            chat_data = data[offset:offset + length]
            chat = Chat.from_bytes(chat_data)
            self.chats.append(chat)
            offset += length

    def last_20_bytes(self):
        """
        Retorna os bytes dos últimos 20 chats, excluindo os 16 bytes finais (MD5 do último).
        """
        recent = self.chats[-20:]
        result = b''
        for i, chat in enumerate(recent):
            chat_bytes = chat.to_bytes()
            if i == len(recent) - 1:
                result += chat_bytes[:-16]  # exclui hash MD5
            else:
                result += chat_bytes
        return result

    def is_valid(self):
        return self._is_valid_recursive(self.chats)

    def _is_valid_recursive(self, chats):
        if len(chats) == 0:
            return True
        last = chats[-1]
        subset = chats[:-1]

        # Verifica hash do último
        context = self._last_20_bytes_subset(subset + [last])
        full = context + last.verifier
        md5 = hashlib.md5(full).digest()
        if not md5.startswith(b'\x00\x00') or md5 != last.md5:
            return False

        return self._is_valid_recursive(subset)

    def _last_20_bytes_subset(self, subset):
        recent = subset[-20:]
        result = b''
        for i, chat in enumerate(recent):
            chat_bytes = chat.to_bytes()
            if i == len(recent) - 1:
                result += chat_bytes[:-16]  # exclui hash do último
            else:
                result += chat_bytes
        return result

    def save(self, path="chat_history.dat"):
        with open(path, "wb") as f:
            f.write(struct.pack("!I", self.size()))
            f.write(self.to_bytes())

    def load(self, path="chat_history.dat"):
        try:
            with open(path, "rb") as f:
                count_data = f.read(4)
                count = struct.unpack("!I", count_data)[0]
                chat_data = f.read()
                self.from_bytes(count, chat_data)
        except FileNotFoundError:
            self.chats = []
