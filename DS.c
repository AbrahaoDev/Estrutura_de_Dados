#include <stdio.h>
#include <stdlib.h>

typedef struct No_Tree{
    int valor;
    struct No_Tree* dir, *esq;
}No_Tree;

typedef struct Tree{
    No_Tree* raiz;
}Tree;

typedef struct No{
    int valor;
    struct No* prox;
}No;

typedef struct lista{
    No* ini, *fim;
}Lista;

Tree* NewTree(){
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->raiz = NULL;
    return tree;
}

No_Tree* NewNo_Tre(int valor){
    No_Tree* no_tree = (No_Tree*)malloc(sizeof(No_Tree));
    no_tree->dir = NULL;
    no_tree->esq = NULL;
    no_tree->valor = valor;
    return no_tree; 
}

void AddNo_Tree(No_Tree* no_tree, int valor){
    if(valor >= no_tree->valor){
        if(no_tree->dir == NULL){
            no_tree->dir = NewNo_Tre(valor);
        }
        else{
            AddNo_Tree(no_tree->dir, valor);
        }
    }
    else{
        if(no_tree->esq == NULL){
            no_tree->esq = NewNo_Tre(valor);
        }
        else{
            AddNo_Tree(no_tree->esq, valor);
        }

    }
}

void AddTree(Tree* tree, int valor){
    if(tree->raiz == NULL){
        tree->raiz = NewNo_Tre(valor);
    }
    else{
        AddNo_Tree(tree->raiz, valor);
    }
}

Lista* NewLista(){
    Lista* lista = (Lista*)malloc(sizeof(lista));
    lista->fim = NULL;
    lista->ini = NULL;
    return lista;
}

No* NewNo(int valor){
    No* no = (No*)malloc(sizeof(No));
    no->prox = NULL;
    no->valor = valor;
    return no;
}

void AddNo(Lista* lista, int valor){
    if(lista->ini == NULL){
        lista->ini = NewNo(valor);
        lista->fim = lista->ini;
    }
    else{
        lista->fim->prox = NewNo(valor);
        lista->fim = lista->fim->prox;
    }
}

void Ler(Lista* lista){
    int i, n, valor;
    printf("Quantos elementos você quer odernar?\n");
    scanf("%d", &n);
    printf("Entre com %d numeros\n", n);
    for(i = 0; i<n; i++){
        scanf("%d", &valor);
        AddNo(lista, valor);
    }
}

int calc_size(Lista* lista){
    int size = 0;
    No* aux = lista->ini;
    while(aux!=NULL){
        size++;
        aux = aux->prox;
    }
    printf("Tamanho da lista: %d\n", size);
    return size;
}


void print(Lista* lista){
    No* aux = lista->ini;
    while(aux != NULL){
        printf("%d,", aux->valor);
        aux = aux->prox;
    }
    printf("\n");
}

void merge(Lista* lista, Lista* lista1, Lista* lista2, int n1, int n2){
    int top = 0, top1 = 0, top2 = 0;
    lista->fim = lista->ini;
    lista1->fim = lista1->ini;
    lista2->fim = lista2->ini;
    while(top1 < n1 && top2 < n2){
        if(lista1->fim->valor < lista2->fim->valor){
            lista->fim->valor = lista1->fim->valor;
            lista->fim = lista->fim->prox;
            lista1->fim = lista1->fim->prox;
            top1++;
            top++;
        }
        else{
            lista->fim->valor = lista2->fim->valor;
            lista->fim = lista->fim->prox;
            lista2->fim = lista2->fim->prox;
            top2++;
            top++;
        }
    }
    while(top1 < n1){
        lista->fim->valor =  lista1->fim->valor;
        lista->fim = lista->fim->prox;
        lista1->fim = lista1->fim->prox;
        top1++;
        top++;       
    }
    while(top2 < n1){
        lista->fim->valor =  lista2->fim->valor;
        lista->fim = lista->fim->prox;
        lista2->fim = lista1->fim->prox;
        top2++;
        top++;       
    }
}

void merge_sort(Lista* lista, int n){
    if(n>1){
        int n1 = n/2, n2 = n-n1, i;
        Lista* lista1 = NewLista(), *lista2 = NewLista();
        lista->fim = lista->ini;

        for(i = 0; i < n1; i++){
            AddNo(lista1, lista->fim->valor);
            lista->fim = lista->fim->prox;
        }
         for(i = 0; i < n2; i++){
            AddNo(lista2, lista->fim->valor);
            lista->fim = lista->fim->prox;
        }
        merge_sort(lista1, n1);
        merge_sort(lista2, n2);
        merge(lista, lista1, lista2, n1, n2);
    }
}

void LerTree(Lista* lista, Tree* tree, int size){
    lista->fim = lista->ini;
    for(int i = 0; i < size; i++){
        AddTree(tree, lista->fim->valor);
        lista->fim = lista->fim->prox;
    }
}
    
void print_tree(No_Tree* no_tree){
    if(no_tree != NULL){
    print_tree(no_tree->esq);
    printf("%d, ", no_tree->valor);
    print_tree(no_tree->dir);
    }
}

int main(){
    Lista* lista = NewLista();
    Tree* tree = NewTree();
    Ler(lista);
    int size = calc_size(lista);
    print(lista);
    merge_sort(lista, size);
    print(lista);
    
    LerTree(lista, tree, size);
    print_tree(tree->raiz);
    printf("\n");
}