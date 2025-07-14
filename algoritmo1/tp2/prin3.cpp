#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

struct Edge {
    int to, rev;
    int cap;
};

class MaxFlow {
public:
    MaxFlow(int n) : graph(n), level(n), iter(n) {}

    void add_edge(int from, int to, int cap) {
        graph[from].push_back({to, (int)graph[to].size(), cap});
        graph[to].push_back({from, (int)graph[from].size() - 1, 0}); // reverse edge
    }

    int edmonds_karp(int s, int t) {
        int flow = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            queue<int> que;
            que.push(s);
            while (!que.empty()) {
                int v = que.front(); que.pop();
                for (const Edge &e : graph[v]) {
                    if (e.cap > 0 && level[e.to] < 0) {
                        level[e.to] = level[v] + 1;
                        que.push(e.to);
                    }
                }
            }
            if (level[t] < 0) break;
            fill(iter.begin(), iter.end(), 0);
            int f;
            while ((f = dfs(s, t, INF)) > 0) {
                flow += f;
            }
        }
        return flow;
    }

private:
    vector<vector<Edge>> graph;
    vector<int> level;
    vector<int> iter;

    int dfs(int v, int t, int upTo) {
        if (v == t) return upTo;
        for (int &i = iter[v]; i < (int)graph[v].size(); ++i) {
            Edge &e = graph[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                int d = dfs(e.to, t, min(upTo, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    graph[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> mat(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> mat[i][j];

    int x_cap, y_cap;
    cin >> x_cap >> y_cap;
    --x_cap; --y_cap; // coordenadas 0-indexadas

    // Cada célula vira dois nós: in e out
    // Total de nós = 2 * n * m + 2 (fonte + destino)
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    auto node_in = [&](int i, int j) { return (i * m + j) * 2; };
    auto node_out = [&](int i, int j) { return (i * m + j) * 2 + 1; };

    int total_nodes = n * m * 2 + 2;
    int source = total_nodes - 2;
    int sink = total_nodes - 1;

    MaxFlow mf(total_nodes);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mat[i][j] == 0) continue; // montanha

            int u_in = node_in(i, j);
            int u_out = node_out(i, j);

            // conexão interna (entrada -> saída) com capacidade mat[i][j]
            mf.add_edge(u_in, u_out, mat[i][j]);

            // vizinhos (liga saída deste para entrada dos vizinhos)
            for (int d = 0; d < 4; ++d) {
                int ni = i + dx[d];
                int nj = j + dy[d];
                if (ni < 0 || nj < 0 || ni >= n || nj >= m) continue;
                if (mat[ni][nj] == 0) continue; // vizinho é montanha
                mf.add_edge(u_out, node_in(ni, nj), INF);
            }

            // borda -> conecta fonte
            if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {
                mf.add_edge(source, u_in, INF);
            }
        }
    }

    mf.add_edge(node_out(x_cap, y_cap), sink, INF);

    int result = mf.edmonds_karp(source, sink);
    cout << result << endl;

    return 0;
}
