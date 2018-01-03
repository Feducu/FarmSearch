#include <stdio.h>
#include <stdlib.h>
typedef struct sfecha
{
	int dia;
	int mes;
	int ano;
	int hs;
	int min;
	int seg;
}tfecha;

typedef struct spedido
{
	int numero=0;
	tfecha fecha;
}tpedido;

typedef struct sproductofinal{
	int cantidad;
	int barras; //es un int así se pueden comparar fácilmente
	char nombre[30];
}tproductofinal;

typedef struct snodo
{
	int barras;
	char *nombre;
	struct snodo *sig,*ant;
}tnodo;

typedef tnodo *tpunteronodo;

void insertarenorden(tpunteronodo *cabeza, tproductofinal archivo);
void procesararchivo(FILE *pedido);
void escribirenbin(char linea);




int main(){
	
	int e=0;
	tpunteronodo cabeza;
	cabeza=NULL;
	
	//Leer linea, son 55 caracteres como máximo
	puts("Codigo de barras:");
	scanf("%d",&e);
	while(e!=-1){

		scanf("%d",&e);
	}

	// imprimir los faltantes

	fclose(pedido);
}





void insertarenorden(tpunteronodo *cabeza, tproductofinal archivo) {
	tpunteronodo actual, anterior, nuevo;
	actual = *cabeza;
	anterior = NULL;
	while (actual != NULL&&actual->barras < archivo.barras)
	{
		anterior = actual;
		actual = actual->sig;
	}
	nuevo = malloc(sizeof(tnodo));
	nuevo->barras = archivo.barras;
	nuevo->nombre = archivo.nombre;
	nuevo->ant = anterior;
	nuevo->sig = actual;
	if (anterior!=NULL)
	{
		anterior->sig = nuevo;
	}
	else
	{
		*cabeza = nuevo;
	}if (actual!=NULL)
	{
		actual->ant = nuevo;
	}
}

void procesararchivo(FILE *pedido){
	FILE *pedido, *pedidobin;
	tproductofinal archivo;
	tpedido pedido;
	char linea[55], cantidad[12],buffername[32];
	int i,j,k=0,l=100000;

	//abrir archivo pedido.txt
	if((pedido=fopen("pedido.txt","r+"))==NULL){
		puts("ERROR AL ABRIR EL ARCHIVO pedido.txt");
		return EXIT_FAILURE;
	}	
	
	
	for(i=0;i<7;i++){
		fgets(linea,55,pedido);
		
		//LEO LA FECHA DEL PEDIDO
		if(i=2)
			sscanf(linea,"%d/%d/%d                      %d:%d:%d",pedido.dia,pedido.mes,pedido.ano,pedido.hs,pedido.min,pedido.seg);
		//FIN FECHA PEDIDO

		//LEO EL NRO DE PEDIDO
		if(i=6)
			for(j=0;j<55;j++)
				if(isdigit(linea[j])){
					pedido.numero=pedido.numero+linea[j]*l;
					l/=10;		
				}
		//FIN NRO PEDIDO
	}
	rewind(pedido);
	//Le saco los 0 restantes al nro de pedido.
	while (!pedido.numero&10)
		pedido.numero/=10;

	//CREO EL ARCHIVO CON NOMBRE 'AÑO-MES-DIA-NROPEDIDO pedido.bin'
	snprintf(buffername, sizeof(char) * 32, "%i-%i-%i-%i pedido.bin",pedido.fecha.ano,pedido.fecha.mes,pedido.fecha.dia, pedido.numero);
	if((pedidobin=fopen(buffername,"wb"))==NULL){
		printf("ERROR AL CREAR EL ARCHIVO %i-%i-%i-%i pedido.bin",pedido.fecha.ano,pedido.fecha.mes,pedido.fecha.dia, pedido.numero);
		return EXIT_FAILURE;
	}
	
	//AVANZO NUEVE LINEAS DE "BASURA"
	for(i=0;i<9;i++)
			fgets(linea,55,pedido);
	//FIN AVANCE

	while(!feof(pedido)){

		fgets(linea,55,pedido);
	//Del caracter 5 a 6 (inclusive) empieza la cantidad
		if (isdigit(linea[5]))
			archivo.cantidad=linea[4]*10+linea[5];
		else archivo.cantidad=linea[4];
	//Del caracter 8 al 33 empieza el nombre del producto
		strncpy(archivo.nombre,&linea[7],25);
	//A partir del caracter 35 (inclusive) empieza el cdo de barras (13NROS)
		sscanf(&linea[34],"%d",&archivo.barras);
	}

		
	//Buscar en todos los cdo el ingresado por el usuario

	// "descartar" los ya encontrados

			}