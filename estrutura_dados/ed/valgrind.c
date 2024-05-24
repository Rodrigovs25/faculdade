#include <stdio.h>
#include <stdlib.h>
/*
int main(int argc, char const *argv[]) {
    int i, *vetor = malloc(10 * sizeof(int));

    for (i = 0; i < 10; i++)
        scanf("%d", &vetor[i]);

    for (i = 9; i >= 0; i--)
        printf("%d\n", vetor[i]);

    return 0;
}
*/

int main(int argc, char** argv){
  int i;
  int *a = malloc(sizeof(int) * 10);
  if (!a) return -1; /*malloc failed*/
  for (i = 0; i < 11; i++){
    a[i] = i;
  }
  free(a);
  return 0;
}
//gcc valgrind.c -o val
//valgrind --leak-check=full ./val