# test_dccnet_frame.py

from pprint import pprint
from dccnet_frame import DCCNetFrame

def main():
    # Criar um frame simples de teste
    print("[TESTE] Criando frame com payload 'Hello'")
    frame = DCCNetFrame(payload=b'Hello', frame_id=0, ack=False, end=False, rst=False)
    built_frame = frame.build()

    # Mostrar o frame em hexadecimal
    print(f"[TESTE] Frame montado (hex): {built_frame.hex()}")

    # Parsear e validar
    parsed_frame, is_valid = DCCNetFrame.parse(built_frame)

    # Exibir resultados
    print(f"[TESTE] Frame parseado: {parsed_frame}")
    print(f"[TESTE] Checksum válido? {is_valid}")

    # Verificar os campos individuais
    print("[TESTE] Campos extraídos:")
    pprint({
        "Payload": parsed_frame.payload.decode('utf-8', errors='replace'),
        "Frame ID": parsed_frame.frame_id,
        "ACK": parsed_frame.ack,
        "END": parsed_frame.end,
        "RST": parsed_frame.rst,
        "Flags (binário)": f"{parsed_frame.flags:08b}",
        "Comprimento (length)": parsed_frame.length
    })

if __name__ == "__main__":
    main()
