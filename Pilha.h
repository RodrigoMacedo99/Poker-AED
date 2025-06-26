//projeto aed - Ana Beatriz Araújo, Beatriz Mouriño, João Pedro Amorim, Levi Abreu, Rodrigo Macêdo.
#ifndef PILHA_H 
#define PILHA_H 
#include <stdio.h>
#include "model.h"
#define TAM 52

//Modelo de estrutura do tipo tp_item que armazena uma variavel do tipo tp_carta 
typedef struct {
   tp_carta c;
}tp_item;

typedef struct {
    int topo;
    tp_item item[TAM];
}tp_pilha;

void inicializa_pilha(tp_pilha *p){ 
    p->topo=-1;
}
 
int pilha_vazia(tp_pilha *p){ 
    if(p->topo == -1) return 1; 
    return 0;
}

int pilha_cheia(tp_pilha *p){
    if(p->topo == TAM-1) return 1;
    return 0;
}

int push(tp_pilha *p, tp_item e){
    if(pilha_cheia(p)==1) return 0;
    p->topo++;
    p->item[p->topo]=e; 
    return 1;
}

int pop(tp_pilha *p, tp_item *e){
    if(pilha_vazia(p)==1) return 0;
    *e=p->item[p->topo];
    p->topo--;
       return 1;
}

int top(tp_pilha *p, tp_item *e){
    if(pilha_vazia(p)==1) return 0;
    *e=p->item[p->topo];
    return 1;
}

int tamanho(tp_pilha *p){
    return p->topo+1; 
}

//Imprime a pilha do modelo carta
void imprime_pilha_carta(tp_pilha p){
    tp_item e;
    printf("\n");
    while(!pilha_vazia(&p)){
        pop(&p,&e);
        printf("[%s | %s]\n",e.c.valor, e.c.naipe);
        }
}

#endif