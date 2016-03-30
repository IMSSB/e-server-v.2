/*
 * functions_2_mail.c
 *
 *  Created on: 25/03/2016
 *      Author: Ruan
 */

#include "functions_2_mail.h"

void menu()
{
	PRINCIPAL *principal = open_server_files();
	settings config;
	int opcao=0,nova_opcao=0,tecla=0,loop=1;
	char *roll[4],cursor[]="-->",vazio[]="   ";
	roll[0]=cursor;
	roll[1]=roll[2]=roll[3]=vazio;

	if (!(principal->settings))
	{
		printf("Foi detectado que essa é a primeira abertura do E-Server v.2.0");
		breakline;
		printf("É necessário que seja feita a configuração inicial para funcionamento do programa.");
		breakline;
		setup(principal);
		principal = open_server_files();
	}

	do {
		rewind(principal->settings);
		fread(&config,sizeof(settings),1,principal->settings);

		while(tecla!=KeyEnter)
		{
			if(opcao-nova_opcao)
			{
				roll[opcao]=vazio;
				roll[nova_opcao]=cursor;
				opcao=nova_opcao;
			}
			printf("Selecione o que deseja fazer e aperte ENTER:"); breakline;
			printf("%s |Criar conta de e-mail",roll[0]); breakline;
			printf("%s |Acessar uma conta de e-mail",roll[1]); breakline;
			printf("%s |Reconfigurar servidor",roll[2]); breakline;
			printf("%s |Fechar programa",roll[3]); breakline;
			breakline;

			kbhit();
			tecla = getch();
			while (tecla != KeySpecial2 && tecla != KeyEnter)
				tecla = getch();
			if (tecla == KeySpecial2)
			{
				tecla = getch();
				if (tecla == KeyUp)
				{
					if (opcao)
						nova_opcao--;
				}
				else if (tecla == KeyDown)
				{
					if (opcao < 3)
						nova_opcao++;
				}
			}
			cls;
		}
		tecla=0;
		switch (opcao)
		{
			case 0: // 	Criar conta
				criar_conta(principal,config.dir);
			break;
			case 1:	//	Acessar uma conta
				acessar_conta(principal,config.dir);
			break;
			case 2:	//	Configurar
				setup(principal);
				close_server_files(principal);	//	Fecha arquivos antigos se tiver sido efetuada alguma altera��o
				principal = open_server_files();	//	Abre novos arquivos
			break;
			case 3:
				loop = 0;
			break;
			default:

			break;
		}
	} while(loop);
	printf("Obrigado por utilizar o E-Server v.0.2"); breakline;
	close_server_files(principal);
	return;
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


void setup(PRINCIPAL *principal)
{
	settings config;
	char *caminho;
	int opcao;

	breakline;
	printf("Configuração do Servidor");
	breakline;
	if ((principal->settings))
	{
		printf("Foi detectada que um arquivo de configura��o anterior do servidor j� foi criado, funcionando na pasta:");
		breakline;

		rewind(principal->settings);
		fread(&config,sizeof(settings),1,principal->settings);
		printf("%s",config.dir);

		breakline;
		printf("Deseja alterar o caminho da pasta de funcionamento do servidor? [0] Não - [1] Sim");
		breakline;
		scanf("%d",&opcao);
		if (opcao != 1)
			return;
	}

	printf("Digite o caminho completo para o diretório em que o servidor de e-mails irá funcionar: (Ex: C:\\E-Server\\\n");
	breakline;
	caminho = ler('\n');

	make_dir(caminho);
	if (opcao == 1)
	{
		sprintf(config.dir,"%s",caminho);
		rewind(principal->settings);
		fwrite(&config,sizeof(settings),1,principal->settings);
	}
	else {
		setup_server(caminho);
		create_address_list(caminho);
		create_tree_account(caminho);
	}

	printf("Servidor configurado corretamente na pasta: %s",caminho);

	pause;
	cls;
	return;
}


void create_account(PRINCIPAL *principal,char *dir,char *user,char *password)
{
	int account_address = add_address(principal->settings,principal->addresses,user,password);
	char *folder;
	close_server_files(principal);
	principal = open_server_files();
	add_CONTA_tree(principal->addresses,principal->tree_CONTA,principal->tree_L_CONTA,account_address);

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
void criar_conta(PRINCIPAL *principal,char *dir)
{
	char *user,*password=(char *)calloc(sizeof(char),1);
	int conta,temp;

	do {
		formated_message("CRIAÇÃO DE CONTA DE USU�RIO");
		printf("Digite o nome de usuário:"); breakline;
		user = ler('\n');
		temp = add_address(principal->settings,principal->addresses,user,password);

		conta = busca_CONTA_tree(principal->addresses,principal->tree_CONTA, principal->tree_L_CONTA,temp);
		if (conta != -1)
			printf("Uma conta de email com esse nome j� existe. Por favor tente com outro nome de usu�rio.\n");
		pause;
		cls;
		remove_address(principal->settings,principal->addresses,temp);

	} while(conta != -1);
	free(password);

	printf("Digite uma senha para a conta:"); breakline;
	password = ler('\n');

	pause;
	create_account(principal,dir,user,password);
	printf("Conta de e-mail criada com sucesso!"); breakline;
	printf("Agora você pode acessá-la pelo menu principal."); breakline;

	pause;
	cls;
	return;
}


void acessar_conta(PRINCIPAL *principal,char *dir)
{
	char *user,*password=(char *)calloc(sizeof(char),1),*t;
	int temp, conta, confirmacao;

	do {
		formated_message("ACESSAR UMA CONTA");
		printf("Digite o nome de usuário:"); breakline;
		user = ler('\n');
		temp = add_address(principal->settings,principal->addresses,user,password);

		conta = busca_CONTA_tree(principal->addresses,principal->tree_CONTA, principal->tree_L_CONTA,temp);

		if (conta == -1)
			printf("A conta de email não foi localizada, por favor tente novamente com um email válido.\n");
		pause;
		cls;
		remove_address(principal->settings,principal->addresses,temp);
	} while(conta == -1);
	free(password);

	do {
		printf("Digite a senha da conta:"); breakline;
		password = ler('\n');
		t = get_password(principal->addresses,conta);
		if ((confirmacao = strcmp(password,t)))
			printf("Senha inválida. Tente novamente com a senha correta.");
		pause;
		cls;
	} while(confirmacao);
	printf("Acesso autorizado à conta: %s.\n",user);
	pause;
	cls;
	abrir_conta(principal,dir,conta);
	return;
}

int generic_account_menu(MENU_GUIDE GUIDE)
{
	int opcao=0,nova_opcao=0,tecla=0,loop=1,c,total_itens=GUIDE.num_headered_itens+GUIDE.num_simple_itens;
	char *roll[total_itens],cursor[]="-->",vazio[]="   ";//Uma roubadinha

	for(c=0;c<total_itens;c++)
	{
		if(!c)
			roll[c]=cursor;
		else
			roll[c]=vazio;
	}


	do {
		while(tecla!=KeyEnter)
		{
			if(opcao-nova_opcao)
			{
				roll[opcao]=vazio;
				roll[nova_opcao]=cursor;
				opcao=nova_opcao;
			}
			printf("\n%s",GUIDE.menu_header); breakline;
			for(c=0;c<total_itens;c++)
			{
				if(c<GUIDE.num_headered_itens)
					printf("%s |%21s (%d)",roll[c],GUIDE.headered_titles[c],GUIDE.headers[c]);
				else
					printf("%s |%25s",roll[c],GUIDE.simple_titles[c-GUIDE.num_headered_itens]);

				breakline;
			}

			tecla = getch();
			while (tecla != KeySpecial2 && tecla != KeyEnter)
				tecla = getch();
			if (tecla == KeySpecial2)
			{
				tecla = getch();
				if (tecla == KeyUp)
				{
					if (opcao)
						nova_opcao--;
				}
				else if (tecla == KeyDown)
				{
					if (opcao < total_itens)
						nova_opcao++;
				}
			}
			cls;
		}//Apertou enter, saiu

		loop=0;

	}while(loop);

	return opcao;
}

void abrir_conta(PRINCIPAL *principal,char *dir,int conta)
{
	ARQUIVOS *arquivos = open_account_files(dir,conta);
	int opcao=0,nova_opcao=0,tecla=0,loop=1;
	char *roll[8],cursor[]="-->",vazio[]="   ";
	roll[0]=cursor;
	roll[1]=roll[2]=roll[3]=roll[4]=roll[5]=roll[6]=roll[7]=vazio;

	do {
		while(tecla!=KeyEnter)
		{
			if(opcao-nova_opcao)
			{
				roll[opcao]=vazio;
				roll[nova_opcao]=cursor;
				opcao=nova_opcao;
			}
			printf("\n[Opção] - Pasta (Nº de E-mails) "); breakline;
			printf("%s |%21s (%d)",roll[0],"Caixa de Entrada",number_of_emails(arquivos->inbox_tree_messages)); breakline;
			printf("%s |%21s (%d)",roll[1],"Caixa de Saída",number_of_emails(arquivos->outbox_tree_messages)); breakline;
			printf("%s |%21s (%d)",roll[2],"Lidos",number_of_emails(arquivos->read_tree_messages)); breakline;
			printf("%s |%21s (%d)",roll[3],"Enviados",number_of_emails(arquivos->sent_tree_messages)); breakline;
			printf("%s |%21s (%d)",roll[4],"Lixeira",number_of_emails(arquivos->trash_tree_messages)); breakline;

			printf("%s |%25s",roll[5],"Escrever novo e-mail"); breakline;
			printf("%s |%25s",roll[6],"Pesquisar por e-mail"); breakline;
			printf("%s |-%25s",roll[7],"Sair da conta"); breakline;

			tecla = getch();
			while (tecla != KeySpecial2 && tecla != KeyEnter)
				tecla = getch();
			if (tecla == KeySpecial2)
			{
				tecla = getch();
				if (tecla == KeyUp)
				{
					if (opcao)
						nova_opcao--;
				}
				else if (tecla == KeyDown)
				{
					if (opcao < 7)
						nova_opcao++;
				}
			}
			cls;
		}
		tecla=0;
		// Essas são as funções que faltam ser definidas
		switch (opcao)
		{
			case 0: // Caixa de Entrada
				access_inbox(principal,arquivos);
			break;
			case 1: // Caixa de Saída
				access_outbox(principal,arquivos);
			break;
			case 2: // Lidos
				access_read(principal,arquivos);
			break;
			case 3: // Enviados
				access_sent(principal,arquivos);
			break;
			case 4: // Lixeira
				access_trash(principal,arquivos);
			break;
			case 5: // Enviar Email
				send_email(principal,arquivos,NULL);
			break;
			case 6: // Pesquisar Email
				search_email(arquivos);
			break;
			case 7: // Sair da Conta
				loop=0;
				close_account_files(arquivos);
				printf("O logoff foi efetuado com sucesso."); breakline;
			break;
			default:
				return;
		}
	} while (loop);

	return;
}

void print_email_header(ARQUIVOS *arquivos,int email_pos)
{
	SUB_NODO email; 				//	Manipulação de email
	subjects assunto;
	HORARIO data;
	CONTA remetente, destinatario;

	fseek(arquivos->email_list,sizeof(SUB_NODO)*email_pos,SEEK_SET);
	fread(&email,sizeof(SUB_NODO),1,arquivos->email_list);

	fseek(arquivos->subject_list,sizeof(subjects)*email.assunto,SEEK_SET);
	fread(&assunto,sizeof(subjects),1,arquivos->subject_list);

	fseek(arquivos->horario_list,sizeof(HORARIO)*email.data,SEEK_SET);
	fread(&data,sizeof(HORARIO),1,arquivos->horario_list);

	fseek(arquivos->addresses,sizeof(CONTA)*email.remetente,SEEK_SET);
	fread(&remetente,sizeof(CONTA),1,arquivos->addresses);
	fseek(arquivos->addresses,sizeof(CONTA)*email.destinatario,SEEK_SET);
	fread(&destinatario,sizeof(CONTA),1,arquivos->addresses);

	printf("De: %s",remetente.user); breakline;
	printf("Para: %s",destinatario.user); breakline;
	printf("%s   ",assunto.subject);
	print_horario(data); breakline;
}

char * print_email_header_to_string(ARQUIVOS *arquivos,int email_pos)
{
	char *email_header=calloc(size_subject+(size_address*2)+size_horario+10*4,sizeof(char)),*hor;
	SUB_NODO email; 				//	Manipulação de email
	subjects assunto;
	HORARIO data;
	CONTA remetente, destinatario;

	fseek(arquivos->email_list,sizeof(SUB_NODO)*email_pos,SEEK_SET);
	fread(&email,sizeof(SUB_NODO),1,arquivos->email_list);

	fseek(arquivos->subject_list,sizeof(subjects)*email.assunto,SEEK_SET);
	fread(&assunto,sizeof(subjects),1,arquivos->subject_list);

	fseek(arquivos->horario_list,sizeof(HORARIO)*email.data,SEEK_SET);
	fread(&data,sizeof(HORARIO),1,arquivos->horario_list);

	fseek(arquivos->addresses,sizeof(CONTA)*email.remetente,SEEK_SET);
	fread(&remetente,sizeof(CONTA),1,arquivos->addresses);
	fseek(arquivos->addresses,sizeof(CONTA)*email.destinatario,SEEK_SET);
	fread(&destinatario,sizeof(CONTA),1,arquivos->addresses);

	sprintf(email_header,"%s","|De: ");
	strcat(email_header,remetente.user);
	strcat(email_header,"\n    |Para: ");
	strcat(email_header,destinatario.user);
	strcat(email_header,"\n    | ");
	strcat(email_header,assunto.subject);
	strcat(email_header,"\n    | ");
	hor=print_horario_to_string(data);
	strcat(email_header,hor);

	free(hor);

	return email_header;
}

void print_email(ARQUIVOS *arquivos,int email_pos)
{
	SUB_NODO email; 				//	Manipula��o de email
	messages mensagem;
	subjects assunto;
	HORARIO data;
	CONTA remetente, destinatario;

	fseek(arquivos->email_list,sizeof(SUB_NODO)*email_pos,SEEK_SET);
	fread(&email,sizeof(SUB_NODO),1,arquivos->email_list);

	fseek(arquivos->text_list,sizeof(messages)*email.MSG,SEEK_SET);
	fread(&mensagem,sizeof(messages),1,arquivos->text_list);

	fseek(arquivos->subject_list,sizeof(subjects)*email.assunto,SEEK_SET);
	fread(&assunto,sizeof(subjects),1,arquivos->subject_list);

	fseek(arquivos->horario_list,sizeof(HORARIO)*email.data,SEEK_SET);
	fread(&data,sizeof(HORARIO),1,arquivos->horario_list);

	fseek(arquivos->addresses,sizeof(CONTA)*email.remetente,SEEK_SET);
	fread(&remetente,sizeof(CONTA),1,arquivos->addresses);
	fseek(arquivos->addresses,sizeof(CONTA)*email.destinatario,SEEK_SET);
	fread(&destinatario,sizeof(CONTA),1,arquivos->addresses);

	breakline;
	print_horario(data);
	breakline;
	printf("Remetente: %s\n",remetente.user);
	printf("Destinat�rio: %s\n",destinatario.user);
	printf("Assunto: %s\n",assunto.subject);
	printf("%s\n",mensagem.mail);

	//	Implementar impress�o do hist�rico (recurs�o?)
	// 	Melhorar formata��o da impress�o
}

void print_horario(HORARIO data)
{
	printf("%02d/%02d/%04d %02d:%02d:%02d",
			data.data[2],data.data[1],data.data[0],
			data.data[3],data.data[4],data.data[5]);
}

char * print_horario_to_string(HORARIO data)
{
	char *horario=(char *)calloc(size_horario+2,sizeof(char));
	sprintf(horario,"%02d/%02d/%04d %02d:%02d:%02d",
			data.data[2],data.data[1],data.data[0],
			data.data[3],data.data[4],data.data[5]);
	return horario;
}

void access_inbox(PRINCIPAL *principal,ARQUIVOS *arquivos)
{
	RESULTADO resultado = create_result_list();
	ARVOREB avb;
	int opcao=0,nova_opcao=0,tecla=0,loop=1,multiplicador=0,aux;
	char *roll[11],cursor[]="-->",vazio[]="   ",*title=(char *) malloc(sizeof(char)*40);
	roll[0]=cursor;
	roll[1]=roll[2]=roll[3]=roll[4]=roll[5]=roll[6]=roll[7]=roll[8]=roll[9]=roll[10]=vazio;

	rewind(arquivos->inbox_tree_HORARIO);
	fread(&avb,sizeof(ARVOREB),1,arquivos->inbox_tree_HORARIO);

	if (avb.num_NODOS)
		list_email_decreasing(&resultado,arquivos,arquivos->inbox_tree_L_HORARIO,avb.raiz);

	sprintf(title,"%s %s%d%s","CAIXA DE EMAILS ENVIADOS","  (",avb.num_NODOS?resultado.num_resultados:0," Emails)");
	do
	{
		while(tecla!=KeyEnter)
		{
			if(opcao-nova_opcao)
			{
				roll[opcao]=vazio;
				roll[nova_opcao]=cursor;
				opcao=nova_opcao;
			}
			formated_message(title);
			printf("Selecione o que deseja fazer e aperte ENTER:"); breakline;
			printf("%s |-Sair da pasta",roll[0]); breakline;
			if (avb.num_NODOS)
			{
				printf("%s %s",roll[1],(*(resultado.index+(multiplicador*10)))->text); breakline;
				if (1+(multiplicador*10)<resultado.num_resultados) {
					printf("%s %s",roll[2],(*(resultado.index+1+(multiplicador*10)))->text); breakline;
					if (2+(multiplicador*10)<resultado.num_resultados)
					{
						printf("%s %s",roll[3],(*(resultado.index+2+(multiplicador*10)))->text); breakline;
						if (3+(multiplicador*10)<resultado.num_resultados)
						{
							printf("%s %s",roll[4],(*(resultado.index+3+(multiplicador*10)))->text); breakline;
							if (4+(multiplicador*10)<resultado.num_resultados)
							{
								printf("%s %s",roll[5],(*(resultado.index+4+(multiplicador*10)))->text); breakline;
								if (5+(multiplicador*10)<resultado.num_resultados)
								{
									printf("%s %s",roll[6],(*(resultado.index+5+(multiplicador*10)))->text); breakline;
									if (6+(multiplicador*10)<resultado.num_resultados)
									{
										printf("%s %s",roll[7],(*(resultado.index+6+(multiplicador*10)))->text); breakline;
										if (7+(multiplicador*10)<resultado.num_resultados)
										{
											printf("%s %s",roll[8],(*(resultado.index+7+(multiplicador*10)))->text); breakline;
											if (8+(multiplicador*10)<resultado.num_resultados)
											{
												printf("%s %s",roll[9],(*(resultado.index+8+(multiplicador*10)))->text); breakline;
												if (9+(multiplicador*10)<resultado.num_resultados)
													printf("%s %s",roll[10],(*(resultado.index+9+(multiplicador*10)))->text); breakline;
											}
										}
									}
								}
							}
						}
					}
				}
				breakline;
			}
			else
				printf("Pasta vazia. Não existem e-mails para serem exibidos.");
			kbhit();
			tecla = getch();
			while (tecla != KeySpecial2 && tecla != KeyEnter)
				tecla = getch();
			if (tecla == KeySpecial2)
			{
				tecla = getch();
				aux = resultado.num_resultados-((multiplicador)*10);
				if (tecla == KeyUp)
				{
					if (opcao)
						nova_opcao--;
					else
						nova_opcao=((aux>9)?10:aux);
				}
				else if (tecla == KeyDown)
				{
					if (opcao < ((aux>9)?10:aux))
						nova_opcao++;
					else
						nova_opcao=0;
				}
				else if (tecla == KeyLeft)
				{
					if (multiplicador)
						multiplicador--;
				}
				else if (tecla == KeyRight)
				{
					if (resultado.num_resultados/((multiplicador+1)*10) > 1)
						multiplicador++;
				}
			}
			cls;
		}
		tecla=0;

		switch(opcao)
		{
			case 0:	//	Sair da pasta
				loop=0;
			break;
			case 1:	//	Selecionar o email na posição 1
				exibir_email(principal,arquivos,"inbox",(*(resultado.index+(multiplicador*10)))->pos_email);
			break;
			case 2:	//	Selecionar o email na posição 2
				exibir_email(principal,arquivos,"inbox",(*(resultado.index+1+(multiplicador*10)))->pos_email);
			break;
			case 3:	//	Selecionar o email na posição 3
				exibir_email(principal,arquivos,"inbox",(*(resultado.index+2+(multiplicador*10)))->pos_email);
			break;
			case 4:	//	Selecionar o email na posição 4
				exibir_email(principal,arquivos,"inbox",(*(resultado.index+3+(multiplicador*10)))->pos_email);
			break;
			case 5:	//	Selecionar o email na posição 5
				exibir_email(principal,arquivos,"inbox",(*(resultado.index+4+(multiplicador*10)))->pos_email);
			break;
			case 6:	//	Selecionar o email na posição 6
				exibir_email(principal,arquivos,"inbox",(*(resultado.index+5+(multiplicador*10)))->pos_email);
			break;
			case 7:	//	Selecionar o email na posição 7
				exibir_email(principal,arquivos,"inbox",(*(resultado.index+6+(multiplicador*10)))->pos_email);
			break;
			case 8:	//	Selecionar o email na posição 8
				exibir_email(principal,arquivos,"inbox",(*(resultado.index+7+(multiplicador*10)))->pos_email);
			break;
			case 9:	//	Selecionar o email na posição 9
				exibir_email(principal,arquivos,"inbox",(*(resultado.index+8+(multiplicador*10)))->pos_email);
			break;
			case 10://	Selecionar o email na posição 10
				exibir_email(principal,arquivos,"inbox",(*(resultado.index+9+(multiplicador*10)))->pos_email);
			break;
			default:
			break;
		}
	}while(loop);

	return;
}

void access_outbox(PRINCIPAL *principal,ARQUIVOS *arquivos)
{
	RESULTADO resultado = create_result_list();
	ARVOREB avb;
	int opcao=0,nova_opcao=0,tecla=0,loop=1,multiplicador=0,aux;
	char *roll[11],cursor[]="-->",vazio[]="   ",*title=(char *) malloc(sizeof(char)*40);
	roll[0]=cursor;
	roll[1]=roll[2]=roll[3]=roll[4]=roll[5]=roll[6]=roll[7]=roll[8]=roll[9]=roll[10]=vazio;

	rewind(arquivos->outbox_tree_HORARIO);
	fread(&avb,sizeof(ARVOREB),1,arquivos->outbox_tree_HORARIO);

	if (avb.num_NODOS)
		list_email_decreasing(&resultado,arquivos,arquivos->outbox_tree_L_HORARIO,avb.raiz);

	sprintf(title,"%s %s%d%s","CAIXA DE EMAILS ENVIADOS","  (",avb.num_NODOS?resultado.num_resultados:0," Emails)");
	do
	{
		while(tecla!=KeyEnter)
		{
			if(opcao-nova_opcao)
			{
				roll[opcao]=vazio;
				roll[nova_opcao]=cursor;
				opcao=nova_opcao;
			}
			formated_message(title);
			printf("Selecione o que deseja fazer e aperte ENTER:"); breakline;
			printf("%s |-Sair da pasta",roll[0]); breakline;
			if (avb.num_NODOS)
			{
				printf("%s %s",roll[1],(*(resultado.index+(multiplicador*10)))->text); breakline;
				if (1+(multiplicador*10)<resultado.num_resultados) {
					printf("%s %s",roll[2],(*(resultado.index+1+(multiplicador*10)))->text); breakline;
					if (2+(multiplicador*10)<resultado.num_resultados)
					{
						printf("%s %s",roll[3],(*(resultado.index+2+(multiplicador*10)))->text); breakline;
						if (3+(multiplicador*10)<resultado.num_resultados)
						{
							printf("%s %s",roll[4],(*(resultado.index+3+(multiplicador*10)))->text); breakline;
							if (4+(multiplicador*10)<resultado.num_resultados)
							{
								printf("%s %s",roll[5],(*(resultado.index+4+(multiplicador*10)))->text); breakline;
								if (5+(multiplicador*10)<resultado.num_resultados)
								{
									printf("%s %s",roll[6],(*(resultado.index+5+(multiplicador*10)))->text); breakline;
									if (6+(multiplicador*10)<resultado.num_resultados)
									{
										printf("%s %s",roll[7],(*(resultado.index+6+(multiplicador*10)))->text); breakline;
										if (7+(multiplicador*10)<resultado.num_resultados)
										{
											printf("%s %s",roll[8],(*(resultado.index+7+(multiplicador*10)))->text); breakline;
											if (8+(multiplicador*10)<resultado.num_resultados)
											{
												printf("%s %s",roll[9],(*(resultado.index+8+(multiplicador*10)))->text); breakline;
												if (9+(multiplicador*10)<resultado.num_resultados)
													printf("%s %s",roll[10],(*(resultado.index+9+(multiplicador*10)))->text); breakline;
											}
										}
									}
								}
							}
						}
					}
				}
				breakline;
			}
			else
				printf("Pasta vazia. Não existem e-mails para serem exibidos.");
			kbhit();
			tecla = getch();
			while (tecla != KeySpecial2 && tecla != KeyEnter)
				tecla = getch();
			if (tecla == KeySpecial2)
			{
				tecla = getch();
				aux = resultado.num_resultados-((multiplicador)*10);
				if (tecla == KeyUp)
				{
					if (opcao)
						nova_opcao--;
					else
						nova_opcao=((aux>9)?10:aux);
				}
				else if (tecla == KeyDown)
				{
					if (opcao < ((aux>9)?10:aux))
						nova_opcao++;
					else
						nova_opcao=0;
				}
				else if (tecla == KeyLeft)
				{
					if (multiplicador)
						multiplicador--;
				}
				else if (tecla == KeyRight)
				{
					if (resultado.num_resultados/((multiplicador+1)*10.0) > 1)
						multiplicador++;
					pause;
				}
			}
			cls;
		}
		tecla=0;

		switch(opcao)
		{
			case 0:	//	Sair da pasta
				loop=0;
			break;
			case 1:	//	Selecionar o email na posição 1
				exibir_email(principal,arquivos,"outbox",(*(resultado.index+(multiplicador*10)))->pos_email);
			break;
			case 2:	//	Selecionar o email na posição 2
				exibir_email(principal,arquivos,"outbox",(*(resultado.index+1+(multiplicador*10)))->pos_email);
			break;
			case 3:	//	Selecionar o email na posição 3
				exibir_email(principal,arquivos,"outbox",(*(resultado.index+2+(multiplicador*10)))->pos_email);
			break;
			case 4:	//	Selecionar o email na posição 4
				exibir_email(principal,arquivos,"outbox",(*(resultado.index+3+(multiplicador*10)))->pos_email);
			break;
			case 5:	//	Selecionar o email na posição 5
				exibir_email(principal,arquivos,"outbox",(*(resultado.index+4+(multiplicador*10)))->pos_email);
			break;
			case 6:	//	Selecionar o email na posição 6
				exibir_email(principal,arquivos,"outbox",(*(resultado.index+5+(multiplicador*10)))->pos_email);
			break;
			case 7:	//	Selecionar o email na posição 7
				exibir_email(principal,arquivos,"outbox",(*(resultado.index+6+(multiplicador*10)))->pos_email);
			break;
			case 8:	//	Selecionar o email na posição 8
				exibir_email(principal,arquivos,"outbox",(*(resultado.index+7+(multiplicador*10)))->pos_email);
			break;
			case 9:	//	Selecionar o email na posição 9
				exibir_email(principal,arquivos,"outbox",(*(resultado.index+8+(multiplicador*10)))->pos_email);
			break;
			case 10://	Selecionar o email na posição 10
				exibir_email(principal,arquivos,"outbox",(*(resultado.index+9+(multiplicador*10)))->pos_email);
			break;
			default:
			break;
		}
	}while(loop);

	return;
}

void access_read(PRINCIPAL *principal,ARQUIVOS *arquivos)
{
	RESULTADO resultado = create_result_list();
	ARVOREB avb;
	int opcao=0,nova_opcao=0,tecla=0,loop=1,multiplicador=0,aux;
	char *roll[11],cursor[]="-->",vazio[]="   ",*title=(char *) malloc(sizeof(char)*40);
	roll[0]=cursor;
	roll[1]=roll[2]=roll[3]=roll[4]=roll[5]=roll[6]=roll[7]=roll[8]=roll[9]=roll[10]=vazio;

	rewind(arquivos->read_tree_HORARIO);
	fread(&avb,sizeof(ARVOREB),1,arquivos->read_tree_HORARIO);

	if (avb.num_NODOS)
		list_email_decreasing(&resultado,arquivos,arquivos->read_tree_L_HORARIO,avb.raiz);

	sprintf(title,"%s %s%d%s","CAIXA DE EMAILS ENVIADOS","  (",avb.num_NODOS?resultado.num_resultados:0," Emails)");
	do
	{
		while(tecla!=KeyEnter)
		{
			if(opcao-nova_opcao)
			{
				roll[opcao]=vazio;
				roll[nova_opcao]=cursor;
				opcao=nova_opcao;
			}
			formated_message(title);
			printf("Selecione o que deseja fazer e aperte ENTER:"); breakline;
			printf("%s |-Sair da pasta",roll[0]); breakline;
			if (avb.num_NODOS)
			{
				printf("%s %s",roll[1],(*(resultado.index+(multiplicador*10)))->text); breakline;
				if (1+(multiplicador*10)<resultado.num_resultados) {
					printf("%s %s",roll[2],(*(resultado.index+1+(multiplicador*10)))->text); breakline;
					if (2+(multiplicador*10)<resultado.num_resultados)
					{
						printf("%s %s",roll[3],(*(resultado.index+2+(multiplicador*10)))->text); breakline;
						if (3+(multiplicador*10)<resultado.num_resultados)
						{
							printf("%s %s",roll[4],(*(resultado.index+3+(multiplicador*10)))->text); breakline;
							if (4+(multiplicador*10)<resultado.num_resultados)
							{
								printf("%s %s",roll[5],(*(resultado.index+4+(multiplicador*10)))->text); breakline;
								if (5+(multiplicador*10)<resultado.num_resultados)
								{
									printf("%s %s",roll[6],(*(resultado.index+5+(multiplicador*10)))->text); breakline;
									if (6+(multiplicador*10)<resultado.num_resultados)
									{
										printf("%s %s",roll[7],(*(resultado.index+6+(multiplicador*10)))->text); breakline;
										if (7+(multiplicador*10)<resultado.num_resultados)
										{
											printf("%s %s",roll[8],(*(resultado.index+7+(multiplicador*10)))->text); breakline;
											if (8+(multiplicador*10)<resultado.num_resultados)
											{
												printf("%s %s",roll[9],(*(resultado.index+8+(multiplicador*10)))->text); breakline;
												if (9+(multiplicador*10)<resultado.num_resultados)
													printf("%s %s",roll[10],(*(resultado.index+9+(multiplicador*10)))->text); breakline;
											}
										}
									}
								}
							}
						}
					}
				}
				breakline;
			}
			else
				printf("Pasta vazia. Não existem e-mails para serem exibidos.");
			kbhit();
			tecla = getch();
			while (tecla != KeySpecial2 && tecla != KeyEnter)
				tecla = getch();
			if (tecla == KeySpecial2)
			{
				tecla = getch();
				aux = resultado.num_resultados-((multiplicador)*10);
				if (tecla == KeyUp)
				{
					if (opcao)
						nova_opcao--;
					else
						nova_opcao=((aux>9)?10:aux);
				}
				else if (tecla == KeyDown)
				{
					if (opcao < ((aux>9)?10:aux))
						nova_opcao++;
					else
						nova_opcao=0;
				}
				else if (tecla == KeyLeft)
				{
					if (multiplicador)
						multiplicador--;
				}
				else if (tecla == KeyRight)
				{
					if (resultado.num_resultados/((multiplicador+1)*10.0) > 1)
						multiplicador++;
					pause;
				}
			}
			cls;
		}
		tecla=0;

		switch(opcao)
		{
			case 0:	//	Sair da pasta
				loop=0;
			break;
			case 1:	//	Selecionar o email na posição 1
				exibir_email(principal,arquivos,"read",(*(resultado.index+(multiplicador*10)))->pos_email);
			break;
			case 2:	//	Selecionar o email na posição 2
				exibir_email(principal,arquivos,"read",(*(resultado.index+1+(multiplicador*10)))->pos_email);
			break;
			case 3:	//	Selecionar o email na posição 3
				exibir_email(principal,arquivos,"read",(*(resultado.index+2+(multiplicador*10)))->pos_email);
			break;
			case 4:	//	Selecionar o email na posição 4
				exibir_email(principal,arquivos,"read",(*(resultado.index+3+(multiplicador*10)))->pos_email);
			break;
			case 5:	//	Selecionar o email na posição 5
				exibir_email(principal,arquivos,"read",(*(resultado.index+4+(multiplicador*10)))->pos_email);
			break;
			case 6:	//	Selecionar o email na posição 6
				exibir_email(principal,arquivos,"read",(*(resultado.index+5+(multiplicador*10)))->pos_email);
			break;
			case 7:	//	Selecionar o email na posição 7
				exibir_email(principal,arquivos,"read",(*(resultado.index+6+(multiplicador*10)))->pos_email);
			break;
			case 8:	//	Selecionar o email na posição 8
				exibir_email(principal,arquivos,"read",(*(resultado.index+7+(multiplicador*10)))->pos_email);
			break;
			case 9:	//	Selecionar o email na posição 9
				exibir_email(principal,arquivos,"read",(*(resultado.index+8+(multiplicador*10)))->pos_email);
			break;
			case 10://	Selecionar o email na posição 10
				exibir_email(principal,arquivos,"read",(*(resultado.index+9+(multiplicador*10)))->pos_email);
			break;
			default:
			break;
		}
	}while(loop);

	return;
}

void access_sent(PRINCIPAL *principal,ARQUIVOS *arquivos)
{
	RESULTADO resultado = create_result_list();
	ARVOREB avb;
	int opcao=0,nova_opcao=0,tecla=0,loop=1,multiplicador=0,aux;
	char *roll[11],cursor[]="-->",vazio[]="   ",*title=(char *) malloc(sizeof(char)*40);
	roll[0]=cursor;
	roll[1]=roll[2]=roll[3]=roll[4]=roll[5]=roll[6]=roll[7]=roll[8]=roll[9]=roll[10]=vazio;

	rewind(arquivos->sent_tree_HORARIO);
	fread(&avb,sizeof(ARVOREB),1,arquivos->sent_tree_HORARIO);

	if (avb.num_NODOS)
		list_email_decreasing(&resultado,arquivos,arquivos->sent_tree_L_HORARIO,avb.raiz);


	sprintf(title,"%s %s%d%s","CAIXA DE EMAILS ENVIADOS","  (",avb.num_NODOS?resultado.num_resultados:0," Emails)");
	do
	{
		while(tecla!=KeyEnter)
		{
			if(opcao-nova_opcao)
			{
				roll[opcao]=vazio;
				roll[nova_opcao]=cursor;
				opcao=nova_opcao;
			}
			formated_message(title);
			printf("Selecione o que deseja fazer e aperte ENTER:"); breakline;
			printf("%s |-Sair da pasta",roll[0]); breakline;
			if (avb.num_NODOS)
			{
				printf("%s %s",roll[1],(*(resultado.index+(multiplicador*10)))->text); breakline;
				if (1+(multiplicador*10)<resultado.num_resultados) {
					printf("%s %s",roll[2],(*(resultado.index+1+(multiplicador*10)))->text); breakline;
					if (2+(multiplicador*10)<resultado.num_resultados)
					{
						printf("%s %s",roll[3],(*(resultado.index+2+(multiplicador*10)))->text); breakline;
						if (3+(multiplicador*10)<resultado.num_resultados)
						{
							printf("%s %s",roll[4],(*(resultado.index+3+(multiplicador*10)))->text); breakline;
							if (4+(multiplicador*10)<resultado.num_resultados)
							{
								printf("%s %s",roll[5],(*(resultado.index+4+(multiplicador*10)))->text); breakline;
								if (5+(multiplicador*10)<resultado.num_resultados)
								{
									printf("%s %s",roll[6],(*(resultado.index+5+(multiplicador*10)))->text); breakline;
									if (6+(multiplicador*10)<resultado.num_resultados)
									{
										printf("%s %s",roll[7],(*(resultado.index+6+(multiplicador*10)))->text); breakline;
										if (7+(multiplicador*10)<resultado.num_resultados)
										{
											printf("%s %s",roll[8],(*(resultado.index+7+(multiplicador*10)))->text); breakline;
											if (8+(multiplicador*10)<resultado.num_resultados)
											{
												printf("%s %s",roll[9],(*(resultado.index+8+(multiplicador*10)))->text); breakline;
												if (9+(multiplicador*10)<resultado.num_resultados)
													printf("%s %s",roll[10],(*(resultado.index+9+(multiplicador*10)))->text); breakline;
											}
										}
									}
								}
							}
						}
					}
				}
				breakline;
			}
			else
				printf("Pasta vazia. Não existem e-mails para serem exibidos.");
			kbhit();
			tecla = getch();
			while (tecla != KeySpecial2 && tecla != KeyEnter)
				tecla = getch();
			if (tecla == KeySpecial2)
			{
				tecla = getch();
				aux = resultado.num_resultados-((multiplicador)*10);
				if (tecla == KeyUp)
				{
					if (opcao)
						nova_opcao--;
					else
						nova_opcao=((aux>9)?10:aux);
				}
				else if (tecla == KeyDown)
				{
					if (opcao < ((aux>9)?10:aux))
						nova_opcao++;
					else
						nova_opcao=0;
				}
				else if (tecla == KeyLeft)
				{
					if (multiplicador)
						multiplicador--;
				}
				else if (tecla == KeyRight)
				{
					if (resultado.num_resultados/((multiplicador+1)*10.0) > 1)
						multiplicador++;
					pause;
				}
			}
			cls;
		}
		tecla=0;

		switch(opcao)
		{
			case 0:	//	Sair da pasta
				loop=0;
			break;
			case 1:	//	Selecionar o email na posição 1
				exibir_email(principal,arquivos,"sent",(*(resultado.index+(multiplicador*10)))->pos_email);
			break;
			case 2:	//	Selecionar o email na posição 2
				exibir_email(principal,arquivos,"sent",(*(resultado.index+1+(multiplicador*10)))->pos_email);
			break;
			case 3:	//	Selecionar o email na posição 3
				exibir_email(principal,arquivos,"sent",(*(resultado.index+2+(multiplicador*10)))->pos_email);
			break;
			case 4:	//	Selecionar o email na posição 4
				exibir_email(principal,arquivos,"sent",(*(resultado.index+3+(multiplicador*10)))->pos_email);
			break;
			case 5:	//	Selecionar o email na posição 5
				exibir_email(principal,arquivos,"sent",(*(resultado.index+4+(multiplicador*10)))->pos_email);
			break;
			case 6:	//	Selecionar o email na posição 6
				exibir_email(principal,arquivos,"sent",(*(resultado.index+5+(multiplicador*10)))->pos_email);
			break;
			case 7:	//	Selecionar o email na posição 7
				exibir_email(principal,arquivos,"sent",(*(resultado.index+6+(multiplicador*10)))->pos_email);
			break;
			case 8:	//	Selecionar o email na posição 8
				exibir_email(principal,arquivos,"sent",(*(resultado.index+7+(multiplicador*10)))->pos_email);
			break;
			case 9:	//	Selecionar o email na posição 9
				exibir_email(principal,arquivos,"sent",(*(resultado.index+8+(multiplicador*10)))->pos_email);
			break;
			case 10://	Selecionar o email na posição 10
				exibir_email(principal,arquivos,"sent",(*(resultado.index+9+(multiplicador*10)))->pos_email);
			break;
			default:
			break;
		}
	}while(loop);

	return;
}

void access_trash(PRINCIPAL *principal,ARQUIVOS *arquivos)
{
	RESULTADO resultado = create_result_list();
	ARVOREB avb;
	int opcao=0,nova_opcao=0,tecla=0,loop=1,multiplicador=0,aux;
	char *roll[11],cursor[]="-->",vazio[]="   ",*title=(char *) malloc(sizeof(char)*40);
	roll[0]=cursor;
	roll[1]=roll[2]=roll[3]=roll[4]=roll[5]=roll[6]=roll[7]=roll[8]=roll[9]=roll[10]=vazio;

	rewind(arquivos->trash_tree_HORARIO);
	fread(&avb,sizeof(ARVOREB),1,arquivos->trash_tree_HORARIO);

	if (avb.num_NODOS)
		list_email_decreasing(&resultado,arquivos,arquivos->trash_tree_L_HORARIO,avb.raiz);

	sprintf(title,"%s %s%d%s","CAIXA DE EMAILS ENVIADOS","  (",avb.num_NODOS?resultado.num_resultados:0," Emails)");
	do
	{
		while(tecla!=KeyEnter)
		{
			if(opcao-nova_opcao)
			{
				roll[opcao]=vazio;
				roll[nova_opcao]=cursor;
				opcao=nova_opcao;
			}
			formated_message(title);
			printf("Selecione o que deseja fazer e aperte ENTER:"); breakline;
			printf("%s |-Sair da pasta",roll[0]); breakline;
			if (avb.num_NODOS)
			{
				printf("%s %s",roll[1],(*(resultado.index+(multiplicador*10)))->text); breakline;
				if (1+(multiplicador*10)<resultado.num_resultados) {
					printf("%s %s",roll[2],(*(resultado.index+1+(multiplicador*10)))->text); breakline;
					if (2+(multiplicador*10)<resultado.num_resultados)
					{
						printf("%s %s",roll[3],(*(resultado.index+2+(multiplicador*10)))->text); breakline;
						if (3+(multiplicador*10)<resultado.num_resultados)
						{
							printf("%s %s",roll[4],(*(resultado.index+3+(multiplicador*10)))->text); breakline;
							if (4+(multiplicador*10)<resultado.num_resultados)
							{
								printf("%s %s",roll[5],(*(resultado.index+4+(multiplicador*10)))->text); breakline;
								if (5+(multiplicador*10)<resultado.num_resultados)
								{
									printf("%s %s",roll[6],(*(resultado.index+5+(multiplicador*10)))->text); breakline;
									if (6+(multiplicador*10)<resultado.num_resultados)
									{
										printf("%s %s",roll[7],(*(resultado.index+6+(multiplicador*10)))->text); breakline;
										if (7+(multiplicador*10)<resultado.num_resultados)
										{
											printf("%s %s",roll[8],(*(resultado.index+7+(multiplicador*10)))->text); breakline;
											if (8+(multiplicador*10)<resultado.num_resultados)
											{
												printf("%s %s",roll[9],(*(resultado.index+8+(multiplicador*10)))->text); breakline;
												if (9+(multiplicador*10)<resultado.num_resultados)
													printf("%s %s",roll[10],(*(resultado.index+9+(multiplicador*10)))->text); breakline;
											}
										}
									}
								}
							}
						}
					}
				}
				breakline;
			}
			else
				printf("Pasta vazia. Não existem e-mails para serem exibidos.");
			kbhit();
			tecla = getch();
			while (tecla != KeySpecial2 && tecla != KeyEnter)
				tecla = getch();
			if (tecla == KeySpecial2)
			{
				tecla = getch();
				aux = resultado.num_resultados-((multiplicador)*10);
				if (tecla == KeyUp)
				{
					if (opcao)
						nova_opcao--;
					else
						nova_opcao=((aux>9)?10:aux);
				}
				else if (tecla == KeyDown)
				{
					if (opcao < ((aux>9)?10:aux))
						nova_opcao++;
					else
						nova_opcao=0;
				}
				else if (tecla == KeyLeft)
				{
					if (multiplicador)
						multiplicador--;
				}
				else if (tecla == KeyRight)
				{
					if (resultado.num_resultados/((multiplicador+1)*10.0) > 1)
						multiplicador++;
					pause;
				}
			}
			cls;
		}
		tecla=0;

		switch(opcao)
		{
			case 0:	//	Sair da pasta
				loop=0;
			break;
			case 1:	//	Selecionar o email na posição 1
				exibir_email(principal,arquivos,"trash",(*(resultado.index+(multiplicador*10)))->pos_email);
			break;
			case 2:	//	Selecionar o email na posição 2
				exibir_email(principal,arquivos,"trash",(*(resultado.index+1+(multiplicador*10)))->pos_email);
			break;
			case 3:	//	Selecionar o email na posição 3
				exibir_email(principal,arquivos,"trash",(*(resultado.index+2+(multiplicador*10)))->pos_email);
			break;
			case 4:	//	Selecionar o email na posição 4
				exibir_email(principal,arquivos,"trash",(*(resultado.index+3+(multiplicador*10)))->pos_email);
			break;
			case 5:	//	Selecionar o email na posição 5
				exibir_email(principal,arquivos,"trash",(*(resultado.index+4+(multiplicador*10)))->pos_email);
			break;
			case 6:	//	Selecionar o email na posição 6
				exibir_email(principal,arquivos,"trash",(*(resultado.index+5+(multiplicador*10)))->pos_email);
			break;
			case 7:	//	Selecionar o email na posição 7
				exibir_email(principal,arquivos,"trash",(*(resultado.index+6+(multiplicador*10)))->pos_email);
			break;
			case 8:	//	Selecionar o email na posição 8
				exibir_email(principal,arquivos,"trash",(*(resultado.index+7+(multiplicador*10)))->pos_email);
			break;
			case 9:	//	Selecionar o email na posição 9
				exibir_email(principal,arquivos,"trash",(*(resultado.index+8+(multiplicador*10)))->pos_email);
			break;
			case 10://	Selecionar o email na posição 10
				exibir_email(principal,arquivos,"trash",(*(resultado.index+9+(multiplicador*10)))->pos_email);
			break;
			default:
			break;
		}
	}while(loop);

	return;
}

void exibir_email(PRINCIPAL *principal,ARQUIVOS *arquivos,char *pasta,int pos_email)
{
	int opcao=0,nova_opcao=0,tecla=0,loop=1;
	char *roll[11],cursor[]="-->",vazio[]="   ";
	roll[0]=cursor;
	roll[1]=roll[2]=roll[3]=roll[4]=vazio;

	// Responder, Mover Email, Excluir
	do
	{
		while(tecla!=KeyEnter)
		{
			print_email(arquivos,pos_email);
			if(opcao-nova_opcao)
			{
				roll[opcao]=vazio;
				roll[nova_opcao]=cursor;
				opcao=nova_opcao;
			}
			printf("Selecione o que deseja fazer e aperte ENTER:"); breakline;
			printf("%s |Voltar para a pasta",roll[0]); breakline;
			printf("%s |Responder",roll[1]); breakline;
			printf("%s |Mover",roll[2]); breakline;
			printf("%s |Excluir",roll[3]); breakline;

			kbhit();
			tecla = getch();
			while (tecla != KeySpecial2 && tecla != KeyEnter)
				tecla = getch();
			if (tecla == KeySpecial2)
			{
				tecla = getch();

				if (tecla == KeyUp)
				{
					if (opcao)
						nova_opcao--;
					else
						nova_opcao=3;
				}
				else if (tecla == KeyDown)
				{
					if (opcao < 3)
						nova_opcao++;
					else
						nova_opcao=0;
				}
			}
			cls;
		}
		tecla=0;


		switch(opcao)
		{
			case 0:	//	Sair da exibição de e-mail
				loop=0;
			break;
			case 1:	//	Responder ao e-mail
				send_email(principal,arquivos,remetente_email(arquivos,pos_email));
				cls;
				printf("E-mail resposta enviado com sucesso!\n");
				pause;
				cls;
				loop = 0;
			break;
			case 2:	//	Mover e-mail para outra pasta
				move_email(arquivos,pos_email,pasta);
			break;
			case 3:	//	Excluir e-mail
				if (!strcmp(pasta,"trash")) //	Excluir e-mail permanentemente
				{
					delete_email(arquivos,pos_email,"trash");
				}
				else
				{
					remove_email_from_tfolder(arquivos,pos_email,pasta);
					add_email_to_tfolder(arquivos,pos_email,"trash");
				}
			break;
			default:
			break;
		}
	}while(loop);
}
char *destinatario_email(ARQUIVOS *arquivos, int pos_email)
{
	SUB_NODO email;
	CONTA destinatario;
	char *dest;
	fseek(arquivos->email_list,sizeof(SUB_NODO)*pos_email,SEEK_SET);
	fread(&email,sizeof(SUB_NODO),1,arquivos->email_list);
	fseek(arquivos->addresses,sizeof(CONTA)*email.destinatario,SEEK_SET);
	fread(&destinatario,sizeof(CONTA),1,arquivos->addresses);

	dest = (char *) malloc(sizeof(char)*strlen(destinatario.user));
	strcpy(dest,destinatario.user);
	return dest;
}
char *remetente_email(ARQUIVOS *arquivos, int pos_email)
{
	SUB_NODO email;
	CONTA remetente;
	char *res;
	fseek(arquivos->email_list,sizeof(SUB_NODO)*pos_email,SEEK_SET);
	fread(&email,sizeof(SUB_NODO),1,arquivos->email_list);
	fseek(arquivos->addresses,sizeof(CONTA)*email.destinatario,SEEK_SET);
	fread(&remetente,sizeof(CONTA),1,arquivos->addresses);

	res = (char *) malloc(sizeof(char)*strlen(remetente.user));
	strcpy(res,remetente.user);
	return res;
}

void search_email(PRINCIPAL *principal,ARQUIVOS *arquivos)
{
	char *palavra;
	printf("Digite uma palavra para efetuar uma busca em todos os e-mails: ");
	palavra = ler('\n');

}

void send_email(PRINCIPAL *principal, ARQUIVOS *arquivos,char *dest)
{
	SUB_NODO email; 				//	Manipulação de email
	HORARIO data;
	configuration con;
	time_t tempo;
	struct tm *tempoc;
	char *mensagem,*assunto,*destinatario,*password=(char *)malloc(sizeof(char));
	int auxad;
	int pos_email;

	printf("Destinatário: ");
	if (!dest)
		destinatario = ler('\n');
	else
	{
		printf("%s\n",dest);
		destinatario = dest;
	}
	printf("Assunto: ");
	assunto = ler('\n');
	mensagem = ler('\n');

	rewind(arquivos->config);
	fread(&con,sizeof(configuration),1,arquivos->config);
	email.remetente = con.account_address;

	auxad = add_address(principal->settings,principal->addresses,destinatario,password);
	email.destinatario = busca_CONTA_tree(principal->addresses,principal->tree_CONTA,principal->tree_L_CONTA,auxad);
	remove_address(principal->settings,principal->addresses,auxad);
	free(password);

	email.assunto = add_subject(arquivos->config,arquivos->subject_list,assunto);

	/*rewind(arquivos->config);
	fread(&con,sizeof(configuration),1,arquivos->config);
	breakline;
	print_configuration(con); breakline;*/

	email.MSG = add_text(arquivos->config,arquivos->text_list,mensagem);


	tempo = time(NULL);
	tempoc = localtime(&tempo);
	data.data[0]=(tempoc->tm_year)+1900;
	data.data[1]=(tempoc->tm_mon)+1;
	data.data[2]=tempoc->tm_mday;
	data.data[3]=tempoc->tm_hour;
	data.data[4]=tempoc->tm_min;
	data.data[5]=tempoc->tm_sec;
	email.data = add_horario(arquivos->config,arquivos->horario_list,data);


	pos_email = add_email(arquivos->config,arquivos->email_list,email.remetente,email.destinatario,email.assunto,email.MSG,email.data,email.historico);

	//add_email_to_tfolder(arquivos,pos_email,"outbox");
	//add_email_to_tfolder(arquivos,pos_email,"");
	add_SUB_NODO_tree(arquivos,arquivos->outbox_tree_HORARIO,arquivos->outbox_tree_L_HORARIO,"horario",email.data,pos_email);
	add_SUB_NODO_tree(arquivos,arquivos->outbox_tree_messages,arquivos->outbox_tree_L_messages,"messages",email.MSG,pos_email);
	add_SUB_NODO_tree(arquivos,arquivos->outbox_tree_subjects,arquivos->outbox_tree_L_subjects,"subjects",email.assunto,pos_email);
	add_SUB_NODO_tree(arquivos,arquivos->tree_HORARIO,arquivos->tree_L_HORARIO,"horario",email.data,pos_email);
	add_SUB_NODO_tree(arquivos,arquivos->tree_messages,arquivos->tree_L_messages,"messages",email.MSG,pos_email);
	add_SUB_NODO_tree(arquivos,arquivos->tree_subjects,arquivos->tree_L_subjects,"subjects",email.assunto,pos_email);

}

void move_email(ARQUIVOS *arquivos,int email_pos,char *from)
{
	char *to=(char *)malloc(sizeof(char)*8);
	int opcao=0,nova_opcao=0,tecla=0,loop=1;
	char *roll[5],cursor[]="-->",vazio[]="   ";
	roll[0]=cursor;
	roll[1]=roll[2]=roll[3]=roll[4]=vazio;

	do {
		while(tecla!=KeyEnter)
		{
			if(opcao-nova_opcao)
			{
				roll[opcao]=vazio;
				roll[nova_opcao]=cursor;
				opcao=nova_opcao;
			}
			printf("\nSelecione para qual pasta tu deseja mover o e-mail:"); breakline;
			printf("%s |-Cancelar ação",roll[1]); breakline;
			printf("%s |Caixa de Entrada",roll[1]); breakline;
			printf("%s |Caixa de Saída",roll[2]); breakline;
			printf("%s |Lidos",roll[3]); breakline;
			printf("%s |Enviados",roll[4]); breakline;
			printf("%s |Lixeira",roll[5]); breakline;

			tecla = getch();
			while (tecla != KeySpecial2 && tecla != KeyEnter)
				tecla = getch();
			if (tecla == KeySpecial2)
			{
				tecla = getch();
				if (tecla == KeyUp)
				{
					if (opcao)
						nova_opcao--;
					else
						nova_opcao=4;
				}
				else if (tecla == KeyDown)
				{
					if (opcao < 4)
						nova_opcao++;
					else
						nova_opcao=0;
				}
			}
			cls;
		}
		tecla=0;
		// Essas são as funções que faltam ser definidas
		switch (opcao)
		{
			case 0: //
				return;
			break;
			case 1: // Caixa de Entrada
				strcpy(to,"inbox");
				loop = 0;
			break;
			case 2: // Caixa de Saída
				strcpy(to,"outbox");
				loop = 0;
			break;
			case 3: // Lidos
				strcpy(to,"read");
				loop = 0;
			break;
			case 4: // Enviados
				strcpy(to,"sent");
				loop = 0;
			break;
			case 5: // Lixeira
				strcpy(to,"trash");
				loop = 0;
			break;
			default:
			break;
		}
	} while (loop);
	remove_email_from_tfolder(arquivos,email_pos,from);
	add_email_to_tfolder(arquivos,email_pos,to);
	return;
}

void delete_email(ARQUIVOS *arquivos,int email_pos,char *folder)
{	//	Deleta por completo um email na pasta
	SUB_NODO email;
	fseek(arquivos->email_list,sizeof(SUB_NODO)*email_pos,SEEK_SET);
	fread(&email,sizeof(SUB_NODO),1,arquivos->email_list);

	remove_email_from_tfolder(arquivos,email_pos,"");
	remove_email_from_tfolder(arquivos,email_pos,"t");

	remove_email(arquivos->config,arquivos->email_list,email_pos);
	remove_subject(arquivos->config,arquivos->subject_list,email.assunto);
	remove_text(arquivos->config,arquivos->text_list,email.MSG);
	remove_horario(arquivos->config,arquivos->horario_list,email.data);

	return;
}

void add_email_to_tfolder(ARQUIVOS *arquivos,int email_pos,char *folder)
{
	SUB_NODO email;
	fseek(arquivos->email_list,sizeof(SUB_NODO)*email_pos,SEEK_SET);
	fread(&email,sizeof(SUB_NODO),1,arquivos->email_list);
	if (!strcmp(folder,""))
	{
		add_SUB_NODO_tree(arquivos,arquivos->tree_HORARIO,arquivos->tree_L_HORARIO,"HORARIO",email.data,email_pos);
		add_SUB_NODO_tree(arquivos,arquivos->tree_subjects,arquivos->tree_L_subjects,"subjects",email.assunto,email_pos);
		add_SUB_NODO_tree(arquivos,arquivos->tree_messages,arquivos->tree_L_messages,"messages",email.MSG,email_pos);
	}
	else if (!strcmp(folder,"inbox"))
	{
		add_SUB_NODO_tree(arquivos,arquivos->inbox_tree_HORARIO,arquivos->inbox_tree_L_HORARIO,"HORARIO",email.data,email_pos);
		add_SUB_NODO_tree(arquivos,arquivos->inbox_tree_subjects,arquivos->inbox_tree_L_subjects,"subjects",email.assunto,email_pos);
		add_SUB_NODO_tree(arquivos,arquivos->inbox_tree_messages,arquivos->inbox_tree_L_messages,"messages",email.MSG,email_pos);
	}
	else if (!strcmp(folder,"outbox"))
	{
		add_SUB_NODO_tree(arquivos,arquivos->outbox_tree_HORARIO,arquivos->outbox_tree_L_HORARIO,"HORARIO",email.data,email_pos);
		add_SUB_NODO_tree(arquivos,arquivos->outbox_tree_subjects,arquivos->outbox_tree_L_subjects,"subjects",email.assunto,email_pos);
		add_SUB_NODO_tree(arquivos,arquivos->outbox_tree_messages,arquivos->outbox_tree_L_messages,"messages",email.MSG,email_pos);
	}
	else if (!strcmp(folder,"read"))
	{
		add_SUB_NODO_tree(arquivos,arquivos->read_tree_HORARIO,arquivos->read_tree_L_HORARIO,"HORARIO",email.data,email_pos);
		add_SUB_NODO_tree(arquivos,arquivos->read_tree_subjects,arquivos->read_tree_L_subjects,"subjects",email.assunto,email_pos);
		add_SUB_NODO_tree(arquivos,arquivos->read_tree_messages,arquivos->read_tree_L_messages,"messages",email.MSG,email_pos);
	}
	else if (!strcmp(folder,"sent"))
	{
		add_SUB_NODO_tree(arquivos,arquivos->sent_tree_HORARIO,arquivos->sent_tree_L_HORARIO,"HORARIO",email.data,email_pos);
		add_SUB_NODO_tree(arquivos,arquivos->sent_tree_subjects,arquivos->sent_tree_L_subjects,"subjects",email.assunto,email_pos);
		add_SUB_NODO_tree(arquivos,arquivos->sent_tree_messages,arquivos->sent_tree_L_messages,"messages",email.MSG,email_pos);
	}
	else if (!strcmp(folder,"trash"))
	{
		add_SUB_NODO_tree(arquivos,arquivos->trash_tree_HORARIO,arquivos->trash_tree_L_HORARIO,"HORARIO",email.data,email_pos);
		add_SUB_NODO_tree(arquivos,arquivos->trash_tree_subjects,arquivos->trash_tree_L_subjects,"subjects",email.assunto,email_pos);
		add_SUB_NODO_tree(arquivos,arquivos->trash_tree_messages,arquivos->trash_tree_L_messages,"messages",email.MSG,email_pos);
	}

	return;
}

void remove_email_from_tfolder(ARQUIVOS *arquivos,int email_pos,char *folder)
{
	SUB_NODO email;
	fseek(arquivos->email_list,sizeof(SUB_NODO)*email_pos,SEEK_SET);
	fread(&email,sizeof(SUB_NODO),1,arquivos->email_list);

	if (!strcmp(folder,""))
	{
		remove_SUB_NODO_tree(arquivos,arquivos->tree_HORARIO,arquivos->tree_L_HORARIO,"HORARIO",email.data,email_pos);
		remove_SUB_NODO_tree(arquivos,arquivos->tree_subjects,arquivos->tree_L_subjects,"subjects",email.assunto,email_pos);
		remove_SUB_NODO_tree(arquivos,arquivos->tree_messages,arquivos->tree_L_messages,"messages",email.MSG,email_pos);
	}
	if (!strcmp(folder,"inbox"))
	{
		remove_SUB_NODO_tree(arquivos,arquivos->inbox_tree_HORARIO,arquivos->inbox_tree_L_HORARIO,"HORARIO",email.data,email_pos);
		remove_SUB_NODO_tree(arquivos,arquivos->inbox_tree_subjects,arquivos->inbox_tree_L_subjects,"subjects",email.assunto,email_pos);
		remove_SUB_NODO_tree(arquivos,arquivos->inbox_tree_messages,arquivos->inbox_tree_L_messages,"messages",email.MSG,email_pos);
	}
	else if (!strcmp(folder,"outbox"))
	{
		remove_SUB_NODO_tree(arquivos,arquivos->outbox_tree_HORARIO,arquivos->outbox_tree_L_HORARIO,"HORARIO",email.data,email_pos);
		remove_SUB_NODO_tree(arquivos,arquivos->outbox_tree_subjects,arquivos->outbox_tree_L_subjects,"subjects",email.assunto,email_pos);
		remove_SUB_NODO_tree(arquivos,arquivos->outbox_tree_messages,arquivos->outbox_tree_L_messages,"messages",email.MSG,email_pos);
	}
	else if (!strcmp(folder,"read"))
	{
		remove_SUB_NODO_tree(arquivos,arquivos->read_tree_HORARIO,arquivos->read_tree_L_HORARIO,"HORARIO",email.data,email_pos);
		remove_SUB_NODO_tree(arquivos,arquivos->read_tree_subjects,arquivos->read_tree_L_subjects,"subjects",email.assunto,email_pos);
		remove_SUB_NODO_tree(arquivos,arquivos->read_tree_messages,arquivos->read_tree_L_messages,"messages",email.MSG,email_pos);
	}
	else if (!strcmp(folder,"sent"))
	{
		remove_SUB_NODO_tree(arquivos,arquivos->sent_tree_HORARIO,arquivos->sent_tree_L_HORARIO,"HORARIO",email.data,email_pos);
		remove_SUB_NODO_tree(arquivos,arquivos->sent_tree_subjects,arquivos->sent_tree_L_subjects,"subjects",email.assunto,email_pos);
		remove_SUB_NODO_tree(arquivos,arquivos->sent_tree_messages,arquivos->sent_tree_L_messages,"messages",email.MSG,email_pos);
	}
	else if (!strcmp(folder,"trash"))
	{
		remove_SUB_NODO_tree(arquivos,arquivos->trash_tree_HORARIO,arquivos->trash_tree_L_HORARIO,"HORARIO",email.data,email_pos);
		remove_SUB_NODO_tree(arquivos,arquivos->trash_tree_subjects,arquivos->trash_tree_L_subjects,"subjects",email.assunto,email_pos);
		remove_SUB_NODO_tree(arquivos,arquivos->trash_tree_messages,arquivos->trash_tree_L_messages,"messages",email.MSG,email_pos);
	}

	return;
}


void list_email_decreasing(RESULTADO *resultado,ARQUIVOS *arquivos,FILE *nodo_list,int pos)
{	//	FUNÇÃO PARA IMPRIMIR LISTA DE EMAILS DE FORMA DECRESCENTE COM ORGANIZA��O A PARTIR DE UMA �RVORE
	NODO nodo;
	LISTA lista_subnodo;
	int c;
	if (pos >= 0)
	{
		fseek(nodo_list,sizeof(NODO)*pos,SEEK_SET);
		fread(&nodo,sizeof(NODO),1,nodo_list);
		if (!nodo.ne_folha)
		{
			printf("num_chaves = %d\n",nodo.num_chaves);
			pause;
			for (c=nodo.num_chaves-1;c+1;c--)
			{
				fseek(arquivos->lista_enc,sizeof(LISTA)*nodo.addresses[c],SEEK_SET);
				fread(&lista_subnodo,sizeof(LISTA),1,arquivos->lista_enc);

				add_result(resultado,lista_subnodo.address,print_email_header_to_string(arquivos,lista_subnodo.address));
				while (lista_subnodo.next != -1)
				{
					fseek(arquivos->lista_enc,sizeof(LISTA)*lista_subnodo.next,SEEK_SET);
					fread(&lista_subnodo,sizeof(LISTA),1,arquivos->lista_enc);
					add_result(resultado,lista_subnodo.address,print_email_header_to_string(arquivos,lista_subnodo.address));
				}
			}
		}
		else	//	Ramificação
		{
			for (c=nodo.num_chaves;c+1;c--)
			{
				list_email_decreasing(resultado,arquivos,nodo_list,nodo.filhos[c]);
				if (c)
				{
					fseek(arquivos->lista_enc,sizeof(LISTA)*nodo.addresses[c-1],SEEK_SET);
					fread(&lista_subnodo,sizeof(LISTA),1,arquivos->lista_enc);
					add_result(resultado,lista_subnodo.address,print_email_header_to_string(arquivos,lista_subnodo.address));
					while (lista_subnodo.next != -1)
					{
						fseek(arquivos->lista_enc,sizeof(LISTA)*lista_subnodo.next,SEEK_SET);
						fread(&lista_subnodo,sizeof(LISTA),1,arquivos->lista_enc);
						add_result(resultado,lista_subnodo.address,print_email_header_to_string(arquivos,lista_subnodo.address));
					}
				}
			}
		}
	}
	return;
}
void list_email_increasing(RESULTADO *resultado,ARQUIVOS *arquivos,FILE *nodo_list,int pos)
{//	FUN��O PARA IMPRIMIR LISTA DE EMAILS DE FORMA CRESCENTE COM ORGANIZA��O A PARTIR DE UMA �RVORE
	NODO nodo;
	LISTA lista_subnodo;
	int c;
	if (pos >= 0)
	{
		fseek(nodo_list,sizeof(NODO)*pos,SEEK_SET);
		fread(&nodo,sizeof(NODO),1,nodo_list);
		if (!nodo.ne_folha)
		{
			for (c=0;c<nodo.num_chaves;c++)
			{
				fseek(arquivos->lista_enc,sizeof(LISTA)*nodo.addresses[c],SEEK_SET);
				fread(&lista_subnodo,sizeof(LISTA),1,arquivos->lista_enc);
				add_result(resultado,lista_subnodo.address,print_email_header_to_string(arquivos,lista_subnodo.address));
				while (lista_subnodo.next != -1)
				{
					fseek(arquivos->lista_enc,sizeof(LISTA)*lista_subnodo.next,SEEK_SET);
					fread(&lista_subnodo,sizeof(LISTA),1,arquivos->lista_enc);
					add_result(resultado,lista_subnodo.next,print_email_header_to_string(arquivos,lista_subnodo.address));
				}
			}
		}
		else//ramificação
		{
			for (c=0;c<=nodo.num_chaves;c++)
			{
				list_email_increasing(resultado,arquivos,nodo_list,nodo.filhos[c]);
				if (c<nodo.num_chaves)
				{
					fseek(arquivos->lista_enc,sizeof(LISTA)*nodo.addresses[c],SEEK_SET);
					fread(&lista_subnodo,sizeof(LISTA),1,arquivos->lista_enc);
					add_result(resultado,lista_subnodo.address,print_email_header_to_string(arquivos,lista_subnodo.address));
					while (lista_subnodo.next != -1)
					{
						fseek(arquivos->lista_enc,sizeof(LISTA)*lista_subnodo.next,SEEK_SET);
						fread(&lista_subnodo,sizeof(LISTA),1,arquivos->lista_enc);
						add_result(resultado,lista_subnodo.next,print_email_header_to_string(arquivos,lista_subnodo.address));
					}
				}
			}
		}
	}
	return;
}

ARQUIVOS *open_account_files(char *dir, int account_address)
{
	ARQUIVOS *arquivos= (ARQUIVOS *) malloc(sizeof(ARQUIVOS));
	char *arquivo;
	//	Arquivos Gerais
	arquivo=filepath_gen(dir,"addresses.bin");
	if (!(arquivos->addresses = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"config.bin");
	if (!(arquivos->config = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"email_list.bin");
	if (!(arquivos->email_list = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"horario_list.bin");
	if (!(arquivos->horario_list = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"subject_list.bin");
	if (!(arquivos->subject_list = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"text_list.bin");
	if (!(arquivos->text_list = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"word_list.bin");
	if (!(arquivos->word_list = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"lista_enc.bin");
	if (!(arquivos->lista_enc = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	//	Árvores Gerais
	arquivo=dir_builder(dir,account_address,"tree_HORARIO.bin");
	if (!(arquivos->tree_HORARIO = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"tree_messages.bin");
	if (!(arquivos->tree_messages = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"tree_PALAVRA.bin");
	if (!(arquivos->tree_PALAVRA = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"tree_subjects.bin");
	if (!(arquivos->tree_subjects = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"tree_L_HORARIO.bin");
	if (!(arquivos->tree_L_HORARIO = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"tree_L_messages.bin");
	if (!(arquivos->tree_L_messages = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"tree_L_PALAVRA.bin");
	if (!(arquivos->tree_L_PALAVRA = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"tree_L_subjects.bin");
	if (!(arquivos->tree_L_subjects = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	//	Caixas de Emails
	//	Árvores de Inbox
	arquivo=dir_builder(dir,account_address,"inbox/tree_HORARIO.bin");
	if (!(arquivos->inbox_tree_HORARIO = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"inbox/tree_messages.bin");
	if (!(arquivos->inbox_tree_messages = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"inbox/tree_PALAVRA.bin");
	if (!(arquivos->inbox_tree_PALAVRA = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"inbox/tree_subjects.bin");
	if (!(arquivos->inbox_tree_subjects = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"inbox/tree_L_HORARIO.bin");
	if (!(arquivos->inbox_tree_L_HORARIO = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"inbox/tree_L_messages.bin");
	if (!(arquivos->inbox_tree_L_messages = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"inbox/tree_L_PALAVRA.bin");
	if (!(arquivos->inbox_tree_L_PALAVRA = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"inbox/tree_L_subjects.bin");
	if (!(arquivos->inbox_tree_L_subjects = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	//	Árvores de Outbox
	arquivo=dir_builder(dir,account_address,"outbox/tree_HORARIO.bin");
	if (!(arquivos->outbox_tree_HORARIO = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"outbox/tree_messages.bin");
	if (!(arquivos->outbox_tree_messages = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"outbox/tree_PALAVRA.bin");
	if (!(arquivos->outbox_tree_PALAVRA = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"outbox/tree_subjects.bin");
	if (!(arquivos->outbox_tree_subjects = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"outbox/tree_L_HORARIO.bin");
	if (!(arquivos->outbox_tree_L_HORARIO = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"outbox/tree_L_messages.bin");
	if (!(arquivos->outbox_tree_L_messages = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"outbox/tree_L_PALAVRA.bin");
	if (!(arquivos->outbox_tree_L_PALAVRA = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"outbox/tree_L_subjects.bin");
	if (!(arquivos->outbox_tree_L_subjects = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	//	�rvores de Read
	arquivo=dir_builder(dir,account_address,"read/tree_HORARIO.bin");
	if (!(arquivos->read_tree_HORARIO = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"read/tree_messages.bin");
	if (!(arquivos->read_tree_messages = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"read/tree_PALAVRA.bin");
	if (!(arquivos->read_tree_PALAVRA = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"read/tree_subjects.bin");
	if (!(arquivos->read_tree_subjects = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"read/tree_L_HORARIO.bin");
	if (!(arquivos->read_tree_L_HORARIO = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"read/tree_L_messages.bin");
	if (!(arquivos->read_tree_L_messages = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"read/tree_L_PALAVRA.bin");
	if (!(arquivos->read_tree_L_PALAVRA = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"read/tree_L_subjects.bin");
	if (!(arquivos->read_tree_L_subjects = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	//	�rvores de Sent
	arquivo=dir_builder(dir,account_address,"sent/tree_HORARIO.bin");
	if (!(arquivos->sent_tree_HORARIO = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"sent/tree_messages.bin");
	if (!(arquivos->sent_tree_messages = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"sent/tree_PALAVRA.bin");
	if (!(arquivos->sent_tree_PALAVRA = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"sent/tree_subjects.bin");
	if (!(arquivos->sent_tree_subjects = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"sent/tree_L_HORARIO.bin");
	if (!(arquivos->sent_tree_L_HORARIO = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"sent/tree_L_messages.bin");
	if (!(arquivos->sent_tree_L_messages = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"sent/tree_L_PALAVRA.bin");
	if (!(arquivos->sent_tree_L_PALAVRA = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"sent/tree_L_subjects.bin");
	if (!(arquivos->sent_tree_L_subjects = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	//	�rvores de Trash
	arquivo=dir_builder(dir,account_address,"trash/tree_HORARIO.bin");
	if (!(arquivos->trash_tree_HORARIO = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"trash/tree_messages.bin");
	if (!(arquivos->trash_tree_messages = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"trash/tree_PALAVRA.bin");
	if (!(arquivos->trash_tree_PALAVRA = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"trash/tree_subjects.bin");
	if (!(arquivos->trash_tree_subjects = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"trash/tree_L_HORARIO.bin");
	if (!(arquivos->trash_tree_L_HORARIO = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"trash/tree_L_messages.bin");
	if (!(arquivos->trash_tree_L_messages = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"trash/tree_L_PALAVRA.bin");
	if (!(arquivos->trash_tree_L_PALAVRA = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	arquivo=dir_builder(dir,account_address,"trash/tree_L_subjects.bin");
	if (!(arquivos->trash_tree_L_subjects = fopen(arquivo,"r+b")))
		error_m("Error at file opening");
	free(arquivo);

	return arquivos;
}

void close_account_files(ARQUIVOS *arquivos)
{
	fclose(arquivos->config);
	fclose(arquivos->email_list);
	fclose(arquivos->horario_list);
	fclose(arquivos->text_list);
	fclose(arquivos->subject_list);
	fclose(arquivos->word_list);
	fclose(arquivos->lista_enc);
	fclose(arquivos->tree_HORARIO);
	fclose(arquivos->tree_PALAVRA);
	fclose(arquivos->tree_messages);
	fclose(arquivos->tree_subjects);
	fclose(arquivos->tree_L_HORARIO);
	fclose(arquivos->tree_L_PALAVRA);
	fclose(arquivos->tree_L_messages);
	fclose(arquivos->tree_L_subjects);
	fclose(arquivos->inbox_tree_HORARIO);
	fclose(arquivos->inbox_tree_PALAVRA);
	fclose(arquivos->inbox_tree_messages);
	fclose(arquivos->inbox_tree_subjects);
	fclose(arquivos->inbox_tree_L_HORARIO);
	fclose(arquivos->inbox_tree_L_PALAVRA);
	fclose(arquivos->inbox_tree_L_messages);
	fclose(arquivos->inbox_tree_L_subjects);
	fclose(arquivos->outbox_tree_HORARIO);
	fclose(arquivos->outbox_tree_PALAVRA);
	fclose(arquivos->outbox_tree_messages);
	fclose(arquivos->outbox_tree_subjects);
	fclose(arquivos->outbox_tree_L_HORARIO);
	fclose(arquivos->outbox_tree_L_PALAVRA);
	fclose(arquivos->outbox_tree_L_messages);
	fclose(arquivos->outbox_tree_L_subjects);
	fclose(arquivos->read_tree_HORARIO);
	fclose(arquivos->read_tree_PALAVRA);
	fclose(arquivos->read_tree_messages);
	fclose(arquivos->read_tree_subjects);
	fclose(arquivos->read_tree_L_HORARIO);
	fclose(arquivos->read_tree_L_PALAVRA);
	fclose(arquivos->read_tree_L_messages);
	fclose(arquivos->read_tree_L_subjects);
	fclose(arquivos->sent_tree_HORARIO);
	fclose(arquivos->sent_tree_PALAVRA);
	fclose(arquivos->sent_tree_messages);
	fclose(arquivos->sent_tree_subjects);
	fclose(arquivos->sent_tree_L_HORARIO);
	fclose(arquivos->sent_tree_L_PALAVRA);
	fclose(arquivos->sent_tree_L_messages);
	fclose(arquivos->sent_tree_L_subjects);
	fclose(arquivos->trash_tree_HORARIO);
	fclose(arquivos->trash_tree_PALAVRA);
	fclose(arquivos->trash_tree_messages);
	fclose(arquivos->trash_tree_subjects);
	fclose(arquivos->trash_tree_L_HORARIO);
	fclose(arquivos->trash_tree_L_PALAVRA);
	fclose(arquivos->trash_tree_L_messages);
	fclose(arquivos->trash_tree_L_subjects);

	free(arquivos);
	return;
}

PRINCIPAL *open_server_files()
{
	PRINCIPAL *principal=(PRINCIPAL *)malloc(sizeof(PRINCIPAL));
	settings set;
	char *arquivo;

	if ((principal->settings = fopen("settings.bin","r+b")))
	{
		fread(&set,sizeof(settings),1,principal->settings);
		rewind(principal->settings);
		arquivo=filepath_gen(set.dir,"addresses.bin");
		if (!(principal->addresses = fopen(arquivo,"r+b")))
			error_m("Error at file opening");
		free(arquivo);
		arquivo=filepath_gen(set.dir,"tree_CONTA.bin");
		if (!(principal->tree_CONTA = fopen(arquivo,"r+b")))
			error_m("Error at file opening");
		free(arquivo);
		arquivo=filepath_gen(set.dir,"tree_L_CONTA.bin");
		if (!(principal->tree_L_CONTA = fopen(arquivo,"r+b")))
			error_m("Error at file opening");
		free(arquivo);;
	}
	return principal;
}

void close_server_files(PRINCIPAL *principal)
{
	fclose(principal->addresses);
	fclose(principal->settings);
	fclose(principal->tree_CONTA);
	fclose(principal->tree_L_CONTA);
}

int number_of_emails(FILE *tree)
{
	ARVOREB avb;
	rewind(tree);
	fread(&avb,sizeof(ARVOREB),1,tree);
	return avb.num_SUB_NODOS;
}



void formated_message(char *string){
	printf("%s %-66s %s\n",
				"\\\\\\\\\t",
				string,
				"\t\\\\\\\\");
}
