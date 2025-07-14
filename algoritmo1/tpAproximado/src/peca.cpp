#include "peca.hpp"

Peca::Peca() {
    this->x = 0;
    this->y = 0;
}

Peca::Peca(int x, int y) : x(x), y(y) {}

std::pair<int, int> Peca::posicao() const {
    return {x, y};
}