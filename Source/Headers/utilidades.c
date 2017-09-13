#include "utilidades.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef DEBUG
#define INITIAL_ALLOC 2
#else
#define INITIAL_ALLOC 512
#endif

limpiarbufferchar(char c){
	while ((c = getchar()) != '\n' && c != EOF);
}
void grabarreceta(FILE *f, int nreg, treceta reg){
	fseek(f,nreg*sizeof(reg),SEEK_SET);
	fwrite(&reg,sizeof(reg),1,f);
}
treceta leerreceta(FILE *f, int nreg){
	treceta reg;
	fseek(f,nreg*sizeof(reg),SEEK_SET);
	fread(&reg,sizeof(reg),1,f);
	return reg;
}

//Busca de una forma rudimentaria en un archivo binario que NO está ordenado.
int buscarreceta(FILE *archreceta, treceta receta) {
	int reg=0,flag=1;
	treceta lectura;
	while (flag)
	{
		lectura = leerreceta(archreceta, reg);
		if (lectura.numero == receta.numero)
			flag = 0;
		else		
			reg++;			
	}
	return reg;
}

char *read_line(FILE *fin) {
    char *buffer;
    char *tmp;
    int read_chars = 0;
    int bufsize = INITIAL_ALLOC;
    char *line = malloc(bufsize);

    if ( !line ) {
        return NULL;
    }

    buffer = line;

    while ( fgets(buffer, bufsize - read_chars, fin) ) {
        read_chars = strlen(line);

        if ( line[read_chars - 1] == '\n' ) {
            line[read_chars - 1] = '\0';
            return line;
        }

        else {
            bufsize = 2 * bufsize;
            tmp = realloc(line, bufsize);
            if ( tmp ) {
                line = tmp;
                buffer = line + read_chars;
            }
            else {
                free(line);
                return NULL;
            }
        }
    }
    return NULL;
}




