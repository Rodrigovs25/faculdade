from pprint import pprint
from dccnet_frame import DCCNetFrame

# Criar um frame simples de teste
frame = DCCNetFrame(payload=b'Hello', frame_id=0, ack=False, end=False, rst=False)
built_frame = frame.build()

# Mostrar o frame em hexadecimal
print(f"Frame built (hex): {built_frame.hex()}")

# Parsear e validar
parsed_frame, is_valid = DCCNetFrame.parse(built_frame)

# Exibir resultados
print(f"Parsed frame: {parsed_frame}")
print(f"Checksum valid? {is_valid}")

# Verificar os campos individuais
print("Campos extraídos:")
pprint({
    "Payload": parsed_frame.payload,
    "Frame ID": parsed_frame.frame_id,
    "ACK": parsed_frame.ack,
    "END": parsed_frame.end,
    "RST": parsed_frame.rst,
    "Flags (binário)": f"{parsed_frame.flags:08b}",
    "Comprimento (length)": parsed_frame.length
})
