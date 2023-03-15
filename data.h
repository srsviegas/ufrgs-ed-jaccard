#ifndef DATA_H
#define DATA_H

#define WSIZE 30

// --- Tipo Data --- --- --- --
typedef struct T_Data {
    char word[WSIZE];
    int len;
} T_Data;


// --- Tipo AVL --- --- --- ---
typedef struct AVL {
    T_Data data;
    AVL* l_child;
    AVL* r_child;
} AVL;

typedef struct AVL_info {
    AVL* root;
    int len;
} AVL_info;

void AVL_insert(AVL_info* tree, T_Data word);
bool AVL_search(AVL_info tree, T_Data word);


// --- Tipo lista --- --- --- --
typedef struct lst {
    T_Data data;
    lst* next;
} lst;

typedef struct lst_info {
    lst* list;
    int len;
} lst_info;

void lst_insert(lst_info list, T_Data word);


#endif DATA_H