#ifndef PECA_HPP
#define PECA_HPP

#include <string>

// Classe que representa uma peca
class Peca {
    private:
        int x, y;

    public:
        Peca();
        Peca(int x, int y);

        // Retorna a posição da rainha como um par (linha, coluna)
        std::pair<int, int> posicao() const;

};

#endif