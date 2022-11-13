#include "dispersion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Crea un fichero hash inicialmente vacio segun los criterios especificados en la practica
// Primera tarea a realizar para  crear un fichero organizado mediante DISPERSION
void creaHvacio(char *fichHash) { 
        FILE *fHash;
    tipoCubo cubo;
    int j;
    int numCubos =CUBOS+CUBOSDESBORDE;

    memset(&cubo,0,sizeof(cubo)); //rellenar una zona de mem con un valor 

    fHash = fopen(fichHash,"wb");
    for (j=0;j<numCubos;j++) 
        fwrite(&cubo,sizeof(cubo),1,fHash);
    fclose(fHash);
}
// Lee el contenido del fichero hash organizado mediante el metodo de DISPERSION segun los criterios
// especificados en la practica. Se leen todos los cubos completos tengan registros asignados o no. La
// salida que produce esta funcion permite visualizar el metodo de DISPERSION

int leeHash(char *fichHash) { 
    FILE *f;
    tipoCubo cubo;
    int j, i = 0;
    size_t numLee;

    f = fopen(fichHash,"rb");
    rewind(f);  //si se abre el fichero con r no hace falta
    fread(&cubo,sizeof(cubo),1,f);
    while (!feof(f)) {
            for (j = 0;j < C; j++) {  //cuando leo, leo un cubo entero
                if (j == 0) {
                    printf("Cubo %2d (%2d reg. ASIGNADOS)",i,cubo.numRegAsignados);
                } else { 	
                    printf("\t\t\t");
                }
                if (j < cubo.numRegAsignados) {
                    printf("\t%s %s %s %s %s\n", cubo.reg[j].dni, cubo.reg[j].nombre, cubo.reg[j].ape1, cubo.reg[j].ape2, cubo.reg[j].provincia);
                } else { 
                    printf ("\n");
                }
            }
            i++;
            fread(&cubo,sizeof(cubo),1,f);
    }
    fclose(f);
    return i;
}


int calcularHash(char *clave) {
	int i;
	int suma=0;
	
	for (i = 0; clave[i] != '\0' ; i++) {
		suma = suma + clave[i];
	}
	
	suma = suma % (CUBOS + CUBOSDESBORDE);
	
	return suma;
}


//Insertamos el registro reg en el cubo correspondiente del fichero hash fHash
//Devolvemos el num de cubo donde se inserta
int insertarReg(FILE *fHash, tipoAlumno reg) {
    tipoCubo cubo;
	int numCubo;
	
	//Calculamos el numero de cubo donde deberia de estar el registro
	numCubo = calcularHash(reg.dni);
	
	//Usamos la funcion fseek que permite colocar el indice interno
	//de un fichero en una posicion determinada
	fseek(fHash, sizeof(tipoCubo)*numCubo, SEEK_SET);
	
	//Para insertar un registro, hay que leer el cubo donde queremos poner el reg, copiar el registro
	//en la posicion correspondiente y volver a escribir el cubo en el fichero
	fread(&cubo, sizeof(tipoCubo), 1, fHash);
	
	//Es posible que el cubo este lleno
	//Si no lo esta, podemos copiar el reg en este cubo
	if (cubo.numRegAsignados < C) {
		//Hay hueco. El valor de numRegAsignados indica la posicion libre del array (PE
		//si hay 0 registros asignados, la posicion a usar en el cubo es la 0. Si hay tres reg,
		//estan en las posiciones 0,1 y 2, hay que ponerlo en la 3.
		cubo.reg[cubo.numRegAsignados]=reg;
		cubo.numRegAsignados++;
		
		//Una vez copiado el reg hay que volver a escribirlo en el fichero.
		//OJO. Despues de la lectura, hay que volver a posicionar el indice
		//interno del fichero para poder escribir en la misma posicion que hemos leido
		fseek(fHash, sizeof(tipoCubo)*numCubo, SEEK_SET);
		fwrite(&cubo, sizeof(tipoCubo), 1, fHash);
		
		return numCubo;	
	}
	//Si estamos aqui es porque el cubo estaba lleno. Hay que ir al area de desborde
	fseek(fHash, sizeof(tipoCubo)*CUBOS, SEEK_SET);
	
	for(numCubo = CUBOS; numCubo < CUBOS + CUBOSDESBORDE; numCubo++){
		fread(&cubo, sizeof(cubo), 1, fHash);
		
		//Hay que ver si en este cubo hay sitio
		if (cubo.numRegAsignados<C) {
			//Hay hueco. El valor de numRegAsignados indica la posicion libre del array (PE
			//si hay 0 registros asignados, la posicion a usar en el cubo es la 0. Si hay tres reg,
			//estan en las posiciones 0,1 y 2, hay que ponerlo en la 3. 
			cubo.reg[cubo.numRegAsignados] = reg;
			cubo.numRegAsignados++;
			
			//Una vez copiado el reg hay que volver a escribirlo en el fichero.
			//OJO. Despues de la lectura, hay que volver a posicionar el indice
			//interno del fichero para poder escribir en la misma posicion que hemos leido
			fseek(fHash, sizeof(tipoCubo)*numCubo, SEEK_SET);
			fwrite(&cubo, sizeof(tipoCubo), 1, fHash);
		
			return numCubo;	
		}
	}
	
	//Si llegamos aqui es porque no se ha podido insertar
	return -1;
}

//Lee el fichero de entrada secuencialmente y cada registro lo guarda en el fichero hash
int creaHash(char *fichEntrada,char *fichHash) {
	FILE *fEntrada, *fHash;
	tipoAlumno reg;
	int contDesbordes;
	int retorno;
	
	fEntrada=fopen(fichEntrada, "rb");
	if(fEntrada == NULL){
		return -1;
	}
	
	creaHvacio(fichHash);
	
	//r+ indica lectura y escritura y si no existe el fichero falla
	fHash=fopen(fichHash, "r+b");
	if(fHash == NULL){
		fclose(fEntrada);
		return -1;
	}
	
	contDesbordes = 0;
	
	//Leemos secuencialmente el fichero de entrada
	fread(&reg, sizeof(tipoAlumno), 1, fEntrada);
	while(!feof(fEntrada)){
		//Para cada reg leido del fichero lo insertamos en el hash
		retorno = insertarRegistro(fHash, reg);
		
		if(retorno == -1){
			fclose(fEntrada);
			fclose(fHash);
			return -1;
		}
		
		//Compruebo si es desborde
		if(retorno >= CUBOS){
			contDesbordes++;
		}
		
		fread(&reg, sizeof(tipoAlumno), 1, fEntrada);
	}
	fclose(fEntrada);
	fclose(fHash);
	
	return contDesbordes;
}

tipoAlumno *busquedaHash(FILE *f, char *dni, int *nCubo, int *nCuboDes, int *posReg, int *error) {
	tipoCubo cubo;
	int i;
	tipoAlumno *registro;
	
	//Obtenemos el numero de cubo donde deberia estar el registro
	*nCubo = calcularHash(dni);
	
	//Posiciono el fichero en ese numero de cubo. fseek
	fseek(f, sizeof(tipoCubo)*nCubo, SEEK_SET);
	
	//Leemos el cubo --> fread y guardamos en cubo
	fread(&registro, sizeof(tipoAlumno), 1, f);
	
	//Recorremos los registros de cubo
	for (i = 0; i < C; i++) {
		//Comprobamos si este registro i es el que tiene el dni que buscamos
		if (strcmp(cubo.reg[i].dni, dni) == 0) {
			//Lo he encontrado, *nCuboDes=-1, *error=0, *posReg=i
			*nCuboDes = -1;
			*error = 0;
			*posReg = i;
			//Creamos mem dinamica para el registro
			//Si error --> *error=-4; return NULL;
			registro = (tipoAlumno *)malloc(sizeof(tipoAlumno));
			if(registro == NULL){
				*error = -4;
				return NULL;
			}
			//Asignamos al registro dinamico cubo.reg[i]
			registro = cubo.reg[i];
			
			return registro;
		}
	}
	
	//Si estamos aqui es porque no esta el registro
	//(Opcional; si el num de registros del cubo es menor que C y no lo he encontrado, es que el registro no existe y no hace falta mirar en desborde)
	if (cubo.reg[i] < C) {
		*error = -4;
		return NULL;
	}
	//Posiciono el fichero en los cubos de desborde
	fseek(f, sizeof(tipoCubo)*CUBOS, SEEK_SET);
	//Recorremos los cubos de desborde
	for (*nCuboDes=CUBOS; *nCuboDes< CUBOS+CUBOSDESBORDE; (*nCuboDes)++) {
		//Leer el sig registro
		fread(&registro, sizeof(tipoAlumno), 1, f);
		//Bucle buscando en cubo.reg[i] el dni. Si lo encontramos, hacemos lo mismo que antes
		if (strcmp(cubo.reg[i].dni, dni) == 0) {
			
			*nCuboDes = -1;
			*error = 0;
			*posReg = i;
			
			registro=(tipoAlumno *)malloc(sizeof(tipoAlumno));
			if(registro == NULL){
				*error=-4;
				return NULL;
			}
		
			registro = cubo.reg[i];
			
			return registro;
		}
	}
	//El registro no existe
	*nCuboDes = -1;
	*error = 0;
	
	return NULL;
	
}

int modificarReg(char *fichero, char *dni, char *provincia) {
	tipoAlumno *alumno;
	tipoCubo *cubo;
	FILE *fp;
	int nCubo, nCuboDes, posReg, error;
	int i;
	fp = fopen(fichero, "r+b");
	//errores return -2
	if(fp == NULL){
		return -2;
	}
	
	alumno=busquedaHash(fp, dni, &nCubo, &nCuboDes, &posReg, &error);
	if(alumno == NULL){
		fclose(fp);
		if(error == -1){
			return -1;
		}else if(error == -4){
			return -4;
		}
		return -4;
	}
	
	//Si se ha encontrado el registro
	
	
	//Comprobamos si estamos en un cubo normal
	if(nCubo != -1){
		fseek(fp, sizeof(tipoCubo)*nCubo, SEEK_SET);
	}else{
		fseek(fp, sizeof(tipoCubo)*CUBOS, SEEK_SET);
	}
	
	//Leer el cubo
	fread(&alumno, sizeof(tipoAlumno), 1, fp);
	
	//Accedemos al registro posReg y en su campo provincia le asignamos la provincia nueva
	//strcyp algo asi
	for (i = 0; i < C; i++){
		
		if (strcmp(cubo.reg[i].provincia, provincia) == 0) {
			
			*nCuboDes = -1;
			*error = 0;
			*posReg = i;
			
			alumno = (tipoAlumno *)malloc(sizeof(tipoAlumno));
			if(alumno == NULL){
				*error = -4;
				return NULL;
			}
			
			alumno = cubo.reg[i];
			
			return alumno;
		}
	}
	
	//Modificar la posicion del fichero para retrasarlo un cubo
	fseek(fp, sizeof(tipoCubo)*CUBOS, SEEK_SET);
	//Escribimos el cubo modificado
	
	//Liberar la memoria alumno
	
	//Cerrar el fichero
	fclose(fp);
	//Devolvemos el numero de cubo donde esta el registro
	//ojo que puede ser cubo normal o de desborde
}