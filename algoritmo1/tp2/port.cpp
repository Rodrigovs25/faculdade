#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INFINITO = 1e9;

struct Aresta {
    int destino, reversa;
    int capacidade;
};

class FluxoMaximo {
public:
    FluxoMaximo(int n) : grafo(n), nivel(n), iterador(n) {}

    void adicionar_aresta(int de, int para, int capacidade) {
        grafo[de].push_back({para, (int)grafo[para].size(), capacidade});
        grafo[para].push_back({de, (int)grafo[de].size() - 1, 0}); // aresta reversa
    }

    int edmonds_karp(int origem, int destino) {
        int fluxo = 0;
        while (true) {
            fill(nivel.begin(), nivel.end(), -1);
            nivel[origem] = 0;
            queue<int> fila;
            fila.push(origem);
            while (!fila.empty()) {
                int v = fila.front(); fila.pop();
                for (const Aresta &e : grafo[v]) {
                    if (e.capacidade > 0 && nivel[e.destino] < 0) {
                        nivel[e.destino] = nivel[v] + 1;
                        fila.push(e.destino);
                    }
                }
            }
            if (nivel[destino] < 0) break;
            fill(iterador.begin(), iterador.end(), 0);
            int f;
            while ((f = dfs(origem, destino, INFINITO)) > 0) {
                fluxo += f;
            }
        }
        return fluxo;
    }

private:
    vector<vector<Aresta>> grafo;
    vector<int> nivel;
    vector<int> iterador;

    int dfs(int v, int destino, int limite) {
        if (v == destino) return limite;
        for (int &i = iterador[v]; i < (int)grafo[v].size(); ++i) {
            Aresta &e = grafo[v][i];
            if (e.capacidade > 0 && nivel[v] < nivel[e.destino]) {
                int d = dfs(e.destino, destino, min(limite, e.capacidade));
                if (d > 0) {
                    e.capacidade -= d;
                    grafo[e.destino][e.reversa].capacidade += d;
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

    vector<vector<int>> mapa(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> mapa[i][j];

    int x_capital, y_capital;
    cin >> x_capital >> y_capital;
    --x_capital; --y_capital; // coordenadas ajustadas para índice começando em 0

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    auto no_entrada = [&](int i, int j) { return (i * m + j) * 2; };
    auto no_saida = [&](int i, int j) { return (i * m + j) * 2 + 1; };

    int total_nos = n * m * 2 + 2;
    int origem = total_nos - 2;
    int destino = total_nos - 1;

    FluxoMaximo fluxo(total_nos);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mapa[i][j] == 0) continue; // montanha

            int entrada = no_entrada(i, j);
            int saida = no_saida(i, j);

            // conexão interna (entrada -> saída) com capacidade do mapa
            fluxo.adicionar_aresta(entrada, saida, mapa[i][j]);

            // vizinhos (ligar saída aos vizinhos válidos)
            for (int d = 0; d < 4; ++d) {
                int ni = i + dx[d];
                int nj = j + dy[d];
                if (ni < 0 || nj < 0 || ni >= n || nj >= m) continue;
                if (mapa[ni][nj] == 0) continue; // vizinho é montanha
                fluxo.adicionar_aresta(saida, no_entrada(ni, nj), INFINITO);
            }

            // se estiver na borda, conecta à origem
            if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {
                fluxo.adicionar_aresta(origem, entrada, INFINITO);
            }
        }
    }

    fluxo.adicionar_aresta(no_saida(x_capital, y_capital), destino, INFINITO);

    int resultado = fluxo.edmonds_karp(origem, destino);
    cout << resultado << endl;

    return 0;
}
