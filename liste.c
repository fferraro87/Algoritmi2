#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
/*
 * 
 */
struct listNode {
    char data; //informazione contenuta in ogni nodo
    struct listNode *nextPtr; //puntatore al prossimo nodo
};
typedef struct listNode ListNode; //sinonimo di struct listNode
typedef ListNode *ListNodePtr; //Sinonimo di ListNode

void insert (ListNodePtr *sPtr,char value);
char delete (ListNodePtr *sPtr,char value);
int isEmpty (ListNodePtr sPtr);
void printList (ListNodePtr currentPtr);
void instructions (void);
int main(int argc, char** argv) {
    ListNodePtr startPtr = NULL; //all'inizio la lista è vuota e non contiene nodi
    int choice; //scelta dell'utente
    char item; //carattere digitato
    instructions(); // visualizza il menu
    printf (" ? \n");
    scanf ("%d",choice);
    
    //esegue il ciclo fino a che non si preme 3
    while (choice != 3){
        switch (choice){
            case 1:
                printf ("Inserisci un carattere : \n");
                scanf ("%c",&item);
                insert (&startPtr, item); //inserisce l'elemento nella lista
                printList(startPtr);
                break;
            case 2:
                //Se la lista non è vuota
                if (!isEmpty( startPtr )){
                    printf("Inserisci un carattere da eliminare\n");
                    scanf("%c",&item);
                    //se il carattere viene trovato, viene rimosso
                    if (delete(&startPtr,item)){
                        printf ("%c cancellato\n",item);
                        printList(startPtr);
                    }//fine if
                    else{
                        printf("%c non trovato nella lista\n",item);
                    }//fine else
                }//fine if
                else{
                    printf("La lista è vuota\n");
                }//fine else
                break;
            default:
                printf("Scelta non valida\n");
                instructions();
                break;
        }//fine switch
        printf("?\n");
        scanf("%d",&choice);
    }//fine del while
    printf("Fine programma\n");
    return (EXIT_SUCCESS);
}

//visualizza le istruzioni sullo schermo
void instructions( void ){
    printf ("Inserisci il numero che vuoi da 1 a 3 :\n"
            " 1. Inserisci un elemento nella lista\n"
            " 2. Elimina un elemento dalla lista\n"
            " 3. Termina il programma\n");
}//fine instructions

//inserisce un nuovo elemento nella lista
void insert(ListNodePtr *sPtr,char value){
    ListNodePtr newPtr; //puntatore al nuovo nodo
    ListNodePtr previousPtr; //puntatore al nodo precedente
    ListNodePtr currentPtr; //puntato al nodo corrente
    newPtr = malloc(sizeof(ListNode)); //crea il nodo
    if (newPtr!=NULL){
        newPtr->data =value; //memorizza il valore nel nuovo nodo
        newPtr->nextPtr = NULL; //il nuovo nodo non è collegato a nessun altro nodo
        previousPtr = NULL;
        currentPtr = *sPtr;
        //esegue un ciclo per trovare la posizione corretta nella lista
        while (currentPtr != NULL && value > currentPtr->data){
            previousPtr = currentPtr; //passa al...
            currentPtr = currentPtr->nextPtr; //..prossimo nodo
        }// fine del while
        
        //inserisce il nuovo nodo all'inizio della lista
        if (previousPtr == NULL){
            newPtr->nextPtr = *sPtr;
            *sPtr=newPtr;
        }//fine ramo if
        else { //inserisce il nuovo nodo tra previousPtr e currentPtr
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        }//fine ramo else
    }//fine ramo if
    else {
        printf ("%c non è stato inserito\n",value);
    }//fine else
}

//Elimina un elemento dalla lista
char delete (ListNodePtr *sPtr,char value){
    ListNodePtr previousPtr; //puntatore al nodo precedente
    ListNodePtr currentPtr; //puntatore al nodo corrente
    ListNodePtr tempPtr; // puntatore a un nodo temporaneo
    
    //elimina il primo nodo
    
    if (value == (*sPtr)->data){
        tempPtr = *sPtr; //memorizza il nodo che sta per essere rimosso
        
        *sPtr = ( *sPtr )->nextPtr; //toglie il nodo
        free(tempPtr); //libera la memoria dal nodo tolto
        return value;
        
    }//fine if
    else {
        previousPtr = *sPtr;
        currentPtr = (*sPtr)->nextPtr;
        //eseguo un ciclo per trovare la posizione corretta nella lista
        while (currentPtr != NULL && currentPtr->data != value){
            previousPtr =currentPtr; //passa al ..
            currentPtr = currentPtr->nextPtr; //..prossimo nodo
        }//fine del while
        
        //elimina il nodo puntato da currentPtr
        if(currentPtr != NULL){
            tempPtr=currentPtr;
            previousPtr->nextPtr=currentPtr->nextPtr;
            free(tempPtr);
            return value;
        }//fine if
    }//fine else
    return '\0';
} //fine delete

//Se la lista è vuota restituisce 1 altrimenti 0
int isEmpty(ListNodePtr sPtr){
    return sPtr == NULL;
}//fine isEmpty

//visualizza la lista
void printList (ListNodePtr currentPtr){
    //se la lista è vuota
    if (currentPtr == NULL){
        printf ("La lista è vuota \n");
    }
    else{
        printf ("La lista è :\n");
        //finche non raggiunge la fine della lista
        while (currentPtr != NULL){
            printf("%c -->",currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }//fine del while
        printf ("NULL\n\n");
    }//fine else
}//fine printList
