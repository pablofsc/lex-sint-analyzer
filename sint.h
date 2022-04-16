void sdeclaracao(int lex) {
	if(listalex[lex - 1].categoria != INTEIRO) {
		printf(" ERRO SINT�TICO em '%s:%s':\n\t '%s' n�o � um tipo de vari�vel v�lido\n", listalex[lex - 1].conteudo, listalex[lex + 1].conteudo, listalex[lex - 1].conteudo); outlex(lex); printf("\n");
		qtderrs++;
	}
	
	if(listalex[lex + 1].categoria != IDEN) {
		printf(" ERRO SINT�TICO em '%s:%s':\n\t '%s' n�o � um nome v�lido para a vari�vel\n", listalex[lex - 1].conteudo, listalex[lex + 1].conteudo, listalex[lex - 1].conteudo); outlex(lex); printf("\n");
		qtderrs++;
	}
	
	return;
}

void sfunc(int lex) {
	if(listalex[lex + 1].categoria != PARN) {
		printf(" ERRO SINT�TICO na fun��o %s: aus�ncia de par�nteses de abertura\n", listalex[lex].conteudo); outlex(lex); printf("\n");
		qtderrs++;
	}
	
	if(strcmp(listalex[lex].conteudo, "imprima") == 0) {
		switch(listalex[lex + 2].categoria) {
			case INTL:
			case STRL:
			case IDEN:
				break;
				
			default:
				printf(" ERRO SINT�TICO na fun��o %s: par�metro incompat�vel com a fun��o\n", listalex[lex].conteudo); outlex(lex); printf("\n");
				qtderrs++;
		}
	}
	else if(strcmp(listalex[lex].conteudo, "leia") == 0) {
		switch(listalex[lex + 2].categoria) {
			case IDEN:
				break;
				
			default:
				printf(" ERRO SINT�TICO na fun��o %s: par�metro incompat�vel com a fun��o\n", listalex[lex].conteudo); outlex(lex); printf("\n");
				qtderrs++;
		}
	}
	else {
		printf(" ERRO L�XICO/SINT�TICO na fun��o %s: fun��o desconhecida resulta em desconhecimento dos par�metros esperados\n", listalex[lex].conteudo); outlex(lex); printf("\n");
		qtderrs++;
	}
	
	if(listalex[lex + 3].categoria != PARM) {
		if(listalex[lex + 3].categoria == VIRG) {
			printf(" ERRO SINT�TICO na fun��o %s: fun��o n�o espera receber mais de um par�metro\n", listalex[lex].conteudo); outlex(lex); printf("\n");
			qtderrs++;
		}
		
		for(int aux = lex + 3; listalex[aux].categoria != NEWL; aux++) {
			if(listalex[aux].categoria == PARM) return;
		}
		
		printf(" ERRO SINT�TICO na fun��o %s: aus�ncia de par�nteses de fechamento\n", listalex[lex].conteudo); outlex(lex); printf("\n");
		qtderrs++;
	}
}

void sif(int lex) {
	if(listalex[lex + 2].categoria != RELA && listalex[lex + 2].categoria != LOGI) {
		printf(" ERRO SINT�TICO na condicional: esperava proposi��o l�gica ou relacional como par�metro\n", listalex[lex].conteudo); outlex(lex); printf("\n");
		qtderrs++;
	}
	
	if(listalex[lex + 4].categoria != ENTAO) {
		printf(" ERRO SINT�TICO na condicional: esperava token 'entao'\n", listalex[lex].conteudo); outlex(lex + 4); printf("\n");
		qtderrs++;
	}
	
	int i = lex + 1, meta = 1;
	while(meta > 0) {
		if(listalex[i].categoria == SE) {
			meta++;
		}
		
		if(i > qtdlex) {
			printf(" ERRO SINT�TICO na condicional: aus�ncia de indicador de final 'fim_se'\n", listalex[lex].conteudo); outlex(lex); printf("\n");
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
		printf(" ERRO SINT�TICO no la�o: esperava atribui��o como par�metro\n", listalex[lex].conteudo); outlex(lex + 2); printf("\n");
		qtderrs++;
	}
	
	if(listalex[lex + 4].categoria != ATE) {
		printf(" ERRO SINT�TICO no la�o: esperava token 'ate'\n", listalex[lex].conteudo); outlex(lex + 4); printf("\n");
		qtderrs++;
	}
	
	if(listalex[lex + 5].categoria != INTL && listalex[lex + 5].categoria != IDEN) {
		printf(" ERRO SINT�TICO no la�o: esperava vari�vel inteira ou inteiro literal\n", listalex[lex].conteudo); outlex(lex + 5); printf("\n");
		qtderrs++;
	}
	
	if(listalex[lex + 6].categoria != PASSO) {
		printf(" ERRO SINT�TICO no la�o: esperava token 'passo'\n", listalex[lex].conteudo); outlex(lex + 6); printf("\n");
		qtderrs++;
	}
	
	if(listalex[lex + 7].categoria != INTL && listalex[lex + 7].categoria != IDEN) {
		printf(" ERRO SINT�TICO no la�o: esperava vari�vel inteira ou inteiro literal\n", listalex[lex].conteudo); outlex(lex + 7);printf("\n");
		qtderrs++;
	}
	
	int i = lex + 1, meta = 1;
	while(meta > 0) {
		if(listalex[i].categoria == PARA) {
			meta++;
		}
		
		if(i > qtdlex) {
			printf(" ERRO SINT�TICO no la�o: aus�ncia de indicador de final 'fim_para'\n", listalex[lex].conteudo); outlex(lex); printf("\n");
			qtderrs++;
			break;
		}
		
		if(listalex[i].categoria == FIMPARA) {
			meta--;
		}
		
		i++;
	}
}
