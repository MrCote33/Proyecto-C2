#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
#define LARGO 150

struct Marcas{
	
	char *Marca;
	struct Marcas *SgteMa;
	
};

struct Modelos{
	
	char *Modelo;
	struct Modelos *SgteMo;
	
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

struct Marcas *Ingresar_Marca(struct Marcas *Inicio, char Dato[]){
	
	struct Marcas *Nuevo;
	
	Nuevo = malloc(sizeof(struct Marcas));
	Nuevo -> Marca = Dato;
	printf("%s ",Nuevo -> Marca);
	Nuevo -> SgteMa = Inicio;
	
	return Nuevo;
	
}

struct Modelos *Ingresar_Modelo(struct Modelos *Inicio, char Dato[]){
	
	struct Modelos *Nuevo;
	
	Nuevo = malloc(sizeof(struct Modelos));
	Nuevo -> Modelo = Dato;
	printf("%s ",Nuevo -> Modelo);
	Nuevo -> SgteMo = Inicio;
	
	return Nuevo;
	
}

struct Datos *Ingresar_Datos(struct Datos *Comienzo, char Linea[], int Start){
	
	struct Datos *Nuevo;
	char Dato[MAX];
	int Inicio = Start;
	Nuevo = malloc(sizeof(struct Datos));
	
	Inicio = PuntoComa(Inicio,Linea,Dato);
	Nuevo -> Year = atoi(Dato);
	printf("%d ",Nuevo -> Year);
	Inicio = PuntoComa(Inicio,Linea,Dato);
	Nuevo -> Tipo = Dato;
	printf("%s ",Nuevo -> Tipo);
	Inicio = PuntoComa(Inicio,Linea,Dato);
	Nuevo -> Desplazamiento = atof(Dato);
	printf("%.1f ",Nuevo -> Desplazamiento);
	Inicio = PuntoComa(Inicio,Linea,Dato);
	Nuevo -> Cilindros = atoi(Dato);
	printf("%d ",Nuevo -> Cilindros);
	Inicio = PuntoComa(Inicio,Linea,Dato);
	Nuevo -> Combustible = Dato;
	printf("%s ",Nuevo -> Combustible);
	Inicio = PuntoComa(Inicio,Linea,Dato);
	Nuevo -> Cambio = Dato;
	printf("%s ",Nuevo -> Cambio);
	Inicio = PuntoComa(Inicio,Linea,Dato);
	Nuevo -> Traccion = Dato;
	printf("%s\n",Nuevo -> Traccion);
	
	Nuevo -> SgteDs = Comienzo;
	return Nuevo;
	
}

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
	Vehiculos = fopen("vehiculos-chico.csv","r");
	
	Inicio = 0;
	
	struct Marcas *Marca;
	Marca = NULL;
	struct Modelos *Modelo;
	Modelo = NULL;
	struct Datos *AllDatos;
	AllDatos = NULL;
	
	while(fgets(Linea,LARGO,Vehiculos) != NULL){
			
		Inicio = PuntoComa(Inicio,Linea,Dato);
		Marca = Ingresar_Marca(Marca,Dato);
		
		Inicio = PuntoComa(Inicio,Linea,Dato);
		Modelo = Ingresar_Modelo(Modelo,Dato);
		
		AllDatos = Ingresar_Datos(AllDatos,Linea,Inicio);
		
		Inicio = 0;

	}
	
}
