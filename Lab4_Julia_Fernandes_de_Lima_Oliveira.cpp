/* Julia Fernandes de Lima Oliveira */
/* Turma 3 */
/* Exercício 4: Agenda + Vetor Simples */
/* Programa compilado com Visual Studio Code 6.3.0 */

// Instituto Tecnológico de Aeronáutica
// CES-11: Algoritmos e Estruturas de Dados
// Prof. Armando
// outubro de 2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* declarando a struct agenda */
typedef struct filaPrioridade agenda;

/*------------------------------------------------------------------------------------------------*/

/* struct pedida no enunciado contendo a um vetor com o codigo da tarefa, um vetor de numeros de importancia, a descricao, o numero de elementos no vetor e o numero maximo de tarefas */
struct filaPrioridade
{
    char* tarefa;
    int* importancia;
    char** descricao;
    int numeroElementos;
    int max;
};

/*------------------------------------------------------------------------------------------------*/

/* funcao publica que incializa a lista alocando a memoria necessaria na struct e inicializando o numero de elementos como 0 */
void inicializar(agenda *fila)
{
    fila->tarefa = (char*)malloc(10 * sizeof(char));
    fila->importancia = (int*)malloc((fila->max + 1) * sizeof(int));
    fila->descricao = (char**)malloc((fila->max + 1) * sizeof(char*));

    int j = 0;

    for( ; j < fila->max + 1; j++)
    {
        fila->descricao[j] = (char*)malloc(40 * sizeof(char));
    }

    fila->numeroElementos = 0;
}

/*------------------------------------------------------------------------------------------------*/

/* funcao privada para busca binaria no vetor de importancia */
int buscaBinaria(int n, const agenda *fila, int esq, int dir)
{
    int med;

    while(esq < dir - 1)
    {
        med = (esq + dir) / 2;
        if(n >= fila->importancia[med])
        {
            esq = med;
        }
        else
        {
            dir = med; 
        }
    }

    return dir;
}

/*------------------------------------------------------------------------------------------------*/

/* funcao publica que chama a funcao privada de busca binaria, encontra a posicao e shifta os elementos necessarios para adicionar o novo */
int insert(int novoElemento, agenda *fila)
{
    fila->numeroElementos++;

    int esq = 0;
    int dir = fila->numeroElementos;
    int pos = buscaBinaria(novoElemento, fila, esq, dir);
    int i = fila->numeroElementos;

    for( ; i > pos; i--)
    {
        fila->importancia[i] = fila->importancia[i - 1];
        strcpy(fila->descricao[i], fila->descricao[i-1]);
    }
    fila->importancia[pos] = novoElemento;

    return pos;
}

/*------------------------------------------------------------------------------------------------*/

/* funcao publica que verifica se a fila esta vazia e retorna um bool */
int filaVazia(const agenda *fila)
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
int filaCheia(const agenda *fila)
{
    bool cheia = false;

    if(fila->numeroElementos >= fila->max)
    {
        cheia = true;
    }

    return cheia;
}

/*------------------------------------------------------------------------------------------------*/

/* funcao publica que retorna a posicao do elemento de maior prioridade na fila */
int maximum(const agenda *fila)
{
    int max = fila->numeroElementos;

    return max;
}

/*------------------------------------------------------------------------------------------------*/

/* funcao publica que zera o numero de importancia do elemento de maior prioridade e diminui em uma unidade a quantidade de elementos na lista */ 
void removeMax(agenda *fila, int *max)
{
    fila->importancia[*max] = 0;
    (*max)--;
    fila->numeroElementos--;
}

/*------------------------------------------------------------------------------------------------*/

/* funcao publica que finaliza a lista, desalocando a memoria */
void finalizar(agenda *fila)
{
    int i = 0;

    for( ; i < fila->max + 1; i++)
    {
        free(fila->descricao[i]);
    }
    free(fila->descricao);
    free(fila->importancia);
    free(fila->tarefa);
}

/*------------------------------------------------------------------------------------------------*/

int main()
{
    /* declaracao dos ponteiros para arquivos, abertura da entrada e criacao da saida */
    FILE* input = fopen("entrada4.txt", "r");
    FILE* output = fopen("Lab4_Julia_Fernandes_de_Lima_Oliveira.txt", "w");

    /* declaracao da variavel linha para leitura de linhas do arquivo e da struct da agenda  */
    char line[70];
    agenda fila; 

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

    sscanf(line, "%d", &fila.max);

    for( ; i < 9; i++)
    {
        fgets(line, sizeof(line), input);
    }
    /* variaveis para guardar a importancia do ultimo elemento lido, a posicao desse elemento na fila e o maximo de elementos na fila */
    int novoElemento = 0;
    int pos = 1;
    int max = 0;

    /* escrevendo o cabecalho no arquivo */
    fprintf(output, "Agenda Eletronica\nOrdenacao das atividades por ordem de prioridade\nOUTUBRO 2023\nQuinta-feira, 17\n\n");
    fprintf(output,"--------------------------------------------------\nRESPOSTAS DAS CONSULTAS\n--------------------------------------------------\n");
    
    /* chamando a funcoa inicializar */
    inicializar(&fila);

    /* loop que le as linhas do arquivo ate que se leia "FIM" nas tarefas */
    do
    {
        /* leitura do codigo para a tarefa */
        fscanf(input, "%s", fila.tarefa);

        if(strcmp(fila.tarefa, "NOVA") == 0)
        {
            /* se for lido "NOVA" e a fila estiver cheia isso eh mostrado na saida */
            if(filaCheia(&fila) == true)
            {
                fprintf(output, "ERRO     Ops, a agenda esta cheia :(\n");
            }

            /* se a fila nao estiver cheia le-se o valor da importancia, a funcao insert eh chamada para saber a posicao de insercao e a descricao eh guardada na posicao da fila */
            else
            {
                fscanf(input, "%d ", &novoElemento);
                pos = insert(novoElemento, &fila);
                fgets(line, sizeof(line), input);
                strcpy(fila.descricao[pos], line);
            }

            /* funcao maximum eh chamada para que se guarde o valor do numero de elementos na variavel max */
            max = maximum(&fila);

        }

        else if(strcmp(fila.tarefa, "PROXIMA") == 0)
        {
            /* se for lido "PROXIMA" e a fila estiver vazia isso eh mostrado na saida */ 
            if(filaVazia(&fila) == true)
            {
                fprintf(output, "AVISO    Oba, a agenda esta vazia :)\n");
            }

            /* se a fila nao estiver vazia, chama-se a funcao maximum para se saber o numero de elementos, e esse valor junto com sua descricao eh printado na saida, por ultimo chama-se remove max para remover da lista o valor maximo */
            else
            {
                max = maximum(&fila);
                fprintf(output, "%2d       ", fila.importancia[max]);
                fputs(fila.descricao[max], output);
                removeMax(&fila, &max);
            }
        }

    } while(strcmp(fila.tarefa, "FIM"));

    /* em seguida printa-se as tarefas que irao ficar para o dia seguinte */
    fprintf(output, "\n--------------------------------------------------\nFICA PARA O DIA SEGUINTE\n--------------------------------------------------\n");
    
    /* se nao ha tarefas para o dia seguintes isso eh mostrado na saida */
    if(max == 0)
    {
        fprintf(output, "Agenda vazia, sem tarefas para amanha :)\n");
    }

    /* se existem tarefas elas sao printadas conforme a ordem de prioridade */
    else
    {
        while(max >= 1)
        {
            max = maximum(&fila);
            fprintf(output, "%2d       ", fila.importancia[max]);
            fputs(fila.descricao[max], output);
            removeMax(&fila, &max);
        }
    }
    
    /* finalmente a funcao finalizar eh chamada e os arquivos sao fechados */
    finalizar(&fila);

    fclose(input);
    fclose(output);

    return 0;
}