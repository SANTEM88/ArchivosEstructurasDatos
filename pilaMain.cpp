/**
 * 2024
 * Santiago Enriquez Martinez 
 * Pilas
*/
#include<stdlib.h>
#include<stdio.h>
struct nodo{

    int info;
    struct nodo *sig;
};
//prototipos de funciones
void agregar(struct nodo **raiz);
void imprimir(struct nodo **raiz);
void borrar(struct nodo **raiz);
void liberar(struct nodo **raiz);
int cantidad(struct nodo **raiz);

int main(void){

    int i = 0;
    int a = 0;
    int b;//aqui se insertara la cantidad de datos a agregar
    int w = 0;//contador de elementos de la pila
    struct nodo *raiz = NULL;
    /*
    * Necesitamos:
    * agregar -
    * imprimir-
    * extraer-
    * liberar-
    * cantidad-
    */
    do{
        system("cls");
        printf("MENU\n");
        printf("1-.Insertar un nodo a la pila.\n");
        printf("2-.Imprimir pila.\n");
        printf("3-.Quitar de la pila.\n");
        printf("4-.Vaciar la pila.\n");
        printf("5-.Consultar el numero de datos de la pila.\n");
        printf("6-.Salir.\n");
        printf("Su opcion: ");

        scanf("%d", &i);
        getchar();

        switch (i){

            case 1:
                printf("Escriba el numero de datos que quiere agregar a la pila: ");
                scanf("%d", &b);
                getchar();
                while (a < b){

                    agregar(&raiz);
                    a++;
                }
                a = 0;//en caso de agregar mas tarde en la misma ejecucion
                printf("Dato(s) agregado(s) correctamente!\n");
                getchar();
            break;

            case 2:
                imprimir(&raiz);
            break;

            case 3:
                borrar(&raiz);
            break;

            case 4:
                liberar(&raiz);
            break;

            case 5:
                w = cantidad(&raiz);
                printf("Hay %d datos en la pila.", w);
                getchar();
            break;

            case 6:
                //salir del bucle
            break;

            default:
            break;
        }
    } while(i != 6);

    return 0;
}
//opcion 1
void agregar(struct nodo **raiz){
    int x;
    printf("Escriba un numero que se guardara en la pila: ");
    scanf("%d", &x);
    getchar();

    struct nodo *nuevo = NULL;
    nuevo = (struct nodo *) malloc(sizeof(struct nodo));
    nuevo->info = x;

    if (*raiz == NULL){
        nuevo->sig = NULL;
        *raiz = nuevo;
    }
    else{
        nuevo->sig = *raiz;
        *raiz = nuevo;
    }
}
//opcion 2
void imprimir(struct nodo **raiz) {

    if(*raiz == NULL){
        printf("La pila esta vacia, no hay nada que imprimir.");
        getchar();
        return;
    }
    struct nodo *pila_temp = NULL;
    struct nodo *pila_temp2 = NULL;
    struct nodo *arriba = NULL;
    struct nodo *recor = NULL;
    struct nodo *borrar = NULL;

    recor = (*raiz);

    // Volteamos los elementos de la pila original en una pila temporal
    while (recor != NULL) {
        arriba = (struct nodo *) malloc(sizeof(struct nodo));//se tiene que abrir memoria puesto que si no se hace 
        if(pila_temp == NULL){                               //es imposible que se cree una pila, iteraria en un puntero. Solo habria un elemento
            arriba->info = recor->info;
            arriba->sig = NULL; // Aseguramos que el último nodo apunte a NULL
            pila_temp = arriba; 
        } else{
            arriba->info = recor->info;
            arriba->sig = pila_temp;
            pila_temp = arriba; // Movemos el puntero al nuevo tope de la pila
        } 
        borrar = recor;
        recor = recor->sig; // Avanzamos al siguiente nodo de la pila original
        free(borrar);
    } //pila guardada en pila_temp

    borrar = NULL;
    recor = NULL;
    recor = pila_temp;

    while (recor != NULL) {
        arriba = (struct nodo *) malloc(sizeof(struct nodo));
        if(pila_temp2 == NULL){                              
            arriba->info = recor->info;
            arriba->sig = NULL; // Aseguramos que el último nodo apunte a NULL
            pila_temp2 = arriba; 
        } else{
            arriba->info = recor->info;
            arriba->sig = pila_temp2;
            pila_temp2 = arriba; // Movemos el puntero al nuevo tope de la pila
        }
        borrar = recor;
        recor = recor->sig; // Avanzamos al siguiente nodo de la pila original
        free(borrar);
    } //pila guardada en pila_temp2

    recor = NULL;
    recor = pila_temp2;

    printf("cabeza_pila===========fondo_pila\n");
    while (recor != NULL){
        printf("%d ", recor->info);
        recor = recor->sig;
    }

    recor = NULL;
    borrar = NULL;


    (*raiz) = NULL;//para evitar errores.
    (*raiz) = pila_temp2; //pasa a ser la nueva pila.

    printf("\n*****************************\n");
    printf("Datos mostrados correctamente.");
    getchar();

}
// Opción 3
void borrar(struct nodo **raiz) {
    if (*raiz == NULL) {
        printf("La pila está vacía, no hay nada que eliminar.\n");
        getchar();
        return;
    }

    int posicion;
    printf("Ingrese la posición del dato que desea eliminar (empezando desde 1): ");
    scanf("%d", &posicion);
    getchar();

    if (posicion < 1) {
        printf("Posición inválida.\n");
        getchar();
        return;
    }

    struct nodo *temp = *raiz;
    struct nodo *anterior = NULL;
    int contador = 1;

    // Recorremos la pila hasta la posición deseada o hasta el final de la pila
    while (temp != NULL && contador != posicion) {
        anterior = temp;
        temp = temp->sig;
        contador++;
    }

    if (temp == NULL) {
        printf("La posición especificada está más allá del final de la pila.\n");
        getchar();
        return;
    }

    // Eliminar el nodo en la posición especificada
    if (anterior == NULL) {
        // El nodo a eliminar está en la parte superior de la pila
        *raiz = temp->sig;
    } else {
        anterior->sig = temp->sig;
    }

    free(temp);
    
    printf("Dato eliminado exitosamente de la pila.\n");
    getchar();
}
//opcion 4
void liberar(struct nodo **raiz){
    struct nodo *reco = *raiz;
    struct nodo *bor;
   	if(*raiz==NULL)
   		printf("La pila esta vacia.\n");
	else{
	    while (reco != NULL){
	        bor = reco;
	        reco = reco->sig;
	        free(bor);
	    }
		*raiz=NULL;
        printf("Datos eliminados exitosamente!");
	}
    getchar();
}
//opcion 5
int cantidad(struct nodo **raiz){

    if(*raiz == NULL){
        return 0;
    }

    int i = 0;
    struct nodo *pila_temp = NULL;
    struct nodo *pila_temp2 = NULL;
    struct nodo *arriba = NULL;
    struct nodo *recor = NULL;
    struct nodo *borrar = NULL;

    recor = (*raiz);

    // Volteamos los elementos de la pila original en una pila temporal
    while (recor != NULL) {
        arriba = (struct nodo *) malloc(sizeof(struct nodo));//se tiene que abrir memoria puesto que si no se hace 
        if(pila_temp == NULL){                               //es imposible que se cree una pila, iteraria en un puntero. Solo habria un elemento
            arriba->info = recor->info;
            arriba->sig = NULL; // Aseguramos que el último nodo apunte a NULL
            pila_temp = arriba; 
        } else{
            arriba->info = recor->info;
            arriba->sig = pila_temp;
            pila_temp = arriba; // Movemos el puntero al nuevo tope de la pila
        } 
        borrar = recor;
        recor = recor->sig; // Avanzamos al siguiente nodo de la pila original
        free(borrar);
    } //pila guardada en pila_temp

    borrar = NULL;
    recor = NULL;
    recor = pila_temp;

    while (recor != NULL) {
        arriba = (struct nodo *) malloc(sizeof(struct nodo));
        if(pila_temp2 == NULL){                              
            arriba->info = recor->info;
            arriba->sig = NULL; // Aseguramos que el último nodo apunte a NULL
            pila_temp2 = arriba; 
        } else{
            arriba->info = recor->info;
            arriba->sig = pila_temp2;
            pila_temp2 = arriba; // Movemos el puntero al nuevo tope de la pila
        }
        borrar = recor;
        recor = recor->sig; // Avanzamos al siguiente nodo de la pila original
        free(borrar);
    } //pila guardada en pila_temp2

    recor = NULL;
    recor = pila_temp2;

    while (recor != NULL){
        recor = recor->sig;
        i++;
    }

    recor = NULL;
    borrar = NULL;


    (*raiz) = NULL;//para evitar errores.
    (*raiz) = pila_temp2; //pasa a ser la nueva pila.

    return i;
}
