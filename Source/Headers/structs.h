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

typedef struct sproducto
{
	char nombre[100];
	char lab[100];
	char tipo[3];
	float precio;
	bool trazabilidad;
	float iva;
	char barras[13];
	char troquel[7];
	tfecha vencimiento;
	bool baja;
	int stock;
	char drogas[200]; // Revisar esto, no se si conviene hacer 2 strings distintas para droga o no.
}tproducto;
 
#endif