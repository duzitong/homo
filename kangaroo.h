#pragma once
#include "utils.h"
#include <stdio.h>

/*
 * ref: https://web.northeastern.edu/seigen/11Magic/KruskalsCount/CryptographyKangaroosCardTricks.pdf
 */

struct Kangaroo {
    unsigned int size;
    int type; // 0 - int group, 1 - elliptic curve
    element_t trap;
    mpz_t Am;
};

int init_kangaroo(struct Kangaroo *, unsigned int, unsigned int, element_t, pairing_t, int);
int element_dlog_pollard_kangaroo(element_t, element_t, element_t, struct Kangaroo);
