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
#define KeyEnter 13
//Teclas Especiais
#define KeySpecial 0
// Teclas Especiais 2
#define KeySpecial2 224
#define KeyUp 72
#define KeyLeft 75
#define KeyRight 77
#define KeyDown 80

#define numMenu 5

void menu();
void project_presentation();
void setup(PRINCIPAL principal);

void create_account(PRINCIPAL *principal,char *dir,char *user,char *password);
void criar_conta(PRINCIPAL *principal,char *dir);
void acessar_conta(PRINCIPAL *principal,char *dir);
void abrir_conta(PRINCIPAL principal,char *dir,int conta);

char * print_email_header_to_string(ARQUIVOS arquivos,int email_pos);
void print_email(ARQUIVOS arquivos,int email_pos);
void print_horario(HORARIO data);
char * print_horario_to_string(HORARIO data);

void access_inbox(ARQUIVOS arquivos);
send_email(PRINCIPAL principal, ARQUIVOS arquivos);

void list_email_decreasing(RESULTADO *resultado,ARQUIVOS arquivos,FILE *tree,FILE *nodo_list,int pos);


ARQUIVOS open_account_files(char *dir, int account_address);
void close_account_files(ARQUIVOS arquivos);
PRINCIPAL open_server_files();
void close_server_files(PRINCIPAL principal);

int number_of_emails(FILE *tree);

void formated_message(char *string);


#endif /* FUNCTIONS_2_H_ */
