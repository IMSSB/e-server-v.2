/*
 * functions_2.h
 *
 *  Created on: 11/01/2016
 *      Author: ricardo
 */

#ifndef FUNCTIONS_2_H_
#define FUNCTIONS_2_H_
#include "functions_2_struct.h"

void create_account(char *dir,char *user,char *password);
void print_email(int account_address,char *dir,int email_pos);
void print_horario(HORARIO data);
void setup();
void menu();
void criar_conta(char *dir);
void acessar_conta(char *dir);
void formated_message(char *string);

void create_account(char *dir,char *user,char *password)
{
	CONTA novaConta;
	int account_address = add_address(user,dir);
	char *folder;
	//novaConta.user = add_word(account_address,dir,user);
	//novaConta.password = add_word(account_address,dir,password);

	create_config(account_address,dir);

	create_LISTA_ENC(account_address,dir);
	create_email_list(account_address,dir);
	create_subject_list(account_address,dir);
	create_word_list(account_address,dir);
	create_text_list(account_address,dir);
	create_horario_list(account_address,dir);

	create_tree(account_address,dir,"","subjects.bin");
	create_tree(account_address,dir,"","messages.bin");
	create_tree(account_address,dir,"","HORARIO.bin");
	create_tree(account_address,dir,"","PALAVRA.bin");

	folder = dir_builder(account_address,dir,"inbox/");
	make_dir(folder);
	create_tree(account_address,dir,"inbox/","subjects.bin");
	create_tree(account_address,dir,"inbox/","messages.bin");
	create_tree(account_address,dir,"inbox/","HORARIO.bin");
	create_tree(account_address,dir,"inbox/","PALAVRA.bin");
	free(folder);

	folder = dir_builder(account_address,dir,"outbox/");
	make_dir(folder);
	create_tree(account_address,dir,"outbox/","subjects.bin");
	create_tree(account_address,dir,"outbox/","messages.bin");
	create_tree(account_address,dir,"outbox/","HORARIO.bin");
	create_tree(account_address,dir,"outbox/","PALAVRA.bin");
	free(folder);

	folder = dir_builder(account_address,dir,"read/");
	make_dir(folder);
	create_tree(account_address,dir,"read/","subjects.bin");
	create_tree(account_address,dir,"read/","messages.bin");
	create_tree(account_address,dir,"read/","HORARIO.bin");
	create_tree(account_address,dir,"read/","PALAVRA.bin");
	free(folder);

	folder = dir_builder(account_address,dir,"trash/");
	make_dir(folder);
	create_tree(account_address,dir,"trash/","subjects.bin");
	create_tree(account_address,dir,"trash/","messages.bin");
	create_tree(account_address,dir,"trash/","HORARIO.bin");
	create_tree(account_address,dir,"trash/","PALAVRA.bin");
	free(folder);

	folder = dir_builder(account_address,dir,"sent/");
	make_dir(folder);
	create_tree(account_address,dir,"sent/","subjects.bin");
	create_tree(account_address,dir,"sent/","messages.bin");
	create_tree(account_address,dir,"sent/","HORARIO.bin");
	create_tree(account_address,dir,"sent/","PALAVRA.bin");
	free(folder);

	return;
}

void print_email(int account_address,char *dir,int email_pos)
{
	char *address=dir_builder(account_address,dir,"email_list.bin");
	FILE *email_list,*to_print; 	// 	Arquivos que serão abertos
	SUB_NODO email; 				//	Manipulação de email
	messages mensagem;
	subjects assunto;
	HORARIO data;
	addresses remetente, destinatario;

	if (!(email_list = fopen(address,"rb")))
		error_m("Error at file opening");
	fseek(email_list,sizeof(SUB_NODO)*email_pos,SEEK_SET);
	fread(&email,sizeof(SUB_NODO),1,email_list);
	fclose(email_list);
	free(address);

	address=dir_builder(account_address,dir,"text_list.bin");
	if (!(to_print = fopen(address,"rb")))
		error_m("Error at file opening");
	fseek(to_print,sizeof(messages)*email.MSG,SEEK_SET);
	fread(&mensagem,sizeof(messages),1,to_print);
	fclose(to_print);
	free(address);

	address=dir_builder(account_address,dir,"subject_list.bin");
	if (!(to_print = fopen(address,"rb")))
		error_m("Error at file opening");
	fseek(to_print,sizeof(subjects)*email.assunto,SEEK_SET);
	fread(&assunto,sizeof(subjects),1,to_print);
	fclose(to_print);
	free(address);

	address=dir_builder(account_address,dir,"horario_list.bin");
	if (!(to_print = fopen(address,"rb")))
		error_m("Error at file opening");
	fseek(to_print,sizeof(HORARIO)*email.data,SEEK_SET);
	fread(&data,sizeof(HORARIO),1,to_print);
	fclose(to_print);
	free(address);

	address=filepath_gen(dir,"addresses.bin");
	if (!(to_print = fopen(address,"rb")))
		error_m("Error at file opening");
	fseek(to_print,sizeof(addresses)*email.remetente,SEEK_SET);
	fread(&remetente,sizeof(addresses),1,to_print);
	fseek(to_print,sizeof(addresses)*email.destinatario,SEEK_SET);
	fread(&destinatario,sizeof(addresses),1,to_print);
	fclose(to_print);
	free(address);

	breakline;
	print_horario(data);
	breakline;
	printf("Remetente: %s\n",remetente.address);
	printf("Destinatário: %s\n",destinatario.address);
	printf("Assunto: %s\n",assunto.subject);
	printf("%s\n",mensagem.mail);

	//	Implementar impressão do histórico (recursão?)
	// 	Melhorar formatação da impressão
}

void print_horario(HORARIO data)
{
	printf("%00d/%00d/%0000d %00d:%00d:%00d",
			data.data[2],data.data[1],data.data[0],
			data.data[3],data.data[4],data.data[5]);
}
void project_presentation()
{
	line;
	formated_message("E-Server v.2.0");
	formated_message("Trabalho da Disciplina Algoritmos e Estrutura de Dados II");
	formated_message("Professora: Ana Emilia de Melo Queiroz");
	formated_message("Alunos:     Ricardo Valério Teixeira de Medeiros Silva");
	formated_message("            Ruan de Medeiros Bahia");
	formated_message("Simulador de um servidor de e-mails, sendo salvos em arquivos,");
	formated_message("com uso de Árvores B para pesquisas nos dados");
	line;

	pause;
	cls;

	return;
}

void setup()
{
	FILE *set;
	settings config;
	char *caminho;
	int opcao;

	breakline;
	printf("Configuração do Servidor");
	breakline;
	if ((set = fopen("settings.bin","r+b")))
	{
		printf("Foi detectada que um arquivo de configuração anterior do servidor já foi criado, funcionando na pasta:");
		breakline;

		fread(&config,sizeof(settings),1,set);
		printf("%s",config.dir);

		breakline;
		printf("Deseja alterar o caminho da pasta de funcionamento do servidor? [0] Não - [1] Sim");
		breakline;
		scanf("%d",&opcao);
		if (opcao != 1)
		{
			fclose(set);
			return;
		}
	}
	else
		if (!(set = fopen("settings.bin","wb")))
			error_m("Error at file allocation");

	printf("Digite o caminho completo para o diretório em que o servidor de e-mails irá funcionar: (Ex: C:\\E-Server\\\n");
	breakline;
	caminho = ler('\n');

	make_dir(caminho);
	setup_server(caminho);
	create_address_list(caminho);
	sprintf(config.dir,"%s",caminho);
	rewind(set);
	fwrite(&config,sizeof(settings),1,set);
	fclose(set);

	printf("Servidor configurado corretamente na pasta: %s",caminho);

	pause;
	cls;
	return;
}

void menu()
{
	FILE *set;
	settings config;
	int opcao=0;
	if (!(set = fopen("settings.bin","r+b")))
	{
		printf("Foi detectado que essa é a primeira abertura do E-Server v.2.0");
		breakline;
		printf("É necessário que seja feita a configuração inicial para funcionamento do programa");
		breakline;
		setup();
	}
	else
		fclose(set);

	do {
		if (!(set = fopen("settings.bin","r+b")))
			error_m("Error at file opening");
		fread(&config,sizeof(settings),1,set);
		fclose(set);

		printf("Selecione o que deseja fazer:"); breakline;
		printf("[1] Criar conta de e-mail"); breakline;
		printf("[2] Acessar uma conta de e-mail"); breakline;
		printf("[3] Reconfigurar servidor"); breakline;
		printf("[0] Fechar programa"); breakline;
		scanf("%d",&opcao);
		cls;
		switch (opcao)
		{
			case 1: // 	Criar conta
				criar_conta(config.dir);
			break;
			case 2:	//	Acessar uma conta
				acessar_conta(config.dir);
			break;
			case 3:	//	Configurar
				setup();
			break;

			default:

			break;
		}
	} while(opcao);

	return;
}
void criar_conta(char *dir)
{
	char *user,*password;
	printf("Digite o nome de usuário:"); breakline;
	user = ler('\n');
	printf("Digite a senha para a conta"); breakline;
	password = ler('\n');
	printf("--->%s\n",dir);
	pause;
	create_account(dir,user,password);
	printf("Conta de e-mail criada com sucesso!"); breakline;
	printf("Agora você pode acessá-la pelo menu principal."); breakline;

	pause;
	cls;
	return;
}

void acessar_conta(char *dir)
{
	int c;

	return;
}

void formated_message(char *string){
	printf("%s %-66s %s\n",
				"\\\\\\\\\t",
				string,
				"\t\\\\\\\\");
}

#endif /* FUNCTIONS_2_H_ */
