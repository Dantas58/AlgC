#include<stdlib.h>
#include <string.h>
#include <stdio.h>

#define HSIZE 23
#define FREE -1
typedef struct entry {
int probeC; // -1: free
int key;
int value;
} HTable [HSIZE];

int hash (int key, int size);

/*
3. Considere as definicoes ao lado para implementar dicionarios
usando tabelas de hash com open addressing e linear probing.
Para cada entrada da tabela armazena-se ainda o numero de
probes que foram feitos na insercao dessa entrada (probeC == 0 significa que
a chave foi inserida no ́ındice correspondente ao seu hash).
Defina a funcao int update (HTable t, int key, int value)
que adiciona um novo par à tabela, e no caso de a
chave existir, actualiza a informacao correspondente.
A fun cao dever ́a preencher o campo porbeC e retornar 0 em
caso de sucesso (tabela nao cheia).
*/

int update (HTable t, int key, int value){  //pergunta estranha duvido que seja isto mas foi o que percebi do enunciado
                                            //quem me dera que fosse assim no nosso
    int chave = hash(key, HSIZE);
    int aux = chave;
    int col = 0;

    while(chave<HSIZE){
        if(t[chave].probeC == FREE){
            t[chave].probeC = col;
            t[chave].key = key;
            t[chave].value = value;
            return 0;
        }
        chave++;
        col++;
    }
    
    chave = 0;
    while(chave<aux){
        if(t[chave].probeC == FREE){
            t[chave].probeC = col;
            t[chave].key = key;
            t[chave].value = value;
            return 0;
        }
        chave++;
        col++;        
    }
    return -1;
}

/*
4. Admita que existe definida uma funcao int dijkstraSP (Grafo g, int v, int pesos[], int pais[])
que calcula os caminhos mais curtos a partir de um dado vertice. Defina uma funcao int aproxMeio (Grafo g, int o, int d) 
que calcula, caso exista, um vertice intermedio no caminho mais curto
entre o e d e que seja o mais proximo possıvel do ponto medio entre esses vertices.
A funcao devera retornar o vertice origem caso o caminho mais curto contenha apenas uma aresta.
A funcao devera retornar -1 caso nao exista caminho entre os vertices dados.
*/

// O balofo do Dijkstra ta sempre a aparecer tenho de ver isto