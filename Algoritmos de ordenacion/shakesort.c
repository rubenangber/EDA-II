#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 25

int main(int argc, char const *argv[]) {
    int numeros[TAM];

    srand(time(NULL));

    for (int i = 0; i < TAM; i++) {
        numeros[i] = rand() % 10000; // Numeros entre 0 y 9999
    }

    printf("DESORDENADO\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n");

    int left = 0, right = TAM - 1, swapped = 1;
    while (swapped) {
        swapped = 0;
        // Mover los elementos más grandes hacia el final
        for (int i = left; i < right; i++) {
            if (numeros[i] > numeros[i + 1]) {
                int temp = numeros[i];
                numeros[i] = numeros[i + 1];
                numeros[i + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;
        swapped = 0;
        right--;
        // Mover los elementos más pequeños hacia el principio
        for (int i = right - 1; i >= left; i--) {
            if (numeros[i] > numeros[i + 1]) {
                int temp = numeros[i];
                numeros[i] = numeros[i + 1];
                numeros[i + 1] = temp;
                swapped = 1;
            }
        }
        left++;
    }

    printf("\nORDENADO\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n");

    return 0;
}
