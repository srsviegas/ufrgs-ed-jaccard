#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jaccard.h"
#include "data.h"

void intersection(AVL* A, AVL* B, int* accumulator) {
    /* Calcula a intersecção entre duas árvores AVL armazenando o resultado
    em um acumulador. */

    if (!A || !B) {
        return;
    }

    intersection(A->l_child, B, accumulator);
    if (AVL_search(B, A->data)) {
        (*accumulator)++;
    }
    intersection(A->r_child, B, accumulator);
}

float jaccard(AVL* A, AVL* B, int A_len, int B_len) {
    /* Calcula o coeficiente de Jaccard de dois textos, com suas palavras
    armazenadas em árvores AVL. */

    // Calcula a intersecção entre as árvores
    int intersect_len = 0;
    intersection(A, B, &intersect_len);

    // Calcula a união entre as árvores
    int union_len = A_len + B_len - intersect_len;

    // Calcula o coeficiente de Jaccard
    return (float)intersect_len/union_len;
}