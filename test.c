#include <stdio.h>
#include <pbc/pbc.h>
#include "utils.h"
#include "kangaroo.h"

int main() {
    // init pairing
    pairing_t pairing;
    char param[1024];
    size_t count = fread(param, 1, 1024, stdin);
    if (!count) pbc_die("input error");
    pairing_init_set_buf(pairing, param, count);

    element_t g, h, gt, p, gp, hp, gtp, ans;
    element_init_G1(g, pairing);
    element_init_G1(gp, pairing);
    element_init_Zr(h, pairing);
    element_init_Zr(hp, pairing);
    element_init_Zr(ans, pairing);
    element_init_GT(gt, pairing);
    element_init_GT(gtp, pairing);
    element_init_Zr(p, pairing);
    element_set_si(p, 1073740000);
    rnd_non_zero(g);
    rnd_non_zero(h);
    element_pairing(gt, g, g);
    element_pow_zn(gp, g, p);

    // element_printf("g: %B\n", g);
    // element_printf("h: %B\n", h);
    // element_printf("hp: %B\n", hp);
    // element_printf("gt: %B\n", gt);

    struct Kangaroo k;
    printf("Initializing...\n");
    init_kangaroo(&k, 20, 65536, g, pairing, 1);
    printf("Calculating...\n");
    int failed = element_dlog_pollard_kangaroo(ans, g, gp, k);
    element_printf("ans(%d): %B\n", failed, ans);

    return 0;
}
