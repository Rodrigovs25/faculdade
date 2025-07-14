#include "fluxoMaximo.hpp"

FluxoMaximo::FluxoMaximo(int n)
    : grafo(n), nivel(n), iterador(n), totalCapacidade(0) {}

void FluxoMaximo::adicionarAresta(int noOrigem, int noDestino, int capacidade) {
    grafo[noOrigem].push_back({noDestino, (int)grafo[noDestino].size(), capacidade});
    grafo[noDestino].push_back({noOrigem, (int)grafo[noOrigem].size() - 1, 0}); // Aresta reversa com capacidade 0
}

int FluxoMaximo::edmondsKarp(int origem, int destino) {
    int fluxo = 0;
    while (true) {
        fill(nivel.begin(), nivel.end(), -1);
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
        
        fill(iterador.begin(), iterador.end(), 0); // Resetar os valores do vetor
        int f;
        // Busca por caminhos aumentantes via DFS
        while ((f = enviarFluxo(origem, destino, totalCapacidade)) > 0) {
            fluxo += f;
        }
    }
    return fluxo;
}

void FluxoMaximo::setLimite(int limite) {
    this->totalCapacidade = limite;
}

// Função recursiva que tenta empurrar fluxo do nó atual até o destino,
// seguindo apenas arestas com capacidade residual positiva e que respeitam
// os níveis construídos pela BFS. Retorna a quantidade de fluxo que foi possível
// enviar ao longo do caminho encontrado, ou 0 se não for possível.
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