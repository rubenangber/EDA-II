#include <stdio.h>
#include "dispersion.h"

typedef struct {
	int numMat;
	char dni[9];
} tipoIndice;

int busquedaBinariaIndice(int numMat, char *dni, FILE *f);
tipoAlumno * busqueda(int numMat, char *ficheroDatos,char *ficheroIndice, int *error);
