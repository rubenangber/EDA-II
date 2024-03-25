#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 25

int main(int argc, char const *argv[]) {
    int numeros[TAM], key, i, j;

    srand(time(NULL));

    for (int i = 0; i < TAM; i++) {
        numeros[i] = rand() % 10000; // Numeros entre 0 y 9999
    }

    printf("DESORDENADO\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n");

    for (i = 1; i < TAM; i++) {
        key = numeros[i];
        j = i - 1;
        while (j >= 0 && numeros[j] > key) {
            numeros[j + 1] = numeros[j];
            j = j - 1;
        }
        numeros[j + 1] = key;
    }
    
    printf("\nORDENADO\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n");

    return 0;
}
