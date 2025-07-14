#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <chrono>

//using namespace std;

// Classe que representa a posição da rainha
class Peca {
private:
    int x, y;

public:

    Peca(int x = 0, int y = 0) : x(x), y(y) {}

    // Retorna a posição da rainha como um par (linha, coluna)
    pair<int, int> posicao() const {
        return {x, y};
    }
};

// Classe principal que resolve o problema da captura de peões
class TabuleiroRainha {
private:
    int N, M, K;                           // Dimensões do tabuleiro e número de peões
    vector<string> tabuleiro;             // Matriz do tabuleiro (entrada)
    Peca rainha;                        // Objeto que representa a rainha
    vector<Peca> peoes;                   // Vetor com todos os peões

    // Matrizes de distâncias calculadas
    vector<int> dist_rainha;              // Distância da rainha para cada peão
    vector<vector<int>> dist_peoes;       // Distância entre todos os pares de peões

    // Busca em largura adaptada para movimentos da rainha
    vector<vector<int>> bfs(pair<int, int> inicio) {
        vector<vector<int>> dist(N, vector<int>(M, -1)); // -1 = ainda não visitado
        queue<pair<int, int>> fila;
        dist[inicio.first][inicio.second] = 0;
        fila.push(inicio);

        // Movimentos da rainha (8 direções)
        vector<pair<int, int>> direcoes = {
            {-1,  0}, {1,  0}, {0, -1}, {0,  1},
            {-1, -1}, {-1, 1}, {1, -1}, {1,  1}
        };

        // Realiza BFS em cada direção até encontrar obstáculo
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

    // Pré-processa todas as distâncias necessárias (rainha → peões, peões ↔ peões)
    void calcularTodasDistancias() {
        dist_rainha.resize(K);
        dist_peoes.assign(K, vector<int>(K, -1));

        // Distâncias da rainha até todos os peões
        auto dist_da_rainha = bfs(rainha.posicao());
        for (int i = 0; i < K; ++i) {
            auto [px, py] = peoes[i].posicao();
            dist_rainha[i] = dist_da_rainha[px][py];
        }

        // Distâncias entre todos os pares de peões
        for (int i = 0; i < K; ++i) {
            auto dist_do_peao = bfs(peoes[i].posicao());
            for (int j = 0; j < K; ++j) {
                auto [qx, qy] = peoes[j].posicao();
                dist_peoes[i][j] = dist_do_peao[qx][qy];
            }
        }
    }

public:
    // Construtor: inicializa o tabuleiro com seus elementos
    TabuleiroRainha(int n, int m, int k,
                    const vector<string>& tab,
                    const Peca& r,
                    const vector<Peca>& p)
        : N(n), M(m), K(k), tabuleiro(tab), rainha(r), peoes(p) {}

    // Resolve o problema com Programação Dinâmica + Bitmask
    int resolverTSP() {
        calcularTodasDistancias();

        int total_mascaras = 1 << K;
        vector<vector<int>> dp(total_mascaras, vector<int>(K, -1)); // -1 = estado inválido

        // Estados iniciais: rainha vai diretamente até algum peão
        for (int i = 0; i < K; ++i) {
            if (dist_rainha[i] != -1) {
                dp[1 << i][i] = dist_rainha[i];
            }
        }

        // Transições da DP: de um conjunto de peões visitados, tentar visitar mais um
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

        // Resposta final: menor custo para capturar todos os peões
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

// Função principal
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    vector<string> tabuleiro(N);
    Peca rainha;
    vector<Peca> peoes;

    // Leitura do tabuleiro e localização da rainha e dos peões
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

    // Criação do objeto e resolução do problema
    TabuleiroRainha jogo(N, M, K, tabuleiro, rainha, peoes);

    // Início da medição de tempo
    auto inicio = chrono::high_resolution_clock::now();

    int resposta = jogo.resolverTSP();

    auto fim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duracao = fim - inicio;

    std::cout << resposta << '\n';

    // Saída da duração
    std::cout << "Tempo de execução: " << duracao.count() << " ms" << std::endl;

    return 0;
}
