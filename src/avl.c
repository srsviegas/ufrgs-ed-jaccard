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

    // Calcula a altura da ra�z
    root->height = AVL_height(root);

    // Calcula o fator de balanceamento da �rvore
    int balance = AVL_balance(root);

    // Realiza o balanceamento da �rvore
    if (balance > 1) {
        // Compara��o com o filho esquerdo
        int l_cmp = root->l_child ? strcmp(data.word, root->l_child->data.word) : 0;
        if (l_cmp < 0) {
            /* Inserido � esquerda do filho esquerdo e FB > 1,
            Rota��o � direita */
            root = AVL_rotate_right(root);
        }
        else {
            /* Inserido � direita do filho esquerdo e FB > 1,
            Rota��o dupla � direita */
            root->l_child = AVL_rotate_left(root->l_child);
            root = AVL_rotate_right(root);
        }
    }
    else if (balance < -1) {
        // Compara��o com o filho direito
        int r_cmp = root->r_child ? strcmp(data.word, root->r_child->data.word) : 0;
        if (r_cmp > 0) {
            /* Inserido � direita do filho direito e FB < -1,
            Rota��o � esquerda */
            root = AVL_rotate_left(root);
        }
        else {
            /* Inserido � esquerda do filho direito e FB < -1,
            Rota��o dupla � esquerda */
            root->r_child = AVL_rotate_right(root->r_child);
            root = AVL_rotate_left(root);
        }
    }

    return root;
}


AVL* AVL_rotate_left(AVL* p) {
    /* Realiza uma rota��o � esquerda na �rvore de raiz 'p'. */

    /* Faz as atribui��es: 
        1) z era filho direito de p 
        2) t2 era filho esquerdo do filho direito de p
        3) t2 se torna filho direito de p
        4) p se torna filho esquerdo de z */
    AVL* z = p->r_child;
    AVL* t2 = z->l_child;
    p->r_child = t2;
    z->l_child = p;

    // Atualiza a altura de n�s que tiveram filhos alterados
    p->height = AVL_height(p);
    z->height = AVL_height(z);

    // Retorna a nova ra�z da �rvore (z)
    return z;
}


AVL* AVL_rotate_right(AVL* p) {
    /* Realiza uma rota��o � direita na �rvore de raiz 'p'. */

    /* Faz as atribui��es:
        1) u era filho esquerdo de p
        2) t2 era filho direito do filho esquerdo de p
        3) t2 se torna filho esquerdo de p
        4) p se torna filho direito de u */
    AVL* u = p->l_child;
    AVL* t2 = u->r_child;
    p->l_child = t2;
    u->r_child = p;

    // Atualiza a altura de n�s que tiveram filhos alterados
    p->height = AVL_height(p);
    u->height = AVL_height(u);

    // Retorna a nova ra�z da �rvore (u)
    return u;
}


int AVL_height(AVL* root) {
    /* Retorna o valor da altura de uma �rvore de raiz 'root'. */

    if (!root)
        return 0;

    // Armazena a altura dos dois nodos filhos de root
    int l_height = root->l_child ? root->l_child->height : 0;
    int r_height = root->r_child ? root->r_child->height : 0;

    // Retorna a maior altura entre os dois mais 1
    return ((l_height > r_height) ? l_height : r_height) + 1;
}


int AVL_balance(AVL* root) {
    /* Retorna o valor do fator de balanceamento da raiz 'root'. */

    if (!root)
        return 0;

    // Armazena a altura dos dois odos filhos de root
    int l_height = root->l_child ? root->l_child->height : 0;
    int r_height = root->r_child ? root->r_child->height : 0;

    return l_height - r_height;
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
    printf("[%s] (B = %d, H = %d)\n", 
        root->data.word, AVL_balance(root), root->height);
    AVL_print(root->r_child);
}