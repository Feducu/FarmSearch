#include "utilidades.h"
#include "structs.h"

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



