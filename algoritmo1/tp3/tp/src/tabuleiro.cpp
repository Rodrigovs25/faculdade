#include "tabuleiro.hpp"

Tabuleiro::Tabuleiro(){
    this->n = 0;
    this->m = 0;
    this->k = 0;
    this->tabuleiro = {};
    this->rainha = {0, 0};
    this->peoes = {};
}

// Construtor: inicializa o tabuleiro com seus elementos
Tabuleiro::Tabuleiro(int n, int m, int k,
                const std::vector<std::string>& tabuleiro,
                const Peca& rainha,
                const std::vector<Peca>& peoes)
    : n(n), m(m), k(k), tabuleiro(tabuleiro), rainha(rainha), peoes(peoes) {}

// Busca em largura adaptada para movimentos da rainha
std::vector<std::vector<int>> Tabuleiro::bfs(std::pair<int, int> inicio) {
    std::vector<std::vector<int>> dist(n, std::vector<int>(m, -1)); // -1 = ainda não visitado
    std::queue<std::pair<int, int>> fila;
    dist[inicio.first][inicio.second] = 0;
    fila.push(inicio);

    // Movimentos da rainha (8 direções)
    std::vector<std::pair<int, int>> direcoes = {
        {-1,  0}, {1,  0}, {0, -1}, {0,  1},
        {-1, -1}, {-1, 1}, {1, -1}, {1,  1}
    };

    // Realiza BFS em cada direção até encontrar obstáculo
    while (!fila.empty()) {
        auto [x, y] = fila.front(); fila.pop();
        int d = dist[x][y];

        for (auto [dx, dy] : direcoes) {
            int nx = x + dx, ny = y + dy;
            while (nx >= 0 && nx < n && ny >= 0 && ny < m && tabuleiro[nx][ny] != '-') {
                if (dist[nx][ny] == -1) {
                    dist[nx][ny] = d + 1;
                    fila.emplace(nx, ny);
                }
                nx += dx;
                ny += dy;
            }
        }
    }

    return dist;
}

// Pré-processa todas as distâncias necessárias (rainha → peões, peões ↔ peões)
void Tabuleiro::calcularTodasDistancias() {
    dist_rainha.resize(k);
    dist_peoes.assign(k, std::vector<int>(k, -1));

    // Distâncias da rainha até todos os peões
    auto dist_da_rainha = bfs(rainha.posicao());
    for (int i = 0; i < k; ++i) {
        auto [px, py] = peoes[i].posicao();
        dist_rainha[i] = dist_da_rainha[px][py];
    }

    // Distâncias entre todos os pares de peões
    for (int i = 0; i < k; ++i) {
        auto dist_do_peao = bfs(peoes[i].posicao());
        for (int j = 0; j < k; ++j) {
            auto [qx, qy] = peoes[j].posicao();
            dist_peoes[i][j] = dist_do_peao[qx][qy];
        }
    }
}

// Resolve o problema com Programação Dinâmica + Bitmask
int Tabuleiro::resolverCaixeiroViajante() {
    calcularTodasDistancias();

    int total_mascaras = 1 << k;
    std::vector<std::vector<int>> dp(total_mascaras, std::vector<int>(k, -1)); // -1 = estado inválido

    // Estados iniciais: rainha vai diretamente até algum peão
    for (int i = 0; i < k; ++i) {
        if (dist_rainha[i] != -1) {
            dp[1 << i][i] = dist_rainha[i];
        }
    }

    // Transições de um conjunto de peões visitados, tentar visitar mais um
    for (int mascara = 0; mascara < total_mascaras; ++mascara) {
        for (int u = 0; u < k; ++u) {
            if (!(mascara & (1 << u)) || dp[mascara][u] == -1) continue;

            for (int v = 0; v < k; ++v) {
                if (mascara & (1 << v)) continue;
                if (dist_peoes[u][v] == -1) continue;

                int nova_mascara = mascara | (1 << v);
                int novo_custo = dp[mascara][u] + dist_peoes[u][v];

                if (dp[nova_mascara][v] == -1 || dp[nova_mascara][v] > novo_custo) {
                    dp[nova_mascara][v] = novo_custo;
                }
            }
        }
    }

    // Resposta final: menor custo para capturar todos os peões
    int resultado = -1;
    int mascara_final = (1 << k) - 1;
    for (int i = 0; i < k; ++i) {
        if (dp[mascara_final][i] != -1) {
            if (resultado == -1 || dp[mascara_final][i] < resultado) {
                resultado = dp[mascara_final][i];
            }
        }
    }

    return resultado;
}

