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
    vector<int> dist_rainha;
    vector<vector<int>> dist_peoes;

    vector<vector<int>> bfs(pair<int, int> inicio) {
        vector<vector<int>> dist(N, vector<int>(M, -1));
        queue<pair<int, int>> fila;
        dist[inicio.first][inicio.second] = 0;
        fila.push(inicio);

        vector<pair<int, int>> direcoes = { // vetor de deslocamento, 8 direções da rainha
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

    void calcularTodasDistancias() {
        dist_rainha.resize(K);
        dist_peoes.assign(K, vector<int>(K, -1));

        auto dist_da_rainha = bfs(rainha);
        for (int i = 0; i < K; ++i) {
            auto [px, py] = peoes[i];
            dist_rainha[i] = dist_da_rainha[px][py];
        }

        for (int i = 0; i < K; ++i) {
            auto dist_do_peao = bfs(peoes[i]);
            for (int j = 0; j < K; ++j) {
                auto [qx, qy] = peoes[j];
                dist_peoes[i][j] = dist_do_peao[qx][qy];
            }
        }
    }

public:

    TabuleiroRainha(int n, int m, int k,
                    const vector<string>& tab,
                    const pair<int, int>& r,
                    const vector<pair<int, int>>& p)
        : N(n), M(m), K(k), tabuleiro(tab), rainha(r), peoes(p) {}

    int resolverTSP() {
        calcularTodasDistancias();

        int total_mascaras = 1 << K;
        vector<vector<int>> dp(total_mascaras, vector<int>(K, -1));

        for (int i = 0; i < K; ++i) {
            if (dist_rainha[i] != -1) {
                dp[1 << i][i] = dist_rainha[i];
            }
        }

        for (int mascara = 0; mascara < total_mascaras; ++mascara) {
            for (int u = 0; u < K; ++u) {
                if (!(mascara & (1 << u)) || dp[mascara][u] == -1) continue;

                for (int v = 0; v < K; ++v) {
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

        int resultado = -1;
        int mascara_final = (1 << K) - 1;
        for (int i = 0; i < K; ++i) {
            if (dp[mascara_final][i] != -1) {
                if (resultado == -1 || dp[mascara_final][i] < resultado) {
                    resultado = dp[mascara_final][i];
                }
            }
        }

        return resultado;
    }
};

// ========== FUNÇÃO PRINCIPAL ============
int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    vector<string> tabuleiro(N);
    pair<int, int> rainha;
    vector<pair<int, int>> peoes;

    for (int i = 0; i < N; i++) {
        cin >> tabuleiro[i];
        for (int j = 0; j < M; j++) {
            if (tabuleiro[i][j] == 'R') {
                rainha = {i, j};
            } else if (tabuleiro[i][j] == 'P') {
                peoes.emplace_back(i, j);
            }
        }
    }

    TabuleiroRainha jogo(N, M, K, tabuleiro, rainha, peoes);
    int resposta = jogo.resolverTSP();
    cout << resposta << '\n';

    return 0;
}
