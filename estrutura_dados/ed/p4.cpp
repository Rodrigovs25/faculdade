#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;


class FilaCircular {
private:
    int* elementos;
    int capacidade;
    int inicio;
    int fim;
    int quantidade;
public:
    FilaCircular(int capacidade) {
        this->capacidade = capacidade;
        this->elementos = new int[capacidade];
        this->inicio = 0;
        this->fim = 0;
        this->quantidade = 0;
    }

    ~FilaCircular() {
        delete[] elementos;
    }

    void enfileirar(int elemento) {
        if (quantidade == capacidade) {
            throw overflow_error("Fila cheia");
        } else {
            elementos[fim] = elemento;
            fim = (fim + 1) % capacidade;
            quantidade++;
        }
    }

    int desenfileirar() {
        if (quantidade == 0) {
            throw underflow_error("Fila vazia");
        } else {
            int resultado = elementos[inicio];
            inicio = (inicio + 1) % capacidade;
            quantidade--;
            return resultado;
        }
    }

    bool vazia() {
        return quantidade == 0;
    }

    int tamanho() {
        return quantidade;
    }

    int frente() {
        if (quantidade == 0) {
            throw underflow_error("Fila vazia");
        } else {
            return elementos[inicio];
        }
    }
};

class Pilha {
private:
    FilaCircular fila1;
    FilaCircular fila2;
public:
    Pilha(int capacidade) : fila1(capacidade), fila2(capacidade) {}

    void push(int x) {
        fila1.enfileirar(x);
    }

    int pop() {
        int n = fila1.tamanho();
        for (int i = 0; i < n-1; i++) {
            fila2.enfileirar(fila1.desenfileirar());
        }
        int resultado = fila1.desenfileirar();
        for (int i = 0; i < n-1; i++) {
            fila1.enfileirar(fila2.desenfileirar());
        }
        return resultado;
    }

    bool empty() {
        return fila1.vazia();
    }

    int size() {
        return fila1.tamanho();
    }

    int top() {
        int n = fila1.tamanho();
        for (int i = 0; i < n-1; i++) {
            fila2.enfileirar(fila1.desenfileirar());
        }
        int resultado = fila1.frente();
        fila2.enfileirar(fila1.desenfileirar());
        for (int i = 0; i < n-1; i++) {
            fila1.enfileirar(fila2.desenfileirar());
        }
        return resultado;
    }
};

int main(){

  

  srand(time(NULL)); // inicializa o gerador de números aleatórios

    Pilha pilha(10);
    /*
    for (int i = 0; i < 10; i++) {
        int elemento = i;
        cout << "Empilhando " << elemento << endl;
        pilha.push(elemento);
    }
    */
    cout << endl;

    for (int i = 0; i < 10; i++) {
        int escolha = rand() % 2;
        if (escolha == 0 && !pilha.empty()) {
            int elemento = pilha.pop();
            cout << "Desempilhando " << elemento << endl;
        } else {
            int elemento = rand() % 10;
            cout << "Empilhando " << elemento << endl;
            pilha.push(elemento);
        }
    }

  return 0;
}

class Pilha {
private:
    FilaArranjo fila1;
    FilaArranjo fila2;
    int tamanho;
public:
    Pilha(){
      tamanho = 0;
    }

    void push(TipoItem x) {
        fila1.Enfileira(x);
    }

    TipoItem pop() {
        int n = fila1.GetTamanho();
        for (int i = 0; i < n-1; i++) {
            fila2.Enfileira(fila1.Desenfileira());
        }
        TipoItem resultado = fila1.Desenfileira();
        for (int i = 0; i < n-1; i++) {
            fila1.Enfileira(fila2.Desenfileira());
        }
        return resultado;
    }

    bool empty() {
        return fila1.Vazia();
    }

    int size() {
        return fila1.GetTamanho();
    }

    TipoItem top() {
        int n = fila1.GetTamanho();
        for (int i = 0; i < n-1; i++) {
            fila2.Enfileira(fila1.Desenfileira());
        }
        int resultado = fila1.itens[frente];
        fila2.Enfileira(fila1.Desenfileira());
        for (int i = 0; i < n-1; i++) {
            fila1.Enfileira(fila2.Desenfileira());
        }
        return resultado;
    }
};
