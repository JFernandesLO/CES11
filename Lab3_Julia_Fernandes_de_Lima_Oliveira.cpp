#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int compare(char *a, char *b, int *count){
    (*count)++;
    return strcmp(a, b);
}

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

void Merge(char** merge, int head, int end, int numberOfStrings, int* length, int *countM)
{
    int mid, i, j, k;     
    mid = (head + end) / 2;
    j = head;
    int n = 0;
    k = mid + 1;
    i = head;
    char** temp = (char**)malloc(numberOfStrings * sizeof(char*));
    for( ; n < numberOfStrings; n++)
    {
        temp[n] = (char*)malloc(50 * sizeof(char));
    }
    while(j <= mid && k <= end)
    {
        if(compare(merge[j], merge[k], countM) <= 0)
        {
            for(n = 0; n < length[j]; n++)
            {
                temp[i][n] = merge[j][n];
            }
            j++;
        }
        else
        {
            for(n = 0; n < length[k]; n++)
            {
                temp[i][n] = merge[k][n];
            }
            k++;
        }
        i++;
    }
    while(j <= mid)
    {
        for(n = 0; n < length[j]; n++)
        {
            temp[i][n] = merge[j][n];
        }
        i++;
        j++;
    }

    while(k <= end)
    {
        for(n = 0; n < length[k]; n++)
        {
            temp[i][n] = merge[k][n];
        }
        i++;
        k++;
    }
    for(i = head; i <= end; i++)
    {
        for(n = 0; n < length[i]; n++){
            merge[i][n] = temp[i][n];
        }
    }
    for (n = 0 ; n < numberOfStrings; n++) {
        free(temp[n]);
    }
    free(temp);
}

void MergeSort(char** merge, int head, int end, int numberOfStrings, int* length, int *countM){
    int mid;
    if(head < end)
    {
        mid = (head + end) / 2;          
        MergeSort(merge, head, mid, numberOfStrings, length, countM);  
        MergeSort(merge, mid + 1, end, numberOfStrings, length, countM);  
        Merge(merge, head, end, numberOfStrings, length, countM);  
    }
}

int Partition(char** quick, int head, int end, int* length, int *countQ){
    int left = head + 1;
    int rght = end;
    char* pvt = (char*)malloc(50 * sizeof(char));
    char* aux;
    int i = 0;
    for( ; i < length[head]; i++)
    {
        pvt[i] = quick[head][i];
    }
    do
    {
        while((left < end) && (compare(quick[left], pvt, countQ) < 0))
        {
            left++;
        }
        while((rght > head) && (compare(quick[rght], pvt, countQ) >= 0))
        {
            rght--;
        }
        if(left < rght){
            aux = quick[left];
            quick[left] = quick[rght];
            quick[rght] = aux;
        }
    } while(left < rght);
    
    aux = quick[head];
    quick[head] = quick[rght];
    quick[rght] = aux;
    free(pvt);
    return rght;
}

void QuickSort(char** quick, int head, int end, int* length, int *countQ)
{
    int pvt;
    if(end > head)
    {
        pvt = Partition(quick, head, end, length, countQ);
        QuickSort(quick, head, pvt - 1, length, countQ);
        QuickSort(quick, pvt + 1, end, length, countQ);
    }
}

int main(){
    FILE* input;
    FILE* outputBubble;
    FILE* outputMerge;
    FILE* outputQuick;

    char line[60];

    /* abrindo o arquivo de entrada em modo leitura */
    input = fopen("entrada3.txt", "r");

    /* criando os arquivos de saida */
    outputBubble = fopen("Lab3_Julia_Fernandes_de_Lima_Oliveira_bubble.txt", "w");
    outputMerge = fopen("Lab3_Julia_Fernandes_de_Lima_Oliveira_merge.txt", "w");
    outputQuick = fopen("Lab3_Julia_Fernandes_de_Lima_Oliveira_quick.txt", "w");

    /* testando para saber se a leitura e criacao dos arquivos funcionou */
    if(input == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        exit(1);
    }
    if(outputBubble == NULL)
    {
        printf("Erro ao criar o arquivo Bubble!");
        exit(1);
    }
    if(outputMerge == NULL)
    {
        printf("Erro ao criar o arquivo Merge!");
        exit(1);
    }
    if(outputQuick == NULL)
    {
        printf("Erro ao criar o arquivo Quick!");
        exit(1);
    }

    int numberOfStrings = 0;
    fgets(line, sizeof(line), input);
    sscanf(line, "%d", &numberOfStrings);
    char** bubble = (char**)malloc(numberOfStrings * sizeof(char*));
    char** merge = (char**)malloc(numberOfStrings * sizeof(char*));
    char** quick = (char**)malloc(numberOfStrings * sizeof(char*));
    int* length = (int*)malloc((numberOfStrings + 2) * sizeof(int));

    /* variavel para contar as linhas */   
    int i = 0;
    for( ; i < numberOfStrings; i++)
    {
        bubble[i] = (char*)malloc(50 * sizeof(char));
        merge[i] = (char*)malloc(50 * sizeof(char));
        quick[i] = (char*)malloc(50 * sizeof(char));
        fgets(line, sizeof(line), input);
        
        int n = 0;
        while(line[n] != '\n')
        {
            bubble[i][n] = line[n];
            merge[i][n] = line[n];
            quick[i][n] = line[n];
            n++;
        }

        length[i] = n;
    }

    int countB = 0; 
    int countM = 0;
    int countQ = 0;

    clock_t startB, endB, startM, endM, startQ, endQ;
    float delta_tB, delta_tM, delta_tQ;

    startB = clock();
    BubbleSort(bubble, numberOfStrings, &countB);
    endB = clock();
    delta_tB = (endB - startB) / (float) CLOCKS_PER_SEC;
    
    fprintf(outputBubble, "Algoritmo: Bubble-Sort\n\nTamanho da entrada: %d\nComparações feitas: %d\n", numberOfStrings, countB);
    fprintf(outputBubble,"Tempo de execução: %f segundos\n\n--------------------------------------------------\n", delta_tB);

    startM = clock();
    MergeSort(merge, 0, numberOfStrings - 1, numberOfStrings, length, &countM);
    endM = clock();
    delta_tM = (endM - startM) / (float) CLOCKS_PER_SEC;

    fprintf(outputMerge, "Algoritmo: Merge-Sort\n\nTamanho da entrada: %d\nComparações feitas: %d\n", numberOfStrings, countM);
    fprintf(outputMerge,"Tempo de execução: %f segundos\n\n--------------------------------------------------\n", delta_tM);

    startQ = clock();
    QuickSort(quick, 0, numberOfStrings - 1, length, &countQ);
    endQ = clock();
    delta_tQ = (endQ - startQ) / (float) CLOCKS_PER_SEC;

    fprintf(outputQuick, "Algoritmo: Quick-Sort\n\nTamanho da entrada: %d\nComparações feitas: %d\n", numberOfStrings, countQ);
    fprintf(outputQuick,"Tempo de execução: %f segundos\n\n--------------------------------------------------\n", delta_tQ);

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
    }
    free(length);
    free(bubble);
    free(merge);
    free(quick);
    fclose(input);
    fclose(outputBubble);
    return 0;
}
