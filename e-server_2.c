/*
 * e-server.c
 *
 *  Created on: 11/01/2016
 *      Author: ricardo
 */
#include "functions_2_mail.h"
#include "functions_2_struct.h"
#define er "C:/Users/Ruan/Desktop/T/"
int main(void)
{
	int c;

	printf("TESTE0: Configurando servidor\n");
		setup(er);
	printf("TESTE1.0: Criando lista de endereços\n");
		create_address_list(er);
	printf("TESTE1.1: Adicionando endereço\n");
		add_address("ruanmed@e-server.com",er);
	printf("TESTE1.1: Adicionando endereço 2\n");
		add_address("ricardo@e-server.com",er);
	printf("TESTE1.2: Lendo endereço\n");
	printf("TESTE1.3: Removendo endereço\n");
	printf("TESTE_FINAL\n");
	return 0;
}


//MUDANÇAS
