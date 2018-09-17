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
