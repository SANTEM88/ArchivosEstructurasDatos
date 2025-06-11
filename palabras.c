/*
*
* Tema: Arbol ABB
* Nombre: Santiago Enriquez Martinez
* Compilador: TMD-GCC x64
* version del programa: 3.0.0
* Objetivo: Escriba un programa que permita crear un diccionario
* de palabras soportado en una estructura ABB (BST en ingles).
* Cada nodo del arbol contiene una palabra del diccionario, su significado,
* su categoría gramatical (sustantivo, verbo, adverbio, adjetivo, otro), N sinonimos.
*
* An*adidos de version (3.0.0):  
* - Se ha anadido una nueva funcion para agregar nodo teniendo en cuenta el metodo AVL en arbol binario.
* - Se ha anadido una funcion que imprime los valores en pantalla de cada nodo del arbol binario.
* - Se ha an*adido la libreria (windows.h) para implementar gotoxy
* - Se ha an*adido una nueva opcion para imprimir el arbol binario
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX 30
#define DEF 70

//******definicion de funciones funcionales
//limpiar buffer
void limpiar_buffer(){
    while(getchar() != '\n');
}
//imprimir en la consola
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//*****datos tipo struct

struct list_sinonimos{
    char sinonimo[MAX];
    struct list_sinonimos *ant, *sig;
};

struct nodo{
    char palabra[MAX];
    char definicion[DEF];
    int cate_gramatical;
    struct list_sinonimos *lista_sinonimos;
    struct nodo *der, *izq;
};

//******definicion de funciones auxiliares*******
void menu(void){
    printf("%c-------------------------%c \n", 218, 191);
    printf("|      MENU PRINCIPAL     | \n");
    printf("%c-------------------------%c \n",192, 217);
    printf("1-.Agregar palabra al diccionario.\n");
    printf("2-.Modificar elementos de una palabra.\n");
    printf("3-.Eliminar Palabra.\n");
    printf("4-.Mostrar elementos de una palabra.\n");
    printf("5-.Listado de palabras por categoria gramatical.\n");
    printf("6-.Listado de palabras por letra.\n");
    printf("7-.Listado de palabras en orden alfabetico.\n");
    printf("8-.Imprimir arbol binario.\n");
    printf("9-.Salir\n");
    printf("Su opcion: ");
}

int categoria_gramatical(){
    int opcion;
    printf("\nDigite la opcion de acuerdo al tipo de palabra: \n");
    printf("1-.Sustantivo.\n");
    printf("2-.Adjetivo.\n");
    printf("3-.Verbo.\n");
    printf("4-.Adverbio.\n");
    printf("5-.Determinante.\n");
    printf("6-.Pronombre.\n");
    printf("7-.Preposicion.\n");
    printf("8-.Conjuncion.\n");
    printf("9-.Interjeccion.\n");
    printf("Su opcion:");
    scanf("%d", &opcion);
    limpiar_buffer();

    while(opcion > 9 && opcion <= 0){
        printf("\nError!: Vuelva a ingresar una de las opciones validas!\n");
        printf("Su opcion:");
        scanf("%d", &opcion);
        limpiar_buffer();
    }

    return opcion;
}

//****funciones manipulacion de lista de sustantivos

void crear_lista_sinonimos(struct list_sinonimos **cabeza){
    struct list_sinonimos *temp = *cabeza;
    struct list_sinonimos *nuevo = (struct list_sinonimos *) malloc (sizeof(struct list_sinonimos));

    if(*cabeza == NULL){
        printf("Escriba el sinonimo:");
        fgets(nuevo->sinonimo, sizeof(nuevo->sinonimo), stdin);
        nuevo->ant = NULL;
        nuevo->sig = NULL;
        *cabeza = nuevo;
        return;
    }

    if(*cabeza != NULL){
        printf("Escriba un sinonimo: ");
        fgets(nuevo->sinonimo, sizeof(nuevo->sinonimo), stdin);
        nuevo->sig = NULL;

        while(temp->sig != NULL){
            temp = temp->sig;
        }

        nuevo->ant= temp;
        temp->sig = nuevo;
    }
}

void cambiar_un_sustantivo(struct list_sinonimos **cabeza){
    struct list_sinonimos *temp = *cabeza;
    char sustantivo_antiguo[MAX];
    char sustantivo_nuevo[MAX];

    while(temp != NULL){
        printf("Sustantivo: %s \n", temp->sinonimo);
        temp = temp->sig;
    }

    temp = *cabeza;

    printf("Escriba el sustantivo que desea cambiar:");
    fgets(sustantivo_antiguo, sizeof(sustantivo_antiguo), stdin);

    while(temp != NULL){
        if(strcmp(sustantivo_antiguo, temp->sinonimo) == 0){
          printf("Escriba el nuevo sustantivo:");
          fgets(sustantivo_nuevo, sizeof(sustantivo_nuevo), stdin);
          strcpy(temp->sinonimo, sustantivo_nuevo);
        }
        temp = temp->sig;
    }
}

void hallar_categoria_gramatical(int a){
    printf("Categoria gramaticar: ");
    switch(a){
    case 1:
        printf(" Sustantivo\n");
        break;
    case 2:
        printf(" Adjetivo.\n");
        break;
    case 3:
        printf(" Verbo.\n");
        break;
    case 4:
        printf(" Adverbio.\n");
        break;
    case 5:
        printf(" Determinante.\n");
        break;
    case 6:
        printf(" Pronombre.\n");
        break;
    case 7:
        printf(" Preposicion.\n");
        break;
    case 8:
        printf(" Conjuncion.\n");
        break;
    case 9:
        printf(" Interjeccion.\n");
        break;
    }
}

//****funciones manipulacion del arbol

void recorrido(struct nodo **recor, struct nodo **nodo_cadena){
    struct nodo *temp = *recor;
    struct nodo *cadena = *nodo_cadena;

    if(strcmp(cadena->palabra, temp->palabra) > 0){
        if(temp->der == NULL){
            temp->der = *nodo_cadena;
            return;
        }
        recorrido(&temp->der, nodo_cadena);

    } else if (strcmp(cadena->palabra, temp->palabra) < 0){
        if(temp->izq == NULL){
            temp->izq = *nodo_cadena;
            return;
        }
        recorrido(&temp->izq, nodo_cadena);

    } else if(strcmp((*nodo_cadena)->palabra, temp->palabra) == 0){
        printf("\nError! : No puede repetir palabras!\n");
        return;
    }
}

void agregar_palabra(struct nodo **raiz){
    if(*raiz == NULL){
        struct nodo *nuevo = (struct nodo *) malloc (sizeof(struct nodo));
        printf("Escriba la primera palabra que ira en el diccionario:");
        fgets(nuevo->palabra, sizeof(nuevo->palabra), stdin);

        printf("Escriba la definicion de la palabra:");
        fgets(nuevo->definicion, sizeof(nuevo->definicion), stdin);

        printf("Categoria gramatical:");
        nuevo->cate_gramatical = categoria_gramatical();

        int opcion;
        nuevo->lista_sinonimos = NULL;
        printf("Desea agregar una lista de sinonimos?:\n1-.Si.\n2-.No.\nSu opcion:");
        scanf("%d", &opcion);
        limpiar_buffer();
        if(opcion == 1){
            int n_veces;
            int contador = 0;
            printf("Digite cuantos sinonimos desea agregar?:");
            scanf("%d", &n_veces);
            limpiar_buffer();
            while(contador != n_veces){
                crear_lista_sinonimos(&nuevo->lista_sinonimos);
                ++contador;
            }
        }
        nuevo->der = NULL;
        nuevo->izq = NULL;
        *raiz = nuevo;
        return;
    }

    if(*raiz != NULL){
        struct nodo *nuevo = (struct nodo *) malloc (sizeof(struct nodo));
        printf("Escriba otra palabra que ira en el diccionario:");
        fgets(nuevo->palabra, sizeof(nuevo->palabra),stdin);

        printf("Escriba la definicion de la palabra:");
        fgets(nuevo->definicion, sizeof(nuevo->definicion), stdin);

        printf("Categoria gramatical:");
        nuevo->cate_gramatical = categoria_gramatical();

        int opcion;
        nuevo->lista_sinonimos = NULL;
        printf("Desea agregar una lista de sinonimos?\n1-.Si.\n2-.No.\nSu opcion:");
        scanf("%d", &opcion);
        limpiar_buffer();
        if(opcion == 1){
            int n_veces;
            int contador = 0;
            printf("Digite cuantos sinonimos desea agregar:");
            scanf("%d", &n_veces);
            limpiar_buffer();
            while(n_veces != contador){
                crear_lista_sinonimos(&nuevo->lista_sinonimos);
                ++contador;
            }
        }
        nuevo->izq = NULL;
        nuevo->der = NULL;
        recorrido(&(*raiz), &nuevo);
        //aqui recursividad
    }
}

void mostrar_ordenalfabetico(struct nodo *raiz){
    if (raiz != NULL){
       mostrar_ordenalfabetico(raiz->izq);
       printf("%c:", raiz->palabra[0]);
       printf("%s\n", raiz->palabra);
       mostrar_ordenalfabetico(raiz->der);
    }
}

void modificar_elementos_de_una_palabra(struct nodo **raiz){
    struct nodo *temp = *raiz;
    char buscar_palabra[MAX];
    printf("Escribe la palabra a la que deseas cambiarle sus caracteristicas:");
    fgets(buscar_palabra, sizeof(buscar_palabra), stdin);

    while(strcmp(buscar_palabra, temp->palabra) != 0){
        if(strcmp(buscar_palabra, temp->palabra) > 0){
            temp = temp->der;
        } else if (strcmp(buscar_palabra, temp->palabra) < 0){
            temp = temp->izq;
        }
    }

    int opcion;
    printf("Digita la caracteristica que deseas cambiar:\n");
    printf("1-.Definicion.\n");
    printf("2-.Categoria gramatical.\n");
    printf("3-.Lista de sinonimos.\n");

    scanf("%d", &opcion);
    limpiar_buffer();

    if(opcion == 1){
        printf("Escriba la definicion la nueva definicion de la palabra seleccionada:");
        fgets(temp->definicion, sizeof(temp->definicion), stdin);
    }

    if(opcion == 2){
        printf("Cambiando la categoria gramatical:");
        printf("---------------------------------");
        temp->cate_gramatical = categoria_gramatical();
    }

    if(opcion == 3){
        int opc;
        if(temp->lista_sinonimos == NULL){
            printf("Aun no hay una lista creada!");
            printf("Desea crear una?\n1-.Si.\n2-.No.\nSu opcion:");
            scanf("%d", &opc);
            limpiar_buffer();
            if(opc == 1){
                int n_veces;
                int contador = 0;
                printf("Digite cuantos sinonimos desea agregar:");
                scanf("%d", &n_veces);
                limpiar_buffer();
                while(n_veces != contador){
                    crear_lista_sinonimos(&temp->lista_sinonimos);
                    ++contador;
                }
            }
        } else {
            cambiar_un_sustantivo(&temp->lista_sinonimos);
        }
    }

    printf("\nExito!\n");
}

void recorrido_eliminacion(struct nodo **recor, char cadena[MAX]){
    struct nodo *temp = *recor;
    struct nodo *temp2 = NULL;
    struct nodo *temp3 = NULL;

    if(temp == NULL)
        return;

    if(strcmp(cadena, temp->palabra) > 0){
        recorrido_eliminacion(&(temp->der), cadena);
    } else if (strcmp(cadena, temp->palabra) < 0){
        recorrido_eliminacion(&(temp->izq), cadena);
    } else {
        temp2 = temp;
        if (temp->der == NULL && temp->izq == NULL){
            // Caso especial: el nodo es una hoja
            free(temp2);
            *recor = NULL; // Actualizar el puntero al nodo
            return;
        } else if (temp->der == NULL){
            // Caso especial: el nodo no tiene hijo derecho
            temp = temp->izq;
            while(temp->der != NULL){
                temp3 = temp;
                temp = temp->der;
            }
        } else {
            // Caso general
            temp = temp->der;
            while(temp->izq != NULL){
                temp3 = temp;
                temp = temp->izq;
            }
        }

        // Realizar el intercambio de datos
        strcpy(temp2->palabra,temp->palabra);
        strcpy(temp2->definicion, temp->definicion);
        temp2->cate_gramatical = temp->cate_gramatical;
        free(temp2->lista_sinonimos);
        temp2->lista_sinonimos = temp->lista_sinonimos;

        // Eliminar el nodo temporal
        if(temp3 == NULL){
            // No se movió temp
            if(temp->der == NULL)
                (*recor)->izq = NULL;
            else
                (*recor)->der = NULL;
        } else {
            // Se movió temp
            if(temp->der == NULL)
                temp3->izq = NULL;
            else
                temp3->der = NULL;
        }
        free(temp);
    }
}

void mostrar_elementos_palabra(struct nodo *raiz, char cadena[MAX]){
    struct nodo *temp = raiz;
    if(strcmp(cadena, temp->palabra) > 0){
        recorrido_eliminacion(&(temp->der), cadena);
    } else if (strcmp(cadena, temp->palabra) < 0){
        recorrido_eliminacion(&(temp->izq), cadena);
    } else {
        printf("Resultados de la busqueda:\n");
        printf("\nPalabra: %s\n", temp->palabra);
        printf("Definicion: %s\n", temp->definicion);
        hallar_categoria_gramatical(temp->cate_gramatical);
        printf("Lista de sinonimos:\n");
        struct list_sinonimos *temp_sinonimos = temp->lista_sinonimos;
        if(temp->lista_sinonimos == NULL){
            printf("\nNo se encontraron elementos!\n");
        }else {
            while(temp_sinonimos != NULL){
                printf("Sinonimo: %s\n", temp_sinonimos->sinonimo);
                temp_sinonimos = temp_sinonimos->sig;
            }
        }
    }
}

void mostrar_por_categoria(struct nodo *raiz, int op, char *tipos_de_categorias[10]){
    if(raiz != NULL){
        mostrar_por_categoria(raiz->izq, op, tipos_de_categorias);
       if(raiz->cate_gramatical == op){
            printf("Tipo:");
            printf("%s", tipos_de_categorias[op]);
            printf(" Palabra:");
            printf("%s", raiz->palabra);
       }
       mostrar_por_categoria(raiz->der, op, tipos_de_categorias);
    }
}

void mostrar_elementos_letra(struct nodo *raiz, char letra){
    struct nodo *temp = raiz;
    if(raiz != NULL){
        mostrar_elementos_letra(temp->izq, letra);
        if(letra == temp->palabra[0]){
            printf("Resultados de la busqueda:%c\n", letra);
            printf("\nPalabra: %s\n", temp->palabra);
            printf("Definicion: %s\n", temp->definicion);
            hallar_categoria_gramatical(temp->cate_gramatical);
            printf("Lista de sinonimos:\n");
            struct list_sinonimos *temp_sinonimos = temp->lista_sinonimos;

            if(temp->lista_sinonimos == NULL){
                printf("\nNo se encontraron elementos!\n");
            }else {
                while(temp_sinonimos != NULL){
                    printf("Sinonimo: %s\n", temp_sinonimos->sinonimo);
                    temp_sinonimos = temp_sinonimos->sig;
                }
            }

            printf("\n***************************************\n");

        }
        mostrar_elementos_letra(temp->der, letra);
    }
}

//****funciones nuevas arbol tipo AVL

int calcular_altura(struct nodo *raiz){
    if (raiz == NULL)
        return 0;
    int altura_izq = calcular_altura(raiz->izq);
    int altura_der = calcular_altura(raiz->der);
    return (altura_izq > altura_der ? altura_izq : altura_der) + 1;
}

void rotacion_izquierda(struct nodo **raiz) {
    struct nodo *nodo_temporal = (*raiz)->der;
    (*raiz)->der = nodo_temporal->izq;
    nodo_temporal->izq = *raiz;
    *raiz = nodo_temporal;
}

void rotacion_derecha(struct nodo **raiz) {
    struct nodo *nodo_temporal = (*raiz)->izq;
    (*raiz)->izq = nodo_temporal->der;
    nodo_temporal->der = *raiz;
    *raiz = nodo_temporal;
}

void balancear(struct nodo **raiz){
    if (*raiz == NULL) return;
    
    int altura_izquierda = calcular_altura((*raiz)->izq);
    int altura_derecha = calcular_altura((*raiz)->der);
    
    printf("Altura izquierda: %d, Altura derecha: %d\n", altura_izquierda, altura_derecha);
    
    int factor_de_equilibrio = altura_izquierda - altura_derecha;
    
    if (factor_de_equilibrio > 1) {
        // Caso izquierda
        if (calcular_altura((*raiz)->izq->izq) >= calcular_altura((*raiz)->izq->der)) {
            // Caso izquierda-izquierda
            rotacion_derecha(&(*raiz));
        } else {
            // Caso izquierda-derecha
            rotacion_izquierda(&((*raiz)->izq));
            rotacion_derecha(&(*raiz));
        }
    } else if (factor_de_equilibrio < -1) {
        // Caso derecha
        if (calcular_altura((*raiz)->der->der) >= calcular_altura((*raiz)->der->izq)) {
            // Caso derecha-derecha
            rotacion_izquierda(&(*raiz));
        } else {
            // Caso derecha-izquierda
            rotacion_derecha(&((*raiz)->der));
            rotacion_izquierda(&(*raiz));
        }
    }
}

void agregar_palabra_AVL(struct nodo **raiz){
    if(*raiz == NULL){
        struct nodo *nuevo = (struct nodo *) malloc (sizeof(struct nodo));
        printf("Escriba la primera palabra que ira en el diccionario:");
        fgets(nuevo->palabra, sizeof(nuevo->palabra), stdin);

        printf("Escriba la definicion de la palabra:");
        fgets(nuevo->definicion, sizeof(nuevo->definicion), stdin);

        printf("Categoria gramatical:");
        nuevo->cate_gramatical = categoria_gramatical();

        int opcion;
        nuevo->lista_sinonimos = NULL;
        printf("Desea agregar una lista de sinonimos?:\n1-.Si.\n2-.No.\nSu opcion:");
        scanf("%d", &opcion);
        limpiar_buffer();
        if(opcion == 1){
            int n_veces;
            int contador = 0;
            printf("Digite cuantos sinonimos desea agregar?:");
            scanf("%d", &n_veces);
            limpiar_buffer();
            while(contador != n_veces){
                crear_lista_sinonimos(&nuevo->lista_sinonimos);
                ++contador;
            }
        }
        nuevo->der = NULL;
        nuevo->izq = NULL;
        *raiz = nuevo;
        return;
    }

    if(*raiz != NULL){
        struct nodo *nuevo = (struct nodo *) malloc (sizeof(struct nodo));
        printf("Escriba otra palabra que ira en el diccionario:");
        fgets(nuevo->palabra, sizeof(nuevo->palabra),stdin);

        printf("Escriba la definicion de la palabra:");
        fgets(nuevo->definicion, sizeof(nuevo->definicion), stdin);

        printf("Categoria gramatical:");
        nuevo->cate_gramatical = categoria_gramatical();

        int opcion;
        nuevo->lista_sinonimos = NULL;
        printf("Desea agregar una lista de sinonimos?\n1-.Si.\n2-.No.\nSu opcion:");
        scanf("%d", &opcion);
        limpiar_buffer();
        if(opcion == 1){
            int n_veces;
            int contador = 0;
            printf("Digite cuantos sinonimos desea agregar:");
            scanf("%d", &n_veces);
            limpiar_buffer();
            while(n_veces != contador){
                crear_lista_sinonimos(&nuevo->lista_sinonimos);
                ++contador;
            }
        }
        nuevo->izq = NULL;
        nuevo->der = NULL;
        recorrido(&(*raiz), &(nuevo));
        balancear(&(*raiz));
    }
}

// Función para imprimir el árbol utilizando gotoxy
void imprimir_arbol(struct nodo *raiz, int x, int y, int nivel) {
    if (raiz == NULL)
        return;

    // Ajustar el desplazamiento horizontal en función de la longitud de la palabra
    int desplazamiento_horizontal = strlen(raiz->palabra) + 2;

    // Imprimir el nodo actual
    gotoxy(x, y);
    printf("%s", raiz->palabra);

    // Moverse a la izquierda
    if (raiz->izq != NULL) {
        imprimir_arbol(raiz->izq, x - desplazamiento_horizontal, y + nivel, nivel + 1);
    }

    // Moverse a la derecha
    if (raiz->der != NULL) {
        imprimir_arbol(raiz->der, x + desplazamiento_horizontal, y + nivel, nivel + 1);
    }
}


//****funcion principal

int main(void){
    int opcion;
    struct nodo *raiz = NULL;
    do{
        system("cls");
        menu();
        scanf("%d", &opcion);
        limpiar_buffer();
        switch(opcion){
        case 1:
            system("cls");
            agregar_palabra_AVL(&(raiz));
            //agregar_palabra(&raiz);
            printf("\nCreado con exito!");
            getchar();
            break;
        case 2:
            system("cls");
            if(raiz == NULL){
                printf("Error!: No ninguna palabra para modificar!");
                getchar();
            } else {
                system("cls");
                modificar_elementos_de_una_palabra(&raiz);
                printf("\nModificada con exito!");
                getchar();
            }
            break;
        case 3:
            system("cls");
            if(raiz == NULL){
                printf("Error!: No hay nada para borrar!");
                getchar();
            } else {
                system("cls");
                char cadena[MAX];
                printf("Escriba la palabra que desea eliminar:");
                fgets(cadena, sizeof(cadena), stdin);
                recorrido_eliminacion(&raiz, cadena);
                printf("\nEliminada con exito!");
                getchar();
            }
            break;
        case 4:
            system("cls");
            if(raiz == NULL){
                printf("Error!: No hay nada para mostrar!");
                getchar();
            } else {
                system("cls");
                char cadena1[MAX];
                printf("Escriba la palabra que desea buscar:");
                fgets(cadena1, sizeof(cadena1), stdin);
                mostrar_elementos_palabra(raiz, cadena1);
                getchar();
            }
            break;
        case 5:
            system("cls");
            if(raiz == NULL){
                printf("Error! : No hay nada para mostrar!");
                getchar();
            } else {
                int op;
                char *tipos_de_categorias[10] = {" ","Sustantivo","Adjetivo","Verbo","Adverbio","Determinante","Pronombre","Preposicion","Conjuncion","Interjeccion"};
                printf("Categorias gramaticales:\n");
                printf("De las siguientes categorias elija una a buscar por palabra:\n");
                printf("1-.Sustantivo.\n");
                printf("2-.Adjetivo.\n");
                printf("3-.Verbo.\n");
                printf("4-.Adverbio.\n");
                printf("5-.Determinante.\n");
                printf("6-.Pronombre.\n");
                printf("7-.Preposicion.\n");
                printf("8-.Conjuncion.\n");
                printf("9-.Interjeccion.\n");
                scanf("%d", &op);
                limpiar_buffer();
                mostrar_por_categoria(raiz, op, tipos_de_categorias);
                getchar();
            }
            break;
        case 6:
            system("cls");
            if(raiz == NULL){
                printf("Error! : No hay nada para mostrar!");
                getchar();
            } else {
                char letra;
                printf("Ingrese la letra que mostrara todos los resultados de palabras del diccionario:");
                scanf("%c", &letra);
                limpiar_buffer();
                mostrar_elementos_letra(raiz,letra);
                getchar();
            }
            break;
        case 7:
            system("cls");
            if(raiz == NULL){
                printf("\nError!: Aun no hay nada para mostrar!\n");
                getchar();
            } else {
                printf("\nLista de palabras por orden alfabetico:\n");
                mostrar_ordenalfabetico(raiz);
                getchar();
            }
            break;
        case 8:
            system("cls");
            imprimir_arbol(raiz, 100, 1, 0);
            getchar();
            break;
        case 9:
            break;
        default:
            printf("\nError!: Esa opcion no existe!\n");
            getchar();
            break;
        }
    } while(opcion != 9);

    return 0;
}
