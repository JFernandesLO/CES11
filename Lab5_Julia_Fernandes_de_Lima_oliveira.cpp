/* Julia Fernandes de Lima Oliveira */
/* Turma 3 */
/* Exercício 5: Agenda Eletronia + Heap */
/* Programa compilado com Visual Studio Code 6.3.0 */

// Instituto Tecnológico de Aeronáutica
// CES-11: Algoritmos e Estruturas de Dados
// Prof. Armando
// novembro de 2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* declarando as structs tarefa e agenda */
typedef struct tarefa tarefa;
typedef struct agenda agenda;

/*------------------------------------------------------------------------------------------------*/

/* struct de cada tarefa que guarda o valor da importancia e a descricao */
struct tarefa
{
    int importancia;
    char descricao[42];
};

/*------------------------------------------------------------------------------------------------*/

/* struct para a fila/agenda que comtem o vetor, o numero de elementos e o valor do maximo */
struct agenda
{
    tarefa* vet;
    int numeroElementos;
    int max;
};

/*------------------------------------------------------------------------------------------------*/

/* funcao publica que incializa a lista alocando a memoria necessaria na struct, inicializando o numero de elementos como 0, e atribuindo o max para o valor lido do arquivo */
void inicializar(agenda *fila, int max)
{
    fila->vet = (tarefa*)malloc((max + 1) * sizeof(tarefa));
    fila->max = max;
    fila->numeroElementos = 0;
}

/*------------------------------------------------------------------------------------------------*/

/* funcao privada que troca dois inteiros */

void trocaImportancia(int *a, int *b)
{
    int aux = 0;
    aux = *a;
    *a = *b;
    *b = aux;
}

/*------------------------------------------------------------------------------------------------*/

/* funcao privada que troca duas strings */
void trocaDescricao(char a[], char b[])
{
    char aux[42];
    strcpy(aux, a);
    strcpy(a, b);
    strcpy(b, aux);
}

/*------------------------------------------------------------------------------------------------*/

/* funcao publica que insere cada novo elemento na posicao final do vetor e vai fazendo as trocas para reestabelecer o balanceamento do heap */
void insert(tarefa tarefa, agenda *fila)
{
    fila->numeroElementos++;
    int i = fila->numeroElementos;
    fila->vet[i].importancia = tarefa.importancia;
    strcpy(fila->vet[i].descricao, tarefa.descricao);

    if(i > 1)
    {
        int pai = i / 2;

        while(fila->vet[pai].importancia < fila->vet[i].importancia)
        {
            trocaImportancia(&fila->vet[i].importancia, &fila->vet[pai].importancia);
            trocaDescricao(fila->vet[i].descricao, fila->vet[pai].descricao);
            i = pai;
            pai = i / 2;
        }
    }
}

/*------------------------------------------------------------------------------------------------*/

/* funcao publica que verifica se a fila esta vazia e retorna um bool */
bool filaVazia(const agenda *fila)
{
    bool vazia = false;

    if(fila->numeroElementos == 0)
    {
        vazia = true;
    }

    return vazia;
}

/*------------------------------------------------------------------------------------------------*/

/* funcao publica que verifica se a fila esta cheia e retorna um bool */
bool filaCheia(const agenda *fila)
{
    bool cheia = false;

    if(fila->numeroElementos >= fila->max)
    {
        cheia = true;
    }

    return cheia;
}

/*------------------------------------------------------------------------------------------------*/

/* funcao publica que retorna a posicao do elemento de maior prioridade na fila, ou seja o primeiro */
void maximum(const agenda *fila, tarefa *tarefa)
{
    tarefa->importancia = fila->vet[1].importancia;
    strcpy(tarefa->descricao, fila->vet[1].descricao);
}

/*------------------------------------------------------------------------------------------------*/

/* funcao recursiva que cpnserta o balanceamento da arvore de heap quando o elemento maximo eh removido */
void balanceamento(agenda *fila, int pai)
{
    int esq = 2 * pai;
    int dir = (2 * pai) + 1;
    int maior = pai;

    if(dir <= fila->numeroElementos && fila->vet[esq].importancia < fila->vet[dir].importancia)
    {
        maior = dir;
    }
    else if(esq <= fila->numeroElementos && fila->vet[dir].importancia <= fila->vet[esq].importancia)
    {
        maior = esq;
    }

    if(fila->vet[maior].importancia > fila->vet[pai].importancia && maior <= fila->numeroElementos)
    {
        trocaImportancia(&fila->vet[maior].importancia, &fila->vet[pai].importancia);
        trocaDescricao(fila->vet[maior].descricao, fila->vet[pai].descricao);
        balanceamento(fila, maior);
    }

}

/* funcao publica que zera coloca o ultimo elemento do vetor na primeira posicao e chama a funcao balanceamento para retomar a ordem correta do heap */ 
void removeMax(agenda *fila)
{
    fila->vet[1].importancia = fila->vet[fila->numeroElementos].importancia;
    strcpy(fila->vet[1].descricao, fila->vet[fila->numeroElementos].descricao);
    fila->vet[fila->numeroElementos].importancia = 0;
    fila->numeroElementos--;

    balanceamento(fila, 1);
}

/*------------------------------------------------------------------------------------------------*/

/* funcao publica que finaliza a lista, desalocando a memoria */
void finalizar(agenda *fila)
{
    free(fila->vet);
}

/*------------------------------------------------------------------------------------------------*/

int main()
{
    /* declaracao dos ponteiros para arquivos, abertura da entrada e criacao da saida */
    FILE* input = fopen("entrada5.txt", "r");
    FILE* output = fopen("Lab5_Julia_Fernandes_de_Lima_Oliveira.txt", "w");

    /* declaracao da variavel linha para leitura de linhas do arquivo, de comando para saber o comando e das structs  */
    char line[70];
    char comando[10];
    agenda fila;
    tarefa tarefa;

    /* variavel para guardar o maximo e o contador de linhas */
    int max = 0;
    int i = 0;

    /* teste para saber se a abertura e criacao funcionaram */
    if(input == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        exit(1);
    }
    if(output == NULL)
    {
        printf("Erro ao criar o arquivo!");
        exit(1);
    }

    /* ignorando as 5 primeiras, lendo o valor do maximo da agenda na sexta linha depois ignorando as 3 linhas seguintes*/
    for( ; i < 6; i++)
    {
        fgets(line, sizeof(line), input);
    }

    sscanf(line, "%d", &max);

    for( ; i < 9; i++)
    {
        fgets(line, sizeof(line), input);
    }

    /* escrevendo o cabecalho no arquivo */
    fprintf(output, "Agenda Eletronica\nOrdenacao das atividades por ordem de prioridade\nNOVEMBRO 2023\nQuarta-feira, 29\n\n");
    fprintf(output,"--------------------------------------------------\nRESPOSTAS DAS CONSULTAS\n--------------------------------------------------\n");
    
    /* chamando a funcoa inicializar */
    inicializar(&fila, max);

    /* loop que le as linhas do arquivo ate que se leia "FIM" nas tarefas */
    do
    {
        /* leitura do codigo para a tarefa */
        fscanf(input, "%s", comando);

        if(strcmp(comando, "NOVA") == 0)
        {
            /* se for lido "NOVA" e a fila estiver cheia isso eh mostrado na saida */
            if(filaCheia(&fila) == true)
            {
                fprintf(output, "ERRO     Ops, a agenda esta cheia :(\n");
            }
            /* se a fila nao estiver cheia le-se o valor da importancia, a funcao insert eh chamada para saber a posicao de insercao e a descricao eh guardada na posicao da fila */
            else
            {
                fscanf(input, "%d ", &tarefa.importancia);
                fgets(tarefa.descricao, sizeof(tarefa.descricao), input);
                insert(tarefa, &fila);
            }

            /* funcao maximum eh chamada para que se guarde o valor do numero de elementos na variavel max */
            maximum(&fila, &tarefa);

        }

        else if(strcmp(comando, "PROXIMA") == 0)
        {
            /* se for lido "PROXIMA" e a fila estiver vazia isso eh mostrado na saida */ 
            if(filaVazia(&fila) == true)
            {
                fprintf(output, "AVISO    Oba, a agenda esta vazia :)\n");
            }

            /* se a fila nao estiver vazia, chama-se a funcao maximum para se saber a importancia maxima, e esse valor junto com sua descricao eh printado na saida, por ultimo chama-se remove max para remover da lista o valor maximo */
            else
            {
                maximum(&fila, &tarefa);
                fprintf(output, "%2d       ", tarefa.importancia);
                fputs(tarefa.descricao, output);
                removeMax(&fila);
            }
        }

    } while(strcmp(comando, "FIM"));

    /* em seguida printa-se as tarefas que irao ficar para o dia seguinte */
    fprintf(output, "\n--------------------------------------------------\nFICA PARA O DIA SEGUINTE\n--------------------------------------------------\n");
    
    /* se nao ha tarefas para o dia seguintes isso eh mostrado na saida */
    if(filaVazia(&fila) == true)
    {
        fprintf(output, "Agenda vazia, sem tarefas para amanha :)\n");
    }

    /* se existem tarefas elas sao printadas conforme a ordem de prioridade */
    else
    {
        while(filaVazia(&fila) == false)
        {
            maximum(&fila, &tarefa);
            fprintf(output, "%2d       ", tarefa.importancia);
            fputs(tarefa.descricao, output);
            removeMax(&fila);
        }
    }
    
    /* finalmente a funcao finalizar eh chamada e os arquivos sao fechados */
    finalizar(&fila);

    fclose(input);
    fclose(output);

    return 0;
}