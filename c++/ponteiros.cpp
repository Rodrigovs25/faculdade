#include <iostream>

using namespace std;

int main(){//g++ ponteiros.cpp -o a
    // 1) Declare uma variável do tipo inteiro e atribua o valor '10'
    int num1=10;
    
    // 2) Declare um ponteiro para inteiros e inicialize com valor nulo
    int *num2=nullptr;

    // 3) Declare um vetor de inteiros e inicialize com valores de 9 a 0 (nessa ordem)
    int vetor[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    /*
    vetor = new int[10];
    for (int i = 0; i < 10; i++){
        vetor[i] = i;
    }
    for (int i = 0; i < 10; i++){
        cout << "vetor: " << vetor[i] << endl;
    }
    */

    // 4) Imprima o ENDEREÇO da variável declarada em (1)
    cout << &num1 << endl;
    /*
    int *pon;
    pon = &num1;
    cout << pon << endl;
    */

    // 5) Imprima o VALOR da variável declarada em (1)
    cout << num1 << endl;
    
    // 6) Imprima o ENDEREÇO da variável declarada em (2)
    cout << &num2 << endl;
    
    // 7) Imprima o VALOR da variável declarada em (2)
    cout << num2 << endl;

    // 8) Imprima o ENDEREÇO da variável declarada em (3)
    cout << &vetor << endl;

    // 9) Imprima o ENDEREÇO da primeira posição da variável declarada em (3)
    cout << &vetor[0] << endl;

    // 10) Imprima o VALOR da primeira posição da variável declarada em (3)
    cout << vetor[0] << endl;
    
    // 11) Atribua o ENDEREÇO da variável declarada em (1) à variável declarada em (2)
    num2 = &num1;

    // 12) Imprima o VALOR da variável declarada em (2)
    cout << num2 << endl;

    // 13) Imprima o VALOR guardado no ENDEREÇO apontado por (2)
    std::cout << *num2 << std::endl;

    // 14) Imprima o resultado da comparação do ENDEREÇO de (1) e do VALOR de (2)
    if (&num1 == num2){
        std::cout << 1 << std::endl;
    }
    else{
        std::cout << 0 << std::endl;
    }

    // 15) Coloque o VALOR '5' no ENDEREÇO apontado por (2)
    *num2 = 5;

    // 16) Imprima o VALOR da variável declarada em (1)
    std::cout << num1 << std::endl;

    // 17) Atribua o ENDEREÇO da variável (3) à variável declarada em (2)
    num2 = vetor;

    // 18) Imprima o VALOR da variável declarada em (2)
    std::cout << num2 << std::endl;

    // 19) Imprima o VALOR guardado no ENDEREÇO apontado por (2)
    std::cout << *num2 << std::endl;

    // 20) Atribua o ENDEREÇO da primeira posição de (3) à variável declarada em (2)
    num2 = &vetor[0];

    // 21) Imprima o VALOR da variável declarada em (2)
    std::cout << num2 << std::endl;

    // 22) Imprima o VALOR guardado no ENDEREÇO apontado por (2)
    std::cout << *num2 << std::endl;

    // 23) Multiplique todos os valores do vetor declarado em (3) por '10', porém manipulando apenas a variável (2)
    for (int i = 0; i < 10; i++)
    {
        *(num2 + i) *= 10;
    }
    
    // 24) Imprima os elementos de (3) a partir variável do vetor utilizando a notação [] (colchetes)
    for (int i = 0; i < 10; i++)
    {
        std::cout << vetor[i] << " ";
    }
    std::cout << std::endl;

    // 25) Imprima os elementos de (3) a partir variável do vetor utilizando a notação ponteiro/deslocamento
    for (int i = 0; i < 10; i++)
    {
        std::cout << *(vetor + i) << " ";
    }
    std::cout << std::endl;

    // 26) Imprima os elementos de (3) utilizando a variável (2) e a notação ponteiro/deslocamento
    for (int i = 0; i < 10; i++)
    {
        std::cout << *(num2 + i) << " ";
    }
    std::cout << std::endl;

    // 27) Atribua o ENDEREÇO da quinta posição de (3) à variável declarada em (2)
    num2 = &vetor[4];

    // 28) Imprima o VALOR da variável declarada em (2)
    std::cout << num2 << std::endl;

    // 29) Imprima o VALOR guardado no ENDEREÇO apontado por (2)
    std::cout << *num2 << std::endl;

    // 30) Imprima o VALOR guardado no ENDEREÇO do ponteiro (2) decrementado de 4
    std::cout << *(num2-4) << std::endl;

    // 31) Declare um ponteiro para ponteiro e o inicialize com o ENDEREÇO da variável (2)
    int **ponteiro = &num2;

    // 32) Imprima o VALOR da variável declarada em (31)
    std::cout << ponteiro << std::endl;

    // 33) Imprima o ENDEREÇO da variável declarada em (31)
    std::cout << &ponteiro << std::endl;

    // 34) Imprima o VALOR guardado no ENDEREÇO apontado por (31)
    std::cout << *ponteiro << std::endl;

    // 35) Imprima o VALOR guardado no ENDEREÇO do ponteiro apontado por (31)
    std::cout << **ponteiro << std::endl;
    
    return 0;

}