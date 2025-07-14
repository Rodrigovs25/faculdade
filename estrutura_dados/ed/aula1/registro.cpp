#include <iostream>
#include <fstream>

using namespace std;

struct TipoRegistro {
  int chave;  
};

int Pesquisa(TipoRegistro *A, int n, int chave){
    int i = 0;

    while (i < n){
        if(A[i].chave == chave)
            break;
        i++;
    }

    return i;
}

int main(){

    TipoRegistro A[5] = {}; // deixar o [] *** stack smashing detected ***: terminated Aborted
    //ofstream arq1; // ofstream - arquivo apenas para saída de dados
    //arq1.open ("regchave.txt"); // função open - abre o arquivo. Cria o arquivo caso ele não exista.
    ofstream arq1("regchave.txt");

    //ifstream – abre o arquivo apenas para leitura
    //ifstream arq_in ("nomes.txt");

    int i = 0;
    while (i < 5){
        cin >> A[i].chave;
        if (arq1.is_open()){
            arq1 << A[i].chave * 10 << endl; // Insere nomes no arquivo (operador "<<")
        }
        i++;
    }

    cout << "Chave: " << Pesquisa(A, 5, 3) << endl;

    arq1.close(); // função close - fecha o arquivo
    
    return 0;
}