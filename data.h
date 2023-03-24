#ifndef DATA_H
#define DATA_H

#define WSIZE 30

// Tipo Data

typedef struct T_Data {
    char word[WSIZE];
} T_Data;


// Tipo AVL

typedef struct AVL {
    T_Data data;
    struct AVL* l_child;
    struct AVL* r_child;
    int height;
} AVL;

AVL* AVL_from_file(FILE* file, int* len, AVL* stopwords);
AVL* AVL_from_file_stopwords(FILE* file);
AVL* AVL_insert(AVL* root, T_Data data, int* len);
AVL* AVL_rotate_left(AVL* root);
AVL* AVL_rotate_right(AVL* root);
int AVL_height(AVL* root);
int AVL_balance(AVL* root);
int AVL_search(AVL* root, T_Data data);
void AVL_print(AVL* root);


// Tipo Lista

typedef struct lst {
    T_Data data;
    struct lst* next;
} lst;

lst* lst_from_file(FILE* file, int* len, AVL* stopwords);
lst* lst_insert(lst* list, T_Data data, int* len);
void lst_print(lst* list);


#endif