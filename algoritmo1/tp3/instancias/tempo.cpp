#include <chrono> // inclusão necessária para medir o tempo

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

    TabuleiroRainha jogo(N, M, K, tabuleiro, rainha, peoes);

    // Início da medição de tempo
    auto inicio = chrono::high_resolution_clock::now();

    int resposta = jogo.resolverTSP();

    auto fim = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracao = fim - inicio;

    // Saída da resposta
    cout << resposta << '\n';

    // Saída da duração
    cerr << "Tempo de execução: " << duracao.count() << " ms\n";

    return 0;
}
