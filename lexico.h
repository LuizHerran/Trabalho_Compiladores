#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAIS         "OPERADOR MATEMATICO DE SOMA"
#define MENOS        "OPERADOR MATEMATICO DE SUBTRACAO"
#define IGUAL        "IGUAL"
#define MULT         "OPERADOR MATEMATICO DE MULTIPLICACAO"
#define DIV          "OPERADOR MATEMATICO DE DIVISAO"
#define LPAREN       "ABRE PARENTESES"
#define RPAREN       "FECHA PARENTESES"
#define INT          "INTEIRO"
#define FLOAT        "REAL"
#define PONTOVIRGULA "PONTO E VIRGULA"
#define VIRGULA      "VIRGULA"
#define DOISPONTOS   "DOIS PONTOS"
#define PONTO        "PONTO"
#define MAIOR        "MAIOR QUE"
#define MENOR        "MENOR QUE"
#define PROGRAM      "PALAVRA RESERVADA: program"
#define VARIAVEL     "VARIAVEL"
#define BEGIN        "PALAVRA RESERVADA: begin"
#define VAR          "PALAVRA RESERVADA: var"
#define IF           "PALAVRA RESERVADA: if"
#define ELSE         "PALAVRA RESERVADA: else"
#define THEN         "PALAVRA RESERVADA: then"
#define WHILE        "PALAVRA RESERVADA: while"
#define DO           "PALAVRA RESERVADA: do"
#define TRUE         "OPERADOR BOOLEANO: true"
#define FALSE        "OPERADOR BOOLEANO: false"
#define ABRECHAVE   "ABRE CHAVE"
#define FECHACHAVE  "FECHA CHAVE"
#define DOISPONTOIGUAL "DOIS PONTOS E IGUAL"
#define MAIORIGUAL     "MAIOR OU IGUAL"
#define MENORIGUAL     "MENOR OU IGUAL"
#define INTEGER        "PALAVRA RESERVADA: integer"
#define REAL        "PALAVRA RESERVADA: real"
#define FIM
#define ERRO         "ERRO"
#define END          "PALAVRA RESERVADA: end"

typedef struct{
    char *palavraReservada;
    int   num;
    float real;
    char *variavel;
    char  simbolo;
    char  *simbolos;
}leituraDeLinha[4095];
leituraDeLinha tk;
int contador = 0;

//Leitura de arquivo
int numeroValor = 0;
int numeroLinha = 1;
int verificador = 0;
char linha[256];

//Identifica o caracter ou palavra e armazena em leituraDeLinha
char* recuperaTipoDado(char *token, leituraDeLinha tk){  
    printf("\nLeitura{recuperarTipoDado} token = %s\n", token);

    //Verifica se ele é um simbolo
    if(strlen(token) == 1 && !isdigit(token[0])){
        char simbolos[15] = {'+', '-', '=', '*', '/', '(', ')', ';', ',', ':', '.', '>', '<', '{', '}'};
        char c = *token;
        
        for(int p = 0; p < strlen(simbolos); p++){
            if(c == simbolos[p]){
                printf("Verificacao de simbolo de recuperarDado = %c\n", c);
                printf("Linha[%d] - valor[%d] = '%c' -> ", numeroLinha, numeroValor, c);
                switch(c){
                    case '+':       numeroValor ++; tk[contador].simbolo = c; contador++; return MAIS; break;
                    case '-':       numeroValor ++; tk[contador].simbolo = c; contador++; return MENOS; break;
                    case '=':       numeroValor ++; tk[contador].simbolo = c; contador++; return IGUAL; break;
                    case '*':       numeroValor ++; tk[contador].simbolo = c; contador++; return MULT; break;
                    case '/':       numeroValor ++; tk[contador].simbolo = c; contador++; return DIV; break;
                    case '(':       numeroValor ++; tk[contador].simbolo = c; contador++; return LPAREN; break;
                    case ')':       numeroValor ++; tk[contador].simbolo = c; contador++; return RPAREN; break;
                    case ';':       numeroValor ++; tk[contador].simbolo = c; contador++; return PONTOVIRGULA; break;
                    case ',':       numeroValor ++; tk[contador].simbolo = c; contador++; return VIRGULA; break;
                    case ':':       numeroValor ++; tk[contador].simbolo = c; contador++; return DOISPONTOS; break;
                    case '.':       numeroValor ++; tk[contador].simbolo = c; contador++; return PONTO; break;
                    case '>':       numeroValor ++; tk[contador].simbolo = c; contador++;; return MAIOR; break;
                    case '<':       numeroValor ++; tk[contador].simbolo = c; contador++; return MENOR; break;
                    case '{':       numeroValor ++; tk[contador].simbolo = c; contador++; return ABRECHAVE; break;
                    case '}':       numeroValor ++; tk[contador].simbolo = c; contador++; return FECHACHAVE; break;
                    default: return ERRO;    
                }
            }
        } 
    }

        //verifica se ele é um simbolo de 2 caracteres
    if (strcmp(token, ":=") == 0) { 
        printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
        numeroValor++; 
        tk[contador].simbolos = strdup(token);
        contador++;
        return DOISPONTOIGUAL;
    } else if (strcmp(token, ">=") == 0) { 
        printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
        numeroValor++; 
        tk[contador].simbolos = strdup(token);
        contador++;
        return MAIORIGUAL;}
    else if (strcmp(token, "<=") == 0) { 
        printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
        numeroValor++; 
        tk[contador].simbolos = strdup(token);
        contador++;
        return MENORIGUAL;
    } else if (strcmp(token, "==") == 0) { 
        printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
        numeroValor++; 
        tk[contador].simbolos = strdup(token);
        contador++;
        return MENORIGUAL;
    } else if (strcmp(token, "!=") == 0) { 
        printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
        numeroValor++; 
        tk[contador].simbolos = strdup(token);
        contador++;
        return MENORIGUAL;}


    //Verifica se ele é um número e se é inteiro ou real
    if (isdigit(token[0]) || (token[0] == '.' && isdigit(token[1]))){
        printf("Verificaao de numero em recuperarDado = %s entrada\n", token);
    char *temponto = strchr(token, '.');
    if (temponto != NULL) {
        printf("Verificaao de numero em recuperarDado = %s saida real\n", token);
        printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
        numeroValor ++;
        tk[contador].real = atof(token);
        contador++;
        return "REAL";
    } else {
        printf("Verificaao de numero em recuperarDado = %s saida inteiro\n", token);
        printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
        numeroValor ++;
        tk[contador].num = atoi(token);
        contador++;
        return "INTEIRO";
        }
    }

    //Verifica as palavras reservadas
    if (strcmp(token, "program") == 0) { 
        
            printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
            tk[contador].palavraReservada = strdup(token);
            contador++;
            numeroValor++; 
            return PROGRAM;
        
    } else if (strcmp(token, "begin") == 0) {
            
            tk[contador].palavraReservada = strdup(token);
            contador++;
            printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
            numeroValor++; 
            return BEGIN;
            
     } else if (strcmp(token, "var") == 0) { 
        
            tk[contador].palavraReservada = strdup(token);
            contador++;
            printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
            numeroValor++; return VAR;
        
      } else if (strcmp(token, "if") == 0) {
        
            tk[contador].palavraReservada = strdup(token);
            contador++;
            printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
            numeroValor++; return IF;
        
       } else if (strcmp(token, "else") == 0) {
            
            tk[contador].palavraReservada = strdup(token);
            contador++;
            printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
            numeroValor++; return ELSE;
            
        } else if (strcmp(token, "then") == 0) { 
            
                tk[contador].palavraReservada = strdup(token);
                contador++;
            printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
            numeroValor++; return THEN;
            
         } else if (strcmp(token, "while") == 0) { 
            
                tk[contador].palavraReservada = strdup(token);
                contador++;
                printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
                numeroValor++; return WHILE;
            
          } else if (strcmp(token, "do") == 0) { 
                
                    tk[contador].palavraReservada = strdup(token);
                    contador++;
                printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
                numeroValor++; return DO;
                
           } else if (strcmp(token, "true") == 0) { 
                
                    tk[contador].palavraReservada = strdup(token);
                    contador++;
                printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
                numeroValor++; return TRUE;
                
            } else if (strcmp(token, "false") == 0) { 
                
                    tk[contador].palavraReservada = strdup(token);
                    contador++;
                printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
                numeroValor++; return FALSE;
                
             } else if (strcmp(token, "integer") == 0) { 
                
                    tk[contador].palavraReservada = strdup(token);
                    contador++;
                printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
                numeroValor++; return INTEGER;
                
              } else if (strcmp(token, "real") == 0) { 
                
                    tk[contador].palavraReservada = strdup(token);
                    contador++;
                    printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
                    numeroValor++; return REAL;
                } else if (strcmp(token, "end") == 0) { 
                    tk[contador].palavraReservada = strdup(token);
                    contador++;
                    printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
                    numeroValor++; return END;
                }
                    tk[contador].variavel = strdup(token);
                    contador++;
                    printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
                    numeroValor ++;
                    return VARIAVEL;       
}

void separaSimbolos(char *token) {

    printf("\ntoken = %s\n", token);
    
    const char simbolos_simples[] = {"+-*/})({}:,;<>="};
    char temp[512];
    int j = 0;

    for (int i = 0; token[i] != '\0'; i++) {
        if (token[i+1] != '\0') {
            if ((token[i] == ':' && token[i+1] == '=') || (token[i] == '<' && token[i+1] == '=') ||
                (token[i] == '>' && token[i+1] == '=') || (token[i] == '=' && token[i+1] == '=')) {
                temp[j++] = ' ';
                temp[j++] = token[i];
                temp[j++] = token[i+1];
                printf("\n simbolos = %c%c\n", token[i], token[i+1]);
                temp[j++] = ' ';
                i++; 
                continue;
            }
        }

        if (strchr(simbolos_simples, token[i]) != NULL) {
            temp[j++] = ' ';
            temp[j++] = token[i];
            printf("\n simbolo = %c\n", token[i]);
            temp[j++] = ' ';
        } else {
            temp[j++] = token[i];
            printf("\npalavra else = %c\n", token[i]);
        }
    }
    temp[j] = '\0';

    int i = 0;
    printf("\ntemp = ");
    while(temp[i] != 0){
        printf("%c", temp[i]);
        i++;
    }
    printf("\n");
    i = 0;
    
    char *aux = strtok(temp, " \t\n\r");
    printf("primeira leitura de AUX = %s\n", aux);
    
    while (temp[i] != '\0') {
        //2 não cai no if
        if (strlen(aux) > 0) {
            char *resultado = recuperaTipoDado(aux, tk);
            printf("Tipo de dado: %s\n", resultado);
        }
        aux = strtok(NULL, " \t\n\r");
        printf("\nleitura[%d] de AUX = %s\n", i, aux);
        i++;
    }
}


void abrirarquivo(){
    const char nome_arquivo[] = "fonte.pas";
    FILE *ptr_file_in = fopen(nome_arquivo, "r");

    if (ptr_file_in == NULL){
        printf("Erro ao abrir o arquivo: %s", nome_arquivo);
        return;
    }

    while (fgets(linha, sizeof(linha), ptr_file_in)){
        linha[strcspn(linha, "\r\n")] = '\0';

        char *token = strtok(linha, " ");
        while (token != NULL) {
            separaSimbolos(token);
            token = strtok(NULL, " ");
        }

        numeroLinha++;
        printf("\n");
        numeroValor = 0;
    }
    fclose(ptr_file_in);
}


void lerStruct(leituraDeLinha tk){
    
    for (int k = 0; k < contador; k++) {
        if (tk[k].palavraReservada != NULL) {
            printf("Valor[%d] - %s - Palavra reservada!\n", k, tk[k].palavraReservada);
        } 
        else if (tk[k].variavel != NULL) {
            printf("Valor[%d] - %s - Variavel!\n", k, tk[k].variavel);
        } 
        else if (tk[k].simbolos != NULL) {
            printf("Valor[%d] - %s - Simbolo duplo!\n", k, tk[k].simbolos);
        } 
        else if (tk[k].simbolo != 0) {
            printf("Valor[%d] - %c - Simbolo simples!\n", k, tk[k].simbolo);
        } 
        else if (tk[k].real != 0.0f) {
            printf("Valor[%d] - %.2f - Numero real!\n", k, tk[k].real);
        } 
        else {
            printf("Valor[%d] - %d - Numero inteiro!\n", k, tk[k].num);
        }
    }
}


 /*
    1 - Ler arquivo (.pas) identificando todos os TOKENS
    2 - Gerar arquivo (.lex) contendo todos os TOKENS identificados
    3 - Ler arquivo (.lex) construindo a arvore sintatica a cada TOKEN
    */