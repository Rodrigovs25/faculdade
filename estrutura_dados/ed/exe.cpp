#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Erro: expressao numerica nao fornecida como argumento" << std::endl;
        return 1;
    }

    std::stringstream ss(argv[1]);
    std::string expressao;
    ss >> expressao;

    std::cout << "Expressao numerica fornecida: " << expressao << std::endl;

    return 0;
}

//g++ exe.cpp
//./a.out < in.txt