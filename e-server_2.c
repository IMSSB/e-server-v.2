/*
 * e-server.c
 *
 *  Created on: 11/01/2016
 *      Author: ricardo
 */
#include "functions_2_mail.h"


int main(void)
{
	//int c;
	HORARIO hora;
	FILE *novo;
	LISTA lista;
	NODO nodo;
	ARVOREB avb;
	char *er =detecta_os();
	printf("\n|| Bem vindo ao E-Server v.2.0\n ||");
	/*printf("\nString: %s -\n",get_text(1,er,2));
	add_text(1,er,"FML BOYS");

	//remove_text(1,er,2);/*/
	/*
	printf("TESTE0: Configurando servidor\n");pause;


		setup(er);
	printf("TESTE1.0: Criando lista de endereços\n");pause;
		create_address_list(er);
	printf("TESTE1.1: Adicionando endereço\n");pause;
		add_address("ruanmed@e-server.com",er);
	printf("TESTE1.1: Adicionando endereço 2\n");pause;
		add_address("ricardo@e-server.com",er);
	ler_end(er);
	printf("TESTE1.3: Removendo endereço 0\n");pause;
		remove_address(0,er);
	ler_end(er);
	printf("TESTE1.5: Adicionando endereço\n");pause;
		add_address("adolfo@e-server.com",er);
	ler_end(er);
	printf("TESTE2.0: Criando config Adolfo\n");pause;
		create_config(0,er);
	printf("TESTE2.0: Criando config Ricardo\n");pause;
		create_config(1,er);


	*/

	/*printf("Criando lista de Mensagens");
		create_text_list(1,er);
		add_text(1,er,"hehehehhehehehehehhehe, teste mano");
		add_text(1,er,"bora ver se funciona");
		add_text(1,er,"tem que funcionar");
		add_text(1,er,"é isso");
	*/
	/*
	printf("Criando lista de Assuntos\n");
		create_subject_list(1,er);
		add_subject(1,er,"ASSUNTO 1");


	printf("Criando lista de Horários\n");
		create_horario_list(1,er);
		hora.data[0] = 1990;
		hora.data[1] = 1;
		hora.data[2] = 1;
		hora.data[3] = 12;
		hora.data[4] = 50;
		hora.data[5] = 29;
		add_horario(1,er,hora);

	printf("Criando lista de Palavras\n");
		create_word_list(1,er);
		add_word(1,er,"Palavra 1");

	printf("Criando lista de Emails\n");
		create_email_list(1,er);
		add_email(1,er,0,1,0,0,0,0);

	printf("Criando lista de Listas Encadeadas de Emails\n");
		create_LISTA_ENC(1,er);
		add_LISTA_ENC(1,er,-1,0);
		*/
	printf("Criando árvore de Assuntos\n");
	//create_tree(1,er,"subjects.bin");
	add_SUB_NODO_tree(1,er,"subjects.bin",0,2);
	//add_SUB_NODO_tree(1,er,"subjects.bin",1,1);
	//add_email(1,er,0,1,1,1,1,1);
	//add_subject(1,er,"ASSUNTO 2");


	novo = fopen(dir_builder(1,er,"tree_L_subjects.bin"),"r+b");
	fread(&nodo,sizeof(NODO),1,novo);
	printf("\nchave[0] = %d\n", nodo.chaves[0]);
	printf("\nchave[1] = %d\n", nodo.chaves[1]);
	printf("\nchave[2] = %d\n", nodo.chaves[2]);
	printf("addresses[0] = %d\n", nodo.addresses[0]);
	printf("addresses[1] = %d\n", nodo.addresses[1]);
	printf("addresses[2] = %d\n", nodo.addresses[2]);
	printf("pai = %d\n", nodo.pai);
	printf("num_chaves = %d\n", nodo.num_chaves);
	printf("não é folha = %d\n", nodo.ne_folha);

	printf("TESTE_FINAL\n");
	return 0;
}


//MUDANÇAS
