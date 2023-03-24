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


#define DEBUG 1


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

    FILE* file = fopen(argv[3], "r");

    lst* textoA = NULL;
    AVL* textoB = NULL;
    AVL* stopwords = NULL;

    // Definindo a AVL das stopwords
    if (!file) {
        printf("ERRO: Não foi possível abrir a lista de stopwords.\n"
        "Nome do arquivo: '%s'", argv[3]);
        return 1;
    }
    stopwords = AVL_from_file_stopwords(file);
    if (is_debugging)
        AVL_print(stopwords);

    // Calcula qual dos dois textos é maior


    printf("Tempo de execução: %.2f s\n",
    (double)(clock() - start)/CLOCKS_PER_SEC);

    return 0;
}
