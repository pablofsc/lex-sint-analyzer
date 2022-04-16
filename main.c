/* 
Trabalho de conclusão de disciplina

27 de novembro de 2020
Engenharia de Computação - 6º semestre
Compiladores
*/

// Requer a flag -std=gnu11 para compilação apropriada

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

#include "declaracoes.h"
#include "testadores.h"
#include "lexico.h"
#include "saida.h"
#include "sint.h"

int main() {
	setlocale(LC_ALL, "portuguese");
	
	char nomearquivo[64];
	
	do {
		//printf("Insira o nome do arquivo: ");
		//scanf("%s", nomearquivo);
	
		fonte = fopen("prog.ptgol", "r");
	} while(fonte == NULL && printf("Erro: não foi possível abrir o arquivo '%s'\n\n", nomearquivo));
	
	char caractere;
	for(caractere = fgetc(fonte); feof(fonte) == 0; caractere = fgetc(fonte)) { //printf("%c", caractere);	
		char enviar[2] = {caractere, '\0'};
		
		if(caractere == '"') {
			novastring();
		}
		else if(caractere >= '0' && caractere <= '9') {
			novointlit(caractere);
		}
		else if((caractere >= 'A' && caractere <= 'Z') || (caractere >= 'a' && caractere <= 'z')) {
			novapalavra(caractere);
		}
		else if(caractere == ':') {
			registrar(DECL, enviar, SIM);
		}
		else if(caractere == '(') {
			registrar(PARN, enviar, SIM);
		}
		else if(caractere == ')') {
			registrar(PARM, enviar, SIM);
		}
		else if(caractere == ';') {
			registrar(DELI, enviar, SIM);
		}
		else if(caractere == ',') {
			registrar(VIRG, enviar, SIM);
		}
		else if(caractere == '\n') {
			linhatual++;
			registrar(NEWL, enviar, SIM);
		}
		else if(caractere == '\t') {
			if(listalex[qtdlex - 1].categoria == NEWL || listalex[qtdlex - 1].categoria == INDE) {
				registrar(INDE, enviar, SIM);
			}
			else {
				registrar(INDE, enviar, NAO);
				strcpy(listaerros[qtdlex], "Indicador de indentação em local inválido");
			}
		}
		else if(caractere == ' ') {
			continue;
		}
		else if(arit(enviar) == SIM) {
			registrar(ARIT, enviar, SIM);
		}
		else if(inicioop(caractere) == SIM) {
			novoop(caractere);
		}
		else {
			strcpy(listaerros[qtdlex], "Lexema inválido ou não reconhecido");
			registrar(INVL, enviar, NAO);
		}
	}
	
	tabela();
	listaerroslex();
	
	fclose(fonte);
	
	printf("-------------- MENSAGENS DO ANALISADOR SINTÁTICO ------------------\n\n");
	
	int lexema;
	tipolexema tipo, tipoant = STRT;
	for(lexema = 0; lexema < qtdlex; lexema++) {
		tipo = listalex[lexema].categoria;
		
		if(tipo == DECL) {
			sdeclaracao(lexema);
		}
		else if(tipo == FUNC) {
			sfunc(lexema);
		}
		else if(tipo == SE) {
			sif(lexema);
		}
		else if(tipo == PARA) {
			spara(lexema);
		}
	}
	
	if(qtderrs == 0) {
		printf("A análise sintática não encontrou erros.\n\n");
	}
	
	getchar();
}
