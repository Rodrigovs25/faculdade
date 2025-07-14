#include <iostream>
#include <string>

using namespace std;

class Celula {
    public:
        Celula(string n) {
            this->_num = n;
        }
        
        Celula* _prox;
        string _num;


};

class Lista {
    public:
        Lista () {
            this->_primeira = NULL;
        }

        Celula* _primeira;

        void Imprime(){
            Celula* aux = this->_primeira;
            while (aux != NULL) {
                cout << "IMPRIMINDO" << endl;
                cout << aux->_num << endl;
                aux = aux->_prox;
            }
        }

        void insere(string n) {
            
            Celula* nova = new Celula(n);
            
            if (this->_primeira == NULL) {
                cout << "Trocando Primeira" << endl;
                this->_primeira = nova;

            }
            
            else {
                cout << "Colocando coisa nova" << endl;
                Celula* aux = this->_primeira;
                while (aux->_prox != NULL) {
                    if (aux->_prox->_num > n) {
                        nova->_prox = aux->_prox;
                        aux->_prox = nova;
                        break;
                    }
                    aux = aux->_prox;

                }
                aux->_prox = nova;
            }

        }
};

int main(){

    int n=0, qts_tot = 0, qts_agr = 0;

    string str1, str2;

    while(cin >> n){
        Lista L;
        qts_tot = 0;
        cin >> str1;

        L.insere(str1);

        L.Imprime();

        for (int i = 1; i < n; i++){
            cin >> str2;
            L.insere(str2);
        }




        string string_ref = L._primeira->_num;
        Celula* aux = L._primeira->_prox;
        string string_comp;

        while (aux->_prox != NULL) {
            qts_agr = 0;
            string_comp = aux->_num;
            for (int j = 0; j < string_ref.length(); j++) {
                if(str1[j] == str2[j]){
                    qts_agr++;
                }
                else{
                    break;
                }
            }
            if (qts_agr == 0) {
                str1 = str2;
            } else {
                qts_tot += qts_agr;
                //cout << "aux: " << aux << endl;
            }
        }

        cout << qts_tot << endl;
    }

    return 0;
}