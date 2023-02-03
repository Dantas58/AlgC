#include<stdlib.h>
#include <string.h>
#include <stdio.h>

#define NV 20
typedef struct aresta {
int dest; int custo;
struct aresta *prox;
} *LAdj, *GrafoL [NV];


typedef int GrafoM [NV][NV];

LAdj createAresta(int c, int d){
    LAdj new = malloc(sizeof(struct aresta));
    new->dest = d;
    new->custo = c;
    new->prox = NULL;
    return new;
}

void fromMat (GrafoM in, GrafoL out){

    int i = 0;
    int j = 0;
    for(i; i<NV; i++) out[i] = createAresta(i, -1);
    
    for(i=0; i<NV; i++){
        LAdj aux = out[i];
        for(j=0; j<NV; j++){
            if(in[i][j]!=0){
                aux->prox = createAresta(j, in[i][j]);
                aux = aux->prox;
            }
        }
    }
}

void inverte (GrafoL in, GrafoL out){ // nao sei se funfa

    for(int k = 0; k<NV; k++) out/*zin*/[k] = createAresta(k, -1);

    for(int i=0; i<NV; i++){                                    // para cada nodo de out
        LAdj aux2 = out[i];                                
        for(int j = 0; j<NV; j++){                              // para cada lista ligada (aux para nao mexer na propria)
            LAdj aux = in[j];
            for(aux = aux->prox; aux; aux = aux->prox){         // percorre toas as listas ligadas (a partir de aux[j]->prox porque eventualmente ia chegar a aux[j] em que j = i)
                if(aux->dest == i){
                    
                    aux2->prox = createAresta(j, aux->custo);   // o que realmente inverte
                    aux2 = aux2->prox;
                    break;                                      // break porque so precisa de encontrar 1x
                } 
            }
        }
    }
}



int inDegree (GrafoL g){    // fé

    int max = 0;
    int cont;
    for(int i = 0; i<NV; i++){                               // para cada nodo
        cont = 0;
        for(int j = 0; j<NV; j++){                           // para cada lista ligada
            LAdj aux = g[j];
            for(aux = aux->prox; aux; aux = aux->prox){      // percorre a lsita ligada
                if(aux->dest == i){cont++; break;}           // procura se existe i e adiciona ao contador
            }
            if(cont>max) max = cont;
        }
    }
    return max;
}

int colorOK (GrafoL g, int cor[]){

    for(int i = 0; i<NV; i++){
        LAdj aux = g[i];
        for(aux = aux->prox; aux; aux = aux->prox){
            if(cor[i] == cor[aux->dest] && aux->dest != i) return -1;
        }
    }
    return 1;
}


/*int homomorfOK (GrafoL g, GrafoL h, int f[]){   // tenho o cerebro em papa sou incapaz

    for(int i = 0; i<NV; i++){
        LAdj auxg = g[i];
        LAdj auxh = h[i];
        for(auxg; auxg && auxh; auxg->prox){
            if()
        }
    }
}
*/