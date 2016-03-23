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
#include <sys/stat.h>
#ifndef __linux__ // Verifica se o sistema atual não é Linux
	#include <direct.h> 	//	Inclui biblioteca específica do Windows se não for
#endif

#define cls system("CLS || clear");
#define pause printf("\nDigite algo para continuar"); getchar();
#define spc printf("  |");
#define spc_m printf("              ");
#define breakline printf("\n");
#define line breakline; printf("____________________________________________________________"); breakline;
#define x 10	// Limite de histórico
#define k 6	// Ordem - Use número par - Número de Chaves será k-1 e o número de filhos será k
#define min_chaves ((k/2)-1)
#define windus "C:/Users/Ruan/Desktop/T/"
#define ubuntus "/home/ricardo/e-server"


// 	Temos que voltar o ponteiro dos arquivos depois das operações de leitura

typedef struct
{
	int num_addresses;
	int next_address;
	int anum_address;
	char dir[200];
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
	int anum_messages;
	int anum_subjects;
	int anum_emails;
	int anum_LISTA_ENC;
	int anum_HORARIO;
	int anum_PALAVRA;

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
	//int dia,mês,ano,horas,minutos,segundos;
	int data[6];//data ordenada por relevância (ano,mês,dia,hora,minuto,segundo)

}HORARIO;

typedef struct
{
	int remetente;
	int destinatario;
	int assunto;
	int MSG;
	int data;
	int historico; 		// PARA RICARDO E RUAN DO FUTURO: A ESTRUTURA RETRO ALUDIDA
						// REFERENCIARÁ UM SUBNODO, E ASSIM EM DIANTE, ENCADEANDO. COM CADEADOS.
}SUB_NODO;

typedef struct
{
       char user[64];
       char password[64];
       /*int inbox; //Todos vão conter o valor no qual está no vetor o NODO que corresponde
       int outbox;
       int read;
       int trash;
       int sent;*/

}CONTA;//Conta deve ser uma arvore pois seria totalmente incompreensível
//usar métodos tão sofisticados de busca pra tudo exceto pra achar as contas

typedef struct
{
	int chaves[k-1]; 	// Campo que é escolhido convenientemente ao funcionamento do sistema. (messages, subjects, HORARIO
	int addresses[k-1];	// Apontam para Listas de SUB_NODO
	int filhos[k]; 		// NODOS
	int pai;
	char num_chaves;	// Escolha do tipo char devido ao tamanho máximo escalado para o programa, 64 filhos e 63 chaves.
	char ne_folha;	// Número de Filhos. Também pode indicar se o NODO é uma folha ou não, 0 = folha.

}NODO;

typedef struct
{
	int raiz;
	int num_NODOS;
	int anum_NODOS;
	int next_NODO;
	int num_SUB_NODOS;

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

typedef struct
{
	FILE *addresses;
	FILE *config;
	FILE *email_list;
	FILE *horario_list;
	FILE *subject_list;
	FILE *text_list;
	FILE *word_list;
	FILE *lista_enc;
	//Árvores Gerais
	FILE *tree_HORARIO;
	FILE *tree_messages;
	FILE *tree_PALAVRA;
	FILE *tree_subjects;
	FILE *tree_L_HORARIO;
	FILE *tree_L_messages;
	FILE *tree_L_PALAVRA;
	FILE *tree_L_subjects;
	//Caixas de Emails
	//Inbox
	FILE *inbox_tree_HORARIO;
	FILE *inbox_tree_messages;
	FILE *inbox_tree_PALAVRA;
	FILE *inbox_tree_subjects;
	FILE *inbox_tree_L_HORARIO;
	FILE *inbox_tree_L_messages;
	FILE *inbox_tree_L_PALAVRA;
	FILE *inbox_tree_L_subjects;
	//Outbox
	FILE *outbox_tree_HORARIO;
	FILE *outbox_tree_messages;
	FILE *outbox_tree_PALAVRA;
	FILE *outbox_tree_subjects;
	FILE *outbox_tree_L_HORARIO;
	FILE *outbox_tree_L_messages;
	FILE *outbox_tree_L_PALAVRA;
	FILE *outbox_tree_L_subjects;
	//Read
	FILE *read_tree_HORARIO;
	FILE *read_tree_messages;
	FILE *read_tree_PALAVRA;
	FILE *read_tree_subjects;
	FILE *read_tree_L_HORARIO;
	FILE *read_tree_L_messages;
	FILE *read_tree_L_PALAVRA;
	FILE *read_tree_L_subjects;
	//Sent
	FILE *sent_tree_HORARIO;
	FILE *sent_tree_messages;
	FILE *sent_tree_PALAVRA;
	FILE *sent_tree_subjects;
	FILE *sent_tree_L_HORARIO;
	FILE *sent_tree_L_messages;
	FILE *sent_tree_L_PALAVRA;
	FILE *sent_tree_L_subjects;
	//Trash
	FILE *trash_tree_HORARIO;
	FILE *trash_tree_messages;
	FILE *trash_tree_PALAVRA;
	FILE *trash_tree_subjects;
	FILE *trash_tree_L_HORARIO;
	FILE *trash_tree_L_messages;
	FILE *trash_tree_L_PALAVRA;
	FILE *trash_tree_L_subjects;

}ARQUIVOS;

//ESCOPO DAS FUNÇÕES
char* detecta_os();
void ler_end(char *er);
void print_nodo(NODO nodo);
void prin_arvoreb(ARVOREB avb);
void error_m(char *errormessage);
void make_dir(char *aux);
char* dir_builder(char*dir,int account_number,char* file);
char* filepath_gen(char *dir, char *file);
char* merge_string(char *string1, char *string2);
void create_address_list(char *dir);
int add_address(char *dir,char *user,char *password);
void remove_address(char *dir,int pos);
char* get_address(char *dir,int account_number);
void setup_server(char *dir);
void create_config(char *dir,int account_address);
void create_text_list(char *dir,int account_address);
int add_text(FILE *config,FILE *text_list,char *new);
void remove_text(FILE *config,FILE *text_list,int scroll);
char* get_text(FILE *config,FILE *text_list, int scroll);
void create_subject_list(char *dir,int account_address);
int add_subject(FILE *config, FILE *subject_list,char *new);
void remove_subject(char *dir,int account_address,int scroll);
char* get_subject(char *dir,int account_address,int scroll);
void create_email_list(char *dir,int account_address);
int add_email(char *dir,int account_address,int remetente,int destinatario, int assunto, int MSG, int data, int historico);
void remove_email(char *dir,int account_address,int scroll);
void create_LISTA_ENC(char *dir,int account_address);
int add_LISTA_ENC(char *dir,int account_address,int ultimo,int novo);
void remove_LISTA_ENC(char *dir,int account_address, int anterior,int atual);//A chamada desta função deve ser feita dentro da arvore onde é posível ter essas informações
void create_horario_list(char *dir,int account_address);
int add_horario(char *dir,int account_address, HORARIO novo);
void remove_horario(char *dir,int account_address, int scroll);
void create_word_list(char *dir,int account_address);
int add_word(char *dir,int account_address, char *new);
void remove_word(char* dir,int account_address, int scroll);
void create_tree_type(char *dir,int account_address, char *folder, char *type);
void split_tree(FILE *tree,FILE *nodo_list,int pai,int scroll);
fpos_t predescessor(FILE *tree,FILE *nodo_list,int nodo,int key);
int merge_nodo(FILE *tree,FILE *nodo_list,int pai,int scroll);
void add_key_tree(char *dir,int account_address,char *folder,char *type,int key,int SUB_NODO);
void remove_key_tree(char *dir,int account_address,char *folder,char *type,int key);
int busca_SUB_NODO_tree(char *dir,int account_address,char *folder,char *type,int key);
void add_SUB_NODO_tree(char *dir,int account_address,char *folder,char *type,int key,int SUB_NODO);
void remove_SUB_NODO_tree(char *dir,int account_address, char *folder, char *type,int key,int SUB_NODO);
int compara_infos(char *dir,int account_address,char *type,int a,int b);
int horario_igual(HORARIO a,HORARIO b);
int horario_maior(HORARIO a,HORARIO b);
int horario_menor(HORARIO a,HORARIO b);
int horario_menor_igual(HORARIO a,HORARIO b);
int horario_maior_igual(HORARIO a,HORARIO b);

// FUNÇÕES DE TESTE INTERNO
void ler_end(char *er)
{
	printf("TESTE1.x.1: Lendo endereço 0\n");pause;
			printf("Endereço lido: %s\n",get_address(er,0));
	printf("TESTE1.x.2: Lendo endereço 1\n");pause;
		printf("Endereço lido: %s\n",get_address(er,1));
}

char* detecta_os()
{
	#ifdef __linux__
		return ubuntus;
	#else
		return windus;
	#endif
}

void print_nodo(NODO nodo){
	printf("\nchave[0] = %d\n", nodo.chaves[0]);
	printf("chave[1] = %d\n", nodo.chaves[1]);
	printf("chave[2] = %d\n", nodo.chaves[2]);
	printf("chave[3] = %d\n", nodo.chaves[3]);
	printf("chave[4] = %d\n", nodo.chaves[4]);
	printf("addresses[0] = %d\n", nodo.addresses[0]);
	printf("addresses[1] = %d\n", nodo.addresses[1]);
	printf("addresses[2] = %d\n", nodo.addresses[2]);
	printf("addresses[3] = %d\n", nodo.addresses[3]);
	printf("addresses[4] = %d\n", nodo.addresses[4]);
	printf("\nfilho[0] = %d\n", nodo.filhos[0]);
	printf("filho[1] = %d\n", nodo.filhos[1]);
	printf("filho[2] = %d\n", nodo.filhos[2]);
	printf("filho[3] = %d\n", nodo.filhos[3]);
	printf("filho[4] = %d\n", nodo.filhos[4]);
	breakline;
	printf("pai = %d\n", nodo.pai);
	printf("num_chaves = %d\n", nodo.num_chaves);
	printf("não é folha = %d\n", nodo.ne_folha);
}
void print_arvoreb(ARVOREB avb)
{
	printf("AVB - raiz = %d\n", avb.raiz);
	printf("AVB - num_NODOS = %d\n", avb.num_NODOS);
	printf("AVB - anum_NODOS = %d\n", avb.anum_NODOS);
	printf("AVB - num_SUB_NODOS = %d\n", avb.num_SUB_NODOS);
	printf("AVB - next_NODO = %d\n", avb.next_NODO);
}
//Função para resolver ambiguidade de modos entre sistemas operacionais
void make_dir(char *aux)
{
	#ifdef __linux
		mkdir(aux, S_IRWXU);
	#else
		_mkdir(aux);
	#endif
}
// 	FUNÇÕES ÚTEIS
void error_m(char *errormessage)
{ 	/* Função para facilitar exibição de mensagens de erro */
    printf("\n%s",errormessage);
    pause;
    exit(1);
}


char* filepath_gen(char *dir, char *file)
{ 	// 	Função para gerar ponteiro para char com o diretório
	char *path=(char *) malloc(sizeof(char)*250);	//	Alocando espaço para ponteiro que será retornado
	sprintf(path, "%s",dir);	//	Colocando diretório fornecido no espaço alocado
	strcat(path,"/");			//	Concatenando com uma barra
	strcat(path,file);			//	Concatenando com o nome do arquivo
	return path;				//	Retornando o ponteiro
}
// Não se pode usar strcat em string constante, perdi um tempinho com isso.

char* dir_builder(char*dir,int account_number,char* file)
{	//	Função para gerar o caminho do arquivo
	char *ad = get_address(dir,account_number), *r;

	r = strcat(strcat(strcat(filepath_gen(dir,""),ad),"/"),file);
	printf("\nAd = %s \n r= %s",ad,r);
	free(ad);
	return r;
}
char* ler(char modo)
{
	char *lido=NULL;
	int c = 0;
	#ifdef __linux__
		__fpurge(stdin);
	#else
		fflush(stdin);
	#endif
	do
	{
		lido = (char *) realloc(lido,sizeof(char)*(c+1));
		if (!lido)
			error_m("Erro ao ler");
		lido[c] = getchar();
		c++;
	}
	while (lido[c-1]-modo);
	lido[c-1] = '\0';

	return lido;
}

char* merge_string(char *string1, char *string2)
{
	char *merged = (char *) malloc(sizeof(char)*(strlen(string1)+strlen(string2)+1));
	sprintf(merged,"%s",string1);
	strcat(merged,string2);
	return merged;
}

//LISTA DE ENDEREÇOS GLOBAL
void create_address_list(char *dir) //
{	// Função para criar o arquivo da Lista de Endereços
	FILE *new;			//	Declarando ponteiro para arquivo que será criado
	CONTA ad;		//	Declarando variável addresses para ser escrita no arquivo
	char *dir_ad=filepath_gen(dir,"addresses.bin");		//	Gerando caminho para o arquivo

	if(!(new=fopen(dir_ad,"wb")))	//	Criando arquivo
		error_m("Error at file allocation");	//	Mensagem de erro se o arquivo não conseguir ser criado/subscrito
	else
	{
		sprintf(&(ad.user[0]),"%d",-1);	//	Colocando "-1" na variável para indicar que ainda não há nenhum endereço
		fwrite(&ad,sizeof(addresses),1,new);	//	Escrevendo no arquivo
		fclose(new);	// 	Fechando arquivo
	}

	return;
}

int add_address(char *dir,char *user,char *password)
{	//	Função para adicionar um endereço na Lista de Endereços
	FILE *set,*ad;
	char *dir_ad=filepath_gen(dir,"addresses.bin");
	settings s;
	CONTA ads;
	int scroll;		//	Variáveis auxiliares
	fpos_t c;
	if(!(set=fopen("settings.bin","r+b")))				// Confirmando abertura dos arquivos de settings e addresses
		error_m("Error at file opening");
	if(!(ad=fopen(dir_ad,"r+b")))
		error_m("Error at file opening");

	fread(&s,sizeof(settings),1,set);	//	Lendo arquivo de configurações e armazenando na variável s
	rewind(set);						//	Colocando a posição do fluxo de dados no inicio
	scroll=(s.next_address == -1)?s.num_addresses:s.next_address;	//	Definindo a posição em que o novo endereço será salvo no arquivo addresses.bin
	printf("NEXT: %d\nNUM AD: %d",s.next_address,s.num_addresses);
	fseek(ad,scroll*sizeof(CONTA),SEEK_SET);				//	Deslocando a posição do buffer no arquivo addresses.bin
	if(s.next_address!=-1)										//	caso haja blocos não utilizados a serem subscritos
	{
		fgetpos(ad,&c);								//	Guardando a posição atual do fluxo de dados
		fread(&ads,sizeof(CONTA),1,ad);			//	Lendo arquivo de endereços e armazenando na variável ad
		sscanf(ads.user,"%d",&(s.next_address));	//	Atualizando o próximo a ser subscrito
		fsetpos(ad,&c);								// 	Retornando a posição do fluxo de dados para a salva anteriormente
	}
	else
		s.anum_address++;
	sprintf(ads.user,"%s",user);			//	Guardando usuário
	sprintf(ads.password,"%s",user);			//	Guardando senha
	s.num_addresses++;						//	Incrementando o número de endereços
	fwrite(&s,sizeof(settings),1,set);		//	Escrevendo alterações feitas nos arquivos
	fwrite(&ads,sizeof(CONTA),1,ad);
	fclose(set);							// Fechando arquivos
	fclose(ad);

	free(dir_ad);	// Liberando ponteiros

	return scroll;
}

void remove_address(char *dir,int pos)
{	//	Função para remover um endereço da Lista de Endereços
	FILE *set,*ad;
	char *dir_ad=filepath_gen(dir,"addresses.bin");
	settings s;
	CONTA ads;
	fpos_t c;

	if(!(set=fopen("settings.bin","r+b")))
		error_m("Error at file opening");
	fread(&s,sizeof(settings),1,set);
	rewind(set);
	if (pos < s.anum_address && pos >= 0)
	{
		if(!(ad=fopen(dir_ad,"r+b")))
		error_m("Error at file opening");

		fseek(ad,pos*sizeof(CONTA),SEEK_SET);
		fgetpos(ad,&c);
		fread(&ads,sizeof(CONTA),1,ad);
		fsetpos(ad,&c);
		sprintf(&(ads.user[0]),"%d", s.next_address);
		s.next_address=pos;
		s.num_addresses--;
		fwrite(&s,sizeof(settings),1,set);//escrevendo alterações feitas
		fwrite(&ads,sizeof(CONTA),1,ad);
		fclose(ad);
	}
	fclose(set);
	free(dir_ad);

	return;
}

char* get_address(char *dir,int account_number)
{	//	Função que retorna um endereço da Lista de Endereços
	char* address = (char*)malloc(sizeof(char)*64),*dir_ad=filepath_gen(dir,"addresses.bin");
	FILE *ad;
	CONTA ads;

	if(!(ad=fopen(dir_ad,"rb")))
		error_m("Error at file opening");

	fseek(ad,account_number*sizeof(CONTA),SEEK_SET);
	fread(&ads,sizeof(CONTA),1,ad);
	sprintf(address,"%s",ads.user);
	fclose(ad);

	return address;
}

//CONFIGURAÇÃO
void setup_server(char *dir)
{	//	Função para configuração geral do Servidor
	FILE *set;
	settings new;

	if(!(set=fopen("settings.bin","wb")))
		error_m("Error at file allocation");
	else
	{
		sprintf(new.dir,"%s",dir);
		new.num_addresses=0;
		new.next_address=0;
		new.anum_address=0;
		fwrite(&new,sizeof(settings),1,set);
		fclose(set);
	}

	return;
}

void create_config(char *dir,int account_address)
{	// Função para criar o arquivo de Configuração do Usuário
	char *address = dir_builder(dir,account_address,"config.bin"), *ac, *aux;
	FILE *config;
	configuration new;

	ac = get_address(dir, account_address);
	aux = filepath_gen(dir,ac);

	make_dir(aux);

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
		new.num_PALAVRA=0;

		new.next_message=0;
		new.next_subject=0;
		new.next_email=0;
		new.next_LISTA_ENC=0;
		new.next_HORARIO=0;
		new.next_PALAVRA=0;

		new.anum_messages=0;
		new.anum_subjects=0;
		new.anum_emails=0;
		new.anum_LISTA_ENC=0;
		new.anum_HORARIO=0;
		new.anum_PALAVRA=0;

		fwrite(&new,sizeof(configuration),1,config);
		fclose(config);
	}
	free(ac);
	free(aux);
	free(address);

	return;
}

//LISTA DE TEXTOS
void create_text_list(char *dir,int account_address)
{	//	Função para criar o arquivo da Lista de Textos do usuário
	char *address=dir_builder(dir,account_address,"text_list.bin");
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

int add_text(FILE *config,FILE *text_list,char *new)
{	//	Função para adicionar um texto à Lista de Textos
	messages msg;
	configuration c;
	int scroll;
	fpos_t p;

	rewind(config);
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
	else
		c.anum_messages++;
	sprintf(msg.mail,"%s",new);
	c.num_messages++;
	fwrite(&c,sizeof(configuration),1,config);
	fwrite(&msg,sizeof(messages),1,text_list);

	return scroll;
}

void remove_text(FILE *config,FILE *text_list,int pos)//precisamos validar as remoções depois
{	//	Função para remover um texto da Lista de Textos
	messages msg;
	configuration c;

	rewind(config);
	fread(&c,sizeof(configuration),1,config);
	rewind(config);
	if (pos < c.anum_messages && pos >=0)
	{
		sprintf(msg.mail,"%d",c.next_message);

		c.num_messages--;
		c.next_message=pos;
		fseek(text_list,pos*sizeof(messages),SEEK_SET);
		fwrite(&msg,sizeof(messages),1,text_list);
		fwrite(&c,sizeof(configuration),1,config);
	}

	return;
}

char* get_text(FILE *config,FILE *text_list, int pos)
{	//	Função que retorna um texto da Lista de Textos
	char *t=(char*)malloc(sizeof(char)*300);
	messages read;

	fseek(text_list,pos*sizeof(messages),SEEK_SET);
	fread(&read,sizeof(messages),1,text_list);

	sprintf(t,"%s",read.mail);

	return t;
}


//LISTA DE ASSUNTOS
void create_subject_list(char* dir,int account_address)
{	// Função para criar o arquivo da Lista de Assuntos do usuário
	char *subjects_address=dir_builder(dir,account_address,"subject_list.bin");//fazer uma função pra isso!!!
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

int add_subject(FILE *config, FILE *subject_list,char *new)
{	// Função para adicionar um assunto à Lista de Assuntos
	configuration c;
	subjects s;
	int pos;
	fpos_t p;

	fread(&c,sizeof(configuration),1,config);
	rewind(config);
	pos=(c.next_subject==-1)?c.num_subjects:c.next_subject;
	fseek(subject_list,pos*sizeof(subjects),SEEK_SET);
	if(c.next_subject != -1)
	{
		fgetpos(subject_list,&p);
		fread(&s,sizeof(subjects),1,subject_list);
		sscanf(s.subject,"%d",&(c.next_subject));
		fsetpos(subject_list,&p);
	}
	else
		c.anum_subjects++;
	sprintf(s.subject,"%s",new);
	c.num_subjects++;
	fwrite(&c,sizeof(configuration),1,config);
	fwrite(&s,sizeof(subjects),1,subject_list);

	return pos;
}

void remove_subject(char* dir,int account_address,int scroll)
{	// Função para remover um assunto da Lista de Assuntos
	char *address=dir_builder(dir,account_address,"subject_list.bin"),*config_address=dir_builder(dir,account_address,"/config.bin");
	FILE *subject_list,*config;
	configuration c;
	subjects s;

	if(!(config=fopen(config_address,"r+b")))
		error_m("Error at file opening");
	fread(&c,sizeof(configuration),1,config);
	rewind(config);
	if (scroll < c.anum_subjects && scroll >=0)
	{
		if(!(subject_list=fopen(address,"r+b")))
		error_m("Error at file opening");

		sprintf(s.subject,"%d",c.next_subject);
		c.num_subjects--;
		c.next_subject=scroll;
		fseek(subject_list,scroll*sizeof(subjects),SEEK_SET);
		fwrite(&s,sizeof(subjects),1,subject_list);
		fwrite(&c,sizeof(configuration),1,config);
		fclose(subject_list);
	}
	fclose(config);
	free(address);
	free(config_address);

	return;
}

char* get_subject(char* dir,int account_address,int scroll)
{	//	Função que retorna um assunto da Lista de Assuntos dada sua posição (scroll)
	char *address=dir_builder(dir,account_address,"subject_list.bin");
	FILE *subject_list;
	char *sub;
	subjects s;

	if(!(subject_list=fopen(address,"rb")))
		error_m("Error at file opening");
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
void create_email_list(char* dir,int account_address)
{	// Função para criar o arquivo da Lista de Emails
	char *address = dir_builder(dir,account_address,"email_list.bin");
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

int add_email(char* dir,int account_address,int remetente,int destinatario, int assunto, int MSG, int data, int historico)
{ 	//	Função para adicionar um email na Lista de Emails
	char *address=dir_builder(dir,account_address,"email_list.bin"),*config_address=dir_builder(dir,account_address,"/config.bin");
	FILE *email_list, *config; 	// 	Arquivos que serão abertos
	configuration c; 			//	Manipulação da configuração
	SUB_NODO e; 				//	Manipulação de email
	int scroll;					// 	Variável para deslocamento
	fpos_t p;

	if (!(email_list=fopen(address,"r+b"))) 	// 	Abrindo o arquivo da Lista de Emails
		error_m("Error at file opening"); 		// 	Mensagem de erro
	else
	if (!(config=fopen(config_address,"r+b"))) 	// 	Abrindo o arquivo de Configuração da Conta
		error_m("Error at file opening");		// 	Mensagem de erro
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
		else
			c.anum_emails++;
		c.num_emails++;											//
		e.remetente = remetente;								//
		e.destinatario = destinatario;							//
		e.assunto = assunto;									//
		e.MSG = MSG;											//
		e.data = data;
		e.historico = historico;								//
		fwrite(&c,sizeof(configuration),1,config);				//
		fwrite(&e,sizeof(SUB_NODO),1,email_list);				//
		fclose(config);											//
		fclose(email_list);										//
	}
	free(address);			//
	free(config_address);	//

	return scroll;
}

void remove_email(char* dir,int account_address,int scroll)
{	//	Função para removar email da Lista de Emails dada sua posição (scroll)
	char *address=dir_builder(dir,account_address,"email_list.bin"),*config_address=dir_builder(dir,account_address,"/config.bin");
	FILE *email_list, *config; 	// 	Arquivos que serão abertos
	configuration c; 			//	Manipulação da configuração
	SUB_NODO e; 				//	Manipulação de email
	fpos_t p;

	if (!(config=fopen(config_address,"r+b"))) 	// 	Abrindo o arquivo da Lista de Emails
		error_m("Error at file opening"); 		// 	Mensagem de erro
	fread(&c,sizeof(configuration),1,config);				//
	rewind(config);
	if (scroll < c.anum_emails && scroll >=0 )
	{
		if (!(email_list=fopen(address,"r+b"))) 	// 	Abrindo o arquivo de Configuração da Conta
			error_m("Error at file opening");		// 	Mensagem de erro

		fseek(email_list,scroll*sizeof(SUB_NODO),SEEK_SET);								//
		fgetpos(email_list,&p);
		fread(&e,sizeof(SUB_NODO),1,email_list);				//
		fsetpos(email_list,&p);
		e.remetente = c.next_email;								//
		c.next_email = scroll;									//
		c.num_emails--;											//
		fwrite(&c,sizeof(configuration),1,config);				//
		fwrite(&e,sizeof(SUB_NODO),1,email_list);				//
		fclose(email_list);										//
	}
	fclose(config);			//
	free(address);			//
	free(config_address);	//

	return;
}

//LISTA DE LISTAS ENCADEADAS DE EMAILS
void create_LISTA_ENC(char *dir,int account_address)
{	// Função para criar o arquivo da Lista de Listas Encadeadas de Emails
	char* address = dir_builder(dir,account_address,"lista_enc.bin");
	FILE *lista_enc;
	LISTA l;

	if(!(lista_enc=fopen(address,"wb")))
		error_m("Error at file allocation");
	else
	{
		l.next=l.address=-1;
		fwrite(&l,sizeof(LISTA),1,lista_enc);
		fclose(lista_enc);
	}
	free(address);

	return;
}

int add_LISTA_ENC(char *dir, int account_address, int antecessor,int novo)
{	//	Função para adicionar lista à Lista de Listas Encadeadas de Emails
	char   *address = dir_builder(dir,account_address,"lista_enc.bin"),*config_address=dir_builder(dir,account_address,"/config.bin");
	FILE *lista_enc,*config;
	LISTA a;
	configuration c;
	int scroll,aux=-1;
	fpos_t p;
	// FUTURO: FAZER SUPOSIÇÃO DA POSIÇÃO NA LISTA QUANDO não houver antecessor
	if(!(config=fopen(config_address,"r+b")))
		error_m("Error at file opening");
	else
	if(!(lista_enc=fopen(address,"r+b")))
		error_m("Error at file opening");
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
			fwrite(&a,sizeof(LISTA),1,lista_enc);
		}
		fseek(lista_enc,scroll*sizeof(LISTA),SEEK_SET);
		fgetpos(lista_enc,&p);
		fread(&a,sizeof(LISTA),1,lista_enc);
		fsetpos(lista_enc,&p);
		if(c.next_LISTA_ENC!=-1)
			c.next_LISTA_ENC=a.next;
		else
			c.anum_LISTA_ENC++;
		c.num_LISTA_ENC++;
		a.next=aux;
		a.address = novo;
		fwrite(&a,sizeof(LISTA),1,lista_enc);
		fwrite(&c,sizeof(configuration),1,config);
		fclose(lista_enc);
		fclose(config);
	}
	free(address);
	free(config_address);

	return (scroll);
}

void remove_LISTA_ENC(char *dir,int account_address, int antecessor,int atual)
{	//	Função para remover lista da Lista de Listas Encadeadas de Emails
	char   *address = dir_builder(dir,account_address,"/lista_enc.bin"),*config_address=dir_builder(dir,account_address,"/config.bin");
	FILE *lista_enc,*config;
	LISTA a;
	configuration c;
	int aux;
	fpos_t p;

	if(!(config=fopen(config_address,"r+b")))
		error_m("Error at file opening");
	if(atual < c.anum_LISTA_ENC && atual >= 0)
	{
		if(!(lista_enc=fopen(address,"r+b")))
			error_m("Error at file opening");

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
void create_horario_list(char *dir,int account_address)
{	// Função para criar arquivo da Lista de Horários
	char *address = dir_builder(dir,account_address,"horario_list.bin");
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

int add_horario(char *dir,int account_address, HORARIO novo)
{	// Função para adicionar horário à Lista de Horários
	char *address = dir_builder(dir,account_address,"horario_list.bin"),*config_address=dir_builder(dir,account_address,"config.bin");
	FILE *horarios,*config;
	HORARIO a;
	configuration c;
	int scroll,cont;
	fpos_t p;

	if(!(config=fopen(config_address,"r+b")))
		error_m("Error at file opening");
	else
	if(!(horarios=fopen(address,"r+b")))
		error_m("Error at file opening");
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
		else
			c.anum_HORARIO++;
		c.num_HORARIO++;
		for(cont=0;cont<6;cont++)
			a.data[cont]=novo.data[cont];
		fwrite(&c,sizeof(configuration),1,config);
		fwrite(&a,sizeof(HORARIO),1,horarios);
		fclose(horarios);
		fclose(config);
	}
	free(address);
	free(config_address);

	return scroll;
}

void remove_horario(char *dir,int account_address, int scroll)
{	// Função para remover horário da Lista de Horários
	char *address = dir_builder(dir,account_address,"horario_list.bin"),*config_address=dir_builder(dir,account_address,"config.bin");
	FILE *horarios,*config;
	HORARIO a;
	configuration c;

	if(!(config=fopen(config_address,"r+b")))
		error_m("Error at file opening");
	fread(&c,sizeof(configuration),1,config);
	rewind(config);
	if(scroll < c.anum_HORARIO && scroll > 0)
	{
		if(!(horarios=fopen(address,"r+b")))
			error_m("Error at file opening");

		a.data[0]=c.next_HORARIO;
		c.next_HORARIO=scroll;
		c.num_HORARIO--;
		fseek(horarios,scroll*sizeof(HORARIO),SEEK_SET);
		fwrite(&c,sizeof(configuration),1,config);
		fwrite(&a,sizeof(HORARIO),1,horarios);
		fclose(horarios);
	}
	fclose(config);
	free(address);
	free(config_address);

	return;
}

//LISTA DE PALAVRAS
void create_word_list(char *dir,int account_address)
{	//	Função para criar o arquivo da Lista de Palavras
	char *address = dir_builder(dir,account_address,"word_list.bin");
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

int add_word(char *dir,int account_address, char *new)
{	// 	Função para adicionar palavra da Lista de Palavras
	char *address = dir_builder(dir,account_address,"word_list.bin"),*config_address=dir_builder(dir,account_address,"config.bin");
	FILE *word_list,*config;
	PALAVRA w;
	configuration c;
	int scroll;
	fpos_t p;

	if (!(word_list=fopen(address,"r+b")))
		error_m("Error at file opening");
	else
	if (!(config=fopen(config_address,"r+b")))
		error_m("Error at file opening");
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
		else
			c.anum_PALAVRA++;
		sprintf(w.key,"%s",new);
		c.num_PALAVRA++;
		fwrite(&w,sizeof(PALAVRA),1,word_list);
		fwrite(&c,sizeof(PALAVRA),1,config);
		fclose(word_list);
		fclose(config);
	}
	free(address);
	free(config_address);

	return scroll;
}

void remove_word(char *dir,int account_address, int scroll)
{	// 	Função para remover palavra da Lista de Palavras
	char *address = dir_builder(dir,account_address,"word_list.bin"),*config_address=dir_builder(dir,account_address,"config.bin");
	FILE *word_list,*config;
	PALAVRA w;
	configuration c;

	if (!(config=fopen(config_address,"r+b")))
		error_m("Error at file opening");
	fread(&c,sizeof(configuration),1,config);
	rewind(config);
	if (scroll < c.anum_PALAVRA && scroll >0)
	{
		if (!(word_list=fopen(address,"r+b")))
			error_m("Error at file opening");

		sprintf(w.key,"%d",c.next_PALAVRA);
		c.num_PALAVRA--;
		c.next_PALAVRA=scroll;
		fseek(word_list,scroll*sizeof(PALAVRA),SEEK_SET);
		fwrite(&w,sizeof(PALAVRA),1,word_list);
		fwrite(&c,sizeof(PALAVRA),1,config);
		fclose(word_list);
	}
	fclose(config);
	free(address);
	free(config_address);

	return;
}
//FUNÇÕES DA ARVORE
void create_tree_type(char *dir,int account_address,char *folder, char *type)
{
	char *address, *sub_address, *a, *sa;
	FILE *tree, *nodo_list;
	ARVOREB new;
	NODO nnew;

	a = merge_string(folder,merge_string("tree_",type));
	sa = merge_string(folder,merge_string("tree_L_",type));
	address = dir_builder(dir,account_address,a);
	sub_address	= dir_builder(dir,account_address,sa);
	printf("\nChegou aqui 1\n");
	if (!(tree = fopen(address,"wb")))
		error_m("Error at file allocation");
	if (!(nodo_list = fopen(sub_address,"wb")))
		error_m("Error at file allocation");
	new.num_NODOS=0;
	new.num_SUB_NODOS=0;
	new.raiz=-1;
	new.anum_NODOS=0;
	new.next_NODO=-1;
	nnew.num_chaves=0;
	nnew.ne_folha=0;
	nnew.pai=-1;

	printf("\nChegou aqui 2\n");
	fwrite(&nnew,sizeof(NODO),1,nodo_list);
	fwrite(&new,sizeof(ARVOREB),1,tree);

	fclose(tree);
	fclose(nodo_list);

	free(a);
	free(sa);
	free(address);
	free(sub_address);

	return;
}

void split_tree(FILE *tree,FILE *nodo_list,int pai,int scroll)
{	//	Função para dividir nós cheios durante inserção
	NODO pain,son1,son2;
	ARVOREB AVB;
	int c,felipe,smith;
	fpos_t p,f1,f2;

	rewind(tree);
	fread(&AVB,sizeof(ARVOREB),1,tree); 	//	Lê o arquivo de configuração da árvore
	if(pai+1)	// 	Caso o NODO a ser dividido tenha pai
	{
		printf("\n---> CASO TENHA PAI)\nscroll = %d\n",scroll);
		fseek(nodo_list,sizeof(NODO)*pai,SEEK_SET); // Procura a posição do pai no arquivo
		fgetpos(nodo_list,&p);	//	Guarda a posição de gravação do Pai
		fread(&pain,sizeof(NODO),1,nodo_list);	//
		fseek(nodo_list,sizeof(NODO)*pain.filhos[scroll],SEEK_SET);	// Procura posição do filho cheio, que vai ser o Filho 1
		fgetpos(nodo_list,&f1);	//	Guarda a posição de gravação do Filho 1
		fread(&son1,sizeof(NODO),1,nodo_list);
	}
	else	//	Se o NODO a ser dividido não tiver pai (Caso for raiz)
	{
		printf("\n---> CASO NÃO TENHA PAI)\n");
		fseek(nodo_list,sizeof(NODO)*AVB.raiz,SEEK_SET);
		fgetpos(nodo_list,&f1);	//	Guarda a posição de gravação do Filho 1
		fread(&son1,sizeof(NODO),1,nodo_list);
		smith = (AVB.next_NODO == -1)?AVB.num_NODOS:AVB.next_NODO;
		fseek(nodo_list,sizeof(NODO)*smith,SEEK_SET);
		fgetpos(nodo_list,&p);
		fread(&pain,sizeof(NODO),1,nodo_list);
		if (AVB.next_NODO+1)
			AVB.next_NODO = pain.pai; // Possibilitar isso na remoção
		else
			AVB.anum_NODOS++;

		AVB.num_NODOS++;
		felipe = smith;//Felipe é endereço do pai
		pain.pai=-1;
		pain.num_chaves=1;
		pain.ne_folha=1;
		pain.filhos[0]=AVB.raiz;
		pain.chaves[0]=son1.chaves[min_chaves];
		pain.addresses[0]=son1.addresses[min_chaves];
	}

	smith = (AVB.next_NODO == -1)?AVB.num_NODOS:AVB.next_NODO;
	fseek(nodo_list,sizeof(NODO)*smith,SEEK_SET);
	fgetpos(nodo_list,&f2);
	fread(&son2,sizeof(NODO),1,nodo_list);
	if (AVB.next_NODO+1)
		AVB.next_NODO = son2.pai;
	else
		AVB.anum_NODOS++;

	AVB.num_NODOS++;

	for(c=k/2;c<k-1;c++)
	{
		son2.chaves[c-(k/2)] = son1.chaves[c];
		son2.addresses[c-(k/2)] = son1.addresses[c];
		if (son1.ne_folha)
			son2.filhos[c-(k/2)] = son1.filhos[c];
	}
	if (son1.ne_folha)
		son2.filhos[c-(k/2)] = son1.filhos[c];
	son2.ne_folha = son1.ne_folha;
	son1.num_chaves = son2.num_chaves = min_chaves; // Só funciona para ordem par

	if(pai+1)
	{
		son1.pai = son2.pai = pai;
		//if (son1.ne_folha)
			pain.filhos[k-1]=pain.filhos[k-2];
		for (c=k-2;c>scroll;c--)
		{
			//if (son1.ne_folha)
				pain.filhos[c]=pain.filhos[c-1];
			pain.addresses[c]=pain.addresses[c-1];
			pain.chaves[c]=pain.chaves[c-1];
		}
		pain.filhos[scroll+1]=smith;
		pain.chaves[scroll]=son1.chaves[min_chaves];
		pain.addresses[scroll]=son1.addresses[min_chaves];
		pain.num_chaves++;
	}
	else // Criar nodo no arquivo para ser o pai
	{
		son1.pai = son2.pai = felipe;
		pain.filhos[1]=smith;
		AVB.raiz=felipe;//Acho que isso resolve
		printf("\nAVB.raiz = %d\n", AVB.raiz);
	}
	line;
	breakline;
	printf("PAIN:\n");
	print_nodo(pain);
	breakline;
	printf("SON 1:\n");
	print_nodo(son1);
	breakline;
	printf("SON 2:\n");
	print_nodo(son2);
	line;

	fsetpos(nodo_list,&p);
	fwrite(&pain,sizeof(NODO),1,nodo_list);
	fsetpos(nodo_list,&f1);
	fwrite(&son1,sizeof(NODO),1,nodo_list);
	fsetpos(nodo_list,&f2);
	fwrite(&son2,sizeof(NODO),1,nodo_list);
	rewind(tree);
	fwrite(&AVB,sizeof(NODO),1,tree);

	return;
}
int merge_nodo(FILE *tree,FILE *nodo_list,int pai,int scroll)
{	//	Função para juntar dois NODOs irmãos, retorna o tipo da junção. 0 = Só passou um elemento, 1 = Junção dos irmãos com o pai.
	NODO pain,son1,son2;
	ARVOREB AVB;
	int c,felipe,smith;
	fpos_t p,f1,f2;

	rewind(tree);
	fread(&AVB,sizeof(ARVOREB),1,tree); 	//	Lê o arquivo de configuração da árvore
	fseek(nodo_list,sizeof(NODO)*pai,SEEK_SET);
	fgetpos(nodo_list,&p);
	fread(&pain,sizeof(NODO),1,nodo_list);
	fseek(nodo_list,sizeof(NODO)*pain.filhos[scroll],SEEK_SET);
	fgetpos(nodo_list,&f1);
	fread(&son1,sizeof(NODO),1,nodo_list);
	felipe=scroll;
	felipe+=(scroll <= pain.num_chaves)?1:-1; // Verifica se tem irmão à direita e define o irmão para junção
	fseek(nodo_list,sizeof(NODO)*pain.filhos[felipe],SEEK_SET);
	fgetpos(nodo_list,&f2);
	fread(&son2,sizeof(NODO),1,nodo_list);
	if(son2.num_chaves< k/2)
	{
		if(scroll>felipe)
		{
			fseek(nodo_list,f2,SEEK_SET);
			fread(&son1,sizeof(NODO),1,nodo_list);
			fseek(nodo_list,f1,SEEK_SET);
			fread(&son2,sizeof(NODO),1,nodo_list);
		}
			son1.chaves[son1.num_chaves]=pain.chaves[scroll];//Talvez tenha que fazer um deslocamento em alguns casos disso (AFF)
			son1.addresses[son1.num_chaves++]=pain.addresses[scroll];
			pain.num_chaves--;

			for(c=0;c<son2.num_chaves;c++)
			{
				son1.chaves[son1.num_chaves+c]=son2.chaves[c];
				son1.addresses[son1.num_chaves+c]=son2.addresses[c];
				son1.filhos[son1.num_chaves+(c+1)]=son2.filhos[c];//Ruan, veja a questão dos filhos nos outros casos!
			}
			son1.num_chaves+=c;
			son1.filhos[son1.num_chaves+1]=son2.filhos[c];


			AVB.num_NODOS--;
			//Manter funcionamento da lista okay...


	}
	else
	if(scroll<felipe)//Acho que isso não altera a configuração de filhos caso feito do jeito certo
	{	//caso não seja o ultimo filho e o irmão tenha 1 chave para doar
		son1.chaves[++son1.num_chaves]=pain.chaves[scroll];
		son1.addresses[son1.num_chaves]=pain.addresses[scroll];
		pain.chaves[scroll]=son2.chaves[0];
		pain.addresses[scroll]=son2.addresses[0];

		for(c=son2.num_chaves; c>0;c--)
		{
			son2.chaves[c-1]=son2.chaves[c];
			son2.addresses[c-1]=son2.addresses[c];
		}

	}
	else
	{//caso seja o ultimo filho e o irmão tenha 1 chave para doar

		for(c=son1.num_chaves; c>=0;c--)
		{
				son1.chaves[c+1]=son1.chaves[c];
				son1.addresses[c+1]=son1.addresses[c];
		}
		son1.chaves[0]=pain.chaves[scroll];
		son1.addresses[0]=pain.addresses[scroll];
		son1.num_chaves++;
		pain.chaves[scroll]=son2.chaves[son2.num_chaves];
		pain.addresses[scroll];son2.addresses[son2.num_chaves];
		son2.num_chaves--;
		//em tese é só isso...

	}






	return 0;
}
void add_key_tree(char *dir,int account_address,char *folder, char *type,int key,int SUB_NODO)
{	// Função para adicionar chaves na árvore
	char *address, *sub_address, *a, *sa;
	FILE *tree, *nodo_list;
	ARVOREB new;
	NODO nnew;
	int c=0,scroll,aux,aux2,aux3,cdn=1;
	printf("\nKey tree 1\n");
	a = merge_string(folder,merge_string("tree_",type));
	sa = merge_string(folder,merge_string("tree_L_",type));
	address = dir_builder(dir,account_address,a);
	sub_address	= dir_builder(dir,account_address,sa);
	printf("\nKey tree 2\n");
	if (!(tree = fopen(address,"r+b")))
		error_m("Error at file opening");
	if (!(nodo_list = fopen(sub_address,"r+b")))
		error_m("Error at file opening");
	fread(&new,sizeof(ARVOREB),1,tree);
	rewind(tree);
	printf("\nKey tree 3\n");
	scroll=new.raiz;
	if(new.raiz==-1)
	{	printf("\nEntrou em condição raiz =-1\n");
		nnew.chaves[0]=key;
		nnew.num_chaves=1;
		nnew.addresses[0]=add_LISTA_ENC(dir,account_address,-1,SUB_NODO);//Aqui deve ser o endereço da lista
		nnew.pai=-1;
		nnew.ne_folha=0;
		new.raiz=new.next_NODO==-1?new.num_NODOS:new.next_NODO;
		printf("new.raiz = %d\nnew.next_NODO = %d\nnew.num_NODOS = %d\n",new.raiz,new.next_NODO,new.num_NODOS);
		new.num_NODOS++;
		cdn=0;
	}
	else
	while(cdn)
	{
		fseek(nodo_list,sizeof(NODO)*scroll,SEEK_SET);
		fread(&nnew,sizeof(NODO),1,nodo_list);

		if(nnew.num_chaves==k-1) // 	Divisão de NODO cheio
		{
			printf("\n---> DIVISÃO)\n");
			split_tree(tree,nodo_list,nnew.pai,c);
			rewind(tree);
			printf("\nnewraiz = %d\n", new.raiz);
			fread(&new,sizeof(ARVOREB),1,tree);
			rewind(tree);
			scroll=nnew.pai+1?nnew.pai:new.raiz;
			fseek(nodo_list,sizeof(NODO)*scroll,SEEK_SET);
			fread(&nnew,sizeof(NODO),1,nodo_list);
		}

		for(c=0;c<nnew.num_chaves && 1 > compara_infos(dir,account_address,type,nnew.chaves[c],key);c++);
		if(!nnew.ne_folha)//Caso básico
		{
			aux=nnew.chaves[c];
			aux3=c;
			nnew.chaves[c++] = key;
			for(;c<nnew.num_chaves;c++)
			{
				aux2=nnew.chaves[c];
				nnew.chaves[c]=aux;
				aux=aux2;
			}
			c=aux3;
			aux=nnew.addresses[c];
			nnew.addresses[c++] = add_LISTA_ENC(dir,account_address,-1,SUB_NODO);//MESMA COISA AQUI
			for(;c<nnew.num_chaves;c++)
			{
				aux2=nnew.addresses[c];
				nnew.addresses[c]=aux;
				aux=aux2;
			}
			nnew.num_chaves++;
			fseek(nodo_list,sizeof(NODO)*scroll,SEEK_SET);
			cdn=0;
		}
		//GENIAL CORMEN <3
		else	// 	Garante que haja filhos, por causa do if acima
			scroll=nnew.filhos[c];

	}
	new.num_SUB_NODOS++;
	fwrite(&new,sizeof(ARVOREB),1,tree);
	fwrite(&nnew,sizeof(NODO),1,nodo_list);

	fclose(tree);
	fclose(nodo_list);

	free(a);
	free(sa);
	free(address);
	free(sub_address);

	return;
}

//Decisão de projeto
/*void remove_key_tree(int account_address, char *dir,char *name,int key)
{	//	Remover chave da árvore, só chamado caso todos os SUB_NODOS da chave tenham sido removidos
	char *address, *sub_address, *a, *sa;
	FILE *tree, *nodo_list;
	ARVOREB new;
	NODO nnew;
	int c,scroll,aux,aux2,aux3,cdn=1;

	a = merge_string("tree_",name);
	sa = merge_string("tree_L_",name);
	address = dir_builder(dir,account_address,a);
	sub_address	= dir_builder(dir,account_address,sa);

	if (!(tree = fopen(address,"r+b")))
		error_m("Error at file opening");
	if (!(nodo_list = fopen(sub_address,"r+b")))
		error_m("Error at file opening");
	fread(&new,sizeof(ARVOREB),1,tree);
	rewind(tree);


	if((scroll=new.raiz)==-1)
		cdn=0;
	while(cdn)
	{
		fseek(nodo_list,sizeof(NODO)*scroll,SEEK_SET);
		fread(&nnew,sizeof(NODO),1,nodo_list);

		if (nnew.num_chaves == min_chaves && nnew.pai+1)
		{
			aux2 = merge_nodo(tree,nodo_list,nnew.pai,scroll);
			rewind(tree);
			fread(&new,sizeof(ARVOREB),1,tree);
			rewind(tree);
			scroll=nnew.pai?nnew.pai:new.raiz;	// definir após definir merge_nodo
			fseek(nodo_list,sizeof(NODO)*scroll,SEEK_SET);
			fread(&nnew,sizeof(NODO),1,nodo_list);
		}

		for(c=0;c<nnew.num_chaves && 1 > (aux=compara_infos(dir,account_address,name,nnew.chaves[c],key)) && aux;c++);
		if(!aux)
		{

		}
		else
			scroll=nnew.filhos[c];
	}




	fwrite(&new,sizeof(ARVOREB),1,tree);
	fwrite(&nnew,sizeof(NODO),1,nodo_list);

	fclose(tree);
	fclose(nodo_list);

	free(a);
	free(sa);
	free(address);
	free(sub_address);

	return;
}*/
;

int busca_SUB_NODO_tree(char *dir,int account_address,char *folder, char *type,int key)
{
	char *address, *sub_address, *a, *sa;
	FILE *tree, *nodo_list;
	ARVOREB new;
	NODO nnew;
	int c,scroll,aux,cdn=1,achou=-1;

	a = merge_string(folder,merge_string("tree_",type));
	sa = merge_string(folder,merge_string("tree_L_",type));
	address = dir_builder(dir,account_address,a);
	sub_address	= dir_builder(dir,account_address,sa);

	if (!(tree = fopen(address,"r+b")))
		error_m("Error at file opening");
	if (!(nodo_list = fopen(sub_address,"r+b")))
		error_m("Error at file opening");
	fread(&new,sizeof(ARVOREB),1,tree);
	rewind(tree);

	scroll = new.raiz;
	printf("\n----> Aqui cara");
	while(cdn && new.raiz+1)
	{
		fseek(nodo_list,sizeof(NODO)*scroll,SEEK_SET);
		fread(&nnew,sizeof(NODO),1,nodo_list);
		printf("\n----> Em baixo, cara");
		for(c=0;c<nnew.num_chaves && 1 > (aux=compara_infos(dir,account_address,type,nnew.chaves[c],key)) && aux;c++);
		printf("\n AUX = %d",aux);
		if (!aux)
		{	printf("\nPF 1");
			achou = nnew.addresses[c];
			cdn = 0;
		}
		else
		if (!nnew.ne_folha)//É FOLHA!
		{	printf("\nPF 2");
			achou = -1;
			cdn = 0;
		}
		else
		{
			scroll = nnew.filhos[c];
			printf("\nPF 3");
		}
	}
	fclose(tree);
	fclose(nodo_list);

	free(a);
	free(sa);
	free(address);
	free(sub_address);

	return achou;
}

//OPS! LISTA ENCADEADA
void add_SUB_NODO_tree(char *dir, int account_address,char *folder, char *type,int key,int SUB_NODO)
{
	char *address, *sub_address = dir_builder(dir,account_address,"lista_enc.bin"), *a;
	FILE *tree, *sub_nodo_list;
	ARVOREB new;
	int pos;

	a = merge_string(folder,merge_string("tree_",type));

	address = dir_builder(dir,account_address,a);

	printf("\nChegou aqui 3\n");
	pos = busca_SUB_NODO_tree(dir,account_address,folder,type,key);
	if (pos == -1)
		add_key_tree(dir,account_address,folder,type,key,SUB_NODO);
	else
	{
		LISTA primeiro;
		int scroll = pos, aux=1;
		if (!(tree = fopen(address,"r+b")))
				error_m("Error at file opening");
		if (!(sub_nodo_list = fopen(sub_address,"r+b")))
			error_m("Error at file opening");
		fread(&new,sizeof(ARVOREB),1,tree);
		rewind(tree);
		printf("\nChegou aqui 4\n");
		for (;aux;)
		{
			fseek(sub_nodo_list,sizeof(LISTA)*scroll,SEEK_SET);
			fread(&primeiro,sizeof(LISTA),1,sub_nodo_list);
			if (primeiro.next+1)
				scroll = primeiro.next;
			else
				aux = 0;
		}
		add_LISTA_ENC(dir,account_address,scroll,SUB_NODO);
		new.num_SUB_NODOS++;

		fwrite(&new,sizeof(ARVOREB),1,tree);
		fclose(sub_nodo_list);
		fclose(tree);
	}
	free(a);
	printf("\nChegou aqui 5.3\n");
	free(address);
	printf("\nChegou aqui 5.4\n");
	free(sub_address);
	printf("\nChegou aqui 5.5\n");

	return;
}

void remove_SUB_NODO_tree(char *dir,int account_address,char *folder, char *type,int key,int SUB_NODO)
{


}


//FUNÇÕES DE ÁRVORE DE CONTAS
void create_tree_account(char *dir)
{
	char *address, *sub_address;
	FILE *tree, *nodo_list;
	ARVOREB avb;
	NODO nodo;

	address = merge_string(dir,"tree_CONTA.bin");
	sub_address = merge_string(dir,"tree_L_CONTA.bin");

	if (!(tree = fopen(address,"wb")))
		error_m("Error at file allocation");
	if (!(nodo_list = fopen(sub_address,"wb")))
		error_m("Error at file allocation");
	avb.num_NODOS=0;
	avb.num_SUB_NODOS=0;
	avb.raiz=-1;
	avb.anum_NODOS=0;
	avb.next_NODO=-1;
	nodo.num_chaves=0;
	nodo.ne_folha=0;
	nodo.pai=-1;

	fwrite(&nodo,sizeof(NODO),1,nodo_list);
	fwrite(&avb,sizeof(ARVOREB),1,tree);

	fclose(tree);
	fclose(nodo_list);

	free(address);
	free(sub_address);

	return;
}
void add_CONTA_tree(char *dir,int account_address)
{	// Função para adicionar chaves na árvore
	char *address, *sub_address, *a, *sa;
	FILE *tree, *nodo_list;
	ARVOREB avb;
	NODO nodo;
	int c=0,scroll,aux,aux2,aux3,cdn=1;

	address = merge_string(dir,"tree_CONTA.bin");
	sub_address = merge_string(dir,"tree_L_CONTA.bin");

	if (!(tree = fopen(address,"r+b")))
		error_m("Error at file opening");
	if (!(nodo_list = fopen(sub_address,"r+b")))
		error_m("Error at file opening");
	fread(&avb,sizeof(ARVOREB),1,tree);
	rewind(tree);

	scroll=avb.raiz;
	if(avb.raiz==-1)
	{	printf("\nEntrou em condição raiz =-1\n");
		nodo.chaves[0]=account_address;
		nodo.addresses[0]=account_address;
		nodo.num_chaves=1;
		nodo.pai=-1;
		nodo.ne_folha=0;
		avb.raiz=avb.next_NODO==-1?avb.num_NODOS:avb.next_NODO;
		/*DEBUG ABAIXO*/
		printf("avb.raiz = %d\nodo.next_NODO = %d\nodo.num_NODOS = %d\n",avb.raiz,avb.next_NODO,avb.num_NODOS);
		avb.num_NODOS++;
		cdn=0;
	}
	else
	while(cdn)
	{
		fseek(nodo_list,sizeof(NODO)*scroll,SEEK_SET);
		fread(&nodo,sizeof(NODO),1,nodo_list);

		if(nodo.num_chaves==k-1) // 	Divisão de NODO cheio
		{	/*DEBUG ABAIXO*/
			printf("\n---> DIVISÃO)\n");
			split_tree(tree,nodo_list,nodo.pai,c);
			rewind(tree);
			printf("\nnewraiz = %d\n", avb.raiz);
			fread(&avb,sizeof(ARVOREB),1,tree);
			rewind(tree);
			scroll=nodo.pai+1?nodo.pai:avb.raiz;
			fseek(nodo_list,sizeof(NODO)*scroll,SEEK_SET);
			fread(&nodo,sizeof(NODO),1,nodo_list);
		}

		for(c=0;c<nodo.num_chaves && 1 > compara_infos(dir,0,"addresses.bin",nodo.chaves[c],account_address);c++);
		if(!nodo.ne_folha)//Caso básico
		{
			aux=nodo.chaves[c];
			aux3=c;
			nodo.chaves[c] = account_address;
			nodo.addresses[c++] = account_address;
			for(;c<nodo.num_chaves;c++)
			{
				aux2=nodo.chaves[c];
				nodo.chaves[c]=aux;
				aux=aux2;
			}
			c=aux3;
			aux=nodo.addresses[c];
			for(;c<nodo.num_chaves;c++)
			{
				aux2=nodo.addresses[c];
				nodo.addresses[c]=aux;
				aux=aux2;
			}
			nodo.num_chaves++;
			fseek(nodo_list,sizeof(NODO)*scroll,SEEK_SET);
			cdn=0;
		}
		//GENIAL CORMEN <3
		else	// 	Garante que haja filhos, por causa do if acima
			scroll=nodo.filhos[c];

	}
	avb.num_SUB_NODOS++;
	fwrite(&avb,sizeof(ARVOREB),1,tree);
	fwrite(&nodo,sizeof(NODO),1,nodo_list);

	fclose(tree);
	fclose(nodo_list);

	free(a);
	free(sa);
	free(address);
	free(sub_address);

	return;
}


//FUNÇÕES DE COMPARAÇÃO
int compara_infos(char *dir,int account_address, char *tipo,int a,int b)
{
	char *address;
	FILE *list;

	if (!strcmp(tipo,"messages.bin"))
	{
		messages A,B;
		address = dir_builder(dir,account_address,"text_list.bin");
		if (!(list = fopen(address,"rb")))
			error_m("Error at file opening");
		fseek(list,sizeof(messages)*a,SEEK_SET);
		fread(&A,sizeof(messages),1,list);
		fseek(list,sizeof(messages)*b,SEEK_SET);
		fread(&B,sizeof(messages),1,list);
		fclose(list);
		return (strcmp(A.mail,B.mail));
	}
	else
	if (!strcmp(tipo,"subjects.bin"))
	{
		subjects A,B;
		address = dir_builder(dir,account_address,"subject_list.bin");
		if (!(list = fopen(address,"rb")))
			error_m("Error at file opening");
		fseek(list,sizeof(subjects)*a,SEEK_SET);
		fread(&A,sizeof(subjects),1,list);
		fseek(list,sizeof(subjects)*b,SEEK_SET);
		fread(&B,sizeof(subjects),1,list);
		fclose(list);
		return (strcmp(A.subject,B.subject));
	}
	else
	if (!strcmp(tipo,"PALAVRA.bin"))
	{
		PALAVRA A,B;
		address = dir_builder(dir,account_address,"word_list.bin");
		if (!(list = fopen(address,"rb")))
			error_m("Error at file opening");
		fseek(list,sizeof(PALAVRA)*a,SEEK_SET);
		fread(&A,sizeof(PALAVRA),1,list);
		fseek(list,sizeof(PALAVRA)*b,SEEK_SET);
		fread(&B,sizeof(PALAVRA),1,list);
		fclose(list);
		return (strcmp(A.key,B.key));
	}
	else
	if (!strcmp(tipo,"HORARIO.bin"))
	{
		HORARIO A,B;
		address = dir_builder(dir,account_address,"horario_list.bin");
		if (!(list = fopen(address,"rb")))
			error_m("Error at file opening");
		fseek(list,sizeof(HORARIO)*a,SEEK_SET);
		fread(&A,sizeof(HORARIO),1,list);
		fseek(list,sizeof(HORARIO)*b,SEEK_SET);
		fread(&B,sizeof(HORARIO),1,list);
		fclose(list);
		return horario_menor(A,B)?-1:(horario_igual(A,B)?0:1);
	}
	else
	if (!strcmp(tipo,"addresses.bin"))
	{
		CONTA A,B;
		address = merge_string(dir,"addresses.bin");
		if (!(list = fopen(address,"rb")))
			error_m("Error at file opening");
		fseek(list,sizeof(CONTA)*a,SEEK_SET);
		fread(&A,sizeof(CONTA),1,list);
		fseek(list,sizeof(CONTA)*b,SEEK_SET);
		fread(&B,sizeof(CONTA),1,list);
		fclose(list);
		if (account_address)
			return (strcmp(A.password,B.password));
		return (strcmp(A.user,B.user));
	}

	return 1;
}
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
fpos_t predescessor(FILE *tree,FILE *nodo_list,int nodo,int key)
{

	NODO N,N1;
	int aux;
	fpos_t p;

	fseek(nodo_list,sizeof(NODO)*nodo,SEEK_SET);
	fread(&N,sizeof(NODO),1,nodo_list);
	fseek(nodo_list,sizeof(NODO)*N.filhos[key],SEEK_SET);
	fread(&N1,sizeof(NODO),1,nodo_list);

	while(!N1.ne_folha)
	{
		fseek(nodo_list,sizeof(NODO)*N1.filhos[aux = N1.num_chaves+1],SEEK_SET);
		fread(&N1,sizeof(NODO),1,nodo_list);

	}

	if(N1.num_chaves == k/2-1)
	{
		merge_nodo(tree,nodo_list,N1.pai,aux);//Eis a questão
		fseek(nodo_list,sizeof(NODO)*N1.pai,SEEK_SET);
		fread(&N1,sizeof(NODO),1,nodo_list);
		fseek(nodo_list,sizeof(NODO)*N1.filhos[aux = N1.num_chaves+1],SEEK_SET);
		fgetpos(nodo_list,&p);
		fread(&N1,sizeof(NODO),1,nodo_list);
	}

	N.addresses[key] = N1.addresses[N1.num_chaves];
	N.chaves[key] = N1.chaves[N1.num_chaves];

	return p;
}
#endif /* FUNCTIONS_2_STRUCT_H_ */
