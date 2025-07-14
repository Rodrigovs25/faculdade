#include "soma.h"

float soma(int n, float v[]){
    float soma = 0;
    int i = 0;
    for (i = 0; i < n; i++)
    {
        soma += v[i];
    }
    return soma;
}