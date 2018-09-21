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

void init_fkey(struct FKey *fk, struct F f, int index, element_t g, pairing_t pairing) {
    element_init_G1(fk->sk, pairing);
    rnd_non_zero(fk->sk);
    element_init_GT(fk->pk, pairing);
    element_t tmp;
    element_init_G1(tmp, pairing);
    element_pow_zn(tmp, g, f.q[index]);
    element_pairing(fk->pk, tmp, fk->sk);
}

void print_fkey(struct FKey fk) {
    element_printf("sk: %B\n", fk.sk);
    element_printf("pk: %B\n", fk.pk);
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

// Deprecated
void H(element_t mu, element_t g_a, element_t x, element_t g, element_t y, pairing_t pairing) {
    element_init_G1(mu, pairing);
    element_pow_zn(mu, g_a, x);
    element_t tmp;
    element_init_G1(tmp, pairing);
    element_pow_zn(mu, g, y);
    element_mul(mu, mu, tmp);
}

void init_eninput(struct EnInput *eni, struct FKey fk, struct SKey sk, element_t *m, int l, element_t g, element_t gt, pairing_t pairing) {
    element_t x,y,r,k;
    element_init_Zr(x, pairing);
    rnd_non_zero(x);
    element_init_Zr(y, pairing);
    rnd_non_zero(y);
    element_init_Zr(r, pairing);
    rnd_non_zero(r);
    element_init_Zr(k, pairing);
    rnd_non_zero(k);

    element_init_G1(eni->sigma, pairing);
    element_set(eni->sigma, fk.sk);

    element_pp_t g_pp, gt_pp;
    element_pp_init(g_pp, g);
    element_pp_init(gt_pp, gt);
    element_t tmp;
    element_init_G1(tmp, pairing);
    for (int i = 0; i < l-1; i++) {
        element_pp_pow_zn(tmp, m[i], g_pp);
        element_mul(eni->sigma, eni->sigma, tmp);
    }
    element_pow_zn(eni->sigma, eni->sigma, sk.sk.beta);

    element_init_G1(eni->c.g_k, pairing);
    element_pp_pow_zn(eni->c.g_k, k, g_pp);
    eni->c.gt_m_gt_a1_k = (element_t*) malloc(sizeof(element_t) * (l-1));
    element_t gt_m, gt_a1_k;
    element_init_GT(gt_m, pairing);
    element_init_GT(gt_a1_k, pairing);
    for (int i = 0; i < l-1; i++) {
        element_init_GT(eni->c.gt_m_gt_a1_k[i], pairing);
        element_pp_pow_zn(gt_m, m[i], gt_pp);
        element_pow_zn(gt_a1_k, sk.pk.gt_a1[i], k);
        element_mul(eni->c.gt_m_gt_a1_k[i], gt_m, gt_a1_k);
    }

    element_init_GT(eni->c.gt_r_gt_a1_k, pairing);
    element_pp_pow_zn(gt_m, r, gt_pp);
    element_pow_zn(gt_a1_k, sk.pk.gt_a1[l-1], k);
    element_mul(eni->c.gt_r_gt_a1_k, gt_m, gt_a1_k);
    eni->c.flag = '2';

    eni->l = l;

    element_pp_clear(g_pp);
    element_pp_clear(gt_pp);
}

void print_eninput(struct EnInput eni) {
    element_printf("sigma: %B\n", eni.sigma);
    element_printf("c:\n");
    element_printf("    g_k: %B\n", eni.c.g_k);
    element_printf("    gt_m_gt_a1_k:");
    for (int i = 0; i < eni.l - 1; i++) {
        element_printf(" %B", eni.c.gt_m_gt_a1_k[i]);
    }
    element_printf("\n");
    element_printf("    gt_r_gt_a1_k: %B\n", eni.c.gt_r_gt_a1_k);
    element_printf("    flag: %c\n", eni.c.flag);
}

void free_eninput(struct EnInput eni) {
    free_non_null(eni.c.gt_m_gt_a1_k);
    eni.c.gt_m_gt_a1_k = NULL;
}
