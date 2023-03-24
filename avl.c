#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "data.h"


AVL* AVL_from_file_stopwords(FILE* file) {
    /* Cria uma AVL para stopwords a partir de um arquivo de texto */

    AVL* tree = NULL;

    char c, word[WSIZE];
    int word_len = 0; 
    while ((c = fgetc(file)) != EOF) {
        if (isalpha(c)) {
            if (word_len < (WSIZE + 1)) {
                word[word_len] = c;
                word_len++;
            }
        }
        else if (word_len > 0) {
            word[word_len] = '\0';
            word_len = 0;
            T_Data data;
            strcpy(data.word, word);
            printf("%s\n", data.word);
            tree = AVL_insert(tree, data, NULL);
        }
    }

    return tree;
}


AVL* AVL_insert(AVL* root, T_Data data, int* len) {
    /* Insere um novo nodo contendo 'data' na árvore de raiz 'root', 
    aumentando o valor de 'len', caso a inserção seja bem sucedida. */

    if (!root) {
        /* Caso 'raiz vazia':
        Inicializa e retorna a nova raiz */
        AVL* new = (AVL*)malloc(sizeof(AVL));
        new->l_child = NULL;
        new->r_child = NULL;
        new->height = 1;
        new->data = data;
        if (len)
            (*len)++;
        return new;
    }
    int lexicoCmp = strcmp(data.word, root->data.word);
    if (lexicoCmp < 0) {
        /* Se a palavra for lexicograficamente menor que a da raiz,
        insere a palavra na sua subárvore esquerda */
        root->l_child = AVL_insert(root->l_child, data, len);
    }
    else if (lexicoCmp > 0) {
        /* Se a palavra for lexicograficamente maior que a da raiz,
        insere a palavra na sua subárvore direita */
        root->r_child = AVL_insert(root->r_child, data, len);
    }
    else {
        /* Se as palavras forem iguais,
        não insere nada */
        return root;
    }

    // Calcula o fator de balanceamento da árvore
    int balance = root->l_child->height - root->r_child->height;

    // Balanceia a árvore
    if (lexicoCmp < 0 && balance > 1) {
        root = AVL_rotate_right(root);
    }
    else if (lexicoCmp > 0 && balance < -1) {
        root = AVL_rotate_left(root);
    }
    else if (lexicoCmp > 0 && balance > 1) {
        root->l_child = AVL_rotate_left(root->l_child);
        root = AVL_rotate_right(root);
    }
    else if (lexicoCmp < 0 && balance < -1) {
        root->r_child = AVL_rotate_right(root->r_child);
        root = AVL_rotate_left(root);
    }
    return root;
}


AVL* AVL_rotate_left(AVL* root) {
    /* Realiza uma rotação à esquerda na árvore de raiz 'root'. */

    AVL* z = root->r_child;
    root->r_child = z->l_child;
    z->l_child = root;
    root = z;

    root->height = AVL_height(root);
    z->height = AVL_height(z);

    return root;
}


AVL* AVL_rotate_right(AVL* root) {
    /* Realiza uma rotação à direita na árvore de raiz 'root'. */

    AVL* u = root->l_child;
    root->l_child = u->r_child;
    u->r_child = root;
    root = u;

    root->height = AVL_height(root);
    u->height = AVL_height(u);

    return root;
}


int AVL_height(AVL* root) {
    /* Retorna o valor da altura de uma árvore de raiz 'root'. */

    if (root->l_child->height > root->r_child->height)
        return root->l_child->height + 1;
    else
        return root->r_child->height + 1;
}


void AVL_print(AVL* root) {
    /* Imprime os elementos da árvore em ordem, com o caminhamento
    central à esquerda */

    AVL_print(root->l_child);
    printf("[%s]\n", root->data.word);
    AVL_print(root->r_child);
}