#include <stdio.h>
#include <stdlib.h>
#ifndef ARVORE_B_H
#define ARVORE_B_H
#define M 5

enum Status { Repetido,  ok, Inserir};
enum Status ins(struct node *ptr, int chave, int *chaveAlta, struct node **novoNo);
enum Status del(struct node *ptr, int chave);

#endif
int procuraPosicao(int chave, int *chaveArray, int n);


struct node {
    int n; 
    int chaves[M - 1];
    struct node *p[M];
} *raiz = NULL;




void inserir(int chave) {
    struct node *novoNo;
    int chaveAlta;
    enum Status valor;
    valor = ins(raiz, chave, &chaveAlta, &novoNo);
    if (valor == Repetido)
        printf("Chave repetida\n");
    if (valor == Inserir) {
        struct node *upraiz = raiz;
        raiz = (struct node *) malloc(sizeof(struct node));
        raiz->n = 1;
        raiz->chaves[0] = chaveAlta;
        raiz->p[0] = upraiz;
        raiz->p[1] = novoNo;
    }
}

enum Status ins(struct node *ptr, int chave, int *chaveAlta, struct node **novoNo) {
    struct node *newPtr, *lastPtr;
    int pos, i, n, dividirPosicao;
    int novaChave, ultimaChave;
    enum Status valor;
    if (ptr == NULL) {
        *novoNo = NULL;
        *chaveAlta = chave;
        return Inserir;
    }
    n = ptr->n;
    pos = procuraPosicao(chave, ptr->chaves, n);
    if (pos < n && chave == ptr->chaves[pos])
        return Repetido;
    valor = ins(ptr->p[pos], chave, &novaChave, &newPtr);
    if (valor != Inserir)
        return valor;
    if (n < M - 1) {
        pos = procuraPosicao(novaChave, ptr->chaves, n);        
        for (i = n; i > pos; i--) {
            ptr->chaves[i] = ptr->chaves[i - 1];
            ptr->p[i + 1] = ptr->p[i];
        }
        ptr->chaves[pos] = novaChave;
        ptr->p[pos + 1] = newPtr;
        ++ptr->n;
        return ok;
    }
    if (pos == M - 1) {
        ultimaChave = novaChave;
        lastPtr = newPtr;
    } else {
        ultimaChave = ptr->chaves[M - 2];
        lastPtr = ptr->p[M - 1];
        for (i = M - 2; i > pos; i--) {
            ptr->chaves[i] = ptr->chaves[i - 1];
            ptr->p[i + 1] = ptr->p[i];
        }
        ptr->chaves[pos] = novaChave;
        ptr->p[pos + 1] = newPtr;
    }
    dividirPosicao = (M - 1) / 2;
    (*chaveAlta) = ptr->chaves[dividirPosicao];

    (*novoNo) = (struct node *) malloc(sizeof(struct node));
    ptr->n = dividirPosicao;
    (*novoNo)->n = M - 1 - dividirPosicao;
    for (i = 0; i < (*novoNo)->n; i++) {
        (*novoNo)->p[i] = ptr->p[i + dividirPosicao + 1];
        if (i < (*novoNo)->n - 1)
            (*novoNo)->chaves[i] = ptr->chaves[i + dividirPosicao + 1];
        else
            (*novoNo)->chaves[i] = ultimaChave;
    }
    (*novoNo)->p[(*novoNo)->n] = lastPtr;
    return Inserir;
}

void exibir(struct node *ptr, int espacosEmBranco) {
    if (ptr) {
        int i;
        for (i = 1; i <= espacosEmBranco; i++)
            printf(" ");
        for (i = 0; i < ptr->n; i++)
            printf("%d ", ptr->chaves[i]);
        printf("\n");
        for (i = 0; i <= ptr->n; i++)
            exibir(ptr->p[i], espacosEmBranco + 10);
    }
}

void busca(int chave) {
    int pos, i, n;
    struct node *ptr = raiz;
    printf("Busca:\n");
    while (ptr) {
        n = ptr->n;
        for (i = 0; i < ptr->n; i++)
            printf(" %d", ptr->chaves[i]);
        printf("\n");
        pos = procuraPosicao(chave, ptr->chaves, n);
        if (pos < n && chave == ptr->chaves[pos]) {
            printf("chave %d posição %d da último pagina\n", chave, i);
            return;
        }
        ptr = ptr->p[pos];
    }
    printf("chave %d não está disponível\n", chave);
}

int procuraPosicao(int chave, int *chaveArray, int n) {
    int pos = 0;
    while (pos < n && chave > chaveArray[pos])
        pos++;
    return pos;
}


int main() {
    int chave;
    int escolha;
    inserir(10);
    inserir(11);
    inserir(13);
    inserir(14);
    inserir(15);
    inserir(16);
    inserir(17);
    inserir(18);
    inserir(19);
    inserir(20);
    inserir(30);
    inserir(40);
    inserir(50);
    inserir(60);
    inserir(70);
    inserir(80);
    inserir(90);
    inserir(100);
    inserir(101);
    inserir(102);


    printf("\n\nArvore B-tree %d\n\n", M);
    while (1) {
        printf("Digite sua escolha :\n\n ");
        printf("     (1) Inserir\n      (2) Busca\n      (3) Printar\n      (4)Sair\n");

        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                system("clear");
                printf("Digite o chave : ");
                scanf("%d", &chave);
                inserir(chave);
                
                break;
            case 2:
                printf("Digite o chave : ");
                scanf("%d", &chave);
                busca(chave);
                
                break;
            case 3:
                system("clear");
                printf("Arvore B-tree :\n");
                exibir(raiz, 0);
                printf("\n\n");
                break;
            case 4:
                exit(1);
            default:
                printf("Escolha escolha\n");
                break;
        }
    }
    return 0;
}
