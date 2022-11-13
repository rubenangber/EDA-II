#include <stdio.h>
#define C 5	               // Capacidad del cubo
#define CUBOS 20           // Numero de cubos en el area prima
#define CUBOSDESBORDE  4   // Numero de cubos area de desborde

typedef struct {
	char dni[9];
	char nombre[19];
	char ape1[19];
	char ape2[19];
	char provincia[11];
} tipoAlumno;


typedef struct {
	tipoAlumno reg[C];
	int cuboDES;      // De momento no la vamos a utilizar
	int numRegAsignados;
} tipoCubo;

// Funciones proporcionadas
void creaHvacio(char *fichHash);
int leeHash(char *fichHash);
// Funciones a codificar
int creaHash(char *fichEntrada,char *fichHash);
int buscaReg(FILE *fHash, tipoAlumno *reg,char *dni);

int insertarReg(FILE *fHash, tipoAlumno reg);
int calcularHash(char *clave);

tipoAlumno *busquedaHash(FILE *f, char *dni, int *nCubo, int *ncuboDes, int *posReg, int *error);
int modificarReg(char *fichero, char *dni, char *provincia);



