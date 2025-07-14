#ifndef FUNCAO_HPP
#define FUNCAO_HPP

#include <set>
#include <queue>
#include <algorithm>
#include "abrigo.hpp"

// Constrói o grafo de conexões entre abrigos com base na distância dos centros e seus raios
void construirGrafo(const std::vector<Abrigo>& abrigos, std::vector<std::vector<int>>& grafo);

// Executa uma BFS no grafo entre dois vértices (se alvo != -1) ou retorna a maior distância de um vértice (se alvo == -1)
int bfs(const std::vector<std::vector<int>>& grafo, int inicio, int alvo);

// Calcula maior diâmetro de todos os componentes do grafo
int encontrarDiametro(const std::vector<std::vector<int>>& grafo);

// DFS modificada para detectar pontos de articulação (abrigos críticos)
void dfs(int u, int p, int &timer,
         const std::vector<std::vector<int>>& grafo,
         std::vector<bool>& visitado,
         std::vector<int>& tin,
         std::vector<int>& low,
         std::set<int>& articulacoes);

// Encontra os abrigos críticos (pontos de articulação) no grafo         
std::set<int> encontrarAbrigosCriticos(const std::vector<std::vector<int>>& grafo);

#endif 