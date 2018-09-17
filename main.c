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
    struct Key k;
    init_key(&k, 2, pairing, g, gt);
    print_key(k);
    free_key(k);

    return 0;
}

