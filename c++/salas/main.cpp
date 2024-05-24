#include <iostream>
#include <iomanip>

#include "QuadroAlocacao.hpp"

using namespace std;

int main() {
  
    
    // Definindo o formato da saida
    cout << fixed << showpoint; 
    cout << setprecision(2);

    QuadroAlocacao quadro_alocacao;
    string codigo, nome, dia, horario, sala;

    ListaProcessos lista;

    char data;
    while (cin >> data) {
        switch (data) {
            
            
            case 'a':                 
                cin >> codigo >> nome >> dia >> horario >> salas;
                quadro_alocacao.inserir_alocacao(codigo, nome, dia, horario, sala)
                break;

            
            case 'm': 
                vector<Disciplinas> mais_ofertadas = quadro_alocacao.recuperar_disciplina();
                for(Disciplina &disciplina : mais_ofertadas)
                    disciplina.imprimir_alocacao();
                break;   

            
            case 'r':                  
                cin >> codigo >> horario;
                quadro_alocacao.remover_alocacao_disciplina(codigo, horario);

                break;     

            
            case 'p':                  
                quadro_alocacao.imprimir_alocacao_completa();
                
                break;                                              
        }
    }
    
    return 0;
}
