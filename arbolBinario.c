/*
*
* Nombre: Santiago Enriquez Martinez
* Codigo: 1010105344
* Tema: Arboles binarios
* compilador: TDM-GCC x64
* Fecha: 4/21/2024
*
*/

#include <stdio.h>
#include <stdlib.h>

struct nodo {
    int info;
    struct nodo *izq;
    struct nodo *der;
};
//******************************************************************* ZONA DE FUNCIONES AUXILIARES
void limpiarbuffer(){
    while(getchar() != '\n');
}

void menu1(){
    printf("*****MENU******\n");
    printf("1-.Agregar un nodo al arbol binario.\n");
    printf("2-.Mostrar arbol binario inorden.\n");
    printf("3-.Salir\n");
    printf("Su opcion:");
}

//*************************** FUNCIONES*****************

//agregar nodos
void agregar(struct nodo **raiz){
    system("cls");
    struct nodo *temp = *raiz;
    //caso en el que no hay una raiz
    if(temp == NULL){
        printf("Aun no hay una raiz, desea agregar una?\n1-.Si\n2-.No\n");
        int a;
        scanf("%d", &a);
        limpiarbuffer();
        if(a != 1){return;}
        struct nodo *nuevo = (struct nodo *) malloc(sizeof(struct nodo));
        nuevo->izq = NULL;
        nuevo->der = NULL;
        printf("Inserte el numero que ira en este nodo:");
        scanf("%d", &nuevo->info);
        limpiarbuffer();
        *raiz = nuevo;
    }

    //caso si ya hay una raiz
    if(temp != NULL){
        if(temp->izq == NULL && temp->der == NULL){
            printf("Ambos lados estan vacios\nA que lado desea agregar el nodo?\n1-.Izquierda\n2-.Derecha\n");
            int b;
            scanf("%d", &b);
            limpiarbuffer();
            //agregar nodo hacia la izquierda
            if(b == 1){
                struct nodo *nuevo = (struct nodo*) malloc(sizeof(struct nodo));
                nuevo->izq = NULL;
                nuevo->der = NULL;
                printf("Ingrese el numero que habra en este nodo:");
                scanf("%d", &nuevo->info);
                limpiarbuffer();
                temp->izq = nuevo;
                //agregar nodo hacia la derecha
            } else if(b == 2) {
                struct nodo *nuevo = (struct nodo *) malloc(sizeof(struct nodo));
                nuevo->izq = NULL;
                nuevo->der = NULL;
                printf("Ingrese el numero que habra en este nodo:");
                scanf("%d", &nuevo->info);
                limpiarbuffer();
                temp->der = nuevo;
            }

            return;
        }
        //si izquierda esta lleno
        if(temp->izq != NULL && temp->der == NULL){
            printf("Solo esta disponible el lado derecho.\n1-.desea insertar en ese lado\n2-.desea seguir por rama izquierda\n");
            int c;
            scanf("%d", &c);
            limpiarbuffer();
            if(c == 1){
                struct nodo *nuevo = (struct nodo *) malloc(sizeof(struct nodo));
                nuevo->izq = NULL;
                nuevo->der = NULL;
                printf("Ingrese el numero que habra en este nodo:");
                scanf("%d", &nuevo->info);
                limpiarbuffer();
                temp->der = nuevo;
            } else if(c == 2){
                agregar(&temp->izq);
            }
            return;
        }
        //si derecha esta lleno
        if(temp->izq == NULL && temp->der != NULL){
            printf("Solo el lado izquierdo esta disponible.\n1-.desea insertar en ese lado\n2-.desea seguir por rama derecha\n");
            int d;
            scanf("%d", &d);
            limpiarbuffer();
            if(d == 1){
                struct nodo *nuevo = (struct nodo *) malloc(sizeof(struct nodo));
                nuevo->izq = NULL;
                nuevo->der = NULL;
                printf("Inserte el numero que habra en este nodo:");
                scanf("%d", &nuevo->info);
                limpiarbuffer();
                temp->izq = nuevo;
            } else if(d == 2){
                agregar(&temp->der);
            }
            return;
        }

        //si ambos estan llenos: moverse
        if(temp->izq != NULL && temp->der != NULL){
            printf("Ambos estan llenos!\n1-.Desea moverse por la izquierda de nodo\n2-.Desea moverse a la derecha del nodo\n");
            int e;
            scanf("%d", &e);
            limpiarbuffer();
            if(e == 1){
                agregar(&temp->izq);
            } else if(e == 2){
                agregar(&temp->der);
            }
        }
    }

}

//imprimir inOrden
void mostrar(struct nodo *raiz){
    struct nodo *p = raiz;
    if(p != NULL){
       mostrar(p->izq);
       printf("%d->", p->info);
       mostrar(p->der);
    }
}

//********FUNCION PRINCIPAL*******
int main(void){
    struct nodo *raiz = NULL;
    int opcion;
    do{
        system("cls");
        menu1();
        scanf("%d", &opcion);
        limpiarbuffer();

        switch(opcion){
        case 1:
            agregar(&raiz);
            break;
        case 2:
            if(raiz == NULL){
                printf("No se ha creado un arbol aun!");
                getchar();
            } else {
                mostrar(raiz);
                printf("\n");
                printf("Mostrado correctamente!");
                getchar();
            }
            break;
        case 3:
            //salir
            break;
        default:
            printf("Numero incorrecto o error, vuelva a intentarlo!");
            getchar();
            break;
        }
    } while(opcion != 3);

    return 0;
}
