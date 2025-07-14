#include <iostream>
using namespace std;

/*
int main(){
    
    int *a = nullptr;
    int b = 10;

    a = new int;
    *a = 20;
    delete a;
    a = &b;
    *a = 30;

    int *p = new int[10];
    p[0] = 99;
    delete[] p;
    

    int x=5;
    int *ptr=nullptr;
    ptr = &x;
    std::cout << "O endereço de X é: " << ptr << std::endl;
    std::cout << "O valor da variável X é: " << *ptr << std::endl;
    *ptr = 10;
    std::cout << "Agora, X vale: " << *ptr << std::endl;

    return 0;
}*/

/*//ALOCAÇÂO DINAMICA DE MEMORIA
int main()
{
    int *ptr_a;

    ptr_a = new int;
    // cria a área necessária para 01 inteiro e
    // coloca em 'ptr_a' o endereço desta área.

    if (ptr_a == NULL)
    {
        cout << "Memória insuficiente!" << endl;
        exit(1);
    }
    cout << "Endereço de ptr_a: " <<  ptr_a << endl;
    *ptr_a = 90;
    cout << "Conteúdo de ptr_a: " << *ptr_a << endl;
    delete ptr_a;
}
*/

//ALOCACAO DE VETORES
int main(){
    int i;
    int *v=nullptr;
    v = new int[10];  // 'v' é um ponteiro para uma área que
                        // tem 10 inteiros.
                        // 'v' funciona exatamente como um vetor
    v[0] = 10;
    v[1] = 11;
    v[2] = 12;
    // continua...
    v[9] = 19;

    for(i = 0; i < 10; i++)
        cout << "v[" << i << "]: " << v[i] << endl;

    cout << "Endereço de 'v': " << v << endl; // imprime o endereço da área alocada para 'v'
    delete[] v;
}

//g++ ponteiro.cpp -o a