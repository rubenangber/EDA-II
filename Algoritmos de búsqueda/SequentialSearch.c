#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 25

int sequentialSearch(int arr[], int n, int x) {
    // Recorremos el arreglo
    for (int i = 0; i < n; i++) {
        // Si encontramos el elemento, devolvemos su índice
        if (arr[i] == x) {
            return i;
        }
    }
    // Si no encontramos el elemento, devolvemos -1
    return -1;
}

int main(int argc, char const *argv[]) {
    int numeros[TAM], temp;

    srand(time(NULL));

    for (int i = 0; i < TAM; i++) {
        numeros[i] = rand() % 10000; // Numeros entre 0 y 9999
    }

    printf("DESORDENADO\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n");

    for (int i = 0; i < TAM - 1; i++) {
        for (int j = 0; j < TAM - i - 1; j++) {
            if (numeros[j] > numeros[j + 1]) {
                temp = numeros[j];
                numeros[j] = numeros[j + 1];
                numeros[j + 1] = temp;
            }
        }
    }
    
    printf("\nORDENADO\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n");

    int num;
    printf("Introduzca el numero a buscar >> ");
    scanf("%d", &num);

    if(sequentialSearch(numeros, TAM, num) == -1) {
        printf("No se ha encontrado el numero >> %d\n", num);
    } else {
        printf("El numero %d está presente en el índice %d\n", num, sequentialSearch(numeros, TAM, num));
    }

    return 0;
}
