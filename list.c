#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "data.h"


lst* lst_from_file(FILE* file, int* len, AVL* stopwords) {
    /* Cria uma lista para as palavras de um arquivo de texto */

    lst* list = NULL;

    char c, word[WSIZE];
    int word_len = 0; 
    while ((c = fgetc(file)) != EOF && word_len < WSIZE) {
        if (isalpha(c)) {
            // Se c for letra, adiciona c no buffer
            word[word_len] = tolower(c);
            word_len++;
        }
        else if (word_len > 0) {
            /* Se c não for letra, e tiver palavra no buffer, 
            adiciona a palavra na lista, caso não seja uma stopword */
            word[word_len] = '\0';
            word_len = 0;
            T_Data data;
            strcpy(data.word, word);
            if (!(AVL_search(stopwords, data)))
                list = lst_insert(list, data, len);
        }
    }
    if (word_len > 0) {
        /* Se ainda tiver palavra no buffer,
        adiciona a palavra na AVL */
        word[word_len] = '\0';
        word_len = 0;
        T_Data data;
        strcpy(data.word, word);
        if (!(AVL_search(stopwords, data)))
                list = lst_insert(list, data, len);
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
        return new;
    }

    lst* ptr = list;

    do {
        /* Busca o último elemento, enquanto checa se a palavra
        já está presente na lista */
        if (strcmp(ptr->data.word, data.word) == 0) {
            /* Caso 'palavra já está na lista': não realiza nada */
            return list;
        }
        if (ptr->next) {
            ptr = ptr->next;
        }
    } while (ptr->next);

    // Coloca o novo elemento no final da lista, e retorna a lista
    ptr->next = new;
    return list;
}


void lst_print(lst* list) {
    /* Imprime os elementos da lista em ordem */

    while (list) {
        printf("[%s]\n", list->data.word);
        list = list->next;
    }
}