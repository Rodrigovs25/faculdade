#include "funcao.hpp"

void construirGrafo(const std::vector<Abrigo>& abrigos, std::vector<std::vector<int>>& grafo) {
    int numeroVertices = static_cast<int>(abrigos.size());
    grafo.assign(numeroVertices, std::vector<int>());
    for(int i = 0; i < numeroVertices; ++i){
        for(int j = i + 1; j < numeroVertices; ++j){
            int distanciaEntreCentros = abrigos[i].getCentro().distanciaEntreDoisPontos(abrigos[j].getCentro());
            int somaRaios = abrigos[i].getRaio() + abrigos[j].getRaio();
            if(distanciaEntreCentros <= somaRaios * somaRaios){
                grafo[i].push_back(j);
                grafo[j].push_back(i);
            }
        }
    }
}

// Parte 1

int bfs(const std::vector<std::vector<int>>& grafo, int origem, int destino  = -1) {
    std::queue<std::pair<int, int>> fila; // Fila para BFS, armazena pares (vértice, distância)
    std::vector<bool> visitado(grafo.size(), false); // Vetor para marcar os vértices já visitados
    fila.push({origem, 0}); // Começa a partir do vértice inicial
    visitado[origem] = true;

    int maiorDistancia = 0; //Maior distância encontrada (caso destino  == -1)

    // Loop principal da BFS: visita os vértices em largura
    while (!fila.empty()) {
        auto [atual, dist] = fila.front(); fila.pop(); // Pega o vértice atual e sua distância

        if (atual == destino ) return dist;
        // Atualiza a maior distância, se for o caso
        maiorDistancia = std::max(maiorDistancia, dist);

        // Visita todos os vizinhos do vértice atual
        for (int vizinho : grafo[atual]) {
            if (!visitado[vizinho]) {
                visitado[vizinho] = true;
                fila.push({vizinho, dist + 1});
            }
        }
    }

    return (destino == -1 ? maiorDistancia : 0);
}

// Parte 2

int encontrarDiametro(const std::vector<std::vector<int>>& grafo) {
    int diametro = 0; // Armazena o maior valor de menor distância (diâmetro)
    std::vector<bool> visitado(grafo.size(), false); // Marca os vértices visitados
    int numeroVertices = static_cast<int>(grafo.size()); // Número total de vértices
    for (int i = 0; i < numeroVertices; ++i) {
        // Encontra o vértice distante no componente
        if (!visitado[i]) {
            std::queue<int> fila; // Fila para a BFS
            std::vector<int> distancia(numeroVertices, -1); // Distância de cada vértice a partir de i
            fila.push(i);
            distancia[i] = 0;
            visitado[i] = true;
            int verticeDistante = i; 
            
            // Percorre a fila
            while (!fila.empty()) {
                int atual = fila.front(); fila.pop();
                for (int vizinho : grafo[atual]) {
                    if (distancia[vizinho] == -1) {
                        distancia[vizinho] = distancia[atual] + 1;
                        visitado[vizinho] = true;
                        fila.push(vizinho);
                        verticeDistante = vizinho; // Atualiza o vértice mais distante
                    }
                }
            }

            // Acha o diâmetro a partir do vértice mais distante encontrado
            diametro = std::max(diametro, bfs(grafo, verticeDistante));
        }
    }

    return diametro;
}

// Parte 3

void dfs(int verticeAtual, int verticePai, int &tempo,
         const std::vector<std::vector<int>>& grafo,
         std::vector<bool>& visitado,
         std::vector<int>& discoveryTime,
         std::vector<int>& lowLink,
         std::set<int>& articulacoes) {
    
    visitado[verticeAtual] = true;
    discoveryTime[verticeAtual] = lowLink[verticeAtual] = tempo++; // Define tempo de descoberta e inicializa o menor tempo alcançável
    int numeroFilhos = 0; // Número de filhos na árvore de DFS

    // Explora todos os vizinhos de verticeAtual        
    for (int vizinho : grafo[verticeAtual]) {
        if (vizinho == verticePai) continue; // Ignora aresta para o pai

        if (visitado[vizinho]) {
            // Se já foi visitado, atualiza o lowLink do verticeAtual
            lowLink[verticeAtual] = std::min(lowLink[verticeAtual], discoveryTime[vizinho]);
        } else {
            // Se não foi visitado, realiza DFS recursiva
            dfs(vizinho, verticeAtual, tempo, grafo, visitado, discoveryTime, lowLink, articulacoes);
            lowLink[verticeAtual] = std::min(lowLink[verticeAtual], lowLink[vizinho]);
            // Verifica se verticeAtual é ponto de articulação
            if (lowLink[vizinho] >= discoveryTime[verticeAtual] && verticePai != -1) {
                articulacoes.insert(verticeAtual);
            }
            numeroFilhos++;
        }
    }

    // Verifique se verticeAtual for raiz da DFS e tiver mais de um filho, logo verticeAtual é ponto de articulação
    if (verticePai == -1 && numeroFilhos > 1) {
        articulacoes.insert(verticeAtual);
    }
}

// Retorna um conjunto de índices dos vértices que são pontos de articulação, começa do 0
std::set<int> encontrarAbrigosCriticos(const std::vector<std::vector<int>>& grafo) {
    int n = static_cast<int>(grafo.size());
    std::vector<bool> visitado(n, false); // Marca vértices visitados
    std::vector<int> discoveryTime(n, -1); // Marca o tempo de descoberta de cada vértice
    std::vector<int> low(n, -1); // Marca o menor tempo alcançável a partir de cada vértice
    std::set<int> articulacoes;  // Conjunto dos pontos de articulação
    int tempo = 0;

    // Aplica DFS para cada componente conexo não visitado
    for (int i = 0; i < n; ++i) {
        if (!visitado[i]) {
            dfs(i, -1, tempo, grafo, visitado, discoveryTime, low, articulacoes);
        }
    }

    return articulacoes;
}