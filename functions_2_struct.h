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

char *dir;
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
	int next_message;
	int next_subject;
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
	int dia,mes,ano,horas,minutos,segundos;

}HORARIO;

typedef struct
{
	int remetente;
	int destinatario;
	int assunto;
	int  MSG;
	HORARIO data;

}HISTORICO;

typedef struct
{
	int remetente;
	int destinatario;
	int assunto;
	int MSG;
	HORARIO data;
	int historico[x];

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
	int chaves[k-1];
	int filhos[k];
	int pai;

}NODO;//B, B# ou B+? já passou da hora!!

void error_m(char *errormessage)
{ /* Função para facilitar exibição de mensagens de erro */
    printf("\n%s",errormessage);
    pause;
    exit(1);
}

//Lista de Endereços Global
void create_address_list(void)
{
	FILE *new;
	addresses ad;

	if(!(new=fopen(dir,"wb")))
		error_m("Error at file allocation");
	else
	{	ad.address[0]=-1;
		fwrite(&ad,sizeof(addresses),1,new);
		fclose(new);
	}

	return;
}

void add_address()
{

}

void remove_address()
{

}

char* get_address(int account_address)
{	char* address;

	return address;
}

void setup(char *dir)
{
	FILE *set;
	settings new;
	char *name = strcat(dir,"/settings.bin");
	if(!(set=fopen(name,"wb")))
		error_m("Error at file allocation");
	else
	{
		sprintf(new.dir,"%s",dir);
		new.num_addresses=0;
		new.next_address=0;
		fclose(set);
	}
}
void create_config(int account_address)
{	char *address;
	FILE *config;
	configuration new;


	address = strcat(dir,get_address(account_address));
	address = strcat(address,"/config.bin");

	if(!(config=fopen(address,"wb")))
		error_m("Error at file allocation");
	else
	{
		new.account_address=account_address;
		new.num_messages=0;
		new.num_subjects=0;
		new.next_message=0;
		new.next_subject=0;

		fwrite(&new,sizeof(configuration),1,config);
		fclose(config);
	}

	return;
}
//Lista de Textos


//Lista de Assuntos


//Lista de Emails



#endif /* FUNCTIONS_2_STRUCT_H_ */
