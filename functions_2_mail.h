/*
 * functions_2.h
 *
 *  Created on: 11/01/2016
 *      Author: ricardo
 */

#ifndef FUNCTIONS_2_H_
#define FUNCTIONS_2_H_
#include "functions_2_struct.h"

//	Teclas
#ifdef __linux__
#define KeyEnter 10
//Teclas Especiais
#define KeySpecial 27
// Teclas Especiais 2
#define KeySpecial2 79
#define KeySpecial3 91
#define KeyUp 65
#define KeyDown 66
#define KeyRight 67
#define KeyLeft 68

#else
#define KeyEnter 13
//Teclas Especiais
#define KeySpecial 0
// Teclas Especiais 2
#define KeySpecial2 224
#define KeyUp 72
#define KeyDown 80
#define KeyRight 77
#define KeyLeft 75

#endif

#define numMenu 5

void menu();
void project_presentation();
void setup(PRINCIPAL *principal);

void create_account(PRINCIPAL *principal,char *dir,char *user,char *password);
void criar_conta(PRINCIPAL *principal,char *dir);
void acessar_conta(PRINCIPAL *principal,char *dir);
int generic_account_menu(MENU_GUIDE GUIDE);
void abrir_conta(PRINCIPAL *principal,char *dir,int conta);

char * print_email_header_to_string(ARQUIVOS *arquivos,int email_pos);
void print_email(ARQUIVOS *arquivos,int email_pos);
void print_horario(HORARIO data);
char * print_horario_to_string(HORARIO data);

void access_inbox(PRINCIPAL *principal,ARQUIVOS *arquivos);
void access_outbox(PRINCIPAL *principal,ARQUIVOS *arquivos);
void access_read(PRINCIPAL *principal,ARQUIVOS *arquivos);
void access_sent(PRINCIPAL *principal,ARQUIVOS *arquivos);
void access_trash(PRINCIPAL *principal,ARQUIVOS *arquivos);

void search_email(PRINCIPAL *principal,ARQUIVOS *arquivos);
void send_email(PRINCIPAL *principal, ARQUIVOS *arquivos, char *dest);
void move_email(ARQUIVOS *arquivos,int email_pos,char *from);
void delete_email(ARQUIVOS *arquivos,int email_pos,char *folder);
void add_email_to_tfolder(ARQUIVOS *arquivos,int email_pos,char *folder);
void remove_email_from_tfolder(ARQUIVOS *arquivos,int email_pos,char *folder);

void exibir_email(PRINCIPAL *principal,ARQUIVOS *arquivos,char *pasta,int pos_email);
char *destinatario_email(ARQUIVOS *arquivos, int pos_email);
char *remetente_email(ARQUIVOS *arquivos, int pos_email);

void list_email_decreasing(RESULTADO *resultado,ARQUIVOS *arquivos,FILE *nodo_list,int pos);
void list_email_increasing(RESULTADO *resultado,ARQUIVOS *arquivos,FILE *nodo_list,int pos);

ARQUIVOS *open_account_files(char *dir, int account_address);
void close_account_files(ARQUIVOS *arquivos);
PRINCIPAL *open_server_files();
void close_server_files(PRINCIPAL *principal);

int number_of_emails(FILE *tree);

void formated_message(char *string);


#endif /* FUNCTIONS_2_H_ */
