#include <stdio.h>
#include "utils.h"
#include "keygen.h"
#include "enc.h"

int main() {
    // init pairing
    pairing_t pairing;
    char param[1024];
    size_t count = fread(param, 1, 1024, stdin);
    if (!count) pbc_die("input error");
    pairing_init_set_buf(pairing, param, count);

    int l = 2;

    // init g & gt
    element_t g, h, gt;
    element_init_G1(g, pairing);
    element_init_G1(h, pairing);
    rnd_non_zero(g);
    rnd_non_zero(h);
    element_init_GT(gt, pairing);
    pairing_pp_t pp;
    pairing_pp_init(pp, g, pairing);
    pairing_pp_apply(gt, h, pp);
    pairing_pp_clear(pp);

    
    struct SKey sk;
    init_skey(&sk, l, pairing, g, gt);
    printf("===== sk =====\n");
    print_skey(sk);

    struct VKey vk;
    init_vkey(&vk, l, pairing, g, gt);
    printf("===== vk =====\n");
    print_vkey(vk);

    struct SRKey srk;
    init_srkey(&srk, sk.sk, vk.aux, l, pairing);
    printf("===== srk =====\n");
    print_srkey(srk);

    struct VRKey vrk;
    struct PK pk[1];
    struct RK rk[1];
    pk[0] = sk.pk;
    rk[0] = srk.rk;
    init_vrkey(&vrk, pk, vk.mk, rk, 1, pairing);
    printf("===== vrk =====\n");
    print_vrkey(vrk);

    struct F f;
    init_f(&f, 1, pairing);
    printf("===== f =====\n");
    print_f(f);

    struct EnFunc enf;
    init_enfunc(&enf, f, vrk.ak, vk.mk, vk.l ,vrk.n);
    printf("===== enf =====\n");
    print_enfunc(enf);

    struct EnInput eni;
    element_t *m;
    m = (element_t*) malloc(sizeof(element_t) * (l-1));
    for (int i = 0; i < l-1; i++) {
        element_init_Zr(m[i], pairing);
        rnd_non_zero(m[i]);
    }
    init_eninput(&eni, sk, m, l, g, gt, pairing);
    printf("===== eni =====\n");
    print_eninput(eni);


    free_skey(sk);
    free_vkey(vk);
    free_srkey(srk);
    free_vrkey(vrk);
    free_eninput(eni);
    free(m);

    return 0;
}

