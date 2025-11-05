#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10  // Capacidade máxima da mochila

// Estrutura que representa um item do inventário
typedef struct {
    char nome[30];    // Nome do item
    char tipo[20];    // Tipo do item: arma, munição, cura, etc.
    int quantidade;   // Quantidade do item
} Item;

// Função para inserir um item no inventário
void inserirItem(Item mochila[], int *totalItens) {
    if (*totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", novo.nome);  // Lê string com espaços
    printf("Digite o tipo do item: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[*totalItens] = novo;
    (*totalItens)++;

    printf("Item adicionado com sucesso!\n");
}

// Função para remover um item pelo nome
void removerItem(Item mochila[], int *totalItens) {
    if (*totalItens == 0) {
        printf("Mochila vazia! Nenhum item para remover.\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a remover: ");
    scanf(" %[^\n]", nome);

    int encontrado = 0;
    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = 1;
            // Move os itens posteriores uma posição para frente
            for (int j = i; j < *totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*totalItens)--;
            printf("Item removido com sucesso!\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Item não encontrado!\n");
    }
}

// Função para listar todos os itens do inventário
void listarItens(Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    printf("Itens na mochila:\n");
    for (int i = 0; i < totalItens; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Função para buscar um item pelo nome
void buscarItem(Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a buscar: ");
    scanf(" %[^\n]", nome);

    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("Item encontrado: Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Item não encontrado!\n");
    }
}

// Função principal
int main() {
    Item mochila[MAX_ITENS];   // Vetor para armazenar os itens
    int totalItens = 0;        // Número de itens atuais na mochila
    int opcao;

    do {
        printf("\n=== Menu da Mochila ===\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 4:
                buscarItem(mochila, totalItens);
                break;
            case 0:
                printf("Saindo do sistema de mochila.\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
