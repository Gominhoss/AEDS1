#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//STRUCTS---------------------------------------------------------------------------------
typedef struct item
{
    int codigo;
    char descricao[100];
    char nome [100];
    int QTD;
    float preco;

} TProduto;

typedef struct celula
{
    TProduto item;
    struct celula* prox;
} TCelula;

typedef struct fila
{
    TCelula* frente;
    TCelula* tras;
    int tamanho;
} TFila;

//FUNÇÕES---------------------------------------------------------------------------------
void FFVazia(TFila *Fila)
{
    Fila->frente = (TCelula *) malloc (sizeof(TCelula));
    Fila->tras = Fila->frente;
    Fila->frente->prox = NULL;
    Fila->tamanho = 0;
}

int Vazia(TFila Fila)
{
    return (Fila.frente==Fila.tras);
}

void Enfileirar(TProduto x, TFila *Fila)
{
    Fila->tras->prox = (TCelula*) malloc(sizeof(TCelula));
    Fila->tras = Fila->tras->prox;
    Fila->tras->item = x;
    Fila->tras->prox = NULL;
    Fila->tamanho++;
}

void Desenfileirar(TFila *Fila, TProduto *Item)
{
    TCelula *aux;
    if(!Vazia(*Fila))
    {
    aux = Fila->frente->prox;
    Fila->frente->prox = aux->prox;
    *Item = aux->item;
    free(aux);
        if(Fila->frente->prox == NULL)
            Fila->tras = Fila->frente;
        Fila->tamanho--;
    }
}

void ImprimirProduto(TProduto Item)
{
    printf("\n\nCodigo: %d",Item.codigo);
    printf("\nNome: %s",Item.nome);
    printf("\nDescricao: %s",Item.descricao);
    printf("\nPreco: %.2f",Item.preco);
    printf("\nQuantidade: %d",Item.QTD);
}

void ImprimirFila(TFila *Fila)
{
    TProduto x;
    TFila Faux;
    FFVazia (&Faux);
    int i, n = Fila->tamanho;

    for (i=0; i<n; i++)
    {
        Desenfileirar(Fila,&x);
        ImprimirProduto(x);
        Enfileirar(x, &Faux);
    }
    while(!Vazia(Faux))
    {
        Desenfileirar(&Faux, &x);
        Enfileirar (x, Fila);
    }
}

int PesquisarFila(TFila *Fila, TProduto *Item)
{
    TProduto x;
    TFila Faux;
    FFVazia(&Faux);
    int flag=0;
    while(!Vazia(*Fila))
    {
        Desenfileirar(Fila,&x);
        if(strcmp(x.nome, Item->nome))
        {
            flag=1;//elemento foi encontrado
            *Item=x;
        }
        Enfileirar(x, &Faux);
    }
    while(!Vazia(Faux))
    {
        Desenfileirar(&Faux, &x);
        Enfileirar (x, Fila);
    }
    if(flag==0)
    {
        Item->codigo=-1;
    }
    return flag;

}

void LiberarFila (TFila *Fila)
{
    TProduto x;
    while(!Vazia(*Fila))
    {
        Desenfileirar(Fila, &x);
    }
    free(Fila->frente); //Exclui a cabeça da fila
    Fila->frente = NULL;
}

int main()
{
    printf("Ola mundo\n");
    return 0;
}
