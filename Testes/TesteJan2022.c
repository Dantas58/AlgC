#include<stdlib.h>
#include <string.h>
#include <stdio.h>

struct btree {
int info;
int weight;
struct btree *left, *right;
};
typedef struct btree *BTree;


// 2.

int tweight(BTree t) {
    if (!t) return 0;

    return (1+tweight(t->right)+tweight(t->left));
}

int check (BTree t){

    if(!t) return 0;

    return(t->weight == tweight(t));
}

int checkWeight(BTree t){

    if(!t) return 1;

    if(check(t)) return(checkWeight(t->right) && checkWeight(t->left));
    return 0;
}