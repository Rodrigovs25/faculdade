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

// Contrução do grafo
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

int main(int argc, char const *argv[]){

    // Arquivo de entrada
    std::ifstream inf;
    inf.open(argv[1]);
    if(!inf){
        std::cerr << "Arquivo não pode ser aberto!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Leitura da Ana e Bernando
    Pessoa Ana, Bernando;
    inf >> Ana.coordenada.x >> Ana.coordenada.y;
    inf >> Bernando.coordenada.x >> Bernando.coordenada.y;

    int numero_abrigos;
    inf >> numero_abrigos;

    // Leitura dos abrigos
    std::vector<Abrigo> abrigos(numero_abrigos);
    for(int i = 0; i < numero_abrigos; ++i){
        inf >> abrigos[i].raio >> abrigos[i].centro.x >> abrigos[i].centro.y;
    }

    // Abrigo de Ana e Bernando
    int abrigo_ana = encontrar_abrigo(abrigos, Ana.coordenada);
    int abrigo_bernando = encontrar_abrigo(abrigos, Bernando.coordenada);

    if(abrigo_ana == -1 || abrigo_bernando == -1){
        std::cout << "NENHUM" << std::endl;
        //return 0;
    }

    auto grafo = construir_grafo(abrigos);

    if(caminho_possivel(abrigo_ana, abrigo_bernando, grafo)){
        std::cout << "SIM" << std::endl;
    } else {
        std::cout << "NAO" << std::endl;
    }
    
    return 0;

}
