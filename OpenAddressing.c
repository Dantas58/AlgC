#include<stdlib.h>


unsigned hash(char *str){
unsigned hash = 5381;
int c;
while (c = *str++)
hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
return hash;
}

#define Size 50
#define Free 0
#define Used 1
#define Del 2
typedef struct bucket {
int status; // Free | Used | Del
char *chave; int ocorr;
} THash [Size];


/*int where (char *s, THash t){

    int key = hash(s) % Size;
    int i = key+1;

    if((t[key].status == Used && strcmp(s, t[key]) == 0) || t[key].status == Free || t[key].status == Del) return key;

    for(i; i<Size; i++){
        if((t[i].status == Used && strcmp(s, t[i]) == 0) || t[i].status == Free || t[i].status == Del) return i;
    }

    i = 0;

    for(i; i<key; i++){
        if((t[i].status == Used && strcmp(s, t[i]) == 0) || t[i].status == Free || t[i].status == Del) return i;
    }

    return -1;
}

*/

int where (char *s, THash t){

    int key = hash(s) % Size;

    if(t[key].status == Used && strcmp(t[key], s) == 0 || t[key].status == Free) return key; // Ve no sitio exato

    int N = key;
    key++;

    for(key; key<Size; key++){
        if(t[key].status == Used && strcmp(t[key], s) == 0 || t[key].status == Free) return key; // Ve nas posições seguintes (colisões)
    }

    key = 0;

    for(key; key<N; key++){
        if(t[key].status == Used && strcmp(t[key], s) == 0 || t[key].status == Free) return key; // Ve nas posições anteriores (colisões)
    }

    return -1;
}


void initEmpty (THash t){

    int i = 0;
    while(i<Size){
        t[i].status = Free;
        t[i].ocorr = 0;
        i++;
    }
}

void add (char *s, THash t){

    int key = where(s, t);
    if(key == -1) return;

    if(t[key].status == Used) t[key].ocorr++;
    else{
        t[key].status = Used;
        t[key].ocorr = 1;
        t[key].chave = strdup(s);
    }
}

int lookup (char *s, THash t){

    int key = where(s, t);
    if(key == -1) return -1;
                                    // Estou a supor que é inicializada com status Free e ocorr 0 se não tinha de especificar
                                    // if(t[key].status == Used) return t[key].ocorr 
    return t[key].ocorr;            // return 0;
}


int remove (char *s, THash t){

    int key = where(s,t);
    if(key == -1) return -1;

    if(t[key].status == Used && t[key].ocorr == 1){
        t[key].ocorr = 0;
        t[key].status = Del;
        return 1;
    }

    if(t[key].status == Used){
        t[key].ocorr--;
        return 1;
    }

    return 0;
}

int remove2(char *s, THash t){  // porque sim

    int i = where(s,t);
    if(i==-1) return 0;

    if(t[i].status == Used){
        t[i].ocorr--;
        if(t[i].ocorr == 0){
            t[i].status = Del; 
        }
        return 1;
    }
    return 0;
}


int garbCollection (THash t){   // não faço ideia se funfa

    char *v[Size];
    int i = 0;
    int j = 0;
    for(j; j<Size; j++){
        if(t[j].status == Used){v[i] = t[j].chave; i++;}
    }

    initEmpty(t);
    i = 0;

    for(i; v[i] != '\0'; i++){
        add(v[i], t);
    }

    return 1;
}


typedef struct bucket {
int probC;
int status; // Free | Used | Del
char *chave; int ocorr;
} THash [Size];

void addicionar (char *s, THash t){

    int key = where(s,t);
    int i = hash(s)%Size;

    if(key == -1) return;

    if(key >= i) t[key].probC = key - i;  // Se for maior resolve key-i colisoes (Ex:. i = 5 e key = 7...a posição 5 e 6 estavam Used/Del e a 7 é a primeira Free, resolveu 2 coluisões)

    else t[key].probC = Size-i+key;       // Se for menor resolveu todas as colisoes do indice inicial ate a ultima posição + da posiçõ inicial ate a posição em que se encontra
}