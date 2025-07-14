#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int INF = INT_MAX;

// Estrutura de aresta para o grafo de fluxo
struct Edge {
    int to, rev;
    int capacity;
};

// Grafo de fluxo com Edmonds-Karp
class FlowGraph {
public:
    FlowGraph(int n) : graph(n), level(n), ptr(n) {}

    void addEdge(int u, int v, int cap) {
        graph[u].push_back({v, (int)graph[v].size(), cap});
        graph[v].push_back({u, (int)graph[u].size() - 1, 0});
    }

    int maxFlow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (int pushed = dfs(s, t, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }

private:
    vector<vector<Edge>> graph;
    vector<int> level, ptr;

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const Edge& e : graph[u]) {
                if (e.capacity > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    int dfs(int u, int t, int pushed) {
        if (pushed == 0) return 0;
        if (u == t) return pushed;
        for (int& i = ptr[u]; i < (int)graph[u].size(); ++i) {
            Edge& e = graph[u][i];
            if (e.capacity > 0 && level[e.to] == level[u] + 1) {
                int tr = dfs(e.to, t, min(pushed, e.capacity));
                if (tr > 0) {
                    e.capacity -= tr;
                    graph[e.to][e.rev].capacity += tr;
                    return tr;
                }
            }
        }
        return 0;
    }
};

// Funções auxiliares para obter índices dos nós
int nodeIn(int i, int j, int m) {
    return (i * m + j) * 2;
}

int nodeOut(int i, int j, int m) {
    return (i * m + j) * 2 + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> grid[i][j];

    int cx, cy;
    cin >> cx >> cy;
    cx--, cy--; // Ajusta para índice 0-based

    int V = 2 * n * m + 2; // Dois nós por célula + fonte + sumidouro
    int source = V - 2;
    int sink = V - 1;

    FlowGraph g(V);

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 0) continue; // Montanha

            int in = nodeIn(i, j, m);
            int out = nodeOut(i, j, m);

            g.addEdge(in, out, grid[i][j]); // custo dos soldados

            // Conecta com vizinhos válidos
            for (int d = 0; d < 4; ++d) {
                int ni = i + dx[d];
                int nj = j + dy[d];
                if (ni >= 0 && ni < n && nj >= 0 && nj < m && grid[ni][nj] != 0) {
                    g.addEdge(out, nodeIn(ni, nj, m), INF);
                }
            }

            // Células na borda são conectadas à fonte
            if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                g.addEdge(source, in, INF);
            }
        }
    }

    // Conecta capital ao sumidouro
    int capitalOut = nodeOut(cx, cy, m);
    g.addEdge(capitalOut, sink, INF);

    // Calcula fluxo máximo (equivalente ao menor número de soldados)
    cout << g.maxFlow(source, sink) << "\n";

    return 0;
}
