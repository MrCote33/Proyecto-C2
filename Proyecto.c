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

struct Marcas *Insertar_Marca(struct Marcas *Comienzo, char Dato[]){
	
	struct Marcas *NuevaMarca;
	
	NuevaMarca = malloc(sizeof(struct Marcas));
	NuevaMarca->Marca = Dato;
	NuevaMarca->SgteMa = Comienzo;
	
	return NuevaMarca;
	
}

struct Modelos *Insertar_Modelo(struct Modelos *Comienzo, char Dato[]){
	
	struct Modelos *NuevoModelo;
	
	NuevoModelo = malloc(sizeof(struct Marcas));
	NuevoModelo->Modelo = Dato;
	NuevoModelo->SgteMo = Comienzo;
	
	return NuevoModelo;
	
}

struct Datos *Insertar_Datos(struct Datos *Comienzo, char Dato[], int Contador){
	
	struct Datos *NuevoDato;
	
	NuevoDato = malloc(sizeof(struct Datos));
	
	if(Contador == 2){
		NuevoDato->Year = atoi(Dato);
	}
	if(Contador == 3){
		NuevoDato->Tipo = Dato;
	}
	if(Contador == 4){
		NuevoDato->Desplazamiento = strtof(Dato,NULL);
	}
	if(Contador == 5){
		NuevoDato->Cilindros = atoi(Dato);
	}
	if(Contador == 6){
		NuevoDato->Combustible = Dato;
	}
	if(Contador == 7){
		NuevoDato->Cambio = Dato;
	}
	if(Contador == 8){
		NuevoDato->Traccion = Dato;
	}
	
}

main(){
	
	int Inicio, ContPuntoComa;
	char Linea[LARGO];
	char Dato[MAX];

	FILE *Vehiculos;
	Vehiculos = fopen("vehiculos-diminuto.csv","r");
	
	struct Marcas *Marca;
	Marca = NULL;
	struct Modelos *Modelo;
	Modelo = NULL;
	struct Datos *AllDatos;
	AllDatos = NULL;
	
	Inicio = 0;
	
	while(fgets(Linea,LARGO,Vehiculos) != NULL){
		
		for(ContPuntoComa = 0; ContPuntoComa < 9; ContPuntoComa++){
			
			Inicio = PuntoComa(Inicio,Linea,Dato);
			
			if(ContPuntoComa == 0){
				Marca = Insertar_Marca(Marca,Dato);
				printf("%s ",Marca->Marca);
			}
			if(ContPuntoComa == 1){
				Modelo = Insertar_Modelo(Modelo,Dato);
				printf("%s ",Modelo->Modelo);
			}
			if(ContPuntoComa == 2){
				AllDatos = Insertar_Datos(AllDatos,Dato,ContPuntoComa);
				printf("%d ",AllDatos->Year);
			}
			if(ContPuntoComa == 3){
				AllDatos = Insertar_Datos(AllDatos,Dato,ContPuntoComa);
				printf("%s ",AllDatos->Tipo);	
			}
			if(ContPuntoComa == 4){
				AllDatos = Insertar_Datos(AllDatos,Dato,ContPuntoComa);
				printf("%.1f ",AllDatos->Desplazamiento);
			}
			if(ContPuntoComa == 5){
				AllDatos = Insertar_Datos(AllDatos,Dato,ContPuntoComa);
				printf("%d ",AllDatos->Cilindros);
			}
			if(ContPuntoComa == 6){
				AllDatos = Insertar_Datos(AllDatos,Dato,ContPuntoComa);
				printf("%s ",AllDatos->Combustible);
			}
			if(ContPuntoComa == 7){
				AllDatos = Insertar_Datos(AllDatos,Dato,ContPuntoComa);
				printf("%s ",AllDatos->Cambio);
			}
			if(ContPuntoComa == 8){
				AllDatos = Insertar_Datos(AllDatos,Dato,ContPuntoComa);
				printf("%s ",AllDatos->Traccion);
			}
		
		}
		
		printf("\n");
		Inicio = 0;

	}
	
}
