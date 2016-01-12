#include "correction_symboles.h"

//Rappel :
//sym_list est global
//tableau d'index sections est global
//le header est global
//

void correction_symboles(Elf32_Ehdr h, Shdr_list * l, Sym_list * sl, int * num_sections)
{
	Shdr_list * L;
	Shdr_list * S = find_symbols_section(l);
	void* dump = S->dump;
	
	// Correction
	int i; 
	for(i = 0; i < sl->nb; i++)
	{
		// Re-indexation des sections correspondants au symbole
		sl->list[i].st_shndx = num_sections[sl->list[i].st_shndx];
		/* DEBUG !!!! */  sl->list[i].st_value += 100;
		
		// Calcul de la valeur du symbole, i.e son adresse qui vaut offset + adresse de chargement de sa section correspondante 
		L = find_section((unsigned int)sl->list[i].st_shndx, l);
		sl->list[i].st_value += L->header.sh_addr;
		
		// Ecriture dans la section
		((uint32_t*)dump)[0] = recuperer_valeur32(h, sl->list[i].st_name );
		((uint32_t*)dump)[1] = recuperer_valeur32(h, sl->list[i].st_value );
		((uint32_t*)dump)[2] = recuperer_valeur32(h, sl->list[i].st_size );
		((uint16_t*)dump)[7] = recuperer_valeur16(h, sl->list[i].st_shndx );
		
		((unsigned char*)dump)[12] = sl->list[i].st_info;
		((unsigned char*)dump)[13] = sl->list[i].st_other;
		
	}	
}