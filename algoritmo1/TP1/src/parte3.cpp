#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

struct Ponto {
    int x, y;
};

struct Pessoa {
    Ponto coordenada;
};

struct Abrigo {
    int raio;
    Ponto centro;
};

int encontrar_abrigo(const std::vector<Abrigo>& abrigos, Ponto p) {
    int n = static_cast<int>(abrigos.size());
    for(int i = 0; i < n; ++i) {
        int dx = abrigos[i].centro.x - p.x;
        int dy = abrigos[i].centro.y - p.y;
        int dist2 = dx*dx + dy*dy;
        if(dist2 <= abrigos[i].raio * abrigos[i].raio) {
            return i;
        }
    }
    return -1;
}

void construir_grafo(const std::vector<Abrigo>& abrigos, std::vector<std::vector<int>>& grafo) {
    int n = static_cast<int>(abrigos.size());
    grafo.assign(n, std::vector<int>());
    for(int i = 0; i < n; ++i){
        for(int j = i + 1; j < n; ++j){
            int dx = abrigos[i].centro.x - abrigos[j].centro.x;
            int dy = abrigos[i].centro.y - abrigos[j].centro.y;
            int dist2 = dx*dx + dy*dy;
            int rsum = abrigos[i].raio + abrigos[j].raio;
            if(dist2 <= rsum * rsum){
                grafo[i].push_back(j);
                grafo[j].push_back(i);
            }
        }
    }
}

int bfs(const std::vector<std::vector<int>>& grafo, int inicio, int alvo = -1) {
    std::queue<std::pair<int, int>> fila;
    std::vector<bool> visitado(grafo.size(), false);
    fila.push({inicio, 0});
    visitado[inicio] = true;

    int maxDist = 0;

    while (!fila.empty()) {
        auto [atual, dist] = fila.front(); fila.pop();
        if (atual == alvo) return dist;
        maxDist = std::max(maxDist, dist);

        for (int vizinho : grafo[atual]) {
            if (!visitado[vizinho]) {
                visitado[vizinho] = true;
                fila.push({vizinho, dist + 1});
            }
        }
    }

    return (alvo == -1 ? maxDist : 0);
}

int calcular_maior_distancia(const std::vector<std::vector<int>>& grafo) {
    int maior = 0;
    std::vector<bool> visitado(grafo.size(), false);
    int n = static_cast<int>(grafo.size());
    for (int i = 0; i < n; ++i) {
        if (!visitado[i]) {
            // Encontra um vértice distante no componente
            std::queue<int> fila;
            std::vector<int> dist(grafo.size(), -1);
            fila.push(i);
            dist[i] = 0;
            visitado[i] = true;
            int u = i;

            while (!fila.empty()) {
                int atual = fila.front(); fila.pop();
                for (int viz : grafo[atual]) {
                    if (dist[viz] == -1) {
                        dist[viz] = dist[atual] + 1;
                        visitado[viz] = true;
                        fila.push(viz);
                        u = viz; // último visitado será o mais distante
                    }
                }
            }

            // Acha a maior distância a partir do vértice mais distante encontrado
            maior = std::max(maior, bfs(grafo, u));
        }
    }

    return maior;
}

int calcular_maior_distancia(const std::vector<std::vector<int>>& grafo) {
    int n = static_cast<int>(grafo.size());
    std::vector<bool> visitado(n, false);
    int maior = 0;

    for (int i = 0; i < n; ++i) {
        if (!visitado[i]) {
            // Primeiro BFS para achar o ponto mais distante
            std::queue<int> fila;
            std::vector<int> dist(n, -1);
            fila.push(i);
            dist[i] = 0;
            visitado[i] = true;

            int mais_distante = i;

            while (!fila.empty()) {
                int atual = fila.front(); fila.pop();
                for (int viz : grafo[atual]) {
                    if (dist[viz] == -1) {
                        dist[viz] = dist[atual] + 1;
                        fila.push(viz);
                        visitado[viz] = true;
                        if (dist[viz] > dist[mais_distante]) {
                            mais_distante = viz;
                        }
                    }
                }
            }

            // Segundo BFS a partir do mais distante
            int dist_max = bfs(grafo, mais_distante);
            maior = std::max(maior, dist_max);
        }
    }

    return maior;
}

void dfs(int u, int p, int &timer,
         const std::vector<std::vector<int>>& grafo,
         std::vector<bool>& visitado,
         std::vector<int>& tin,
         std::vector<int>& low,
         std::set<int>& articulacoes) {
    
    visitado[u] = true;
    tin[u] = low[u] = timer++;
    int filhos = 0;

    for (int v : grafo[u]) {
        if (v == p) continue; // ignora aresta para o pai

        if (visitado[v]) {
            low[u] = std::min(low[u], tin[v]);
        } else {
            dfs(v, u, timer, grafo, visitado, tin, low, articulacoes);
            low[u] = std::min(low[u], low[v]);
            if (low[v] >= tin[u] && p != -1) {
                articulacoes.insert(u);
            }
            filhos++;
        }
    }

    if (p == -1 && filhos > 1) {
        articulacoes.insert(u);
    }
}

std::vector<int> abrigos_criticos(const std::vector<std::vector<int>>& grafo) {
    int n = static_cast<int>(grafo.size());
    std::vector<bool> visitado(n, false);
    std::vector<int> tin(n, -1), low(n, -1);
    std::set<int> articulacoes;
    int timer = 0;

    for (int i = 0; i < n; ++i) {
        if (!visitado[i]) {
            dfs(i, -1, timer, grafo, visitado, tin, low, articulacoes);
        }
    }

    std::vector<int> resultado(articulacoes.begin(), articulacoes.end());
    for (int &i : resultado) i += 1; // base 1
    std::sort(resultado.begin(), resultado.end());
    return resultado;
}



int main(int /*argc*/, char const *argv[]){

    std::ifstream inf;
    inf.open(argv[1]);
    if(!inf){
        std::cerr << "Arquivo não pode ser aberto!" << std::endl;
        exit(EXIT_FAILURE);
    }

    Pessoa Ana, Bernando;
    inf >> Ana.coordenada.x >> Ana.coordenada.y;
    inf >> Bernando.coordenada.x >> Bernando.coordenada.y;

    int numero_abrigos;
    inf >> numero_abrigos;

    std::vector<Abrigo> abrigos(numero_abrigos);
    for(int i = 0; i < numero_abrigos; ++i){
        inf >> abrigos[i].raio >> abrigos[i].centro.x >> abrigos[i].centro.y;
    }

    // Parte 1

    int abrigo_ana = encontrar_abrigo(abrigos, Ana.coordenada);
    int abrigo_bernando = encontrar_abrigo(abrigos, Bernando.coordenada);

    if(abrigo_ana == -1 || abrigo_bernando == -1)
        std::cout << "Parte1: -1" << std::endl;
    std::vector<std::vector<int>> grafo;
    construir_grafo(abrigos, grafo);
    int respostaParte1 = bfs(grafo, abrigo_ana, abrigo_bernando);
    if (respostaParte1 == 0)
        std::cout << "Parte1: -1" << std::endl;
    else
        std::cout << "Parte1: " << respostaParte1 << std::endl;


    // Parte 2
    int respostaParte2 = calcular_maior_distancia(grafo);
    std::cout << "Parte2: " << respostaParte2 << std::endl;

    // Parte 3
    auto criticos = abrigos_criticos(grafo);
    std::cout << "Parte3: " << criticos.size();
    for (int idx : criticos) {
        std::cout << " " << idx; // Já na base 1
    }
    std::cout << std::endl;

    return 0;
}