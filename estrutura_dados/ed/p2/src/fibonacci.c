#include <math.h>
#include "fibonacci.h"
#include "msgassert.h"

int fibonacciRecursivo (int n){
    if (n <= 2){
        return 1;
    }
    else{
        //int i=0, numero=0;
        //for ( i = 0; i < 10000000; i++){
        //    numero = sin(i);
        //}
        return fibonacciRecursivo(n-1) + fibonacciRecursivo(n-2);
    }
}

int fibonacciIterativo (int n){
    int a = 0, b = 1, c = 0;

    for (int i = 1; i < n; i++){
        c = a + b;
        a = b;
        b = c;
    }

    //int i=0, numero=0;
    //for ( i = 0; i < 10000000; i++){
    //    numero = sin(i);
    //}
    
    return b;
}