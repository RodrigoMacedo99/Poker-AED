// Na nesta lista duplamente encadeada usamos um descritor (struct de nome tp_listad). � um dado estruturado
// que tem como objetivo melhorar a manipula��o e o acesso aos n�s da lista. Este descritor � alocado na mem�ria
//dinamicamente e possui 2 (ou 3) membros. Um ponteiro (*ini) que vai apontar para o 1o n� (tp_no) da lista, 
//outro ponteiro (*fim) que vai apontar para o �ltimo n� da lista e, opcionalmente, o tamanho da lista (tamanho)

//� importante difernciar as estruturas nesta biblioteca. Temos dois dados estruturados: a descritor e o n� da lista

#ifndef LISTADE_H
#define LISTADE_H

#include <stdio.h>
#include <stdlib.h>
#include "model.h"



// Modelo da estrutura do nó da lista, do tipo tp_carta
typedef struct tp_no_aux {   
  struct tp_no_aux *ant;  
  tp_carta info;  
  struct tp_no_aux *prox;   
} tp_no; 

//dado estruturado que representa o n� da lista
typedef struct {   
  tp_no *ini;   
  tp_no *fim;   
  int tamanho;   
}tp_listad;

//aloca-se mem�ria para o descritor (explicado no �nicio deste arquivo) e faz o seus ponteiros apontarem para o Nulo
tp_listad *inicializa_listad(){
   tp_listad *lista=(tp_listad*) malloc(sizeof(tp_listad));   
   lista->ini = NULL;   
   lista->fim = NULL;   
   lista->tamanho = 0;   
   return lista;
}

//verifica se a lista est� vazia
int listad_vazia(tp_listad *lista) {
    if (lista->ini == NULL)
        return 1;
    return 0;
}

//Aloca um n� da lista
tp_no *aloca() {
	tp_no* pt;
	pt=(tp_no*) malloc(sizeof(tp_no));
	return pt;
}

//insere a peça no fim da lista
int insere_listad_no_fim (tp_listad *lista, tp_carta e){   
  tp_no *novo;   
  novo=aloca();
  if (!novo) return 1;
  novo->info = e;  
  if ( listad_vazia(lista) ){ //Se for o primeiro elemento da lista
     novo->prox = NULL;   
     novo->ant = NULL; 
     lista->ini = lista->fim = novo;
     }  
  else {
     novo->prox = NULL;   
     novo->ant = lista->fim; 
     lista->fim->prox = novo;
     lista->fim = novo;
     }  
    lista->tamanho++;   
  return 0;   
}        

// Adicionar peça no inicio da lista 
int insere_listad_no_ini (tp_listad *lista, tp_carta e){   
  tp_no *novo;   
  novo=aloca();
  if (!novo) return 1;
  novo->info = e;  
  if ( listad_vazia(lista) ){ //Se for o primeiro elemento da lista
     novo->prox = NULL;   
     novo->ant = NULL; 
     lista->ini = lista->fim = novo;
     }  
  else {
     novo->prox = lista->ini;   
     novo->ant = NULL; 
     lista->ini->ant = novo;
     lista->ini = novo;
     }  
    lista->tamanho++;   
  return 0;   
}     

//imprime os conte�dos da lista (de frente para tr�s ou de tr�s pra frente)
void imprime_listad(tp_listad *lista, int ordem) {
	if (lista==NULL)
		printf("Lista nao inicializada\n");
	else {
     tp_no *atu;     
     switch (ordem) {
        case 1: atu = lista->ini;
                while (atu != NULL) {
                   printf("[%s:%s]",atu->info.naipe, atu->info.valor);
                   atu=atu->prox;           
                   }
                break;   
        case 2: atu = lista->fim;
                while (atu != NULL) {
                   printf("[%s:%s]",atu->info.naipe, atu->info.valor);
                   atu=atu->ant;           
                   }
                break;   
        default: printf("codigo invalido");        
     }
	}
    printf("\n");
}

//remove um elemento da lista
int remove_listad(tp_listad *lista, tp_carta e) {
  tp_no *atu;
  atu = lista->ini;
  while ((atu != NULL) && (atu->info.id_carta != e.id_carta)) {
    atu = atu->prox;
  }
  if (atu == NULL) {
    return 1; // Falha: elemento não encontrado
  }
  if (lista->ini == lista->fim) { // Se for o único elemento da lista
    lista->ini = lista->fim = NULL;
  } else {
    if (lista->ini == atu) { // Se for o primeiro elemento da lista
      lista->ini = atu->prox;
      atu->prox->ant = NULL;
    } else {
      if (lista->fim == atu) { // Se for o último nó da lista
        lista->fim = atu->ant;
        atu->ant->prox = NULL;
      } else {
        atu->prox->ant = atu->ant;
        atu->ant->prox = atu->prox;
      }
    }
  }
  free(atu);
  lista->tamanho--;
  return 0; // Sucesso: elemento removido
}

// Remover a carta com a referencia do ID delas; E retorna os valores das tp_cartas 
tp_carta remove_listad_id (tp_listad *lista, tp_carta e){   
  tp_no *atu;
  atu = lista->ini;
  tp_carta removido;
  removido.id_carta = 0;

  while ( (atu != NULL) && (atu->info.id_carta != e.id_carta) ) { 
        atu=atu->prox;}
  if ( atu == NULL) return removido;  

  removido = atu->info;

  if (lista->ini == lista->fim) { 
      lista->ini = lista->fim = NULL; }
  else {   
   if (lista->ini == atu) {  
      lista->ini = atu->prox;
      atu->prox->ant = NULL;
      }  
   else {
      if (lista->fim == atu) {
       lista->fim = atu->ant;
       atu->ant->prox = NULL;              
       }
      else {
        atu->prox->ant = atu->ant;   
        atu->ant->prox = atu->prox;
        } 
      }
     }   
   free(atu);  
  lista->tamanho--;   
  return removido;   
}

//Com base em um conte�do, retorna-se o endere�o do n� que cont�m o conte�do
tp_no * busca_listade (tp_listad *lista, tp_carta e){
  tp_no *atu;
  atu = lista->ini;
  while ( (atu != NULL) && (atu->info.id_carta != e.id_carta) ) { 
        atu=atu->prox;}
    return atu;
}        

//Retira da mem�ria todos os n�s da lista e tamb�m o descritor
tp_listad * destroi_listad (tp_listad *lista){
  tp_no *atu;
  atu = lista->ini;
  while (atu != NULL)  { 
        lista->ini = atu->prox;
        free(atu);
        atu=lista->ini;
		}
  free(lista);
  return NULL;
}

//Retorna o primeiro elemento da lista
/*tp_carta primeiro_elemento(tp_listad *lista){
  if (lista != NULL && lista->ini != NULL)
    return lista->ini->info;
}*/


#endif