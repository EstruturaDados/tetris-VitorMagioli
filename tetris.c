#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 5
/**
 * @brief Define a estrutura de uma Peça do tetris
 * Possui Tipo e um identificador da peça
 */
typedef struct {
    char tipo;
    int id;
} Peca;

typedef struct {
    Peca pecas[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// --- PROTÓTIPOS DAS FUNÇÕES ---
void inicializar(Fila *f);
int filaCheia(Fila *f);
int filaVazia(Fila *f);
void inserir(Fila *f, Peca p);
Peca retirar(Fila *f);
void mostrarFila(Fila *f);
void gerarPeca(Peca *p); 

int main() {
    Fila f;
    int opcao; //variável para o menu

    srand(time(NULL)); //inicializa o gerador de numeros aleatórios
    inicializar(&f); //inicializa a fila
    

    printf("==============================\n");
    printf("        JOGO DE TETRIS        \n");
    printf("==============================\n");
    printf("Organize e posicione as peças utilizando estruturas de dados fundamentais como parte das mecânicas de jogo!\n");
    // Loop principal do menu
    do {
        printf("\n-------------------[ MENU PRINCIPAL ]-------------------\n");
        printf("1. Jogar uma Peça\n");
        printf("2. Inserir nova Peça\n");
        printf("0. Sair\n");
        scanf("%d", &opcao);
        while (getchar() != '\n');  // Limpa o buffer de entrada (para o caso de o usuário digitar letras)

        switch (opcao)
        {
            case 1: // Jogar uma Peça
                if (filaVazia(&f)) {
                    printf("\nFILA VAZIA! Nenhuma peça para jogar.\n");
                } 
                else {
                    Peca jogada = retirar(&f);
                    printf("\nPeça jogada! ID: %d, Tipo: %c\n", jogada.id, jogada.tipo);
                }
                mostrarFila(&f);
                break;
            
            case 2: //Inserir uma peça
                
                if (filaCheia(&f)) {
                    printf("\nFILA CHEIA! Jogue uma peça antes de gerar outra.\n");
                } else {
                    Peca nova;        // 1. Cria uma struct de peça vazia
                    gerarPeca(&nova); // 2. Passa o endereço para a função preenchê-la
                    inserir(&f, nova);// 3. Insere a peça preenchida na fila
                    printf("\nNova peça gerada! ID: %d, Tipo: %c\n", nova.id, nova.tipo);
                }
                mostrarFila(&f);
                break;

            case 0:
                printf("\nSaindo do jogo...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
                break;
        } 
    } while (opcao != 0); // Fim do loop do-while

    return 0;
}

//==============INICIO DAS FUNÇÕES===================//
/**
 * Inicializa a fila
 */
void inicializar(Fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(Fila *f){
    return f->total == MAX;
}

int filaVazia(Fila *f){
    return f->total == 0;
}

void inserir(Fila *f, Peca p){
    if(filaCheia(f)){ //encerra a execução se a fila estiver cheia
        // Adiciona um feedback para o usuário
        printf("\nERRO: Fila cheia. Não foi possível inserir.\n");
        return;
    }
    f->pecas[f->fim] = p;           //insere a peça no final
    f->fim = (f->fim +1) % MAX;     //atualiza a fila circular
    f->total++;                     //faz a contagem de peças
}

Peca retirar(Fila *f){
    Peca vazia = {' ',-1};              //valor padrão caso a fila esteja vazia
    if(filaVazia(f))
        return vazia;              //evita remoção se já estiver vazia
    Peca p = f->pecas[f->inicio];  //armazena o item a ser removido
    f->inicio = (f->inicio +1) % MAX; //atualiza a fila circular
    f->total--;                    //faz o decremento da contagem das peças da fila
    return p;                      //retorna a peça removida
}

void mostrarFila(Fila *f){
    if(filaVazia(f)){
        printf("Fila: [ VAZIA ]\n");
        return;
    }
    printf("Fila Atual: \n");
    // Este loop imprime os elementos na ordem correta da fila circular
    for(int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx+1) % MAX){
        printf("[%d]: [%c]\n", f->pecas[idx].id, f->pecas[idx].tipo);
    }
    printf("\n");
}

void gerarPeca(Peca *p){
    // 1. GERAÇÃO DO ID SEQUENCIAL
    // 'static' faz com que a variável 'proximo_id' mantenha seu valor
    // mesmo depois que a função termina.
    static int proximo_id = 1;

    // Atribui o ID sequencial usando o ponteiro
    p->id = proximo_id;

    proximo_id++; // Prepara o ID para a próxima peça

    // 2. GERAÇÃO DO TIPO ALEATÓRIO (Peças de Tetris)
    // Lista de tipos de peça (como chars)
    const char tiposDePeca[] = {'I', 'O', 'T', 'S', 'Z', 'J', 'L'};

    // sizeof(tiposDePeca) retorna o número de bytes (que é 7, pois são 7 chars)
    int numTipos = sizeof(tiposDePeca); 

    // rand() % numTipos gera um número aleatório entre 0 e 6
    int indiceAleatorio = rand() % numTipos;

    // Atribui o tipo aleatório à peça usando o ponteiro
    p->tipo = tiposDePeca[indiceAleatorio];
}


// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha
