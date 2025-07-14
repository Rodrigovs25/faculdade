#include <iostream>

using namespace std;

int fibonacciIterativo (int n){
    int a = 0, b = 1, c = 0;

    for (int i = 1; i < n; i++){
        c = a + b;
        a = b;
        b = c;
    }
    
    return b;
}

int fibonacciRecursivo (int n){
    if (n <= 2){
        return 1;
    }

    return fibonacciRecursivo(n-1) + fibonacciRecursivo(n-2);
}

int fatorialRecursivo (int n){
    if(n < 1){
        return 1;
    }
    return n * fatorialRecursivo(n-1);
}

int fatorialIterativo (int n){
    int fat = 1;
    
    for (int i = 1; i <= n; i++){
        fat *= i;
    }
    
    return fat;
}

int main(){
    
    cout << fatorialRecursivo(5) << endl;
}

//g++ main.cpp -g -o main