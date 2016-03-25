/*
 * e-server.c
 *
 *  Created on: 11/01/2016
 *      Author: ricardo
 */

#include "functions_2_mail.h"

void testar_estrutura(char *er)
{
	FILE *new,*tree;
	LISTA lista;
	NODO nodo;
	ARVOREB avb;
	new = fopen(dir_builder(er,1,"tree_L_subjects.bin"),"rb");
	fseek(new,sizeof(NODO)*3,SEEK_SET);
	fread(&nodo,sizeof(NODO),1,new);
	tree = fopen(dir_builder(er,1,"tree_subjects.bin"),"rb");
	fread(&avb,sizeof(ARVOREB),1,tree);
	print_nodo(nodo);
	print_arvoreb(avb);
	fclose(new);
	fclose(tree);
}


int main(void)
{
	setlocale(LC_ALL,"Portuguese");
	project_presentation();
	menu();

	return 0;
}


//MUDANÇAS

