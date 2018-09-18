#include <stdio.h>
#include "utils.h"
#include "keygen.h"

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
    element_init_G2(h, pairing);
    rnd_non_zero(g);
    rnd_non_zero(h);
    element_init_GT(gt, pairing);
    pairing_pp_t pp;
    pairing_pp_init(pp, g, pairing);
    pairing_pp_apply(gt, h, pp);
    pairing_pp_clear(pp);
    struct SKey sk;
    init_skey(&sk, l, pairing, g, gt);
    print_skey(sk);

    struct VKey vk;
    init_vkey(&vk, l, pairing, g, gt);
    print_vkey(vk);

    struct SRKey srk;
    init_srkey(&srk, sk.sk, vk.aux, l, pairing);
    print_srkey(srk);

    struct VRKey vrk;
    struct PK pk[1];
    struct RK rk[1];
    pk[0] = sk.pk;
    rk[0] = srk.rk;
    init_vrkey(&vrk, pk, vk.mk, rk, 1, pairing);
    print_vrkey(vrk);

    free_skey(sk);
    free_vkey(vk);
    free_srkey(srk);
    free_vrkey(vrk);

    return 0;
}

