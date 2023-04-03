#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no *proximo; //aponta pro no seguinte
}No;

void inserior_no_inicio(No **lista, int num){ //ponteiro para NO Lista(recebe o endereço da variavel e a variavel apontara para um no, por isso ponteiro para ponteiro)
    No *novo = malloc(sizeof(No));

    if(novo){
        novo->valor = num; //valor recebido é guardado no novo NO criado
        novo->proximo = *lista; //novo NO apontar para o CONTEUDO(*) do inicio da lista
        *lista = novo; //conteudo da lista receberá o endereco do novo nó
    }else
        printf("Erro na alocacao de memorioa\n");
}

void inserir_no_fim(No **lista, int num){ //lista será criado em main
    No *aux, *novo = malloc(sizeof(No)); //alocacao de memoria para NOVO NÓ

    if(novo){
        novo->valor = num;
        novo->proximo = NULL; //final na lista

        //é o primeiro? na primeira vez esse nó será o primeiro nó da fila
        if(*lista == NULL) //verificar se a fila é vazia
            *lista = novo;
        else{
            aux = *lista; //percorrer toda a lista
            while(aux->proximo)
                aux = aux->proximo;
            aux->proximo = novo; //quando PROXIMO for NULL
        }


    }else
        printf("Erro na alocacao de memoria\n");
}

void inserir_no_meio(No **lista, int num, int ant){//poteiro para o inicio da lista / inserir um elementod depois de uma referencia(ANT)
    No *aux, *novo = malloc(sizeof(No));

    if (novo){
        novo->valor = num;

        //é o primeiro NO? se a lista está vazia
        if(*lista == NULL){ //olhar o conteudo da lista
            novo->proximo = NULL; //se a lista está vazia, o proximo tbm será nulo
            *lista = novo; //o inicio da lista será este novo no
        }
        else{ //percorrer a lista em busca do parametetro ANTERIOR
            aux = *lista; //auxiliar pega o endereço do INICIO da lista
            while(aux->valor != ant && aux->proximo) // && enquanto o aux->prox existir
                aux = aux->proximo; //caminhar na lista
            novo->proximo = aux->proximo;
            aux->proximo = novo; 
        }
    }
    else
        printf("Erro na alocação de memoria\n");

}

void imprimir(No *no){
    printf("\n\tLista: ");
    while(no){
        printf("%d ", no->valor);
        no = no->proximo; //percorrer a listar
    }
    printf("\n\n");

}

No* remover(No **lista, int num){
    No *aux, *remover = NULL;

    if(*lista){ //verificar se a lista é nula
        if((*lista)->valor == num){ //no que quero remover é o primeiro da lista //o conteudo desta posição é igual ao que estou procurando?
            remover = *lista; //remove o primeiro nó da lista
            *lista = remover->proximo; //o primeiro nó da lista passa a ser o próximo
        }
        else{ //se não for o primeito nó, percerre-se a lista procurando
            aux = *lista; //preserva o prieiro nó da lista
            while(aux->proximo && aux->proximo->valor != num)
                aux = aux->proximo;
            if(aux->proximo){ //quer dizer que este valor existe
                remover = aux->proximo; //no que se quer remover
                aux->proximo = remover->proximo;//mantedo a lista ligada
            }else
                printf("\n\tElemento inexistente\n");
        }
    }

    return remover;
}

No* buscar(No **lista,int num){
    No *aux, *no = NULL;

    aux = *lista;
    while(aux && aux->valor != num)
        aux = aux->proximo;
    if(aux)
        no = aux;
    return no;
}

int main()
{
    int opcao, valor, anterior;
    No *removido, *lista = NULL;


    do{
        printf("\n\t0 - Sair\n\t1 - Inserir Inicio\n\t2 - Inserir Meio\n\t3 - Inserir Fim\n\t4 - Imprimir\n\t5 - Remover\n\t6 - Buscar\n\t");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                printf("\n\tInsira um numero: ");
                scanf("%d", &valor);
                inserior_no_inicio(&lista, valor);
                break;
            case 2:
                printf("\n\tInsira um numero e um valor de referencia: ");
                scanf("%d%d", &valor, &anterior);
                inserir_no_meio(&lista, valor, anterior);
                break;
            case 3:
                printf("\n\tInsira um numero: ");
                scanf("%d", &valor);
                inserir_no_fim(&lista, valor);
                break;
            case 4:
                imprimir(lista); //precisa apenas passar o endereço ao primeiro NO, como já é ponteiro
                                 // basta passar o conteudo do ponteiro lista
                break;
            case 5:
                printf("\n\tInsira um numero: ");
                scanf("%d", &valor);
                removido = remover(&lista, valor);
                if(removido){
                    printf("\n\tElemento %d removido.\n", removido->valor);
                    free(removido); //de fato foi removido da lista
                }
                break;
            case 6:
                puts("\n\tDigite um valor a ser buscado: ");
                scanf("%d", &valor);
                removido = buscar(&lista, valor);
                if(removido)
                    printf("\n\tElemento encontrado: %d\n", removido->valor);
                else
                    puts("Elemento nao encontrado!\n");
                break;
            default:
                if(opcao != 0)
                    printf("\n\tOpcao Invalida\n");
        }


    }while (opcao != 0);

    return 0;
}