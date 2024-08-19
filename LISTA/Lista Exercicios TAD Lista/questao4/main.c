#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//STRUCTS---------------------------------------------------------------------------------
typedef struct produto
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

typedef struct lista
{
    TCelula* primeiro;
    TCelula* ultimo;
    int tamanho;

} TLista;

//FUNÇÕES---------------------------------------------------------------------------------
void FLVazia(TLista *Lista)
{
    Lista -> primeiro = (TCelula *) malloc (sizeof(TCelula));
    Lista -> ultimo = Lista -> primeiro;
    Lista -> primeiro -> prox = NULL;
    Lista -> tamanho = 0;
}
int Vazia (TLista Lista)
{
    return (Lista.primeiro==Lista.ultimo);//Se sim retorna 1, senão retorna 0
}

void Inserir (TProduto x, TLista *Lista)
{
    Lista -> ultimo -> prox = (TCelula *)malloc(sizeof(TCelula));
    Lista -> ultimo = Lista -> ultimo -> prox;
    Lista ->  ultimo -> item = x;
    Lista ->  ultimo -> prox = NULL;
    Lista -> tamanho++;
}
void ImprimirProduto(TProduto Item)
{
    printf("\n\nCodigo: %d",Item.codigo);
    printf("\nNome: %s",Item.nome);
    printf("\nDescricao: %s",Item.descricao);
    printf("\nPreco: %.2f",Item.preco);
    printf("\nQuantidade: %d",Item.QTD);
}
void Imprimir (TLista Lista)
{
    TCelula *Aux;
    Aux = Lista.primeiro -> prox;
    while (Aux != NULL)
    {
        ImprimirProduto(Aux->item);
        Aux = Aux -> prox;
    }
}
TCelula *Pesquisar (TLista Lista, TProduto Item)
{
    TCelula *Aux;
    Aux = Lista.primeiro;
    while (Aux->prox != NULL)
    {
        if(Aux->prox->item.codigo == Item.codigo)
            return Aux;
        Aux = Aux->prox;
    }
    return NULL;
}
void Excluir (TLista *Lista, TProduto *Item)
{
    TCelula *Aux1, *Aux2;
    Aux1 = Pesquisar(*Lista, *Item);
    if (Aux1 != NULL)
    {
        Aux2 = Aux1 -> prox;
        Aux1 -> prox = Aux2-> prox;
        *Item = Aux2 -> item;
        if(Aux1->prox == NULL)
            Lista->ultimo=Aux1;
        free(Aux2);
        Lista -> tamanho--;
    }
    else
    {
        Item->codigo = -1;
    }
}

void LerProduto (TProduto *Item)
{
    printf("\nDigite o codigo do produto:");
    fflush(stdin);
    scanf("%d", &Item->codigo);
    printf("Digite o nome do produto:");
    fflush(stdin);
    fgets(Item->nome, 100, stdin);
    Item->nome[strcspn(Item->nome, "\n")] = 0;
    printf("Digite a descricao:");
    fflush(stdin);
    fgets(Item->descricao, 100, stdin);
    Item->descricao[strcspn(Item->descricao, "\n")] = 0;
    printf("Digite o valor do produto:");
    fflush(stdin);
    scanf("%f", &Item->preco);
    printf("Digite a quantidade:");
    fflush(stdin);
    scanf("%d", &Item->QTD);
}
void LiberarLista (TLista *Lista)
{

    while(!Vazia(*Lista))
    {
        Excluir(Lista, &Lista->primeiro->prox->item);
    }
    free(Lista->primeiro); //Exclui a cabeça da lista
    Lista->primeiro = NULL;
}


////MAIN-------------------------------------------------------------------------------------
int main()
{
    int opcao, QuantosProdutosQuerInserir;

    //CRIANDO LISTA E PRODUTO
    TProduto x;
    TCelula *AuxiliarDePesquisa;
    TLista L1;
    FLVazia(&L1);

        //TESTANDO SE LISTA ESTA VAZIA
        if(Vazia(L1)!= 1)
        {
            printf("Nao foi possivel criar a lista");
            return 1;
        }

    do
    {
        printf("\n\n\tDigite um numero para realizar algo com a lista\n\n");
        printf("0 - Sair do programa\n");
        printf("1 - Adicionar produto na lista\n");
        printf("2 - Imprimir a lista\n");
        printf("3 - Pesquisar algum produto na lista\n");
        printf("4 - Excluir algum produto da lista\n");
        printf("5 - Excluir lista\n");
        fflush(stdin);
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
            LiberarLista(&L1);
            printf("\nObrigado por usar o programa! Caso queira fazer uma nova lista execute o programa novamente...\n");
            break;
        case 1:
            printf("\nQuantos produtos quer inserir?\n");
            fflush(stdin);
            scanf("%d", &QuantosProdutosQuerInserir);
            for (int i=0; i<QuantosProdutosQuerInserir; i++)
            {
                //LENDO UM PRODUTO
                printf("\n\n\tProduto %d:\n\n", i+1);
                LerProduto(&x);

                //INSERINDO PRODUTO
                Inserir(x, &L1);
            }
            break;

        case 2:
            Imprimir(L1);
            break;

        case 3:
            printf("\nQual codigo do item?\n");
            fflush(stdin);
            scanf("%d", &x.codigo);
            AuxiliarDePesquisa = Pesquisar(L1, x);
            if(AuxiliarDePesquisa==NULL)
            {
                printf("\nNao foi possivel encontrar o produto");
            }
            else
            {
                printf("\nProduto encontrado!");
            }
            break;

        case 4:
            printf("\nQual codigo do produto que deseja excluir?\n");
            fflush(stdin);
            scanf("%d", &x.codigo);
            Excluir(&L1, &x);

            if(x.codigo==-1)
            {
                printf("\nNao foi possivel excluir o produto");
            }
            else
            {
                printf("\nProduto excluido");
            }
            break;

        case 5:
            LiberarLista(&L1);
            printf("\nObrigado por usar o programa! Caso queira fazer uma nova lista execute o programa novamente...\n");
            opcao = 0;
            break;
        default:
            printf("\nOpcao invalida!");
            break;
        }
    }while(opcao!=0);

    return 0;
}
