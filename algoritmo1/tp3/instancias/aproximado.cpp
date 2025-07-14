#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int N, M, K;
vector<string> board;
pair<int, int> queen;
vector<pair<int, int>> pawns;
vector<bool> captured;

void readInput() {
    cin >> N >> M >> K;
    board.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> board[i];
        for (int j = 0; j < M; ++j) {
            if (board[i][j] == 'R') {
                queen = {i, j};
            } else if (board[i][j] == 'P') {
                pawns.emplace_back(i, j);
            }
        }
    }
    captured.assign(K, false);
}

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

int greedyApproximation() {
    int total_moves = 0;
    pair<int, int> current = queen;

    for (int steps = 0; steps < K; ++steps) {
        auto dist = bfs(current);
        int best = -1;
        int min_dist = -1;

        for (int i = 0; i < K; ++i) {
            if (captured[i]) continue;
            auto [x, y] = pawns[i];
            if (dist[x][y] != -1) {
                if (min_dist == -1 || dist[x][y] < min_dist) {
                    min_dist = dist[x][y];
                    best = i;
                }
            }
        }

        if (best == -1) return -1; // nenhum peão acessível

        captured[best] = true;
        total_moves += min_dist;
        current = pawns[best];
    }

    return total_moves;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    readInput();
    int answer = greedyApproximation();
    cout << answer << '\n';
    return 0;
}
