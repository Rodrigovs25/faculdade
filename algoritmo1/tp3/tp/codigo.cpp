#include <iostream>
#include <string>
#include <vector>
#include <queue>

// Classe que representa uma peca
class Peca {
    private:
        int x, y;

    public:
        Peca() {
            this->x = 0;
            this->y = 0;
        }
        Peca(int x, int y) : x(x), y(y) {}

        // Retorna a posição da rainha como um par (linha, coluna)
        std::pair<int, int> posicao() const {
            return {x, y};
        }

};

// Classe principal que resolve o problema da captura de peões
class Tabuleiro {
    private:
        int n, m, k;                           // Dimensões do tabuleiro e k=número de peões
        std::vector<std::string> tabuleiro;             // Matriz do tabuleiro (entrada)
        Peca rainha;                        // Objeto que representa a rainha
        std::vector<Peca> peoes;                   // Vetor com todos os peões

        // Matrizes de distâncias calculadas
        std::vector<int> distanciaRainha;              // Distância da rainha para cada peão
        std::vector<std::vector<int>> distanciaPeoes;       // Distância entre todos os pares de peões

        // Busca em largura adaptada para movimentos da rainha
        std::vector<std::vector<int>> bfs(std::pair<int, int> origem){
            std::vector<std::vector<int>> matrizDistancia(n, std::vector<int>(m, -1)); // -1 = ainda não visitado
            std::queue<std::pair<int, int>> fila;
            matrizDistancia[origem.first][origem.second] = 0;
            fila.push(origem);

            // Movimentos da rainha (8 direções)
            std::vector<std::pair<int, int>> direcoes = {
                {-1,  0}, {1,  0}, {0, -1}, {0,  1},
                {-1, -1}, {-1, 1}, {1, -1}, {1,  1}
            };

            // Realiza BFS em cada direção até encontrar obstáculo
            while (!fila.empty()) {
                auto [linhaAtual, colunaAtual] = fila.front(); 
                fila.pop();
                int distanciaAtual = matrizDistancia[linhaAtual][colunaAtual];

                for (auto [deltaLinha, deltaColuna] : direcoes) {
                    int novaLinha = linhaAtual + deltaLinha;
                    int novaColuna = colunaAtual + deltaColuna;
                    while (novaLinha >= 0 && novaLinha < n && novaColuna >= 0 && 
                        novaColuna < m && tabuleiro[novaLinha][novaColuna] != '-') {
                        if (matrizDistancia[novaLinha][novaColuna] == -1) {
                            matrizDistancia[novaLinha][novaColuna] = distanciaAtual + 1;
                            fila.emplace(novaLinha, novaColuna);
                        }
                        novaLinha += deltaLinha;
                        novaColuna += deltaColuna;
                    }
                }
            }

            return matrizDistancia;
        }

        // Processa todas as distâncias necessárias (rainha -> peões, peões <-> peões)
        void calcularTodasDistancias() {
            distanciaRainha.resize(k);
            distanciaPeoes.assign(k, std::vector<int>(k, -1));

            // Distâncias da rainha até todos os peões
            auto distanciaDaRainha = bfs(rainha.posicao());
            for (int i = 0; i < k; ++i) {
                auto [linha, coluna] = peoes[i].posicao();
                distanciaRainha[i] = distanciaDaRainha[linha][coluna];
            }

            // Distâncias entre todos os pares de peões
            for (int i = 0; i < k; ++i) {
                auto distanciaDoPeao = bfs(peoes[i].posicao());
                for (int j = 0; j < k; ++j) {
                    auto [linhaDestino, colunaDestino] = peoes[j].posicao();
                    distanciaPeoes[i][j] = distanciaDoPeao[linhaDestino][colunaDestino];
                }
            }
        }

    public:
        // Construtor: inicializa o tabuleiro com seus elementos
        Tabuleiro(int n, int m, int k,
                const std::vector<std::string>& tabuleiro,
                const Peca& rainha,
                const std::vector<Peca>& peoes)
        : n(n), m(m), k(k), tabuleiro(tabuleiro), rainha(rainha), peoes(peoes) {}

        // Resolve o problema com Programação Dinâmica + Bitmask
        int resolverCaixeiroViajante() {
            calcularTodasDistancias();

            int totalMascaras = 1 << k;
            std::vector<std::vector<int>> custoMinimo(totalMascaras, std::vector<int>(k, -1)); // -1 = estado inválido

            // Estados iniciais: rainha vai diretamente até algum peão
            for (int i = 0; i < k; ++i) {
                if (distanciaRainha[i] != -1) {
                    custoMinimo[1 << i][i] = distanciaRainha[i];
                }
            }

            // Transições de um conjunto de peões visitados, tentar visitar mais um
            for (int mascara = 0; mascara < totalMascaras; ++mascara) {
                for (int peaoAtual = 0; peaoAtual < k; ++peaoAtual) {
                    if (!(mascara & (1 << peaoAtual )) || custoMinimo[mascara][peaoAtual] == -1) continue;

                    for (int proximoPeao = 0; proximoPeao < k; ++proximoPeao) {
                        if (mascara & (1 << proximoPeao)) continue;
                        if (distanciaPeoes[peaoAtual][proximoPeao] == -1) continue;

                        int novaMascara = mascara | (1 << proximoPeao);
                        int novoCusto = custoMinimo[mascara][peaoAtual] + distanciaPeoes[peaoAtual][proximoPeao];

                        if (custoMinimo[novaMascara][proximoPeao] == -1 || custoMinimo[novaMascara][proximoPeao] > novoCusto) {
                            custoMinimo[novaMascara][proximoPeao] = novoCusto;
                        }
                    }
                }
            }

            // Resposta final: menor custo para capturar todos os peões
            int resultado = -1;
            int mascaraFinal = (1 << k) - 1;
            for (int i = 0; i < k; ++i) {
                if (custoMinimo[mascaraFinal][i] != -1) {
                    if (resultado == -1 || custoMinimo[mascaraFinal][i] < resultado) {
                        resultado = custoMinimo[mascaraFinal][i];
                    }
                }
            }

            return resultado;
        }

        int resolverGuloso() {
            std::vector<bool> peaoCapturado(k, false);
            std::pair<int, int> posicaoAtual = rainha.posicao();
            int movimentosTotais = 0;

            for (int capturados = 0; capturados < k; ++capturados) {
                auto dist = bfs(posicaoAtual);
                int menorDistancia = -1;
                int indiceMaisProximo = -1;

                for (int i = 0; i < k; ++i) {
                    if (peaoCapturado[i]) continue;
                    auto [linha, coluna] = peoes[i].posicao();
                    int d = dist[linha][coluna];
                    if (d != -1 && (menorDistancia == -1 || d < menorDistancia)) {
                        menorDistancia = d;
                        indiceMaisProximo = i;
                    }
                }

                if (indiceMaisProximo == -1) {
                    return -1; // não há caminho até algum peão
                }

                peaoCapturado[indiceMaisProximo] = true;
                movimentosTotais += menorDistancia;
                posicaoAtual = peoes[indiceMaisProximo].posicao();
            }

            return movimentosTotais;
        }

};

// Função principal
int main() {

    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<std::string> tabuleiro(n);
    Peca rainha;
    std::vector<Peca> peoes;

    // Leitura do tabuleiro e localização da rainha e dos peões
    for (int i = 0; i < n; ++i) {
        std::cin >> tabuleiro[i];
        for (int j = 0; j < m; ++j) {
            if (tabuleiro[i][j] == 'R') {
                rainha = Peca(i, j);
            } else if (tabuleiro[i][j] == 'P') {
                peoes.emplace_back(i, j);
            }
        }
    }

    // Criação do objeto e resolução do problema
    Tabuleiro jogo(n, m, k, tabuleiro, rainha, peoes);
    int respostaExato = jogo.resolverCaixeiroViajante();
    std::cout << respostaExato << std::endl;

    int respostaAproximada = jogo.resolverGuloso();
    std::cout << respostaAproximada << std::endl;

    return 0;
}
