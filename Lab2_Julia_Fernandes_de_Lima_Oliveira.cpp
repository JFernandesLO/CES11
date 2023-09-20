/* Julia Fernandes de Lima Oliveira */
/* Turma 3 */
/* Exercício 2: Produto de Matrizes */
/* Programa compilado com Visual Studio Code 6.3.0 */

// Instituto Tecnológico de Aeronáutica
// CES-11: Algoritmos e Estruturas de Dados
// Prof. Armando
// setembro de 2023

#include <stdio.h>
#include <stdlib.h>

/* funcao recursiva para calcular o minimo produto das matrizes, retornando esse valor, alem de contar quantas vezes (para a letra a) a funcao foi chamada e preencher os valores para a matriz de cortes (para a letra b) */
int minimum(int i, int j, int** dimensions, int *count, int** cuts)
{
    /* contagem sobre toda vez que a funcao eh chamada */
    (*count)++;
    /* variavel auxiliar k que representa o ponto em que os cortes estao sendo feitos */
    int k = i;
    /* variavel para guardar o valor minimo, que eh inicialmente atribuida para um valor muito alto para nao atrapalhar os calculos */
    int min = 200000000;
    
    /* se i = j o valor e 0 */
    if(i == j)
    {
        return 0;
    }

    /* loop que calcula a soma atraves da recursao da funcao adicionando no final a multiplicacao da primeira linha, com a coluna do corte e com a coluna final */
    for( ; k < j; k++)
    {
        int sum = minimum(i, k, dimensions, count, cuts) + minimum(k + 1, j, dimensions, count, cuts) + (dimensions[i][0] * dimensions[k][1] * dimensions[j][1]);
        
        /* loop que salva o valor do minimo */
        if(min > sum)
        {
            min = sum;
            /* a matriz com os melhores cortes eh preenchida conforme os minimos sao calculados */
            cuts[i][j] = k;
        } 
    }

    /* retorna o valor minimo */
    return min;
}

/*------------------------------------------------------------------------------------------------*/

/* funcao recursiva para printar a ordem em que as multiplicacoes devem ser feitas (parte b) */
void printCuts(int** cuts, int i, int j, FILE* output)
{
    /* variavel auxiliar k que acessa, da matriz de cortes, o valor do melhor corte entre duas matrizes */
    int k = cuts[i][j];

    /* para que a impressao possa ser feita com a ordem certa das multiplicacoes, os melhores cortes vao sendo acessados ate que se tenha no maximo tres matrizes por vez para printar a ordem, por isso o loop que ira chamar a funcao novamente so ira rodar se tiverem mais que tres matrizes */
    if(j - i > 2){
        /* caso o corte foi feito entre mais de tres matrizes a funcao eh chamada novamente para ir diminuindo a quantidade de matrizes entre i e j, alem disso, a funcao eh chamada para a esquerda e para a direita para que todas as multiplicacoes sejam printadas */
        printCuts(cuts, i, k, output);
        printCuts(cuts, k + 1, j, output);
        
        /* tem se abaixo 4 'ifs' para evitar erros na hora da impressao de uma mesma matriz ser printada duas vezes com o '-', portanto se os valores de k + 1 e j sao iguais ou i e k sao iguais, a impressao eh feita sem repetir valores */
        if((k + 1 != j) && (i != k))
        {
            fprintf(output, "%2d- %d x  %d- %d\n", i, k, k+1, j);
        }
        if((k + 1 == j) && (i != k))
        {
            fprintf(output, "%2d- %d x  %d\n", i, k, j);
        }
        if((k + 1 != j) && (i == k))
        {
            fprintf(output, "    %d x  %d- %d\n", i, k+1, j);
        }
        if((k + 1 == j) && (i == k))
        {
            fprintf(output, "    %d x  %d\n", i, j);
        }
    }
    else
    {
        /* esses loops abaixo sao para impressao dos valores para cada pequeno grupo de duas ou tres matrizes */
        if(k == i)
        {
            /* se sao tres matrizes e o corte entre elas eh feito entre a primeira e a segunda, printa-se a segunda vezes a terceira e em seguida a primeira vezes a anterior */
            if(i + 1 != j){
            fprintf(output, "    %d x  %d\n", i + 1, j);
            fprintf(output, "    %d x  %d- %d\n", i, i + 1, j);
            }
            /* se sao duas matrizes elas sao printadas */
            else
            {
            fprintf(output, "    %d x  %d\n", i, j);
            }
        }
        /* se eh um grupo de tres matrizes tambem, e o corte eh feito entre a segunda e a terceira, printa-se a primeira vezes a segunda e em seguida essa vezes a terceira */
        else if(k == i + 1)
        {
            fprintf(output, "    %d x  %d\n", i, i + 1);
            fprintf(output, "%2d- %d x  %d\n", i, i + 1, j);
        }
    }
    
}

/*------------------------------------------------------------------------------------------------*/

int main()
{
    /* declarando as variaveis para a abertura do arquivo de entrada e um vetor para char para descartar as primeiras linhas */
    FILE* input;
    FILE* output;
    char line[70];
    /* variavel para contar as linhas lidas do arquivo */   
    int i = 0; 

    /* abrindo o arquivo de entrada em modo leitura */
    input = fopen("entrada2.txt", "r");

    /* criando o arquivo de saida */
    output = fopen("Lab2_Julia_Fernandes_de_Lima_Oliveira.txt", "w");
    
    /* testando para saber se a leitura e criacao dos arquivos funcionaram*/
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

    /* descartando as 5 primeiras linhas e guardando o valor da 6 linha*/
    for( ; i < 6; i++)
    {
        fgets(line, sizeof(line), input);
    }

    /* impressao das 3 primeiras linhas do arquivo */
    fprintf(output, "Arquivo de saida final\nExercicio 2\nProduto de Matrizes");
    /* declarando uma variavel para saber quantas matrizes serao multiplicadas e lendo da variavel linha esse valor */
    int numberMat = 0;
    sscanf(line, "%d", &numberMat);

    /* criacao de duas matrizes uma que ira guardas as dimensoes de cada matriz e outra para guardar os melhores cortes entre cada matriz */
    int** dimensions = (int**)malloc((numberMat + 1) * sizeof(int*));
    int** cuts = (int**)malloc((numberMat + 1) * sizeof(int*));
    /* variavel para contar quantas vezes a funcao recursiva foi chamada */
    int count = 0;

    /* descartando as duas linhas seguintes */
    for( ; i < 8; i++)
    {
        fgets(line, sizeof(line), input);
    }
    /* declaracao de duas variaveis apenas para os loops */
    int n = 1;
    int m = 1;

    /* loop para alocar memoria para as matrizes e para ler o arquivo e ir guardando as dimensoes das matrizes */
    for( ; n <= numberMat; n++)
    {
        dimensions[n] = (int*)malloc(2 * sizeof(int));
        cuts[n] = (int*)malloc((numberMat + 1) * sizeof(int));
        fgets(line, sizeof(line), input);
        sscanf(line, "%d %d", &dimensions[n][0], &dimensions[n][1]);
        /* loop para atribuir valor inicial de 0 para a matriz de melhores cortes */
        for(m = 1; m <= numberMat; m++)
        {
            cuts[n][m] = 0;
        }
    }

    /* reatibuindo o valor de i para 1 para usa-lo na funcao como a variavel que guarda a matriz inicial para os trechos que serao separados para multiplicacao */
    i = 1;
    /* variavel j ira guardar a matriz final para esses trechos */
    int j = numberMat;

    /* funcao eh chamada o valor retornado por ela e guardado na variavel min */
    int min = minimum(i, j, dimensions, &count, cuts);

    /* impressao do resultado do minimo de multiplicacoes escalares e do numero de chamamentos da funcao recursiva */
    fprintf(output, "\n\nTotal de multiplicacoes escalares = %d\n", min);
    fprintf(output, "\nChamadas da funcao: %d\n", count);
    fprintf(output, "\nMelhor ordem para realizar o produto: \n");

    /* valores de i e j sao ressetados */
    i = 1;
    j = numberMat;

    /* funcao de prints e chamada para se printar a ordem em que as multiplicacoes devem ser feitas */
    printCuts(cuts, i, j, output);
    
    /*fechamento dos arquivos*/
    fclose(input);
    fclose(output);
}