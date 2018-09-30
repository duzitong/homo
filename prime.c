#include <pbc/pbc.h>

int main(){
    pbc_param_t par;
    pbc_param_init_a_gen(par, 3, 5);
    pbc_param_out_str(stdout, par);
}
