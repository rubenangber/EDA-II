#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 25

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void cocktailSort(int arr[], int n) {
    int swapped = 1;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = 0;
        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                swapped = 1;
            }
        }

        if (swapped) {
            end--;
        }

        swapped = 0;
        for (int i = end; i > start; i--) {
            if (arr[i] < arr[i - 1]) {
                swap(&arr[i], &arr[i - 1]);
                swapped = 1;
            }
        }

        start++;
    }
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

    cocktailSort(numeros, TAM);
    
    printf("\nORDENADO\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n");

    return 0;
}
