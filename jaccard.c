#include <stdio.h>
#include <stdlib.h>

#include "jaccard.h"
#include "data.h"

int intersection(lst* A, AVL* B) {
    /* Calcula a intersecção entre uma lista A e uma AVL B, buscando
    cada elemento da lista na AVL e contando os elementos compartilhados. */

    int intersection = 0;

    while (A) {
        if (AVL_search(B, A->data))
            intersection++;
        A = A->next;
    }

    return intersection;
}

float jaccard(lst* A, AVL* B, int lenA, int lenB) {
    /* Calcula o coeficiente de Jaccard entre um texto armazenado em uma lista
    e um texto armazenado em uma AVL. */

    int txtIntersect = intersection(A, B);
    int txtUnion = lenA + lenB - txtIntersect;

    return (float)txtIntersect/txtUnion;
}