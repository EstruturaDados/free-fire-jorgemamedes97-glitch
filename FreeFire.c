#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_ITENS 20
#define MAX_NOME 30
#define MAX_TIPO 20

// Estrutura do item
struct Item {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
    int prioridade;
};

/* ================= FUNÇÕES AUXILIARES ================= */
void remove_newline(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') s[len - 1] = '\0';
}

void mostrarItens(struct Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("\nA mochila está vazia.\n");
        return;
    }
    printf("\n=== Itens na Mochila ===\n");
    for (int i = 0; i < totalItens; i++) {
        printf("%2d) Nome: %-25s | Tipo: %-15s | Quantidade: %d | Prioridade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
}

/* =================== INSERÇÃO =================== */
void inserirItem(struct Item mochila[], int *totalItens) {
    if (*totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }
    printf("\n=== Cadastro de Novo Item ===\n");

    printf("Nome do item: ");
    getchar(); // Limpa buffer
    fgets(mochila[*totalItens].nome, MAX_NOME, stdin);
    remove_newline(mochila[*totalItens].nome);

    printf("Tipo do item: ");
    fgets(mochila[*totalItens].tipo, MAX_TIPO, stdin);
    remove_newline(mochila[*totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[*totalItens].quantidade);

    printf("Prioridade (1 a 10): ");
    scanf("%d", &mochila[*totalItens].prioridade);
    if (mochila[*totalItens].prioridade < 1) mochila[*totalItens].prioridade = 1;
    if (mochila[*totalItens].prioridade > 10) mochila[*totalItens].prioridade = 10;

    (*totalItens)++;
    printf("Item adicionado com sucesso!\n");
}

/* =================== REMOÇÃO =================== */
void removerItem(struct Item mochila[], int *totalItens) {
    if (*totalItens == 0) {
        printf("\nA mochila está vazia. Nenhum item para remover.\n");
        return;
    }

    char nomeRemover[MAX_NOME];
    printf("\nDigite o nome do item que deseja remover: ");
    getchar();
    fgets(nomeRemover, MAX_NOME, stdin);
    remove_newline(nomeRemover);

    int encontrado = -1;
    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1) {
        printf("Item '%s' não encontrado.\n", nomeRemover);
        return;
    }

    for (int i = encontrado; i < *totalItens - 1; i++)
        mochila[i] = mochila[i + 1];

    (*totalItens)--;
    printf("Item '%s' removido com sucesso!\n", nomeRemover);
}

/* =================== BUSCA =================== */
int buscaBinariaPorNome(struct Item mochila[], int totalItens, char chave[], long long *comparacoes) {
    int inicio = 0, fim = totalItens - 1;
    *comparacoes = 0;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        (*comparacoes)++;
        int cmp = strcmp(mochila[meio].nome, chave);
        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

/* =================== ORDENAÇÃO =================== */
// Bubble Sort por Nome
void bubbleSortNome(struct Item mochila[], int totalItens, long long *comparacoes, double *tempo) {
    *comparacoes = 0;
    clock_t inicio = clock();
    for (int i = 0; i < totalItens - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < totalItens - 1 - i; j++) {
            (*comparacoes)++;
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                struct Item tmp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = tmp;
                trocou = 1;
            }
        }
        if (!trocou) break;
    }
    *tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
}

// Insertion Sort por Tipo
void insertionSortTipo(struct Item mochila[], int totalItens, long long *comparacoes, double *tempo) {
    *comparacoes = 0;
    clock_t inicio = clock();
    for (int i = 1; i < totalItens; i++) {
        struct Item key = mochila[i];
        int j = i - 1;
        while (j >= 0 && strcmp(mochila[j].tipo, key.tipo) > 0) {
            (*comparacoes)++;
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = key;
    }
    *tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
}

// Selection Sort por Prioridade
void selectionSortPrioridade(struct Item mochila[], int totalItens, long long *comparacoes, double *tempo) {
    *comparacoes = 0;
    clock_t inicio = clock();
    for (int i = 0; i < totalItens - 1; i++) {
        int min = i;
        for (int j = i + 1; j < totalItens; j++) {
            (*comparacoes)++;
            if (mochila[j].prioridade < mochila[min].prioridade) min = j;
        }
        if (min != i) {
            struct Item tmp = mochila[i];
            mochila[i] = mochila[min];
            mochila[min] = tmp;
        }
    }
    *tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
}

/* =================== MENU PRINCIPAL =================== */
int main() {
    struct Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;
    bool ordenadaPorNome = false;
    char entrada[50];

    do {
        printf("\n=== Sistema de Inventário Avançado ===\n");
        printf("1. Inserir novo item\n");
        printf("2. Listar itens\n");
        printf("3. Ordenar por Nome (Bubble Sort)\n");
        printf("4. Ordenar por Tipo (Insertion Sort)\n");
        printf("5. Ordenar por Prioridade (Selection Sort)\n");
        printf("6. Buscar item por Nome (Busca Binária)\n");
        printf("7. Montagem final\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        fgets(entrada, sizeof(entrada), stdin);
        opcao = atoi(entrada);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                ordenadaPorNome = false;
                break;
            case 2:
                mostrarItens(mochila, totalItens);
                break;
            case 3: {
                long long comparacoes;
                double tempo;
                bubbleSortNome(mochila, totalItens, &comparacoes, &tempo);
                printf("\nItens ordenados por NOME.\nComparações: %lld | Tempo: %.6f s\n", comparacoes, tempo);
                mostrarItens(mochila, totalItens);
                ordenadaPorNome = true;
                break;
            }
            case 4: {
                long long comparacoes;
                double tempo;
                insertionSortTipo(mochila, totalItens, &comparacoes, &tempo);
                printf("\nItens ordenados por TIPO.\nComparações: %lld | Tempo: %.6f s\n", comparacoes, tempo);
                mostrarItens(mochila, totalItens);
                ordenadaPorNome = false;
                break;
            }
            case 5: {
                long long comparacoes;
                double tempo;
                selectionSortPrioridade(mochila, totalItens, &comparacoes, &tempo);
                printf("\nItens ordenados por PRIORIDADE.\nComparações: %lld | Tempo: %.6f s\n", comparacoes, tempo);
                mostrarItens(mochila, totalItens);
                ordenadaPorNome = false;
                break;
            }
            case 6: {
                if (!ordenadaPorNome) {
                    printf("A busca binária requer ordenação por nome.\n");
                    break;
                }
                char chave[MAX_NOME];
                printf("Digite o nome do item para busca: ");
                fgets(chave, MAX_NOME, stdin);
                remove_newline(chave);
                long long comparacoes;
                int pos = buscaBinariaPorNome(mochila, totalItens, chave, &comparacoes);
                if (pos != -1) {
                    printf("Item encontrado na posição %d:\nNome: %s | Tipo: %s | Quantidade: %d | Prioridade: %d\n",
                           pos + 1, mochila[pos].nome, mochila[pos].tipo, mochila[pos].quantidade, mochila[pos].prioridade);
                } else {
                    printf("Item '%s' não encontrado.\n", chave);
                }
                printf("Comparações realizadas: %lld\n", comparacoes);
                break;
            }
            case 7:
                printf("\n=== Montagem final da torre de resgate ===\n");
                mostrarItens(mochila, totalItens);
                break;
            case 0:
                printf("Saindo do sistema. Boa sorte na fuga!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
