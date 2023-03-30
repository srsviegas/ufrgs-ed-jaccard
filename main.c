/* O programa retorna o coeficiente de similaridade textual entre um texto A e um
texto B, ignorando as palavras dadas por uma lista de stopwords*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <ctype.h>

#include "data.h"
#include "jaccard.h"

#define DEBUG 0

int main(int argc, char *argv[])
{
    int is_debugging = DEBUG;

    if (argc != 4) {
        printf("ERRO: Número incorreto de parâmetros.\n"
        "A chamada deve ser: jaccard <texto1> <texto2> <stopwords>\n");
        return 1;
    }

    setlocale(LC_ALL, "Portuguese");
    clock_t start = clock();

    AVL* A_words = NULL;         // TADs para árvores de palavras
    AVL* B_words = NULL;
    AVL* stopwords = NULL;

    int A_len = 0;               // Comprimento das árvores
    int B_len = 0;

    // Define a AVL das stopwords
    FILE* file = fopen(argv[3], "r");
    if (!file) {
        printf("ERRO: Não foi possível abrir a lista de stopwords.\n"
        "Nome do arquivo: '%s'", argv[3]);
        return 1;
    }
    stopwords = AVL_from_file_stopwords(file);
    if (is_debugging) {
        printf("Stopwords:\n");
        AVL_print(stopwords);
    }
    fclose(file);

    // Define a AVL do texto 1
    file = fopen(argv[1], "r");
    A_words = AVL_from_file(file, &A_len, stopwords);
    if (is_debugging) {
        printf("\n\nPalavras Texto A:\n");
        AVL_print(A_words);
    }
    fclose(file);

    // Define a AVL do texto 2
    file = fopen(argv[2], "r");
    B_words = AVL_from_file(file, &B_len, stopwords);
    if (is_debugging) {
        printf("\n\nPalavras Texto B:\n");
        AVL_print(B_words);
    }
    fclose(file);

    // Imprime os resultados
    printf("[%s]: %d palavras distintas\n", argv[1], A_len);
    printf("[%s]: %d palavras distintas\n", argv[2], B_len);
    printf("Jaccard = %.2f\n", jaccard(A_words, B_words, A_len, B_len));

    printf("Tempo de execução: %.5f ms\n",
    (double)(clock() - start)/CLOCKS_PER_SEC*1000);

    return 0;
}