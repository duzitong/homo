#pragma once
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pbc/pbc.h>

void read_q(mpz_t, char*);

void rnd_init(gmp_randstate_t);
void rnd_q(mpz_t, gmp_randstate_t, const mpz_t);

void element_exp(element_t, element_t, int);
