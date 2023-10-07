#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"ListaP.h"
#include"ListaT.h"

int main(){
    ListaP *lista=criar();
    Termo it={0, 0};
    char nome[30];
    printf("Insira o nome do polinomio: ");
    fgets(nome, 30, stdin);
    nome[strlen(nome)-1]='\0';
    inserir(lista, nome);
    while(it.exp>=0){
        printf("Insira o expoente do polinomio(insira um numero negativo para sair): ");
        scanf("%d", &it.exp);
        if(it.exp>=0){
            printf("Insira o coeficiente do polinomio: ");
            scanf("%f", &it.coef);
            inserirNovo(buscarLista(lista, 0), it);
        }
    }
    mostrar(lista);
    return 0;
}