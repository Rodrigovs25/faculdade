#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class TabuleiroRainha {
private:
    int N, M, K;
    vector<string> tabuleiro;
    pair<int, int> rainha;
    vector<pair<int, int>> peoes;
    vector<bool> capturado;

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
    TabuleiroRainha(int n, int m, int k,
                    const vector<string>& tab,
                    const pair<int, int>& r,
                    const vector<pair<int, int>>& p)
        : N(n), M(m), K(k), tabuleiro(tab), rainha(r), peoes(p), capturado(k, false) {}

    int resolverAproximado() {
        int movimentos_totais = 0;
        pair<int, int> atual = rainha;

        for (int etapa = 0; etapa < K; ++etapa) {
            auto dist = bfs(atual);
            int melhor = -1;
            int menor_dist = -1;

            for (int i = 0; i < K; ++i) {
                if (capturado[i]) continue;
                auto [x, y] = peoes[i];
                if (dist[x][y] != -1) {
                    if (menor_dist == -1 || dist[x][y] < menor_dist) {
                        menor_dist = dist[x][y];
                        melhor = i;
                    }
                }
            }

            if (melhor == -1) return -1;

            capturado[melhor] = true;
            movimentos_totais += menor_dist;
            atual = peoes[melhor];
        }

        return movimentos_totais;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    vector<string> tabuleiro(N);
    pair<int, int> rainha;
    vector<pair<int, int>> peoes;

    for (int i = 0; i < N; ++i) {
        cin >> tabuleiro[i];
        for (int j = 0; j < M; ++j) {
            if (tabuleiro[i][j] == 'R') {
                rainha = {i, j};
            } else if (tabuleiro[i][j] == 'P') {
                peoes.emplace_back(i, j);
            }
        }
    }

    TabuleiroRainha jogo(N, M, K, tabuleiro, rainha, peoes);
    int resposta = jogo.resolverAproximado();
    cout << resposta << '\n';

    return 0;
}
