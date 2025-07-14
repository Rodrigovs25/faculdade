#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <chrono>

using namespace std;

// Classe genérica que representa uma peça (rainha ou peão) pela sua posição
class Peca {
private:
    int x, y;

public:
    Peca(int x = 0, int y = 0) : x(x), y(y) {}

    pair<int, int> posicao() const {
        return {x, y};
    }
};

// Classe que encapsula a lógica da versão aproximada (gulosa)
class TabuleiroRainha {
private:
    int N, M, K;
    vector<string> tabuleiro;
    Peca rainha;
    vector<Peca> peoes;
    vector<bool> capturado; // Marca se o peão já foi capturado

    // BFS adaptado para movimentos da rainha em 8 direções
    vector<vector<int>> bfs(pair<int, int> inicio) {
        vector<vector<int>> dist(N, vector<int>(M, -1));
        queue<pair<int, int>> fila;
        dist[inicio.first][inicio.second] = 0;
        fila.push(inicio);

        vector<pair<int, int>> direcoes = {
            {-1,  0}, {1,  0}, {0, -1}, {0,  1},
            {-1, -1}, {-1, 1}, {1, -1}, {1,  1}
        };

        while (!fila.empty()) {
            auto [x, y] = fila.front(); fila.pop();
            int d = dist[x][y];

            for (auto [dx, dy] : direcoes) {
                int nx = x + dx, ny = y + dy;
                while (nx >= 0 && nx < N && ny >= 0 && ny < M && tabuleiro[nx][ny] != '-') {
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

public:
    // Construtor com inicialização direta
    TabuleiroRainha(int n, int m, int k,
                    const vector<string>& tab,
                    const Peca& r,
                    const vector<Peca>& p)
        : N(n), M(m), K(k), tabuleiro(tab), rainha(r), peoes(p), capturado(k, false) {}

    // Solução gulosa: vai sempre ao peão mais próximo
    int resolverAproximado() {
        int total_movimentos = 0;
        pair<int, int> atual = rainha.posicao();

        for (int etapa = 0; etapa < K; ++etapa) {
            auto dist = bfs(atual);
            int melhor = -1;
            int menor_dist = -1;

            // Escolhe o peão mais próximo ainda não capturado
            for (int i = 0; i < K; ++i) {
                if (capturado[i]) continue;

                auto [x, y] = peoes[i].posicao();
                if (dist[x][y] != -1) {
                    if (menor_dist == -1 || dist[x][y] < menor_dist) {
                        menor_dist = dist[x][y];
                        melhor = i;
                    }
                }
            }

            // Se não há mais peões acessíveis, falha
            if (melhor == -1) return -1;

            capturado[melhor] = true;
            total_movimentos += menor_dist;
            atual = peoes[melhor].posicao();
        }

        return total_movimentos;
    }
};

// Função principal
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    vector<string> tabuleiro(N);
    Peca rainha;
    vector<Peca> peoes;

    for (int i = 0; i < N; ++i) {
        cin >> tabuleiro[i];
        for (int j = 0; j < M; ++j) {
            if (tabuleiro[i][j] == 'R') {
                rainha = Peca(i, j);
            } else if (tabuleiro[i][j] == 'P') {
                peoes.emplace_back(i, j);
            }
        }
    }

    TabuleiroRainha jogo(N, M, K, tabuleiro, rainha, peoes);

    // Início da medição de tempo
    auto inicio = chrono::high_resolution_clock::now();

    int resposta = jogo.resolverAproximado();

    auto fim = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracao = fim - inicio;

    cout << resposta << '\n';

    // Saída da duração
    cerr << "Tempo de execução: " << duracao.count() << " ms\n";

    return 0;
}
