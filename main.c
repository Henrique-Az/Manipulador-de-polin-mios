#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"ListaP.h"
#include"ListaT.h"

int main(){
    ListaP *lista=criar();
    Termo it={0, 0};
    int opcao;
    char nome[30];
    printf("Insira o nome do polinomio: ");
    fgets(nome, 30, stdin);
    nome[strlen(nome)-1]='\0';
    inserir(lista, nome);
    while(it.exp>=0){
        printf("Insira o expoente do polinomio(insira um numero negativo para sair): ");
        scanf("%d", &it.exp);
        if(it.exp>=0){
            if(contemExp(buscarLista(lista, 0), it.exp)==0){
                printf("Esse termo ja existe, voce deseja:\n1 - Somar um valor para esse termo\n2 - Substituir esse valor\n3 - Incrementar os outros expoentes\n");
                scanf("%d", &opcao);
                switch(opcao){
                    case 1:
                        printf("Insira o valor que deve ser somado: ");
                        scanf("%f", &it.coef);
                        somarValor(buscarLista(lista, 0), it);
                        break;
                    case 2:
                        printf("Insira o coeficiente que deve ser substituido: ");
                        scanf("%f", &it.coef);
                        substituir(buscarLista(lista, 0), it);
                        break;
                    case 3:
                        printf("Insira o coeficiente que deve ser inserido: ");
                        scanf("%f", &it.coef);
                        inserirIncrementar(buscarLista(lista, 0), it);
                        break;
                    default:
                        printf("Nao foi inserido uma opcao valida");
                }
            } else{
                printf("Insira o coeficiente do polinomio: ");
                scanf("%f", &it.coef);
                inserirNovo(buscarLista(lista, 0), it);
            }
        }
    }
    mostrar(lista);
    return 0;
}