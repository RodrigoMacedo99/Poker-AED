#ifndef __MODEL_H_
#define __MODEL_H_

#include <stdio.h>
#include <stdlib.h>

//Modelo de estrutura do tipo tp_carta 
typedef struct {
    short int id_carta; //id da carta
    char valor[3];//vetor que armazena o valor da carta
    char naipe[10];//vetor que armazena o simbolo da carta
 }tp_carta;

typedef struct {
    char nome[50]; //Nome do jogador
    short int id_do_jogador; //id da peça
    int carteira;
    bool ta_jogando;
    tp_carta *mao; 
    tp_carta cartas_vencedoras[5]; 
}tp_jogador;

typedef struct {
        int id_jogador;
        int valor_combinacao;
        int kickers[5];
        int num_kickers;
        tp_carta cartas_combinacao[2]; // Armazena as cartas do par/trinca
    } AnaliseJogador;
    
typedef struct{
	int  pote;
} pote;

#endif