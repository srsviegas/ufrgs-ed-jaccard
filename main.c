/* O programa retorna o coeficiente de similaridade textual entre um texto A e um
texto B, ignorando as palavras dadas por uma lista de stopwords, atravï¿½s do seguinte
algoritmo:

    1. Carrega stopwords em uma AVL

    2. Carrega o texto menor em uma lista e o texto maior em uma AVL, ignorando palavras
    repetidas, stopwords e separadores, enquanto conta len(A) e len(B)

    3. Busca palavras de A em B, contando len(A intersect B)

    4. Retorna sim_tex = len(A intersect B)/(len(A) + len(B)) - 1

*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <ctype.h>

#include "data.h"
#include "jaccard.h"

#define DEBUG 0


int largest_file(char* filename1, char* filename2);


int main(int argc, char *argv[])
{
    int isDebugging = DEBUG;

    if (argc != 4) {
        printf("ERRO: Número incorreto de parâmetros.\n"
        "A chamada deve ser: jaccard <texto1> <texto2> <stopwords>\n");
        return 1;
    }

    setlocale(LC_ALL, "Portuguese");
    clock_t start = clock();

    lst* textoA = NULL;         // TADs para listas de palavras
    AVL* textoB = NULL;
    AVL* stopwords = NULL;

    int lenA = 0;               // Comprimento das listas
    int lenB = 0;

    // Calcula qual dos dois textos é maior
    int largestFile = largest_file(argv[1], argv[2]);
    int smallestFile = (largestFile == 1)? 2: 1;

    // Define a AVL das stopwords
    FILE* file = fopen(argv[3], "r");
    if (!file) {
        printf("ERRO: Não foi possível abrir a lista de stopwords.\n"
        "Nome do arquivo: '%s'", argv[3]);
        return 1;
    }
    stopwords = AVL_from_file_stopwords(file);
    if (isDebugging)
        AVL_print(stopwords);
    fclose(file);

    // Define a lista do menor texto
    file = fopen(argv[smallestFile], "r");
    textoA = lst_from_file(file, &lenA, stopwords);
    if (isDebugging)
        lst_print(textoA);
    fclose(file);

    // Define a AVL do maior texto
    file = fopen(argv[largestFile], "r");
    textoB = AVL_from_file(file, &lenB, stopwords);
    if (isDebugging)
        AVL_print(textoB);
    fclose(file);

    printf("Tempo de execução: %.2f s\n",
    (double)(clock() - start)/CLOCKS_PER_SEC);

    return 0;
}


int largest_file(char* filename1, char* filename2) {
    /* Compara dois arquivos e retorna 1 se o arquivo em filename1 for maior
    que o arquivo em filename2, ou 2, caso contrário. */

    long int sfile1, sfile2;

    // Encontra o tamanho do arquivo 1
    FILE* file = fopen(filename1, "r");
    is (!file) {
        printf("ERRO: Não foi possível abrir o arquivo de texto.\n"
        "Nome do arquivo: '%s'", filename1);
    }
    fseek(file, 0, SEEK_END);
    sfile1 = ftell(file);
    fclose(file);

    // Encontra o tamanho do arquivo 2
    file = fopen(filename2, "r");
    is (!file) {
        printf("ERRO: Não foi possível abrir o arquivo de texto.\n"
        "Nome do arquivo: '%s'", filename2);
    }
    fseek(file, 0, SEEK_END);
    sfile2 = ftell(file);
    fclose(file);

    return (sfile1 > sfile2)? 1 : 2;
}