import random

def print_case(start, end, shelters):
    print(f"{start[0]} {start[1]}")
    print(f"{end[0]} {end[1]}")
    print(len(shelters))
    for s in shelters:
        print(f"{s[0]} {s[1]} {s[2]}")

def linear_graph(n):
    shelters = [(10, i * 15, 0) for i in range(n)]
    return (shelters[0], shelters[-1], shelters)

def star_graph(n):
    center = (10, 0, 0)
    leaves = [(10, random.randint(-50, 50), random.randint(-50, 50)) for _ in range(n - 1)]
    return (leaves[0], leaves[-1], [center] + leaves)

def clique_graph(n):
    shelters = []
    for i in range(n):
        x = random.randint(0, 50)
        y = random.randint(0, 50)
        shelters.append((10, x, y))
    return (shelters[0], shelters[-1], shelters)

def cycle_graph(n):
    radius = 30
    shelters = []
    for i in range(n):
        angle = 2 * 3.14159 * i / n
        x = int(radius * round(math.cos(angle), 2))
        y = int(radius * round(math.sin(angle), 2))
        shelters.append((10, x, y))
    return (shelters[0], shelters[n//2], shelters)

def test_cases():
    print("=== Linear Graph ===")
    print_case(*linear_graph(5))
    print("\n=== Star Graph ===")
    print_case(*star_graph(6))
    print("\n=== Clique Graph ===")
    print_case(*clique_graph(5))
    print("\n=== Cycle Graph ===")
    print_case(*cycle_graph(6))

if __name__ == "__main__":
    import math
    test_cases()
