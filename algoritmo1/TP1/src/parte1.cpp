#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <queue>

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
    for(int i = 0; i < abrigos.size(); ++i) {
        int dx = abrigos[i].centro.x - p.x;
        int dy = abrigos[i].centro.y - p.y;
        int dist2 = dx*dx + dy*dy;
        if(dist2 <= abrigos[i].raio * abrigos[i].raio) {
            return i;
        }
    }
    return -1;
}

bool caminho_possivel(int inicio, int destino, const std::vector<std::vector<int>>& grafo) {
    std::vector<bool> visitado(grafo.size(), false);
    std::queue<int> fila;

    fila.push(inicio);
    visitado[inicio] = true;

    while(!fila.empty()) {
        int atual = fila.front();
        fila.pop();

        if(atual == destino) return true;

        for(int vizinho : grafo[atual]) {
            if(!visitado[vizinho]) {
                visitado[vizinho] = true;
                fila.push(vizinho);
            }
        }
    }

    return false;
}

std::vector<std::vector<int>> construir_grafo(const std::vector<Abrigo>& abrigos) {
    int n = abrigos.size();
    std::vector<std::vector<int>> grafo(n);
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
    return grafo;
}

int bfs_min_distance(const std::vector<std::vector<int>>& graph, int start, int end) {
    std::queue<std::pair<int, int>> fila;
    std::vector<bool> visitado(graph.size(), false);

    fila.push({start, 0}); // Contamos o abrigo de início
    visitado[start] = true;

    while (!fila.empty()) {
        auto [atual, dist] = fila.front();
        fila.pop();

        if (atual == end)
            return dist;

        for (int vizinho : graph[atual]) {
            if (!visitado[vizinho]) {
                visitado[vizinho] = true;
                fila.push({vizinho, dist + 1});
            }
        }
    }

    return 0; // Não há caminho
}

int main(int argc, char const *argv[]){

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

    int abrigo_ana = encontrar_abrigo(abrigos, Ana.coordenada);
    int abrigo_bernando = encontrar_abrigo(abrigos, Bernando.coordenada);

    if(abrigo_ana == -1 || abrigo_bernando == -1){
        std::cout << "Parte1: -1" << std::endl;
    } else {
        auto grafo = construir_grafo(abrigos);
        int respostaParte1 = bfs_min_distance(grafo, abrigo_ana, abrigo_bernando);
        if (respostaParte1 == 0)
            std::cout << "Parte1: -1" << std::endl;
        else
            std::cout << "Parte1: " << respostaParte1 << std::endl;

    }

    return 0;
}
