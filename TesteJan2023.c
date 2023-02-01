#include<stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct avlnode {
    int valor; int bal;
    struct avlnode *esq, *dir;
} *AVLTree;



/*
1. Árvores AVL (5 valores)
Defina uma função AVLTree build (int a[], int N) que constrói uma
árvore AVL a partir de um array ordenado. Garanta que os factores de balanço
ficam bem preenchidos e que a função executa em tempo linear.
*/

 int depth (AVLTree t, int r){

    if(t) return depth(t->esq, r+1)+depth(t->dir, r+1);
    return r;
 }


 AVLTree build (int a[], int N){   //nao sei se funfa

    AVLTree t = NULL;   
    int meio = (N-1)/2;
    while(N>0){
        t = malloc(sizeof(AVLTree)); 
        t->valor = a[meio];
        t->esq = build(a, meio);   
        t->dir = build(a+meio+1, N-meio-1);
        t->bal = abs(depth(t->esq, 1) - depth(t->dir, 1));
    }
    return t;    
 }


/*
3. Min-heaps (5 valores)
Implemente uma função int decrease(int x, int y, int h[], int N)
que dada uma min-heap h com N elementos e um valor x que está na min-heap,
troque esse valor pelo valor y, assumindo que y < x. Analise o pior e melhor
caso da função implementada.
*/

void swap(int a, int b, int h[]){

    int i = h[a];
    h[a] = h[b];
    h[b] = i;
}
void bubbleUp(int i, int h[], int N){

    while(i>0 && h[i]<h[(i-1)/2]){
        swap(i, (i-1)/2, h);
        i=(i-1)/2;
    }
}

int lookup(int x, int h[], int N){  //usar min-heap para procura mais eficiente (nao me apetece)

    int i = 0;
    while(i<N){
        if(h[i] == x) return i;
        i++;
    }
    return -1;
}

int decrease(int x, int y, int h[], int N){ //deve funfar

    int i = lookup(x, h, N);
    if(i == -1) return -1;
    h[i] = y;

    bubbleUp(i, h, N);

    return 1;
}

// melhor caso: o y é menor que o pai de x e por isso ja esta na posição certa, nao é preciso efetuar trocas -> O(1)

// pior caso: o y é o novo mínimo da min-heap, é preciso fazer trocas até ficar na raiz da min-heap -> O(log(N))

// tenho a certeza dos casos mas nao tenho a certeza dos tempos de execução


/*
4. Grafos (5 valores)
Implemente a função int maior(int image[N][N]) que dado um bitmap com
uma imagem de dimensão N por N, devolva o tamanho da maior figura (pixeis
contíguos horizontal ou verticalmente) nela contida. Por exemplo, no seguinte
bitmap a maior figura tem tamanho 7. Pode assumir que os píxeis a 1 nunca têm
coordenadas 0 ou N-1.

{{0,0,0,0,0,0},
{0,1,0,1,1,0},
{0,1,1,1,0,0},
{0,1,0,0,1,0},
{0,0,1,1,1,0},
{0,0,0,0,0,0}}

*/

// xd nao