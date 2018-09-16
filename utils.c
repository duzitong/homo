#include "utils.h"

void read_q(mpz_t q, char* param) {
    char type[20], name[3][3], v[3][200];
    sscanf(param, "type %s\n%s %s\n%s %s\n%s %s", type, name[0], v[0], name[1], v[1], name[2], v[2]);
    for (int i = 0; i < 3; i++) {
        if (strcmp(name[i], "n") == 0) {
            mpz_set_str(q, v[i], 10);
            return;
        }
    }
}

void element_exp(element_t res, element_t a, int exp) {
    element_set1(res);
    for (int i = 0; i < exp; i++) {
        element_mul(res, res, a);
    }
}
