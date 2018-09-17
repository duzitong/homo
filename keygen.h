#pragma once
#include <pbc/pbc.h>
#include "utils.h"

struct SK {
    element_t beta;
    element_t a;
    element_t b;
    element_t *a1;
    element_t *a2;
};

struct PK {
    element_t *gt_a1;
    element_t *g_a2;
    element_t g_beta;
    element_t g_inv_beta;
    element_t g_a;
    element_t gt_b;
};

struct Key {
    element_t id;
    struct SK sk;
    struct PK pk;
    int l;
};

void init_key(struct Key *, int, pairing_t, element_t, element_t);
void print_key(struct Key);
void free_key(struct Key);
