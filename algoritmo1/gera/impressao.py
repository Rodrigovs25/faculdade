import matplotlib.pyplot as plt

def desenhar_circulos_de_arquivo(nome_arquivo):
    with open(nome_arquivo, 'r') as arquivo:
        linhas = arquivo.readlines()

    n = int(linhas[0])
    dados = [list(map(float, linha.strip().split())) for linha in linhas[1:n+1]]

    # Criar a figura e o eixo
    fig, ax = plt.subplots()
    ax.set_aspect('equal')

    for i, (r, x, y) in enumerate(dados):
        circulo = plt.Circle((x, y), r, fill=False, edgecolor='blue')
        ax.add_patch(circulo)
        ax.plot(x, y, 'ro')  # centro em vermelho
        ax.text(x, y, f'{i+1}', fontsize=10, ha='center', va='center', color='black')

    # Ajustar limites e mostrar
    ax.relim()
    ax.autoscale_view()
    plt.grid(True)
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.title("Círculos no plano cartesiano")
    plt.show()

# Exemplo de uso
desenhar_circulos_de_arquivo('entrada.txt')
