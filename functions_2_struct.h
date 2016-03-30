/*
 * functions_2_struct.h
 *
 *  Created on: 11/01/2016
 *      Author: ricardo
 */
//MUDAN�AS
#ifndef FUNCTIONS_2_STRUCT_H_
#define FUNCTIONS_2_STRUCT_H_

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include <time.h>
#include <sys/stat.h>
#ifndef __linux__ // Verifica se o sistema atual n�o � Linux
	#include <direct.h> 	//	Inclui biblioteca específica do Windows se não for
	#include <conio.h>
#else
	#include <curses.h>
#endif

#define cls system("CLS || clear");
#define pause printf("\nDigite algo para continuar"); getchar();
#define spc printf("  |");
#define spc_m printf("              ");
#define breakline printf("\n");
#define line breakline; printf("____________________________________________________________"); breakline;
#define x 10	// Limite de hist�rico
#define k 6
// Ordem - Usar n�mero par - N�mero de Chaves ser� k-1 e o n�mero de filhos ser� k
#define numChaves k-1
#define numFilhos k
#define minChaves ((k/2)-1)
#define windus "C:/Users/Ruan/Desktop/T/"
#define ubuntus "/home/ricardo/e-server"
//	Tamanho dos tipos de arquivos
#define size_message 300
#define size_subject 100
#define size_address 64
#define size_word 30
#define size_horario strlen("00/00/0000 00:00:00")

// 	Temos que voltar o ponteiro dos arquivos depois das opera��es de leitura


typedef struct
{
	int num_addresses;
	int next_address;
	int anum_address;
	char dir[200];
}
settings;

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
}
configuration;

//	Estrutura dos tipos de informa��es de email
typedef struct
{
	char mail[size_message];
}
messages;

typedef struct
{
	char subject[size_subject];
}
subjects;

typedef struct
{
	char address[size_address];
}
addresses;

typedef struct //O resto das informações não servem pra busca
{
	//int dia,mês,ano,horas,minutos,segundos;
	int data[6];//data ordenada por relevância (ano,mês,dia,hora,minuto,segundo)
}
HORARIO;

typedef struct
{
	char key[size_word];
}
PALAVRA;

typedef struct
{
	int remetente;
	int destinatario;
	int assunto;
	int MSG;
	int data;
	int historico; 		// PARA RICARDO E RUAN DO FUTURO: A ESTRUTURA RETRO ALUDIDA
}						// REFERENCIAR� UM SUBNODO, E ASSIM EM DIANTE, ENCADEANDO.
SUB_NODO;

typedef struct
{
       char user[size_address];
       char password[64];
       /*int inbox; //Todos v�o conter o valor no qual est� no vetor o NODO que corresponde
       int outbox;
       int read;
       int trash;
       int sent;*/
}
CONTA;		//Conta deve ser uma arvore pois seria totalmente incompreensível
			//usar métodos tão sofisticados de busca pra tudo exceto pra achar as contas

typedef struct
{
	int chaves[k-1]; 	// Campo que é escolhido convenientemente ao funcionamento do sistema. (messages, subjects, HORARIO
	int addresses[k-1];	// Apontam para Listas de SUB_NODO
	int filhos[k]; 		// NODOS
	int pai;
	char num_chaves;	// Escolha do tipo char devido ao tamanho máximo escalado para o programa, 64 filhos e 63 chaves.
	char ne_folha;	// Número de Filhos. Também pode indicar se o NODO é uma folha ou não, 0 = folha.
}
NODO;

typedef struct
{
	int raiz;
	int num_NODOS;
	int anum_NODOS;
	int next_NODO;
	int num_SUB_NODOS;
}
ARVOREB;

typedef struct
{
	int address;
	int next;
}
LISTA; //	Lista de SUB_NODOs

//	Estruturas para abertura dos arquivos
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
}
ARQUIVOS;

typedef struct{
	FILE *settings;
	FILE *addresses;
	FILE *tree_CONTA;
	FILE *tree_L_CONTA;
}
PRINCIPAL;

typedef struct{
	int pos_email;
	char *text;
}RESULT;

typedef struct{
	int num_resultados;
	RESULT **index;
}RESULTADO;

typedef struct{

	char *menu_header;
	int num_headered_itens;
	int *headers;
	int num_simple_itens;
	char **headered_titles;
	char **simple_titles;

}MENU_GUIDE;

//ESCOPO DAS FUN��ES
char* detecta_os();
void print_nodo(NODO nodo);
void print_arvoreb(ARVOREB avb);
void print_configuration(configuration c);
void make_dir(char *aux);
void error_m(char *errormessage);
char* filepath_gen(char *dir, char *file);
char* dir_builder(char*dir,int account_number,char* file);
char* merge_string(char *string1, char *string2);
char* ler(char modo);

void create_address_list(char *dir);
int add_address(FILE *set, FILE *ad,char *user,char *password);
void remove_address(FILE *set, FILE *ad,int pos);
char* get_address(char *dir,int account_number);
char* get_password(FILE *ad,int account_number);

void setup_server(char *dir);
void create_config(char *dir,int account_address);

void create_text_list(char *dir,int account_address);
int add_text(FILE *config,FILE *text_list,char *new);
void remove_text(FILE *config,FILE *text_list,int scroll);
char* get_text(FILE *config,FILE *text_list, int scroll);
char** words_from_text(FILE *config,FILE *text_list, int scroll);

void create_subject_list(char *dir,int account_address);
int add_subject(FILE *config, FILE *subject_list,char *new);
void remove_subject(FILE *config, FILE *subject_list,int scroll);
char* get_subject(FILE *config, FILE *subject_list,int scroll);

void create_email_list(char *dir,int account_address);
int add_email(FILE *config, FILE *email_list,int remetente,int destinatario, int assunto, int MSG, int data, int historico);
void remove_email(FILE *config, FILE *email_list,int scroll);

void create_LISTA_ENC(char *dir,int account_address);
int add_LISTA_ENC(FILE *config, FILE *lista_enc,int ultimo,int novo);
int remove_LISTA_ENC(FILE *config, FILE *lista_enc, int anterior,int atual);//A chamada desta fun��o deve ser feita dentro da arvore onde � pos�vel ter essas informa��es

void create_horario_list(char *dir,int account_address);
int add_horario(FILE *config, FILE *horario_list, HORARIO novo);
void remove_horario(FILE *config, FILE *horario_list, int scroll);

void create_word_list(char *dir,int account_address);
int add_word(FILE *config, FILE *word_list, char *new);
void remove_word(FILE *config, FILE *word_list, int scroll);

void create_tree_type(char *dir,int account_address, char *folder, char *type);
void split_tree(FILE *tree,FILE *nodo_list,int pai,int scroll);
void predecessor(FILE *tree,FILE *nodo_list,int nodo,int key);
int merge_nodo(FILE *tree,FILE *nodo_list,int pai,int scroll);
void add_key_tree(ARQUIVOS *arquivos,FILE *tree, FILE *nodo_list,char *type,int key,int SUB_NODO);
void remove_key_tree(ARQUIVOS *arquivos,FILE *tree, FILE *nodo_list,char *type,int key);
int busca_SUB_NODO_tree(ARQUIVOS *arquivos,FILE *tree, FILE *nodo_list, char *type,int key);
void add_SUB_NODO_tree(ARQUIVOS *arquivos,FILE *tree, FILE *nodo_list,char *type,int key,int SUB_NODO);
void remove_SUB_NODO_tree(ARQUIVOS *arquivos,FILE *tree, FILE *nodo_list, char *type,int key,int SUB_NODO);

NODO clean_NODO(void);

void create_tree_account(char *dir);
void add_CONTA_tree(FILE *addresses,FILE *tree, FILE *nodo_list,int account_address);
int busca_CONTA_tree(FILE *addresses,FILE *tree, FILE *nodo_list,int key);

int compara_infos(ARQUIVOS *arquivos,char *type,int a,int b);
int horario_igual(HORARIO a,HORARIO b);
int horario_maior(HORARIO a,HORARIO b);
int horario_menor(HORARIO a,HORARIO b);
int horario_menor_igual(HORARIO a,HORARIO b);
int horario_maior_igual(HORARIO a,HORARIO b);

RESULTADO create_result_list(void);
void add_result(RESULTADO *lista,int pos_email,char *text);


#endif /* FUNCTIONS_2_STRUCT_H_ */
