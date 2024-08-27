#include "contref.h"
#include <stdio.h>
#include <stdlib.h>

// Estrutura para manter a contagem de referências
typedef struct ContagemRef {
    void *endereco;
    int contagem;
    struct ContagemRef *proximo;
} ContagemRef;

ContagemRef *lista_refs = NULL;

// Função para encontrar um bloco de memória na lista de referências
ContagemRef* encontrar_ref(void *endereco) {
    ContagemRef *atual = lista_refs;
    while (atual) {
        if (atual->endereco == endereco)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}

// Função para adicionar uma nova entrada de contagem de referência
void adicionar_ref(void *endereco) {
    ContagemRef *nova_ref = (ContagemRef *)malloc(sizeof(ContagemRef));
    nova_ref->endereco = endereco;
    nova_ref->contagem = 1;
    nova_ref->proximo = lista_refs;
    lista_refs = nova_ref;
}

// Função para remover uma entrada de contagem de referência
void remover_ref(void *endereco) {
    ContagemRef *atual = lista_refs, *anterior = NULL;
    while (atual) {
        if (atual->endereco == endereco) {
            if (anterior)
                anterior->proximo = atual->proximo;
            else
                lista_refs = atual->proximo;
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

// Função para alocar memória e inicializar a contagem de referências
void* malloc2(size_t tamanho) {
    void *ptr = malloc(tamanho);
    if (ptr) {
        adicionar_ref(ptr);
    }
    return ptr;
}

// Função para realizar a atribuição de ponteiros e atualizar a contagem de referências
void atrib2(void *endereco1, void *endereco2) {
    ContagemRef *ref1 = encontrar_ref(endereco1);
    ContagemRef *ref2 = encontrar_ref(endereco2);

    if (ref1) {
        ref1->contagem--;
        if (ref1->contagem == 0) {
            free(ref1->endereco);
            remover_ref(ref1->endereco);
        }
    }

    if (ref2) {
        ref2->contagem++;
    }
}

// Função para exibir o estado atual das contagens de referências
void dump() {
    ContagemRef *atual = lista_refs;
    printf("Contagens de referencias atuais:\n");
    while (atual) {
        printf("Endereco: %p | Contagem: %d\n", atual->endereco, atual->contagem);
        atual = atual->proximo;
    }
    printf("-----------------------------\n");
}
