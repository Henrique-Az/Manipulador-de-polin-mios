#include"ListaT.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct listaT {
    NoT *inicio;
}ListaT;

typedef struct noT {
    Termo x;
    NoT *prox;
}NoT;

ListaT *criarT(){
    ListaT *l = (ListaT *)malloc(sizeof(ListaT));
    NoT *no=(NoT *)malloc(sizeof(NoT));
    no->prox=NULL;
    no->x.coef=0;
    no->x.exp=0;
    l->inicio=no;
    return l;
}

void limparT(ListaT *l){
    while(listaVaziaT(l)==1) removerInicioT(l);
    l=NULL;
}

int reinicializar(ListaT *l){
    //limpa o polinomio e o cria novamente, zerado
    if(l==NULL) return 2;
    if(listaVaziaT(l)==0) return 1;
    limparT(l);
    l = criarT();
    return 0;
}

int listaVaziaT(ListaT *l){
    if(l==NULL) return 2;
    if(l->inicio==NULL) return 0;
    else return 1;
}

int inserirNovo(ListaT *l, Termo it){
    if(l==NULL) return 2;
    NoT *no=(NoT *)malloc(sizeof(NoT));
    no->x.coef=it.coef;
    no->x.exp=it.exp;
    NoT *aux=l->inicio;
    if(it.exp>aux->x.exp){
        l->inicio=no;
        no->prox=aux;
        return 0;
    }
    while(aux->prox!=NULL&&aux->prox->x.exp>it.exp){
        aux=aux->prox;
    }
    no->prox=aux->prox;
    aux->prox=no;
    return 0;
}

int inserirIncrementar(ListaT *l, Termo it){
    if(l==NULL) return 1;
    if(listaVaziaT(l)==0) return 2;
    NoT *no=l->inicio;
    while(no->x.exp>=it.exp){
        no->x.exp++;
        if(no->prox!=NULL)
            no=no->prox;
        else break;
    }
    NoT *aux=(NoT *)malloc(sizeof(NoT));
    aux->prox=no->prox;
    no->prox=aux;
    aux->x.coef=it.coef;
    aux->x.exp=it.exp;
    return 0;
}

int somarValor(ListaT *l, Termo it){
    if(l==NULL) return 1;
    if(listaVaziaT(l)==0) return 2;
    NoT *no=l->inicio;
    while(no!=NULL){
        if(no->x.exp==it.exp){
            no->x.coef+=it.coef;
            return 0;
        }
    }
    return 1;
}

int substituir(ListaT *l, Termo it){
    if(l==NULL) return 1;
    if(listaVaziaT(l)==0) return 2;
    NoT *no=l->inicio;
    while(no!=NULL){
        if(no->x.exp==it.exp){
            no->x.coef=it.coef;
            return 0;
        }
    }
    return 1;
}

void mostrarT(ListaT *l){
    if(l != NULL){
        NoT *No = l->inicio;
        printf("P(x) = ");
	    if(No->x.coef < 0) printf("- ");
        while(No != NULL){
            printf("%.2fx^%d", mod(No->x.coef), No->x.exp);
            if(No->prox != NULL){
                if(No->prox->x.coef < 0) printf(" - ");
                else  printf(" + ");
            }
            No = No->prox;
        }
        printf("\n");
    }
}

int removerInicioT(ListaT *l){
    if(l==NULL) return 1;
    if(listaVaziaT(l)==0) return 2;
    NoT *no = l->inicio, *aux = NULL;
    while(no->prox!=NULL){
        aux = no;
        no = no->prox;
    }
    if(aux==NULL) l->inicio = NULL;
    else aux->prox = NULL;
    free(no);
    return 0;
}

int removerFimT(ListaT *l){
    if(l==NULL) return 1;
    if(listaVaziaT(l)==0) return 2;
    NoT *no = l->inicio;
    l->inicio = no->prox;
    free(no);
    return 0;
}

int removerExp(ListaT *l, int exp){
    if (l == NULL) return 2;
    if (listaVaziaT(l) == 0) return 1;
    NoT *aux = NULL, *no = l->inicio;
    while(no->x.exp>exp && no->prox!=NULL){
        aux = no;
        no = no->prox;
    }
    if(no->x.exp==exp){
        if(aux==NULL){
            free(no);
            l->inicio = NULL;
        }else{
            aux->prox = no->prox;
            free(no);
        }
        return 0;
    }
    return 3;
}

int buscarCoef(ListaT *l, int exp, int *ret){
    if(l==NULL) return 1;
    if(listaVaziaT(l)==0) return 2;
    for(NoT *no=l->inicio; no!=NULL; no=no->prox){
        if(no->x.exp==exp){
            *ret=no->x.coef;
            return 0;
        }
    }
    return 3;
}

int somarPolT(ListaT *l1, ListaT *l2, ListaT *ret){
    if(l1 == NULL || l2 == NULL) return 2;
    if(listaVaziaT(l1) == 0 || listaVaziaT(l2) == 0) return 1;
    ret = criarT();
    NoT *pol1 = l1->inicio, *pol2 = l2->inicio;
    
    while(pol1 != NULL && pol2 != NULL){
        /*adiciona no novo polinomio o maior expoente dos dois até que
        estejam no mesmo expoente*/
        if(pol2->x.exp > pol1->x.exp){ 
            inserirNovo(ret, pol2->x);
            pol2 = pol2->prox;
        }else if(pol2->x.exp < pol1->x.exp){
            inserirNovo(ret, pol1->x);
            pol1 = pol1->prox;
        }else{
            /*adiona a soma dos expoentes coincidentes em ambos os polinomios*/
            Termo temp;
            temp.exp = pol1->x.exp;
            temp.coef = pol1->x.coef + pol2->x.coef;
            inserirNovo(ret, temp);
            pol1 = pol1->prox;
            pol2 = pol2->prox;
        }
    }
    
    return 0;
}

int calcPx(ListaT *l, float x, float *ret){
    if(l==NULL) return 1;
    if(listaVaziaT(l)==0) return 2;
    *ret=0;
    NoT *no=l->inicio;
    while(no!=NULL){
        *ret+=no->x.coef*pot(no->x.exp, x);
        no=no->prox;
    }
    return 0;
}

float pot(int exp, float base){
    if(base==0) return 0;
    float res=1;
    for(;exp>0; exp--) res*=base;
    return res;
}

float mod(float x){
    if(x<0){
        return -x;
    }
    return x;
}