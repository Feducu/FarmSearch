#include "utilidades.h"

limpiarbufferchar(char c){
	while ((c = getchar()) != '\n' && c != EOF);
}


