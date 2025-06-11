/*
* Programa lista enlazadas simples
* Santiago Enriquez Martinez
* compilador: TDM-GCC 4.9.2 X64
*/
#include <stdio.h>
#include <stdlib.h>

struct nodo
{
    int id;
    struct nodo *sig;
};

//prototipos de funciones
void AnadirNodo(struct nodo **principal);
void MostrarLista(struct nodo **principal);
void PosNodoInd(struct nodo **principal);
void InsertNodoPer(struct nodo **principal);
void EliminarPos(struct nodo **principal);
void EliminarPer(struct nodo **principal);

int main()
{
    int opcion;
    struct nodo *principal = NULL;

    do
    {
        system("cls");
        printf("MENU LISTAS\n");
        printf("1-.Insertar nodo(inicial o nuevo).\n");
        printf("2-.Insertar nodo en posicion de lista.\n");
        printf("3-.Insertar un nodo despues de una persona (id) indicada.\n");
        printf("4-.Eliminar el nodo de una posicion indicada.\n");
        printf("5-.Eliminar un nodo despues de una persona (id) indicada.\n");
        printf("6-.Mostrar el contenido de la lista.\n");
        printf("7-.Salir.\n");
        printf("Su opcion:");

        scanf("%d", &opcion);
        getchar();

        switch (opcion)
        {
        case 1:
            AnadirNodo(&principal);
            break;
        case 2:
            PosNodoInd(&principal);
            break;
        case 3:
            InsertNodoPer(&principal);
            break;
        case 4:
            EliminarPos(&principal);
            break;
        case 5:
            EliminarPer(&principal);
            break;
        case 6:
            MostrarLista(&principal);
            break;
        case 7:
            break;      
        default:
            break;
        }

    } while (opcion != 7);
    system("cls");
    return 0;
}

void MostrarLista(struct nodo **principal)
{
    // Para imprimir los valores de los nodos
    struct nodo *temp = *principal;
    if(temp == NULL)
    {
        printf("No hay una lista de datos.");
        getchar();
        return;
    }
    while (temp != NULL)
    {
        printf("ID: %d\n", temp->id);
        temp = temp->sig;
    }
    printf("Datos mostrados con exito!");
    getchar();
}

void AnadirNodo(struct nodo **principal)
{
    struct nodo *nuevo = (struct nodo*) malloc(sizeof(struct nodo));

    printf("Inserte una id: ");
    scanf("%d", &nuevo->id);
    getchar();
    nuevo->sig = NULL;//siempre pone el NULL

    if (*principal == NULL)
    {
        *principal = nuevo;
    } 
    else 
    {
        struct nodo *temp = *principal;
        while (temp->sig != NULL)
        {
            temp = temp->sig;
        }
        temp->sig = nuevo;
    }
    printf("ID agregada correctamente!");
    getchar();
}

void PosNodoInd(struct nodo **principal)
{
    struct nodo *temp = *principal;
    
    if(temp == NULL)
    {
        printf("No hay una lista de datos.");
        getchar();
        return;
    }
    
    int i = 1;
    while (temp != NULL)
    {
        printf("posicion: %d, dato: ID= %d\n", i, temp->id);
        temp = temp->sig;
        i++;
    }
    
    int pos;
    printf("De la anterior lista digite la posicion para agregar un nodo: ");
    scanf("%d", &pos);
    getchar();
    
    if (pos < 1 || pos > i) {
        printf("Posicion no valida.");
        getchar();
        return;
    }
    
    // Crear un nuevo nodo
    struct nodo *nuevo = (struct nodo*)malloc(sizeof(struct nodo));
    printf("Agregue una direccion ID:");
    scanf("%d", &nuevo->id);
    getchar();
    
    // Insertar el nuevo nodo en la posicion especificada
    if (pos == 1) {
        nuevo->sig = *principal;
        *principal = nuevo;
    } else {
        struct nodo *temp2 = *principal;
        for (int j = 1; j < pos - 1; j++) {
            temp2 = temp2->sig;
        }
        nuevo->sig = temp2->sig;
        temp2->sig = nuevo;
    }
    printf("Nodo agregado correctamente!");
}

void InsertNodoPer(struct nodo **principal)
{
    struct nodo *temp;
    temp = *principal;
    if(temp == NULL)
    {
        printf("Error: No hay una lista creada!");
        getchar();
        return;
    }

    int ID;
    int pos = 1;
    printf("Inserte el ID de la persona: ");
    scanf("%d", &ID);
    getchar();
    while(temp != NULL)
    {
        if(ID == temp->id)
        {
            break;
        }
        temp = temp->sig;
        pos++;
    }

    //agregar nueva id
    struct nodo *nuevo;
    nuevo = (struct nodo*)malloc(sizeof(struct nodo));
    struct nodo *temp2;
    temp2 = *principal;
    printf("Inserte la ID de la nueva persona: ");
    scanf("%d", &nuevo->id);
    if (pos == 1) {
        nuevo->sig = *principal;
        *principal = nuevo;
    } else {
        struct nodo *temp2 = *principal;
        for (int j = 1; j < pos; j++) {
            temp2 = temp2->sig;
        }
        nuevo->sig = temp2->sig;
        temp2->sig = nuevo;
    }
    printf("Nodo agregado correctamente!");
}

void EliminarPos(struct nodo **principal)
{
    struct nodo *temp = *principal;
    if(temp == NULL)
    {
        printf("Error: no hay una lista de datos creada!");
        getchar();
        return;
    }

    int i = 1;
    while (temp != NULL)
    {
        printf("posicion: %d, dato: ID= %d\n", i, temp->id);
        temp = temp->sig;
        i++;
    }
    
    int pos;
    printf("De la anterior lista digite la posicion para eliminar un nodo: ");
    scanf("%d", &pos);
    getchar();
    
    if (pos < 1 || pos >= i) {
        printf("Posicion no valida!");
        getchar();
        return;
    }
    
    // Borrar el nodo de posicion especificada
    struct nodo *temp2 = *principal;
    struct nodo *temp3 = NULL;
    if (pos == 1) {
        *principal = temp2->sig;
        free(temp2);
    } else {
        for (int j = 1; j < pos; j++) {
            temp3 = temp2;
            temp2 = temp2->sig; 
        }
        temp3->sig = temp2->sig;//guardo la cola
        free(temp2);  //liberar memoria del puntero   
    }
    printf("Nodo eliminado correctamente!");
    getchar();
}

void EliminarPer(struct nodo **principal) 
{
    struct nodo *temp = *principal;
    if (temp == NULL) 
    {
        printf("Error: no hay una lista de datos creada!");
        getchar();
        return;
    }

    int i = 1;
    while (temp != NULL) 
    {
        printf("posicion: %d, dato: ID= %d\n", i, temp->id);
        temp = temp->sig;
        i++;
    }
    
    int ID;
    printf("De la anterior lista digite la ID a eliminar: ");
    scanf("%d", &ID);
    getchar();
    
    // Buscar el nodo con la ID especificada
    struct nodo *temp2 = *principal;
    while (temp2 != NULL && temp2->id != ID) {
        temp2 = temp2->sig;
    }

    if (temp2 == NULL) {
        printf("No se encontro la ID especificada en la lista.");
        getchar();
        return;
    }

    // Verificar si hay un nodo después del nodo con la ID especificada
    if (temp2->sig != NULL) {
        struct nodo *temp3 = temp2->sig; // Nodo a eliminar
        temp2->sig = temp3->sig; // Saltar el nodo a eliminar
        free(temp3); // Liberar memoria del nodo eliminado
        printf("Nodo siguiente a la ID especificada eliminado correctamente.");
        getchar();
    } else {
        printf("No hay nodo siguiente a la ID especificada para eliminar.");
        getchar();
    }
}


