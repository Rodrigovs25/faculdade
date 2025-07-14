#ifndef TABULEIRO_HPP
#define TABULEIRO_HPP

#include <vector>
#include <queue>
#include "peca.hpp"

// Classe principal que resolve o problema da captura de peões
class Tabuleiro {
    private:
        int n, m, k;                           // Dimensões do tabuleiro e k=número de peões
        std::vector<std::string> tabuleiro;             // Matriz do tabuleiro (entrada)
        Peca rainha;                        // Objeto que representa a rainha
        std::vector<Peca> peoes;                   // Vetor com todos os peões

        // Matrizes de distâncias calculadas
        std::vector<int> distanciaRainha;              // Distância da rainha para cada peão
        std::vector<std::vector<int>> distanciaPeoes;       // Distância entre todos os pares de peões

        // Busca em largura adaptada para movimentos da rainha
        std::vector<std::vector<int>> bfs(std::pair<int, int> inicio);

        // Processa todas as distâncias necessárias (rainha -> peões, peões <-> peões)
        void calcularTodasDistancias();

    public:
        // Construtor: inicializa o tabuleiro com seus elementos
        Tabuleiro();
        Tabuleiro(int n, int m, int k,
                        const std::vector<std::string>& abuleiro,
                        const Peca& rainha,
                        const std::vector<Peca>& peoes);

        // Resolve o problema com Programação Dinâmica + Bitmask
        //int resolverCaixeiroViajante();

        // Solução gulosa: vai sempre ao peão mais próximo
        int resolverGuloso();
        
};

#endif