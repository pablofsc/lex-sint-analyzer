sn operadorarit(char caractere) {
	if(caractere >= '(' && caractere <= '-') return SIM;
	else return NAO;
}

sn caracfim(char caractere) {
	switch(caractere) {
		case ' ':
		case '\n':
			return SIM;
			
		default:
			return NAO;
	} 
}

sn reservada(char palavra[128]) {
	int i;
	for(i = 0; i <= 32; i++) {
		if(strcmp(palavra, reservstr[i]) == 0) {
			return reservint[i];
		}
	}
	
	return NAO;
}

id numid(char nome[128]) {
	int i;
	for(i = 0; i <= qtdvar; i++) {
		if(strcmp(nome, listavar[i].conteudo) == 0) {
			return listavar[i].categoria;
		}
	}
	
	return(-1);
}

sn invalidoempalavra(char caractere) {
	if(caractere >= '\0' && caractere <= '/') return SIM;
	else if(caractere >= ':' && caractere <= '@') return SIM;
	else if(caractere >= '[' && caractere <= '`' && caractere != '_') return SIM;
	else if(caractere >= '{' && caractere <= '~') return SIM;
	else return NAO;
}

sn funcaovalida(char f[]) {
	int i;
	for(i = 0; i <= 1; i++) {
		if(strcmp(funcoes[i], f) == 0) return SIM;
	}
	
	return NAO;
}

sn arit(char op[]) {
	if(strcmp(op, "+") == 0) return SIM;
	if(strcmp(op, "-") == 0) return SIM;
	if(strcmp(op, "/") == 0) return SIM;
	if(strcmp(op, "*") == 0) return SIM;
	
	return NAO;
}

sn inicioop(char caractere) {
	switch(caractere) {
		case '>':
		case '<':
		case '=':
		case '!':
			return SIM;
			
		default:
			return NAO;
	}
}

char isvalid(sn valido) {
	switch(valido) {
		case SIM:
			return ' ';
			
		case NAO:
			return 'X';
	}
}
