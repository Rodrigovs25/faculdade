#include "tabuleiro.hpp"

Tabuleiro::Tabuleiro(){
    this->n = 0;
    this->m = 0;
    this->k = 0;
    this->tabuleiro = {};
    this->rainha = {0, 0};
    this->peoes = {};
}

// Construtor: inicializa o tabuleiro com seus elementos
Tabuleiro::Tabuleiro(int n, int m, int k,
                const std::vector<std::string>& tabuleiro,
                const Peca& rainha,
                const std::vector<Peca>& peoes)
    : n(n), m(m), k(k), tabuleiro(tabuleiro), rainha(rainha), peoes(peoes) {}

// Busca em largura adaptada para movimentos da rainha
std::vector<std::vector<int>> Tabuleiro::bfs(std::pair<int, int> origem) {
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

// Pré-processa todas as distâncias necessárias (rainha → peões, peões ↔ peões)
void Tabuleiro::calcularTodasDistancias() {
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

// Resolve o problema com Programação Dinâmica + Bitmask
/*int Tabuleiro::resolverCaixeiroViajante() {
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
}*/

int Tabuleiro::resolverGuloso() {
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
