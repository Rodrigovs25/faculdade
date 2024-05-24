#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class ArvoreBinaria
{
 public:
    ArvoreBinaria();
    ~ArvoreBinaria();
    void Insere(TipoItem item);
    void caminha(int tipo);
    void limpa();
 private:
    void InsereRecursivo(TipoNo* &p, TipoItem item);
    void ApagaRecursivo(TipoNo* p);
    void PorNivel(TipoNo* p);
    void PreOrdem(TipoNo* p);
    void InOrdem(TipoNo* p);
    void PosOrdem(TipoNo* p);

    TipoNo *raiz;
};


int main(){

    while(true){
        char* preordem = new char[27];
        char* inordem = new char[27];
        std::cin >> preordem;
        std::cin >> inordem;
        int t = strlen(preordem);
        for(int i = t; i>0; i--)
        {
            preordem[i] = preordem[i-1];
            inordem[i] = inordem[i-1];
        }
        CelulaArvoreBinaria* raiz;
        raiz = prein_arvore(preordem, inordem, 1, t);
        posordem(raiz);
        std::cout << "\n";
    }    

    
    return 0;
}


//