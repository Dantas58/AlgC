#include<stdlib.h>
#include<stdio.h>

#define Max 100
typedef struct pQueue {
int valores [Max];
int tamanho;
} PriorityQueue;




void swap (int h[], int x, int y){

    int i = h[x];
    h[x] = h[y];
    h[y] = i;
}

void bubbleUp (int i, int h[]){

    while(i!= 0 && h[(i-1)/2] > h[i]){
        swap(h, i, (i-1)/2);
        i = (i-1)/2;
    }
}

void bubbleDown (int i, int h[], int N){

    int min; 

    while(2*i+1<N){

        min = 2*i+1;
        if(h[2*i+1] > h[2*i+2] && 2*i+2<N) min = 2*i+2;

        if(h[i]>h[min]) {swap(h, i, min); i = min;}
        else return;
    }
}

//-------------------------------------------------//

void empty (PriorityQueue *q){

    q-> tamanho = 0;
}


int isEmpty (PriorityQueue *q){

    if(q->tamanho != 0) return -1;
    return 1;
}


int add (int x, PriorityQueue *q){

    if(q->tamanho == Max) return -1;

    q->valores[q->tamanho] = x;
    q->tamanho++;
    bubbleUp(q->tamanho-1, q->valores);
    
    return 0;
}


int remove (PriorityQueue *q, int *rem){


    if(q->tamanho == 0) return -1;

    rem = q->valores[0];
    q->valores[0] = q->valores[q->tamanho-1];
    bubbleDown(0, q->valores, q->tamanho-1);
    q->tamanho--;
    return 0;
}


int isHeap(int *v, int N) {                         // Descobrir indice onde min-heap deixa de ser valida
    for (int i = 0; i < N/2; i++) {                 // Só até N/2 porque o resto são folhas  
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < N && v[left] < v[i]) return i;   // Verificar primeiro esquerda porque deixa logo de ser valida se falhar
        if (right < N && v[right] < v[i]) return i;
    }
    return 0;
}


void topDown (int v[], int N){

    int index = isHeap(v, N);
    bubbleUp(index+1, v);
}


void bottomUp(int v[], int N){

    int meio = N/2-1;               // primeira folha
    while(meio>=0){                 // verificar tambem indice 0
        bubbleDown(meio, v, N);
        meio--;
    }
}


// Res do T-Bago
void ordenaHeap (int h[], int N) {

    while (N>0){                    
        swap(0,--N,h);              // Troca o primeiro elemento com o último, decrementa N e faz bubbleDown
        bubbleDown(0, h, N);        // Ao decrementar N o minimo (que esta agora na ultima posição) não é mais alterado
    }                               // Assumindo que a min-heap é válida
}                                   // T-Bago és um génio casa comigo 