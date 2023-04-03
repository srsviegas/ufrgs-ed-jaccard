#ifndef JACCARD
#define JACCARD

#include "data.h"

void intersection(AVL* A, AVL* B, int* accumulator);
float jaccard(AVL* A, AVL* B, int A_len, int B_len);

#endif