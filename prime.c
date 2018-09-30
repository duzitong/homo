#include <pbc/pbc.h>

int main(){
    pbc_param_t par;
    pbc_param_init_a_gen(par, 4, 10);
    pbc_param_out_str(stdout, par);
}
