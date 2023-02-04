#include<stdlib.h>
#include <string.h>
#include <stdio.h>

typedef enum balancefactor { LH , EH , RH } BalanceFactor;
    typedef struct treenode {
    BalanceFactor bf; // indicador de equilíbrio AVL
    int entry; // inteiro guardado no nó
    int n_elems; // número de elementos desta árvore
    struct treeNode *left, *right;
} *Tree;



/*
3. Considere uma estrutura de dados Árvore Binária AVL de números inteiros,
alterada da seguinte forma: é guardado em cada nó o número de elementos da
árvore que tem esse nó como raíz

(i) Escreva a função de rotação à esquerda para estas árvores, que deverá
naturalmente ajustar adequadamente o valor do campo n_elems não é
necessário ajustar o valor do campo bf ):
*/

int num_elems(Tree t){

    if(t) return(1 + num_elems(t->right) + num_elems(t->left));
    return 0;
}

void give_elems(Tree t){

    if(!t) return;
    t->n_elems = num_elems(t);
    give_elems(t->right);
    give_elems(t->left);
}


Tree rotateLeft(Tree t){     // acho que dá (?)   

    Tree aux = t->right;
    t->right = aux->left;
    aux->left = t;
    t = aux;

    give_elems(t);

    return t;
}


/*
(ii) Pretende-se utilizar estas árvores para a implementação de conjuntos de
números naturais, suportando em particular uma operação de rank: dado um
inteiro x , contar o número de elementos do conjunto de valor inferior ou igual a
ele.
*/

int rank(Tree t, int x){

    if(!t) return 0;
    if(t->entry <= x){  
        if(t->left){                                // pode ser NULL 
        Tree aux = t->left;
        return(1+aux->n_elems+rank(t->right, x));   // pode haver elementos <=x a direita
        }
    return (1+rank(t->right, x));
    }
    return rank(t->left, x);                        // se não é menor à direita tambem nao vai ser
}   