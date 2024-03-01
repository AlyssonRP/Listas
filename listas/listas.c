#include <stdio.h>
#include <stdlib.h>

struct No {
    int dado;
    struct No* proximoNo;
    struct No* noAnterior;
};

void insereInicio(struct No** cabeca, int novoDado) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->dado = novoDado;
    novoNo->proximoNo = (*cabeca);
    novoNo->noAnterior = NULL;
    if (*cabeca != NULL) {
        (*cabeca)->noAnterior = novoNo;
    }
    (*cabeca) = novoNo;
}

void insereNoFim(struct No** cabeca, int novoDado) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->dado = novoDado;
    novoNo->proximoNo = NULL;

    if (*cabeca == NULL) {
        novoNo->noAnterior = NULL;
        *cabeca = novoNo;
        return;
    }

    struct No* ultimoNo = *cabeca;
    while (ultimoNo->proximoNo != NULL) {
        ultimoNo = ultimoNo->proximoNo;
    }

    ultimoNo->proximoNo = novoNo;
    novoNo->noAnterior = ultimoNo;
}

void insertAposNoEspecifico(struct No** cabeca, int dadoExistente, int novoDado) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->dado = novoDado;

    struct No* atual = *cabeca;

    while (atual != NULL && atual->dado != dadoExistente) {
        atual = atual->proximoNo;
    }

    if (atual == NULL) {
        printf("Nó com dado %d não encontrado na lista.\n", dadoExistente);
        free(novoNo);
        return;
    }

    novoNo->proximoNo = atual->proximoNo;
    novoNo->noAnterior = atual;
    if (atual->proximoNo != NULL) {
        atual->proximoNo->noAnterior = novoNo;
    }
    atual->proximoNo = novoNo;
}

void excluiInicio(struct No** cabeca) {
    if (*cabeca == NULL) {
        printf("A lista está vazia. Não há nada para excluir.\n");
        return;
    }

    struct No* temp = *cabeca;
    *cabeca = (*cabeca)->proximoNo;
    if (*cabeca != NULL) {
        (*cabeca)->noAnterior = NULL;
    }
    free(temp);
}

void excluiFim(struct No** cabeca) {
    if (*cabeca == NULL) {
        printf("A lista está vazia. Não há nada para excluir.\n");
        return;
    }

    struct No* atual = *cabeca;
    while (atual->proximoNo != NULL) {
        atual = atual->proximoNo;
    }

    if (atual->noAnterior != NULL) {
        atual->noAnterior->proximoNo = NULL;
    } else {
        *cabeca = NULL;
    }
    free(atual);
}

void excluiPosicaoEspecifica(struct No** cabeca, int posicao) {
    if (*cabeca == NULL) {
        printf("A lista está vazia. Não há nada para excluir.\n");
        return;
    }

    struct No* atual = *cabeca;
    if (posicao == 0) {
        *cabeca = atual->proximoNo;
        if (*cabeca != NULL) {
            (*cabeca)->noAnterior = NULL;
        }
        free(atual);
        return;
    }

    int i;
    for (i = 0; atual != NULL && i < posicao; i++) {
        atual = atual->proximoNo;
    }

    if (atual == NULL) {
        printf("Posição inválida para exclusão.\n");
        return;
    }

    if (atual->proximoNo != NULL) {
        atual->proximoNo->noAnterior = atual->noAnterior;
    }
    atual->noAnterior->proximoNo = atual->proximoNo;
    free(atual);
}

void display(struct No* cabeca) {
    struct No* atual = cabeca;

    printf("Lista: ");
    while (atual != NULL) {
        printf("%d -> ", atual->dado);
        atual = atual->proximoNo;
    }
    printf("NULL\n");
}


void displayReverse(struct No* cabeca) {
    struct No* atual = cabeca;
    while (atual != NULL && atual->proximoNo != NULL) {
        atual = atual->proximoNo;
    }

    printf("Lista em ordem reversa:\n");
    while (atual != NULL) {
        printf("%d -> ", atual->dado);
        atual = atual->noAnterior;
    }
    printf("NULL\n");
}

int main() {
   
       struct No* lista = NULL;

    // Operações de inserção
    insereInicio(&lista, 5);
    insereNoFim(&lista, 10);
    insertAposNoEspecifico(&lista, 5, 15);

    // Exibir a lista após as inserções
    printf("Lista após inserções:\n");
    display(lista);
    displayReverse(lista);

    // Pesquisa por um dado nó
    int dadoPesquisa = 10;
    struct No* encontrado = NULL;
    struct No* atual = lista;
    while (atual != NULL) {
        if (atual->dado == dadoPesquisa) {
            encontrado = atual;
            break;
        }
        atual = atual->proximoNo;
    }
    if (encontrado != NULL) {
        printf("\nNó com dado %d encontrado na lista.\n", dadoPesquisa);
    } else {
        printf("\nNó com dado %d não encontrado na lista.\n", dadoPesquisa);
    }

    // Exibição de todos os nós da lista
    printf("\nExibição de todos os nós da lista:\n");
    display(lista);

    // Operações de exclusão
    excluiInicio(&lista);
    excluiFim(&lista);
    excluiPosicaoEspecifica(&lista, 1);

    // Exibir a lista resultante após as exclusões
    printf("\nLista após exclusões:\n");
    display(lista);

    return 0;
}




 