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
	//int dia,mes,ano,horas,minutos,segundos;
	int data[6];//data ordenada por relevancia (ano,mes,dia,hora,minuto,segundo)

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
	char *dir_ad=strcat(dir,"/addresses.bin");

	if(!(new=fopen(dir_ad,"wb")))
		error_m("Error at file allocation");
	else
	{	ad.address[0]=-1;
		fwrite(&ad,sizeof(addresses),1,new);
		fclose(new);
	}

	return;
}

void add_address(char *new)
{
	FILE *set,*ad;
	char *dir_s=strcat(dir,"/settings.bin"),*dir_ad=strcat(dir,"/addresses.bin");
	settings s;
	addresses ads;
	int scroll;

	if(!(set=fopen(dir_s,"w+b")))
		error_m("error at file oppening");
	if(!(ad=fopen(dir_ad,"w+b")))
		error_m("error at file oppening");

	{
		fread(&s,sizeof(settings),1,set);
		sprintf(ads.address,"%s",new);//guardando novo endereço
		scroll=(s.next_address == -1)?s.num_addresses:s.next_address;
		fseek(ad,scroll,0);
		fread(&ads,sizeof(addresses),1,ad);
		if(s.next_address!=-1)//caso haja blocos não utilizados a serem subscritos
			s.next_address=ads.address[0];//definir em remoção a possibilidade disso
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

void remove_address(int scroll)
{
	FILE *set,*ad;
	char *dir_s=strcat(dir,"/settings.bin"),*dir_ad=strcat(dir,"/addresses.bin");
	settings s;
	addresses ads;


	if(!(set=fopen(dir_s,"w+b")))
		error_m("error at file oppening");
	if(!(ad=fopen(dir_ad,"w+b")))
		error_m("error at file oppening");
	{
		fread(&s,sizeof(settings),1,set);
		fseek(ad,scroll,0);
		fread(&ads,sizeof(addresses),1,ad);
		ads.address[0]=s.next_address;
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

char* get_address(int scroll)
{	char* address = (char*)malloc(sizeof(char)*64),*dir_ad=strcat(dir,"/addresses.bin");
	FILE *ad;
	addresses ads;


	if(!(ad=fopen(dir_ad,"w+b")))
		error_m("error at file oppening");
	{
		fseek(ad,scroll,0);
		fread(&ads,sizeof(addresses),1,ad);
		sprintf(address,"%s",ads.address);
		fclose(ad);
	}
	return address;
}

void setup(char *dir)
{
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
	free(address);
	return;
}
//Lista de Textos


//Lista de Assuntos


//Lista de Emails

//Funções de comparação de horário
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
		if(a.data[c] > b.data[c])
			return 1;
		if(a.data[c] < b.data[c])
			return 0;
	}
	return 0;//se chegar aqui necessariamente é igual
}
int horario_menor(HORARIO a,HORARIO b)
{
	int c;

	for(c=0;c<6;c++)
	{
		if(a.data[c] < b.data[c])
			return 1;
		if(a.data[c] > b.data[c])
			return 0;
	}
	return 0;//se chegar aqui necessariamente é igual
}
int horario_menor_igual(HORARIO a,HORARIO b)
{
	return(horario_menor(a,b) || horario_igual(a,b));
}
int horario_maior_igual(HORARIO a,HORARIO b)
{
	return(horario_maior(a,b) || horario_igual(a,b));
}

#endif /* FUNCTIONS_2_STRUCT_H_ */
