/*Crie uma função que receba como parâmetro três filas e que realiza a “interseção” (operação de conjunto)
dos elementos das duas primeiras filas na terceira.*/

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
    //somente para questao 2
    int elemento;

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
    printf("\nElemento: %d",Item.elemento);
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
int PesquisarElementoFila(TFila *Fila, TProduto *Item)
{
    TProduto x;
    TFila Faux;
    FFVazia(&Faux);
    int flag=0;
    while(!Vazia(*Fila))
    {
        Desenfileirar(Fila,&x);
        if(x.elemento==Item->elemento)
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

int VerificarSeFilasTemElementosIguais(TFila *Fila1, TFila *Fila2)
{
    TProduto x;
    TFila Faux;
    FFVazia(&Faux);
    int flag=0;

    //se os tamanhos forem diferentes, as filas ja nao sao iguais
    if (Fila1->tamanho!=Fila2->tamanho)
    {
        return 0;
    }
    else
    {
        while(!Vazia(*Fila1))
        {
            Desenfileirar(Fila1,&x);
            if (PesquisarElementoFila(Fila2, &x))
            {
                flag++;
            }
            Enfileirar(x, &Faux);
        }
        while(!Vazia(Faux))
        {
            Desenfileirar(&Faux, &x);
            Enfileirar (x, Fila1);
        }
        if (flag==Fila1->tamanho)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}
void IntercesaoTresFilas (TFila *F1, TFila *F2, TFila *F3)
{
    //criacao de produto e fila auxiliares
    TProduto x;
    TFila Faux1, Faux2, Faux3;
    FFVazia(&Faux1);
    FFVazia(&Faux2);
    FFVazia(&Faux3);

    //juncao da primeira fila na segunda
    while(!Vazia(*F1))
    {
        Desenfileirar(F1, &x);
        Enfileirar(x, &Faux1);
    }
    while (!Vazia(Faux))
    {
        Desenfileirar(&Faux1, &x);
        Enfileirar(x, &F1);
    }

    LiberarFila(&Faux1);
    LiberarFila(&Faux2);
}

int main()
{
    //criando 3 filas e produto auxiliar
    TFila F[4];
    FFVazia(&F[0]);
    FFVazia(&F[1]);
    FFVazia(&F[2]);
    FFVazia(&F[3]);
    TProduto x;

    //criando fila 1 igual a fila 2
    for(int i=0; i<5; i++)
    {
        x.elemento = i+1;
        Enfileirar(x, &F[0]);
    }
    ImprimirFila(&F[0]);
    for(int i=5; i>0; i--)
    {
        x.elemento = i;
        Enfileirar(x, &F[1]);
    }
    ImprimirFila(&F[1]);

    //criando fila 3 e 4 diferentes das 2 outras filas
    for(int i=0; i<5; i++)
    {
        x.elemento = i+6;
        Enfileirar(x, &F[2]);
    }
    for(int i=0; i<6; i++)
    {
        x.elemento = i+1;
        Enfileirar(x, &F[3]);
    }


    //verificando se as filas sao iguais e dando retorno com o printf
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if (VerificarSeFilasTemElementosIguais(&F[i], &F[j]))
                printf("\nAs filas %d e %d tem elementos iguais!", i+1, j+1);
            else
                printf("\nAs filas %d e %d tem elementos diferentes!", i+1, j+1);
        }
    }


    LiberarFila(&F[0]);
    LiberarFila(&F[1]);
    LiberarFila(&F[2]);
    LiberarFila(&F[3]);

    return 0;
}
