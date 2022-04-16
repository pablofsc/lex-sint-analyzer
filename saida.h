void extenso(int tipo) {
	if(tipo >= 5 && tipo <= 19)  {
			printf("pal. reservada");
		return;
	}
	
	switch(tipo) {
		case SIM:
			printf("              ");
			break;
		
		case NAO:
			printf("(inválido)    ");
			break;
			
		case STRL:
			printf("string literal");
			break;
			
		case INTL:
			printf("int. literal  ");
			break;
			
		case ATRI:
			printf("op. atribuição");
			break;
			
		case RESR:
			printf("palavra reser.");
			break;
			
		case IDEN:
			printf("ident. #");
			break;
		
		case PARN:
			printf("parêntese abr.");
			break;
			
		case PARM:
			printf("parêntese fch.");
			break;
			
		case FUNC:
			printf("função        ");
			break;
		
		case DELI:
			printf("delimitador   ");
			break;
		
		case NEWL:
			printf("fim de linha  ");
			break;
			
		case INDE:
			printf("indic. indent.");
			break;
		
		case RELA:
			printf("op. relacional");
			break;
			
		case LOGI:
			printf("op. lógico    ");
			break;
			
		case ARIT:
			printf("op. aritmético");
			break;
		
		case DECL:
			printf("op. declaração");
			break;
		
		case INVL:
			printf("lex. inválido ");
			break;
		
		case VIRG:
			printf("separador     ");
			break;
		
		default:
			printf("??????????????");
			break;
	}
}

void tabela() {
	printf("\n------------------------ TABELA DE LEXEMAS ------------------------\n\n");
	printf("  L  |   #   | No | v |    descrição   |    conteúdo\n");
	
	for(int i = 0; i < qtdlex; i++) {
		outlex(i);
	}
	
	printf("\n\n");
}

void listaerroslex() {
	printf("--------------- MENSAGENS DO ANALISADOR LÉXICO --------------------\n\n");
	int i, qtderr = 0;
	for(i = 0; i < qtdlex; i++) {
		if(listalex[i].valido != SIM) {
			qtderr++;
			
			printf(" ERRO LÉXICO: %s:\n", listaerros[i]);
			
			outlex(i);
			
			if(listalex[i].categoria < 0) {
				//printf(" (%i)", listalex[i].conteudo[0]);
			}
			
			printf("\n\n");
		}
	}
	
	if(qtderr == 0) {
		printf("A análise léxica não encontrou erros.\n\n");
	}
}

void outlex(int i) {
	printf(" %3i | %05i | %2i | %c | ", listalex[i].linha, i, listalex[i].categoria, isvalid(listalex[i].valido));
	extenso(listalex[i].categoria);
	
	if(listalex[i].categoria == IDEN) {
		printf("%06i", numid(listalex[i].conteudo));
	}
		
	printf(" | %s\n", listalex[i].conteudo);
}
