#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

void inserirItem(struct Item mochila[], int *totalItens) {
    if (*totalItens >= 10) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\n=== Cadastro de Novo Item ===\n");

    printf("Nome do item: ");
    scanf("%s", mochila[*totalItens].nome);

    printf("Tipo do item: ");
    scanf("%s", mochila[*totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[*totalItens].quantidade);

    (*totalItens)++;

    printf("Item adicionado com sucesso!\n");
}

void listarItens(struct Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("\nA mochila está vazia.\n");
        return;
    }

    printf("\n=== Itens na Mochila ===\n");
    for (int i = 0; i < totalItens; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", mochila[i].nome);
        printf("  Tipo: %s\n", mochila[i].tipo);
        printf("  Quantidade: %d\n", mochila[i].quantidade);
        printf("---------------------------\n");
    }
}

void buscarItem(struct Item mochila[], int totalItens) {
    char nomeBusca[30];
    int encontrado = 0;

    if (totalItens == 0) {
        printf("\nA mochila está vazia. Nenhum item para buscar.\n");
        return;
    }

    printf("\n=== Buscar Item ===\n");
    printf("Digite o nome do item que deseja procurar: ");
    scanf("%s", nomeBusca);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("  Nome: %s\n", mochila[i].nome);
            printf("  Tipo: %s\n", mochila[i].tipo);
            printf("  Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem '%s' não encontrado na mochila.\n", nomeBusca);
    }
}

void removerItem(struct Item mochila[], int *totalItens) {
    if (*totalItens == 0) {
        printf("\nA mochila está vazia. Nenhum item para remover.\n");
        return;
    }

    char nomeRemover[30];
    int encontrado = -1;

    printf("\n=== Remover Item ===\n");
    printf("Digite o nome do item que deseja remover: ");
    scanf("%s", nomeRemover);

    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Item '%s' não encontrado na mochila.\n", nomeRemover);
        return;
    }

    for (int i = encontrado; i < *totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*totalItens)--;

    printf("Item '%s' removido com sucesso!\n", nomeRemover);
}

int main() {
    struct Item mochila[10];
    int totalItens = 0;
    int opcao;

    do {
        printf("\n=== Sistema de Inventário do Jogador ===\n");
        printf("1. Inserir novo item\n");
        printf("2. Listar itens\n");
        printf("3. Buscar item\n");
        printf("4. Remover item\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                break;
            case 2:
                listarItens(mochila, totalItens);
                break;
            case 3:
                buscarItem(mochila, totalItens);
                break;
            case 4:
                removerItem(mochila, &totalItens);
                break;
            case 0:
                printf("\nSaindo do sistema... Até logo!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
