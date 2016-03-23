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
void print_email(ARQUIVOS arquivos,int email_pos);
void print_horario(HORARIO data);
void setup();
void menu();
void criar_conta(char *dir);
void acessar_conta(char *dir);
ARQUIVOS open_account_files(char *dir, int account_address);
void close_account_files(ARQUIVOS arquivos);
void formated_message(char *string);

void create_account(char *dir,char *user,char *password)
{
	int account_address = add_address(dir,user,password);
	char *folder;

	create_config(dir,account_address);

	create_LISTA_ENC(dir,account_address);
	create_email_list(dir,account_address);
	create_subject_list(dir,account_address);
	create_word_list(dir,account_address);
	create_text_list(dir,account_address);
	create_horario_list(dir,account_address);

	create_tree_type(dir,account_address,"","subjects.bin");
	create_tree_type(dir,account_address,"","messages.bin");
	create_tree_type(dir,account_address,"","HORARIO.bin");
	create_tree_type(dir,account_address,"","PALAVRA.bin");

	folder = dir_builder(dir,account_address,"inbox/");
	make_dir(folder);
	create_tree_type(dir,account_address,"inbox/","subjects.bin");
	create_tree_type(dir,account_address,"inbox/","messages.bin");
	create_tree_type(dir,account_address,"inbox/","HORARIO.bin");
	create_tree_type(dir,account_address,"inbox/","PALAVRA.bin");
	free(folder);

	folder = dir_builder(dir,account_address,"outbox/");
	make_dir(folder);
	create_tree_type(dir,account_address,"outbox/","subjects.bin");
	create_tree_type(dir,account_address,"outbox/","messages.bin");
	create_tree_type(dir,account_address,"outbox/","HORARIO.bin");
	create_tree_type(dir,account_address,"outbox/","PALAVRA.bin");
	free(folder);

	folder = dir_builder(dir,account_address,"read/");
	make_dir(folder);
	create_tree_type(dir,account_address,"read/","subjects.bin");
	create_tree_type(dir,account_address,"read/","messages.bin");
	create_tree_type(dir,account_address,"read/","HORARIO.bin");
	create_tree_type(dir,account_address,"read/","PALAVRA.bin");
	free(folder);

	folder = dir_builder(dir,account_address,"trash/");
	make_dir(folder);
	create_tree_type(dir,account_address,"trash/","subjects.bin");
	create_tree_type(dir,account_address,"trash/","messages.bin");
	create_tree_type(dir,account_address,"trash/","HORARIO.bin");
	create_tree_type(dir,account_address,"trash/","PALAVRA.bin");
	free(folder);

	folder = dir_builder(dir,account_address,"sent/");
	make_dir(folder);
	create_tree_type(dir,account_address,"sent/","subjects.bin");
	create_tree_type(dir,account_address,"sent/","messages.bin");
	create_tree_type(dir,account_address,"sent/","HORARIO.bin");
	create_tree_type(dir,account_address,"sent/","PALAVRA.bin");
	free(folder);

	return;
}

void print_email(ARQUIVOS arquivos,int email_pos)
{
	SUB_NODO email; 				//	Manipulação de email
	messages mensagem;
	subjects assunto;
	HORARIO data;
	addresses remetente, destinatario;

	fseek(arquivos.email_list,sizeof(SUB_NODO)*email_pos,SEEK_SET);
	fread(&email,sizeof(SUB_NODO),1,arquivos.email_list);

	fseek(arquivos.text_list,sizeof(messages)*email.MSG,SEEK_SET);
	fread(&mensagem,sizeof(messages),1,arquivos.text_list);

	fseek(arquivos.subject_list,sizeof(subjects)*email.assunto,SEEK_SET);
	fread(&assunto,sizeof(subjects),1,arquivos.subject_list);

	fseek(arquivos.horario_list,sizeof(HORARIO)*email.data,SEEK_SET);
	fread(&data,sizeof(HORARIO),1,arquivos.horario_list);

	fseek(arquivos.addresses,sizeof(addresses)*email.remetente,SEEK_SET);
	fread(&remetente,sizeof(addresses),1,arquivos.addresses);
	fseek(arquivos.addresses,sizeof(addresses)*email.destinatario,SEEK_SET);
	fread(&destinatario,sizeof(addresses),1,arquivos.addresses);

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

	printf("Digite o caminho completo para o diretório em que o servidor de e-mails irá funcionar: (Ex: C:\\E-Server\\\n");
	breakline;
	caminho = ler('\n');

	make_dir(caminho);
	if (opcao == 1)
	{
		sprintf(config.dir,"%s",caminho);
		rewind(set);
		fwrite(&config,sizeof(settings),1,set);
	}
	else {
		setup_server(caminho);
		create_address_list(caminho);
	}

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

ARQUIVOS open_account_files(char *dir, int account_address)
{
	ARQUIVOS arquivos;
	char *arquivo;
	//	Arquivos Gerais
	arquivo=filepath_gen(dir,"addresses.bin");
	if (!(arquivos.addresses = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"config.bin");
	if (!(arquivos.config = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"email_list.bin");
	if (!(arquivos.email_list = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"horario_list.bin");
	if (!(arquivos.horario_list = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"subject_list.bin");
	if (!(arquivos.subject_list = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"text_list.bin");
	if (!(arquivos.text_list = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"word_list.bin");
	if (!(arquivos.word_list = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"lista_enc.bin");
	if (!(arquivos.lista_enc = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	//	Árvores Gerais
	arquivo=dir_builder(dir,account_address,"tree_HORARIO.bin");
	if (!(arquivos.tree_HORARIO = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"tree_messages.bin");
	if (!(arquivos.tree_messages = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"tree_PALAVRA.bin");
	if (!(arquivos.tree_PALAVRA = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"tree_subjects.bin");
	if (!(arquivos.tree_subjects = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"tree_L_HORARIO.bin");
	if (!(arquivos.tree_L_HORARIO = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"tree_L_messages.bin");
	if (!(arquivos.tree_L_messages = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"tree_L_PALAVRA.bin");
	if (!(arquivos.tree_L_PALAVRA = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"tree_L_subjects.bin");
	if (!(arquivos.tree_L_subjects = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	//	Caixas de Emails
	//	Árvores de Inbox
	arquivo=dir_builder(dir,account_address,"inbox/tree_HORARIO.bin");
	if (!(arquivos.inbox_tree_HORARIO = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"inbox/tree_messages.bin");
	if (!(arquivos.inbox_tree_messages = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"inbox/tree_PALAVRA.bin");
	if (!(arquivos.inbox_tree_PALAVRA = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"inbox/tree_subjects.bin");
	if (!(arquivos.inbox_tree_subjects = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"inbox/tree_L_HORARIO.bin");
	if (!(arquivos.inbox_tree_L_HORARIO = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"inbox/tree_L_messages.bin");
	if (!(arquivos.inbox_tree_L_messages = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"inbox/tree_L_PALAVRA.bin");
	if (!(arquivos.inbox_tree_L_PALAVRA = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"inbox/tree_L_subjects.bin");
	if (!(arquivos.inbox_tree_L_subjects = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	//	Árvores de Outbox
	arquivo=dir_builder(dir,account_address,"outbox/tree_HORARIO.bin");
	if (!(arquivos.outbox_tree_HORARIO = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"outbox/tree_messages.bin");
	if (!(arquivos.outbox_tree_messages = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"outbox/tree_PALAVRA.bin");
	if (!(arquivos.outbox_tree_PALAVRA = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"outbox/tree_subjects.bin");
	if (!(arquivos.outbox_tree_subjects = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"outbox/tree_L_HORARIO.bin");
	if (!(arquivos.outbox_tree_L_HORARIO = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"outbox/tree_L_messages.bin");
	if (!(arquivos.outbox_tree_L_messages = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"outbox/tree_L_PALAVRA.bin");
	if (!(arquivos.outbox_tree_L_PALAVRA = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"outbox/tree_L_subjects.bin");
	if (!(arquivos.outbox_tree_L_subjects = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	//	Árvores de Read
	arquivo=dir_builder(dir,account_address,"read/tree_HORARIO.bin");
	if (!(arquivos.read_tree_HORARIO = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"read/tree_messages.bin");
	if (!(arquivos.read_tree_messages = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"read/tree_PALAVRA.bin");
	if (!(arquivos.read_tree_PALAVRA = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"read/tree_subjects.bin");
	if (!(arquivos.read_tree_subjects = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"read/tree_L_HORARIO.bin");
	if (!(arquivos.read_tree_L_HORARIO = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"read/tree_L_messages.bin");
	if (!(arquivos.read_tree_L_messages = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"read/tree_L_PALAVRA.bin");
	if (!(arquivos.read_tree_L_PALAVRA = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"read/tree_L_subjects.bin");
	if (!(arquivos.read_tree_L_subjects = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	//	Árvores de Sent
	arquivo=dir_builder(dir,account_address,"sent/tree_HORARIO.bin");
	if (!(arquivos.sent_tree_HORARIO = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"sent/tree_messages.bin");
	if (!(arquivos.sent_tree_messages = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"sent/tree_PALAVRA.bin");
	if (!(arquivos.sent_tree_PALAVRA = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"sent/tree_subjects.bin");
	if (!(arquivos.sent_tree_subjects = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"sent/tree_L_HORARIO.bin");
	if (!(arquivos.sent_tree_L_HORARIO = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"sent/tree_L_messages.bin");
	if (!(arquivos.sent_tree_L_messages = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"sent/tree_L_PALAVRA.bin");
	if (!(arquivos.sent_tree_L_PALAVRA = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"sent/tree_L_subjects.bin");
	if (!(arquivos.sent_tree_L_subjects = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	//	Árvores de Trash
	arquivo=dir_builder(dir,account_address,"trash/tree_HORARIO.bin");
	if (!(arquivos.trash_tree_HORARIO = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"trash/tree_messages.bin");
	if (!(arquivos.trash_tree_messages = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"trash/tree_PALAVRA.bin");
	if (!(arquivos.trash_tree_PALAVRA = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"trash/tree_subjects.bin");
	if (!(arquivos.trash_tree_subjects = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"trash/tree_L_HORARIO.bin");
	if (!(arquivos.trash_tree_L_HORARIO = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"trash/tree_L_messages.bin");
	if (!(arquivos.trash_tree_L_messages = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"trash/tree_L_PALAVRA.bin");
	if (!(arquivos.trash_tree_L_PALAVRA = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"trash/tree_L_subjects.bin");
	if (!(arquivos.trash_tree_L_subjects = fopen(arquivo,"rb+")))
		error_m("Error at file opening");
	free(arquivo);

	return arquivos;
}

void close_account_files(ARQUIVOS arquivos)
{
	fclose(arquivos.config);
	fclose(arquivos.email_list);
	fclose(arquivos.horario_list);
	fclose(arquivos.text_list);
	fclose(arquivos.subject_list);
	fclose(arquivos.word_list);
	fclose(arquivos.lista_enc);
	fclose(arquivos.tree_HORARIO);
	fclose(arquivos.tree_PALAVRA);
	fclose(arquivos.tree_messages);
	fclose(arquivos.tree_subjects);
	fclose(arquivos.tree_L_HORARIO);
	fclose(arquivos.tree_L_PALAVRA);
	fclose(arquivos.tree_L_messages);
	fclose(arquivos.tree_L_subjects);
	fclose(arquivos.inbox_tree_HORARIO);
	fclose(arquivos.inbox_tree_PALAVRA);
	fclose(arquivos.inbox_tree_messages);
	fclose(arquivos.inbox_tree_subjects);
	fclose(arquivos.inbox_tree_L_HORARIO);
	fclose(arquivos.inbox_tree_L_PALAVRA);
	fclose(arquivos.inbox_tree_L_messages);
	fclose(arquivos.inbox_tree_L_subjects);
	fclose(arquivos.outbox_tree_HORARIO);
	fclose(arquivos.outbox_tree_PALAVRA);
	fclose(arquivos.outbox_tree_messages);
	fclose(arquivos.outbox_tree_subjects);
	fclose(arquivos.outbox_tree_L_HORARIO);
	fclose(arquivos.outbox_tree_L_PALAVRA);
	fclose(arquivos.outbox_tree_L_messages);
	fclose(arquivos.outbox_tree_L_subjects);
	fclose(arquivos.read_tree_HORARIO);
	fclose(arquivos.read_tree_PALAVRA);
	fclose(arquivos.read_tree_messages);
	fclose(arquivos.read_tree_subjects);
	fclose(arquivos.read_tree_L_HORARIO);
	fclose(arquivos.read_tree_L_PALAVRA);
	fclose(arquivos.read_tree_L_messages);
	fclose(arquivos.read_tree_L_subjects);
	fclose(arquivos.sent_tree_HORARIO);
	fclose(arquivos.sent_tree_PALAVRA);
	fclose(arquivos.sent_tree_messages);
	fclose(arquivos.sent_tree_subjects);
	fclose(arquivos.sent_tree_L_HORARIO);
	fclose(arquivos.sent_tree_L_PALAVRA);
	fclose(arquivos.sent_tree_L_messages);
	fclose(arquivos.sent_tree_L_subjects);
	fclose(arquivos.trash_tree_HORARIO);
	fclose(arquivos.trash_tree_PALAVRA);
	fclose(arquivos.trash_tree_messages);
	fclose(arquivos.trash_tree_subjects);
	fclose(arquivos.trash_tree_L_HORARIO);
	fclose(arquivos.trash_tree_L_PALAVRA);
	fclose(arquivos.trash_tree_L_messages);
	fclose(arquivos.trash_tree_L_subjects);
	return;
}

void formated_message(char *string){
	printf("%s %-66s %s\n",
				"\\\\\\\\\t",
				string,
				"\t\\\\\\\\");
}

#endif /* FUNCTIONS_2_H_ */
