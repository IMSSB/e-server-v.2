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
//Declarar escopos
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
char* dir_builder(int account_number,char*dir,char* file)
{
	return strcat(strcat(dir,get_address(account_number,dir)),file);
}

//Lista de Endereços Global
void create_address_list(char *dir)
{
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
			sscanf(ads.address,"%d",s.next_address);//Atualizando o próximo a ser subscrito
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
//Configuração
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
void create_config(int account_address,char *dir)
{
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
		new.next_message=0;
		new.next_subject=0;

		fwrite(&new,sizeof(configuration),1,config);
		fclose(config);
	}
	free(address);
	return;
}
//Lista de Textos
void create_text_list(int account_address,char *dir)
{
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
{
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
		fread(&msg,sizeof(messages),1,text_list);
		sscanf(msg.mail,"%d",c.next_message);
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
{
	char *list_address=dir_builder(account_address,dir,"/text_list.bin"),*config_address = dir_builder(account_address,dir,"/config.bin");
	FILE *text_list,*config;
	messages msg;
	configuration c;

	if(!(config=fopen(config_address,"w+b")))
	{
		error_m("Error at file oppening");
	}
	else
	if(!(text_list=fopen(list_address,"w+b")))
	{
		error_m("Error at file oppening");
	}
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
{
	char *address=dir_builder(account_address,dir,"/text_list.bin");
	char *t=(char*)malloc(sizeof(char)*300);
	messages read;
	FILE *texts;

	if(!(texts=fopen(address,"rb")))
	{
		error_m("Eror at file oppening");
	}
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


//Lista de Assuntos
void create_subject_list(int account_address,char* dir)
{
	char *subjects_address=dir_builder(account_address,dir,"/subject_list.bin");//fazer uma função pra isso!!!
	FILE *subject_list;
	subjects sub;

	if(!(subject_list=fopen(subjects_address,"wb")))
	{
		error_m("Error at file allocation");
	}
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
{
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
		fread(&s,sizeof(subjects),1,subject_list);
		if(c.next_subject != -1)
			sscanf(s.subject,"%d",c.next_subject);
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
void remove_subject(account_address,char *dir,int scroll)
{
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
{	char *address=dir_builder(account_address,dir,"/subject_list.bin");
	FILE *subject_list;
	subjects s;
	if(!(subject_list=fopen(address,"w+b")))
	{
		error_m("Error at file oppening");
	}
	else
	{
		fseek(subject_list,scroll,0);
		fread(&s,sizeof(subjects),1,subject_list);
		fclose(subject_list);
	}
	free(address);
	return s.subject;
}
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
	int c;

		for(c=0;c<6;c++)
		{
			if(a.data[c] < b.data[c])
				return 1;
			if(a.data[c] > b.data[c])
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
