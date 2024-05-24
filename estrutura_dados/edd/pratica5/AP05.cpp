#include <iostream>
#include <string.h>

using namespace std;

class TipoCelula {
    public:
        TipoCelula() {_prox = NULL; _item = '0';};
        TipoCelula* _prox;
        char _item;
};

class Pilha {
    public:
        Pilha() {_tam = 0; _cont = 0; _topo = NULL;};
        int _tam;
        int _cont;
        TipoCelula* _topo;
        void Empilha(char c);
        void Desempilha();
        void Imprime();
        void Limpa();
};

void Pilha::Empilha(char c) {

    TipoCelula* nova_c = new TipoCelula();
    nova_c->_item = c; 

    nova_c->_prox = this->_topo;
    this->_topo = nova_c;

    this->_tam++;
}

void Pilha::Desempilha() {

    TipoCelula* aux = this->_topo;
        
    this->_topo = aux->_prox;

    this->_tam--;

    delete aux;
}

void Pilha::Imprime() {
    TipoCelula* aux = this->_topo;
    while (aux != NULL) {
        cout << aux->_item << " ";
        aux = aux->_prox;
    }
    cout << endl;
}

void Pilha::Limpa() {
    TipoCelula* aux = this->_topo;
    while (this->_tam > 0) {
        this->Desempilha();
    }
}

int main() {
    string n;

    string line;

    getline(cin, n);

    Pilha* Principal = new Pilha();
    Pilha* Diamante = new Pilha();

    for (int i = 0; i < stoi(n); i++) {
        getline(cin, line);
        for (int j = 0; j < line.size(); j++) {
            switch(line[j]){
                case '<':
                    Principal->Empilha(line[j]);
                    break;
                case '>':
                    if(Principal->_tam > 0) {
                        Principal->Desempilha(); 
                        Diamante->Empilha('*');
                    }
                    break;
            }
        }
   
        cout << Diamante->_tam << endl;

        Principal->Limpa();
        Diamante->Limpa();

    }

    delete Principal;
    delete Diamante;

    return 0;
}