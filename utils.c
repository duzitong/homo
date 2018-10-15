#include "utils.h"

void rnd_non_zero(element_t e) {
    element_random(e);
    while (element_is0(e)) {
        element_random(e);
    }
}

void rnd_with_length_limited(element_t e, unsigned int bits) {
    mpz_t rnd;
    mpz_init(rnd);
    element_set_mpz(e, rnd);
    while (element_is0(e)) {
        pbc_mpz_randomb(rnd, bits);
        element_set_mpz(e, rnd);
    }
}

void rnd_non_equals(element_t e, element_t p) {
    element_random(e);
    while (element_is0(e) || !element_cmp(e, p)) {
        element_random(e);
    }
}

void free_non_null(void *a) {
    if (a) {
        free(a);
    }
}
