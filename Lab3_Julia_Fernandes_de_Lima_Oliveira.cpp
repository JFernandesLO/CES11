/* Julia Fernandes de Lima Oliveira */
/* Turma 3 */
/* Exercício 3: Ordenação */
/* Programa compilado com Visual Studio Code 6.3.0 */

// Instituto Tecnológico de Aeronáutica
// CES-11: Algoritmos e Estruturas de Dados
// Prof. Armando
// setembro de 2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* funcao fornecida pelo professor que compara duas strings e adiciona um no contador toda vez que eh chaamda */
int compare(char *a, char *b, int *count){
    (*count)++;
    return strcmp(a, b);
}

/*------------------------------------------------------------------------------------------------*/

/* algoritmo bubble sort que comeca no inicio e vai comparando ate encontrar o maior valor, colocando esse valor na ultima posicao */
void BubbleSort(char** bubble, int numberOfStrings, int *countB)
{
    int i = 0;
    int j = 0;
    for( ; i < numberOfStrings - 1; i++)
    {
        for(j = 0; j < numberOfStrings - i - 1; j++)
        {
            if(compare(bubble[j], bubble[j + 1], countB) > 0)
            {
                char* aux = bubble[j];
                bubble[j] = bubble[j + 1];
                bubble[j + 1] = aux;
            }
        }
    }
}

/*------------------------------------------------------------------------------------------------*/

/* funcao merge do algoritmo merge sort fornecido pelo professor e adaptado para ordenar strings */
void Merge(char** merge, int head, int end, int numberOfStrings, int *countM, char** temp)
{
    /* valor arredondado correspondente a posicao na metade do vetor */
    int mid = (head + end) / 2;
    /* percorre temp */
    int i = head;
    /* percorre lado esquerdo de merge */
    int j = head;
    /* percorre lado direito de merge */
    int k = mid + 1;

    /* percorrer selecionando os menores */
    while(j <= mid && k <= end)
    {
        if(compare(merge[j], merge[k], countM) <= 0)
        {
            temp[i] = merge[j];
            j++;
        }
        else
        {
            temp[i] = merge[k];
            k++;
        }
        i++;
    }
    
    /* se sobrou algo a esquerda copiar para temp */
    while(j <= mid)
    {
        temp[i]= merge[j];
        i++;
        j++;
    }

    /* se sobrou algo a direita copiar para temp */
    while(k <= end)
    {
        temp[i] = merge[k];
        i++;
        k++;
    }

    /*merge recebe temp */
    for(i = head; i <= end; i++)
    {
        merge[i] = temp[i];
    }
}

/*------------------------------------------------------------------------------------------------*/

/* funcao mergesort fornecida pelo professor */
void MergeSort(char** merge, int head, int end, int numberOfStrings, int *countM, char** temp){
    int mid;
    if(head < end)
    {
        /* dividir ao meio */
        mid = (head + end) / 2;      
        /* ordenar a esquerda */    
        MergeSort(merge, head, mid, numberOfStrings, countM, temp);
        /* ordenar a direita */  
        MergeSort(merge, mid + 1, end, numberOfStrings, countM, temp);  
        /* mesclar as duas metades */
        Merge(merge, head, end, numberOfStrings, countM, temp);  
    }
}

/*------------------------------------------------------------------------------------------------*/

/* funcao partition do algoritmo quick sort fornecido pelo professor e adaptado para ordenar strings*/
int Partition(char** quick, int head, int end, int *countQ){
    int left = head + 1;
    int rght = end;
    char* pvt = (char*)malloc(50 * sizeof(char));
    char* aux;

    /* pivo eh escolhido como a primeira linha da matriz */
        strcpy(pvt, quick[head]);

    do
    {
        /* percorrer da esquerda para a direita e encontrar alguem >= pivo */
        while((left < end) && (compare(quick[left], pvt, countQ) < 0))
        {
            left++;
        }
        /* percorrer da direita para a esquerda e encontrar alguem < pivo */
        while((rght > head) && (compare(quick[rght], pvt, countQ) >= 0))
        {
            rght--;
        }
        /* se achou um a esquerda e outro a direita trocar */
        if(left < rght){
            aux = quick[left];
            quick[left] = quick[rght];
            quick[rght] = aux;
        }
        /* caso contrario terminar a repeticao */
    } while(left < rght);
    
    quick[head] = quick[rght];
    strcpy(quick[rght], pvt);

    free(pvt);

    return rght;
}

/*------------------------------------------------------------------------------------------------*/

void QuickSort(char** quick, int head, int end, int *countQ)
{
    /* posicao do pivo */
    int pvt;
    if(end > head)
    {
        pvt = Partition(quick, head, end, countQ);
        QuickSort(quick, head, pvt - 1,countQ);
        QuickSort(quick, pvt + 1, end, countQ);
    }
}

/*------------------------------------------------------------------------------------------------*/

int main(){
    /* declaracao dos ponteiros para arquivos */
    FILE* input;
    FILE* outputBubble;
    FILE* outputMerge;
    FILE* outputQuick;

    /* variavel para guardar cada linha do arquivo de entrada*/
    char line[60];

    /* abrindo o arquivo de entrada em modo leitura */
    input = fopen("entrada3.txt", "r");

    /* criando os arquivos de saida */
    outputBubble = fopen("Lab3_Julia_Fernandes_de_Lima_Oliveira_bubble.txt", "w");
    outputMerge = fopen("Lab3_Julia_Fernandes_de_Lima_Oliveira_merge.txt", "w");
    outputQuick = fopen("Lab3_Julia_Fernandes_de_Lima_Oliveira_quick.txt", "w");

    /* testando para saber se a leitura e criacao dos arquivos funcionaram */
    if(input == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        exit(1);
    }
    if(outputBubble == NULL)
    {
        printf("Erro ao criar o arquivo de BubbleSort!");
        exit(1);
    }
    if(outputMerge == NULL)
    {
        printf("Erro ao criar o arquivo de MergeSort!");
        exit(1);
    }
    if(outputQuick == NULL)
    {
        printf("Erro ao criar o arquivo de QuickSort!");
        exit(1);
    }

    /* lendo a primeira linha do arquivo com o numero de strings e armazenando em numberOfStrings */
    int numberOfStrings = 0;
    fgets(line, sizeof(line), input);
    sscanf(line, "%d", &numberOfStrings);

    /* criacao das matrizes para o bubble, merge e quick em que cada linha eh uma string e cada caracter da string eh armazenado em uma coluna */
    char** bubble = (char**)malloc(numberOfStrings * sizeof(char*));
    char** merge = (char**)malloc(numberOfStrings * sizeof(char*));
    char** quick = (char**)malloc(numberOfStrings * sizeof(char*));
    /* matriz temporaria para uso na funcao merge */
    char** temp = (char**)malloc(numberOfStrings * sizeof(char*));

    /* variavel para contar as linhas */   
    int i = 0;
    for( ; i < numberOfStrings; i++)
    {
        /* leitura das linhas da entrada */
        fgets(line, sizeof(line), input);
        
        /* alocando memoria para as matrizes */
        bubble[i] = (char*)malloc((strlen(line) + 2) * sizeof(char));
        merge[i] = (char*)malloc((strlen(line) + 2) * sizeof(char));
        quick[i] = (char*)malloc((strlen(line) + 2) * sizeof(char));
        temp[n] = (char*)malloc((strlen(line) + 2) * sizeof(char));
        
        strcpy(bubble[i], line);
        strcpy(merge[i], line);
        strcpy(quick[i], line);
    }

    /* variaveis para contar o numero de comparacoes feitas em cada algoritmo B, M e Q para Bubble, Merge e Quick Sort*/
    int countB = 0; 
    int countM = 0;
    int countQ = 0;

    /* declarando as variaveis para a contagem do tempo de cada algoritmo seguindo a memsa nomenclatura anterior de B, M e Q */
    clock_t startB, endB, startM, endM, startQ, endQ;
    float delta_tB, delta_tM, delta_tQ;

    /* o tempo eh iniciado, a funcao eh chamada e calcula-se o tempo total gasto por cada algoritmo, em seguida essas informacoes sao printadas nos arquivos de saida conforme pedido */
    startB = clock();
    BubbleSort(bubble, numberOfStrings, &countB);
    endB = clock();
    delta_tB = (endB - startB) / (float) CLOCKS_PER_SEC;
    
    fprintf(outputBubble, "Algoritmo: Bubble-Sort\n\nTamanho da entrada: %d\nComparações feitas: %d\n", numberOfStrings, countB);
    fprintf(outputBubble,"Tempo de execução: %f segundos\n\n--------------------------------------------------\n", delta_tB);

    startM = clock();
    MergeSort(merge, 0, numberOfStrings - 1, numberOfStrings, &countM, temp);
    endM = clock();
    delta_tM = (endM - startM) / (float) CLOCKS_PER_SEC;

    fprintf(outputMerge, "Algoritmo: Merge-Sort\n\nTamanho da entrada: %d\nComparações feitas: %d\n", numberOfStrings, countM);
    fprintf(outputMerge,"Tempo de execução: %f segundos\n\n--------------------------------------------------\n", delta_tM);

    startQ = clock();
    QuickSort(quick, 0, numberOfStrings - 1, &countQ);
    endQ = clock();
    delta_tQ = (endQ - startQ) / (float) CLOCKS_PER_SEC;

    fprintf(outputQuick, "Algoritmo: Quick-Sort\n\nTamanho da entrada: %d\nComparações feitas: %d\n", numberOfStrings, countQ);
    fprintf(outputQuick,"Tempo de execução: %f segundos\n\n--------------------------------------------------\n", delta_tQ);

    /* por fim, as strings sao escritas em ordem alfabetica em cada um dos arquivos e a memoria eh desalocada */
    int k = 0;
    int l = 0;
    for( ; k < numberOfStrings; k++)
    {
        for(l = 0; l < length[k]; l++)
        {
            fprintf(outputBubble, "%c", bubble[k][l]);
            fprintf(outputMerge, "%c", merge[k][l]);
            fprintf(outputQuick, "%c", quick[k][l]);
        }
        fprintf(outputBubble, "\n");
        fprintf(outputMerge, "\n");
        fprintf(outputQuick, "\n");
    }

    for (k = 0; k < numberOfStrings; k++) {
        free(bubble[k]);
        free(merge[k]);
        free(quick[k]);
        free(temp[k]);
    }

    free(bubble);
    free(merge);
    free(quick);
    free(temp);
    
    fclose(input);
    fclose(outputBubble);
    fclose(outputMerge);
    fclose(outputQuick);
    
    return 0;
}

