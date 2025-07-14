#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int N, M, K;
vector<string> board;
pair<int, int> queen;
vector<pair<int, int>> pawns;

// =================== LEITURA ===================
void readInput() {
    cin >> N >> M >> K;
    board.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> board[i];
        for (int j = 0; j < M; j++) {
            if (board[i][j] == 'R') {
                queen = {i, j};
            } else if (board[i][j] == 'P') {
                pawns.emplace_back(i, j);
            }
        }
    }
}

// ============ BFS DA RAINHA ===============
vector<vector<int>> bfs(pair<int, int> start) {
    vector<vector<int>> dist(N, vector<int>(M, -1));
    queue<pair<int, int>> q;
    dist[start.first][start.second] = 0;
    q.push(start);

    vector<pair<int, int>> directions = {
        {-1,  0}, {1,  0}, {0, -1}, {0,  1},
        {-1, -1}, {-1, 1}, {1, -1}, {1,  1}
    };

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        int d = dist[x][y];

        for (auto [dx, dy] : directions) {
            int nx = x + dx, ny = y + dy;
            while (nx >= 0 && nx < N && ny >= 0 && ny < M && board[nx][ny] != '-') {
                if (dist[nx][ny] == -1) {
                    dist[nx][ny] = d + 1;
                    q.emplace(nx, ny);
                }
                nx += dx;
                ny += dy;
            }
        }
    }

    return dist;
}

// ============== DISTÂNCIAS ===================
vector<int> dist_queen;                    // rainha -> peões
vector<vector<int>> dist_pawns;           // entre pares de peões

void computeAllDistances() {
    dist_queen.resize(K);
    dist_pawns.assign(K, vector<int>(K, -1));

    auto dist_from_queen = bfs(queen);
    for (int i = 0; i < K; ++i) {
        auto [px, py] = pawns[i];
        dist_queen[i] = dist_from_queen[px][py];
    }

    for (int i = 0; i < K; ++i) {
        auto dist_from_pawn = bfs(pawns[i]);
        for (int j = 0; j < K; ++j) {
            auto [qx, qy] = pawns[j];
            dist_pawns[i][j] = dist_from_pawn[qx][qy];
        }
    }
}

// ========== DP COM BITMASK ================
int tsp() {
    int total_masks = 1 << K;
    vector<vector<int>> dp(total_masks, vector<int>(K, -1)); // -1 = estado ainda não visitado

    // Inicializa estados iniciais (rainha -> peões)
    for (int i = 0; i < K; ++i) {
        if (dist_queen[i] != -1) {
            dp[1 << i][i] = dist_queen[i];
        }
    }

    // Transições
    for (int mask = 0; mask < total_masks; ++mask) {
        for (int u = 0; u < K; ++u) {
            if (!(mask & (1 << u)) || dp[mask][u] == -1) continue;

            for (int v = 0; v < K; ++v) {
                if (mask & (1 << v)) continue;
                if (dist_pawns[u][v] == -1) continue;

                int next_mask = mask | (1 << v);
                int new_cost = dp[mask][u] + dist_pawns[u][v];

                if (dp[next_mask][v] == -1 || dp[next_mask][v] > new_cost) {
                    dp[next_mask][v] = new_cost;
                }
            }
        }
    }

    // Encontra o melhor resultado no conjunto final
    int result = -1;
    int full_mask = (1 << K) - 1;
    for (int i = 0; i < K; ++i) {
        if (dp[full_mask][i] != -1) {
            if (result == -1 || dp[full_mask][i] < result) {
                result = dp[full_mask][i];
            }
        }
    }

    return result;
}


// ============== MAIN ========================
int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    readInput();
    computeAllDistances();
    int answer = tsp();
    cout << answer << '\n';
    return 0;
}
