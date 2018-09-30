#include "verify.h"

int verify(struct Result *r, struct MK mk, struct Omega omega, element_t *fpk, int n, struct PP pp, element_t g, element_t gt, pairing_t pairing) {
    element_t tmpt, tmpr, tmp1, tmpt2;
    element_init_GT(tmpt, pairing);
    element_init_GT(tmpt2, pairing);
    element_init_Zr(tmpr, pairing);
    element_init_G1(tmp1, pairing);

    int l = omega.cp.l;

    r->y = (element_t*) malloc(sizeof(element_t) * l);

    for (int t = 0; t < l; t++) {
        element_invert(tmpr, mk.a2[t]);
        element_neg(tmpr, tmpr);
        element_pow_zn(tmpt, omega.cp.e_g_k_rk[t], tmpr);
        element_mul(tmpt, omega.cp.gt_m_gt_a1_k[t], tmpt);
        element_init_Zr(r->y[t], pairing);
        element_dlog_brute_force(r->y[t], gt, tmpt);
    }

    r->l = l;

    element_set1(tmpt);
    for (int i = 0; i < n; i++) {
        element_mul(tmpt, tmpt, fpk[i]);
    }
    
    element_set1(tmp1);
    for (int i = 0; i < pp.l; i++) {
        element_mul(tmp1, tmp1, pp.g[i]);
    }
    element_pairing(tmpt2, tmp1, g);
    element_mul(tmpt, tmpt, tmpt2);
    element_pow_zn(tmpt, tmpt, mk.alpha);

    return element_cmp(tmpt, omega.sigma);
}

void print_result(struct Result r) {
    element_printf("y: ");
    for (int i = 0; i < r.l; i++) {
        element_printf(" %B", r.y[i]);
    }
    element_printf("\n");
}

void free_result(struct Result r) {
    free_non_null(r.y);
    r.y = NULL;
}
