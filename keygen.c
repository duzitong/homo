#include "keygen.h"

void init_key(struct Key *k, int l, pairing_t pairing, element_t g, element_t gt) {
    element_t a, b, beta, inv_beta;
    element_t *a1, *a2;

    element_init_Zr(a, pairing);
    rnd_non_zero(a);
    element_init_Zr(b, pairing);
    rnd_non_zero(b);
    element_init_Zr(beta, pairing);
    rnd_non_zero(beta);

    a1 = (element_t*) malloc(sizeof(element_t) * l);
    a2 = (element_t*) malloc(sizeof(element_t) * l);
    for (int i = 0; i < l; i++) {
        element_init_Zr(a1[i], pairing);
        rnd_non_zero(a1[i]);
        element_init_Zr(a2[i], pairing);
        rnd_non_zero(a2[i]);
    }

    // Computing exponentials
    element_pp_t g_pp, gt_pp;
    element_pp_init(g_pp, g);
    element_pp_init(gt_pp, gt);
    element_init_G1(k->id, pairing);
    element_pp_pow_zn(k->id, beta, g_pp);
    element_init_Zr(k->sk.beta, pairing);
    element_set(k->sk.beta, beta);
    element_init_Zr(k->sk.a, pairing);
    element_set(k->sk.a, a);
    element_init_Zr(k->sk.b, pairing);
    element_set(k->sk.b, b);
    k->sk.a1 = a1;
    k->sk.a2 = a2;
    k->pk.gt_a1 = (element_t*) malloc(sizeof(element_t) * l);
    k->pk.g_a2 = (element_t*) malloc(sizeof(element_t) * l);
    for (int i = 0; i < l; i++) {
        element_init_GT(k->pk.gt_a1[i], pairing);
        element_pp_pow_zn(k->pk.gt_a1[i], a1[i], gt_pp);
        element_init_G1(k->pk.g_a2[i], pairing);
        element_pp_pow_zn(k->pk.g_a2[i], a1[i], g_pp);
    }
    element_init_G1(k->pk.g_beta, pairing);
    element_pp_pow_zn(k->pk.g_beta, beta, g_pp);
    element_init_Zr(inv_beta, pairing);
    element_invert(inv_beta, beta);
    element_init_G1(k->pk.g_inv_beta, pairing);
    element_pp_pow_zn(k->pk.g_inv_beta, inv_beta, g_pp);
    element_init_G1(k->pk.g_a, pairing);
    element_pp_pow_zn(k->pk.g_a, a, g_pp);
    element_init_GT(k->pk.gt_b, pairing);
    element_pp_pow_zn(k->pk.gt_b, b, gt_pp);
    
    k->l = l;

    // Clean
    element_pp_clear(g_pp);
    element_pp_clear(gt_pp);
}

void print_key(struct Key k) {
    element_printf("id: %B\n", k.id);
    element_printf("sk:\n");
    element_printf("    beta: %B\n", k.sk.beta);
    element_printf("    a: %B\n", k.sk.a);
    element_printf("    b: %B\n", k.sk.b);
    element_printf("    a1:");
    for (int i = 0; i < k.l; i++) {
        element_printf(" %B", k.sk.a1[i]);
    }
    element_printf("\n");
    element_printf("    a2:");
    for (int i = 0; i < k.l; i++) {
        element_printf(" %B", k.sk.a2[i]);
    }
    element_printf("\n");
    element_printf("pk:\n");
    element_printf("    gt_a1:");
    for (int i = 0; i < k.l; i++) {
        element_printf(" %B", k.pk.gt_a1[i]);
    }
    element_printf("\n");
    element_printf("    g_a2:");
    for (int i = 0; i < k.l; i++) {
        element_printf(" %B", k.pk.g_a2[i]);
    }
    element_printf("\n");
    element_printf("    g_beta: %B\n", k.pk.g_beta);
    element_printf("    g_inv_beta: %B\n", k.pk.g_inv_beta);
    element_printf("    g_a: %B\n", k.pk.g_a);
    element_printf("    gt_b: %B\n", k.pk.gt_b);
}

void free_key(struct Key k) {
    free(k.sk.a1);
    free(k.sk.a2);
    free(k.pk.gt_a1);
    free(k.pk.g_a2);
}
