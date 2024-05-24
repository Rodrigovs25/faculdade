#include <iostream>
#include <iomanip>

#include "ListaProcessos.hpp"

using namespace std;

int main() {
  
    
    // Definindo o formato da saida
    cout << fixed << showpoint; 
    cout << setprecision(2);

    int id, prioridade;
    string nome;

    ListaProcessos lista;

    char data;
    while (cin >> data) {
        switch (data) {
            
            
            case 'a':                 
                cin >> id >> nome >> prioridade;

                lista.adicionar_processo(new Processo(id, nome, prioridade));
                break;

            
            case 'm': 
                lista.remover_processo_maior_prioridade();
                break;

            
            case 'n':                  
               lista.remover_processo_menor_prioridade();
                break;   

            
            case 'r':                  
                cin >> id;
                lista.remover_processo_por_id(id);

                break;     

            
            case 'p':                  
                lista.imprimir_lista();
                
                break;                                              
        }
    }
    
    return 0;
}
