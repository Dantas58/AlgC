#include<stdlib.h>
#include <string.h>
#include <stdio.h>

/*
1. Considere o problema de, dado um array v com N elementos determinar o k-esimo maior elemento
(com k < N), isto  ́e, o elemento que estaria na posi ̧c ̃ao N-k caso o array estivesse ordenado por ordem
crescente.
Uma forma de resolver este problema consiste em percorrer o array guardando numa estrutura auxiliar
apenas os k maiores elementos lidos at ́e ao momento. No final o elemento pretendido  ́e o menor dos
elementos armazenados.
Defina uma funcao int kmaior (int v[], int N, int k) que implementa o algoritmo descrito,
usando como estrutura auxiliar uma min-heap (com k elementos). Admita que existem disponıveis
as funcoes void bubbleDown (int h[], int N) (que faz o bubble down do elemento h[0] na heap h
com N elementos) e void bubbleUp (int h[], int N) (que faz o bubble up do elemento h[N-1] na
heap h).
Identifique o pior caso da solucao apresentada e diga, justificando, qual a complexidade dessa solucao
nesse caso.   
*/


void swap(int h[], int a, int b){

    int i = h[a];
    h[a] = h[b];
    h[b] = i;
}

void bubbleDown2 (int i, int h[], int N){   // nao quero a partir do h[0] quero de onde me apetecer

    int min; 

    while(2*i+1<N){

        min = 2*i+1;
        if(h[2*i+1] > h[2*i+2] && 2*i+2<N) min = 2*i+2;

        if(h[i]>h[min]) {swap(h, i, min); i = min;}
        else return;
    }
}

void toHeap(int v[], int N){

    int meio = N/2-1;               
    while(meio>=0){                 
        bubbleDown2(meio, v, N);
        meio--;
    }
}

int kmaior (int v[], int N, int k){ // meu deus o struggle foi real nao sei quem é o doente mental que faria isto
                                    // em vez de ordenar so o array
    if(k>N) return -1;

    int i = 0;
    int h[k];
    while(i<k){
        h[i] = v[i];
        i++;
    }
    toHeap(h, k);

    while(i<N){
        if(v[i]>h[0]){
            h[0] = v[i];
            bubbleDown2(0, h, k);
        }
        i++;
    }
    return h[0];
}

// melhor caso: os 5 elementos iniciais de v são os k-ésimos maiores já em forma de min-heap, nao é efetuada nenhuma troca -> O(1)

// pior caso: os 5 elementos iniciais de v são os 5 mais pequenos e a min-heap está toda trocada, a partir do elemento k todos os elementos
// de v são maiores que h[0] e estão em ordem crescente -> xd


/*
4. Dado um grafo G um caminho {v0, v1, . . . , vn} diz-se um caminho simples sse nao contiver
elementos repetidos. Defina uma funcao
int simplePath (Graph g, int v[], int k) que testa se a sequencia {v[0],v[1],...,v[k-1]}
é um caminho simples. A funcao deve verificar que se trata realmente de um caminho e que nao tem vertices repetidos.
Indique, justificando, a complexidade da solucao apresentada.
*/

#define N 50
typedef struct edge {
int dest, cost;
struct edge *next;
} * Graph [N];



int lookup(Graph g, int x){

    int i = 0;
    while(i<N){
        if(g[i]->dest == x) return i;
        i++;
    }
    return -1;
}


int simplePath (Graph g, int v[], int k){   // nao faço ideia se funfa mas gosto de acreditar que sim

    int i = 0;
    int j;
    for(i; i<k; i++){
        j = 0;
        for(j; j<k; j++){
            if(v[j]==v[i]) return -1;
        }
    }

    i=0;
    while(i+1<k){
        j = lookup(g, v[i]);
        if(j==-1) return -1;

        while(g[j]){
            if(g[j]->dest == v[i+1]) break;
            g[j] = g[j]->next;
        }
        if(!g[j]) return -1;
        i++;
    }
    return 1;
}