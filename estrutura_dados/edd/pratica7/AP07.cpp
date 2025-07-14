#include <iostream>
#include <string>

using namespace std;

class Celula {
    public:
        Celula(string tel) {
            this->_telefone = tel;
        }
        
        Celula* _prox;
        string _telefone;


};

class Lista {
    public:
        Lista () {
            Celula* nova = new Celula("-1");
            this->_header = nova;
        }

        Celula* _header;

        void insere(string n) {
            
            Celula* nova = new Celula(n);

            Celula* aux = this->_header;

            while (aux->_prox != NULL) {
                if (aux->_prox->_telefone > n) {
                    nova->_prox = aux->_prox;
                    aux->_prox = nova;
                    break;
                }
                aux = aux->_prox;
            }
                aux->_prox = nova;
        }
        
};

int main(){

    int n = 0, eco_total = 0, eco_atual = 0, aux_tam = 0;

    bool troca_ref = true;

    char aux[200];

    while(scanf("%d", &n) != EOF){

        Lista L;
        eco_total = 0;

        for (int i = 0; i < n; i++){
            scanf("%s", aux);
            string str_aux(aux);
            L.insere(str_aux);
        }
        
        string referencia = L._header->_prox->_telefone;

        Celula* aux = L._header->_prox->_prox;

        while (aux != NULL) {

            eco_atual = 0;

            string comparacao = aux->_telefone;

            if (referencia.size() >= comparacao.size()) {
                aux_tam = referencia.size();
            } else {
                aux_tam = comparacao.size();
            }



            for (int j = 0; j < aux_tam; j++) {

                if (referencia[j] == comparacao[j]) {

                    eco_atual++;

                } else {
                    break;
                }
            }

            if (eco_atual == 0){
                referencia = comparacao;
            } else {
                eco_total += eco_atual;
            }

            aux = aux->_prox;
            
        }

        printf("%d\n", eco_total);
            
    }

    return 0;
}