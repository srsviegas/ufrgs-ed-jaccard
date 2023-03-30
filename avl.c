#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "data.h"


AVL* AVL_from_file(FILE* file, int* len, AVL* stopwords) {
    /* Cria uma AVL para as palavras de um arquivo de texto */

    AVL* root = NULL;

    char *word, row[1000];
    char delimiters[]= {" 0123456789-.,&*%\?!;/'@\"$#=~><()][}{:\n\t_"};

    while (fgets(row, 1000, file)) {
        word = strtok(row, delimiters);
        while (word) {
            T_Data data;
            strcpy(data.word, strlwr(word));
            if (!(AVL_search(stopwords, data))) {
                root = AVL_insert(root, data, len);
            }
            word = strtok(NULL, delimiters);
        }
    }

    return root;
}


AVL* AVL_from_file_stopwords(FILE* file) {
    /* Cria uma AVL para stopwords a partir de um arquivo de texto */

    AVL* root = NULL;

    char *word, row[1000];
    char delimiters[]= {" 0123456789-.,&*%\?!;/'@\"$#=~><()][}{:\n\t_"};

    while (fgets(row, 1000, file)) {
        word = strtok(row, delimiters);
        while (word) {
            T_Data data;
            strcpy(data.word, strlwr(word));
            root = AVL_insert(root, data, NULL);
            word = strtok(NULL, delimiters);
        }
    }

    return root;
}


AVL* AVL_insert(AVL* root, T_Data data, int* len) {
    /* Insere um novo nodo contendo 'data' na �rvore de raiz 'root', 
    aumentando o valor de 'len', caso a inser��o seja bem sucedida. */

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
    int cmp = strcmp(data.word, root->data.word);
    if (cmp < 0) {
        /* Se a palavra for lexicograficamente menor que a da raiz,
        insere a palavra na sua sub�rvore esquerda */
        root->l_child = AVL_insert(root->l_child, data, len);
    }
    else if (cmp > 0) {
        /* Se a palavra for lexicograficamente maior que a da raiz,
        insere a palavra na sua sub�rvore direita */
        root->r_child = AVL_insert(root->r_child, data, len);
    }
    else {
        /* Se as palavras forem iguais,
        n�o insere nada */
        return root;
    }

    // Calcula o fator de balanceamento da �rvore
    int balance = AVL_balance(root);

    // Calcula as compara��es com os filhos da raiz, para descobrir onde foi inserido
    int l_cmp = root->l_child ? strcmp(data.word, root->l_child->data.word) : 0;
    int r_cmp = root->r_child ? strcmp(data.word, root->r_child->data.word) : 0;

    // Realiza o balanceamento da �rvore
    if (l_cmp < 0 && balance > 1) {
        /* Inserido � esquerda do filho esquerdo e FB > 1,
        Rota��o � direita */
        root = AVL_rotate_right(root);
    }
    else if (r_cmp > 0 && balance < -1) {
        /* Inserido � direita do filho direito e FB < -1,
        Rota��o � esquerda */
        root = AVL_rotate_left(root);
    }
    else if (l_cmp > 0 && balance > 1) {
        /* Inserido � direita do filho esquerdo e FB > 1,
        Rota��o dupla � direita */
        root->l_child = AVL_rotate_left(root->l_child);
        root = AVL_rotate_right(root);
    }
    else if (r_cmp < 0 && balance < -1) {
        /* Inserido � esquerda do filho direito e FB < -1,
        Rota��o dupla � esquerda */
        root->r_child = AVL_rotate_right(root->r_child);
        root = AVL_rotate_left(root);
    }

    return root;
}


AVL* AVL_rotate_left(AVL* root) {
    /* Realiza uma rota��o � esquerda na �rvore de raiz 'root'. */

    AVL* z = root->r_child;
    root->r_child = z->l_child;
    z->l_child = root;
    root = z;

    root->height = AVL_height(root);
    z->height = AVL_height(z);

    return root;
}


AVL* AVL_rotate_right(AVL* root) {
    /* Realiza uma rota��o � direita na �rvore de raiz 'root'. */

    AVL* u = root->l_child;
    root->l_child = u->r_child;
    u->r_child = root;
    root = u;

    root->height = AVL_height(root);
    u->height = AVL_height(u);

    return root;
}


int AVL_height(AVL* root) {
    /* Retorna o valor da altura de uma �rvore de raiz 'root'. */

    if (root->l_child->height > root->r_child->height)
        return root->l_child->height + 1;
    else
        return root->r_child->height + 1;
}


int AVL_balance(AVL* root) {
    /* Retorna o valor do fator de balanceamento da raiz 'root'. */

    if (!(root->l_child) && !(root->r_child))
        return 0;
    else if (!(root->l_child))
        return 0 - root->r_child->height;
    else if (!(root->r_child))
        return root->l_child->height;
    else
        return root->l_child->height - root->r_child->height;
}


int AVL_search(AVL* root, T_Data data) {
    /* Busca uma palavra na AVL e retorna 1, caso encontre, ou 0. */

    if (!root) {
        return 0;
    }

    int cmp = strcmp(data.word, root->data.word);

    if (cmp == 0) {
        return 1;   // Os itens s�o iguais, data est� na AVL
    }
    else if (cmp < 0) {
        // data < root
        if (!(root->l_child)) {
            // Root n�o possui filho esquerdo, data n�o est� na AVL
            return 0;
        }
        else {
            // Busca data na sub-�rvore esquerda
            return AVL_search(root->l_child, data);
        }
    }
    else {
        // data > root
        if (!(root->r_child)) {
            // Root n�o possui filho direito, data n�o est� na AVL
            return 0;
        }
        else {
            // Busca data na sub-�rvore direita
            return AVL_search(root->r_child, data);
        }
    }
}


void AVL_print(AVL* root) {
    /* Imprime os elementos da �rvore em ordem, com o caminhamento
    central � esquerda. */

    if (!root) {
        return;
    }

    AVL_print(root->l_child);
    printf("[%s] (%d)\n", root->data.word, AVL_balance(root));
    AVL_print(root->r_child);
}