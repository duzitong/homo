#pragma once
#include <pbc/pbc.h>

void rnd_non_zero(element_t);
void rnd_with_length_limited(element_t, unsigned int);
void rnd_non_equals(element_t, element_t);

void free_non_null(void *);
