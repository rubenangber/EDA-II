#include "dispersion.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

int main(){

    int i,numRegDes;
    FILE *f;
    tipoAlumno reg;
    char dni[10];

    numRegDes = creaHash("alumnos.dat","alumnos.hash");
    printf("%d Registros DESBORDADOS\n\n",numRegDes);

    i = leeHash("alumnos.hash");

    // Busqueda de registros
    f = fopen("alumnos.hash","rb");

    strcpy(dni,"7389298"); // Existe en el area PRIMA
    i = buscaReg(f,&reg,dni);
    
    if (i < 0) {
        printf("No existe alumno con dni %s\n",dni);
    } else { 
        printf("Registro encontrado en el CUBO %d",i);
        printf("\t %s %s %s %s %s\n",reg.dni,reg.nombre,reg.ape1,reg.ape2,reg.provincia);
    }

    strcpy(dni,"7219752"); // Existe en el area De DESBORDE
    i = buscaReg(f,&reg,dni);

    if (i < 0) {
        printf("No existe alumno con dni %s\n",dni);
    } else { 
        printf("Registro encontrado en el CUBO %d",i);
        printf("\t %s %s %s %s %s\n",reg.dni,reg.nombre,reg.ape1,reg.ape2,reg.provincia);
    }

    strcpy(dni,"123456789"); // No existe
    i = buscaReg(f,&reg,dni);

    if (i < 0) {
        printf("\nNo existe alumno con dni %s\n",dni);
    } else { 
        printf("Registro encontrado en el CUBO %d",i);
        printf("\t %s %s %s %s %s\n",reg.dni,reg.nombre,reg.ape1,reg.ape2,reg.provincia);
    }

    fclose(f);
}



