#include <iostream>
#include "tabuleiro.hpp"

// Função principal
int main() {

    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<std::string> tabuleiro(n);
    Peca rainha;
    std::vector<Peca> peoes;

    // Leitura do tabuleiro e localização da rainha e dos peões
    for (int i = 0; i < n; ++i) {
        std::cin >> tabuleiro[i];
        for (int j = 0; j < m; ++j) {
            if (tabuleiro[i][j] == 'R') {
                rainha = Peca(i, j);
            } else if (tabuleiro[i][j] == 'P') {
                peoes.emplace_back(i, j);
            }
        }
    }

    // Criação do objeto e resolução do problema
    Tabuleiro jogo(n, m, k, tabuleiro, rainha, peoes);
    int resposta = jogo.resolverCaixeiroViajante();
    std::cout << resposta << std::endl;

    return 0;
}
