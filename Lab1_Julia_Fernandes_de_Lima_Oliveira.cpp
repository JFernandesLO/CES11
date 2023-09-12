/* Julia Fernandes de Lima Oliveira */
/* Turma 3 */
/* Exercício 1: Torre de Controle */
/* Programa compilado com Visual Studio Code 6.3.0 */

// Instituto Tecnológico de Aeronáutica
// CES-11: Algoritmos e Estruturas de Dados
// Prof. Armando
// agosto de 2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* declarando a struct noh */
typedef struct airport noh;

/*--------------------------------------------------*/

/* struct que ira guardar as informacoes de cada voo como o pedido, o numero, a cidade de origem e o ponteiro para a proxima struct */
struct airport
{
    char message[30];
    int flight;
    char city[30];
    noh *next;
};

/*--------------------------------------------------*/

/* funcao que cria a lista conforme le o arquivo de entrada */
void createList(FILE* input, FILE* output)
{
    /* declaracao de ponteiros para struct */

    /* recebe e aponta para o primeiro elemento da lista */
    noh *head = NULL;
    /* recebe todo novo elemento a partir do momento em que a lista ja tem pelo menos um elemento */
    noh *newEl = NULL;
    /* ponteiro auxiliar para procurar elementos dentro da lista */
    noh *p = NULL;
    /* recebe todo novo chamado de urgencia */
    noh *urgNew = NULL;
    /* aponta para o ultimo elemento que pediu urgencia */
    noh *urgEnd = NULL;
    /* ponteiro auxiliar para a troca de posição de elementos na lista */
    noh *aux = NULL;

    /* leitura da linha 8 do arquivo de entrada, excepcionalmente armazenado em newEl */
    newEl = (noh*)malloc(sizeof(noh)); 
    fscanf(input, "%s %d ", newEl->message, &newEl->flight);
    fgets(newEl->city, sizeof(newEl->city), input);
    newEl->next = NULL;

    /* loop que roda ate que se leia "fim" do arquivo */
    while(strcmp(newEl->message, "FIM"))
    {
        /* se a lista esta vazia a leitura e armazenamento sao feitos em head */
        if(head == NULL)
        {
            head = (noh*)malloc(sizeof(noh));
            fscanf(input, "%s %d ", head->message, &head->flight);
            fgets(head->city, sizeof(head->city), input);
            head->next = NULL;

            /* se em head->message se le pista liberada nao ha avioes na fila para pousar */
            if(strcmp(head->message, "pista_liberada") == 0)
            {
                fprintf(output, "0000\tNenhum aviao pousando\n");
                free(head);
                head = NULL;
            }
            
            /* correcao para o caso de head ler a linha com "FIM" */
            else if(strcmp(head->message, "FIM") == 0)
            {
                newEl = head;
            }
        }

        /* se ja ha na lista pelo menos um aviao, os proximos elementos serao lidos em newEl */
        else
        {
            newEl = (noh*)malloc(sizeof(noh)); 
            fscanf(input, "%s %d ", newEl->message, &newEl->flight);
            fgets(newEl->city, sizeof(newEl->city), input);
            newEl->next = NULL;

            /* insercao de novo elemento na lista, apos o ultimo elemento */
            if(strcmp(newEl->message, "pede_pouso") == 0)
            {
                p = head;
                while(p->next != NULL)
                {
                    p = p->next;
                }
                p->next = newEl;
            }

            /* printa o primeiro elemento da lista */
            else if(strcmp(newEl->message, "pista_liberada") == 0)
            {
                fprintf(output, "%04d\t", head->flight);
                fputs(head->city, output);

                /* se so ha um elemento na lista, apos o printf a lista estara vazia */
                if(head->next == NULL)
                {
                    free(head);
                    head = NULL;
                }

                /* caso contrario, o segundo elemento se torna o primeiro */
                else
                {
                    /* se o ultimo aviao a pedir urgencia for o primeiro elemento da fila */
                    if(urgEnd == head)
                    {
                        urgEnd = NULL;
                    }

                    p = (noh*)malloc(sizeof(noh));
                    p = head;
                    head = head->next;
                    free(p);
                }
            }

            /* caso se leia uma urgencia a ordem da lista e alterada */
            else if(strcmp(newEl->message, "URGENCIA") == 0)
            {
                /* caso o aviao a pedir urgencia nao seja o primeiro elemento da fila */
                if(newEl->flight != head->flight)
                {
                    urgNew = head;
                    /* loop para encontrar qual o elemento de dentro da lista que pediu urgencia */
                    while(urgNew->flight != newEl->flight)
                    {
                        urgNew = urgNew->next;
                    }
                    p = head;

                    /* loop para encontrar o elemento anterior ao que pediu urgencia, e em seguida, esse elemento passa a apontar para o proximo depois da urgencia */
                    while(p->next != urgNew)
                    {
                        p = p->next;
                    }
                    p->next = urgNew->next;

                    /* se so ha uma urgencia ele e levado para o inicio da fila */
                    if(urgEnd == NULL)
                    {
                        urgEnd = urgNew;
                        aux = head;
                        urgNew->next = aux;
                        head = urgNew;
                    }

                    /* se ha mais de uma, o primeiro a pedir urgencia continua em primeiro e assim sucessivamente */
                    else
                    {
                        aux = urgEnd->next;
                        urgNew->next = aux;
                        urgEnd->next = urgNew;
                        urgEnd = urgNew;
                    }
                }
                /* caso o aviao a pedir urgencia ja seja o primeiro elemento da fila */
                else
                {
                    urgEnd = head;
                }
            }
        }
    }

    /* printa a situacao final da fila e desaloca a memoria */
    fprintf(output, "\nSituacao da fila\n\n");
    p = head;
    
    /* caso a situacao final da fila seja fila vazia */
    if(p->flight == 0)
    {
        fprintf(output, "Fila vazia!");
    }

    /* caso a fila nao esteja vazia */
    else{
        while(p != NULL)
        {
            fprintf(output, "%04d\t", p->flight);
            fputs(p->city, output);
            p = p->next;
            free(head);
            head = p;
        }
    }
}

/*--------------------------------------------------*/

int main()
{
    /* declarando as variaveis para a abertura do arquivo de entrada e um vetor para char para descartar as primeiras linhas */
    FILE* input;
    FILE* output;
    char line[70];
    /* variavel para contar as linhas descartadas */   
    int i = 0; 

    /* abrindo o arquivo de entrada em modo leitura */
    input = fopen("entrada1.txt", "r");

    /* criando o arquivo de saida */
    output = fopen("Lab1_Julia_Fernandes_de_Lima_Oliveira.txt", "w");
    
    /* testando para saber se a leitura e criacao dos arquivos funcionou */
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

    /* descartando as 7 primeiras linhas */
    for( ; i < 7; i++)
    {
        fgets(line, sizeof(line), input);
    }

    /* printando o cabecalho no arquivo de saida */
    fprintf(output, "Saint Joseph of the Fields International Airport\n05 Sep Thu 16:00\nAUTORIZACOES DE POUSO\n");
    fprintf(output, "=========================================\n");
    fprintf(output, "FLIGHT\tFROM\n\n");
    
    /* chamando a funcao criada */
    createList(input, output);

    /* fechando os arquivos */
    fclose(input);
    fclose(output);
}
