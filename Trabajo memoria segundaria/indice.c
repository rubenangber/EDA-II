#include "indice.h"

typedef struct {
	int numMat;
	char dni[9];
} tipoIndice;



int busquedaBinariaIndice(int numMat, char *dni, FILE *f){
	//Calculamos el num de registros del fichero.
	//opciones: leerlo entero contando o usar ftell
	int base, tope, medio;
	tipoIndice indice;
	
	base=0;
	tope = -1;//num de reg del fichero -1
	
	while (base < tope) {
		medio = (base + tope) / 2;
		
		//Posicionamos el fichero en la posicion que marca el punto medio
		
		//Leemos el registro -->indice
		
		if (indice.numMat==numMat) {
			strcpy(dni, indice.numMat);
			return 0;
		} else if (numMat < indice.numMat) {
			//Me quedo con la parte de la izquierda
			tope = medio - 1;
		} else {
			base = medio;
		}
	}
	
	//Si estamos aqui es porque no lo hemos encontrado
	return -1;
	
}

tipoAlumno *busqueda(int numMat, char *ficheroDatos, char *ficheroIndice, int *error){
	tipoAlumno *alumno;
	FILE *fIndice, *fHash;
	int nCubo, nCuboDes, posReg;
	int retorno;
	char dni[9];
	
	fIndice = fopen(ficheroIndice, "rb");
	if(fIndice == NULL){
		*error = -3;
		return NULL;
	}
	
	fHash=fopen(ficheroDatos, "rb");
	if(fHash == NULL){
		*error = -2;
		fclose(fIndice);
		return NULL;
	}
	
	retorno=busquedaBinariaIndice(numMat, dni, fIndice);
	if(retorno != 0){
		*error = -4;
		fclose(fIndice);
		fclose(fHash);
		return NULL;
	}
	
	alumno=busquedaHash(fHash, dni, &nCubo, &nCuboDes, &posReg, error);
	if(alumno == NULL){
		//Error
	}
	
	*error = 0;
	fclose(fIndice);
	fclose(fHash);
	
	return alumno;
}
