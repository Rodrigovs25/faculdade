#include <iostream>

using namespace std;

void MaxMin1(int A[], int n, int *Max, int *Min){ // pior algoritmo 
    int i = 0;

    *Max = A[0];
    *Min = A[0];
    for (int i = 0; i < n; i++){
        if(A[i] > *Max) {
            *Max = A[i];
        }
        if(A[i] < *Max) {
            *Min = A[i];
        }
    }
}

void MaxMin2(int A[], int n, int *Max, int *Min){ // algoritmo bom para casos medios e ruins para os piores casos
    int i = 0;

    *Max = A[0];
    *Min = A[0];
    for (int i = 0; i < n; i++){
        if(A[i] > *Max) {
            *Max = A[i];
        }
        else if(A[i] < *Max) {
            *Min = A[i];
        }
    }
}

void MaxMin3(int n, int *A, int *Max, int *Min){ // melhor algoritmo para todos os casos    
    int i, FimDoAnel;

    if((n % 2) > 0){
        A[n] = A[n-1];
        FimDoAnel = n;
    }
    else {
        FimDoAnel = n-1;
    }

    if(A[0] > A[1]){
        *Max = A[0];
        *Min = A[1];
    }
    else {
        *Max = A[1];
        *Min = A[0];
    }

    i = 3;
    while(i <= FimDoAnel){
        if(A[i-1] > A[i]){
            if (A[i-1] > *Max) 
                *Max = A[i-1];
            if (A[i] < *Min) 
                *Min = A[i];
        }
        else {
            if (A[i-1] < *Min) 
                *Min = A[i-1];
            if (A[i] > *Max) 
                *Max = A[i];
        }
    }
}

void aumentar(int *m){
    (*m)++;
}

int main(){

    int n = 4, i = 0;
    //cin >> n;
    int A[4] = {10, 2, 20, 1};

    int Max=0, Min=0;//inicializar o ponteiro com a referencia se nao dar segmetation fault
    //Max = &i;
    //Min = &n;
    //MaxMin1(A, n, &Max, &Min); // se max e min fosse ponteiros 
    //while(i < n){
    //    cin >> vetor[i]; 
    //   i++;
    //}

    MaxMin1(A, n, &Max, &Min);

    cout << "Maior: " << Max << ". Menor: " << Min << endl;

    return 0;
}

//g++ maior.cpp
//./a.out < maior.txt