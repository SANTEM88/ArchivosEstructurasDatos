/*
* Estudiante: Santiago Enriquez Martinez
* Actividad: Gestion de informacion usando archivos de registros
* Curso: Estructuras de datos GR.3
* Compilador: TDM-GCC 4.9.2 x64
* Informacion: crear un programa que use archivos binarios, que consulte, modifique, agregue y elimine, datos de automoviles.
*********************************************
* (ver. 1.1)Actualizacion del programa:
* -Se elimino la funcion de menu y se utilizo bucle do-while en lugar de recursividad.
* -Se soluciono error en la conversion de datos a long en la funcion "modificar", particularmente en fseek.
* -Se elimino el argumento rb+ de la funcion consultar.
* -Se cambio el tipo de todas las funciones a void.
* -Se agrego a "struct carro" nuevos datos de acuerdo al problema: placa, modelo, year, estado y color. 
* -Se añade nueva funcion para buscar por placa en lugar del nombre (en la funcion consultar).
* -Se modfico el menu de cambio de dato por do-while en caso de que se escriba una opcion incorrecta.
* -Se corrigio error de buffer en la funcion agregar.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct carro {
	char placa[7];
	char nombre[20];
	char marca[20];
	float precio;
	char tipo;//propio o consignado
	int modelo;
	char color[20];
	int year;
	char estado; // activo o eliminado
};

//prototipos de funciones
void agregar();
void consultar();
void modificar();
void eliminar();
int buscar(char placa[]);
void consultar_estado();

int main() {
	
	setlocale(LC_ALL, "Spanish");
	int p; 
	
	do {
		system("cls");
		printf("MENU PRINCIPAL\n-----------------\n");
		printf("1-. Registrar vehiculos.\n");
		printf("2-. Consultar existencias.\n");
		printf("3-. Actualizar o modificar informacion.\n");
		printf("4-. Eliminar un vehiculo del sistema.\n");
		printf("5-. Consultar por estado.");
		prinft("6-. Salir\n");
		printf("Su opcion: ");
		
		scanf("%i", &p);
		getchar();//vaciar buffer'\n'
		
		switch(p){
		case 1:
			agregar();
		break;
		
		case 2:
			consultar();
		break;
		
		case 3:
			modificar();
		break;
		
		case 4:
			eliminar();
		break;
		
		case 5:
			consultar_estado();
		break;
		
		case 6:
		break;
		
		default:
			system("cls");
			printf("Opcion incorrecta!");
			printf("Presione una tecla para continuar...");
			getchar();
		break;
		} 
	} while(p != 6);
	
	return 0;
}

void agregar(){
	
	struct carro PrimerRegistro;
	char placa[7];
	
	printf("Ingrese la placa del vehiculo de esta forma > EJ.(ABC123): ");
	scanf("%7s", &placa);//carga placa del vehiculo
	getchar();//buffer
	int a = buscar(placa);//funcion buscar en el archivo por si el vehiculo ya se encuentra registrado
	if(a == 1){
		printf("***************************************\n");
		printf("El archivo ya se encuentra en el sistema.\n");
		printf("Presione enter para continuar...");
		getchar();
		return;
	}
	strcpy(PrimerRegistro.placa, placa);//copiar la cadena al registro
	
	FILE* archivo;
	archivo = fopen("vehiculos.bin", "ab");
	if(archivo != NULL){
		printf("Ingrese el nombre del vehiculo: ");
		scanf(" %s", &PrimerRegistro.nombre); //cargar nombre del vehiculo
		printf("Ingrese la marca del vehiculo: ");
		scanf(" %s", &PrimerRegistro.marca);//cargar nombre de la marca
		printf("Ingrese el precio del vehiculo: ");
		scanf(" %f", &PrimerRegistro.precio);
		getchar();
		
		while(PrimerRegistro.precio <= 0){ //el precio no puede ser negativo
			printf("Inserte un precio valido: ");
			scanf(" %f", &PrimerRegistro.precio);
			getchar();
		}
		
		while(getchar() != '\n'){ //vaciar el buffer
		}
		
		printf("El tipo de vehiculo se especifica de acuerdo a:\n");
        printf("P-.Propio.\n");
        printf("C-.Consignado.\n");
        printf("------------------------\n");
        printf("Ingrese el tipo de automovil: ");
		scanf(" %c", &PrimerRegistro.tipo);//cargar el tipo de carro
		getchar();
		
	    while (PrimerRegistro.tipo != 'P' && PrimerRegistro.tipo != 'C'){
	    	printf("Digite un tipo de auto existente como se le menciono anteriormente:");
	    	scanf(" %c", &PrimerRegistro.tipo);
		}
		
		printf("Ingrese el modelo del vehiculo: ");
		scanf(" %i", &PrimerRegistro.modelo);
		getchar();
		
		while(PrimerRegistro.modelo <= 0){ //el modelo no puede ser negativo
			printf("Inserte un modelo valido: ");
			scanf(" %i", &PrimerRegistro.modelo);
			getchar();
		}
		
		printf("Ingrese el color del vehiculo: ");
		scanf(" %s", &PrimerRegistro.color);
		printf("Ingrese el año del vehiculo: ");
		scanf(" %i", &PrimerRegistro.year);
		getchar();
		
		while(PrimerRegistro.year <= 0){ //el año no puede ser negativo
			printf("Inserte un año valido: ");
			scanf(" %i", &PrimerRegistro.year);
			getchar();
		}
		
		printf("Informacion: Al ser primera vez, su automovil estara activo, si lo borra, quedara eliminado.\n");
		PrimerRegistro.estado = 'A';
		
		fwrite(&PrimerRegistro, sizeof(struct carro), 1, archivo);
		fclose(archivo);//cerrar el archivo
		printf("***************************\n");
		printf("Datos almacenados satisfactoriamente.\n");
		printf("Presione enter para continuar...\n");
		getchar();
	} else {
		printf("El archivo no existe.\n");//no existe el archivo
	}
	
}

void consultar(){
    struct carro RegistroBusqueda;
    int i = 0;//contador de tipo
    int f = 0;//contador de precio
    int q;
    FILE* archivo; //puntero al archivo
    
    do
	{
		system("cls");
		printf("BIENVENIDO AL SUBMENU DE BUSQUEDA: \n");
	    printf("1-. Buscar auto por placa.\n");
	    printf("2-. Buscar auto por tipo.\n");
	    printf("3-. Buscar auto por precio.\n");
	    printf("4-. Volver al menu principal\n");
	    printf("Su opcion: ");
	    
	    scanf("%i", &q);
	    getchar(); // Limpiar el bufer de entrada
	    
	    switch(q) {
	        case 1:
				char placa[30];
				
				printf("Escribe la placa del vehiculo para comprobar si esta en el archivo:");
				fgets(placa, sizeof(placa), stdin);
				placa[strcspn(placa, "\n")] = '\0'; // Elimina el caracter de nueva linea (\n)si esta presente
				
				archivo = fopen("vehiculos.bin", "rb");
				
				if(archivo != NULL){
					while(fread(&RegistroBusqueda, sizeof(struct carro), 1, archivo) != NULL){
						if(strcmp(placa, RegistroBusqueda.placa) == 0){
							if(RegistroBusqueda.estado == 'E'){
								printf("El vehiculo fue eliminado anteriormente.\n");
								fclose(archivo);
								break;
							}
							printf("=============================\n");
							printf("Placa: %s\n", RegistroBusqueda.placa);
							printf("Nombre: %s\n", RegistroBusqueda.nombre);
							printf("Marca: %s\n", RegistroBusqueda.marca);
							printf("Precio: %0.2f\n", RegistroBusqueda.precio);
							if(RegistroBusqueda.tipo == 'P'){
								printf("Tipo: Propio\n");
							} else if (RegistroBusqueda.estado = 'C'){
								printf("Tipo: Consignado\n");
							}
							printf("Modelo: %i\n", RegistroBusqueda.modelo);
							printf("Color: %s\n", RegistroBusqueda.color);
							printf("Año: %i\n", RegistroBusqueda.year);
							if(RegistroBusqueda.estado == 'A'){
								printf("Estado: Activo\n");
							} else if (RegistroBusqueda.estado == 'E'){
								printf("Estado: Eliminado\n");
							}
						} 
					}
					printf("***********************************\n");
					printf("Vehiculo encontrado.\n");
					printf("presione enter para continuar...");
					getchar();
					fclose(archivo);//cerrar el archivo		
				} else {
					printf("El archivo no existe.\n");
				}
				
			break;
	            
	        case 2:
	        	
	        	char a;
	            // Logica para buscar por tipo
	            printf("El tipo de vehiculo se especifica de acuerdo a:\n");
	            printf("P-. Propio.\n");
	            printf("C-. Consignado.\n");
	            printf("********************\n");
	            printf("Escriba la letra del tipo correspondiente de vehiculos a buscar:");
	            scanf("%c", &a);
	            getchar();
	            
	            while (a != 'P' && a != 'C'){//filtrar la letra
	            	printf("Digite un tipo de auto existente como se le menciono anteriormente:");
	            	scanf("%c", &a);
	            	getchar();
				}
				
				archivo = fopen("vehiculos.bin", "rb");
				if(archivo != NULL){
					while(fread(&RegistroBusqueda, sizeof(struct carro), 1, archivo) != NULL){
						if(RegistroBusqueda.estado == 'E'){
							i--;
							continue; //si el estado es eliminado no imprima nada asociado a ese registro
						}
						if(RegistroBusqueda.tipo == a){
							printf("=============================\n");
							printf("Placa: %s\n", RegistroBusqueda.placa);
							printf("Nombre: %s\n", RegistroBusqueda.nombre);
							printf("Marca: %s\n", RegistroBusqueda.marca);
							printf("Precio: %0.2f\n", RegistroBusqueda.precio);
							if(RegistroBusqueda.tipo == 'P'){
								printf("Tipo: Propio\n");
							} else if (RegistroBusqueda.estado = 'C'){
								printf("Tipo: Consignado\n");
							}
							printf("Modelo: %i\n", RegistroBusqueda.modelo);
							printf("Color: %s\n", RegistroBusqueda.color);
							printf("Año: %i\n", RegistroBusqueda.year);
							if(RegistroBusqueda.estado == 'A'){
								printf("Estado: Activo\n");
							} else if (RegistroBusqueda.estado == 'E'){
								printf("Estado: Eliminado\n");
							}
							i++;
						} 
					}
					printf("******************************\n");
					printf("REGISTROS DE TIPO ENCONTRADOS: %i\n", i);
					printf("Presione enter para continuar...");
					getchar();
					fclose(archivo);
				} else {
					printf("No se pudo abrir el archivo.\n");
				}
	    	break;
	            
	        case 3:
	            // Logica para buscar por precio
	            float sup;
	            float inf;
	            
	            printf("A continuacion se buscaran vehiculos entre el intervalo que usted elija:\n");
	            printf("Elija el precio inicial: ");
	            scanf("%f", &inf);
	            getchar();
	            
	            while(inf < 0){
	            	printf("El precio no es valido.\n");
	            	printf("Elija el precio inicial: ");
	            	scanf("%f", &inf);
	            	getchar();
				}
				
	            printf("Elija el precio limite: ");
	            scanf("%f", &sup);
	            getchar();
	            
		        while(sup <= 0){
		        	printf("El precio no es valido.\n");
		        	printf("Elija el precio limite: ");
		        	scanf("%f", &sup);
		        	getchar();
				}
				
	            printf("El intervalo que ha escogido va asi: de %0.2f hasta %0.2f\n", inf, sup);
	            
	            archivo = fopen("vehiculos.bin", "rb");
	            if(archivo != NULL){
	            	while(fread(&RegistroBusqueda, sizeof(struct carro), 1, archivo) != NULL){
	            		if(RegistroBusqueda.precio > inf && RegistroBusqueda.precio < sup){
	            			if(RegistroBusqueda.estado == 'E'){
						f--;
	            				continue;//continue a otro registro si el vehiculo esta eliminado
							}
							printf("=============================\n");
							printf("Placa: %s\n", RegistroBusqueda.placa);
							printf("Nombre: %s\n", RegistroBusqueda.nombre);
							printf("Marca: %s\n", RegistroBusqueda.marca);
							printf("Precio: %0.2f\n", RegistroBusqueda.precio);
							if(RegistroBusqueda.tipo == 'P'){
								printf("Tipo: Propio\n");
							} else if (RegistroBusqueda.estado = 'C'){
								printf("Tipo: Consignado\n");
							}
							printf("Modelo: %i\n", RegistroBusqueda.modelo);
							printf("Color: %s\n", RegistroBusqueda.color);
							printf("Año: %i\n", RegistroBusqueda.year);
							if(RegistroBusqueda.estado == 'A'){
								printf("Estado: Activo\n");
							} else if (RegistroBusqueda.estado == 'E'){
								printf("Estado: Eliminado\n");
							}
							f++;
						}
					}
					
					fclose(archivo);
					printf("***********************************\n");
					printf("La cantidad de autos que oscilan ese precio: %i\n", f);
					printf("Presione enter para continuar...");
					getchar();
				} else {
					printf("El archivo no existe.\n");
				}
	        break;
	            
	        case 4:
	        	//salir al menu principal
	        break;
	            
	        default:
	            printf("Opcion incorrecta.\n");
	        break;
	    }	
	} while (q != 4);
}

void modificar() {

    char placa[20];
    struct carro RegistrosModificados;

    printf("Inserte la placa del automovil que se modificara: ");
    scanf("%s", placa);
    getchar();

    FILE* archivo = fopen("vehiculos.bin", "rb+");
    if (archivo != NULL) {
        int encontrado = 0; // Bandera para indicar si se encontro la coincidencia
        while (fread(&RegistrosModificados, sizeof(struct carro), 1, archivo) != NULL) {
            if (strcmp(RegistrosModificados.placa, placa) == 0) {
                encontrado = 1; // Se encontro la coincidencia
                int r;
                do
                {
                	system("cls");
	                printf("ELIJA EL DATO QUE DESEA CAMBIAR:\n");
	                printf("1-. Cambiar nombre.\n");
					printf("2-. Cambiar precio.\n");
					printf("3-. Cambiar modelo.\n");
					printf("4-. Cambiar tipo.\n");
					printf("5-. Cambiar color.\n");
					printf("6-. Cambiar el año.\n");
	                printf("Su opcion: ");
	                
	                scanf("%i", &r);
	                getchar();
	                
	                switch (r) {
	                    case 1:
	                        printf("Escriba el nuevo nombre: ");
	                        scanf("%s", &RegistrosModificados.nombre);
	                        getchar();
	                        break;
	                    case 2:
	                        printf("Escriba el nuevo precio: ");
	                        scanf("%f", &RegistrosModificados.precio);
	                        getchar();
	                    
	                        while(RegistrosModificados.precio <= 0){
	                        	printf("Escriba el precio correctamente: ");
	                        	scanf("%f", &RegistrosModificados.precio);
	                        	getchar();   	
							}
							break;
	                    case 3:
	                        printf("Escriba el nuevo modelo: ");
	                        scanf("%i", &RegistrosModificados.modelo);
	                        getchar();
	                
	                        while(RegistrosModificados.modelo <= 0){
	                        	printf("Escriba el modelo correctamente: ");
	                        	scanf("%i", &RegistrosModificados.modelo);
	                        	getchar();   	
							}	                        
	                        break;
	                    case 4:
	                        printf("Escriba el nuevo tipo asi: \n");
	                        printf("P-. Propio\nC-. Consignado: ");
	                        scanf("%c", &RegistrosModificados.tipo);
	                        getchar();
	                    
	                        while(RegistrosModificados.tipo != 'P' || RegistrosModificados.tipo != 'C'){
	                        	printf("Escriba el tipo correctamente: ");
	                        	scanf("%c", &RegistrosModificados.tipo);
	                        	getchar();   	
							}	                        
	                        break;
	                    case 5:
	                        printf("Escriba el nuevo color: ");
	                        scanf("%s", &RegistrosModificados.color);
	                        getchar();
	                        break;
	                    case 6:
	                        printf("Escriba el nuevo año: ");
	                        scanf("%i", &RegistrosModificados.year);
	                        getchar();
	                        
	                        while(RegistrosModificados.year <= 0){
	                        	printf("Escriba el año correctamente: ");
	                        	scanf("%i", &RegistrosModificados.year);
	                        	getchar();   	
							}	                        
							break;
							
	                    default:
	                        printf("Opcion incorrecta.\n");
	                        break;
	                }
				} while(r != 1 && r != 2 && r != 3 && r != 4 && r != 5 && r != 6);

                fseek(archivo, (long) -sizeof(struct carro), SEEK_CUR); // Retrocede al espacio anteriormente leido para reescribirlo
                fwrite(&RegistrosModificados, sizeof(struct carro), 1, archivo);
                printf("**************************\n");
                printf("El dato ha sido reemplazado satisfactoriamente.\n");
                printf("Presione enter para continuar...");
                getchar();
                break; // Salir del bucle despues de la modificacion
            }
        }
        
        if (!encontrado) {
        	printf("*******************\n");
            printf("No se encontro ningun registro con esa placa.\n");
        }

        fclose(archivo); //cerrar el archivo
    } else {
        printf("El archivo no existe.\n");
    }
}

void eliminar(){
	struct carro RegistroEliminado;
	char placa[7];
	
	printf("Digite la placa del vehiculo a eliminar: ");
	scanf("%s", &placa);
	getchar();
	
	FILE* archivo;
	archivo = fopen("vehiculos.bin", "rb+");
	if(archivo != NULL){
		while(fread(&RegistroEliminado, sizeof(struct carro), 1, archivo) != NULL){
			if (strcmp(RegistroEliminado.placa, placa) == 0) {
				RegistroEliminado.estado = 'E';
                fseek(archivo, (long) -sizeof(struct carro), SEEK_CUR); // Retrocede al espacio anteriormente leido para reescribirlo
                fwrite(&RegistroEliminado, sizeof(struct carro), 1, archivo);
                fclose(archivo);
                printf("*************************\n");
                printf("Vehiculo eliminado satisfactoriamente.\n");
                printf("Presione enter para continuar...");
                getchar();
                break;
			} 
		}
	} else {
		fclose(archivo);
		printf("El archivo no existe.\n");
	}
}

int buscar(char placa[]){ //funcion para encontrar si esta ya una placa en el archivo
	struct carro RegistroCompatible;
	FILE* archivo;
	archivo = fopen("vehiculos.bin", "rb");
	if(archivo != NULL){
		while(fread(&RegistroCompatible, sizeof(struct carro), 1, archivo) != NULL){
			if(strcmp(RegistroCompatible.placa, placa) == 0){//si es igual devuelve 0
				fclose(archivo);
				return 1;
			} 
		}
		fclose(archivo);
	}
	return 0;
}

void consultar_estado(){
	struct carro RegistroEstado;
	char estado;
	printf("Si desea consultar los registros de los vehiculos que estan activos preione 'A' y si quiere ver vehiculos eliminados presione 'E': \n");
	estado = getchar();
	
	while(estado != 'A' && estado != 'E'){
		printf("Escriba la opcion como se le dijo anteriormente.");
		estado = getchar();
	}
	
	FILE* archivo;
	archivo = fopen("vehiculos.bin", "rb");
	if(archivo != NULL){
		while(fread(&RegistroEstado, sizeof(struct carro), 1, archivo) != NULL){
			if(RegistroEstado.estado == estado && estado == 'A'){
		          printf("=============================\n");
							printf("Placa: %s\n", RegistroEstado.placa);
							printf("Nombre: %s\n", RegistroEstado.nombre);
							printf("Marca: %s\n", RegistroEstado.marca);
							printf("Precio: %0.2f\n", RegistroEstado.precio);
							if(RegistroBusqueda.tipo == 'P'){
								printf("Tipo: Propio\n");
							} else if (RegistroEstado.estado = 'C'){
								printf("Tipo: Consignado\n");
							}
							printf("Modelo: %i\n", RegistroEstado.modelo);
							printf("Color: %s\n", RegistroEstado.color);
							printf("Año: %i\n", RegistroEstado.year);
							if(RegistroEstado.estado == 'A'){
								printf("Estado: Activo\n");
							} else if (RegistroEstado.estado == 'E'){
								printf("Estado: Eliminado\n");
							}
						} 
					
			if(RegistroEstado.estado == estado && estado == 'E'){
	          printf("=============================\n");
						printf("Placa: %s\n", RegistroEstado.placa);
						printf("Nombre: %s\n", RegistroEstado.nombre);
						printf("Marca: %s\n", RegistroEstado.marca);
						printf("Precio: %0.2f\n", RegistroEstado.precio);
						if(RegistroBusqueda.tipo == 'P'){
							printf("Tipo: Propio\n");
						} else if (RegistroEstado.estado = 'C'){
							printf("Tipo: Consignado\n");
						}
						printf("Modelo: %i\n", RegistroEstado.modelo);
						printf("Color: %s\n", RegistroEstado.color);
						printf("Año: %i\n", RegistroEstado.year);
						if(RegistroEstado.estado == 'A'){
							printf("Estado: Activo\n");
						} else if (RegistroEstado.estado == 'E'){
							printf("Estado: Eliminado\n");
						}
					} 
				}
					printf("***********************************\n");
					printf("Vehiculos encontrados.\n");
					printf("presione enter para continuar...");
					getchar();
					fclose(archivo);//cerrar el archivo		
		} else {
			printf("El archivo no existe.");
			}
}





