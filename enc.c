#include "enc.h"

void init_f(struct F *f, int n, pairing_t pairing) {
    f->q = (element_t*) malloc(sizeof(element_t) * n);
    for (int i = 0; i < n; i++) {
        element_init_Zr(f->q[i], pairing);
        rnd_non_zero(f->q[i]);
    }

    f->n = n;
}

void print_f(struct F f) {
    element_printf("q:");
    for (int i = 0; i < f.n; i++) {
        element_printf(" %B", f.q[i]);
    }
    element_printf("\n");
}

void free_f(struct F f) {
    free_non_null(f.q);
    f.q = NULL;
}

void init_enfunc(struct EnFunc *enf, struct F f, struct AK ak, struct MK mk, int l, int n) {
    enf->phi.f = f;
    enf->phi.ak = ak;
    enf->xi.f = f;
    enf->xi.mk = mk;
    enf->l = l;
    enf->n = n;
}

void print_enfunc(struct EnFunc enf) {
    element_printf("phi:\n");
    element_printf("    f:\n");
    element_printf("        q:");
    for (int i = 0; i < enf.n; i++) {
        element_printf(" %B", enf.phi.f.q[i]);
    }
    element_printf("\n");
    element_printf("    ak:\n");
    element_printf("        g_inv_beta_alpha:");
    for (int i = 0; i < enf.n; i++) {
        element_printf(" %B", enf.phi.ak.g_inv_beta_alpha[i]);
    }
    element_printf("\n");
    
    element_printf("xi:\n");
    element_printf("    f:\n");
    element_printf("        q:");
    for (int i = 0; i < enf.n; i++) {
        element_printf(" %B", enf.xi.f.q[i]);
    }
    element_printf("\n");
    element_printf("    mk:\n");
    element_printf("        alpha: %B\n", enf.xi.mk.alpha);
    element_printf("        a1:");
    for (int i = 0; i < enf.l; i++) {
        element_printf(" %B", enf.xi.mk.a1[i]);
    }
    element_printf("\n");
    element_printf("        a2:");
    for (int i = 0; i < enf.l; i++) {
        element_printf(" %B", enf.xi.mk.a2[i]);
    }
    element_printf("\n");
}
