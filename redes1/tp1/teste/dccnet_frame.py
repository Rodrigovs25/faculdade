import struct
import hashlib

SYNC = b'\xdc\xc0#\xc2' * 2  # 8 bytes de sincronização

class DCCNetFrame:
    def __init__(self, payload=b'', frame_id=0, ack=False, end=False, rst=False):
        self.payload = payload
        self.frame_id = frame_id
        self.ack = ack
        self.end = end
        self.rst = rst
        self.length = len(payload)
        self.flags = (
            (0x80 if ack else 0) |
            (0x40 if end else 0) |
            (0x20 if rst else 0)
        )

    def build(self):
        # Prepara o cabeçalho sem checksum (coloca checksum = 0 temporariamente)
        header = struct.pack(
            "!8sHHHBB",
            SYNC,
            0,  # Checksum placeholder
            self.length,
            self.frame_id,
            self.flags,
            0  # Reservado (1 byte extra para completar os 16 bytes)
        )

        frame_no_checksum = header + self.payload
        print(f"[DEBUG] (build) Header sem checksum (para cálculo): {header.hex()} + payload de {self.length} bytes")

        # Calcula checksum sobre o frame inteiro (SYNC + header + payload)
        checksum = self.internet_checksum(frame_no_checksum)
        print(f"[DEBUG] Frame total para cálculo de checksum: {len(frame_no_checksum)} bytes")
        print(f"[DEBUG] Checksum calculado: {hex(checksum)}")

        # Agora monta o header definitivo com checksum preenchido
        header_with_checksum = struct.pack(
            "!8sHHHBB",
            SYNC,
            checksum,
            self.length,
            self.frame_id,
            self.flags,
            0
        )

        final_frame = header_with_checksum + self.payload
        print(f"[DEBUG] Tamanho do frame montado: {len(final_frame)} bytes")
        return final_frame

    @staticmethod
    def parse(data):
        if len(data) < 16:
            raise ValueError("Frame muito pequeno para ser válido")

        sync1, checksum_recv, length, frame_id, flags, _ = struct.unpack("!8sHHHBB", data[:16])
        if sync1 != SYNC:
            raise ValueError("SYNC inválido")

        payload = data[16:16+length]

        # Verificar checksum
        header_with_zero_checksum = struct.pack(
            "!8sHHHBB",
            SYNC,
            0,
            length,
            frame_id,
            flags,
            0
        )
        full_frame_for_checksum = header_with_zero_checksum + payload
        checksum_calc = DCCNetFrame.internet_checksum(full_frame_for_checksum)

        print(f"[DEBUG] (parse) Header recebido: {data[:16].hex()}")
        print(f"[DEBUG] (parse) Checksum recebido: {hex(checksum_recv)} | Checksum calculado: {hex(checksum_calc)}")

        frame = DCCNetFrame(payload, frame_id)
        frame.ack = bool(flags & 0x80)
        frame.end = bool(flags & 0x40)
        frame.rst = bool(flags & 0x20)
        frame.length = length
        frame.flags = flags

        return frame, checksum_recv == checksum_calc

    @staticmethod
    def internet_checksum(data):
        """
        Internet checksum (RFC 1071).
        """
        if len(data) % 2:
            data += b'\x00'
        checksum = 0
        for i in range(0, len(data), 2):
            word = (data[i] << 8) + data[i+1]
            checksum += word
            checksum = (checksum & 0xffff) + (checksum >> 16)
        return ~checksum & 0xffff

    def __repr__(self):
        return f"<DCCNetFrame id={self.frame_id} ack={self.ack} end={self.end} rst={self.rst} len={self.length} valid_flags={self.flags:08b}>"
