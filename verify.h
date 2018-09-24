#pragma once
#include "compute.h"
#include "enc.h"
#include "keygen.h"

struct Result {
    element_t *y;
    int l;
};

int verify(struct Result *, struct MK, struct Omega, element_t *, int, struct PP, element_t, element_t, pairing_t);
void print_result(struct Result);
void free_result(struct Result);
