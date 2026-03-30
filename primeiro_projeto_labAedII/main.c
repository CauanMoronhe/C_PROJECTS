#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

void troca(char **valor1, char **valor2);
int particao(char **arr, int menorValor, int maiorValor);
void quicksort(char **arr, int menorValor, int maiorValor);

int main()
{
    FILE *arquivo1, *arquivo2;
    char linha[100];
    char **filmes = NULL;
    int contador = 0;
    int capacidade = 100;
    time_t inicio, fim;
    float diferenca;
    struct tm *tempoInicial, *tempoFinal;

    printf("Realizando leitura de filmes em um arquivo...\n");

    printf("\n=============================================\n\n");

    filmes = malloc(capacidade * sizeof(char*));
    if (!filmes)
    {
        printf("Sem memoria para alocacao!\n\n");
        return 1;
    }

    arquivo1 = fopen("filmes.txt", "r");
    if (arquivo1 == NULL)
    {
        printf("Erro abrir o arquivo!\n\n");
        free(filmes);
        exit(1);
    }

    arquivo2 = fopen("logs.txt", "wt");
    if (arquivo2 == NULL)
    {
        printf("Erro! O arquivo logs nao foi criado!\n\n");
        exit(1);
    }
    fprintf(arquivo2, "Logs de Operacoes do Sistema\n");

    while(!feof(arquivo1))
    {
        fgets(linha, sizeof(linha), arquivo1);
        linha[strcspn(linha, "\n")] = '\0';
        printf("Filme = %s\n", linha);

        if (contador >= capacidade)
        {
            capacidade = capacidade + 10;
            filmes = realloc(filmes, capacidade * sizeof(char*));
            if (filmes == NULL)
            {
                printf("Sem memoria para realocacao!\n\n");
                fclose(arquivo1);
                exit(1);
            }
        }

        filmes[contador] = malloc((strlen(linha) + 1) * sizeof(char));
        if (filmes[contador] == NULL)
        {
            printf("Sem memoria para armazenamento de um nome!\n\n");
            fclose(arquivo1);
            return 1;
        }
        strcpy(filmes[contador], linha);
        contador++;

        fprintf(arquivo2, "=======================================\n");

        fprintf(arquivo2, "Filme = %s\n", linha);

        inicio = time(NULL);
        time(&inicio);
        tempoInicial = localtime(&inicio);
        fprintf(arquivo2, "Inicio = %s", asctime(tempoInicial));

        fim = time(NULL);
        time(&fim);
        tempoFinal = localtime(&fim);

        diferenca = difftime(fim, inicio);

        fprintf(arquivo2, "Tempo de execucao = %.6f segundos\n", diferenca);
        fprintf(arquivo2, "Fim = %s", asctime(tempoFinal));
    }
    fclose(arquivo1);

    printf("\n=============================================\n\n");

    printf("filmes ordenados com quicksort...\n");

    printf("\n=============================================\n\n");

    quicksort(filmes, 0, contador -1);

    for(int i = 0; i < contador; i++)
    {
        printf("%d: %s\n", i+1, filmes[i]);

        fprintf(arquivo2, "=======================================\n");

        fprintf(arquivo2, "Filme = %s\n", filmes[i]);

        inicio = time(NULL);
        time(&inicio);
        tempoInicial = localtime(&inicio);
        fprintf(arquivo2, "Inicio = %s", asctime(tempoInicial));

        fim = time(NULL);
        time(&fim);
        tempoFinal = localtime(&fim);

        diferenca = difftime(fim, inicio);

        fprintf(arquivo2, "Tempo de execucao = %.6f segundos\n", diferenca);
        fprintf(arquivo2, "Fim = %s", asctime(tempoFinal));
    }

    fclose(arquivo2);

    for(int i = 0; i < contador; i++)
    {
        free(filmes[i]);
    }
    free(filmes);

    printf("\n=============================================\n\n");

    printf("Quantidade de filmes lidos do arquivo = %d\n", contador);

    return 0;
}

void swap(char **valor1, char **valor2)
{
    char *aux = *valor1;
    *valor1 = *valor2;
    *valor2 = aux;
}

int particao(char **arr, int menorValor, int maiorValor)
{
    char *pivo = arr[maiorValor];
    int i = (menorValor - 1);

    for (int j = menorValor; j <= maiorValor - 1; j++)
    {
        if (strcmp(arr[j], pivo) <= 0)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[maiorValor]);
    return (i + 1);
}

void quicksort(char **arr, int menor, int maior)
{
    if (menor < maior)
    {
        int pi = particao(arr, menor, maior);
        quicksort(arr, menor, pi - 1);
        quicksort(arr, pi + 1, maior);
    }
}
