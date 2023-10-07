#include"ListaP.h"
#include"ListaT.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct listaP{
    NoP *inicio;
}ListaP;

typedef struct listaT {
    NoT *inicio;
}ListaT;

typedef struct noP{
    char nome[30];
    NoP *prox;
    ListaT *ListaTermos;
} NoP;

ListaP *criar(){
    ListaP *l = (ListaP*)malloc(sizeof(ListaP));
    l->inicio = NULL;
    return l;
}

void limpar(ListaP *l){
    while (listaVazia(l)==1) removerInicio(l);
    free(l);
    l = NULL;
}

int tamanho(ListaP *l){
    if (l == NULL) return -1;
    NoP *no = l->inicio;
    int cont = 0;
    while (no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int listaVazia(ListaP *l){
    if (l == NULL) return 2;
    if (l->inicio == NULL) return 0;
    else return 1;
}

int inserir(ListaP *l, char *str){
    if (l == NULL) return 2;
    Termo it={0, 0};
    NoP *no = (NoP*)malloc(sizeof(NoP));
    strcpy(no->nome,str);
    no->ListaTermos=criarT();
    inserirNovo(no->ListaTermos, it);
    no->prox = l->inicio;
    l->inicio = no;
    return 0;
}

void mostrar(ListaP *l){
    int cont = 1;
    if(l != NULL){
        NoP *no = l->inicio;
        while(no != NULL){
            printf("%d - \"%s\": ",cont,no->nome);
            mostrarT(no->ListaTermos);
            printf("\n");
            no = no->prox;
            cont++;
        }
        printf("\n");
    }
}

int removerInicio(ListaP *l){
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    NoP *no = l->inicio;
    l->inicio = no->prox;
    free(no);
    return 0;
}

int removerFim(ListaP *l){
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    NoP *no = l->inicio, *aux=NULL;
    while(no->prox!=NULL){
        aux=no;
        no = no->prox;
    }
    if(aux==NULL) l->inicio = NULL;
    else aux->prox = NULL;
    free(no);
    return 0;
}

int removerPosicao(ListaP *l, int pos){
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    NoP *aux = NULL, *no = l->inicio;
    while(no->prox!=NULL && (pos>=0)){
        aux = no;
        no = no->prox;
        pos--;
    }
    if(aux==NULL){
        free(no);
        l->inicio = NULL;
    }else{
        aux->prox = no->prox;
        free(no);
    }
    return 0;
}

int buscarPosicao(ListaP *l, char *str){
    if (l == NULL) return -1;
    NoP *no = l->inicio;
    int p = 0;
    while (strcmp(str,no->nome)!=0){
        p++;
        no = no->prox;
    }
    return p;
}

int somarPol(ListaP *l, char *str1, char *str2, char *nome){
    if(l==NULL) return 1;
    if(listaVazia(l)==0) return 2;
    int a=buscarPosicao(l, str1), b=buscarPosicao(l, str2);
    if(a<0||b<0) return 3;
    ListaT *polr, *pol1, *pol2;
    buscarLista(l, a, &pol1);
    buscarLista(l, b, &pol2);
    somarPolT(pol1, pol2, polr);
    inserir(l, nome);
    l->inicio->ListaTermos=polr;
    return 0;   
}

int buscarLista(ListaP *l, int pos, ListaT **ret){
    if(l==NULL){
        return 1;
    }
    if(listaVazia(l)==0){
        return 2;
    }
    NoP *no=l->inicio;
    while(no->prox!=NULL&&pos>0){
        no=no->prox;
    }
    *ret=no->ListaTermos;
    return 0;
}