#include <iostream>
#include <stack>
#include <sstream>
#include <cmath>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Erro: expressao numerica nao fornecida como argumento" << std::endl;
        return 1;
    }

    std::stringstream ss(argv[1]);

    std::stack<double> pilha;

    std::string token;
    while (ss >> token) {
        if (isdigit(token[0])) {
            double numero = std::stod(token);
            pilha.push(numero);
        } else if (token == "+") {
            double b = pilha.top(); pilha.pop();
            double a = pilha.top(); pilha.pop();
            pilha.push(a + b);
        } else if (token == "-") {
            double b = pilha.top(); pilha.pop();
            double a = pilha.top(); pilha.pop();
            pilha.push(a - b);
        } else if (token == "*") {
            double b = pilha.top(); pilha.pop();
            double a = pilha.top(); pilha.pop();
            pilha.push(a * b);
        } else if (token == "/") {
            double b = pilha.top(); pilha.pop();
            double a = pilha.top(); pilha.pop();
            pilha.push(a / b);
        } else if (token == "^") {
            double b = pilha.top(); pilha.pop();
            double a = pilha.top(); pilha.pop();
            pilha.push(std::pow(a, b));
        } else if (token == "sqrt") {
            double a = pilha.top(); pilha.pop();
            pilha.push(std::sqrt(a));
        } else if (token == "sin") {
            double a = pilha.top(); pilha.pop();
            pilha.push(std::sin(a));
        } else if (token == "cos") {
            double a = pilha.top(); pilha.pop();
            pilha.push(std::cos(a));
        } else {
            std::cout << "Erro: token invalido" << std::endl;
            return 1;
        }
    }

    if (pilha.size() != 1) {
        std::cout << "Erro: expressao invalida" << std::endl;
        return 1;
    }

    std::cout << "Resultado: " << pilha.top() << std::endl;

    return 0;
}