#include <iostream>
#include "fluxoMaximo.hpp"

// Funções auxiliares para mapear coordenadas da matriz para vértices do grafo
int indiceEntrada(int i, int j, int m) {
    return (i * m + j) * 2;
}

int indiceSaida(int i, int j, int m) {
    return (i * m + j) * 2 + 1;
}

int main()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> mapa(n, std::vector<int>(m));
    int somaTotal = 0; // Soma total dos soldados

    // Leitura do mapa e cálculo da soma total
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            std::cin >> mapa[i][j];
            somaTotal += mapa[i][j];
        }

    int xCapital, yCapital;
    std::cin >> xCapital >> yCapital;
    --xCapital; --yCapital; // Ajusta para índice base 0

    // Direções: cima, baixo, esquerda, direita
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    // Cálculo do número total de nós no grafo (2 por célula + fonte + sumidouro)
    int totalDeNos = n * m * 2 + 2;
    int origem = totalDeNos - 2;
    int destino = totalDeNos - 1;

    FluxoMaximo fluxo(totalDeNos, somaTotal);

    // Construção do grafo
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mapa[i][j] == 0) continue; // Montanhas são ignoradas

            // Mapeamento das coordenadas da matriz para vértices do grafo
            int entrada = indiceEntrada(i, j, m);
            int saida = indiceSaida(i, j, m);

            // Conecta entrada -> saída da mesma célula (custo = soldados)
            fluxo.adicionarAresta(entrada, saida, mapa[i][j]);

            // Liga saída desta célula para entrada das vizinhas
            for (int d = 0; d < 4; ++d) {
                int novaLinha = i + dx[d];
                int novaColuna = j + dy[d];
                if (novaLinha < 0 || novaColuna < 0 || novaLinha >= n || novaColuna >= m) {
                    continue; // Dentro do mapa
                }
                if (mapa[novaLinha][novaColuna] == 0) {
                    continue; // Vizinho é montanha
                }
                fluxo.adicionarAresta(saida, indiceEntrada(novaLinha, novaColuna, m), somaTotal);
            }

            // Se a célula está na borda do mapa, conecta à origem
            if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {
                fluxo.adicionarAresta(origem, entrada, somaTotal);
            }
        }
    }

    // Conecta saída da capital ao destino
    fluxo.adicionarAresta(indiceSaida(xCapital, yCapital, m), destino, somaTotal);

    // Calcula fluxo máximo entre origem e destino
    int resultado = fluxo.edmondsKarp(origem, destino);
    std::cout << resultado << std::endl;

    return 0;

}

