#include "compute.h"
#include <stdio.h>

void compute(struct Omega *omega, struct PK *pk, struct Phi phi, struct EnInput *eni, struct RK *rk, struct VRKey vrk, int l, int n, pairing_t pairing) {
    element_t tmp, tmp1;
    element_init_GT(tmp, pairing);
    element_init_G1(tmp1, pairing);

    // cp[1]
    omega->cp.e_g_k_rk = (element_t*) malloc(sizeof(element_t) * l);
    for (int t = 0; t < l; t++) {
        element_init_GT(omega->cp.e_g_k_rk[t], pairing);
        element_set1(omega->cp.e_g_k_rk[t]);
    }

    for (int j = 0; j < n; j++) {
        pairing_pp_t pp;
        pairing_pp_init(pp, eni[j].c.g_k, pairing);

        for (int t = 0; t < l; t++) {
            pairing_pp_apply(tmp, rk[j].g_a2_a1[t], pp);
            element_pow_zn(tmp, tmp, phi.f.q[j]);
            element_mul(omega->cp.e_g_k_rk[t], omega->cp.e_g_k_rk[t], tmp);
        }

        pairing_pp_clear(pp);
    }

    // cp[2]
    omega->cp.gt_m_gt_a1_k = (element_t*) malloc(sizeof(element_t) * (l-1));
    for (int t = 0; t < l-1; t++) {
        element_init_GT(omega->cp.gt_m_gt_a1_k[t], pairing);
        element_set1(omega->cp.gt_m_gt_a1_k[t]);
    }
    element_init_GT(omega->cp.gt_r_gt_a1_k, pairing);
    element_set1(omega->cp.gt_r_gt_a1_k);
    for (int j = 0; j < n; j++) {
        for (int t = 0; t < l-1; t++) {
            element_pow_zn(tmp, eni[j].c.gt_m_gt_a1_k[t], phi.f.q[j]);
            element_mul(omega->cp.gt_m_gt_a1_k[t], omega->cp.gt_m_gt_a1_k[t], tmp);
        }
        element_pow_zn(tmp, eni[j].c.gt_r_gt_a1_k, phi.f.q[n-1]);
        element_mul(omega->cp.gt_r_gt_a1_k, omega->cp.gt_r_gt_a1_k, tmp);
    }

    omega->cp.flag = 'R';
    omega->cp.l = l;

    // sigma
    element_init_GT(omega->sigma, pairing);
    element_set1(omega->sigma);
    for (int j = 0; j < n; j++) {
        element_pow_zn(tmp1, eni[j].sigma, phi.f.q[j]);
        element_pairing(tmp, tmp1, vrk.ak.g_inv_beta_alpha[j]);
        element_mul(omega->sigma, omega->sigma, tmp);
    }
}

void print_omega(struct Omega omega) {
    element_printf("cp:\n");
    element_printf("    e_g_k_rk:");
    for (int i = 0; i < omega.cp.l; i++) {
        element_printf(" %B", omega.cp.e_g_k_rk[i]);
    }
    element_printf("\n");
    element_printf("    gt_m_gt_a1_k:");
    for (int i = 0; i < omega.cp.l-1; i++) {
        element_printf(" %B", omega.cp.gt_m_gt_a1_k[i]);
    }
    element_printf("\n");
    element_printf("    gt_r_gt_a1_k: %B\n", omega.cp.gt_r_gt_a1_k);
    element_printf("    flag: %c\n", omega.cp.flag);
    element_printf("sigma: %B\n", omega.sigma);
}

void free_omega(struct Omega omega) {
    free_non_null(omega.cp.e_g_k_rk);
    free_non_null(omega.cp.gt_m_gt_a1_k);

    omega.cp.e_g_k_rk = NULL;
    omega.cp.gt_m_gt_a1_k = NULL;
}
