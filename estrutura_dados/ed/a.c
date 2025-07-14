#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <math.h>


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

int fibonacciRecursivo (int n){
    if (n <= 2){
        return 1;
    }
    else{
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
    
    return b;
}



int main(int argc, char ** argv){

    struct timespec t1, t2, res;
    //int result = clock_gettime(CLOCK_MONOTONIC,&tp);
    // tp.tv_sec;
    // tp.tv_nsec;

    int n = atoi(argv[1]), out;
    printf("%d %s %s\n", argc, argv[0], argv[1]);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    out = fatorialIterativo(n);
    clock_gettime(CLOCK_MONOTONIC, &t2);
    printf("FATITE: %d\n", out);
    if (t2.tv_nsec < t1.tv_nsec){
        res.tv_nsec = 1000000000 + t2.tv_nsec - t1.tv_nsec;
        res.tv_sec = t2.tv_sec - t1.tv_sec - 1;
    }
    else{
        res.tv_nsec = t2.tv_nsec - t1.tv_nsec;
        res.tv_sec = t2.tv_sec - t1.tv_sec;
    }
    printf("%ld.%.9ld", res.tv_sec, res.tv_nsec);
    
    return 0;
}

//time .a.out 20
// .9 no segundo no printf
//g++ -pg ...
//time
//gprof ./a.out gmou.out | more; gprof ./bin/main gmon.out > analise.txt
//man gprof -> opcoes gprof
//man getrusage
//

//gcc -pg test.c
// ./a.out -t -x 20
// gprof ./a.out gmon.out > analise.txt

//gcc -pg a.c
//time ./a.out 20