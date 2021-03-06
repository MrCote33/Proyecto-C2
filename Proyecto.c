//Basado en un ejemplo que realizo en Profesor Federico Meza (hoja.c)
//Creado y provado unicamente en Windows 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LARGO 150
#define MAX_DATOS 50

struct Informacion{
	
	int year;
	char tipo[MAX_DATOS];
	float desplazamiento;
	int cilindros;
	char combustible[MAX_DATOS];
	char transmision[MAX_DATOS];
	char traccion[MAX_DATOS];
	struct Informacion *sgte;
	
};

struct Modelo{
	
	char modelo[MAX_DATOS];
	struct Modelo *sgte;
	struct Informacion *info;
	
};

struct Marca{
	
	char marca[MAX_DATOS];
	struct Modelo *model;
	struct Marca *sgte;
	
};

struct Informacion *ingresar_info(struct Informacion *ComienzoInfo, char Linea[]){
	
	struct Informacion *NuevaInfo, *Puntero;
	char help[MAX_DATOS];
	int Num1, Num2, Contador;
	
	Num2 = 0;
	Contador = 0;
	
	NuevaInfo = malloc(sizeof(struct Informacion));
	
	for(Num1 = 0; Num1 < strlen(Linea); Num1++, Num2++){
		
		help[Num2] = Linea[Num1];
		
		if(help[Num2] == ';' || help[Num2] == '\n'){
			
			Contador++;
			help[Num2] = '\0';
			
			if(Contador == 3){
				NuevaInfo->year = atoi(help);
			}
			if(Contador == 4){
				strcpy(NuevaInfo->tipo,help);
			}
			if(Contador == 5){
				NuevaInfo->desplazamiento = atof(help);
			}
			if(Contador == 6){
				NuevaInfo->cilindros = atoi(help);
			}
			if(Contador == 7){
				strcpy(NuevaInfo->combustible,help);
			}
			if(Contador == 8){
				strcpy(NuevaInfo->transmision,help);
			}
			if(Contador == 9){
				strcpy(NuevaInfo->traccion,help);
			}
			
			Num2 = -1;
			strcpy(help," ");
			
		}
		
	}
	
	if(ComienzoInfo == NULL || NuevaInfo->year < ComienzoInfo->year){
		NuevaInfo->sgte = ComienzoInfo;
		return NuevaInfo;
	}
	
	Puntero = ComienzoInfo;
	
	while(Puntero->sgte != NULL && Puntero->sgte->year < NuevaInfo->year){
		Puntero = Puntero->sgte;
	}
	
	NuevaInfo->sgte = Puntero->sgte;
	Puntero->sgte = NuevaInfo;
	return ComienzoInfo;
	
}

struct Modelo *buscar_modelo(struct Modelo *ComienzoMo, char Busqueda[]){
	
	struct Modelo *Puntero;
	
	Puntero = ComienzoMo;
	
	while(Puntero != NULL && strcmp(Busqueda,Puntero->modelo) != 0){
		Puntero = Puntero->sgte;
	}
	return Puntero;
	
}

struct Modelo *ingresar_modelo(struct Modelo *ComienzoMo, char *modelo){
	
	struct Modelo *NuevoMo, *Puntero;
	
	NuevoMo = malloc(sizeof(struct Modelo));
	strcpy(NuevoMo->modelo,modelo);
	
	if(ComienzoMo == NULL || strcmp(NuevoMo->modelo,ComienzoMo->modelo) < 0){
		NuevoMo->sgte = ComienzoMo;
		return NuevoMo;
	}
	
	Puntero = ComienzoMo;
	
	while(Puntero->sgte != NULL && strcmp(Puntero->sgte->modelo,modelo) < 0){
		Puntero = Puntero->sgte;
	}
	
	NuevoMo->sgte = Puntero->sgte;
	Puntero->sgte = NuevoMo;
	return ComienzoMo;
	
}

struct Modelo *leer_modelo(struct Modelo *ComienzoMo, char Linea[]){
	
	struct Modelo *NuevoMo;
	char help[MAX_DATOS];
	char modelo[MAX_DATOS];
	int Num1, Num2, Contador;
	
	Num2 = 0;
	Contador = 0;
	
	for(Num1 = 0; Num1 < strlen(Linea); Num1++, Num2++){
		
		help[Num2] = Linea[Num1];
		
		if(help[Num2] == ';' || help[Num2] == '\n'){
			
			Contador++;
			help[Num2] = '\0';
			
			if(Contador == 2){
				strcpy(modelo,help);
			}
			if(Contador == 3){
				Num1 = strlen(Linea);
			}
			
			Num2 = -1;
			strcpy(help," ");
			
		}
		
	}
	
	NuevoMo = buscar_modelo(ComienzoMo,modelo);
	
	if(NuevoMo == NULL){
		ComienzoMo = ingresar_modelo(ComienzoMo,modelo);
		NuevoMo = buscar_modelo(ComienzoMo,modelo);
		NuevoMo->info = NULL;
	}
	
	NuevoMo->info = ingresar_info(NuevoMo->info,Linea);
	return ComienzoMo;
	
}

struct Marca *buscar_marca(struct Marca *ComienzoMa, char *Busqueda){
	
	struct Marca *Puntero;
	
	Puntero = ComienzoMa;
	
	while(Puntero != NULL && strcmp(Busqueda,Puntero->marca) != 0){
		Puntero = Puntero->sgte;
	}
	
	return Puntero;
	
}

struct Marca *ingresar_marca(struct Marca *ComienzoMa, char *marca){
	
	struct Marca *NuevaMa, *Puntero;
	
	//Crea la marca, la ordena y la incluye en la lista
	
	NuevaMa =  malloc(sizeof(struct Marca));
	strcpy(NuevaMa->marca,marca);
	
	if(ComienzoMa == NULL || strcmp(NuevaMa->marca,ComienzoMa->marca) < 0){
		NuevaMa->sgte = ComienzoMa;
		return NuevaMa;
	}
	
	Puntero = ComienzoMa;
	
	//While que recorre la lista para ordenarla
	
	while(Puntero->sgte != NULL && strcmp(Puntero->sgte->marca,marca) < 0){
		Puntero = Puntero->sgte;
	}
	
	NuevaMa->sgte = Puntero->sgte;
	Puntero->sgte = NuevaMa;
	return ComienzoMa;
	
}

struct Marca *leer_marca(struct Marca *ComienzoMa, char Linea[]){
	
	struct Marca *NuevaMa;
	char help[MAX_DATOS];
	char marca[MAX_DATOS];
	int Num, Contador;
	
	Contador = 0;
	
	//Ciclo que corta informacion por Punto y Coma.
	for(Num = 0; Num < strlen(Linea); Num++){
		
		help[Num] = Linea[Num];
		
		if(help[Num] == ';' || help[Num] == '\n'){
			
			Contador++;
			help[Num] = '\0';
			
			if(Contador == 1){
				strcpy(marca,help);
			}
			if(Contador == 2){
				Num = strlen(Linea);
			}
			
			strcpy(help," ");
			
		}
		
	}
	
	//Busca si la marca ya existe
	NuevaMa = buscar_marca(ComienzoMa,marca);
	
	//Accion a realizar si la marca no existe
	if(NuevaMa == NULL){
		ComienzoMa = ingresar_marca(ComienzoMa,marca);
		NuevaMa = buscar_marca(ComienzoMa,marca);
		NuevaMa->model = NULL;
	}
	NuevaMa->model = leer_modelo(NuevaMa->model,Linea);
	return ComienzoMa;
	
}

void buscar_desplaza(struct Marca *marca, struct Modelo *modelo, struct Informacion *info, float desplaza){
	
	struct Informacion *Puntero;
	int Contador;
	
	Contador = 0;
	Puntero = info;
	
	printf("\n");
	
	while(Puntero != NULL){
		
		if(Puntero->desplazamiento == desplaza){
			
			Contador++;
			printf("%d %s %.1f %d %s %s %s\n",Puntero->year,Puntero->tipo,Puntero->desplazamiento,Puntero->cilindros,Puntero->combustible,Puntero->transmision,Puntero->traccion);
			
		}
		
		Puntero = Puntero->sgte;
	}
	
	printf("\n");
	
	if(Contador == 0){
		printf("\nNo se encontraron modelos con desplazamiento %.1f para el %s %s.\n\n",desplaza,marca->marca,modelo->modelo);
	}
	
}

void verificar_vehiculo(struct Marca *Comienzo){
	
	struct Marca *marca;
	struct Modelo *modelo;
	struct Informacion *info;
	
	char fabricante[MAX_DATOS];
	char tipo_modelo[MAX_DATOS];
	float desplaza;
	
	system("cls");
	
	printf("\nLa entrada de las variables debe respetar Mayusculas, Minusculas y Espacios\n\n");
	
	printf("Ingresa la marca del vehiculo: ");
	scanf("%s",&fabricante);
	fflush(stdin);
	printf("Ingresa el modelo del vehiculo: ");
	fgets(tipo_modelo,MAX_DATOS,stdin);
	tipo_modelo[strlen(tipo_modelo)-1] = '\0';
	printf("Ingrese el desplazamiento del vehiculo: ");
	scanf("%f",&desplaza);
	
	marca = buscar_marca(Comienzo,fabricante);
	
	if(marca != NULL){
		modelo = marca->model;
		modelo = buscar_modelo(modelo,tipo_modelo);
		if(modelo != NULL){
			info = modelo->info;
			buscar_desplaza(marca,modelo,info,desplaza);
		}else{
			printf("No se encontro tal modelo.\n");
		}
	}else{
		printf("No se encontro tal marca.\n");
	}
	
	system("pause");
	
}

void busqueda_years(struct Marca *marca, struct Modelo *modelo, struct Informacion *info, int Year_Start, int Year_Stop){
	
	struct Informacion *Puntero;
	int Contador;
	
	Contador = 0;
	Puntero = info;
	
	while(Puntero != NULL){
		
		if(Puntero->year >= Year_Start && Puntero->year <= Year_Stop){
			
			Contador++;
			printf("%d %s %.1f %d %s %s %s\n",Puntero->year,Puntero->tipo,Puntero->desplazamiento,Puntero->cilindros,Puntero->combustible,Puntero->transmision,Puntero->traccion);
			
		}
		Puntero = Puntero->sgte;
		
	}
	
	printf("\n");
	
	if(Contador == 0){
		printf("No se encontraron modelos entre el a�o %d y %d para el %s %s.\n\n",Year_Start,Year_Stop,marca->marca,modelo->modelo);
	}
	
}

void buscar_auto(struct Marca *Comienzo){
	
	struct Marca *marca;
	struct Modelo *modelo;
	struct Informacion *info;
	
	char fabricante[MAX_DATOS];
	char tipo_modelo[MAX_DATOS];
	int Year_Start, Year_Stop, Year_Temp;
	
	system("cls");
	
	printf("\nLa entrada de las variables debe respetar Mayusculas, Minusculas y Espacios\n\n");
	
	printf("Ingresa la marca del vehiculo: ");
	scanf("%s",&fabricante);
	fflush(stdin);
	printf("Ingresa el modelo del vehiculo: ");
	fgets(tipo_modelo,MAX_DATOS,stdin);
	tipo_modelo[strlen(tipo_modelo)-1] = '\0';
	
	printf("Ingrese el rango de a�os [A�o Inicio] [A�o Final]: ");
	scanf("%d %d",&Year_Start,&Year_Stop);
	printf("\n");
	
	if(Year_Stop < Year_Start){
		
		Year_Temp = Year_Stop;
		Year_Stop = Year_Start;
		Year_Start = Year_Temp;
		
	}

	marca = buscar_marca(Comienzo,fabricante);
	
	if(marca != NULL){
		modelo = marca->model;
		modelo = buscar_modelo(modelo,tipo_modelo);
		if(modelo != NULL){
			info = modelo->info;
			busqueda_years(marca,modelo,info,Year_Start,Year_Stop);
		}else{
			printf("No se encontro tal modelo.\n");
		}
	}else{
		printf("No se encontro tal marca.\n");
	}
	
	system("pause");
	
}

main(int argc, char *argv[]){
	
	char Linea[MAX_LARGO];
	int opcion;
	
	FILE *Vehiculos;
	Vehiculos = fopen(argv[1],"r");
	
	struct Marca *inicio;
	inicio = NULL;

	if(argc != 2 && Vehiculos == NULL){
		printf("\nArchivo ingresado no es valido o no se encontro en la carpeta\n");
		exit(EXIT_FAILURE);
	}else{
		while(fgets(Linea,MAX_LARGO,Vehiculos) != NULL){
			inicio = leer_marca(inicio,Linea);
		}
		fclose(Vehiculos);
		do{
			system("cls");
			printf("[|] Seleccione una opcion [|]\n");
			printf("\n[1] Buscar apartir de rango de a�os\n");
			printf("[2] Verificar si existe un modelo\n");
			printf("[3] Salir\n");
			
			printf("\nOpcion a realizar: ");
			opcion = 0;
			scanf("%d",&opcion);
			fflush(stdin);
			
			switch(opcion){
				
				system("cls");
				
				case 1:
					buscar_auto(inicio);
					break;
				case 2:
					verificar_vehiculo(inicio);
					break;
				case 3:
					system("cls");
					break;
				default:
					break;

			}
			
		}while(opcion != 3);

	}
}
