/*
* Nombre: Santiago Enriquez Martinez
* Tema: Listas dobles, segunda tarea
* Compilador: TDM-GCC 4.9.2 x64
* Objetivo: Construya un programa que use una lista doblemente enlazada
* para gestionar una base de datos de contactos.
* cada contacto se tiene: Nombre, Apellido, teléfono, whatsapp, email, estado (por defecto Activo, otro estado: Borrado).
*/
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#define ESCAPE 27
#define ENTER 13
#define ARRIBA 72
#define ABAJO 80
#define IZQUIERDA 75
#define DERECHA 77

struct nodo
{
    struct nodo *ant, *sig;
    char nombre[30], apellido[30], email[40], estado;
    long long int telefono, whatsapp;

};

void agregar(struct nodo **principal);
void mostrar(struct nodo **principal);
void modificar(struct nodo **principal);

void limpiarbuffer()
{
    while(getchar() != '\n');
}
void micromodificar(struct nodo **temp)
{
    char email[30];
    long int x, telefono, whatsapp;

    printf("__MENU MODIFICAR__\n");
    printf("1-.Modificar Email.\n");
    printf("2-.Modificar Whatsapp.\n");
    printf("3-.Modificar telefono.\n");
    printf("4-.Salir");
    printf("Su opcion: ");
    scanf("%d", &x);
    limpiarbuffer();

    switch(x)
    {
    case 1:
        printf("Escriba el nuevo email: ");
        scanf("%s", &email);
        limpiarbuffer();

        strcpy((*temp)->email, email);
        break;
    case 2:
        printf("Escriba el nuevo whatsapp: ");
        scanf("%lld", &whatsapp);
        limpiarbuffer();

        (*temp)->whatsapp = whatsapp;
        break;
    case 3:
        printf("Escriba el nuevo telefono: ");
        scanf("%lld", &telefono);
        limpiarbuffer();

        (*temp)->telefono = telefono;

        break;
    case 4:
        break;
    }
}

void menu()
{
    system("cls");
    printf("__MENU__\n");
    printf("1-.Agregar un contacto.\n");
    printf("2-.Consultar la lista.\n");
    printf("3-.Modificar datos de la lista.\n");
    printf("4-.Salir.\n");
    printf("Su opcion: ");
}

int main(void)
{
    struct nodo *principal = NULL;
    int x;

    do
    {
        menu();
        scanf("%d", &x);
        limpiarbuffer();

        switch(x)
        {
        case 1:
            agregar(&principal);
            break;
        case 2:
            mostrar(&principal);
            break;
        case 3:
            modificar(&principal);
            break;
        case 4:
            break;
        default:
            break;
        }
    } while(x != 4);

    return 0;
}

void agregar(struct nodo **principal) {
    system("cls");
    struct nodo *nuevo = (struct nodo *)malloc(sizeof(struct nodo));

    printf("__INGRESAR DATOS__\n");

    printf("Ingrese el nombre: ");
    fgets(nuevo->nombre, sizeof(nuevo->nombre), stdin);
    nuevo->nombre[strcspn(nuevo->nombre, "\n")] = '\0';

    printf("Ingrese apellido: ");
    fgets(nuevo->apellido, sizeof(nuevo->apellido), stdin);
    nuevo->apellido[strcspn(nuevo->apellido, "\n")] = '\0';

    printf("Ingrese Email: ");
    fgets(nuevo->email, sizeof(nuevo->email), stdin);
    nuevo->email[strcspn(nuevo->email, "\n")] = '\0';

    nuevo->estado = 'A'; //estado activo

    printf("Inserte el telefono: ");
    scanf("%lld", &nuevo->telefono);
    limpiarbuffer();

    printf("Inserte el whatsapp: ");
    scanf("%lld", &nuevo->whatsapp);
    limpiarbuffer();

    nuevo->sig = NULL;
    nuevo->ant = NULL;

    if (*principal == NULL) {
        *principal = nuevo;
    } else {
        struct nodo *actual = *principal, *anterior = NULL;
        while (actual != NULL && strcmp(actual->apellido, nuevo->apellido) < 0) {
            anterior = actual;
            actual = actual->sig;
        }

        if (anterior == NULL) { // Insertar al principio
            nuevo->sig = *principal;
            (*principal)->ant = nuevo;
            *principal = nuevo;
        } else if (actual == NULL) { // Insertar al final
            anterior->sig = nuevo;
            nuevo->ant = anterior;
        } else { // Insertar en medio
            nuevo->sig = actual;
            nuevo->ant = anterior;
            anterior->sig = nuevo;
            actual->ant = nuevo;
        }
    }

    printf("Nodo creado correctamente!\n");
    getchar();
}

void mostrar(struct nodo **principal) {
    system("cls");
    if (*principal == NULL) {
        printf("Error: la lista esta vacia!\n");
        _getch(); // Espera por una tecla
        return;
    }

    printf("Presione IZQUIERDA o DERECHA para desplazarse por la lista\n|para ELIMINAR o RESTAURAR a una persona presione ENTER|\ny para salir presione ESCAPE.|\n");
    printf("**********************************\n");
    printf("Presione enter para continuar...");
    getchar();
    struct nodo *temp = *principal;

    int tecla;
    do {
        system("cls");
        if (temp->estado == 'E')
        {
            printf("El contacto aqui fue eliminado para reestablecerlo presione ENTER.");

        } else if (temp->estado == 'A')
        {
            printf("*************PERSONA*****************\n");
            printf("Nombre: %s\n", temp->nombre);
            printf("Apellido: %s\n", temp->apellido);
            printf("Email: %s\n", temp->email);
            if (temp->estado == 'A') printf("Estado: activo\n");
            printf("Telefono: %lld\n", temp->telefono);
            printf("Whatsapp: %lld\n", temp->whatsapp);
            printf("************************************\n");
        }

        tecla = _getch(); // Captura la tecla presionada sin necesidad de presionar enter
        switch (tecla)
        {
            case ARRIBA:
            case IZQUIERDA: // Asumiendo c�digo correcto para la flecha izquierda
                if (temp->ant != NULL)
                {
                    temp = temp->ant; // Navega hacia el nodo anterior
                }
                break;
            case ABAJO:
            case DERECHA: // Asumiendo c�digo correcto para la flecha derecha
                if (temp->sig != NULL)
                {
                    temp = temp->sig; // Navega hacia el nodo siguiente
                }
                break;
            case ENTER:
                if (temp->estado == 'A')
                {
                    printf("\nDesea realmente eliminar? (S/N)\n");
                    if (_getch() == 's' || _getch() == 'S')
                    {
                        temp->estado = 'E';
                        printf("\nEl contacto fue eliminado satisfactoriamente,presione enter para continuar\n");
                        getchar();
                        return;
                    }
                } else if (temp->estado == 'E') {
                    printf("\nDesea reestablecer este contacto? (S/N)\n");
                    if (_getch() == 's' || _getch() == 'S')
                    {
                        temp->estado = 'A';
                        printf("\nEl contacto fue reestablecido satisfactoriamente, presione enter para continuar\n");
                        getchar();
                        return;
                    }
                }
                break;
        }
    } while (tecla != ESCAPE);
}

void modificar(struct nodo **principal)
{
    struct nodo *temp = NULL;
    temp = *principal;

    if(temp == NULL)
    {
        printf("Error: No hay una lista creada!");
        getchar();
        return;
    }

    char nombre[40];

    printf("Escriba el nombre o apellido de la persona a modificar: ");
    scanf("%s", &nombre);
    limpiarbuffer();

    while(temp != NULL)
    {
        if(strcmp(temp->nombre, nombre) == 0 || strcmp(temp->apellido, nombre) == 0 )
        {
            micromodificar(&temp);
            printf("Dato modificado correctamente!");
            getchar();
            return;
        }
        temp = temp->sig;
    }
    printf("No se encontro el contacto.");
    getchar();
}
