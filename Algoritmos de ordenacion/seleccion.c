#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 25

int main(int argc, char const *argv[]) {
    int numeros[TAM], k, t;

    srand(time(NULL));

    for (int i = 0; i < TAM; i++) {
        numeros[i] = rand() % 10000; // Numeros entre 0 y 9999
    }

    printf("DESORDENADO\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n");

    int min_idx;
    for (int i = 0; i < TAM - 1; i++) {
        min_idx = i;
        for (int j = i+1; j < TAM; j++) {
            if (numeros[j] < numeros[min_idx]) {
                min_idx = j;
            }
        }
        int temp = numeros[min_idx];
        numeros[min_idx] = numeros[i];
        numeros[i] = temp;
    }
    
    printf("\nORDENADO\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n");

    return 0;
}