void sdeclaracao(int lex) {
	if(listalex[lex - 1].categoria != INTEIRO) {
		printf(" ERRO SINTÁTICO em '%s:%s':\n\t '%s' não é um tipo de variável válido\n", listalex[lex - 1].conteudo, listalex[lex + 1].conteudo, listalex[lex - 1].conteudo); outlex(lex); printf("\n");
		qtderrs++;
	}
	
	if(listalex[lex + 1].categoria != IDEN) {
		printf(" ERRO SINTÁTICO em '%s:%s':\n\t '%s' não é um nome válido para a variável\n", listalex[lex - 1].conteudo, listalex[lex + 1].conteudo, listalex[lex - 1].conteudo); outlex(lex); printf("\n");
		qtderrs++;
	}
	
	return;
}

void sfunc(int lex) {
	if(listalex[lex + 1].categoria != PARN) {
		printf(" ERRO SINTÁTICO na função %s: ausência de parênteses de abertura\n", listalex[lex].conteudo); outlex(lex); printf("\n");
		qtderrs++;
	}
	
	if(strcmp(listalex[lex].conteudo, "imprima") == 0) {
		switch(listalex[lex + 2].categoria) {
			case INTL:
			case STRL:
			case IDEN:
				break;
				
			default:
				printf(" ERRO SINTÁTICO na função %s: parâmetro incompatível com a função\n", listalex[lex].conteudo); outlex(lex); printf("\n");
				qtderrs++;
		}
	}
	else if(strcmp(listalex[lex].conteudo, "leia") == 0) {
		switch(listalex[lex + 2].categoria) {
			case IDEN:
				break;
				
			default:
				printf(" ERRO SINTÁTICO na função %s: parâmetro incompatível com a função\n", listalex[lex].conteudo); outlex(lex); printf("\n");
				qtderrs++;
		}
	}
	else {
		printf(" ERRO LÉXICO/SINTÁTICO na função %s: função desconhecida resulta em desconhecimento dos parâmetros esperados\n", listalex[lex].conteudo); outlex(lex); printf("\n");
		qtderrs++;
	}
	
	if(listalex[lex + 3].categoria != PARM) {
		if(listalex[lex + 3].categoria == VIRG) {
			printf(" ERRO SINTÁTICO na função %s: função não espera receber mais de um parâmetro\n", listalex[lex].conteudo); outlex(lex); printf("\n");
			qtderrs++;
		}
		
		for(int aux = lex + 3; listalex[aux].categoria != NEWL; aux++) {
			if(listalex[aux].categoria == PARM) return;
		}
		
		printf(" ERRO SINTÁTICO na função %s: ausência de parênteses de fechamento\n", listalex[lex].conteudo); outlex(lex); printf("\n");
		qtderrs++;
	}
}

void sif(int lex) {
	if(listalex[lex + 2].categoria != RELA && listalex[lex + 2].categoria != LOGI) {
		printf(" ERRO SINTÁTICO na condicional: esperava proposição lógica ou relacional como parâmetro\n", listalex[lex].conteudo); outlex(lex); printf("\n");
		qtderrs++;
	}
	
	if(listalex[lex + 4].categoria != ENTAO) {
		printf(" ERRO SINTÁTICO na condicional: esperava token 'entao'\n", listalex[lex].conteudo); outlex(lex + 4); printf("\n");
		qtderrs++;
	}
	
	int i = lex + 1, meta = 1;
	while(meta > 0) {
		if(listalex[i].categoria == SE) {
			meta++;
		}
		
		if(i > qtdlex) {
			printf(" ERRO SINTÁTICO na condicional: ausência de indicador de final 'fim_se'\n", listalex[lex].conteudo); outlex(lex); printf("\n");
			qtderrs++;
			break;
		}
		
		if(listalex[i].categoria == FIMSE) {
			meta--;
		}
		
		i++;
	}
}

void spara(int lex) {
	if(listalex[lex + 2].categoria != ATRI) {
		printf(" ERRO SINTÁTICO no laço: esperava atribuição como parâmetro\n", listalex[lex].conteudo); outlex(lex + 2); printf("\n");
		qtderrs++;
	}
	
	if(listalex[lex + 4].categoria != ATE) {
		printf(" ERRO SINTÁTICO no laço: esperava token 'ate'\n", listalex[lex].conteudo); outlex(lex + 4); printf("\n");
		qtderrs++;
	}
	
	if(listalex[lex + 5].categoria != INTL && listalex[lex + 5].categoria != IDEN) {
		printf(" ERRO SINTÁTICO no laço: esperava variável inteira ou inteiro literal\n", listalex[lex].conteudo); outlex(lex + 5); printf("\n");
		qtderrs++;
	}
	
	if(listalex[lex + 6].categoria != PASSO) {
		printf(" ERRO SINTÁTICO no laço: esperava token 'passo'\n", listalex[lex].conteudo); outlex(lex + 6); printf("\n");
		qtderrs++;
	}
	
	if(listalex[lex + 7].categoria != INTL && listalex[lex + 7].categoria != IDEN) {
		printf(" ERRO SINTÁTICO no laço: esperava variável inteira ou inteiro literal\n", listalex[lex].conteudo); outlex(lex + 7);printf("\n");
		qtderrs++;
	}
	
	int i = lex + 1, meta = 1;
	while(meta > 0) {
		if(listalex[i].categoria == PARA) {
			meta++;
		}
		
		if(i > qtdlex) {
			printf(" ERRO SINTÁTICO no laço: ausência de indicador de final 'fim_para'\n", listalex[lex].conteudo); outlex(lex); printf("\n");
			qtderrs++;
			break;
		}
		
		if(listalex[i].categoria == FIMPARA) {
			meta--;
		}
		
		i++;
	}
}
