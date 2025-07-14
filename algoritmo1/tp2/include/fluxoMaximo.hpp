#ifndef FLUXO_MAXIMO_HPP
#define FLUXO_MAXIMO_HPP

#include <iostream>
#include <vector>
#include <queue>

struct Aresta {
    int destino, reversa;
    int capacidade;
};

// Classe para cálculo de fluxo máximo usando o algoritmo de Edmonds-Karp
class FluxoMaximo {
    private:
        std::vector<std::vector<Aresta>> grafo;
        std::vector<int> nivel;
        std::vector<int> iterador;
        int totalCapacidade;

        // Função auxiliar para encontrar fluxo aumentante
        int enviarFluxo(int noAtual, int destino, int limite);

    public:
        FluxoMaximo(int n);  
        
        // Adiciona uma aresta ao grafo com capacidade 'capacidade'
        void adicionarAresta(int noOrigem, int noDestino, int capacidade);

        // Implementação do algoritmo Edmonds-Karp (BFS para caminhos aumentantes)
        int edmondsKarp(int origem, int destino);
        
        // Define o limite máximo de fluxo (soma de todas as capacidades da matriz)
        void setLimite(int limite);

};

#endif