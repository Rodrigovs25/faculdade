import sys
import socket
import threading
import json
import time

PORT = 55151

class Router:
    def __init__(self, address, period, startup_file=None):
        self.address = address
        self.period = period
        self.neighbors = {}        # ip -> peso
        self.routing_table = {}    # destino -> (próximo salto, custo total)
        self.last_update = {}      # IP do vizinho → timestamp da última atualização

        # Cria socket UDP
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind((address, PORT))

        # Processa arquivo de startup (se houver)
        if startup_file:
            self.process_startup_file(startup_file)

        # Inicia threads
        self.running = True
        threading.Thread(target=self.listen_loop, daemon=True).start()
        threading.Thread(target=self.periodic_update_loop, daemon=True).start()
        threading.Thread(target=self.command_loop, daemon=False).start()

    def process_startup_file(self, filename):
        with open(filename) as f:
            for line in f:
                line = line.strip()
                if line and not line.startswith("#"):
                    self.process_command(line)


    def listen_loop(self):
        while self.running:
            try:
                data, _ = self.sock.recvfrom(4096)
                message = json.loads(data.decode())
                self.handle_message(message)
            except Exception as e:
                print(f"Erro ao receber mensagem: {e}")

    def periodic_update_loop(self):
        while self.running:
            self.send_updates()
            self.remove_stale_routes()
            time.sleep(self.period)

    def command_loop(self):
        while self.running:
            try:
                cmd = input("> ").strip()
                self.process_command(cmd)
            except EOFError:
                break

    def process_command(self, cmd):
        parts = cmd.split()
        if not parts:
            return

        if parts[0] == "add" and len(parts) == 3:
            ip, weight = parts[1], int(parts[2])
            self.neighbors[ip] = weight
            self.routing_table[ip] = (ip, weight)
            print(f"[INFO] Adicionado vizinho {ip} com peso {weight}")

        elif parts[0] == "del" and len(parts) == 2:
            ip = parts[1]
            self.neighbors.pop(ip, None)
            # Remove rotas aprendidas por esse vizinho
            self.routing_table = {dst: info for dst, info in self.routing_table.items() if info[0] != ip}
            print(f"[INFO] Vínculo com {ip} removido")

        elif parts[0] == "trace" and len(parts) == 2:
            destination = parts[1]
            self.send_trace(destination)

        elif parts[0] == "quit":
            print("[INFO] Encerrando roteador...")
            self.running = False
            self.sock.close()
            sys.exit(0)

        else:
            print("[ERRO] Comando inválido")

    def handle_message(self, msg):
        msg_type = msg.get("type")
        if msg_type == "update":
            self.handle_update(msg)
        elif msg_type == "data":
            self.handle_data(msg)
        elif msg_type == "trace":
            self.handle_trace(msg)
        else:
            print(f"[ERRO] Tipo de mensagem desconhecido: {msg_type}")

    def send_updates(self):
        for neighbor_ip in self.neighbors:
            distances = {}

            # Não envie rotas aprendidas do próprio vizinho
            for destination, (next_hop, cost) in self.routing_table.items():
                if next_hop != neighbor_ip:
                    distances[destination] = cost

            # Adiciona rota para si mesmo
            distances[self.address] = 0

            update_msg = {
                "type": "update",
                "source": self.address,
                "destination": neighbor_ip,
                "distances": distances
            }

            try:
                self.sock.sendto(json.dumps(update_msg).encode(), (neighbor_ip, PORT))
            except Exception as e:
                print(f"[ERRO] Falha ao enviar update para {neighbor_ip}: {e}")


    def handle_update(self, msg):
        src = msg["source"]
        distances = msg["distances"]

        if src not in self.neighbors:
            # Ignora mensagens de quem não é vizinho direto
            return

        # Atualiza timestamp do último update
        self.last_update[src] = time.time()

        cost_to_src = self.neighbors[src]

        for dest, cost_from_src in distances.items():
            if dest == self.address:
                continue  # Ignora rotas para si mesmo

            total_cost = cost_to_src + cost_from_src

            # Verifica se é uma nova rota ou uma rota melhor
            if dest not in self.routing_table:
                self.routing_table[dest] = (src, total_cost)
            else:
                current_next_hop, current_cost = self.routing_table[dest]

                # Se veio do mesmo vizinho, atualize sempre (mesmo se o custo aumentou)
                if current_next_hop == src:
                    self.routing_table[dest] = (src, total_cost)
                # Se é uma rota melhor, substitui
                elif total_cost < current_cost:
                    self.routing_table[dest] = (src, total_cost)


    def handle_data(self, msg):
        dest = msg["destination"]

        if dest == self.address:
            print(f"[DATA] {msg['payload']}")
        else:
            self.forward_message(dest, msg)



    def handle_trace(self, msg):
        msg["hops"].append(self.address)

        if msg["destination"] == self.address:
            # Criar resposta
            response = {
                "type": "data",
                "source": self.address,
                "destination": msg["source"],
                "payload": json.dumps(msg)
            }
            self.forward_message(response["destination"], response)
        else:
            self.forward_message(msg["destination"], msg)

    def send_trace(self, destination):
        trace_msg = {
            "destination": destination,
            "type": "trace",
            "hops": [self.address],
            "source": self.address,
        }
        self.forward_message(destination, trace_msg)


    def forward_message(self, destination, message):
        if destination not in self.routing_table:
            print(f"[ERRO] Sem rota para {destination}")
            return
        next_hop = self.routing_table[destination][0]
        self.sock.sendto(json.dumps(message).encode(), (next_hop, PORT))

    def remove_stale_routes(self):
        now = time.time()
        for neighbor in list(self.last_update):
            if now - self.last_update[neighbor] > 4 * self.period:
                print(f"[INFO] Removendo rotas do vizinho inativo: {neighbor}")
                self.last_update.pop(neighbor, None)
                self.neighbors.pop(neighbor, None)
                self.routing_table = {dst: info for dst, info in self.routing_table.items() if info[0] != neighbor}


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Uso: ./router.py <endereco> <periodo> [startup]")
        sys.exit(1)

    ip = sys.argv[1]
    period = float(sys.argv[2])
    startup_file = sys.argv[3] if len(sys.argv) > 3 else None

    Router(ip, period, startup_file)
