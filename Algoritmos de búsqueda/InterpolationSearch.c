#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 25

int interpolationSearch(int arr[], int n, int x) {
    int low = 0, high = n - 1;

    // Iterar mientras el elemento buscado esté en el rango del arreglo
    while (low <= high && x >= arr[low] && x <= arr[high]) {
        // Calcular la posición estimada utilizando interpolación
        int pos = low + ((double)(high - low) / (arr[high] - arr[low])) * (x - arr[low]);

        // Si el elemento está presente en la posición estimada
        if (arr[pos] == x)
            return pos;
        
        // Si el elemento es menor, buscar en la mitad izquierda
        if (arr[pos] < x)
            low = pos + 1;
        // Si el elemento es mayor, buscar en la mitad derecha
        else
            high = pos - 1;
    }
    
    // Si el elemento no está presente en el arreglo
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

    if(interpolationSearch(numeros, TAM, num) == -1) {
        printf("No se ha encontrado el numero >> %d\n", num);
    } else {
        printf("El numero %d está presente en el índice %d\n", num, interpolationSearch(numeros, TAM, num));
    }

    return 0;
}
