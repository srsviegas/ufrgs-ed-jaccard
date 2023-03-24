#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "data.h"


lst* lst_from_file(FILE* file, int* len, AVL* stopwords) {
    /* Cria uma lista para as palavras de um arquivo de texto */

    lst* list = NULL;

    char *word, row[1000];
    char delimiter[]= {" 0123456789-.,&*%\?!;/'@\"$#=~><()][}{:\n\t_"};

    while (fgets(row, 1000, file)) {
        word = strtok(row, delimiter);
        while (word) {
            T_Data data;
            strcpy(data.word, strlwr(word));
            if (!(AVL_search(stopwords, data))) {
                list = lst_insert(list, data, len);
            }
            word = strtok(NULL, delimiter);
        }
    }

    return list;
}


lst* lst_insert(lst* list, T_Data data, int* len) {
    /* Insere um novo item contendo 'data' na lista que começa em 'list',
    aumentando o valor de 'len', caso a inserção seja bem sucedida. */

    // Aloca o novo elemento da lista
    lst* new = (lst*)malloc(sizeof(lst));
    new->next = NULL;
    new->data = data;

    if (!list) {
        /* Caso 'lista vazia': retorna a nova lista */
        if (len)
            (*len)++;
        return new;
    }

    lst *ptr = list, *last;

    do {
        /* Busca o último elemento, enquanto checa se a palavra
        já está presente na lista */
        if (strcmp(ptr->data.word, data.word) == 0) {
            /* Caso 'palavra já está na lista': não realiza nada */
            free(new);
            return list;
        }
        last = ptr;
        ptr = ptr->next;
    } while (ptr);

    // Coloca o novo elemento no final da lista, e retorna a lista
    last->next = new;
    if (len)
        (*len)++;
    return list;
}


void lst_print(lst* list) {
    /* Imprime os elementos da lista em ordem */

    while (list) {
        printf("[%s]\n", list->data.word);
        list = list->next;
    }
}