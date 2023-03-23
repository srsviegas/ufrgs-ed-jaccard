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


int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("ERRO: Número incorreto de parâmetros.\n"
        "A chamada deve ser: jaccard <texto1> <texto1> <stopwords>\n");
        return 1;
    }

    setlocale(LC_ALL, "Portuguese");
    clock_t start = clock();



    printf("Tempo de execução: %.2f s\n",
    (double)(clock() - start)/CLOCKS_PER_SEC);

    return 0;
}
