import struct

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
        # Header com checksum zerado
        header_wo_checksum = struct.pack(
            "!8sHHHBB",
            SYNC,
            0,  # Placeholder do checksum
            self.length,
            self.frame_id,
            self.flags,
            0  # Reservado
        )
        frame_no_checksum = header_wo_checksum + self.payload

        # Garantir paridade para cálculo do checksum
        if len(frame_no_checksum) % 2 != 0:
            frame_no_checksum += b'\x00'

        checksum = self.internet_checksum(frame_no_checksum)

        print(f"[DEBUG] (build) Header sem checksum (para cálculo): {header_wo_checksum.hex()}")
        print(f"[DEBUG] Frame total para cálculo de checksum: {len(frame_no_checksum)} bytes")
        print(f"[DEBUG] Checksum calculado: {checksum:#06x}")

        # Header com checksum preenchido
        header_with_checksum = struct.pack(
            "!8sHHHBB",
            SYNC,
            checksum,
            self.length,
            self.frame_id,
            self.flags,
            0
        )
        full_frame = header_with_checksum + self.payload
        print(f"[DEBUG] Tamanho do frame montado: {len(full_frame)} bytes")
        return full_frame

    @staticmethod
    def parse(data):
        if len(data) < 16:
            raise ValueError("Frame muito pequeno")

        header = data[:16]
        sync1, checksum_recv, length, frame_id, flags, _ = struct.unpack("!8sHHHBB", header)
        if sync1 != SYNC:
            raise ValueError("SYNC inválido")

        if len(data) < 16 + length:
            raise ValueError("Payload incompleto")

        payload = data[16:16 + length]

        # Reconstituir o header zerado para checksum
        header_zero_checksum = struct.pack(
            "!8sHHHBB",
            SYNC,
            0,
            length,
            frame_id,
            flags,
            0
        )
        frame_for_checksum = header_zero_checksum + payload
        if len(frame_for_checksum) % 2 != 0:
            frame_for_checksum += b'\x00'

        checksum_calc = DCCNetFrame.internet_checksum(frame_for_checksum)

        print(f"[DEBUG] (parse) Header recebido: {header.hex()}")
        print(f"[DEBUG] (parse) Checksum recebido: {checksum_recv:#06x} | Checksum calculado: {checksum_calc:#06x}")

        frame = DCCNetFrame(payload, frame_id)
        frame.ack = bool(flags & 0x80)
        frame.end = bool(flags & 0x40)
        frame.rst = bool(flags & 0x20)
        frame.length = length
        frame.flags = flags

        return frame, checksum_recv == checksum_calc

    @staticmethod
    def internet_checksum(data):
        checksum = 0
        for i in range(0, len(data), 2):
            word = (data[i] << 8) + data[i+1]
            checksum += word
            checksum = (checksum & 0xFFFF) + (checksum >> 16)
        return ~checksum & 0xFFFF

    def __repr__(self):
        return (
            f"<DCCNetFrame id={self.frame_id} ack={self.ack} "
            f"end={self.end} rst={self.rst} len={self.length} "
            f"flags=0b{self.flags:08b}>"
        )
