#include "media.h"
#include "soma.h"

float media(int n, float v[]){
    float s = soma(n, v);
    return s / n;
}