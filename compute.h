#pragma once
#include "keygen.h"
#include "enc.h"

struct CP {
    element_t *e_g_k_rk;
    element_t *gt_m_gt_a1_k;
    element_t gt_r_gt_a1_k;
    char flag;
    int l;
};

struct Omega {
    struct CP cp;
    element_t sigma;
};

void compute(struct Omega *, struct PK *, struct Phi, struct EnInput *, struct RK *, struct VRKey, int, int, pairing_t);
void print_omega(struct Omega);
void free_omega(struct Omega);
