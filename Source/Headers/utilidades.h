#ifndef UTILIDADES_H
#define UTILIDADES_H
#include "structs.h"

void limpiarbufferchar(char c);
void grabarreceta(FILE *f, int nreg, treceta reg);
treceta leerreceta(FILE *f, int nreg);
int buscarreceta(FILE *archreceta, treceta receta);
char *readline(FILE *fin);

#endif