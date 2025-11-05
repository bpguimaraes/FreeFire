#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// ----------------------------
// Estrutura para o Item
// ----------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ----------------------------
// Estrutura para lista encadeada
// ----------------------------
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ----------------------------
// VARIÁVEIS GLOBAIS PARA CONTAGEM DE COMPARAÇÕES
// ----------------------------
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ============================
// FUNÇÕES PARA VETOR (LISTA SEQUENCIAL)
// ============================

// Inserir item no vetor
void inserirItemVetor(Item vetor[], int *totalItens) {
    if (*totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", novo.nome);
    printf("Digite o tipo do item: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    vetor[*totalItens] = novo;
    (*totalItens)++;
    printf("Item adicionado com sucesso!\n");
}

// Remover item pelo nome no vetor
void removerItemVetor(Item vetor[], int *totalItens) {
    if (*totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(vetor[i].nome, nome) == 0) {
            for (int j = i; j < *totalItens - 1; j++) {
                vetor[j] = vetor[j + 1];
            }
            (*totalItens)--;
            printf("Item removido com sucesso!\n");
            return;
        }
    }
    printf("Item não encontrado!\n");
}

// Listar itens do vetor
void listarItensVetor(Item vetor[], int totalItens) {
    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    printf("Itens na mochila:\n");
    for (int i = 0; i < totalItens; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n", vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
    }
}

// Ordenar vetor pelo nome (Selection Sort)
void ordenarVetor(Item vetor[], int totalItens) {
    for (int i = 0; i < totalItens - 1; i++) {
        int min = i;
        for (int j = i + 1; j < totalItens; j++) {
            if (strcmp(vetor[j].nome, vetor[min].nome) < 0) {
                min = j;
            }
        }
        if (min != i) {
            Item temp = vetor[i];
            vetor[i] = vetor[min];
            vetor[min] = temp;
        }
    }
}

// Busca sequencial no vetor
int buscarSequencialVetor(Item vetor[], int totalItens, char* nome) {
    comparacoesSequencial = 0;
    for (int i = 0; i < totalItens; i++) {
        comparacoesSequencial++;
        if (strcmp(vetor[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

// Busca binária no vetor (após ordenação)
int buscarBinariaVetor(Item vetor[], int totalItens, char* nome) {
    int esquerda = 0, direita = totalItens - 1;
    comparacoesBinaria = 0;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(vetor[meio].nome, nome);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            esquerda = meio + 1;
        else
            direita = meio - 1;
    }
    return -1;
}

// ============================
// FUNÇÕES PARA LISTA ENCADEADA
// ============================

// Inserir item na lista encadeada
void inserirItemLista(No **cabeca) {
    No *novo = (No*)malloc(sizeof(No));
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", novo->dados.nome);
    printf("Digite o tipo do item: ");
    scanf(" %[^\n]", novo->dados.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    novo->proximo = *cabeca;
    *cabeca = novo;
    printf("Item adicionado com sucesso na lista!\n");
}

// Remover item da lista pelo nome
void removerItemLista(No **cabeca) {
    if (*cabeca == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    char nome[30];
    printf("Digite o nome do item a remover: ");
    scanf(" %[^\n]", nome);

    No *atual = *cabeca, *anterior = NULL;
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) {
                *cabeca = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Item removido com sucesso da lista!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item não encontrado!\n");
}

// Listar itens da lista
void listarItensLista(No *cabeca) {
    if (cabeca == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    printf("Itens na lista encadeada:\n");
    No *atual = cabeca;
    while (atual != NULL) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

// Busca sequencial na lista encadeada
int buscarItemLista(No *cabeca, char* nome) {
    comparacoesSequencial = 0;
    No *atual = cabeca;
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0)
            return 1;
        atual = atual->proximo;
    }
    return 0;
}

// ============================
// FUNÇÃO PRINCIPAL
// ============================
int main() {
    Item mochilaVetor[MAX_ITENS];
    int totalItensVetor = 0;
    No *cabecaLista = NULL;
    int opcao, estrutura;

    do {
        printf("\nEscolha a estrutura de dados:\n");
        printf("1 - Vetor\n2 - Lista encadeada\n0 - Sair\n");
        scanf("%d", &estrutura);

        if (estrutura == 0) break;

        do {
            printf("\n=== Menu ===\n");
            printf("1 - Inserir item\n2 - Remover item\n3 - Listar itens\n4 - Buscar item\n5 - Ordenar vetor (apenas vetor)\n0 - Voltar\n");
            printf("Escolha uma opção: ");
            scanf("%d", &opcao);

            char nomeBusca[30];
            int pos;

            switch(opcao) {
                case 1:
                    if (estrutura == 1) inserirItemVetor(mochilaVetor, &totalItensVetor);
                    else inserirItemLista(&cabecaLista);
                    break;
                case 2:
                    if (estrutura == 1) removerItemVetor(mochilaVetor, &totalItensVetor);
                    else removerItemLista(&cabecaLista);
                    break;
                case 3:
                    if (estrutura == 1) listarItensVetor(mochilaVetor, totalItensVetor);
                    else listarItensLista(cabecaLista);
                    break;
                case 4:
                    printf("Digite o nome do item a buscar: ");
                    scanf(" %[^\n]", nomeBusca);
                    if (estrutura == 1) {
                        pos = buscarSequencialVetor(mochilaVetor, totalItensVetor, nomeBusca);
                        if (pos != -1) printf("Item encontrado! Comparações sequenciais: %d\n", comparacoesSequencial);
                        else printf("Item não encontrado! Comparações sequenciais: %d\n", comparacoesSequencial);

                        pos = buscarBinariaVetor(mochilaVetor, totalItensVetor, nomeBusca);
                        if (pos != -1) printf("Item encontrado! Comparações binárias: %d\n", comparacoesBinaria);
                        else printf("Item não encontrado! Comparações binárias: %d\n", comparacoesBinaria);
                    } else {
                        if (buscarItemLista(cabecaLista, nomeBusca))
                            printf("Item encontrado! Comparações sequenciais: %d\n", comparacoesSequencial);
                        else
                            printf("Item não encontrado! Comparações sequenciais: %d\n", comparacoesSequencial);
                    }
                    break;
                case 5:
                    if (estrutura == 1) {
                        ordenarVetor(mochilaVetor, totalItensVetor);
                        printf("Vetor ordenado pelo nome!\n");
                    } else {
                        printf("Ordenação não disponível para lista encadeada!\n");
                    }
                    break;
                case 0:
                    printf("Voltando ao menu anterior.\n");
                    break;
                default:
                    printf("Opção inválida!\n");
            }
        } while(opcao != 0);

    } while (estrutura != 0);

    // Liberar memória da lista encadeada
    No *atual = cabecaLista;
    while (atual != NULL) {
        No *temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    printf("Programa encerrado.\n");
    return 0;
}