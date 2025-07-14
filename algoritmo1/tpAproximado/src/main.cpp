#include <iostream>
#include <chrono>
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
    
    // Início da medição de tempo
    auto inicio = std::chrono::high_resolution_clock::now();

    // Criação do objeto 
    Tabuleiro jogo(n, m, k, tabuleiro, rainha, peoes);

    // Resolução do problema de maneira dinâmica
    // int respostaExata = jogo.resolverCaixeiroViajante();
    // std::cout << respostaExata << std::endl;
    
    // Resolução de maneira Gulosa
    int respostaAproximada = jogo.resolverGuloso();
    std::cout << respostaAproximada << std::endl;
    
    auto fim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duracao = fim - inicio;
    
    // Saída da duração
    // std::cout << "Tempo de execução: " << duracao.count() << " ms" << std::endl;

    return 0;
}
