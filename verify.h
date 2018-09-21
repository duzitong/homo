#pragma once
#include "compute.h"
#include "enc.h"
#include "keygen.h"

int verify(element_t r, struct MK mk, struct Omega omega, pairing_t pairing);
