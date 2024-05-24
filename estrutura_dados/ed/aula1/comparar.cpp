#include <iostream>

using namespace std;

int Max(int *A, int n){
    int i, temp;

    temp = A[0];
    for (int i = 0; i < n; i++){
        if(temp < A[i])
            temp = A[i];
    }
    return temp;
}

int main(){
    int vetor[] = {7, 5, 4, 1, 10};
    cout << "Maior: " << Max(vetor, 5) << endl; 
}

//g++ pratica7.cpp
//./a.out < in.txt