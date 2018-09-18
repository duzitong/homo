#pragma once
#include "keygen.h"

struct F {
    element_t *q;
    int n;
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

void init_f(struct F *, int, pairing_t);
void print_f(struct F);
void free_f(struct F);

void init_enfunc(struct EnFunc *, struct F, struct AK, struct MK, int, int);
void print_enfunc(struct EnFunc);

