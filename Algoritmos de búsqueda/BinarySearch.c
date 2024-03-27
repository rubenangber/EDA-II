#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 25

int binarySearch(int arr[], int left, int right, int x) {
    // Verificamos si el lado izquierdo es mayor que el lado derecho
    if (right >= left) {
        // Calculamos el punto medio
        int mid = left + (right - left) / 2;

        // Si el elemento está presente en el medio
        if (arr[mid] == x)
            return mid;

        // Si el elemento es menor que el valor en el medio, buscamos en la mitad izquierda
        if (arr[mid] > x)
            return binarySearch(arr, left, mid - 1, x);

        // Si el elemento es mayor que el valor en el medio, buscamos en la mitad derecha
        return binarySearch(arr, mid + 1, right, x);
    }
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

    if(binarySearch(numeros, 0, TAM - 1, num) == -1) {
        printf("No se ha encontrado el numero >> %d\n", num);
    } else {
        printf("El numero %d está presente en el índice %d\n", num, binarySearch(numeros, 0, TAM - 1, num));
    }

    return 0;
}
