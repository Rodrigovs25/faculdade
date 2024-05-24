#include <math.h>
#include "fatorial.h"
#include "msgassert.h"

int fatorialRecursivo (int n){
    if(n < 1){
        return 1;
    }
    //int i=0, numero=0;
    //for ( i = 0; i < 10000000; i++){
    //   numero = sin(i);
    //}
    return n * fatorialRecursivo(n-1);
}

int fatorialIterativo (int n){
    int fat = 1;
    
    for (int i = 1; i <= n; i++){
        fat *= i;
    }

    //int i=0, numero=0;
    //for ( i = 0; i < 10000000; i++){
    //    numero = sin(i);
    //}
    
    return fat;
}