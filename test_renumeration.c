#include "renumeration_section.h"
#include "correction_symboles.h"

int main(int argc, char * argv[])
{
	FILE* f = NULL, *fres = NULL;
	if((f = fopen(argv[1], "r")) == NULL)
	{
		printf("Erreur lors de la lecture du fichier ELF");
		return -1;
	}
	
	printf("[+]Lecture du fichier elf...\n");
	
	Elf32_Ehdr header;
	Shdr_list shdr_list;
	Sym_list sym_list;
	
	// Lecture dans le ficheir 
	read_Elf32_Ehdr(f, &header);
	read_Shdr_list(f, header, &shdr_list);
	read_Sym_list(f, header, &sym_list);
	
	// Suppression des sections de relocation 
	printf("[+]Séparation des sections de relocation (.rel) ...\n");
	enlever_relocation();
		
	// Affichage a l'ecran 
	//afficher_Shdr_list(shdr_list);
	//afficher_Shdr_list(rel_list);
	//afficher_tableau_sections();
	
	// Correction des symboles : 
	printf("[+]Correction des symboles...\n");
	correction_symboles();
	
	// Ecriture dans un fichier 
	
	if((fres = fopen("elfres.exe", "w")) == NULL)
	{
		printf("Erreur lors de la lecture du fichier ELF");
		return -1;
	}
	
	printf("[+]Création du fichier elf executable 'elfres.exe'...\n");
	write_Elf32_Ehdr(fres, header);
	write_Shdr_list(fres, header, &shdr_list);
	
	fclose(f);
	fclose(fres);
	
	printf("[-]Transformation terminee, le resultat peut etre observe via 'readelf [opt] elfres.exe' \n\n");
	
	return 0;
}
