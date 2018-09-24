#include "keygen.h"

void init_pp(struct PP *pp, int l, pairing_t pairing) {
    pp->g = (element_t*) malloc(sizeof(element_t) * l);
    for (int i = 0; i < l; i++) {
        element_init_G1(pp->g[i], pairing);
        rnd_non_zero(pp->g[i]);
    }
    pp->l = l;
}

void print_pp(struct PP pp) {
    element_printf("g: ");
    for (int i = 0; i < pp.l; i++) {
        element_printf(" %B", pp.g[i]);
    }
    element_printf("\n");
}

void free_pp(struct PP *pp) {
    free_non_null(pp->g);
    pp->g = NULL;
}

void init_skey(struct SKey *k, int l, pairing_t pairing, element_t g, element_t gt) {
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

    element_pp_t g_pp, gt_pp;
    element_pp_init(g_pp, g);
    element_pp_init(gt_pp, gt);
    element_init_G1(k->id.g_beta, pairing);
    element_pp_pow_zn(k->id.g_beta, beta, g_pp);
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
        element_pp_pow_zn(k->pk.g_a2[i], a2[i], g_pp);
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

    element_pp_clear(g_pp);
    element_pp_clear(gt_pp);
}

void print_skey(struct SKey k) {
    element_printf("id:\n");
    element_printf("    g_beta: %B\n", k.id.g_beta);
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

void free_skey(struct SKey k) {
    free_non_null(k.sk.a1);
    free_non_null(k.sk.a2);
    free_non_null(k.pk.gt_a1);
    free_non_null(k.pk.g_a2);

    k.sk.a1 = NULL;
    k.sk.a2 = NULL;
    k.pk.gt_a1 = NULL;
    k.pk.g_a2 = NULL;
}

void init_vkey(struct VKey *vk, int l, pairing_t pairing, element_t g, element_t gt) {
    element_t alpha;
    element_t *a1, *a2;

    element_init_Zr(alpha, pairing);
    rnd_non_zero(alpha);

    a1 = (element_t*) malloc(sizeof(element_t) * l);
    a2 = (element_t*) malloc(sizeof(element_t) * l);
    for (int i = 0; i < l; i++) {
        element_init_Zr(a1[i], pairing);
        rnd_non_zero(a1[i]);
        element_init_Zr(a2[i], pairing);
        rnd_non_zero(a2[i]);
    }

    element_init_Zr(vk->mk.alpha, pairing);
    element_set(vk->mk.alpha, alpha);
    vk->mk.a1 = a1;
    vk->mk.a2 = a2;

    element_pp_t g_pp, gt_pp;
    element_pp_init(g_pp, g);
    element_pp_init(gt_pp, gt);
    vk->aux.gt_a1 = (element_t*) malloc(sizeof(element_t) * l);
    vk->aux.g_a2 = (element_t*) malloc(sizeof(element_t) * l);
    for (int i = 0; i < l; i++) {
        element_init_GT(vk->aux.gt_a1[i], pairing);
        element_pp_pow_zn(vk->aux.gt_a1[i], a1[i], gt_pp);
        element_init_G1(vk->aux.g_a2[i], pairing);
        element_pp_pow_zn(vk->aux.g_a2[i], a2[i], g_pp);
    }

    vk->l = l;

    element_pp_clear(g_pp);
    element_pp_clear(gt_pp);
}

void print_vkey(struct VKey vk) {
    element_printf("mk:\n");
    element_printf("    alpha: %B\n", vk.mk.alpha);
    element_printf("    a1:");
    for (int i = 0; i < vk.l; i++) {
        element_printf(" %B", vk.mk.a1[i]);
    }
    element_printf("\n");
    element_printf("    a2:");
    for (int i = 0; i < vk.l; i++) {
        element_printf(" %B", vk.mk.a2[i]);
    }
    element_printf("\n");
    element_printf("aux:\n");
    element_printf("    gt_a1:");
    for (int i = 0; i < vk.l; i++) {
        element_printf(" %B", vk.aux.gt_a1[i]);
    }
    element_printf("\n");
    element_printf("    g_a2:");
    for (int i = 0; i < vk.l; i++) {
        element_printf(" %B", vk.aux.g_a2[i]);
    }
    element_printf("\n");
}

void free_vkey(struct VKey vk) {
    free_non_null(vk.mk.a1);
    free_non_null(vk.mk.a2);
    free_non_null(vk.aux.gt_a1);
    free_non_null(vk.aux.g_a2);

    vk.mk.a1 = NULL;
    vk.mk.a2 = NULL;
    vk.aux.gt_a1 = NULL;
    vk.aux.g_a2 = NULL;
}

void init_srkey(struct SRKey *srk, struct SK sk, struct AUX aux, int l, pairing_t pairing) {
    srk->rk.g_a2_a1 = (element_t*) malloc(sizeof(element_t) * l);
    for (int i = 0; i < l; i++) {
        element_init_G1(srk->rk.g_a2_a1[i], pairing);
        element_pow_zn(srk->rk.g_a2_a1[i], aux.g_a2[i], sk.a1[i]);
    }

    srk->l = l;
}

void print_srkey(struct SRKey srk) {
    element_printf("rk:\n");
    element_printf("    g_a2_a1:");
    for (int i = 0; i < srk.l; i++) {
        element_printf(" %B", srk.rk.g_a2_a1[i]);
    }
    element_printf("\n");
}

void free_srkey(struct SRKey srk) {
    free_non_null(srk.rk.g_a2_a1);
    srk.rk.g_a2_a1 = NULL;
}

void init_vrkey(struct VRKey *vrk, struct PK *pk, struct MK mk, struct RK *rk, int n, pairing_t pairing) {
    vrk->ak.g_inv_beta_alpha = (element_t*) malloc(sizeof(element_t) * n);
    for (int i = 0; i < n; i++) {
        element_init_G1(vrk->ak.g_inv_beta_alpha[i], pairing);
        element_pow_zn(vrk->ak.g_inv_beta_alpha[i], pk[i].g_inv_beta, mk.alpha);
    }

    vrk->n = n;
}

void print_vrkey(struct VRKey vrk) {
    element_printf("ak:\n");
    element_printf("    g_inv_beta_alpha:");
    for (int i = 0; i < vrk.n; i++) {
        element_printf(" %B", vrk.ak.g_inv_beta_alpha[i]);
    }
    element_printf("\n");
}

void free_vrkey(struct VRKey vrk) {
    free_non_null(vrk.ak.g_inv_beta_alpha);
    vrk.ak.g_inv_beta_alpha = NULL;
}
