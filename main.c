//projeto aed - Ana Beatriz Araújo, Beatriz Mouriño, João Pedro Amorim, Levi Abreu, Rodrigo Macêdo.
#include "control.h"
#include <windows.h>

// Função para exibir as regras do jogo
void regras_do_jogo() {
    printf("\n======================================== REGRAS BASICAS DO JOGO ========================================\n");
    printf("1. Cada jogador recebe 2 cartas (mao fechada).\n");
    printf("2. Voce pode escolher 'apostar' (continuar na rodada) ou 'desistir'.\n");
    printf("3. Serão abertas 5 cartas comunitarias na mesa (Flop: 3, Turn: 1, River: 1).\n");
    printf("4. Vence quem tiver a melhor combinacao de 5 cartas (suas 2 + 3 da mesa).\n\n");
    
    printf("============================= HIERARQUIA DAS COMBINACOES (da mais forte para a mais fraca) =============================\n");
    printf("1.  FULL HOUSE: Uma trinca + um par (ex: [8 Copas, 8 Espadas, 8 Ouros, 5 Paus, 5 Copas])\n");
    printf("2.  FLUSH: 5 cartas do mesmo naipe (nao em sequencia) (ex: [A Copas, 3 Copas, 7 Copas, 10 Copas, J Copas])\n");
    printf("3.  SEQUENCIA: 5 cartas em ordem numerica (naipes diferentes) (ex: [4 Copas, 5 Ouros, 6 Espadas, 7 Paus, 8 Espadas])\n");
    printf("4.  TRINCA: 3 cartas do mesmo valor (ex: [Q Espadas, Q Copas, Q Ouros, 9 Paus, 2 Espadas])\n");
    printf("5.  DOIS PARES: 2 pares de valores diferentes (ex: [K Espadas, K Ouros, 3 Copas, 3 Paus, 10 Espadas])\n");
    printf("6.  UM PAR: 2 cartas do mesmo valor (ex: [A Copas, A Espadas, 7 Ouros, 4 Paus, 2 Copas])\n"); 
    
    printf("========================================== DESEMPATE ==========================================\n");
    printf("- Em caso de combinacoes iguais, vence quem tiver as cartas mais altas.\n");
    printf("- Exemplo: Dois jogadores com 'Um Par' -> vence quem tiver o par mais alto (par de K > par de Q).\n");
    printf("- Se ainda empatar, compara-se a carta mais alta fora do par (kicker).\n");
    printf("=============================================================================================\n\n");
}

int main() {
    tp_pilha pilha_baralho;
    int qnt;
    tp_carta baralho[NUM_CARTAS];
    tp_listad *mesa = inicializa_listad();
    pote total_potes;
    ArvAVL *arvore = criarAVL();   

    criar_baralho(baralho);

    embaralhar(baralho);

    empilhar(&pilha_baralho, baralho);

    printf("\n===== BEM-VINDOS AO PATOPOKER =====\n");
    regras_do_jogo();
    printf("Insira a quantidade de jogadores: ");
    scanf("%d", &qnt);
    total_potes.pote = qnt * 1000; //referencia de total de cache
	
    tp_jogador jogadores[qnt+1];
    criar_jogadores(jogadores, qnt);
    
    system("cls");
    jogo(mesa, &pilha_baralho, jogadores, &total_potes, qnt, arvore);
    printf("\n\n\n\nAcabou o jogo!");

    return 0;
}