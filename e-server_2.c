/*
 * e-server.c
 *
 *  Created on: 11/01/2016
 *      Author: ricardo
 */
#include "functions_2_mail.h"
#include "functions_2_struct.h"
#define windus "C:/Users/Ruan/Desktop/T/"
#define ubuntus "/home/ricardo/e-server"

void ler_end(char *er)
{
	printf("TESTE1.x.1: Lendo endereço 0\n");pause;
			printf("Endereço lido: %s\n",get_address(0,er));
	printf("TESTE1.x.2: Lendo endereço 1\n");pause;
		printf("Endereço lido: %s\n",get_address(1,er));

}
char* detecta_os()
{
	FILE *X;
	char *a=filepath_gen(ubuntus,"teste.bin");

	X = fopen(a,"wbx");
	if(X)
	remove(a);
	free(a);

	return X?ubuntus:windus;

}

int main(void)
{
	//int c;
	char *er =detecta_os();
	printf("TESTE0: Configurando servidor\n");pause;
		setup(er);
	printf("TESTE1.0: Criando lista de endereços\n");pause;
		create_address_list(er);
	printf("TESTE1.1: Adicionando endereço\n");pause;
		add_address("ruanmed@e-server.com",er);
	printf("TESTE1.1: Adicionando endereço 2\n");pause;
		add_address("ricardo@e-server.com",er);
	ler_end(er);
	printf("TESTE1.3: Removendo endereço 0\n");pause;
		remove_address(0,er);
	ler_end(er);
	printf("TESTE1.5: Adicionando endereço\n");pause;
		add_address("adolfo@e-server.com",er);
	ler_end(er);
	printf("TESTE2.0: Criando config Adolfo\n");pause;
		create_config(0,er);
	printf("TESTE2.0: Criando config Ricardo\n");pause;
		create_config(1,er);


	printf("TESTE_FINAL\n");
	return 0;
}


//MUDANÇAS
