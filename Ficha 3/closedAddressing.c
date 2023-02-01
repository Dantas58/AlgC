#include<stdlib.h>
#include <string.h>
#include <stdio.h>

unsigned hash(char *str){
unsigned hash = 5381;
int c;
while (c = *str++)
hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
return hash;
}


#define Size 1000
typedef struct nodo {
char *chave; int ocorr;
struct nodo *prox;
} Nodo, *THash [Size];




void initEmpty (THash t){   // podia ser so t[i] = NULL ig

    int i = 0;
    for(i; i<Size; i++){
        t[i] = NULL;
        t[i]->ocorr = 0;
        t[i]->prox = NULL;
    }
}


void add (char *s, THash t){    // nao faço ideia se ta certo 

    int key = hash(s)%Size;
    if(!t[key]) return;

    while(t[key]){
        if(!strcmp(t[key]->chave, s)){t[key]->ocorr++; return;} //strcmp dá 0 se True
        else t[key] = t[key]->prox;
    }

    t[key] = malloc(sizeof(Nodo));
    t[key]->chave = strdup(s);
    t[key]->ocorr = 1;
    t[key]->prox = NULL;
}  


int lookup (char *s, THash t){

    int key = hash(s)%Size;
    if(!t[key]) return;
    Nodo *aux = t[key];

    while(aux){
        if(!strcmp(aux->chave, s)) return aux->ocorr;   
        else aux = aux->prox;
    }
}


int remove (char *s, THash t){  //confusao nao sei se funfa

    int key = hash(s)%Size;
    if(!t[key]) return -1;
    Nodo *atual = t[key];
    Nodo *ant = NULL;

    while(atual){
        if(!strcmp(atual->chave, s)){
            atual->ocorr--;
            if(atual->ocorr == 0){
                if(atual->prox && ant) ant->prox = atual->prox;
                else if(atual->prox && !ant) t[key] = atual->prox;   // caso do primeiro elemento da lista ligada ficar com 0 ocorr e ant = NULL
                else ant->prox = NULL;
            }
            return 1;
        }
        ant = atual;
        atual = atual->prox;
    }
}
