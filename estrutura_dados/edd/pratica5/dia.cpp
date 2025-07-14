#include <iostream>
#include <string.h>

#define MAX_TAM 1000

class TipoCelula
{
public:
    TipoCelula() {prox = NULL; item = 'a';};

    char item;
    TipoCelula *prox;
};

class Pilha
{
public:
    Pilha(){tamanho = 0; contador = 0; topo = NULL;};
    bool vazia() {return tamanho == 0;};
    void Empilha (char c);
    void Desempilha();

    int tamanho;
    TipoCelula *topo;
    int contador;
};

void Pilha::Empilha(char c){
    TipoCelula *novo = new TipoCelula();
    novo->item = c;
    novo->prox = topo;
    topo = novo;
    tamanho++;
}

void Pilha::Desempilha(){
    TipoCelula *p;

    if(this->vazia()){
        return;
    }
    this->contador++;

    p = this->topo;
    this->topo = this->topo->prox;
    delete p;
    this->tamanho--;
}

using namespace std;

int main(){

    int n_teste = 0, j=0;
    //cin >> n_teste;
    n_teste = 1;


    string linha;

    Pilha *antonio;

    linha = "<..><.<..>>";

    for(int i=0; i < n_teste; i++){
        //getline(cin, linha);
        for(int j=0; j<linha.size(); j++){
            if(linha[j] == '<'){
                antonio->Empilha(linha[j]);
            }

            if(linha[j] == '>'){
                antonio->Desempilha();
            }
        }
        cout << antonio->contador << endl;
    }

    return 0;
}
