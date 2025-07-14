#include <iostream>
#include <fstream>
#include "pessoa.hpp"
#include "abrigo.hpp"
#include "funcao.hpp"

int main(int /*argc*/, char const *argv[])
{
    std::ifstream inf;
    inf.open(argv[1]);
    if(!inf){
        std::cerr << "Arquivo não pode ser aberto!" << std::endl;
        exit(EXIT_FAILURE);
    }

    int anaX, anaY, bernardoX, bernardoY;
    inf >> anaX >> anaY;
    inf >> bernardoX >> bernardoY;

    Pessoa Ana(Ponto(anaX, anaY));
    Pessoa Bernardo(Ponto(bernardoX, bernardoY));

    int numeroAbrigos;
    inf >> numeroAbrigos;

    int raio, x, y;
    std::vector<Abrigo> abrigos(numeroAbrigos);
    for(int i = 0; i < numeroAbrigos; ++i){
        inf >> raio >> x >> y;
        abrigos[i] = Abrigo(raio, Ponto(x, y));
    }

    // Parte 1

    Abrigo ana(0, Ana.getCoordenada()), bernardo(0, Bernardo.getCoordenada());
    int abrigoAna = ana.encontrarAbrigo(abrigos);
    int abrigoBernardo = bernardo.encontrarAbrigo(abrigos);
    
    std::vector<std::vector<int>> grafo;
    construirGrafo(abrigos, grafo);
    int respostaParte1 = bfs(grafo, abrigoAna, abrigoBernardo);
    if (respostaParte1 == 0 || abrigoAna == -1 || abrigoBernardo == -1)
        std::cout << "Parte1: -1" << std::endl;
    else
        std::cout << "Parte1: " << respostaParte1 << std::endl;


    // Parte 2
    int respostaParte2 = encontrarDiametro(grafo);
    std::cout << "Parte2: " << respostaParte2 << std::endl;

    // Parte 3
    std::set<int> criticos = encontrarAbrigosCriticos(grafo);
    std::cout << "Parte3: " << criticos.size();
    for (int idx : criticos) {
        std::cout << " " << idx+1; // Aumenta em 1, pois o índice comecça do 0
    }
    std::cout << std::endl;

    return 0;
}
