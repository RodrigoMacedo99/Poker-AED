#ifndef __CONTROL_H__
#define __CONTROL_H__

#include <stdbool.h>  
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pilha.h"
#include "lista_de.h"
#include "ArvoreAVL.h"
#define NUM_CARTAS 52
#define NUM_NAIPES 4
#define NUM_VALORES 13

/// --- Funções Auxiliares (Base) ---
int comparar_cartas(const void *a, const void *b);
int valor_para_numero(const char *valor);
int naipe_para_numero(const char *naipe);
void contar_valores(tp_carta cartas[], int total, int contagem[], tp_carta cartas_por_valor[][4]);

// Funções de verificação de combinações
int tem_um_par(tp_carta cartas[], int total, tp_carta cartas_combinacao[5]);
int tem_dois_pares(tp_carta cartas[], int total, tp_carta cartas_combinacao[5]);
int tem_trinca(tp_carta cartas[], int total, tp_carta cartas_combinacao[5]);
int tem_straight(tp_carta cartas[], int total, tp_carta cartas_combinacao[5]);
int tem_flush(tp_carta cartas[], int total, tp_carta cartas_combinacao[5]);
int tem_full_house(tp_carta cartas[], int total, tp_carta cartas_combinacao[5]);
int tem_quadra(tp_carta cartas[], int total, tp_carta cartas_combinacao[5]);

// --- Avaliação Completa e Comparação ---
int avaliar_pontuacao(tp_carta cartas[], int total, tp_carta cartas_combinacao[5]);
int comparar_maos_semelhantes(tp_carta cartas1[], int tam1, tp_carta mao1[], tp_carta mao2[]);  // Nome corrigido
void imprime_valor_carta(int valor);
// --- Resultados e Desempate ---
void imprimir_tipo_mao(int tipo);
void desempate_cartas_altas(tp_jogador jogadores[], int qnt_vencedores, int vencedores[], tp_listad *mesa);
void verificar_vencedor(tp_jogador jogadores[], int qnt, tp_listad *mesa, ArvAVL* arvore);

void imprime_carta(tp_carta c) {
    printf("[%s | %s]\n", c.valor, c.naipe);
}

// Gera o baralho completo
void criar_baralho(tp_carta baralho[]) {
    int k = 0;
    char *valores[NUM_VALORES] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    char *naipes[NUM_NAIPES] = {"Copas", "Ouros", "Espadas", "Paus"};
    for (int i = 0; i < NUM_NAIPES; i++) {
        for (int j = 0; j < NUM_VALORES; j++) {
            strcpy(baralho[k].naipe, naipes[i]);
            strcpy(baralho[k].valor, valores[j]);
            k++;
        }
    }
}

// Imprime o baralho completo
void imprimir_vetor(tp_carta baralho[]) {
    for (int i = 0; i < NUM_CARTAS; i++) {
        imprime_carta(baralho[i]);
    }
}

// Embaralha o baralho
void embaralhar(tp_carta baralho[]) {
    srand(time(NULL));
    for (int i = NUM_CARTAS; i > 0; i--) {
        int j = rand() % i;
        tp_carta temp = baralho[i - 1];
        baralho[i - 1] = baralho[j];
        baralho[j] = temp;
    }
}

// Empilha as cartas embaralhadas
void empilhar(tp_pilha *p, tp_carta baralho[]) {
    inicializa_pilha(p);
    tp_item e;
    for (int i = 0; i < NUM_CARTAS; i++) {
        strcpy(e.c.naipe, baralho[i].naipe);
        strcpy(e.c.valor, baralho[i].valor);
        push(p, e);
    }
    //imprime_pilha_carta(*p);
}

// criar os josgadores
void criar_jogadores(tp_jogador j[], int qnt) {
    for (int i = 1; i <= qnt; i++) {
        printf("Insira o nome do %d° jogador: ", i);
        scanf("%s", j[i].nome);
        
        // Alocação segura para 2 cartas
        j[i].mao = (tp_carta *)malloc(2 * sizeof(tp_carta));
        if (j[i].mao == NULL) {
            printf("Erro ao alocar memória para as cartas do jogador %d\n", i);
            exit(1);
        }
        
        j[i].carteira = 1000; // Alocando dinheiro para o jogador.
        j[i].ta_jogando = true; // Jogador está ativo na partida.

        // Inicialização explícita
        strncpy(j[i].mao[0].valor, "", sizeof(j[i].mao[0].valor)-1);
        strncpy(j[i].mao[0].naipe, "", sizeof(j[i].mao[0].naipe)-1);
        strncpy(j[i].mao[1].valor, "", sizeof(j[i].mao[1].valor)-1);
        strncpy(j[i].mao[1].naipe, "", sizeof(j[i].mao[1].naipe)-1);
    }
}

// Imprime os jogadores
void imprimir_jogadores(tp_jogador j[], int qnt) {
    printf("\n----- JOGADORES DA PARTIDA -----\n");
    for (int i = 1; i <= qnt; i++) {
        printf("Jogador %d: %s\n", i, j[i].nome);
    }
}

//Distribui as cartas de cada jogador
void distribuicao_cartas_jogadores(tp_pilha *baralho, tp_jogador jogador[], int qnt) {
    tp_item aux;
    for (int i = 1; i <= qnt; i++) {
        printf("\nCartas de %s:\n", jogador[i].nome);
        
        // Primeira carta
        if (!pop(baralho, &aux)) {
            printf("Erro: baralho vazio!\n");
            exit(1);
        }
        strncpy(jogador[i].mao[0].valor, aux.c.valor, sizeof(aux.c.valor)-1);
        strncpy(jogador[i].mao[0].naipe, aux.c.naipe, sizeof(aux.c.naipe)-1);
        imprime_carta(jogador[i].mao[0]);

        // Segunda carta
        if (!pop(baralho, &aux)) {
            printf("Erro: baralho vazio!\n");
            exit(1);
        }
        strncpy(jogador[i].mao[1].valor, aux.c.valor, sizeof(aux.c.valor)-1);
        strncpy(jogador[i].mao[1].naipe, aux.c.naipe, sizeof(aux.c.naipe)-1);
        imprime_carta(jogador[i].mao[1]);
    }
}

// Modifique a declaração para incluir o parâmetro 'imprimir'
void criar_mesa(tp_listad *lista, tp_pilha *baralho, int ciclo, int imprimir) {
    tp_item aux;
    
    switch (ciclo) {
        case 1: 
            for (int i = 0; i < 3; i++) {
                pop(baralho, &aux);
                insere_listad_no_fim(lista, aux.c);
            }
            break;
        case 2: 
            pop(baralho, &aux);
            insere_listad_no_fim(lista, aux.c);
            break;
        case 3: 
            pop(baralho, &aux);
            insere_listad_no_fim(lista, aux.c);
            break;
        default:
            printf("Ciclo inválido!\n");
            return;
    }

    /*if (imprimir) {
        printf("\n----- MESA -----\n");
        imprime_listad(lista, 1);
    }*/
}

// valor npumerico para as cartas que tem letras (A,K,Q e J)// valor npumerico para as cartas que tem letras (A,K,Q e J)
int valor_para_numero(const char *valor) {
    if (strcmp(valor, "A") == 0) return 14;
    if (strcmp(valor, "K") == 0) return 13;
    if (strcmp(valor, "Q") == 0) return 12;
    if (strcmp(valor, "J") == 0) return 11;
    return atoi(valor); // Para valores numéricos (2-10)
}

// Adiciona valor nos naipes das cartas para desenvolver as analises 
int naipe_para_numero(const char *naipe) {
    if (strcmp(naipe, "Copas") == 0) return 0;
    if (strcmp(naipe, "Ouros") == 0) return 1;
    if (strcmp(naipe, "Espadas") == 0) return 2;
    if (strcmp(naipe, "Paus") == 0) return 3;
    return -1;
}

// Função auxiliar para contar valores
void contar_valores(tp_carta cartas[], int total, int contagem[], tp_carta cartas_por_valor[][4]) {
    memset(contagem, 0, 15 * sizeof(int));
    
    for (int i = 0; i < total; i++) {
        int val = valor_para_numero(cartas[i].valor);
        if (val >= 2 && val <= 14) {
            cartas_por_valor[val][contagem[val]] = cartas[i];
            contagem[val]++;
        }
    }
}
int tem_quadra(tp_carta cartas[], int total, tp_carta cartas_combinacao[5]) {
	int contagem[15] = {0};
	tp_carta cartas_por_valor[15][4];
	contar_valores(cartas, total, contagem, cartas_por_valor);
	for (int j = 14; j >= 2; j--) {
		if (contagem[j] >= 4) {
			// Preenche a quadra (4 cartas)
			for (int i = 0; i < 4; i++) {
				cartas_combinacao[i] = cartas_por_valor[j][i];
			}
			// Preenche o kicker (carta mais alta restante)
			for (int k = 14; k >= 2; k--) {
				if (k != j && contagem[k] > 0) {
					cartas_combinacao[4] = cartas_por_valor[k][0];
					return 1;
				}
			}
		}
	}
	return 0;
}
int tem_full_house(tp_carta cartas[], int total, tp_carta cartas_combinacao[5]) {
    int contagem[15] = {0};
    tp_carta cartas_por_valor[15][4];
    contar_valores(cartas, total, contagem, cartas_por_valor);

    int trinca = 0, par = 0;
    
    for (int v = 14; v >= 2; v--) {
        if (contagem[v] >= 3 && !trinca) {
            trinca = v;
        } else if (contagem[v] >= 2 && !par) {
            par = v;
        }
    }

    if (trinca && par) {
        // Preenche trinca
        cartas_combinacao[0] = cartas_por_valor[trinca][0];
        cartas_combinacao[1] = cartas_por_valor[trinca][1];
        cartas_combinacao[2] = cartas_por_valor[trinca][2];
        
        // Preenche par
        cartas_combinacao[3] = cartas_por_valor[par][0];
        cartas_combinacao[4] = cartas_por_valor[par][1];
        
        return 1;
    }
    return 0;
}
int tem_flush(tp_carta cartas[], int total, tp_carta cartas_combinacao[5]) {
    int naipes[4] = {0};
    tp_carta cartas_por_naipe[4][7];
    
    for (int i = 0; i < total; i++) {
        int n = naipe_para_numero(cartas[i].naipe);
        cartas_por_naipe[n][naipes[n]++] = cartas[i];
    }

    for (int n = 0; n < 4; n++) {
        if (naipes[n] >= 5) {
            // Ordena as cartas do naipe
            qsort(cartas_por_naipe[n], naipes[n], sizeof(tp_carta), comparar_cartas);
            
            // Pega as 5 mais altas
            memcpy(cartas_combinacao, cartas_por_naipe[n], sizeof(tp_carta) * 5);
            return 1;
        }
    }
    return 0;
}
int tem_straight(tp_carta cartas[], int total, tp_carta cartas_combinacao[5]) {
    int valores[15] = {0};
    
    // Preenche os valores
    for (int i = 0; i < total; i++) {
        int val = valor_para_numero(cartas[i].valor);
        valores[val] = 1;
        if (val == 14) valores[1] = 1; // Ás como 1
    }

    // Verifica sequência normal (5 cartas altas)
    for (int i = 14; i >= 5; i--) {
        if (valores[i] && valores[i-1] && valores[i-2] && valores[i-3] && valores[i-4]) {
            int seq = 0;
            for (int v = i; v >= i-4; v--) {
                for (int c = 0; c < total && seq < 5; c++) {
                    if (valor_para_numero(cartas[c].valor) == v) {
                        cartas_combinacao[seq++] = cartas[c];
                        break;
                    }
                }
            }
            return 1;
        }
    }
    
    // Verifica sequência baixa (A-2-3-4-5)
    if (valores[14] && valores[2] && valores[3] && valores[4] && valores[5]) {
        int seq = 0;
        int sequencia_baixa[] = {5, 4, 3, 2, 14};
        for (int i = 0; i < 5; i++) {
            for (int c = 0; c < total && seq < 5; c++) {
                if (valor_para_numero(cartas[c].valor) == sequencia_baixa[i]) {
                    cartas_combinacao[seq++] = cartas[c];
                    break;
                }
            }
        }
        return 1;
    }
    
    return 0;
}
int tem_trinca(tp_carta cartas[], int total, tp_carta cartas_combinacao[5]) {
    int contagem[15] = {0};
    tp_carta cartas_por_valor[15][4];
    contar_valores(cartas, total, contagem, cartas_por_valor);

    for (int v = 14; v >= 2; v--) {
        if (contagem[v] >= 3) {
            // Preenche a trinca
            cartas_combinacao[0] = cartas_por_valor[v][0];
            cartas_combinacao[1] = cartas_por_valor[v][1];
            cartas_combinacao[2] = cartas_por_valor[v][2];
            
            // Preenche kickers
            int k = 3;
            for (int vk = 14; vk >= 2 && k < 5; vk--) {
                if (vk != v) {
                    for (int i = 0; i < contagem[vk] && k < 5; i++) {
                        cartas_combinacao[k++] = cartas_por_valor[vk][i];
                    }
                }
            }
            return 1;
        }
    }
    return 0;
}
int tem_dois_pares(tp_carta cartas[], int total, tp_carta cartas_combinacao[5]) {
    int contagem[15] = {0};
    tp_carta cartas_por_valor[15][4];
    contar_valores(cartas, total, contagem, cartas_por_valor);

    int pares[2] = {0};
    int num_pares = 0;
    
    for (int v = 14; v >= 2 && num_pares < 2; v--) {
        if (contagem[v] >= 2) {
            pares[num_pares++] = v;
        }
    }

    if (num_pares >= 2) {
        // Preenche os dois pares
        cartas_combinacao[0] = cartas_por_valor[pares[0]][0];
        cartas_combinacao[1] = cartas_por_valor[pares[0]][1];
        cartas_combinacao[2] = cartas_por_valor[pares[1]][0];
        cartas_combinacao[3] = cartas_por_valor[pares[1]][1];
        
        // Preenche kicker
        for (int v = 14; v >= 2; v--) {
            if (v != pares[0] && v != pares[1] && contagem[v] > 0) {
                cartas_combinacao[4] = cartas_por_valor[v][0];
                break;
            }
        }
        return 1;
    }
    return 0;
}

int tem_um_par(tp_carta cartas[], int total, tp_carta cartas_combinacao[5]) {
    int contagem[15] = {0};
    tp_carta cartas_por_valor[15][4];
    contar_valores(cartas, total, contagem, cartas_por_valor);

    for (int v = 14; v >= 2; v--) {
        if (contagem[v] >= 2) {
            // Preenche as cartas do par
            cartas_combinacao[0] = cartas_por_valor[v][0];
            cartas_combinacao[1] = cartas_por_valor[v][1];
            
            // Preenche kickers
            int k = 2;
            for (int vk = 14; vk >= 2 && k < 5; vk--) {
                if (vk != v) {
                    for (int i = 0; i < contagem[vk] && k < 5; i++) {
                        cartas_combinacao[k++] = cartas_por_valor[vk][i];
                    }
                }
            }
            return 1;
        }
    }
    return 0;
}

// Função para desempate entre mãos do mesmo tipo
int comparar_maos_semelhantes(tp_carta cartas1[], int tam1, tp_carta mao1[], tp_carta mao2[]){
    int valores1[7], valores2[7];
    
    // Converter valores
    for (int i = 0; i < 2; i++) {
        valores1[i] = valor_para_numero(mao1[i+1].valor);
        valores2[i] = valor_para_numero(mao2[i+1].valor);
    }
    
    for (int i = 2; i < tam1; i++) {
        valores1[i] = valor_para_numero(cartas1[i].valor);
        valores2[i] = valor_para_numero(cartas1[i].valor);
    }
    
    // Ordenar em ordem decrescente
    qsort(valores1, tam1, sizeof(int), comparar_cartas);
    qsort(valores2, tam1, sizeof(int), comparar_cartas);
    
    // Comparar
    for (int i = 0; i < tam1; i++) {
        if (valores1[i] > valores2[i]) return 1;
        if (valores1[i] < valores2[i]) return -1;
    }
    return 0;
}

int avaliar_pontuacao(tp_carta cartas[], int total, tp_carta cartas_combinacao[5]) {
    // Limpa as cartas da combinação
    memset(cartas_combinacao, 0, sizeof(tp_carta) * 5);

    //  Verifica Quadra primeiro, pois é uma das mãos mais fortes
    if (tem_quadra(cartas, total, cartas_combinacao)) return 8; // Retorna 8 para Quadra
    if (tem_full_house(cartas, total, cartas_combinacao)) return 7;
    if (tem_flush(cartas, total, cartas_combinacao)) return 6;
    if (tem_straight(cartas, total, cartas_combinacao)) return 5;
    if (tem_trinca(cartas, total, cartas_combinacao)) return 4;
    if (tem_dois_pares(cartas, total, cartas_combinacao)) return 3;
    if (tem_um_par(cartas, total, cartas_combinacao)) return 2;
    
    // Carta alta - pega as 5 melhores
    qsort(cartas, total, sizeof(tp_carta), comparar_cartas);
    memcpy(cartas_combinacao, cartas, sizeof(tp_carta) * 5);
    return 1;
}

int comparar_cartas(const void *a, const void *b) {
    const tp_carta *ca = (const tp_carta *)a;
    const tp_carta *cb = (const tp_carta *)b;
    return valor_para_numero(cb->valor) - valor_para_numero(ca->valor);
}

void desempate_cartas_altas(tp_jogador jogadores[], int qnt_vencedores, int vencedores[], tp_listad *mesa) {
    
    AnaliseJogador analises[qnt_vencedores];
    
    //  Analisa cada jogador
    for (int i = 0; i < qnt_vencedores; i++) {
        int jogador_id = vencedores[i];
        analises[i].id_jogador = jogador_id;
        
        tp_carta todas[7];
        todas[0] = jogadores[jogador_id].mao[0];
        todas[1] = jogadores[jogador_id].mao[1];
        
        tp_no *atual = mesa->ini;
        for (int j = 2; j < 7 && atual != NULL; j++) {
            todas[j] = atual->info;
            atual = atual->prox;
        }

        int contagem[15] = {0};
        for (int j = 0; j < 7; j++) {
            contagem[valor_para_numero(todas[j].valor)]++;
        }

        // Encontra e armazena as cartas da combinação principal
        int combinacao_encontrada = 0;
        analises[i].valor_combinacao = 0;
        
        for (int v = 14; v >= 2; v--) {
            if (contagem[v] >= 2) {
                analises[i].valor_combinacao = v;
                
                // Armazena as cartas que formam a combinação
                for (int j = 0; j < 7 && combinacao_encontrada < 2; j++) {
                    if (valor_para_numero(todas[j].valor) == v) {
                        analises[i].cartas_combinacao[combinacao_encontrada] = todas[j];
                        combinacao_encontrada++;
                    }
                }
                break;
            }
        }

        // Prepara kickers
        int k = 0;
        for (int v = 14; v >= 2; v--) {
            if (v != analises[i].valor_combinacao) {
                for (int j = 0; j < contagem[v] && k < 5; j++) {
                    analises[i].kickers[k++] = v;
                }
            }
        }
        analises[i].num_kickers = k;
    }

    // Ordena jogadores
    for (int i = 0; i < qnt_vencedores; i++) {
        for (int j = i+1; j < qnt_vencedores; j++) {
            if (analises[j].valor_combinacao > analises[i].valor_combinacao ||
                (analises[j].valor_combinacao == analises[i].valor_combinacao &&
                 analises[j].kickers[0] > analises[i].kickers[0])) {
                AnaliseJogador temp = analises[i];
                analises[i] = analises[j];
                analises[j] = temp;
            }
        }
    }

    // Exibe resultado
    if (qnt_vencedores == 1 || 
        analises[0].valor_combinacao > analises[1].valor_combinacao ||
        analises[0].kickers[0] > analises[1].kickers[0]) {
        
        printf("\nDESEMPATE: %s vence com ", jogadores[analises[0].id_jogador].nome);
        
        if (analises[0].valor_combinacao > 0) {
            printf("par de ");
            imprime_valor_carta(analises[0].valor_combinacao);
            printf("s\nCartas decisivas:\n");
            
            // Mostra as 2 cartas que formam o par
            for (int i = 0; i < 2; i++) {
                imprime_carta(analises[0].cartas_combinacao[i]);
            }
        } else {
            printf("carta alta\n");
            // Lógica para carta alta (caso necessário)
        }
    } else {
        printf("\nEMPATE IRREDUTÍVEL - Dividindo o pote\n");
    }
}


void imprime_valor_carta(int valor) { //Para desempate
    const char *valores[] = {"", "", "2", "3", "4", "5", "6", "7", "8", 
                           "9", "10", "J", "Q", "K", "A"};
    if (valor >= 2 && valor <= 14) {
        printf("%s", valores[valor]);
    }
}

void identificar_e_anunciar_vencedores(tp_jogador jogadores[], int qnt, int pontuacoes[], int melhor_pontuacao, tp_listad *mesa) {
    int qnt_vencedores = 0;
    int vencedores[qnt + 1];

    for (int i = 1; i <= qnt; i++) {
        if (pontuacoes[i] == melhor_pontuacao) {
            vencedores[qnt_vencedores++] = i;
        }
    }

    if (qnt_vencedores == 1) {
        printf("\n——— VENCEDOR ———\n");
        printf("%s com ", jogadores[vencedores[0]].nome);
        imprimir_tipo_mao(melhor_pontuacao);
        printf("!\nCartas da combinação vencedora:\n");
        for (int i = 0; i < 5 && strlen(jogadores[vencedores[0]].cartas_vencedoras[i].valor) > 0; i++) {
            imprime_carta(jogadores[vencedores[0]].cartas_vencedoras[i]);
        }
    } else if (qnt_vencedores > 1) {
        printf("\n=== EMPATE DETECTADO ===\n");
        desempate_cartas_altas(jogadores, qnt_vencedores, vencedores, mesa);
    }
}

void verificar_vencedor(tp_jogador jogadores[], int qnt, tp_listad *mesa, ArvAVL* arvore){
    static int resultado_anunciado = 0;
    if (resultado_anunciado) return;
    
    int pontuacoes[qnt+1];
    int melhor_pontuacao = -1;
    
    printf("\n--- AVALIAÇÃO DAS MÃOS ---\n");
    // Avalia cada jogador
    for (int i = 1; i <= qnt; i++) {
        tp_carta todas[7];
        
        // Cartas do jogador
        todas[0] = jogadores[i].mao[0];
        todas[1] = jogadores[i].mao[1];

        // Cartas da mesa
        int k = 2;
        tp_no *atual = mesa->ini;
        while (atual != NULL && k < 7) {
            todas[k++] = atual->info;
            atual = atual->prox;
        }

        // Verifica combinações e armazena cartas vencedoras
        pontuacoes[i] = avaliar_pontuacao(todas, k, jogadores[i].cartas_vencedoras);
        
        printf("%s -> ", jogadores[i].nome);
        imprimir_tipo_mao(pontuacoes[i]);
        printf("\n");
        
        if (pontuacoes[i] > melhor_pontuacao) {
            melhor_pontuacao = pontuacoes[i];
        }
	    
        // Adiciona os tipos das mãos no contador da árvore
        inserir(arvore, pontuacoes[i]);////////////////////    RECENTE   /////////////////////////

    }

    identificar_e_anunciar_vencedores(jogadores, qnt, pontuacoes, melhor_pontuacao, mesa);
    resultado_anunciado = 1;
}

// Função para imprimir o tipo de mão
void imprimir_tipo_mao(int tipo) {
    const char *nomes[] = {
        "", // Índice 0 não usado
        "Carta Alta",
        "Um Par",
        "Dois Pares",
        "Trinca",
        "Sequência",
        "Flush",
        "Full House", 
        "Quadra"
    };
    if (tipo >= 1 && tipo <= 8) {
        printf("%s", nomes[tipo]);
    }
}

// Função para imprimir o contador de mãos
void print_contador(int repeticoes, int tipo_mao){
	printf("Teve %d vezes que o(a)", repeticoes);
	imprimir_tipo_mao(tipo_mao);
	printf("apareceu no jogo.\n");
}

// Função auxiliar para percorrer a árvore em ordem e contar as mãos
void percorrer_e_contar(struct NO* no, int contagem[]) {
    if (no == NULL) {
        return;
    }
    // O valor 'info' do nó é o tipo da mão (1 a 8)
    if (no->info >= 1 && no->info <= 8) {
        contagem[no->info]++;
    }
    percorrer_e_contar(no->esq, contagem);
    percorrer_e_contar(no->dir, contagem);
}

void apresentar_contagem_maos(ArvAVL* arvore) {
    if (arvore == NULL || *arvore == NULL) {
        printf("\nNenhuma jogada vencedora foi registrada.\n");
        return;
    }
    
    // Array para contar as 8 combinações + 1 (índice 0 não usado)
    int contagem[9] = {0}; 

    // Preenche o array de contagem percorrendo a árvore
    percorrer_e_contar(*arvore, contagem);

    printf("\n--- ESTATÍSTICAS FINAIS DO JOGO ---\n");
    printf("Quantidade de vezes que cada combinação venceu uma rodada:\n");

    for (int i = 1; i <= 8; i++) {
        if (contagem[i] > 0) {
            imprimir_tipo_mao(i);
            printf(": %d vez(es)\n", contagem[i]);
        }
    }
}

int todos_apostaram_mesmo_valor(int apostas[], tp_jogador jogadores[], int qnt) {
    int valor_ref = -1;
    for (int j = 1; j <= qnt; j++) {
        if (!jogadores[j].ta_jogando) continue;

        if (valor_ref == -1) {
            valor_ref = apostas[j];
        } else if (apostas[j] != valor_ref) {
            return 0; // Alguém apostou diferente
        }
    }
    return 1; // Todos que ainda jogam apostaram o mesmo valor
}

int valor_para_pagar(int aposta_rodada, int apostas[], int jogador_atual) {
    return aposta_rodada - apostas[jogador_atual];
}

// Menu inicial das jogadas do jogador
int print_escolhas_jogador(tp_listad *mesa, tp_jogador jogadores[], int jogador_atual, int aposta_rodada, int apostas[], pote *pote_atual)   {
    printf("************************************\n");
    printf("Mesa atual: ");
    imprime_listad(mesa, 1); // Imprime as cartas na mesa

    printf("Sua mao:\n");
    imprime_carta(jogadores[jogador_atual].mao[0]);
    imprime_carta(jogadores[jogador_atual].mao[1]);

    printf("\nDinheiro atual: %d\n", jogadores[jogador_atual].carteira);
    printf("Aposta minima da rodada: %d\n", aposta_rodada);
    printf("Pote atual: %d\n", pote_atual->pote);
    printf("Sua aposta na rodada: %d\n", apostas[jogador_atual]);
    printf("************************************\n");

    printf("\n%s, faça sua escolha:\n", jogadores[jogador_atual].nome);
    printf("1 - Aumentar aposta\n");
    printf("2 - Desistir\n");

    // Informa o valor correto a pagar ou se a ação é um "All-in"
    int valor_a_pagar = valor_para_pagar(aposta_rodada, apostas, jogador_atual); // Calcula o valor a pagar para continuar na partida.
    if (valor_a_pagar <= 0) {
        printf("3 - Passar (Check)\n"); // Se não há aposta para cobrir
    } else if (valor_a_pagar >= jogadores[jogador_atual].carteira) {
        printf("3 - All-in (%d)\n", jogadores[jogador_atual].carteira);
    } else {
        printf("3 - Pagar (%d)\n", valor_a_pagar);
    }
    
    printf("Escolha: ");
    
    int escolha;
    scanf("%d", &escolha);

    return escolha;
}

int aumentar_aposta(tp_jogador jogadores[],int jogador_atual, int apostas[], int *aposta_rodada, pote *pote_atual) {
    int valor;
    int diferenca;

    printf("Digite o valor para aumentar (mínimo %d): ", *aposta_rodada + 1);
    scanf("%d", &valor);

    // Verifica se o valor é válido
    if (valor > jogadores[jogador_atual].carteira) {
        valor = jogadores[jogador_atual].carteira;
    } else if (valor < *aposta_rodada + 1) {
        valor = *aposta_rodada + 1;
    }

    // Atualiza a aposta do jogador
    *aposta_rodada = valor;

    // Calcula a diferença entre o valor atual da aposta e o que o jogador já apostou
    diferenca = valor_para_pagar(*aposta_rodada, apostas, jogador_atual);

    // Atualiza o pote da rodada
    pote_atual->pote += diferenca;
    //Reduz a carteira do jogador
    jogadores[jogador_atual].carteira -= diferenca;

    // Atualiza a aposta do jogador no vetor de apostas
    apostas[jogador_atual] = valor;

    return 0;
}

// pagar aposta do jogador
void pagar_aposta(tp_jogador jogadores[], int j, int aposta_rodada, int apostas[], pote *pote_atual) {
    int pagar = valor_para_pagar(aposta_rodada, apostas, j);

    if (pagar > jogadores[j].carteira) {
        pagar = jogadores[j].carteira;
    }
    pote_atual->pote += pagar;
    jogadores[j].carteira -= pagar;
    apostas[j] = aposta_rodada;
}

// Função para escolha de ação do jogador durante a rodada de apostas - CORRIGIDA
void escolha(pote *pote_atual, tp_jogador jogadores[], int qnt, tp_listad *mesa) {
    int aposta_rodada = 0; // Valor mínimo da aposta na rodada
    int apostas[qnt + 1]; //vetor para armazenar as apostas de cada jogador
    int todos_iguais = 0; // Variável para verificar se todos apostaram o mesmo valor

    // Inicializa as apostas e o estado de jogo dos jogadores
    for (int i = 1; i <= qnt; i++) {
        jogadores[i].ta_jogando = true; // Reinicia o estado de jogo dos jogadores
        apostas[i] = 0; // Inicializa as apostas de cada jogador
    }

    // Continua as apostas que todos tenham apostado o mesmo valor ou que todos tenham desistido
    while (!todos_iguais) {
        todos_iguais = 1;

        // Todos os jogadores apostam ou desistem
        for (int j = 1; j <= qnt; j++) {
            if (!jogadores[j].ta_jogando) continue;

            // Verifica se o jogador precisa aumentar a aposta
            if (apostas[j] < aposta_rodada || apostas[j] == 0) {
                switch (print_escolhas_jogador(mesa, jogadores, j, aposta_rodada, apostas, pote_atual)) {
                    case 1:  // Aumentar
                        todos_iguais = aumentar_aposta(jogadores, j, &aposta_rodada, &apostas[j], pote_atual);
                        break;
                    case 2: // Desistir
                        jogadores[j].ta_jogando = false;
                        printf("%s desistiu da rodada.\n", jogadores[j].nome);
                        break;
                    case 3: // Pagar/igualar
                        pagar_aposta(jogadores, j, aposta_rodada, apostas, pote_atual);
                        break;
                    default:
                        printf("Opção inválida. Pular jogador.\n");
                        break;
                }
            }
        }
        
        todos_iguais = todos_apostaram_mesmo_valor(apostas, jogadores, qnt);
    }
    system("clear");
}

void rodada(tp_listad *mesa, tp_pilha *baralho, tp_jogador jogadores[], pote **total_potes, int qnt, ArvAVL* arvore) {
    int ciclo = 1; // Ciclo de apostas 
    pote pote_atual = {0}; // Pote da rodada atual

    // reinicia permissao dos jogadores para jogar
    for (int i = 1; i <= qnt; i++) {
        jogadores[i].ta_jogando = true;
    }

    //distribui as cartas para os jogadores
    distribuicao_cartas_jogadores(baralho, jogadores, qnt);

    // Inicia o ciclo de apostas
    while (4 > ciclo) {
        criar_mesa(mesa, baralho, ciclo, 1); // Cola as cartas na mesa
        escolha(&pote_atual, jogadores, qnt, mesa); // Faz escolha dos jogadores 
        system("clear");
        ciclo++;
    }
    
    esvazia_listad(mesa); // Limpa a mesa para a próxima rodada
    system("clear");

    // Atualiza o total do pote
    (**total_potes).pote += pote_atual.pote;

    // Adiciona o pote atual ao total 
    verificar_vencedor(jogadores, qnt, mesa, arvore);
}

// Vencedor do jogo final
int vencedor_poker(tp_jogador jogadores[], pote *total_pote, int qnt) {
    int ativos = 0; // Contador de jogadores ativos

    // Verifica quantos jogadores ainda estão ativos
    for (int i = 1; i <= qnt; i++) {
        if (jogadores[i].carteira > 0) ativos++;
        if (jogadores[i].carteira == total_pote->pote) return 0; // Fim do jogo
    }
    return (ativos > 1); // Continua se houver mais de um jogador
}

// Função principal do jogo
void jogo(tp_listad *mesa, tp_pilha *baralho, tp_jogador jogadores[], pote *total_pote, int qnt, ArvAVL* arvore) {
    int continuar = 1;

    // O jogo continua enquanto houver não houver um vencedor
    while (continuar) {
        // Verifica se o baralho está vazio e cria um novo baralho se necessário
        if(baralho->topo <= (qnt * 2 + 5)) {
            tp_carta baralho_aux[52]; // vetor auxiliar para o baralho
            
            inicializa_pilha(baralho); // Esvazia o baralho atual
            criar_baralho(baralho_aux); // Cria um novo baralho se estiver vazio
            embaralhar(baralho_aux); // Reembaralha o baralho se estiver vazio
            empilhar(baralho, baralho_aux); // Empilha as cartas no baralho
        }

        rodada(mesa, baralho, jogadores, &total_pote, qnt, arvore);
        continuar = vencedor_poker(jogadores, total_pote, qnt);
    }

    // Exibe as mãos de todas as jogadas do jogo
    apresentar_contagem_maos(arvore);
}

#endif