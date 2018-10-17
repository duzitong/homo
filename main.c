#include <stdio.h>
#include "utils.h"
#include "keygen.h"
#include "enc.h"
#include "compute.h"
#include "verify.h"

#define MAX_BITS 10

int main() {
    // init pairing
    pairing_t pairing;
    char param[1024];
    size_t count = fread(param, 1, 1024, stdin);
    if (!count) pbc_die("input error");
    pairing_init_set_buf(pairing, param, count);

    int l = 4;

    // init g & gt
    element_t g, gt;
    element_init_G1(g, pairing);
    rnd_non_zero(g);
    element_printf("g: %B\n", g);
    element_init_GT(gt, pairing);
    element_pairing(gt, g, g);
    element_printf("gt: %B\n", gt);

    struct PP pp;
    init_pp(&pp, l, pairing);
    printf("===== pp =====\n");
    print_pp(pp);
    
    struct SKey sk1, sk2;
    init_skey(&sk1, l, pairing, g, gt);
    printf("===== sk1 =====\n");
    print_skey(sk1);
    init_skey(&sk2, l, pairing, g, gt);
    printf("===== sk2 =====\n");
    print_skey(sk2);

    struct VKey vk;
    init_vkey(&vk, l, pairing, g, gt);
    printf("===== vk =====\n");
    print_vkey(vk);

    struct SRKey srk1, srk2;
    init_srkey(&srk1, sk1.sk, vk.aux, l, pairing);
    printf("===== srk1 =====\n");
    print_srkey(srk1);
    init_srkey(&srk2, sk2.sk, vk.aux, l, pairing);
    printf("===== srk2 =====\n");
    print_srkey(srk2);

    struct VRKey vrk;
    struct PK pk[2];
    struct RK rk[2];
    pk[0] = sk1.pk;
    pk[1] = sk2.pk;
    rk[0] = srk1.rk;
    rk[1] = srk2.rk;
    init_vrkey(&vrk, pk, vk.mk, rk, 2, pairing);
    printf("===== vrk =====\n");
    print_vrkey(vrk);

    struct F f;
    init_f_with_length_limited(&f, 2, pairing, MAX_BITS);
    printf("===== f =====\n");
    print_f(f);

    struct FKey fk1, fk2;
    init_fkey(&fk1, f, 0, g, pairing);
    printf("===== fk1 =====\n");
    print_fkey(fk1);
    init_fkey(&fk2, f, 1, g, pairing);
    printf("===== fk2 =====\n");
    print_fkey(fk2);

    struct EnFunc enf;
    init_enfunc(&enf, f, vrk.ak, vk.mk, vk.l ,vrk.n);
    printf("===== enf =====\n");
    print_enfunc(enf);

    struct EnInput eni1, eni2;
    element_t *m1, *m2;
    m1 = (element_t*) malloc(sizeof(element_t) * (l));
    m2 = (element_t*) malloc(sizeof(element_t) * (l));
    printf("===== m1 =====\nm:");
    for (int i = 0; i < l; i++) {
        element_init_Zr(m1[i], pairing);
        rnd_with_length_limited(m1[i], MAX_BITS);
        element_printf(" %B", m1[i]);
    }
    printf("\n");
    printf("===== m2 =====\nm:");
    for (int i = 0; i < l; i++) {
        element_init_Zr(m2[i], pairing);
        rnd_with_length_limited(m2[i], MAX_BITS);
        element_printf(" %B", m2[i]);
    }
    printf("\n");
    init_eninput(&eni1, fk1, sk1, m1, pp, g, gt, pairing);
    printf("===== eni1 =====\n");
    print_eninput(eni1);
    init_eninput(&eni2, fk2, sk2, m2, pp, g, gt, pairing);
    printf("===== eni2 =====\n");
    print_eninput(eni2);

    struct Omega omega;
    struct EnInput eni_arr[2];
    eni_arr[0] = eni1;
    eni_arr[1] = eni2;
    compute(&omega, pk, enf.phi, eni_arr, rk, vrk, l, 2, pairing);
    printf("===== omega =====\n");
    print_omega(omega);

    struct Result r;
    element_t fpk[2];
    element_init_GT(fpk[0], pairing);
    element_set(fpk[0], fk1.pk);
    element_init_GT(fpk[1], pairing);
    element_set(fpk[1], fk2.pk);
    int yl = verify(&r, vk.mk, omega, fpk, 2, pp, g, gt, pairing);
    printf("===== r(%d) =====\n", yl);
    print_result(r);

    // free_skey(sk);
    // free_vkey(vk);
    // free_srkey(srk);
    // free_vrkey(vrk);
    // free_eninput(eni);
    // free(m);
    // free_omega(omega);
    // free_result(r);

    return 0;
}

