/*
 * functions_2_struct.c
 *
 *  Created on: 25/03/2016
 *      Author: Ruan
 */
#include "functions_2_struct.h"

// FUN��ES DE TESTE INTERNO

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
	printf("n�o � folha = %d\n", nodo.ne_folha);
}
void print_arvoreb(ARVOREB avb)
{
	printf("AVB - raiz = %d\n", avb.raiz);
	printf("AVB - num_NODOS = %d\n", avb.num_NODOS);
	printf("AVB - anum_NODOS = %d\n", avb.anum_NODOS);
	printf("AVB - num_SUB_NODOS = %d\n", avb.num_SUB_NODOS);
	printf("AVB - next_NODO = %d\n", avb.next_NODO);
}
//Fun��o para resolver ambiguidade de modos entre sistemas operacionais
void make_dir(char *aux)
{
	#ifdef __linux
		mkdir(aux, S_IRWXU);
	#else
		_mkdir(aux);
	#endif
}
// 	FUN��ES �TEIS
void error_m(char *errormessage)
{ 	/* Fun��o para facilitar exibi��o de mensagens de erro */
    printf("\n%s",errormessage);
    pause;
    exit(1);
}


char* filepath_gen(char *dir, char *file)
{ 	// 	Fun��o para gerar ponteiro para char com o diret�rio
	char *path=(char *) malloc(sizeof(char)*250);	//	Alocando espa�o para ponteiro que ser� retornado
	sprintf(path, "%s",dir);	//	Colocando diret�rio fornecido no espa�o alocado
	strcat(path,"/");			//	Concatenando com uma barra
	strcat(path,file);			//	Concatenando com o nome do arquivo
	return path;				//	Retornando o ponteiro
}
// N�o se pode usar strcat em string constante, perdi um tempinho com isso.

char* dir_builder(char*dir,int account_number,char* file)
{	//	Fun��o para gerar o caminho do arquivo
	char *ad = get_address(dir,account_number), *r;

	r = strcat(strcat(strcat(filepath_gen(dir,""),ad),"/"),file);
	printf("\nAd = %s \n r= %s",ad,r);
	free(ad);
	return r;
}

char* merge_string(char *string1, char *string2)
{
	char *merged = (char *) malloc(sizeof(char)*(strlen(string1)+strlen(string2)+1));
	sprintf(merged,"%s",string1);
	strcat(merged,string2);
	return merged;
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


//LISTA DE ENDERE�OS GLOBAL
void create_address_list(char *dir) //
{	// Fun��o para criar o arquivo da Lista de Endere�os
	FILE *new;			//	Declarando ponteiro para arquivo que ser� criado
	CONTA ad;		//	Declarando vari�vel addresses para ser escrita no arquivo
	char *dir_ad=filepath_gen(dir,"addresses.bin");		//	Gerando caminho para o arquivo

	if(!(new=fopen(dir_ad,"wb")))	//	Criando arquivo
		error_m("Error at file allocation - CAL");	//	Mensagem de erro se o arquivo n�o conseguir ser criado/subscrito
	else
	{
		sprintf(&(ad.user[0]),"%d",-1);	//	Colocando "-1" na vari�vel para indicar que ainda n�o h� nenhum endere�o
		fwrite(&ad,sizeof(CONTA),1,new);	//	Escrevendo no arquivo
		fclose(new);	// 	Fechando arquivo
	}

	return;
}

int add_address(FILE *set, FILE *ad,char *user,char *password)
{	//	Fun��o para adicionar um endere�o na Lista de Endere�os
	settings s;
	CONTA ads;
	int scroll;		//	Vari�veis auxiliares
	fpos_t c;

	rewind(set);						//	Colocando a posi��o do fluxo de dados no inicio
	fread(&s,sizeof(settings),1,set);	//	Lendo arquivo de configura��es e armazenando na vari�vel s
	scroll=(s.next_address == -1)?s.num_addresses:s.next_address;	//	Definindo a posi��o em que o novo endere�o ser� salvo no arquivo addresses.bin
	fseek(ad,scroll*sizeof(CONTA),SEEK_SET);				//	Deslocando a posi��o do buffer no arquivo addresses.bin
	if(s.next_address!=-1)										//	caso haja blocos n�o utilizados a serem subscritos
	{
		fgetpos(ad,&c);								//	Guardando a posi��o atual do fluxo de dados
		fread(&ads,sizeof(CONTA),1,ad);			//	Lendo arquivo de endere�os e armazenando na vari�vel ad
		sscanf(ads.user,"%d",&(s.next_address));	//	Atualizando o pr�ximo a ser subscrito
		fsetpos(ad,&c);								// 	Retornando a posi��o do fluxo de dados para a salva anteriormente
	}
	else
		s.anum_address++;
	sprintf(ads.user,"%s",user);			//	Guardando usu�rio
	sprintf(ads.password,"%s",password);			//	Guardando senha
	s.num_addresses++;						//	Incrementando o n�mero de endere�os
	rewind(set);						//	Colocando a posi��o do fluxo de dados no inicio
	fwrite(&s,sizeof(settings),1,set);		//	Escrevendo altera��es feitas nos arquivos
	fwrite(&ads,sizeof(CONTA),1,ad);

	return scroll;
}

void remove_address(FILE *set, FILE *ad,int pos)
{	//	Fun��o para remover um endere�o da Lista de Endere�os
	settings s;
	CONTA ads;
	fpos_t c;

	rewind(set);
	fread(&s,sizeof(settings),1,set);

	if (pos < s.anum_address && pos >= 0)
	{
		fseek(ad,pos*sizeof(CONTA),SEEK_SET);
		fgetpos(ad,&c);
		fread(&ads,sizeof(CONTA),1,ad);
		fsetpos(ad,&c);
		sprintf(&(ads.user[0]),"%d", s.next_address);
		s.next_address=pos;
		s.num_addresses--;
		fwrite(&ads,sizeof(CONTA),1,ad);
		rewind(set);
		fwrite(&s,sizeof(settings),1,set);//escrevendo altera��es feitas
	}

	return;
}

char* get_address(char *dir,int account_number)
{	//	Fun��o que retorna um endere�o da Lista de Endere�os
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

char* get_password(FILE *ad,int account_number)
{	//	Fun��o que retorna um endere�o da Lista de Endere�os
	char* address = (char*)malloc(sizeof(char)*64);
	CONTA ads;

	fseek(ad,account_number*sizeof(CONTA),SEEK_SET);
	fread(&ads,sizeof(CONTA),1,ad);
	sprintf(address,"%s",ads.password);

	return address;
}

//CONFIGURA��O
void setup_server(char *dir)
{	//	Fun��o para configura��o geral do Servidor
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
{	// Fun��o para criar o arquivo de Configura��o do Usu�rio
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
{	//	Fun��o para criar o arquivo da Lista de Textos do usu�rio
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
{	//	Fun��o para adicionar um texto � Lista de Textos
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

void remove_text(FILE *config,FILE *text_list,int pos)//precisamos validar as remo��es depois
{	//	Fun��o para remover um texto da Lista de Textos
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
{	//	Fun��o que retorna um texto da Lista de Textos
	char *t=(char*)malloc(sizeof(char)*300);
	messages read;

	fseek(text_list,pos*sizeof(messages),SEEK_SET);
	fread(&read,sizeof(messages),1,text_list);

	sprintf(t,"%s",read.mail);

	return t;
}
char** words_from_text(FILE *config,FILE *text_list, int scroll)
{
	char  **words;
	messages read;
	char aux[300];
	int c=0,ca=0,tam,num_words=0;

	fseek(text_list,scroll,SEEK_SET);
	fread(&read,sizeof(messages),1,text_list);

	while(c<300 && read.mail[c])
	{
		for(num_words++,ca++,tam=0 ; c<300 && read.mail[c] && tam <=30 && read.mail[c] !=' ' && read.mail[c] !='.' && read.mail[c] !=',' && read.mail[c] !='!' && read.mail[c] !='?' && read.mail[c] !='<' && read.mail[c] !='>' &&read.mail[c] !=';' && read.mail[c] !=':';c++,ca++,tam++ )//Tratando possíveis pontuações existentes
		{
			aux[ca]=read.mail[c];
		}
	}

	aux[ca]='\o';//Barra zero é assim mesmo?

	words=(char**)malloc(sizeof(char*)*num_words);

	for(c=0;c<num_words;c++)
		words[c]=(char*)malloc(sizeof(char)*30);

	ca=0;
	for(c=0;c<num_words;c++,ca++)
		for(tam=0;aux[ca] != ' ';ca++,tam++)
			words[c][tam]=aux[ca];

	return words;

}

//LISTA DE ASSUNTOS
void create_subject_list(char* dir,int account_address)
{	// Fun��o para criar o arquivo da Lista de Assuntos do usu�rio
	char *subjects_address=dir_builder(dir,account_address,"subject_list.bin");//fazer uma fun��o pra isso!!!
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
{	// Fun��o para adicionar um assunto � Lista de Assuntos
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

void remove_subject(FILE *config, FILE *subject_list,int pos)
{	// Fun��o para remover um assunto da Lista de Assuntos
	configuration c;
	subjects s;

	rewind(config);
	fread(&c,sizeof(configuration),1,config);
	if (pos < c.anum_subjects && pos >=0)
	{
		sprintf(s.subject,"%d",c.next_subject);
		c.num_subjects--;
		c.next_subject=pos;
		fseek(subject_list,pos*sizeof(subjects),SEEK_SET);
		fwrite(&s,sizeof(subjects),1,subject_list);
		rewind(config);
		fwrite(&c,sizeof(configuration),1,config);
	}

	return;
}

char* get_subject(FILE *config, FILE *subject_list,int pos)
{	//	Fun��o que retorna um assunto da Lista de Assuntos dada sua posi��o (pos)
	char *sub;
	subjects s;

	sub=(char*)malloc(sizeof(char)*100);
	fseek(subject_list,pos*sizeof(subjects),SEEK_SET);
	fread(&s,sizeof(subjects),1,subject_list);
	fclose(subject_list);
	sprintf(sub,"%s",s.subject);

	return sub;
}

//LISTA DE EMAILS
void create_email_list(char* dir,int account_address)
{	// Fun��o para criar o arquivo da Lista de Emails
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

int add_email(FILE *config, FILE *email_list,int remetente,int destinatario, int assunto, int MSG, int data, int historico)
{ 	//	Fun��o para adicionar um email na Lista de Emails
	configuration c; 			//	Manipula��o da configura��o
	SUB_NODO e; 				//	Manipula��o de email
	int scroll;					// 	Vari�vel para deslocamento
	fpos_t p;

	rewind(config);
	fread(&c,sizeof(configuration),1,config);				//

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
	rewind(config);
	fwrite(&c,sizeof(configuration),1,config);				//
	fwrite(&e,sizeof(SUB_NODO),1,email_list);				//

	return scroll;
}

void remove_email(FILE *config, FILE *email_list,int pos)
{	//	Fun��o para removar email da Lista de Emails dada sua posi��o (scroll)
	configuration c; 			//	Manipula��o da configura��o
	SUB_NODO e; 				//	Manipula��o de email
	fpos_t p;

	rewind(config);
	fread(&c,sizeof(configuration),1,config);				//

	if (pos < c.anum_emails && pos >=0 )
	{
		fseek(email_list,pos*sizeof(SUB_NODO),SEEK_SET);								//
		fgetpos(email_list,&p);
		fread(&e,sizeof(SUB_NODO),1,email_list);				//
		fsetpos(email_list,&p);
		e.remetente = c.next_email;								//
		c.next_email = pos;									//
		c.num_emails--;											//
		rewind(config);
		fwrite(&c,sizeof(configuration),1,config);				//
		fwrite(&e,sizeof(SUB_NODO),1,email_list);				//
	}

	return;
}

//LISTA DE LISTAS ENCADEADAS DE EMAILS
void create_LISTA_ENC(char *dir,int account_address)
{	// Fun��o para criar o arquivo da Lista de Listas Encadeadas de Emails
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

int add_LISTA_ENC(FILE *config, FILE *lista_enc, int antecessor,int novo)
{	//	Fun��o para adicionar lista � Lista de Listas Encadeadas de Emails
	LISTA a;
	configuration c;
	int pos,aux=-1;
	fpos_t p;
	// FUTURO: FAZER SUPOSI��O DA POSI��O NA LISTA QUANDO n�o houver antecessor
	rewind(config);
	fread(&c,sizeof(configuration),1,config);

	pos = (c.next_LISTA_ENC==-1)?c.num_LISTA_ENC:c.next_LISTA_ENC;
	if(antecessor >= 0)
	{
		fseek(lista_enc,antecessor*sizeof(LISTA),SEEK_SET);
		fgetpos(lista_enc,&p);
		fread(&a,sizeof(LISTA),1,lista_enc);
		fsetpos(lista_enc,&p);
		aux = a.next;
		a.next = pos;
		fwrite(&a,sizeof(LISTA),1,lista_enc);
	}
	fseek(lista_enc,pos*sizeof(LISTA),SEEK_SET);
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

	return (pos);
}

void remove_LISTA_ENC(FILE *config, FILE *lista_enc, int antecessor,int atual)
{	//	Fun��o para remover lista da Lista de Listas Encadeadas de Emails
	LISTA a;
	configuration c;
	int aux;
	fpos_t p;

	rewind(config);
	fread(&c,sizeof(configuration),1,config);

	if(atual < c.anum_LISTA_ENC && atual >= 0)
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
		rewind(config);
		fwrite(&c,sizeof(configuration),1,config);
	}

	return;
}

//LISTA DE HOR�RIOS
void create_horario_list(char *dir,int account_address)
{	// Fun��o para criar arquivo da Lista de Hor�rios
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

int add_horario(FILE *config, FILE *horario_list, HORARIO novo)
{	// Fun��o para adicionar hor�rio � Lista de Hor�rios
	HORARIO a;
	configuration c;
	int scroll,cont;
	fpos_t p;

	rewind(config);
	fread(&c,sizeof(configuration),1,config);

	scroll=(c.next_HORARIO==-1)?c.num_HORARIO:c.next_HORARIO;
	fseek(horario_list,scroll*sizeof(HORARIO),SEEK_SET);
	fgetpos(horario_list,&p);
	fread(&a,sizeof(HORARIO),1,horario_list);
	fsetpos(horario_list,&p);
	if(c.next_HORARIO!=-1)
		c.next_HORARIO=a.data[0];
	else
		c.anum_HORARIO++;
	c.num_HORARIO++;
	for(cont=0;cont<6;cont++)
		a.data[cont]=novo.data[cont];
	fwrite(&a,sizeof(HORARIO),1,horario_list);
	rewind(config);
	fwrite(&c,sizeof(configuration),1,config);

	return scroll;
}

void remove_horario(FILE *config, FILE *horario_list, int scroll)
{	// Fun��o para remover hor�rio da Lista de Hor�rios
	HORARIO a;
	configuration c;

	rewind(config);
	fread(&c,sizeof(configuration),1,config);

	if(scroll < c.anum_HORARIO && scroll > 0)
	{
		a.data[0]=c.next_HORARIO;
		c.next_HORARIO=scroll;
		c.num_HORARIO--;
		fseek(horario_list,scroll*sizeof(HORARIO),SEEK_SET);
		fwrite(&a,sizeof(HORARIO),1,horario_list);
		rewind(config);
		fwrite(&c,sizeof(configuration),1,config);
	}

	return;
}

//LISTA DE PALAVRAS
void create_word_list(char *dir,int account_address)
{	//	Fun��o para criar o arquivo da Lista de Palavras
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

int add_word(FILE *config, FILE *word_list, char *new)
{	// 	Fun��o para adicionar palavra da Lista de Palavras
	PALAVRA w;
	configuration c;
	int pos;
	fpos_t p;

	rewind(config);
	fread(&c,sizeof(configuration),1,config);

	pos=(c.next_PALAVRA==-1)?c.num_PALAVRA:c.next_PALAVRA;
	fseek(word_list,pos*sizeof(PALAVRA),SEEK_SET);
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
	rewind(config);
	fwrite(&c,sizeof(PALAVRA),1,config);

	return pos;
}

void remove_word(FILE *config, FILE *word_list, int scroll)
{	// 	Fun��o para remover palavra da Lista de Palavras
	PALAVRA w;
	configuration c;

	rewind(config);
	fread(&c,sizeof(configuration),1,config);

	if (scroll < c.anum_PALAVRA && scroll >0)
	{
		sprintf(w.key,"%d",c.next_PALAVRA);
		c.num_PALAVRA--;
		c.next_PALAVRA=scroll;
		fseek(word_list,scroll*sizeof(PALAVRA),SEEK_SET);
		fwrite(&w,sizeof(PALAVRA),1,word_list);
		rewind(config);
		fwrite(&c,sizeof(PALAVRA),1,config);
	}

	return;
}
//FUN��ES DA ARVORE
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
{	//	Fun��o para dividir n�s cheios durante inser��o
	NODO pain,son1,son2;
	ARVOREB AVB;
	int c,felipe,smith;
	fpos_t p,f1,f2;

	rewind(tree);
	fread(&AVB,sizeof(ARVOREB),1,tree); 	//	L� o arquivo de configura��o da �rvore
	if(pai+1)	// 	Caso o NODO a ser dividido tenha pai
	{
		printf("\n---> CASO TENHA PAI)\nscroll = %d\n",scroll);
		fseek(nodo_list,sizeof(NODO)*pai,SEEK_SET); // Procura a posi��o do pai no arquivo
		fgetpos(nodo_list,&p);	//	Guarda a posi��o de grava��o do Pai
		fread(&pain,sizeof(NODO),1,nodo_list);	//
		fseek(nodo_list,sizeof(NODO)*pain.filhos[scroll],SEEK_SET);	// Procura posi��o do filho cheio, que vai ser o Filho 1
		fgetpos(nodo_list,&f1);	//	Guarda a posi��o de grava��o do Filho 1
		fread(&son1,sizeof(NODO),1,nodo_list);
	}
	else	//	Se o NODO a ser dividido n�o tiver pai (Caso for raiz)
	{
		printf("\n---> CASO N�O TENHA PAI)\n");
		fseek(nodo_list,sizeof(NODO)*AVB.raiz,SEEK_SET);
		fgetpos(nodo_list,&f1);	//	Guarda a posi��o de grava��o do Filho 1
		fread(&son1,sizeof(NODO),1,nodo_list);
		smith = (AVB.next_NODO == -1)?AVB.num_NODOS:AVB.next_NODO;
		fseek(nodo_list,sizeof(NODO)*smith,SEEK_SET);
		fgetpos(nodo_list,&p);
		fread(&pain,sizeof(NODO),1,nodo_list);
		if (AVB.next_NODO+1)
			AVB.next_NODO = pain.pai; // Possibilitar isso na remo��o
		else
			AVB.anum_NODOS++;

		AVB.num_NODOS++;
		felipe = smith;//Felipe � endere�o do pai
		pain.pai=-1;
		pain.num_chaves=1;
		pain.ne_folha=1;
		pain.filhos[0]=AVB.raiz;
		pain.chaves[0]=son1.chaves[minChaves];
		pain.addresses[0]=son1.addresses[minChaves];
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
	son1.num_chaves = son2.num_chaves = minChaves; // S� funciona para ordem par

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
		pain.chaves[scroll]=son1.chaves[minChaves];
		pain.addresses[scroll]=son1.addresses[minChaves];
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

void predescessor(FILE *tree,FILE *nodo_list,int nodo,int key)
{

	NODO N,N1;
	int aux;
	fpos_t p,aux_p;

	fseek(nodo_list,sizeof(NODO)*nodo,SEEK_SET);
	fread(&N,sizeof(NODO),1,nodo_list);
	fgetpos(nodo_list,&aux_p);
	fseek(nodo_list,sizeof(NODO)*N.filhos[key],SEEK_SET);
	fread(&N1,sizeof(NODO),1,nodo_list);

	while(!N1.ne_folha)
	{
		fseek(nodo_list,sizeof(NODO)*N1.filhos[aux = N1.num_chaves+1],SEEK_SET);
		fread(&N1,sizeof(NODO),1,nodo_list);
		fgetpos(nodo_list,&p);

	}

	if(N1.num_chaves == k/2-1)
	{
		merge_nodo(tree,nodo_list,N1.pai,aux);//Eis a quest�o
		fseek(nodo_list,sizeof(NODO)*N1.pai,SEEK_SET);
		fread(&N1,sizeof(NODO),1,nodo_list);
		fseek(nodo_list,sizeof(NODO)*N1.filhos[aux = N1.num_chaves+1],SEEK_SET);
		fgetpos(nodo_list,&p);
		fread(&N1,sizeof(NODO),1,nodo_list);
	}

	N.addresses[key] = N1.addresses[(int)N1.num_chaves];
	N.chaves[key] = N1.chaves[(int)N1.num_chaves];
	N1.num_chaves--;
	fsetpos(nodo_list,&aux_p);
	fwrite(&N,sizeof(nodo),1,nodo_list);
	fsetpos(nodo_list,&p);
	fwrite(&N1,sizeof(nodo),1,nodo_list);


}

int merge_nodo(FILE *tree,FILE *nodo_list,int pai,int scroll)
{	//	Fun��o para juntar dois NODOs irm�os, retorna o tipo da jun��o. 0 = S� passou um elemento, 1 = Jun��o dos irm�os com um elemento do pai.
	NODO pain,son1,son2;
	ARVOREB AVB;
	int c,felipe,retorno;
	fpos_t p,f1,f2,aux;

	rewind(tree);
	fread(&AVB,sizeof(ARVOREB),1,tree); 	//	L� o arquivo de configura��o da �rvore
	fseek(nodo_list,sizeof(NODO)*pai,SEEK_SET);
	fgetpos(nodo_list,&p);
	fread(&pain,sizeof(NODO),1,nodo_list);
	fseek(nodo_list,sizeof(NODO)*pain.filhos[scroll],SEEK_SET);
	fgetpos(nodo_list,&f1);
	fread(&son1,sizeof(NODO),1,nodo_list);
	felipe=scroll;
	felipe+=(scroll <= pain.num_chaves)?1:-1; // Verifica se tem irm�o � direita e define o irm�o para jun��o
	fseek(nodo_list,sizeof(NODO)*pain.filhos[felipe],SEEK_SET);
	fgetpos(nodo_list,&f2);
	fread(&son2,sizeof(NODO),1,nodo_list);
	if(son2.num_chaves< k/2)
	{
		if(scroll>felipe)
		{
			fsetpos(nodo_list,&f2);
			fread(&son1,sizeof(NODO),1,nodo_list);
			fsetpos(nodo_list,&f1);
			fread(&son2,sizeof(NODO),1,nodo_list);
			aux=f2;
			f2=f1;
			f1=aux;
		}

			son1.chaves[(int)son1.num_chaves]=pain.chaves[scroll];
			son1.addresses[(int)son1.num_chaves++]=pain.addresses[scroll];
			for(c=scroll;c<pain.num_chaves;c++)//Deslocando chaves do pai para cobrir a ausência da chave retirada para o filho
			{
				pain.addresses[scroll]=pain.addresses[scroll+1];
				pain.chaves[scroll]=pain.addresses[scroll+1];
				pain.filhos[scroll]=pain.addresses[scroll+1];
			}
			pain.filhos[scroll]=pain.addresses[scroll+1];
			pain.num_chaves--;

			for(c=0;c<son2.num_chaves;c++)//Colocando as chaves do filho dois no um
			{
				son1.chaves[son1.num_chaves+c]=son2.chaves[c];
				son1.addresses[son1.num_chaves+c]=son2.addresses[c];
				son1.filhos[son1.num_chaves+(c+1)]=son2.filhos[c];//Ruan, veja a quest�o dos filhos nos outros casos!
			}
			son1.num_chaves+=c;
			son1.filhos[son1.num_chaves+1]=son2.filhos[c];

			//É necessário remover o nodo de son2. abaixo está sendo feito
			son2.pai=AVB.next_NODO;//Arbitrando isso aqui, se não for, mude!
			AVB.next_NODO=scroll>felipe?scroll:felipe;
			AVB.num_NODOS--;
			//Manter funcionamento da lista okay...

			retorno=1;
	}
	else
	if(scroll<felipe)//Acho que isso n�o altera a configura��o de filhos caso feito do jeito certo
	{	//caso n�o seja o ultimo filho e o irm�o tenha 1 chave para doar
		son1.chaves[(int)son1.num_chaves]=pain.chaves[scroll];
		son1.addresses[(int)son1.num_chaves++]=pain.addresses[scroll];
		pain.chaves[scroll]=son2.chaves[0];
		pain.addresses[scroll]=son2.addresses[0];
		son2.num_chaves--;

		for(c=0; c<son2.num_chaves;c++)
		{
			son2.chaves[c]=son2.chaves[c+1];
			son2.addresses[c]=son2.addresses[c+1];
		}
		retorno=0;
	}
	else
	{//caso seja o ultimo filho e o irm�o tenha 1 chave para doar

		for(c=son1.num_chaves; c>=0;c--)
		{
				son1.chaves[c+1]=son1.chaves[c];
				son1.addresses[c+1]=son1.addresses[c];
		}
		son1.chaves[0]=pain.chaves[scroll];
		son1.addresses[0]=pain.addresses[scroll];
		son1.num_chaves++;
		pain.chaves[scroll]=son2.chaves[(int)son2.num_chaves];
		pain.addresses[scroll]=son2.addresses[(int)son2.num_chaves];
		son2.num_chaves--;
		//em tese � s� isso...//Ainda concordo comigo no passado
		retorno=0;
	}
	fsetpos(nodo_list,&p);
	fwrite(&pain,sizeof(NODO),1,nodo_list);
	fsetpos(nodo_list,&f1);
	fwrite(&son1,sizeof(NODO),1,nodo_list);
	fsetpos(nodo_list,&f2);
	fwrite(&son2,sizeof(NODO),1,nodo_list);
	return retorno;
}
void add_key_tree(ARQUIVOS arquivos,FILE *tree, FILE *nodo_list,char *type,int key,int SUB_NODO)
{	// Fun��o para adicionar chaves na �rvore
	ARVOREB new;
	NODO nnew;
	int c=0,scroll,aux,aux2,aux3,aux4,cdn=1;

	rewind(tree);
	fread(&new,sizeof(ARVOREB),1,tree);

	scroll=new.raiz;
	if(new.raiz==-1)
	{	printf("\nEntrou em condi��o raiz =-1\n");
		nnew.chaves[0]=key;
		nnew.num_chaves=1;
		nnew.addresses[0]=add_LISTA_ENC(arquivos.config,arquivos.lista_enc,-1,SUB_NODO);//Aqui deve ser o endere�o da lista
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

		if(nnew.num_chaves==k-1) // 	Divis�o de NODO cheio
		{
			printf("\n---> DIVIS�O)\n");
			split_tree(tree,nodo_list,nnew.pai,c);
			rewind(tree);
			printf("\nnewraiz = %d\n", new.raiz);
			fread(&new,sizeof(ARVOREB),1,tree);
			rewind(tree);
			scroll=nnew.pai+1?nnew.pai:new.raiz;
			fseek(nodo_list,sizeof(NODO)*scroll,SEEK_SET);
			fread(&nnew,sizeof(NODO),1,nodo_list);
		}

		for(c=0;c<nnew.num_chaves && 1 > compara_infos(arquivos,type,nnew.chaves[c],key);c++);
		if(!nnew.ne_folha)//Caso b�sico
		{
			aux=nnew.chaves[c];
			nnew.chaves[c] = key;

			aux3=nnew.addresses[c];
			nnew.addresses[c++] = add_LISTA_ENC(arquivos.config,arquivos.lista_enc,-1,SUB_NODO);//MESMA COISA AQUI
			for(;c<nnew.num_chaves;c++)
			{
				aux2=nnew.chaves[c];
				nnew.chaves[c]=aux;
				aux=aux2;

				aux4=nnew.addresses[c];
				nnew.addresses[c]=aux3;
				aux3=aux4;
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
	fwrite(&nnew,sizeof(NODO),1,nodo_list);
	rewind(tree);
	fwrite(&new,sizeof(ARVOREB),1,tree);

	return;
}
void remove_key_tree(ARQUIVOS arquivos,FILE *tree, FILE *nodo_list,char *type,int key)
{
	// Fun��o para adicionar chaves na �rvore
		ARVOREB new;
		NODO nnew;
		int c=0,scroll,aux,aux2,aux3,aux4,cdn=1;


		rewind(tree);
		fread(&new,sizeof(ARVOREB),1,tree);


		scroll=new.raiz;

		while(cdn)
		{
			fseek(nodo_list,sizeof(NODO)*scroll,SEEK_SET);
			fread(&nnew,sizeof(NODO),1,nodo_list);

			if(nnew.num_chaves==k/2-1) // 	Junção de NODO com mínimo de chaves
			{
				printf("\n---> Junção)\n");
				merge_tree(tree,nodo_list,nnew.pai,c);
				rewind(tree);
				printf("\nnewraiz = %d\n", new.raiz);
				fread(&new,sizeof(ARVOREB),1,tree);
				rewind(tree);
				scroll=nnew.pai+1?nnew.pai:new.raiz;
				fseek(nodo_list,sizeof(NODO)*scroll,SEEK_SET);
				fread(&nnew,sizeof(NODO),1,nodo_list);
			}

			for(c=0;c<nnew.num_chaves && 1 > compara_infos(arquivos,type,nnew.chaves[c],key);c++);
			if(!compara_infos(arquivos,type,nnew.chaves[c],key))//Caso b�sico
			{
				if(!nnew.ne_folha)//é folha
				{
					for(;c<nnew.num_chaves;c++)
					{
						nnew.addresses[c]=nnew.addresses[c+1];
						nnew.chaves[c]=nnew.chaves[c+1];
						nnew.filhos[c]=nnew.filhos[c+1];
					}
					nnew.filhos[c]=nnew.filhos[c+1];
					nnew.num_chaves--;

				}
				else
					 predecessor(tree,nodo_list,scroll,c);//Sobrescreve a chave pelo predescessor e apaga-o no nó folha
			}
			//GENIAL CORMEN <3
			else	// 	Garante que haja filhos, por causa do if acima
				scroll=nnew.filhos[c];

		}
		new.num_SUB_NODOS--;
		fwrite(&nnew,sizeof(NODO),1,nodo_list);
		rewind(tree);
		fwrite(&new,sizeof(ARVOREB),1,tree);

		return;
}

int busca_SUB_NODO_tree(ARQUIVOS arquivos,FILE *tree, FILE *nodo_list, char *type,int key)
{
	ARVOREB new;
	NODO nnew;
	int c,scroll,aux,cdn=1,achou=-1;

	rewind(tree);
	fread(&new,sizeof(ARVOREB),1,tree);

	scroll = new.raiz;

	while(cdn && new.raiz+1)
	{
		fseek(nodo_list,sizeof(NODO)*scroll,SEEK_SET);
		fread(&nnew,sizeof(NODO),1,nodo_list);

		for(c=0;c<nnew.num_chaves && 1 > (aux=compara_infos(arquivos,type,nnew.chaves[c],key)) && aux;c++);

		if (!aux)
		{
			achou = nnew.addresses[c];
			cdn = 0;
		}
		else
		if (!nnew.ne_folha)//� FOLHA!
		{
			achou = -1;
			cdn = 0;
		}
		else
			scroll = nnew.filhos[c];
	}

	return achou;
}

//OPS! LISTA ENCADEADA
void add_SUB_NODO_tree(ARQUIVOS arquivos,FILE *tree, FILE *nodo_list, char *type,int key,int SUB_NODO)
{
	ARVOREB new;
	int pos;

	pos = busca_SUB_NODO_tree(arquivos,tree,nodo_list,type,key);
	if (pos == -1)
		add_key_tree(arquivos,tree,nodo_list,type,key,SUB_NODO);
	else
	{
		LISTA primeiro;
		int scroll = pos, aux=1;

		rewind(tree);
		fread(&new,sizeof(ARVOREB),1,tree);

		for (;aux;)
		{
			fseek(arquivos.lista_enc,sizeof(LISTA)*scroll,SEEK_SET);
			fread(&primeiro,sizeof(LISTA),1,arquivos.lista_enc);
			if (primeiro.next+1)
				scroll = primeiro.next;
			else
				aux = 0;
		}
		add_LISTA_ENC(arquivos.config,arquivos.lista_enc,scroll,SUB_NODO);
		new.num_SUB_NODOS++;

		rewind(tree);
		fwrite(&new,sizeof(ARVOREB),1,tree);
	}

	return;
}

void remove_SUB_NODO_tree(ARQUIVOS arquivos,FILE *tree, FILE *nodo_list, char *type,int key,int SUB_NODO)
{


}


//FUN��ES DE �RVORE DE CONTAS
void create_tree_account(char *dir)
{
	char *address, *sub_address;
	FILE *tree, *nodo_list;
	ARVOREB avb;
	NODO nodo;

	address = merge_string(dir,"/tree_CONTA.bin");
	sub_address = merge_string(dir,"/tree_L_CONTA.bin");

	if (!(tree = fopen(address,"wb")))
		error_m("Error at file allocation - CTA");
	if (!(nodo_list = fopen(sub_address,"wb")))
		error_m("Error at file allocation - CTA");
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
void add_CONTA_tree(FILE *addresses,FILE *tree, FILE *nodo_list,int account_address)
{	// Fun��o para adicionar chaves na �rvore
	ARVOREB avb;
	NODO nodo;
	int c=0,scroll,aux,aux2,cdn=1;
	ARQUIVOS aux3;
	aux3.addresses = addresses;

	rewind(tree);
	fread(&avb,sizeof(ARVOREB),1,tree);

	scroll=avb.raiz;
	if(avb.raiz==-1)
	{	printf("\nEntrou em condi��o raiz =-1\n");
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

		if(nodo.num_chaves==k-1) // 	Divis�o de NODO cheio
		{	/*DEBUG ABAIXO*/
			printf("\n---> DIVIS�O)\n");
			split_tree(tree,nodo_list,nodo.pai,c);
			rewind(tree);
			printf("\nnewraiz = %d\n", avb.raiz);
			fread(&avb,sizeof(ARVOREB),1,tree);
			rewind(tree);
			scroll=nodo.pai+1?nodo.pai:avb.raiz;
			fseek(nodo_list,sizeof(NODO)*scroll,SEEK_SET);
			fread(&nodo,sizeof(NODO),1,nodo_list);
		}

		for(c=0;c<nodo.num_chaves && 1 > compara_infos(aux3,"addresses",nodo.chaves[c],account_address);c++);
		if(!nodo.ne_folha)//Caso b�sico
		{
			aux=nodo.chaves[c];
			nodo.chaves[c] = account_address;
			nodo.addresses[c++] = account_address;
			for(;c<nodo.num_chaves;c++)
			{
				aux2=nodo.chaves[c];
				nodo.chaves[c]=aux;
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
	rewind(tree);
	fwrite(&avb,sizeof(ARVOREB),1,tree);
	fwrite(&nodo,sizeof(NODO),1,nodo_list);

	return;
}
int busca_CONTA_tree(FILE *addresses,FILE *tree, FILE *nodo_list,int key)
{
	ARVOREB new;
	NODO nnew;
	int c,scroll,aux,cdn=1,achou=-1;
	ARQUIVOS aux3;
	aux3.addresses = addresses;

	rewind(tree);
	fread(&new,sizeof(ARVOREB),1,tree);

	scroll = new.raiz;

	while(cdn && new.raiz+1)
	{
		fseek(nodo_list,sizeof(NODO)*scroll,SEEK_SET);
		fread(&nnew,sizeof(NODO),1,nodo_list);

		for(c=0;c<nnew.num_chaves && 1 > (aux=compara_infos(aux3,"addresses",nnew.chaves[c],key)) && aux;c++);

		if (!aux)
		{
			achou = nnew.chaves[c];
			cdn = 0;
		}
		else
		if (!nnew.ne_folha)//� FOLHA!
		{
			achou = -1;
			cdn = 0;
		}
		else
			scroll = nnew.filhos[c];
	}

	return achou;
}


//FUN��ES DE COMPARA��O
int compara_infos(ARQUIVOS arquivos, char *tipo,int a,int b)
{
	if (!strcmp(tipo,"messages"))
	{
		messages A,B;
		fseek(arquivos.text_list,sizeof(messages)*a,SEEK_SET);
		fread(&A,sizeof(messages),1,arquivos.text_list);
		fseek(arquivos.text_list,sizeof(messages)*b,SEEK_SET);
		fread(&B,sizeof(messages),1,arquivos.text_list);
		return (strcmp(A.mail,B.mail));
	}
	else
	if (!strcmp(tipo,"subjects"))
	{
		subjects A,B;
		fseek(arquivos.subject_list,sizeof(subjects)*a,SEEK_SET);
		fread(&A,sizeof(subjects),1,arquivos.subject_list);
		fseek(arquivos.subject_list,sizeof(subjects)*b,SEEK_SET);
		fread(&B,sizeof(subjects),1,arquivos.subject_list);
		return (strcmp(A.subject,B.subject));
	}
	else
	if (!strcmp(tipo,"PALAVRA"))
	{
		PALAVRA A,B;
		fseek(arquivos.word_list,sizeof(PALAVRA)*a,SEEK_SET);
		fread(&A,sizeof(PALAVRA),1,arquivos.word_list);
		fseek(arquivos.word_list,sizeof(PALAVRA)*b,SEEK_SET);
		fread(&B,sizeof(PALAVRA),1,arquivos.word_list);
		return (strcmp(A.key,B.key));
	}
	else
	if (!strcmp(tipo,"HORARIO"))
	{
		HORARIO A,B;
		fseek(arquivos.horario_list,sizeof(HORARIO)*a,SEEK_SET);
		fread(&A,sizeof(HORARIO),1,arquivos.horario_list);
		fseek(arquivos.horario_list,sizeof(HORARIO)*b,SEEK_SET);
		fread(&B,sizeof(HORARIO),1,arquivos.horario_list);
		return horario_menor(A,B)?-1:(horario_igual(A,B)?0:1);
	}
	else
	if (!strcmp(tipo,"addresses"))
	{
		CONTA A,B;
		fseek(arquivos.addresses,sizeof(CONTA)*a,SEEK_SET);
		fread(&A,sizeof(CONTA),1,arquivos.addresses);
		fseek(arquivos.addresses,sizeof(CONTA)*b,SEEK_SET);
		fread(&B,sizeof(CONTA),1,arquivos.addresses);

		return (strcmp(A.user,B.user));
	}
	else
	if (!strcmp(tipo,"password"))
	{
		CONTA A,B;
		fseek(arquivos.addresses,sizeof(CONTA)*a,SEEK_SET);
		fread(&A,sizeof(CONTA),1,arquivos.addresses);
		fseek(arquivos.addresses,sizeof(CONTA)*b,SEEK_SET);
		fread(&B,sizeof(CONTA),1,arquivos.addresses);

		return (strcmp(A.password,B.password));
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
	return 0;//se chegar aqui necessariamente � igual
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
	return 0;//se chegar aqui necessariamente � igual
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
	return 1;//se chegar aqui necessariamente � igual
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
	return 1;//se chegar aqui necessariamente � igual
}

RESULTADO create_result_list(void)
{
	RESULTADO new;
	new.num_resultados = 0;
	new.index = NULL;
	return new;
}

void add_result(RESULTADO *lista,int pos_email,char *text)
{
	RESULT *novo_resultado=(RESULT *)calloc(sizeof(RESULT),1);
	lista->index = (RESULT **) realloc(lista->index,sizeof(RESULT *)*(++lista->num_resultados));
	(*(lista->index+(lista->num_resultados-1)))= novo_resultado;
	novo_resultado->pos_email = pos_email;
	novo_resultado->text = text;
}

