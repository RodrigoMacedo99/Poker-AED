#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
char valor[3];
char naipe[10];
}tp_carta;

typedef struct{
char nome[20];
tp_carta mao[5];
}tp_jogador;

void criarCartas(tp_carta baralho[52]){

char auxValores[][3] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
char auxNaipes[][10] = {"Ouros", "Espadas", "Copas", "Paus"};
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 13; k++){
        }
    }
}

void embaralhaCartas(tp_carta baralho[52]){

srand(time(NULL));
for (int i = 0; i < 52; i++){
        int k = rand() % 52;
        tp_carta x = baralho[i];
        baralho[i] = baralho[k];
        baralho[k] = x;
    }
}


int main(){

int fim, menu;
tp_carta baralho[52];

criarCartas(baralho);
embaralhaCartas(baralho);

while (fim == 0){
printf("\n\n\n bem vindo ao poker AED! digite a opcao desejada:\n");
printf("1 - teste (printf) \n");
printf("2 - fechar jogo\n");
scanf("%d", &menu);


if(menu == 1){
for (int i = 0; i < 52; i++)
printf(" valor: %s naipe: %s\n", baralho[i].valor, baralho[i].naipe);
}

else if (menu == 2){
fim = 1;
}

 else{
printf("\n erro! comando invalido, digite novamente \n");
    }
}

return 0;
}
