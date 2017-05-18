#ifndef STRUCS_H
#define STRUCS_H

typedef struct sfecha{
	int dia;
	int mes;
	int ano;
}tfecha;

typedef struct autorizacion{
	tfecha desde;
	tfecha hasta;
}tautorizacion;

typedef struct scoseguro{
	char nombre[100];
	tfecha fecha;	
}tcoseguro;

typedef struct sreceta{
	int cronico;
	int numero;
	tautorizacion autorizacion;
	tcoseguro coseguro;
	tfecha fecha;
}treceta;
 
#endif