/*
* NOMBRE: SANTIAGO ENRIQUEZ MARTINEZ
* TEMA: TAREA LISTA CIRCULAR
* COMPILADOR: TDM-GCC 4.9.2 x64
* FECHA: 4/6/2024
* OBJETIVO: Simule una parrilla o guía de canales de un operador de TV por cable. Imagine un menú que permita:
*-agregar canales a la parrilla (lista de canales)
*-agregar programas al canal (lista de programas de un canal)
*-consultar la información de un canal
*-eliminar un canal de la guía
*-eliminar toda la programación de un canal
*-mostrar la guía de canales
*-salir
* Y otras disposiciones.
*
*/
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ESCAPE 27
#define ENTER 13
#define ARRIBA 72
#define ABAJO 80
#define IZQUIERDA 75
#define DERECHA 77
#define LIMPIARPANTA system("cls")

struct canalprogramacion {
    char fhoraria[30];
    char nombre[25];
    int duracion;
    struct canalprogramacion *ant;
    struct canalprogramacion *sig;
};
struct nodo {
    struct nodo *ant, *sig;
    int canal;
    char nombcanal[30];
    struct canalprogramacion *listprograma;
};

void limbuffer(){
    int c;
    while(c = getchar() != '\n');
}
void menu() {
    system("color 3");
    printf("*============================================================================================================================*\n");
    printf("| ######  ######## ########  ##     ## ####  ######  ####  #######   ######     ######## ######## ##       ######## ##     ##|\n");
    printf("|##    ## ##       ##     ## ##     ##  ##  ##    ##  ##  ##     ## ##    ##       ##    ##       ##       ##       ##     ##|\n");
    printf("|##       ##       ##     ## ##     ##  ##  ##        ##  ##     ## ##             ##    ##       ##       ##       ##     ##|\n");
    printf("| ######  ######   ########  ##     ##  ##  ##        ##  ##     ##  ######        ##    ######   ##       ######   ##     ##|\n");
    printf("|      ## ##       ##   ##    ##   ##   ##  ##        ##  ##     ##       ##       ##    ##       ##       ##        ##   ## |\n");
    printf("|##    ## ##       ##    ##    ## ##    ##  ##    ##  ##  ##     ## ##    ##       ##    ##       ##       ##         ## ##  |\n");
    printf("| ######  ######## ##     ##    ###    ####  ######  ####  #######   ######        ##    ######## ######## ########    ###   |\n");
    printf("*============================================================================================================================*\n");
    printf("\n____________________________________________________MENU____________________________________________________________________\n");
    printf("                                   1-.AGREGAR UN CANAL DE TELEVISION.\n");
    printf("                                   2-.AGREGAR PROGRAMAS AL CANAL.\n");
    printf("                                   3-.CONSULTAR INFORMACION DE UN CANAL.\n");
    printf("                                   4-.ELIMINAR UN CANAL DE LA GUIA.\n");
    printf("                                   5-.ELIMINAR TODA LA PROGRAMACION DE UN CANAL.\n");
    printf("                                   6-.MOSTRAR GUIA DE CANALES.\n");
    printf("                                   7-.SALIR.\n");
    printf("                                   SU OPCION: ");
}
void programacionca(struct canalprogramacion **canal){
    struct canalprogramacion *temp = *canal;
    struct canalprogramacion *nuevo;

    nuevo = (struct canalprogramacion *) malloc(sizeof(struct canalprogramacion));

    LIMPIARPANTA;
    printf("INGRESE EL NOMBRE DEL PROGRAMA: ");
    scanf("%s", nuevo->nombre);
    limbuffer();
    printf("INGRESE DURACION DE PROGRAMA EN HORAS: ");
    scanf("%d", &nuevo->duracion);
    limbuffer();
    printf("INSERTE FRANJA HORARIA(ej. 3:00PM-4:00PM):");
    scanf("%s", nuevo->fhoraria);
    limbuffer();
    nuevo->sig = NULL;

    if(temp == NULL){
        *canal = nuevo;
        nuevo->ant = NULL;
        printf("EXITO!\n");
        getchar();
        return;
    }

    while(temp->sig != NULL){
        temp = temp->sig;
    }

    temp->sig = nuevo;
    nuevo->ant = temp;
    printf("EXITO!\n");
    getchar();
}
void eliminarprog(struct canalprogramacion **principal){
    struct canalprogramacion *borrar;

    if(*principal == NULL){
        printf("\n\nERROR: LA PROGRAMACION YA ESTA VACIA.");
        getchar();
        return;
    }

    while(*principal != NULL){
        borrar = *principal;
        *principal = (*principal)->sig;
        free(borrar);
    }

    *principal = NULL;
    printf("\n\nEXITO!: PROGRAMACION ELIMINADA CORRECTAMENTE.");
    getchar();
}

//prototipo de funciones
void consultar(struct nodo **principal);
void agregar(struct nodo **principal);
void agregarcanal(struct nodo **principal);
void eliminarcanal(struct nodo **principal);
void eliminarprogramacion(struct nodo **principal);
void solocanal(struct nodo **principal);

int main(void) {
    struct nodo *principal = NULL;
    int opcion;

    do {
        LIMPIARPANTA;
        menu();
        scanf("%d", &opcion);
        limbuffer();

        switch (opcion) {
            case 1:
                agregar(&principal);
                break;
            case 2:
                agregarcanal(&principal);
                break;
            case 3:
                solocanal(&principal);
                break;
            case 4:
                eliminarcanal(&principal);
                break;
            case 5:
                eliminarprogramacion(&principal);
                break;
            case 6:
                consultar(&principal);
                break;
            case 7:
                printf("EXITO!: MUCHAS GRACIAS, VUELVA PRONTO!");
                break;
            default:
                printf("Opción no válida. Inténtelo de nuevo.\n");
                break;
        }

    } while (opcion != 7);

    return 0;
}

void eliminarcanal(struct nodo **principal) {
    struct nodo *temp = *principal;
    struct canalprogramacion *recor;
    int tecla;

    if (temp == NULL) {
        printf("ERROR: NO HAY CANALES A MOSTRAR!");
        getchar();
        return;
    }

    while (tecla != ESCAPE) {
        LIMPIARPANTA;
        printf("=========================================================================\n\n");
        printf("USTED ESTA VIENDO CANAL: %s \n", temp->nombcanal);
        printf("NUMERO DE CANAL:  %d \n", temp->canal);
        printf("PROGRAMACION: ");
        printf("\n----------------------------------------------------------------------------\n");

        if (temp->listprograma == NULL) {
            printf("AUN NO HAY PROGRAMACION!");
        } else {
            recor = temp->listprograma;
            while (recor != NULL) {
                printf("PROGRAMA: %s\n", recor->nombre);
                printf("FRANJA HORARIA: %s\n", recor->fhoraria);
                printf("DURACION (HORAS): %d\n", recor->duracion);
                printf("****************************************\n");
                recor = recor->sig;
            }
        }

        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("---------------------------------------------------------------------------\n");
        printf("| IZQUIERDA O DERECHA-.VER CANALES. | ENTER-.BORRAR CANAL. | ESC-. SALIR. |");

        tecla = getch();

        switch (tecla) {
            case IZQUIERDA:
                temp = temp->ant; // Navega hacia el nodo anterior
                break;
            case DERECHA:
                temp = temp->sig; // Navega hacia el nodo siguiente
                break;
            case ENTER:
                if (temp->ant != temp && temp->sig != temp) { // Si temp no es el único nodo
                    temp->ant->sig = temp->sig;
                    temp->sig->ant = temp->ant;
                    struct nodo *temp_next = temp->sig;
                    free(temp);
                    temp = temp_next;
                } else { // Si solo queda un nodo
                    free(temp);
                    temp = NULL;
                    *principal = NULL;
                    tecla = ESCAPE;
                }
                printf("\n\n=================================================================\n");
                printf("\n ELIMINADO CON EXITO!");
                printf("\n====================================================================\n");
                limbuffer();
                break;
        }
    }
}

void agregar(struct nodo **principal) {
    int i;
    struct nodo *nuevo;
    struct nodo *temp;

    temp = *principal;

    nuevo = (struct nodo *) malloc(sizeof(struct nodo));

    // Agregando información
    LIMPIARPANTA;
    printf("*==========================================================* \n");
    printf("|                     AGREGAR CANAL                        | \n");
    printf("* =========================================================*  \n");
    printf(" INSERTE NOMBRE DEL CANAL: ");
    fgets(nuevo->nombcanal, sizeof(nuevo->nombcanal), stdin);
    nuevo->nombcanal[strcspn(nuevo->nombcanal, "\n")] = '\0';
    printf(" INSERTE NUMERO DE CANAL: ");
    scanf("%d", &i);
    limbuffer();
    nuevo->canal = i;
    nuevo->listprograma = NULL;//para crear la lista


    if (temp == NULL) {
        *principal = nuevo;
        nuevo->sig = nuevo;
        nuevo->ant = nuevo;
        printf("PRIMER NODO AGREGADO CORRECTAMENTE!");
        getchar();
        return;
    }

    // Buscar la posición adecuada para insertar el nuevo nodo
    while (temp->sig != *principal && nuevo->canal > temp->canal) {
        temp = temp->sig;
    }

    // Insertar el nuevo nodo en la lista
    nuevo->sig = temp->sig;
    nuevo->ant = temp;
    temp->sig->ant = nuevo;
    temp->sig = nuevo;

    // Si el nuevo nodo se inserta antes del nodo principal, actualiza el nodo principal
    if (nuevo->canal < (*principal)->canal) {
        *principal = nuevo;
    }

    printf("NODO CREADO CORRECTAMENTE");
    getchar();
}

void agregarcanal(struct nodo **principal) {//AGREGAR PROGRAMACION
    struct nodo *temp = *principal;
    struct canalprogramacion *recor;
    int tecla;

    if(temp == NULL){
        printf("ERROR: NO HAY CANALES REGISTRADOS.");
        getchar();
        return;
    }

    while(tecla != ESCAPE){
        LIMPIARPANTA;
        printf("=========================================================================\n\n");
        printf("USTED ESTA VIENDO CANAL: %s \n", temp->nombcanal);
        printf("NUMERO DE CANAL:  %d \n", temp->canal);
        printf("PROGRAMACION: ");
        printf("\n----------------------------------------------------------------------------\n");
        if(temp->listprograma == NULL){
            printf("AUN NO HAY PROGRAMACION!");
        } else{
                recor = temp->listprograma;
                while(recor != NULL){
                    printf("PROGRAMA: %s\n", recor->nombre);
                    printf("FRANJA HORARIA: %s\n", recor->fhoraria);
                    printf("DURACION (HORAS): %d\n", recor->duracion);
                    printf("****************************************\n");
                    recor = recor->sig;
                }
        }
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("---------------------------------------------------------------------------\n");
        printf("IZQUIERDA O DERECHA-. VER CANALES. | ENTER-.AGREGAR PROGRAMA AL CANAL. | ESC-. SALIR.");

        tecla = getch();

        switch(tecla){
            case IZQUIERDA:
                temp = temp->ant; // Navega hacia el nodo anterior
                break;
            case DERECHA:
                temp = temp->sig; // Navega hacia el nodo siguiente
                break;
            case ENTER:
                programacionca(&(temp->listprograma));
                break;
        }
    }
}

void consultar(struct nodo **principal){
    struct nodo *temp = *principal;
    int tecla;
    if(temp == NULL){
        printf("NO HAY CANALES A MOSTRAR!");
        getchar();
        return;
    }
    struct canalprogramacion *recor = temp->listprograma; // Inicializa recor al comienzo de la lista
    while(tecla != ESCAPE){
        LIMPIARPANTA;
        printf("=========================================================================\n\n");
        printf("USTED ESTA VIENDO CANAL: %s \n", temp->nombcanal);
        printf("NUMERO DE CANAL:  %d \n", temp->canal);
        printf("PROGRAMACION: ");
        printf("\n----------------------------------------------------------------------------\n");
        if(temp->listprograma == NULL){
            printf("AUN NO HAY PROGRAMACION!\n");
        } else {
            printf("PROGRAMA: %s\n", recor->nombre);
            printf("FRANJA HORARIA: %s\n", recor->fhoraria);
            printf("DURACION (HORAS): %d\n", recor->duracion);
            printf("****************************************\n");
        }
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("---------------------------------------------------------------------------\n");
        printf("IZQUIERDA O DERECHA-. VER CANALES.|ARRIBA O ABAJO-. VER PROGRAMACION| ESC-. SALIR.");

        tecla = getch();

        switch(tecla){
            case IZQUIERDA:
                temp = temp->ant; // Navega hacia el nodo anterior
                break;
            case DERECHA:
                temp = temp->sig; // Navega hacia el nodo siguiente
                break;
            case ARRIBA:
                if (recor != NULL && recor->ant != NULL) {
                    recor = recor->ant; // Navega hacia el programa anterior en la lista
                }
                break;
            case ABAJO:
                if (recor != NULL && recor->sig != NULL) {
                    recor = recor->sig; // Navega hacia el programa siguiente en la lista
                }
                break;
        }
    }
}


void eliminarprogramacion(struct nodo **principal){
    struct nodo *temp = *principal;
    struct canalprogramacion *recor;
    int tecla;
    if(temp == NULL){
        printf("NO HAY CANALES A MOSTRAR!");
        getchar();
        return;
    }
    while(tecla != ESCAPE){
        LIMPIARPANTA;
        printf("================================================================================================\n\n");
        printf("USTED ESTA VIENDO CANAL: %s \n", temp->nombcanal);
        printf("NUMERO DE CANAL:  %d \n", temp->canal);
        printf("PROGRAMACION: ");
        printf("\n------------------------------------------------------------------------------------------------\n");
        if(temp->listprograma == NULL){
            printf("AUN NO HAY PROGRAMACION!");
        } else{
                recor = temp->listprograma;
                while(recor != NULL){
                    printf("PROGRAMA: %s\n", recor->nombre);
                    printf("FRANJA HORARIA: %s\n", recor->fhoraria);
                    printf("DURACION (HORAS): %d\n", recor->duracion);
                    printf("****************************************\n");
                    recor = recor->sig;
                }
        }
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("---------------------------------------------------------------------------------------------------\n");
        printf("IZQUIERDA O DERECHA-. VER CANALES.| ENTER-. ELIMINAR TODA LA PROGRAMACION DEL CANAL. |ESC-. SALIR.");

        tecla = getch();

        switch(tecla){
            case IZQUIERDA:
                temp = temp->ant; // Navega hacia el nodo anterior
                break;
            case DERECHA:
                temp = temp->sig; // Navega hacia el nodo siguiente
                break;
            case ENTER:
                eliminarprog(&(temp->listprograma));
                break;
        }
    }
}

void solocanal(struct nodo **principal){
    struct nodo *temp = *principal;
    struct canalprogramacion *recor;
    int canal;
    int i = 0;

    if(temp == NULL){
        printf("ERROR: NO HAY CANALES CREADOS!");
        getchar();
        return;
    }

    LIMPIARPANTA;
    printf("*================================================\\ \n");
    printf("|                BUSCAR ENTRE CANALES             \\ \n");
    printf("*==================================================\\ \n");
    printf("ESCRIBA EL NUMERO DEL CANAL QUE DESEA CONSULTAR: ");
    scanf("%d", &canal);
    limbuffer();

    while((temp != *principal || temp == *principal) && i == 0){
        if(temp->canal == canal){
            printf("****************************************************************\n");
            printf("USTED ESTA VIENDO CANAL: %s \n", temp->nombcanal);
            printf("NUMERO DE CANAL:  %d \n", temp->canal);
            printf("PROGRAMACION: ");
            printf("\n----------------------------------------------------------------------------\n");
            if(temp->listprograma == NULL){
                printf("AUN NO HAY PROGRAMACION!");
            } else{
                recor = temp->listprograma;
                while(recor != NULL){
                    printf("PROGRAMA: %s\n", recor->nombre);
                    printf("FRANJA HORARIA: %s\n", recor->fhoraria);
                    printf("DURACION (HORAS): %d\n", recor->duracion);
                    printf("****************************************\n");
                    recor = recor->sig;
                }
            }
            printf("\n\n\n\n\n\n\n\n\n\n");
            printf("---------------------------------------------------------------------------\n");
            printf("===========================================================================\n");
            printf("EXITO!");
            i++;
            getchar();
        }
        if(temp->sig == *principal && i == 0){
            printf("ERROR: EL CANAL NO FUE ENCONTRADO");
            getchar();
            i++;
        }
        temp = temp->sig;
    }
}
