/*
 * e-server.c
 *
 *  Created on: 11/01/2016
 *      Author: ricardo
 */
#include "functions_2_mail.h"
void testar_estrutura(char *er){
	FILE *new,*tree;
	LISTA lista;
	NODO nodo;
	ARVOREB avb;
	new = fopen(dir_builder(1,er,"tree_L_subjects.bin"),"rb");
	fseek(new,sizeof(NODO)*1,SEEK_SET);
	fread(&nodo,sizeof(NODO),1,new);
	tree = fopen(dir_builder(1,er,"tree_subjects.bin"),"rb");
	fread(&avb,sizeof(ARVOREB),1,tree);
	printf("\nchave[0] = %d\n", nodo.chaves[0]);
	printf("\nchave[1] = %d\n", nodo.chaves[1]);
	printf("\nchave[2] = %d\n", nodo.chaves[2]);
	printf("\nchave[3] = %d\n", nodo.chaves[3]);
	printf("\nchave[4] = %d\n", nodo.chaves[4]);
	printf("addresses[0] = %d\n", nodo.addresses[0]);
	printf("addresses[1] = %d\n", nodo.addresses[1]);
	printf("addresses[2] = %d\n", nodo.addresses[2]);
	printf("addresses[3] = %d\n", nodo.addresses[3]);
	printf("addresses[4] = %d\n", nodo.addresses[4]);

	printf("pai = %d\n", nodo.pai);
	printf("num_chaves = %d\n", nodo.num_chaves);
	printf("não é folha = %d\n", nodo.ne_folha);

	printf("AVB - raiz = %d\n", avb.raiz);
	printf("AVB - num_NODOS = %d\n", avb.num_NODOS);
	printf("AVB - num_SUB_NODOS = %d\n", avb.num_SUB_NODOS);
	printf("AVB - next_NODO = %d\n", avb.next_NODO);

	fclose(new);
	fclose(tree);
}

int main(void)
{
	int c;
	HORARIO hora;
	char *ass =(int *)malloc(sizeof(char)*100);

	char *er =detecta_os();
	printf("\n|| Bem vindo ao E-Server v.2.0\n ||");
	/*printf("\nString: %s -\n",get_text(1,er,2));
	add_text(1,er,"FML BOYS");

	//remove_text(1,er,2);/*/
printf("TESTE0: Configurando servidor\n");pause;


		setup(er);
	printf("TESTE1.0: Criando lista de endereços\n");pause;
		create_address_list(er);


	create_account(er,"adolfo@e-server.com","senha1");
	printf("TESTE1.1: Adicionando endereço 2\n");pause;
	create_account(er,"ricardo@e-server.com","senha1");



	printf("Adicionando Mensagens");
		add_text(1,er,"hehehehhehehehehehhehe, teste mano");
		add_text(1,er,"bora ver se funciona");
		add_text(1,er,"tem que funcionar");
		add_text(1,er,"é isso");

	printf("Adicionando Assuntos\n");
	for (c=0;c<10;c++)
	{
		sprintf(ass,"%s %d","ASSUNTO",c);
		add_subject(1,er,ass);
	}

	printf("Adicionando Horários\n");
		hora.data[0] = 1990;
		hora.data[1] = 1;
		hora.data[2] = 1;
		hora.data[3] = 12;
		hora.data[4] = 50;
		hora.data[5] = 29;
		add_horario(1,er,hora);
		add_horario(1,er,hora);
		add_horario(1,er,hora);

	printf("Adicionando Palavras\n");
		add_word(1,er,"Palavra 1");
		add_word(1,er,"Palavra 2");
		add_word(1,er,"Palavra 3");

	printf("Adicionando Emails\n");
		add_email(1,er,0,1,0,0,0,0);
		add_email(1,er,0,1,1,1,1,1);
		add_email(1,er,0,1,2,2,2,2);

	printf("Criando lista de Listas Encadeadas de Emails\n");

	printf("Adicionando Assuntos em árvore\n");
	add_SUB_NODO_tree(1,er,"","subjects.bin",0,0);
	testar_estrutura(er);
	add_SUB_NODO_tree(1,er,"","subjects.bin",1,1);
	testar_estrutura(er);
	add_SUB_NODO_tree(1,er,"","subjects.bin",2,2);
	testar_estrutura(er);
	/*
	add_SUB_NODO_tree(1,er,"","subjects.bin",3,900);
	testar_estrutura(er);
	add_SUB_NODO_tree(1,er,"","subjects.bin",4,1000);
	testar_estrutura(er);
	add_SUB_NODO_tree(1,er,"","subjects.bin",5,888);
	testar_estrutura(er);
	//add_SUB_NODO_tree(1,er,"","subjects.bin",6,28388);
	testar_estrutura(er);
	//add_SUB_NODO_tree(1,er,"","subjects.bin",7,5555);
	testar_estrutura(er);
	/**/
	print_email(1,er,0);
	testar_estrutura(er);
	printf("TESTE_FINAL\n");

	return 0;
}


//MUDANÇAS
