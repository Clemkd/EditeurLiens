#ifndef _CORRECTION_SYMBOLES_
#define _CORRECTION_SYMBOLES_

#include "API.h"

Sym_list correction_symboles(Elf32_Ehdr h, Shdr_list * l, Sym_list * sl, int * num_sections);

#endif
