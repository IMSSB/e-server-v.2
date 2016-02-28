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
	int next_message;
	int next_subject;
	int next_email;
	int next_LISTA_ENC;
	int next_HORARIO;

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

char* dir_builder(int account_number,char*dir,char* file)
{	//	Função para gerar o caminho do arquivo
	return strcat(strcat(strcat(dir,"/"),get_address(account_number,dir)),file);
}

//LISTA DE ENDEREÇOS GLOBAL
void create_address_list(char *dir) //
{	// Função para criar o arquivo da Lista de Endereços
	FILE *new;
	addresses ad;
	char *dir_ad=strcat(dir,"/addresses.bin");

	if(!(new=fopen(dir_ad,"wb")))
		error_m("Error at file allocation");
	else
	{	sprintf(&(ad.address[0]),"%d",-1);//Tinha esquecido disso kkkk
		fwrite(&ad,sizeof(addresses),1,new);
		fclose(new);
	}

	return;
}

void add_address(char *new,char *dir)
{	//	Função para adicionar um endereço na Lista de Endereços
	FILE *set,*ad;
	char *dir_s=strcat(dir,"/settings.bin"),*dir_ad=strcat(dir,"/addresses.bin");
	settings s;
	addresses ads;
	int scroll;

	if(!(set=fopen(dir_s,"w+b")))
		error_m("Error at file oppening");
	if(!(ad=fopen(dir_ad,"w+b")))
		error_m("Error at file oppening");

	{
		fread(&s,sizeof(settings),1,set);
		scroll=(s.next_address == -1)?s.num_addresses:s.next_address;
		fseek(ad,scroll,0);
		if(s.next_address!=-1)//caso haja blocos não utilizados a serem subscritos
		{
			fread(&ads,sizeof(addresses),1,ad);
			sscanf(ads.address,"%d",s.next_address);//Atualizando o próximo a ser subscrito
		}
		sprintf(ads.address,"%s",new);//guardando novo endereço
		s.num_addresses++;
		fwrite(&s,sizeof(settings),1,set);//escrevendo alterações feitas
		fwrite(&ads,sizeof(addresses),1,ad);
		fclose(set);
		fclose(ad);
	}
	free(dir_ad);
	free(dir_s);

	return;
}

void remove_address(int scroll,char *dir)
{	//	Função para remover um endereço da Lista de Endereços
	FILE *set,*ad;
	char *dir_s=strcat(dir,"/settings.bin"),*dir_ad=strcat(dir,"/addresses.bin");
	settings s;
	addresses ads;


	if(!(set=fopen(dir_s,"w+b")))
		error_m("Error at file oppening");
	if(!(ad=fopen(dir_ad,"w+b")))
		error_m("Error at file oppening");
	{
		fread(&s,sizeof(settings),1,set);
		fseek(ad,scroll,0);
		fread(&ads,sizeof(addresses),1,ad);
		sprintf(&(ads.address[0]),"%d", s.next_address);
		s.next_address=scroll;
		s.num_addresses--;
		fwrite(&s,sizeof(settings),1,set);//escrevendo alterações feitas
		fwrite(&ads,sizeof(addresses),1,ad);
		fclose(set);
		fclose(ad);
	}
	free(dir_ad);
	free(dir_s);

	return;
}

char* get_address(int scroll,char *dir)
{	//	Função que retorna um endereço da Lista de Endereços
	char* address = (char*)malloc(sizeof(char)*64),*dir_ad=strcat(dir,"/addresses.bin");
	FILE *ad;
	addresses ads;

	if(!(ad=fopen(dir_ad,"w+b")))
		error_m("Error at file oppening");
	{
		fseek(ad,scroll,0);
		fread(&ads,sizeof(addresses),1,ad);
		sprintf(address,"%s",ads.address);
		fclose(ad);
	}

	return address;
}

//CONFIGURAÇÃO
void setup(char *dir)
{	//	Função de configuração geral do Servidor
	FILE *set;
	settings new;
	char *dir_s = strcat(dir,"/settings.bin");

	if(!(set=fopen(dir_s,"wb")))
		error_m("Error at file allocation");
	else
	{
		sprintf(new.dir,"%s",dir);
		new.num_addresses=0;
		new.next_address=0;
		fclose(set);
	}
	free(dir_s);

	return;
}

void create_config(int account_address,char *dir)
{	// Função para criar o arquivo de Configuração do Usuário
	char *address;
	FILE *config;
	configuration new;

	address = dir_builder(account_address,dir,"/config.bin");

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
	{
		error_m("Error at file allocation");
	}
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

	if(!(config=fopen(config_address,"w+b")))
	{
		error_m("Error at file oppening");
	}
	else
	if(!(text_list=fopen(address,"w+b")))
	{
		error_m("Error at file oppening");
	}
	else
	{

		fread(&c,sizeof(configuration),1,config);
		scroll=(c.next_message == -1)?c.num_messages:c.next_message;
		fseek(text_list,scroll,0);
		if (c.next_message != -1)
		{
			fread(&msg,sizeof(messages),1,text_list);
			sscanf(msg.mail,"%d",c.next_message);
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

	if(!(config=fopen(config_address,"w+b")))
		error_m("Error at file oppening");
	else
	if(!(text_list=fopen(list_address,"w+b")))
		error_m("Error at file oppening");
	else
	{
		fread(&c,sizeof(configuration),1,config);
		sprintf(msg.mail,"%d",c.next_message);
		c.num_messages--;
		c.next_message=scroll;
		fseek(text_list,scroll,0);
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
		fseek(texts,scroll,0);
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

	if(!(config=fopen(config_address,"w+b")))
	{
		error_m("Error at file oppening");
	}
	else
	if(!(subject_list=fopen(address,"w+b")))
	{
		error_m("Error at file oppening");
	}
	else
	{
		fread(&c,sizeof(configuration),1,config);
		scroll=(c.next_subject==-1)?c.num_subjects:c.next_subject;
		fseek(subject_list,scroll,0);
		if(c.next_subject != -1)
		{
			fread(&s,sizeof(subjects),1,subject_list);
			sscanf(s.subject,"%d",c.next_subject);
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

	if(!(config=fopen(config_address,"w+b")))
	{
		error_m("Error at file oppening");
	}
	else
	if(!(subject_list=fopen(address,"w+b")))
	{
		error_m("Error at file oppening");
	}
	else
	{	fread(&c,sizeof(configuration),1,config);
		sprintf(s.subject,"%d",c.next_subject);
		fseek(subject_list,scroll,0);
		fwrite(&s,sizeof(subjects),1,subject_list);
		c.num_subjects--;
		c.next_subject=scroll;
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



	if(!(subject_list=fopen(address,"w+b")))
	{
		error_m("Error at file oppening");
	}
	else
	{	sub=(char*)malloc(sizeof(char)*100);
		fseek(subject_list,scroll,0);
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

	if (!(email_list=fopen(address,"w+b"))) 	// 	Abrindo o arquivo da Lista de Emails
		error_m("Error at file oppening"); 		// 	Mensagem de erro
	else
	if (!(config=fopen(config_address,"w+b"))) 	// 	Abrindo o arquivo de Configuração da Conta
		error_m("Error at file oppening");		// 	Mensagem de erro
	else
	{
		fread(&c,sizeof(configuration),1,config);				//
		scroll=(c.next_email==-1)?c.num_emails:c.next_email;	//
		fseek(email_list,scroll,0);								//
		if (c.next_email!=-1)									//
		{
			fread(&e,sizeof(SUB_NODO),1,email_list);			//
			c.next_email = e.remetente;							//
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

	if (!(email_list=fopen(address,"w+b"))) 	// 	Abrindo o arquivo da Lista de Emails
		error_m("Error at file oppening"); 		// 	Mensagem de erro
	else
	if (!(config=fopen(config_address,"w+b"))) 	// 	Abrindo o arquivo de Configuração da Conta
		error_m("Error at file oppening");		// 	Mensagem de erro
	else
	{
		fread(&c,sizeof(configuration),1,config);				//
		fseek(email_list,scroll,0);								//
		fread(&e,sizeof(SUB_NODO),1,email_list);				//
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

//LISTA ENCADEADA DE EMAILS
void create_LISTA_ENC(int account_address, char *dir)
{	// Função para criar o arquivo da Lista de Listas Encadeada de Emails
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

	if(!(config=fopen(config_address,"w+b")))
		error_m("Error at file oppening");
	else
	if(!(lista_enc=fopen(address,"w+b")))
		error_m("Error at file oppening");
	else
	{
		fread(&c,sizeof(configuration),1,config);
		scroll = (c.next_LISTA_ENC==-1)?c.num_LISTA_ENC:c.next_LISTA_ENC;
		if(antecessor >= 0)
		{
			fseek(lista_enc,antecessor,0);
			fread(&a,sizeof(LISTA),1,lista_enc);
			aux = a.next;
			a.next = scroll;
			fwrite(&a,sizeof(LISTA),1,lista_enc);
		}
		rewind(lista_enc);
		fseek(lista_enc,scroll,0);
		fread(&a,sizeof(LISTA),1,lista_enc);
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

	if(!(config=fopen(config_address,"w+b")))
		error_m("Error at file oppening");
	else
	if(!(lista_enc=fopen(address,"w+b")))
		error_m("Error at file oppening");
	else
	{
		fread(&c,sizeof(configuration),1,config);
		fseek(lista_enc,atual,0);
		fread(&a,sizeof(LISTA),1,lista_enc);
		aux = a.next;
		a.next=c.next_LISTA_ENC;
		c.num_LISTA_ENC--;
		c.next_LISTA_ENC=atual;
		if(antecessor >= 0)
		{
			fseek(lista_enc,antecessor,0);
			fread(&a,sizeof(LISTA),1,lista_enc);
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

	if(!(config=fopen(config_address,"w+b")))
		error_m("Error at file oppening");
	else
	if(!(horarios=fopen(address,"w+b")))
		error_m("Error at file allocation");
	else
	{
		fread(&c,sizeof(configuration),1,config);
		scroll=(c.next_HORARIO==-1)?c.num_HORARIO:c.next_HORARIO;
		fseek(horarios,scroll,0);
		fread(&a,sizeof(HORARIO),1,horarios);
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

	if(!(config=fopen(config_address,"w+b")))
		error_m("Error at file oppening");
	else
	if(!(horarios=fopen(address,"w+b")))
		error_m("Error at file allocation");
	else
	{
		fread(&c,sizeof(configuration),1,config);
		a.data[0]=c.next_HORARIO;
		c.next_HORARIO=scroll;
		c.num_HORARIO--;
		fseek(horarios,scroll,0);
		fwrite(&c,sizeof(configuration),1,config);
		fwrite(&a,sizeof(HORARIO),1,horarios);
		fclose(horarios);
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
