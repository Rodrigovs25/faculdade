#include "fluxoMaximo.hpp"

FluxoMaximo::FluxoMaximo() {
    this->grafo = {};
    this->nivel = {};
    this->iterador = {};
    this->totalCapacidade = 0;
}

FluxoMaximo::FluxoMaximo(int n, int limite) 
    : grafo(n), nivel(n), iterador(n), 
    totalCapacidade(limite) {} // O limite máximo de fluxo (soma de todas as capacidades da matriz)
    

void FluxoMaximo::adicionarAresta(int noOrigem, int noDestino, int capacidade) {
    grafo[noOrigem].push_back({noDestino, (int)grafo[noDestino].size(), capacidade});
    grafo[noDestino].push_back({noOrigem, (int)grafo[noOrigem].size() - 1, 0}); // Aresta reversa com capacidade 0
}

int FluxoMaximo::edmondsKarp(int origem, int destino) {
    int fluxo = 0;
    while (true) {
        for (size_t i = 0; i < nivel.size(); i++) {
            nivel[i] = -1;
        }
        nivel[origem] = 0;
        std::queue<int> fila;
        fila.push(origem);
        
        // Construção dos níveis via BFS
        while (!fila.empty()) {
            int noAtual = fila.front(); 
            fila.pop();
            for (const Aresta &e : grafo[noAtual]) {
                if (e.capacidade > 0 && nivel[e.destino] < 0) {
                    nivel[e.destino] = nivel[noAtual] + 1;
                    fila.push(e.destino);
                }
            }
        }
        
        if (nivel[destino] < 0) break; // Não há mais caminho
        for (size_t i = 0; i < iterador.size(); i++) {
            iterador[i] = 0;
        }
        int fluxoEnviado;
        // Busca por caminhos aumentantes via DFS
        while ((fluxoEnviado = enviarFluxo(origem, destino, totalCapacidade)) > 0) {
            fluxo += fluxoEnviado;
        }
    }
    return fluxo;
}

int FluxoMaximo::enviarFluxo(int noAtual, int destino, int limite) {
    if (noAtual == destino) return limite;
    for (int &i = iterador[noAtual]; i < (int)grafo[noAtual].size(); ++i) {
        Aresta &e = grafo[noAtual][i];
        if (e.capacidade > 0 && nivel[noAtual] < nivel[e.destino]) {
            int d = enviarFluxo(e.destino, destino, std::min(limite, e.capacidade));
            if (d > 0) {
                e.capacidade -= d;
                grafo[e.destino][e.reversa].capacidade += d;
                return d;
            }
        }
    }
    return 0;
}