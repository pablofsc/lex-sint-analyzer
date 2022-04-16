typedef int sn; // booleano
#define SIM 1
#define NAO 0

typedef int tipolexema;
#define STRT -3 // comeco do arquivo
#define ERRC -2 // erro de categoria
#define ARIT 91 // operador aritmetico
#define LOGI 92 // operador logico
#define RELA 93 // operador relacional
#define ATRI 94 // operador de atribuicao
#define PARN 95 // parenteses (
#define PARM 96 // parenteses )
#define DELI 99 // delimitador ;
#define DECL 80 // operador de declaracao
#define FUNC 70 // funcao
#define RESR 60 // palavra reservada
#define INTL 50 // inteiro literal
#define STRL 51 // string literal
#define INVL -1 // categoria invalida
#define IDEN 40 // identificador/variavel
#define INDE 35 // indicador de indentação
#define NEWL 30 // indicador de fim de linha
#define VIRG 85 // virgula

struct lexema {
	tipolexema categoria;
	char conteudo[128];
	sn valido;
	int linha;
};
typedef struct lexema lexema;

typedef int palavra_reservada;
#define INICIO 5
#define FIM 6
#define SE 11
#define ENTAO 12
#define SENAO 13
#define FIMSE 14
#define PARA 15
#define ATE 16
#define PASSO 17
#define FIMPARA 18
#define INTEIRO 19

char reservstr[32][64] = {"inicio", "fim", "se", "entao", "senao", "fim_se", "para", "ate", "passo", "fim_para", "inteiro"};
palavra_reservada reservint[32] = {INICIO, FIM, SE, ENTAO, SENAO, FIMSE, PARA, ATE, PASSO, FIMPARA, INTEIRO};

char funcoes[32][64] = {"imprima", "leia"};

typedef int id;

// TESTES DE TIPO
sn operadorarit(char caractere);
sn caracfim(char caractere);
sn reservada(char palavra[128]);
id numid(char nome[128]);
sn invalidoempalavra(char caractere);

// SAIDA
void extenso(int tipo);
void listaerroslex();
void tabela();
void outlex(int i);

// declarações 
FILE* fonte;
lexema listalex[4096];
lexema listavar[4096];
int qtdlex = 0, qtdvar = 0,  qtderrs;

char listaerros[4096][512];
int linhatual = 1;
