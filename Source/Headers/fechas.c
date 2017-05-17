#include"fechas.h"

int istreinta(int mes) {
 	if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
 		return 1;
 	else
 		return 0;
 }
 int istreintauno(int mes) {
 	if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
 		return 1;
 	else
 		return 0;
 }
 int isbisiesto(int ano) {
 	int flag=0;
 	if (ano % 4 == 0) {
 		flag = 1;
 		if (ano % 100 == 0)
 			flag = 0;
 		if (ano % 400 == 0)
 			flag = 1;
 	}
 }