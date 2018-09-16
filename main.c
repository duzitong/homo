#include <stdio.h>
#include "utils.h"

void rnd_non_zero(element_t e) {
    element_random(e);
    while (element_is0(e)) {
        element_random(e);
    }
}

void rnd_non_equals(element_t e, element_t p) {
    element_random(e);
    while (element_is0(e) || !element_cmp(e, p)) {
        element_random(e);
    }
}

void run() {
    pairing_t pairing;
    element_t g, h;
    element_t public_key, secret_key;
    element_t sig;
    element_t temp1, temp2;
    element_t r1;
     
    char param[1024];
    size_t count = fread(param, 1, 1024, stdin);
    if (!count) pbc_die("input error");
    pairing_init_set_buf(pairing, param, count);

    element_init_G1(g, pairing);
    element_init_G2(h, pairing);
    rnd_non_zero(g);
    rnd_non_equals(h, g);
    element_init_GT(r1, pairing);
    // element_init_GT(temp2, pairing);
    // element_init_Zr(secret_key, pairing);

    pairing_pp_t pp;
    pairing_pp_init(pp, g, pairing); // x is some element of G1
    pairing_pp_apply(r1, h, pp);
    element_printf("g: %B\n", g);
    element_printf("h: %B\n", h);
    element_printf("r1: %B\n", r1);
    printf("Finished.");
}

int main() {
    gmp_randstate_t state;
    mpz_t a, q;
    mpz_set_ui(q, 5);
    gmp_randinit_default(state);
    mpz_urandomm(a, state, q);
    gmp_printf("Random q: %Zd\n", a);
    return 0;
}

