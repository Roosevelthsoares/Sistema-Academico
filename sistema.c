#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int Codigo[5+1];
    char Nome[50];
    char Cpf[11+1];
} ALUNO;

typedef struct {
    char Codigo[4];
    char Nome[30];
    char Professor[50];
    char Creditos;
} DISCIPLINA;

typedef struct no{
    //int valor;
    ALUNO aluno;
    struct no *proximo;
}No_aluno;

void inserir_aluno(No_aluno **lista, ALUNO al){ //lista será criado em main
    No_aluno *aux, *novo = malloc(sizeof(No_aluno)); //alocacao de memoria para NOVO NÓ
    int i = 0;

    if(novo){
        novo->aluno = al;
        novo->proximo = NULL; //final na lista

        //é o primeiro? na primeira vez esse nó será o primeiro nó da fila
        if(*lista == NULL) //verificar se a fila é vazia
            *lista = novo;
        else{
            aux = *lista; //percorrer toda a lista
            while(aux->proximo){
                aux = aux->proximo;
                i++;
                printf("%d", &i);
            }
            aux->proximo = novo; //quando PROXIMO for NULL
        }
    }else
        printf("Erro na alocacao de memoria\n");
}

No_aluno* remover_aluno(No_aluno **lista, int num){
    No_aluno *aux, *remover = NULL;

    if(*lista){ //verificar se a lista é nula
        if((*lista)->aluno.Codigo == num){ //no que quero remover é o primeiro da lista //o conteudo desta posição é igual ao que estou procurando?
            remover = *lista; //remove o primeiro nó da lista
            *lista = remover->proximo; //o primeiro nó da lista passa a ser o próximo
        }
        else{ //se não for o primeito nó, percerre-se a lista procurando
            aux = *lista; //preserva o prieiro nó da lista
            while(aux->proximo && aux->proximo->aluno.Codigo != num)
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

No_aluno* buscar_aluno(No_aluno **lista, int num){
    No_aluno *aux, *no = NULL;

    aux = *lista;
    while(aux && aux->aluno.Codigo != num)
        aux = aux->proximo;
    if(aux)
        no = aux;
    return no;
}

void imprimir(No_aluno *no){
    while(no){
        
           
        printf(" %s | ", no->aluno.Codigo);
        printf("%s | ", no->aluno.Cpf);
        printf("%s\n", no->aluno.Nome);
        no = no->proximo; //percorrer a listar
    }
    printf("\n\n");

}

void limpar_tela(){
    #ifdef _linux_
        system("clear");
    #elif _WIN32
        system("cls");
    #else

    #endif
}

void main()
{
    ALUNO CG;
    No_aluno *removido, *lista_aluno = NULL;

    int opcao, op_aluno, codigo;
    char op_remover[6];
    do{
        puts("\t*** Sistema de Matriculas ***");
        puts("\tEscolha a opcao desejada:\n");
        puts("\t1 - Aba Aluno\n");
        puts("\t2 - Aba Disciplina\n");
        puts("\t3 - Aba Matricula\n");
        puts("\t4 - Sair do programa\n");
        scanf ("%d", &opcao);
        limpar_tela();

    switch (opcao)
    {
    case 1:
        do{
            puts("\tAba Aluno:\n");
            puts("\t1 - Inserir Aluno");
            puts("\t2 - Consultar Lista de Alunos");
            puts("\t3 - Remover Aluno");
            puts("\t4 - Voltar ao menu anterior");
            puts("\t5 - Buscar Aluno");
            scanf("%d", &op_aluno);
            fflush(stdin);
            limpar_tela();

            switch (op_aluno){
            case 1:
                puts("\tDigite seu Codigo:\n");
                gets(CG.Codigo);
                fflush(stdin);
                limpar_tela();
                puts("\tDigite seu Nome:\n");
                gets(CG.Nome);
                fflush(stdin);
               // gets(CG.Nome);
                limpar_tela();
                puts("\tDigite seu CPF:\n");
                gets(CG.Cpf);
                fflush(stdin);
                //gets(CG.Cpf);
                limpar_tela();
                inserir_aluno(&lista_aluno, CG); //não esquecer do ENDEREÇO
                
                printf("\tCodigo: %s\n", CG.Codigo);
                printf("\tNome: %s\n", CG.Nome);
                printf("\tCPF: %s\n", CG.Cpf);

                printf("\n\n");
                
                break;            
            case 2:
                printf("\n\tLista de Alunos:\n");
                puts("Codigo |     CPF     | Nome\n");
                imprimir(lista_aluno);

                break; 
            case 3:
                printf("\n\tLista de Alunos:\n");
                puts("Codigo |     CPF     | Nome\n");
                imprimir(lista_aluno);
                puts("\n\tInsira o Codigo do Aluno que deseja remover:\n");
                //gets(CG.Codigo);
                scanf("%d", &codigo);
                removido = remover_aluno(&lista_aluno,codigo);
                if(removido){
                    puts("\tAluno removido\n");
                    free(removido);
                }
                limpar_tela();
                    
                break;            
            case 4:
                break;            
            case 5:
                printf("\n\tLista de Alunos:\n");
                puts("Codigo |     CPF     | Nome\n");
                imprimir(lista_aluno);
                puts("\n\tInsira o Codigo do Aluno que deseja buscar:\n");
                //gets(CG.Codigo);
                scanf("%d", &codigo);
                removido = buscar_aluno(&lista_aluno,codigo);
                if(removido){
                      printf("\n\tElemento encontrado: %d\n", removido->aluno.Codigo);
                }else
                    puts("Elemento nao encontrado!\n");
        
                break;            
            default:
                puts("\tOpcao invalida\n");
                limpar_tela();
                break;
            }

        } while(op_aluno != 4);
        break;
    case 2:
            puts("\tAba Disciplina:\n");
            puts("\t1 - Inserir Disciplina");
            puts("\t2 - Remover Disciplina");
            puts("\t3 - Consultar Lista de Disciplina");
            puts("\t4 - Voltar ao menu anterior");
            scanf("%d", op_aluno);
            limpar_tela();
        break;
    case 3:
            puts("\tAba Matricula:\n");
            puts("\t1 - Matricular Aluno em Disciplina");
            puts("\t2 - Exibir Matriculas existentes");
            puts("\t3 - Listar Disciplinas de Aluno por Matricula");
            puts("\t4 - Listar Alunos de Disciplina por Matricula");
            puts("\t5 - Remover Matricula de Aluno em Disciplina");
            puts("\t6 - Voltar ao menu anterior");
            scanf("%d", op_aluno);
            limpar_tela();
        break;
    case 4:
        //função salvar arquivos
        puts("\tArquivos salvo com sucesso!");
        break;
        
    default:
        puts("\tOpcao invalida\n");
        limpar_tela();
        break;
    }



    }while(opcao != 4);
}