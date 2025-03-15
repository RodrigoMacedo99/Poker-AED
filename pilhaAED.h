#ifndef PILHA_H
#define PILHA_H
#include <stdio.h>
#define MAX 100

typedef int
	tp_item;
	
typedef struct 
{
	int topo;
	tp_item item[MAX];	
} tp_pilha;

//Função respondavel por incializar a pilha, atribuindo -1 ao topo.
void InicializaPilha(tp_pilha *p)
{
	p->topo = -1;
}

//Função responsavel por verificar se a pilha esta vazia, vendo se o valor atualmente atribuido ao topo é -1.
int PilhaVazia(tp_pilha *p)
{
	if (p->topo == -1)
	{
		return 1;
	}
	
	else
	{
		return 0;
	}
}

//Função responsavel por verificar se a pilha esta vazia, vendo se o valor atualmente atribuido ao topo é igual a MAX-1.
int PilhaCheia(tp_pilha *p)
{
	if (p->topo == MAX-1)
	{
		return 1;
	}
	
	else
	{
		return 0;
	}
}

//Função responsavel por adicionar um elemento ao topo da pilha.
int Empilhar(tp_pilha *p, tp_item e)
{
	if(PilhaCheia(p) == 1)
	{
		return 0;
	}
	
	else
	{
		p->topo++;
		p->item[p->topo] = e;
		
		return 1;
	}
}

//Função responsavel por remover um elemento do topo da pilha.
int Desempilhar(tp_pilha *p, tp_item *e)
{
	if (PilhaVazia(p) == 1)
	{
		return 0;
	}
	
	else
	{
		*e = p->item[p->topo];
		p->topo--;
		
		return 1;
	}
}

//Função responsavel por verificar o valor do elemento no topo da pilha e retornar este valor.
int VerificarTopo(tp_pilha *p, tp_item *e)
{
	if (PilhaVazia(p) == 1)
	{
		return 0;
	}
	
	else
	{
		*e = p->item[p->topo];
		
		return 1;
	}
}

//Função responsavel por imprimir os valores dos elementos da pilha.
void ImprimePilha(tp_pilha p)
{
	tp_item e;
	
	while (!PilhaVazia(&p))
	{
		Desempilhar(&p, &e);
		
		printf("%d\n", e);
	}
}


//Função responsavel por verificar em qual posição o topo atualmente se encontra.
int AlturaPilha(tp_pilha *p)
{
	return p->topo+1;
}

#endif
