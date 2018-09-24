#pragma once
#include "keygen.h"

struct F {
    element_t *q;
    int n;
};

struct FKey {
    element_t sk;
    element_t pk;
};

struct Phi {
    struct F f;
    struct AK ak;
};

struct Xi {
    struct F f;
    struct MK mk;
};

struct EnFunc {
    struct Phi phi;
    struct Xi xi;
    int l;
    int n;
};

struct C {
    element_t g_k;
    element_t *gt_m_gt_a1_k;
    element_t gt_r_gt_a1_k;
    char flag;
    int l;
};

struct EnInput {
    element_t sigma;
    struct C c;
    int l;
};

void init_f(struct F *, int, pairing_t);
void print_f(struct F);
void free_f(struct F);

void init_fkey(struct FKey *, struct F, int, element_t, pairing_t);
void print_fkey(struct FKey);

void init_enfunc(struct EnFunc *, struct F, struct AK, struct MK, int, int);
void print_enfunc(struct EnFunc);

// Deprecated
void H(element_t, element_t, element_t, element_t, element_t, pairing_t);

void init_eninput(struct EnInput *, struct FKey, struct SKey, element_t *, struct PP, element_t, element_t, pairing_t);
void print_eninput(struct EnInput);
void free_eninput(struct EnInput);
