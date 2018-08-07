#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
#define LARGO 150

struct Marcas{
	
	char *Marca;
	struct Marcas *SgteMa;
	struct Modelos *SgteMo;
	
};

struct Modelos{
	
	char *Modelo;
	struct Modelos *SgteMo;
	struct Datos *SgteDs;
	
};

struct Datos{
	
	int Year;
	char *Tipo;
	float Desplazamiento;
	int Cilindros;
	char *Combustible;
	char *Cambio;
	char *Traccion;
	struct Datos *SgteDs;
	
};

int PuntoComa(int Inicio, char Linea[], char Regreso[]){
	
	int Largo, Num, Total, Cont, Final;
	char Dato[MAX];
	
	Largo = strlen(Linea);
	
	for(Num = Inicio; Num < Largo; Num++){
		
		if(Linea[Num] == ';' || Linea[Num+1] == '\0'){	
				
			Final = Num;
			Cont = 0;
			
			for(Total = Inicio; Total < Final; Total++){
	
				Dato[Cont] = Linea[Total];
				Dato[Cont+1] = '\0';
				Cont++;
	
			}

			strcpy(Regreso,Dato);
			return Final+1;
			
		}
		
	}

}

main(){
	
	int Inicio, ContPuntoComa;
	char Linea[LARGO];
	char Dato[MAX];

	FILE *Vehiculos;
	Vehiculos = fopen("vehiculos-diminuto.csv","r");
	
	Inicio = 0;
	
	struct Marcas *Marca;
	Marca = NULL;
	struct Modelos *Modelo;
	Modelo = NULL;
	struct Datos *AllDatos;
	AllDatos = NULL;
	
	while(fgets(Linea,LARGO,Vehiculos) != NULL){
		
		for(ContPuntoComa = 0; ContPuntoComa < 9; ContPuntoComa++){
			
			Inicio = PuntoComa(Inicio,Linea,Dato);
			printf("%s ",Dato);
			
		}
		
		printf("\n");
		Inicio = 0;

	}
	
}
