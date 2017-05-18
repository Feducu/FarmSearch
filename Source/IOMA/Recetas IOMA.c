#define _CRT_SECURE_NO_WARNINGS
/*
	El programa lee el nro de receta, se fija si ya fue cargada. Si lo fue, muestra los datos en la pantalla.
	Sino, se procede a cargar la receta y hacer los calculos correspondientes.
	Mostrando si están habilitadas o no para ser facturadas.
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "fechas.h"
#include "structs.h"




void cargarreceta(treceta receta);
void imprimirreceta(int nroreg);
void grabarregistro(FILE *f, int nreg, treceta reg);
treceta leerreceta(FILE *f, int nreg); 
tfecha calcularfecha(treceta receta, int dias);
int buscarreg(FILE *archreceta, treceta receta);

int main() {
	int e,reg;
	treceta receta = { 0 };
	FILE *archreceta;
	puts("Salir: 0");
	puts("Cargar Receta: 1");	
	puts("Consultar Receta: 2");
	while ((e = getchar()) != '\n' && e != EOF);
	scanf("%d", &e);
	switch (e)
	{
	case 0:return 1;
		break;
	case 1: cargarreceta(receta);
		break;
	case 2: 
		puts("Ingresar nro de receta");
		//while ((receta.numero = getchar()) != '\n' && receta.numero != EOF);
		scanf("%d", &receta.numero);
		archreceta = fopen("RecetasIOMA.bin", "wb+");
		if (archreceta == NULL) {
			puts("Hubo un error al abrir el archivo");
			return 0;
		}
		reg = buscarreg(archreceta, receta);
		receta = leerreceta(archreceta, reg);
		break;
	default:
		break;
	}
}

void cargarreceta(treceta receta){
	char e,fecha[9];
	FILE *archrecetas;
	int tamano,i;
	treceta comparacion;
	archrecetas=fopen("RecetasIOMA.bin","wb+");
	if(archrecetas==NULL){
		puts("NO SE PUDO CREAR EL ARCHIVO");
		return;
	}

	puts("Ingresar numero de receta");
	scanf("%d",&receta.numero);
	//ORDENAR ARCHIVO ASCENDENTE POR NRO DE RECETA?? Para ahorrar tiempo.
	for (i = 0; feof(archrecetas);i++) {
		comparacion = leerreceta(archrecetas, i);
		if (comparacion.numero == receta.numero) {
			system("cls");
			puts("ESE NUMERO DE RECETA YA FUE CARGADO!");
			printf("NUMERO: %d\n", comparacion.numero);
			printf("FECHA: %d/%d/%d\n", comparacion.fecha.dia, comparacion.fecha.mes, comparacion.fecha.ano);
			if (comparacion.cronico)
				puts("RECETARIO CRONICO");
			if (comparacion.coseguro.fecha.dia) {
				printf("COSEGURO: %s\n", comparacion.coseguro.nombre);
				printf("FECHA COSEGURO: %d/%d/%d\n", comparacion.coseguro.fecha.dia, comparacion.coseguro.fecha.mes, comparacion.coseguro.fecha.ano);
			}
			if (comparacion.autorizacion.desde.dia) {
				printf("FECHA AUTORIZACION\n");
				printf("DESDE: %d/%d/%d", comparacion.autorizacion.desde.dia, comparacion.autorizacion.desde.mes, comparacion.autorizacion.desde.ano);
				printf("HASTA: %d/%d/%d", comparacion.autorizacion.hasta.dia, comparacion.autorizacion.hasta.mes, comparacion.autorizacion.hasta.ano);				
			}
			return;			
		}
	}
	puts("¿Es cronico? (Receta con cuatro cupones)");
	puts("S/N");
	while ((e = getchar()) != '\n' && e != EOF);
	scanf("%c",&e);
	tolower(e);
	while(e!='n' && e!='s'){
		puts("S/N");
		while ((e = getchar()) != '\n' && e != EOF);
		scanf("%c",&e);
		printf("%c", e);
	}
	if(e=='s')
		receta.cronico=1;
	else
		receta.cronico=0;
	puts("¿Tiene autorizacion? (Papel blanco autorizado por IOMA)");
	puts("S/N");
	while ((e = getchar()) != '\n' && e != EOF);
	scanf("%c",&e);
	tolower(e);
	while(e!='n' && e!='s'){
		puts("S/N");
		while ((e = getchar()) != '\n' && e != EOF);
		scanf("%c",&e);
	}
	if(e=='s'){
		puts("Desde..?  (DD/MM/AA)");
		fgets(fecha,9,stdin);
		sscanf(fecha,"%d/%d/%d", &receta.autorizacion.desde.dia, &receta.autorizacion.desde.mes, &receta.autorizacion.desde.ano);
		puts("Hasta..?  (DD/MM/AA)");
		fgets(fecha,9,stdin);
		sscanf(fecha,"%d/%d/%d", &receta.autorizacion.hasta.dia, &receta.autorizacion.hasta.mes, &receta.autorizacion.hasta.ano);
	} // FALTA VALIDAR FORMATO DE ENTRADA. FALTA VALIDAR LAS FECHAS
	puts("¿Tiene coseguro?");
	puts("S/N");
	while ((e = getchar()) != '\n' && e != EOF);
	scanf("%c",&e);
	tolower(e);
	while(e!='n' && e!='s'){
		puts("S/N");
		while ((e = getchar()) != '\n' && e != EOF);
		scanf("%c",&e);
	}
	if(e=='s'){
		//puts("Ingrese el nombre del coseguro. EJ: FEBOS, AJB, SUTEBA");
		//fgets(receta.coseguro.nombre,100,STDIN);
		strcpy(receta.coseguro.nombre,"FEBOS"); //PARA EL FUTURO, SI SE AGREGA OTRO COSEGURO, DESCOMENTAR LO DE ARRIBA y BORRAR ESTO
	}
	fseek(archrecetas, 0, SEEK_END);
	tamano = ftell(archrecetas);
	grabarregistro(archrecetas, tamano, receta);
	fclose(archrecetas);
}//ESTA FUNCION CARGA LOS DATOS DE LA RECETA Y LOS GUARDA EN UN ARCHIVO BINARIO.
void imprimirreceta(int nroreg){
	system("cls");
	FILE *archrecetas;
	treceta receta;
	tfecha fechacalc;
	int fechacompletareceta, fechacompletaautdesde, fechacompletaauthasta;
	archrecetas=fopen("RecetasIOMA.bin","rb");
	if(archrecetas==NULL){
		puts("NO SE PUDO ABRIR EL ARCHIVO 'RecetasIOMA.bin'");
		return;
	}
	receta=leerreceta(archrecetas,nroreg);
	printf("Fecha de la receta: %d/%d/%d\n",receta.fecha.dia, receta.fecha.mes, receta.fecha.ano);
	if(receta.autorizacion.desde.dia){
		printf("DESDE: %d/%d/%d - HASTA: %d/%d/%d\n",receta.autorizacion.desde.dia,receta.autorizacion.desde.mes,receta.autorizacion.desde.ano,receta.autorizacion.hasta.dia,receta.autorizacion.hasta.mes,receta.autorizacion.hasta.ano );
		puts("");
		printf("* * * FECHAS VÁLIDAS: * * *\n");
		//Se calcula la fecha deseada. En este caso 15 días antes de la fecha de la autorización hasta la fecha de la autorización.
		fechacalc=calcularfecha(receta,15);
		printf("DESDE: %d/%d/%d\n", fechacalc.dia,fechacalc.mes,fechacalc.ano);
		printf("HASTA: %d/%d/%d\n", receta.autorizacion.hasta.dia,receta.autorizacion.hasta.mes,receta.autorizacion.hasta.ano);
		fechacompletareceta=receta.fecha.dia*10000+receta.fecha.mes*100+receta.fecha.ano;
		fechacompletaautdesde=fechacalc.dia*10000+fechacalc.mes*100+fechacalc.ano;
		fechacompletaauthasta = receta.autorizacion.hasta.dia * 10000 + receta.autorizacion.hasta.mes * 100 + receta.autorizacion.hasta.ano;
		printf("* * * * ESTADO DE LA RECETA * * * \n");
		if(fechacompletareceta>=fechacompletaautdesde && fechacompletareceta<=fechacompletaauthasta){
			puts("VÁLIDA: FACTURABLE");
			puts("VÁLIDA: FACTURABLE");
			puts("VÁLIDA: FACTURABLE");
		}
	}
	if (fechacompletareceta<fechacompletaautdesde || fechacompletareceta>fechacompletaauthasta) {
		puts("RECETA INVÁLIDA, FUERA DE FECHA!!");
		puts("RECETA INVÁLIDA, FUERA DE FECHA!!");
	}


}//ESTA FUNCION IMPRIME LA RECETA CON LOS CALCULOS DE FECHA YA REALIZADOS.
void grabarregistro(FILE *f, int nreg, treceta reg){
	fseek(f,nreg*sizeof(reg),SEEK_SET);
	fwrite(&reg,sizeof(reg),1,f);
}
treceta leerreceta(FILE *f, int nreg){
	treceta reg;
	fseek(f,nreg*sizeof(reg),SEEK_SET);
	fread(&reg,sizeof(reg),1,f);
	return reg;
}
tfecha calcularfecha(treceta receta, int dias){
	tfecha fecha;
	fecha.ano = receta.fecha.ano;
	fecha.mes = receta.fecha.mes;	
	fecha.dia=receta.fecha.dia-dias;
	while(fecha.dia<1){
		fecha.mes--;
		if(istreinta(fecha.mes))
			fecha.dia+=30;
		if(istreintauno(fecha.mes))
			fecha.dia+=31;
		if(fecha.mes==2){
			if(isbisiesto(fecha.ano))
				fecha.dia+=29;
			else
				fecha.dia+=28;
			}

		if(fecha.mes<1){
			fecha.ano--;
			fecha.mes=12;
		}
	}
	return fecha;
}
int buscarreg(FILE *archreceta, treceta receta) {
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
