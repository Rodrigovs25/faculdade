import random
import math
import os

def print_case_to_file(start, end, shelters, filename):
    with open(filename, "w") as f:
        f.write(f"{start[0]} {start[1]}\n")
        f.write(f"{end[0]} {end[1]}\n")
        f.write(f"{len(shelters)}\n")
        for s in shelters:
            f.write(f"{s[0]} {s[1]} {s[2]}\n")

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
        angle = 2 * math.pi * i / n
        x = int(radius * math.cos(angle))
        y = int(radius * math.sin(angle))
        shelters.append((10, x, y))
    return (shelters[0], shelters[n//2], shelters)

def random_graph(n, max_dist=50):
    shelters = []
    for _ in range(n):
        x = random.randint(-max_dist, max_dist)
        y = random.randint(-max_dist, max_dist)
        shelters.append((10, x, y))
    return (shelters[0], shelters[-1], shelters)

def generate_tests():
    os.makedirs("test_inputs", exist_ok=True)
    generators = [
        ("linear", linear_graph, 5),
        ("star", star_graph, 6),
        ("clique", clique_graph, 5),
        ("cycle", cycle_graph, 6),
        ("random_small", lambda: random_graph(8), None),
        ("random_large", lambda: random_graph(20, 100), None),
    ]
    
    for i, (name, gen_func, size) in enumerate(generators):
        if size:
            start, end, shelters = gen_func(size)
        else:
            start, end, shelters = gen_func()
        filename = f"test_inputs/{i+1:02d}_{name}.in"
        print_case_to_file(start, end, shelters, filename)
        print(f"Generated: {filename}")

if __name__ == "__main__":
    generate_tests()
