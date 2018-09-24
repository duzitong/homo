#include <stdio.h>
#include <pbc/pbc.h>

int main() {
    // init pairing
    pairing_t pairing;
    char param[1024];
    size_t count = fread(param, 1, 1024, stdin);
    if (!count) pbc_die("input error");
    pairing_init_set_buf(pairing, param, count);

    element_t g, h, gt;
    element_init_G1(g, pairing);
    element_init_G1(h, pairing);
    element_init_GT(gt, pairing);
    element_set_str(g, "[9, 4]", 10);
    element_set_str(h, "[5, 4]", 10);
    element_pairing(gt, g, h);

    element_printf("g: %B\n", g);
    element_printf("h: %B\n", h);
    element_printf("gt: %B\n", gt);

    return 0;
}
