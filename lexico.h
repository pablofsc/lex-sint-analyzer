void novavar(char nome[128]) {
	listavar[qtdvar].categoria = qtdvar;
	strcpy(listavar[qtdvar].conteudo, nome);
	listavar[qtdvar].valido = SIM;
	qtdvar++;
}

void registrar(tipolexema categoria, char conteudo[128], sn valido) {
	listalex[qtdlex].categoria = categoria;
	strcpy(listalex[qtdlex].conteudo, conteudo);
	listalex[qtdlex].valido = valido;
	qtdlex++;
	listalex[qtdlex].linha = linhatual;
}

void novastring() {
	char acumulador[128];
	int n = 0;
	sn valido = SIM;
	
	for(char caractere = fgetc(fonte); feof(fonte) == 0; caractere = fgetc(fonte)) {
		if(caractere == '\n') {
			strcpy(listaerros[qtdlex], "Ausência de aspas de fechamento na string");
			ungetc(caractere, fonte);
			valido = NAO;
			break;
		}
		
		if(caractere >= ' ' && caractere <= '~' && caractere != '"') {
			acumulador[n] = caractere;
			n++;
		}
		else if(caractere == '"') {
			acumulador[n] = '\0';
			break;
		}
		else {
			valido = NAO;
			strcpy(listaerros[qtdlex], "Caractere inválido na string literal");
		}
	}
	
	registrar(STRL, acumulador, valido);
}

void novointlit(char algarismo) {
	char acumulador[128];
	int n = 0;
	acumulador[0] = algarismo;
	n++;
	
	sn valido = SIM;
	
	for(char algarismo = fgetc(fonte); feof(fonte) == 0; algarismo = fgetc(fonte)) {
		if(algarismo >= '0' && algarismo <= '9') {
			acumulador[n] = algarismo;
			n++;
		}
		else if((algarismo >= 'A' && algarismo <= 'Z') || (algarismo >= 'a' && algarismo <= 'z')) {
			strcpy(listaerros[qtdlex], "Caractere inválido no inteiro literal");
			valido = NAO;
			ungetc(algarismo, fonte);
			break;
		}
		else if(operadorarit(algarismo) == SIM || caracfim(algarismo) == SIM) {
			ungetc(algarismo, fonte);
			break;
		}
	}
	
	acumulador[n] = '\0';
	registrar(INTL, acumulador, valido);
}

void novapalavra(char caractere) {
	char acumulador[128], aux;
	int n = 0;
	acumulador[0] = caractere;
	n++;
	
	sn valido = SIM;
	
	for(char caractere = fgetc(fonte); feof(fonte) == 0; caractere = fgetc(fonte)) {
		if(invalidoempalavra(caractere) == NAO) {
			acumulador[n] = caractere;
			n++;
		}
		else if(invalidoempalavra(caractere) == SIM && caracfim(caractere) == NAO) {
			ungetc(caractere, fonte);
			break;
		}
		else if(caracfim(caractere) == SIM) {
			ungetc(caractere, fonte);
			break;
		}
	}
	
	acumulador[n] = '\0';
	tipolexema tipo = reservada(acumulador);
	
	if(tipo == NAO) {
		if(listalex[qtdlex - 1].categoria == DECL) {
			tipo = IDEN;
			if(numid(acumulador) == -1) {
				novavar(acumulador);
			}
			else {
				valido = NAO;
			}
		}
		else if(numid(acumulador) != -1) {
			tipo = IDEN;
		}
		else {
			caractere = fgetc(fonte);
			ungetc(caractere, fonte);
			
			if(caractere == '(') {
				tipo = FUNC;
				
				if(funcaovalida(acumulador) == NAO) {
					valido = NAO;
					strcpy(listaerros[qtdlex], "Função não reconhecida");
				}
			}
			else {
				if(strcmp(acumulador, "E") == 0|| strcmp(acumulador, "OU") == 0|| strcmp(acumulador, "NAO") == 0) {
					tipo = LOGI;
				}
				else {
					aux = fgetc(fonte);
					ungetc(aux, fonte);
					
					if(aux == ':') {
						strcpy(listaerros[qtdlex], "Tipo de variável não existe");
					}
					else {
						strcpy(listaerros[qtdlex], "Variável não declarada");
					}
					
					tipo = INVL;
					valido = NAO;
				}
			}
		}
	}
	
	
	registrar(tipo, acumulador, valido);
}

void novoop(char caractere) {
	char acumulador[3] = {caractere, '\0', '\0'};
	sn valido = SIM;
	tipolexema tipo;
	
	if(caractere == '>' || caractere == '<' || caractere == '!') {
		acumulador[1] = fgetc(fonte);
		
		if(acumulador[1] == '=') {
			tipo = RELA;
		}
		else if(acumulador[1] == '-') {
			tipo = ATRI;
		}
		else {
			tipo = RELA;
			ungetc(acumulador[1], fonte);
			acumulador[1] = '\0';
		}
	}
	else if(caractere == '=') {
		tipo = RELA;
	}
	
	registrar(tipo, acumulador, valido);
}
