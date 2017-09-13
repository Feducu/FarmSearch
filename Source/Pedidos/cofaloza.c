
#include <stdio.h>
#include "structs.h"
#include <string.h>

/*
https://www.cofaloza.com.ar/intranet/aplic/modules/carrito/shop.php?spx=999&buscar=$DATOS
DATOS = Cdgo barras o nombre
*/


void cofaloza(){
	FILE *fin;
    char *line;
    if((fin = fopen(argv[1], "r"))==NULL){
    	//TODO: ARREGLAR EL NOMBRE DEL ARCHIVO CON EL SCRIPT .py
    	puts("ERROR AL ABRIR EL LAST_");
    	return EXIT_FAILURE;
    }
    
    if ( fin ) {
        while ( line = read_line(fin) ) {
            if ( strstr(line, argv[2]) ){
                fprintf(stdout, "%s\n", line);
                //ACA IMPRIME LA LINEA QUE ENCONTRO
            }
            free(line);
        }
    }

    fclose(fin);
    return 0;
}




}





