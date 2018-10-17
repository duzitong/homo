#include "kangaroo.h"

int init_kangaroo(struct Kangaroo *k, unsigned int size, unsigned int rounds, element_t g, pairing_t pairing, int type) {
    if (size > 30) return 1;
    if (type != 0 && type != 1) return 1;

    k->size = size;
    k->rounds = rounds;
    k->type = type;

    element_init_same_as(k->trap, g);
    element_set(k->trap, g);
    mpz_t h, tmpx, tmpy;
    element_t tmp;
    element_pp_t g_pp;
    mpz_init(h);
    mpz_init(tmpx);
    mpz_init(tmpy);
    mpz_init(k->Am);
    mpz_set_ui(k->Am, 1);
    element_init_same_as(tmp, g);
    element_pp_init(g_pp, g);

    if (type == 0) {
        for (int i = 0; i < rounds; i++) {
            element_to_mpz(h, k->trap);
            mpz_mod_ui(h, h, size);
            unsigned int step = 1 << mpz_get_ui(h);
            mpz_add_ui(k->Am, k->Am, step);
            mpz_set_ui(h, step);
            element_pp_pow(tmp, h, g_pp);
            element_mul(k->trap, k->trap, tmp);
        }
    } else {
        for (int i = 0; i < rounds; i++) {
            element_to_mpz(tmpx, element_x(k->trap));
            element_to_mpz(tmpy, element_y(k->trap));
            mpz_add(h, tmpx, tmpy);
            mpz_mod_ui(h, h, size);
            unsigned int step = 1 << mpz_get_ui(h);
            mpz_add_ui(k->Am, k->Am, step);
            mpz_set_ui(h, step);
            element_pp_pow(tmp, h, g_pp);
            element_mul(k->trap, k->trap, tmp);
        }
    }

    mpz_clear(h);
    mpz_clear(tmpx);
    mpz_clear(tmpy);
    element_clear(tmp);
    element_pp_clear(g_pp);
    return 0;
}

int element_dlog_pollard_kangaroo(element_t x, element_t g, element_t h, struct Kangaroo k) {
    int failed = 1;
    element_t wild, tmp;
    element_pp_t g_pp;
    mpz_t tmph, tmpx, tmpy, Bn, ans;
    element_init_same_as(wild, h);
    element_set(wild, h);
    element_init_same_as(tmp, g);
    element_pp_init(g_pp, g);
    mpz_init(tmph);
    mpz_init(tmpx);
    mpz_init(tmpy);
    mpz_init(Bn);
    mpz_init(ans);

    if (k.type == 0) {
        for (;;) {
            element_to_mpz(tmph, wild);
            mpz_mod_ui(tmph, tmph, k.size);
            unsigned int step = 1 << mpz_get_ui(tmph);
            mpz_add_ui(Bn, Bn, step);
            mpz_set_ui(tmph, step);
            element_pp_pow(tmp, tmph, g_pp);
            element_mul(wild, wild, tmp);
            if (!element_cmp(wild, k.trap)) {
                failed = 0;
                break;
            }
            if (mpz_cmp(Bn, k.Am) > 0) {
                break;
            }
        }
    } else {
        for (;;) {
            element_to_mpz(tmpx, element_x(wild));
            element_to_mpz(tmpy, element_y(wild));
            mpz_add(tmph, tmpx, tmpy);
            mpz_mod_ui(tmph, tmph, k.size);
            unsigned int step = 1 << mpz_get_ui(tmph);
            mpz_add_ui(Bn, Bn, step);
            mpz_set_ui(tmph, step);
            element_pp_pow(tmp, tmph, g_pp);
            element_mul(wild, wild, tmp);
            if (!element_cmp(wild, k.trap)) {
                failed = 0;
                break;
            }
            if (mpz_cmp(Bn, k.Am) > 0) {
                break;
            }
        }
    }
    
    mpz_sub(ans, k.Am, Bn);
    if (!failed) element_set_mpz(x, ans);

    element_clear(wild);
    element_clear(tmp);
    element_pp_clear(g_pp);
    mpz_clear(tmph);
    mpz_clear(tmpx);
    mpz_clear(tmpy);
    mpz_clear(Bn);
    mpz_clear(ans);

    return failed;
}
