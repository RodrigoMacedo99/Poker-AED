#ifndef PILHA_H
#define PILHA_H
#include <stdio.h>
#define MAX 100

typedef int
tp_item;

typedef struct {
int topo;
tp_item item[MAX];
} tp_pilha;

//inicializa a pilha atribuindo valor -1 ao topo
void inicializaPilha(tp_pilha *p){
p->topo = -1;
}

//verifica se a pilha está vazaia. Em caso positivo retorna 1 (verdade)
//caso contrário, retorna 0 (falso)

int pilhaVazia(tp_pilha *p){
if (p->topo == -1) return 1;
return 0;
}

//verifica se a pilha está cheia . Em caso positivo retorna 1 (verdade)
//caso contrário, retorna 0 (falso)

int pilhaCheia(tp_pilha *p){
if (p->topo == MAX-1) {
return 1;
} else {
return 0;
}
}

//Tenta empilhar um elemento e caso não consiga (pilha cheia), ela retorna  0 (falha).
//Caso consiga, retorna 1 (sucesso)

int push(tp_pilha *p, tp_item e){
if (pilhaCheia(p)==1) return 0;
p->topo++;
p->item[p->topo]=e;
return 1;
}

//Tenta desempilha um elemento e caso não consiga (pilha vazia), retorna 0 (falha)
//Caso consiga, retorna 1 (sucesso)

int pop(tp_pilha *p, tp_item *e){
if (pilhaVazia(p)==1) return 0;
*e=p->item[p->topo];
p->topo--;
return 1;
}

//Tenta apresentar o elemento do topo da pilha e caso não consiga (pilha vazia), retorna 0 (falha)
//Caso consiga, retorna 1 (sucesso)

int top(tp_pilha *p, tp_item *e){
if (pilhaVazia(p)) return 0;
*e=p->item[p->topo];
return 1;
}

//desempilha todos os elementos (um por um) e imprime em tela

void imprimePilha(tp_pilha p){
tp_item e;
printf("\n");
while (!pilhaVazia(&p)){
pop(&p, &e);
printf("%d ",e);
}
}

//Retorna a quantidade de elementos empilhados

int alturaPilha(tp_pilha *p){

return p->topo+1;
}

#endif
