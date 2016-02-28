/*
 * functions_2_struct.h
 *
 *  Created on: 11/01/2016
 *      Author: ricardo
 */
//MUDANÇAS
#ifndef FUNCTIONS_2_STRUCT_H_
#define FUNCTIONS_2_STRUCT_H_

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "functions_2_mail.h"

#define cls system("CLS || clear");
#define pause printf("\nDigite algo para continuar\n"); getchar();
#define spc printf("  |");
#define spc_m printf("              ");
#define nl printf("\n");
#define line nl; printf("____________________________________________________________"); nl;
#define x 10
#define k 64
//#define dir \e-server-v2\data\ //Diretório no Windows
//#define dir /e-server-v2/data/ //Diretório no Linux

// 	Temos que voltar o ponteiro dos arquivos depois das operações de leitura


typedef struct
{
	int num_addresses;
	int next_address;
	char dir[100];
}settings;

typedef struct
{
	int account_address;
	int num_messages;
	int num_subjects;
	int num_emails;
	int num_LISTA_ENC;
	int num_HORARIO;
	int num_PALAVRA;
	int next_message;
	int next_subject;
	int next_email;
	int next_LISTA_ENC;
	int next_HORARIO;
	int next_PALAVRA;

}configuration;

typedef struct
{
	char mail[300];

}messages;

typedef struct
{
	char subject[100];

}subjects;

typedef struct
{
	char address[64];

}addresses;

typedef struct //O resto das informações não serve pra busca
{
	//int dia,mes,ano,horas,minutos,segundos;
	int data[6];//data ordenada por relevancia (ano,mes,dia,hora,minuto,segundo)

}HORARIO;

typedef struct
{
	int remetente;
	int destinatario;
	int assunto;
	int MSG;
	HORARIO data;
	int historico; 		// PARA RICARDO E RUAN DO FUTURO: A ESTRUTURA RETRO ALUDIDA
						// REFERENCIARÁ UM SUBNODO, E ASSIM EM DIANTE, ENCADEANDO. COM CADEADOS.
}SUB_NODO;

typedef struct
{
       int user;
       int password;
       int inbox; //Todos vão conter o valor no qual está no vetor o NODO que corresponde
       int outbox;
       int read;
       int trash;
       int sent;

}CONTA;//Conta deve ser uma arvore pois seria totalmente incompreensivel
//usar metodos tão sofisticados de busca pra tudo exceto pra achar as contas

typedef struct
{
	int chaves[k-1]; 	// Campo que é escolhido convenientemente ao funcionamento do sistema. (messages, subjects, HORARIO
	int addresses[k-1];	// Apontam para Listas de SUB_NODO
	int filhos[k]; 		// NODOS
	int pai;
	char num_chaves;	// Escolha do tipo char devido ao tamanho máximo escalado para o programa, 64 filhos e 63 chaves.
	char num_filhos;	// Número de Filhos. Também pode indicar se o NODO é uma folha ou não, 0 = folha.

}NODO;	//	B, B# ou B+? já passou da hora!!
		// 	B, PORRA!

typedef struct
{
	int arvoreb;

}ARVOREB;

typedef struct
{
	char key[30];

}PALAVRA;

typedef struct
{
	int address;
	int next;

}LISTA;

//ESCOPO DAS FUNÇÕES
void error_m(char *errormessage);
char* dir_builder(int account_number,char*dir,char* file);
void create_address_list(char *dir);
void add_address(char *new,char *dir);
void remove_address(int scroll,char *dir);
char* get_address(int scroll,char *dir);
void setup(char *dir);
void create_config(int account_address,char *dir);
void create_text_list(int account_address,char *dir);
void add_text(int account_address,char *dir,char *new);
void remove_text(int account_address,char *dir,int scroll);
char* get_text(int account_address, char* dir,int scroll);
void create_subject_list(int account_address,char* dir);
void add_subject(int account_address,char *dir,char *new);
void remove_subject(int account_address,char *dir,int scroll);
char* get_subject(int account_address,char *dir,int scroll);
void create_email_list(int account_address,char *dir);
void add_email(int account_address,char *dir,int remetente,int destinatario, int assunto, int MSG, HORARIO data, int historico);
void remove_email(int account_address,char *dir,int scroll);
void create_LISTA_ENC(int account_address, char *dir);
void add_LISTA_ENC(int account_address, char *dir,int ultimo,int novo);
void remove_LISTA_ENC(int account_address, char *dir,int anterior,int atual);//A chamada desta função deve ser feita dentro da arvore onde é posível ter essas informações
void create_horario_list(int account_address, char *dir);
void add_horario(int account_address, char *dir,HORARIO novo);
void remove_horario(int account_address, char *dir,int scroll);
void create_word_list(int account_address,char *dir);
void add_word(int account_address,char *dir, char *new);
void remove_word(int account_address,char *dir, int scroll);
int horario_igual(HORARIO a,HORARIO b);
int horario_maior(HORARIO a,HORARIO b);
int horario_menor(HORARIO a,HORARIO b);
int horario_menor_igual(HORARIO a,HORARIO b);
int horario_maior_igual(HORARIO a,HORARIO b);


void error_m(char *errormessage)
{ 	/* Função para facilitar exibição de mensagens de erro */
    printf("\n%s",errormessage);
    pause;
    exit(1);
}

char *filepath_gen(char *dir, char *file)
{ 	// 	Função para gerar ponteiro para char com o diretório
	char *path=(char *) malloc(sizeof(char)*250);
	printf("minitest\n");
	sprintf(path, "%s",dir);
	strcat(path,file);
	return path;
}
// Não se pode usar strcat em string constante, perdi um tempinho com isso.
char* dir_builder(int account_number,char*dir,char* file)
{	//	Função para gerar o caminho do arquivo
	return strcat(strcat(strcat(dir,"/"),get_address(account_number,dir)),file);
}

//LISTA DE ENDEREÇOS GLOBAL
void create_address_list(char *dir) //
{	// Função para criar o arquivo da Lista de Endereços
	FILE *new;
	addresses ad;
	char *dir_ad=filepath_gen(dir,"addresses.bin");
	printf("TEST1\n");
	printf("TEST2: %s\n",dir_ad);
	if(!(new=fopen(dir_ad,"wb")))
		error_m("Error at file allocation");
	else
	{
		sprintf(&(ad.address[0]),"%d",-1);//Tinha esquecido disso kkkk
		fwrite(&ad,sizeof(addresses),1,new);
		fclose(new);
	}

	return;
}

void add_address(char *new,char *dir)
{	//	Função para adicionar um endereço na Lista de Endereços
	FILE *set,*ad;
	char *dir_s=filepath_gen(dir,"settings.bin");
	char *dir_ad=filepath_gen(dir,"addresses.bin");
	settings s;
	addresses ads;
	int scroll;		//	Variáveis auxliares
	fpos_t c;
	if(!(set=fopen(dir_s,"r+b")))				// Confirmando abertura dos arquivos de settings e addresses
		error_m("Error at file oppening");
	if(!(ad=fopen(dir_ad,"r+b")))
		error_m("Error at file oppening");

	fread(&s,sizeof(settings),1,set);	//	Lendo arquivo de configurações e armazenando na variável s
	rewind(set);						//	Colocando a posição do fluxo de dados no ínicio
	scroll=(s.next_address == -1)?s.num_addresses:s.next_address;	//	Definindo a posição em que o novo endereço será salvo no arquivo addresses.bin
	printf("NEXT: %d\nNUM AD: %d",s.next_address,s.num_addresses);
	fseek(ad,scroll*sizeof(addresses),SEEK_SET);							//	Deslocando a posição do buffer no arquivo addresses.bin
	if(s.next_address!=-1)											//	caso haja blocos não utilizados a serem subscritos
	{
		fgetpos(ad,&c);								//	Guardando a posição atual do fluxo de dados
		fread(&ads,sizeof(addresses),1,ad);			//	Lendo arquivo de endereços e armazenando na variável ad
		sscanf(ads.address,"%d",&(s.next_address));	//	Atualizando o próximo a ser subscrito
		fsetpos(ad,&c);								// 	Retornando a posição do fluxo de dados para a salva anteriormente
	}
	sprintf(ads.address,"%s",new);			//	Guardando novo endereço
	s.num_addresses++;						//	Incrementando o número de endereços
	fwrite(&s,sizeof(settings),1,set);		//	Escrevendo alterações feitas nos arquivos
	fwrite(&ads,sizeof(addresses),1,ad);
	fclose(set);							// Fechando arquivos
	fclose(ad);

	free(dir_ad);	// Liberando ponteiros
	free(dir_s);

	return;
}

void remove_address(int scroll,char *dir)
{	//	Função para remover um endereço da Lista de Endereços
	FILE *set,*ad;
	char *dir_s=filepath_gen(dir,"settings.bin"),*dir_ad=filepath_gen(dir,"addresses.bin");
	settings s;
	addresses ads;
	fpos_t c;

	if(!(set=fopen(dir_s,"r+b")))
		error_m("Error at file oppening");
	if(!(ad=fopen(dir_ad,"r+b")))
		error_m("Error at file oppening");

	fread(&s,sizeof(settings),1,set);
	rewind(set);
	fseek(ad,scroll*sizeof(addresses),SEEK_SET);
	fgetpos(ad,&c);
	fread(&ads,sizeof(addresses),1,ad);
	fsetpos(ad,&c);
	sprintf(&(ads.address[0]),"%d", s.next_address);
	s.next_address=scroll;
	s.num_addresses--;
	fwrite(&s,sizeof(settings),1,set);//escrevendo alterações feitas
	fwrite(&ads,sizeof(addresses),1,ad);
	fclose(set);
	fclose(ad);

	free(dir_ad);
	free(dir_s);

	return;
}

char* get_address(int scroll,char *dir)
{	//	Função que retorna um endereço da Lista de Endereços
	char* address = (char*)malloc(sizeof(char)*64),*dir_ad=filepath_gen(dir,"addresses.bin");
	FILE *ad;
	addresses ads;

	if(!(ad=fopen(dir_ad,"rb")))
		error_m("Error at file oppening");

	fseek(ad,scroll*sizeof(addresses),SEEK_SET);
	fread(&ads,sizeof(addresses),1,ad);
	sprintf(address,"%s",ads.address);
	fclose(ad);

	return address;
}

//CONFIGURAÇÃO
void setup(char *dir)
{	//	Função de configuração geral do Servidor
	FILE *set;
	settings new;
	char *dir_s = filepath_gen(dir,"settings.bin");

	if(!(set=fopen(dir_s,"wb")))
		error_m("Error at file allocation");
	else
	{
		sprintf(new.dir,"%s",dir);
		new.num_addresses=0;
		new.next_address=0;
		fwrite(&new,sizeof(settings),1,set);
		fclose(set);
	}
	free(dir_s);

	return;
}

void create_config(int account_address,char *dir)
{	// Função para criar o arquivo de Configuração do Usuário
	char *address = dir_builder(account_address,dir,"/config.bin");
	FILE *config;
	configuration new;

	if(!(config=fopen(address,"wb")))
		error_m("Error at file allocation");
	else
	{
		new.account_address=account_address;
		new.num_messages=0;
		new.num_subjects=0;
		new.num_emails=0;
		new.num_LISTA_ENC=0;
		new.num_HORARIO=0;
		new.next_message=0;
		new.next_subject=0;
		new.next_email=0;
		new.next_LISTA_ENC=0;
		new.next_HORARIO=0;

		fwrite(&new,sizeof(configuration),1,config);
		fclose(config);
	}
	free(address);

	return;
}

//LISTA DE TEXTOS
void create_text_list(int account_address,char *dir)
{	// Função para criar o arquivo da Lista de Textos do usuário
	char *address=dir_builder(account_address,dir,"/text_list.bin");
	FILE *text_list;
	messages msg;

	if(!(text_list=fopen(address,"wb")))
		error_m("Error at file allocation");
	else
	{
		sprintf(&(msg.mail[0]),"%d",-1);
		fwrite(&msg,sizeof(messages),1,text_list);
		fclose(text_list);
	}
	free(address);

	return;
}

void add_text(int account_address,char *dir,char *new)
{	//	Função para adicionar um texto à Lista de Textos
	char *address = dir_builder(account_address,dir,"/text_list.bin"),*config_address =dir_builder(account_address,dir,"/config.bin");
	FILE *text_list,*config;
	messages msg;
	configuration c;
	int scroll;
	fpos_t p;

	if(!(config=fopen(config_address,"r+b")))
		error_m("Error at file oppening");
	else
	if(!(text_list=fopen(address,"r+b")))
		error_m("Error at file oppening");
	else
	{
		fread(&c,sizeof(configuration),1,config);
		rewind(config);
		scroll=(c.next_message == -1)?c.num_messages:c.next_message;
		fseek(text_list,scroll*sizeof(messages),SEEK_SET);
		if (c.next_message != -1)
		{
			fgetpos(text_list,&p);
			fread(&msg,sizeof(messages),1,text_list);
			sscanf(msg.mail,"%d",&(c.next_message));
			fsetpos(text_list,&p);
		}
		sprintf(msg.mail,"%s",new);
		c.num_messages++;
		fwrite(&c,sizeof(configuration),1,config);
		fwrite(&msg,sizeof(messages),1,text_list);
		fclose(config);
		fclose(text_list);

	}
	free(address);
	free(config_address);

	return;
}

void remove_text(int account_address,char *dir,int scroll)//precisamos validar as remoções depois
{	//	Função para remover um texto da Lista de Textos
	char *list_address=dir_builder(account_address,dir,"/text_list.bin"),*config_address = dir_builder(account_address,dir,"/config.bin");
	FILE *text_list,*config;
	messages msg;
	configuration c;

	if(!(config=fopen(config_address,"r+b")))
		error_m("Error at file oppening");
	else
	if(!(text_list=fopen(list_address,"r+b")))
		error_m("Error at file oppening");
	else
	{
		fread(&c,sizeof(configuration),1,config);
		rewind(config);
		sprintf(msg.mail,"%d",c.next_message);
		c.num_messages--;
		c.next_message=scroll;
		fseek(text_list,scroll*sizeof(messages),SEEK_SET);
		fwrite(&msg,sizeof(messages),1,text_list);
		fwrite(&c,sizeof(configuration),1,config);
		fclose(text_list);
		fclose(config);
	}
	free(list_address);
	free(config_address);

	return;
}

char* get_text(int account_address, char* dir,int scroll)
{	//	Função que retorna um texto da Lista de Textos
	char *address=dir_builder(account_address,dir,"/text_list.bin");
	char *t=(char*)malloc(sizeof(char)*300);
	messages read;
	FILE *texts;

	if(!(texts=fopen(address,"rb")))
		error_m("Eror at file oppening");
	else
	{
		fseek(texts,scroll*sizeof(messages),SEEK_SET);
		fread(&read,sizeof(messages),1,texts);
		fclose(texts);
	}
	free(address);
	sprintf(t,"%s",read.mail);

	return t;
}


//LISTA DE ASSUNTOS
void create_subject_list(int account_address,char* dir)
{	// Função para criar o arquivo da Lista de Assuntos do usuário
	char *subjects_address=dir_builder(account_address,dir,"/subject_list.bin");//fazer uma função pra isso!!!
	FILE *subject_list;
	subjects sub;

	if(!(subject_list=fopen(subjects_address,"wb")))
		error_m("Error at file allocation");
	else
	{
		sprintf(sub.subject,"%d",-1);
		fwrite(&sub,sizeof(subjects),1,subject_list);
		fclose(subject_list);
	}
	free(subjects_address);

	return;
}

void add_subject(int account_address,char*dir,char *new)
{	// Função para adicionar um assunto à Lista de Assuntos
	char *address=dir_builder(account_address,dir,"/subject_list.bin"),*config_address=dir_builder(account_address,dir,"/config.bin");
	FILE *subject_list,*config;
	configuration c;
	subjects s;
	int scroll;
	fpos_t p;

	if(!(config=fopen(config_address,"r+b")))
		error_m("Error at file oppening");
	else
	if(!(subject_list=fopen(address,"r+b")))
		error_m("Error at file oppening");
	else
	{
		fread(&c,sizeof(configuration),1,config);
		rewind(config);
		scroll=(c.next_subject==-1)?c.num_subjects:c.next_subject;
		fseek(subject_list,scroll*sizeof(subjects),SEEK_SET);
		if(c.next_subject != -1)
		{
			fgetpos(subject_list,&p);
			fread(&s,sizeof(subjects),1,subject_list);
			sscanf(s.subject,"%d",&(c.next_subject));
			fsetpos(subject_list,&p);
		}
		sprintf(s.subject,"%s",new);
		c.num_subjects++;
		fwrite(&c,sizeof(configuration),1,config);
		fwrite(&s,sizeof(subjects),1,subject_list);
		fclose(config);
		fclose(subject_list);
	}
	free(address);
	free(config_address);

	return;
}

void remove_subject(int account_address,char *dir,int scroll)
{	// Função para remover um assunto da Lista de Assuntos
	char *address=dir_builder(account_address,dir,"/subject_list.bin"),*config_address=dir_builder(account_address,dir,"/config.bin");
	FILE *subject_list,*config;
	configuration c;
	subjects s;

	if(!(config=fopen(config_address,"r+b")))
		error_m("Error at file oppening");
	else
	if(!(subject_list=fopen(address,"r+b")))
		error_m("Error at file oppening");
	else
	{
		fread(&c,sizeof(configuration),1,config);
		rewind(config);
		sprintf(s.subject,"%d",c.next_subject);
		c.num_subjects--;
		c.next_subject=scroll;
		fseek(subject_list,scroll*sizeof(subjects),SEEK_SET);
		fwrite(&s,sizeof(subjects),1,subject_list);
		fwrite(&c,sizeof(configuration),1,config);
		fclose(config);
		fclose(subject_list);
	}
	free(address);
	free(config_address);

	return;
}

char* get_subject(int account_address,char *dir,int scroll)
{	//	Função que retorna um assunto da Lista de Assuntos dada sua posição (scroll)
	char *address=dir_builder(account_address,dir,"/subject_list.bin");
	FILE *subject_list;
	char *sub;
	subjects s;

	if(!(subject_list=fopen(address,"rb")))
		error_m("Error at file oppening");
	else
	{
		sub=(char*)malloc(sizeof(char)*100);
		fseek(subject_list,scroll*sizeof(subjects),SEEK_SET);
		fread(&s,sizeof(subjects),1,subject_list);
		fclose(subject_list);
		sprintf(sub,"%s",s.subject);
	}
	free(address);

	return sub;
}

//LISTA DE EMAILS
void create_email_list(int account_address,char *dir)
{	// Função para criar o arquivo da Lista de Emails
	char *address = dir_builder(account_address,dir,"/email_list.bin");
	FILE *email_list;
	SUB_NODO new;

	if (!(email_list=fopen(address,"wb")))
			error_m("Error at file allocation");
	else
	{
		new.remetente=-1;
		fwrite(&new,sizeof(messages),1,email_list);
		fclose(email_list);
	}
	free(address);

	return;
}

void add_email(int account_address,char *dir,int remetente,int destinatario, int assunto, int MSG, HORARIO data, int historico)
{ 	//	Função para adicionar um email na Lista de Emails
	char *address=dir_builder(account_address,dir,"/email_list.bin"),*config_address=dir_builder(account_address,dir,"/config.bin");
	FILE *email_list, *config; 	// 	Arquivos que serão abertos
	configuration c; 			//	Manipulação da configuração
	SUB_NODO e; 				//	Manipulação de email
	int scroll;					// 	Variável para deslocamento
	fpos_t p;

	if (!(email_list=fopen(address,"r+b"))) 	// 	Abrindo o arquivo da Lista de Emails
		error_m("Error at file oppening"); 		// 	Mensagem de erro
	else
	if (!(config=fopen(config_address,"r+b"))) 	// 	Abrindo o arquivo de Configuração da Conta
		error_m("Error at file oppening");		// 	Mensagem de erro
	else
	{
		fread(&c,sizeof(configuration),1,config);				//
		rewind(config);
		scroll=(c.next_email==-1)?c.num_emails:c.next_email;	//
		fseek(email_list,scroll*sizeof(SUB_NODO),SEEK_SET);								//
		if (c.next_email!=-1)									//
		{
			fgetpos(email_list,&p);
			fread(&e,sizeof(SUB_NODO),1,email_list);			//
			c.next_email = e.remetente;							//
			fsetpos(email_list,&p);
		}
		c.num_emails++;											//
		e.remetente = remetente;								//
		e.destinatario = destinatario;							//
		e.assunto = assunto;									//
		e.MSG = MSG;											//
		for (scroll = 0;scroll < 6; scroll++)					//
			e.data.data[scroll] = data.data[scroll];			//
		e.historico = historico;								//
		fwrite(&c,sizeof(configuration),1,config);				//
		fwrite(&e,sizeof(SUB_NODO),1,email_list);				//
		fclose(config);											//
		fclose(email_list);										//
	}
	free(address);			//
	free(config_address);	//

	return;
}

void remove_email(int account_address,char *dir,int scroll)
{	//	Função para removar email da Lista de Emails dada sua posição (scroll)
	char *address=dir_builder(account_address,dir,"/email_list.bin"),*config_address=dir_builder(account_address,dir,"/config.bin");
	FILE *email_list, *config; 	// 	Arquivos que serão abertos
	configuration c; 			//	Manipulação da configuração
	SUB_NODO e; 				//	Manipulação de email
	fpos_t p;

	if (!(email_list=fopen(address,"r+b"))) 	// 	Abrindo o arquivo da Lista de Emails
		error_m("Error at file oppening"); 		// 	Mensagem de erro
	else
	if (!(config=fopen(config_address,"r+b"))) 	// 	Abrindo o arquivo de Configuração da Conta
		error_m("Error at file oppening");		// 	Mensagem de erro
	else
	{
		fread(&c,sizeof(configuration),1,config);				//
		rewind(config);
		fseek(email_list,scroll*sizeof(SUB_NODO),SEEK_SET);								//
		fgetpos(email_list,&p);
		fread(&e,sizeof(SUB_NODO),1,email_list);				//
		fsetpos(email_list,&p);
		e.remetente = c.next_email;								//
		c.next_email = scroll;									//
		c.num_emails--;											//
		fwrite(&c,sizeof(configuration),1,config);				//
		fwrite(&e,sizeof(SUB_NODO),1,email_list);				//
		fclose(config);											//
		fclose(email_list);										//
	}
	free(address);			//
	free(config_address);	//

	return;
}

//LISTA DE LISTAS ENCADEADAS DE EMAILS
void create_LISTA_ENC(int account_address, char *dir)
{	// Função para criar o arquivo da Lista de Listas Encadeadas de Emails
	char* address = dir_builder(account_address,dir,"/lista_enc.bin");
	FILE *lista_enc;
	LISTA l;

	if(!(lista_enc=fopen(address,"wb")))
		error_m("Error at file allocation");
	else
	{
		l.next=l.address==-1;
		fwrite(&l,sizeof(LISTA),1,lista_enc);
		fclose(lista_enc);
	}
	free(address);

	return;
}

void add_LISTA_ENC(int account_address, char *dir,int antecessor,int novo)
{	//	Função para adicionar lista à Lista de Listas Encadeadas de Emails
	char   *address = dir_builder(account_address,dir,"/lista_enc.bin"),*config_address=dir_builder(account_address,dir,"/config.bin");
	FILE *lista_enc,*config;
	LISTA a;
	configuration c;
	int scroll,aux=-1;
	fpos_t p;

	if(!(config=fopen(config_address,"r+b")))
		error_m("Error at file oppening");
	else
	if(!(lista_enc=fopen(address,"r+b")))
		error_m("Error at file oppening");
	else
	{
		fread(&c,sizeof(configuration),1,config);
		rewind(config);
		scroll = (c.next_LISTA_ENC==-1)?c.num_LISTA_ENC:c.next_LISTA_ENC;
		if(antecessor >= 0)
		{
			fseek(lista_enc,antecessor*sizeof(LISTA),SEEK_SET);
			fgetpos(lista_enc,&p);
			fread(&a,sizeof(LISTA),1,lista_enc);
			fsetpos(lista_enc,&p);
			aux = a.next;
			a.next = scroll;
			fwrite(&a,sizeof(LISTA),1,lista_enc);	//	Não tem que voltar uma posição antes de escrever?
													//	Se não vai estar gravando uma posição na frente
													// 	da posição original de a. - FIZ A ALTERAÇÃO
		}
		fseek(lista_enc,scroll*sizeof(LISTA),SEEK_SET);
		fgetpos(lista_enc,&p);
		fread(&a,sizeof(LISTA),1,lista_enc);
		fsetpos(lista_enc,&p);
		if(c.next_LISTA_ENC!=-1)
			c.next_LISTA_ENC=a.next;
		a.next=aux;
		a.address = novo;
		fwrite(&a,sizeof(LISTA),1,lista_enc);
		fwrite(&c,sizeof(configuration),1,config);
		fclose(lista_enc);
		fclose(config);
	}
	free(address);
	free(config_address);

	return;
}

void remove_LISTA_ENC(int account_address, char *dir,int antecessor,int atual)
{	//	Função para remover lista da Lista de Listas Encadeadas de Emails
	char   *address = dir_builder(account_address,dir,"/lista_enc.bin"),*config_address=dir_builder(account_address,dir,"/config.bin");
	FILE *lista_enc,*config;
	LISTA a;
	configuration c;
	int aux;
	fpos_t p;

	if(!(config=fopen(config_address,"r+b")))
		error_m("Error at file oppening");
	else
	if(!(lista_enc=fopen(address,"r+b")))
		error_m("Error at file oppening");
	else
	{
		fread(&c,sizeof(configuration),1,config);
		rewind(config);
		fseek(lista_enc,atual*sizeof(LISTA),SEEK_SET);
		fgetpos(lista_enc,&p);
		fread(&a,sizeof(LISTA),1,lista_enc);
		fsetpos(lista_enc,&p);
		aux = a.next;
		a.next=c.next_LISTA_ENC;
		c.num_LISTA_ENC--;
		c.next_LISTA_ENC=atual;
		if(antecessor >= 0)
		{
			fseek(lista_enc,antecessor,0);
			fgetpos(lista_enc,&p);
			fread(&a,sizeof(LISTA),1,lista_enc);
			fsetpos(lista_enc,&p);
			a.next=aux;
			fwrite(&a,sizeof(LISTA),1,lista_enc);
		}
		fwrite(&c,sizeof(configuration),1,config);
		fclose(lista_enc);
	}
	free(address);
	free(config_address);

	return;
}

//LISTA DE HORÁRIOS
void create_horario_list(int account_address, char *dir)
{	// Função para criar arquivo da Lista de Horários
	char *address = dir_builder(account_address,dir,"/horario_list.bin");
	FILE *horarios;
	HORARIO a;

	if(!(horarios=fopen(address,"wb")))
		error_m("Error at file allocation");
	else
	{
		a.data[0]=-1;
		fwrite(&a,sizeof(HORARIO),1,horarios);
		fclose(horarios);
	}
	free(address);

	return;
}

void add_horario(int account_address, char *dir,HORARIO novo)
{	// Função para adicionar horário à Lista de Horários
	char *address = dir_builder(account_address,dir,"/horario_list.bin"),*config_address=dir_builder(account_address,dir,"/config.bin");
	FILE *horarios,*config;
	HORARIO a;
	configuration c;
	int scroll;
	fpos_t p;

	if(!(config=fopen(config_address,"r+b")))
		error_m("Error at file oppening");
	else
	if(!(horarios=fopen(address,"r+b")))
		error_m("Error at file oppening");
	else
	{
		fread(&c,sizeof(configuration),1,config);
		rewind(config);
		scroll=(c.next_HORARIO==-1)?c.num_HORARIO:c.next_HORARIO;
		fseek(horarios,scroll*sizeof(HORARIO),SEEK_SET);
		fgetpos(horarios,&p);
		fread(&a,sizeof(HORARIO),1,horarios);
		fsetpos(horarios,&p);
		if(c.next_HORARIO!=-1)
			c.next_HORARIO=a.data[0];
		c.num_HORARIO++;
		for(scroll=0;scroll<6;scroll++)
			a.data[scroll]=novo.data[scroll];
		fwrite(&c,sizeof(configuration),1,config);
		fwrite(&a,sizeof(HORARIO),1,horarios);
		fclose(horarios);
		fclose(config);
	}
	free(address);
	free(config_address);

	return;
}

void remove_horario(int account_address, char *dir,int scroll)
{	// Função para remover horário da Lista de Horários
	char *address = dir_builder(account_address,dir,"/horario_list.bin"),*config_address=dir_builder(account_address,dir,"/config.bin");
	FILE *horarios,*config;
	HORARIO a;
	configuration c;

	if(!(config=fopen(config_address,"r+b")))
		error_m("Error at file oppening");
	else
	if(!(horarios=fopen(address,"r+b")))
		error_m("Error at file oppening");
	else
	{
		fread(&c,sizeof(configuration),1,config);
		rewind(config);
		a.data[0]=c.next_HORARIO;
		c.next_HORARIO=scroll;
		c.num_HORARIO--;
		fseek(horarios,scroll*sizeof(HORARIO),SEEK_SET);
		fwrite(&c,sizeof(configuration),1,config);
		fwrite(&a,sizeof(HORARIO),1,horarios);
		fclose(horarios);
		fclose(config);
	}
	free(address);
	free(config_address);

	return;
}

//LISTA DE PALAVRAS
void create_word_list(int account_address,char *dir)
{	//	Função para criar o arquivo da Lista de Palavras
	char *address = dir_builder(account_address,dir,"/word_list.bin");
	FILE *word_list;
	PALAVRA w;

	if (!(word_list=fopen(address,"wb")))
		error_m("Error at file allocation");
	sprintf(w.key,"%d",-1);
	fwrite(&w,sizeof(PALAVRA),1,word_list);
	fclose(word_list);

	free(address);

	return;
}

void add_word(int account_address,char *dir, char *new)
{	// 	Função para adicionar palavra da Lista de Palavras
	char *address = dir_builder(account_address,dir,"/word_list.bin"),*config_address=dir_builder(account_address,dir,"/config.bin");
	FILE *word_list,*config;
	PALAVRA w;
	configuration c;
	int scroll;
	fpos_t p;

	if (!(word_list=fopen(address,"r+b")))
		error_m("Error at file oppening");
	else
	if (!(config=fopen(config_address,"r+b")))
		error_m("Error at file oppening");
	else
	{
		fread(&c,sizeof(configuration),1,config);
		rewind(config);
		scroll=(c.next_PALAVRA==-1)?c.num_PALAVRA:c.next_PALAVRA;
		fseek(word_list,scroll*sizeof(PALAVRA),SEEK_SET);
		fgetpos(word_list,&p);
		fread(&w,sizeof(PALAVRA),1,word_list);
		fsetpos(word_list,&p);
		if (c.next_PALAVRA != -1)
		{
			fgetpos(word_list,&p);
			fread(&w,sizeof(messages),1,word_list);
			sscanf(w.key,"%d",&(c.next_PALAVRA));
			fsetpos(word_list,&p);
		}
		sprintf(w.key,"%s",new);
		c.num_PALAVRA++;
		fwrite(&w,sizeof(PALAVRA),1,word_list);
		fwrite(&c,sizeof(PALAVRA),1,config);
		fclose(word_list);
		fclose(config);
	}
	free(address);
	free(config_address);

	return;
}

void remove_word(int account_address,char *dir, int scroll)
{	// 	Função para remover palavra da Lista de Palavras
	char *address = dir_builder(account_address,dir,"/word_list.bin"),*config_address=dir_builder(account_address,dir,"/config.bin");
	FILE *word_list,*config;
	PALAVRA w;
	configuration c;

	if (!(word_list=fopen(address,"r+b")))
		error_m("Error at file oppening");
	else
	if (!(config=fopen(config_address,"r+b")))
		error_m("Error at file oppening");
	else
	{
		fread(&c,sizeof(configuration),1,config);
		rewind(config);
		sprintf(w.key,"%d",c.next_PALAVRA);
		c.num_PALAVRA--;
		c.next_PALAVRA=scroll;
		fseek(word_list,scroll*sizeof(PALAVRA),SEEK_SET);
		fwrite(&w,sizeof(PALAVRA),1,word_list);
		fwrite(&c,sizeof(PALAVRA),1,config);
		fclose(word_list);
		fclose(config);
	}
	free(address);
	free(config_address);

	return;
}


//FUNÇÕES DE COMPARAÇÃO DE HORÁRIO
int horario_igual(HORARIO a,HORARIO b)
{
	int c;

	for(c=0;c<6;c++)
		if(a.data[c]!=b.data[c])
			return 0;
	return 1;
}

int horario_maior(HORARIO a,HORARIO b)
{
	int c;

	for(c=0;c<6;c++)
	{
		if (a.data[c] > b.data[c])
			return 1;
		if (a.data[c] < b.data[c])
			return 0;
	}
	return 0;//se chegar aqui necessariamente é igual
}

int horario_menor(HORARIO a,HORARIO b)
{
	int c;

	for(c=0;c<6;c++)
	{
		if (a.data[c] < b.data[c])
			return 1;
		if (a.data[c] > b.data[c])
			return 0;
	}
	return 0;//se chegar aqui necessariamente é igual
}

int horario_menor_igual(HORARIO a,HORARIO b)
{
	int c;

	for(c=0;c<6;c++)
	{
		if (a.data[c] < b.data[c])
			return 1;
		if (a.data[c] > b.data[c])
			return 0;
	}
	return 1;//se chegar aqui necessariamente é igual
}

int horario_maior_igual(HORARIO a,HORARIO b)
{
	int c;

	for(c=0;c<6;c++)
	{
		if(a.data[c] > b.data[c])
			return 1;
		if(a.data[c] < b.data[c])
			return 0;
	}
	return 1;//se chegar aqui necessariamente é igual
}

#endif /* FUNCTIONS_2_STRUCT_H_ */
