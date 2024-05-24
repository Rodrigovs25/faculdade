#include <iostream>

#define MAX_TAM 1000

using namespace std;

int main(){

    int n_teste=0, i=0;
    int dima_1 = 0, dima_2 = 0;
    cin >> n_teste;
    n_teste = 1;

    char linha[MAX_TAM] = "<..><.<..>>";
    char caractere;

    for(int j=0; j < n_teste; j++){
        do
        {
            cin >> caractere;
            if(caractere == '<'){
                dima_1++;
            }
            if(caractere == '>'){
                dima_2++;
            }
        } while (caractere != ' ' || caractere != '\n');
        
        if(dima_1 > dima_2){
            cout << dima_2 << endl;
        }
        else{
            cout << dima_1 << endl;
        }
        dima_1 = 0;
        dima_2 = 0;
    }


    return 0;
}


/*
for(int i=0; linha[i] != '\n'; i++){
            if(linha[i] == '<'){
                dima_1++;
            }
            if(linha[i] == '>'){
                dima_2++;
            }
        }
*/