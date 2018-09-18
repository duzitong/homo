#pragma once
#include "utils.h"

/*
 * Two occurences of a1, a2 make naming really confusing.
 * Try your best to understand!
 */

struct ID {
    element_t g_beta;
};

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

struct SKey {
    struct ID id;
    struct SK sk;
    struct PK pk;
    int l;
};

struct MK {
    element_t alpha;
    element_t *a1;
    element_t *a2;
};

struct AUX {
    element_t *gt_a1;
    element_t *g_a2;
};

struct VKey {
    struct MK mk;
    struct AUX aux;
    int l;
};

struct RK {
    element_t *g_a2_a1;
};

struct SRKey {
    struct RK rk;
    int l;
};

struct AK {
    element_t *g_inv_beta_alpha;
};

struct VRKey {
    struct AK ak;
    int n;
};

void init_skey(struct SKey *, int, pairing_t, element_t, element_t);
void print_skey(struct SKey);
void free_skey(struct SKey);

void init_vkey(struct VKey *, int, pairing_t, element_t, element_t);
void print_vkey(struct VKey);
void free_vkey(struct VKey);

void init_srkey(struct SRKey *, struct SK, struct AUX, int, pairing_t);
void print_srkey(struct SRKey);
void free_srkey(struct SRKey);

void init_vrkey(struct VRKey *, struct PK *, struct MK, struct RK *, int, pairing_t);
void print_vrkey(struct VRKey);
void free_vrkey(struct VRKey);
