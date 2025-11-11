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
#define END          "0"




//Leitura de arquivo
int numeroValor = 0;
int numeroLinha = 1;

char* recuperaTipoDado(char *token){    

    if(strlen(token) == 1 && !isdigit(token[0])){
        char simbolos[15] = {'+', '-', '=', '*', '/', '(', ')', ';', ',', ':', '.', '>', '<', '{', '}'};
        char c = *token;
        
        for(int p = 0; p < strlen(simbolos); p++){
            if(c == simbolos[p]){
                printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
                switch(*token){
                case '+':       numeroValor ++; return MAIS; break;
                case '-':       numeroValor ++; return MENOS; break;
                case '=':       numeroValor ++; return IGUAL; break;
                case '*':       numeroValor ++; return MULT; break;
                case '/':       numeroValor ++; return DIV; break;
                case '(':       numeroValor ++; return LPAREN; break;
                case ')':       numeroValor ++; return RPAREN; break;
                case ';':       numeroValor ++; return PONTOVIRGULA; break;
                case ',':       numeroValor ++; return VIRGULA; break;
                case ':':       numeroValor ++; return DOISPONTOS; break;
                case '.':       numeroValor ++; return PONTO; break;
                case '>':       numeroValor ++; return MAIOR; break;
                case '<':       numeroValor ++; return MENOR; break;
                case '{':       numeroValor ++; return ABRECHAVE; break;
                case '}':       numeroValor ++; return FECHACHAVE; break;
                }
            }
        } 
    }

    if (isdigit(token[0]) || (token[0] == '.' && isdigit(token[1]))){
    char *temponto = strchr(token, '.');
    if (temponto != NULL) {
        printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
        numeroValor ++;
        return "REAL";
    } else {
        printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
        numeroValor ++;
        return "INTEIRO";
        }
    }

    if (strcmp(token, ":=") == 0) { 
        printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
        numeroValor++; 
        return DOISPONTOIGUAL;}
    else if (strcmp(token, ">=") == 0) { 
        printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
        numeroValor++; 
        return MAIORIGUAL;}
    else if (strcmp(token, "<=") == 0) { 
        printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
        numeroValor++; 
        return MENORIGUAL;}

    char *palavra = malloc(strlen(token)+1);
    char pontuacao = '\0';
    int j = 0;
    for(int i = 0; token[i] != '\0'; i++){
        if(isalpha(token[i]) || isdigit(token[i])){
            palavra[j++] = token[i];
        }else{
            pontuacao = token[i];
        }
    }
    palavra[j] = '\0';

    //printf("\n\npalavra: %s\npontuacao: %c\n\n", palavra, pontuacao);

    if (strcmp(palavra, "program") == 0) { 
        if(pontuacao == '\0'){
            printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
            numeroValor++; return PROGRAM;
        } else {
            printf("Linha[%d] - valor[%d] = '%s' -> Tipo de dado: %s\n", numeroLinha, numeroValor, palavra, PROGRAM);
            numeroValor++;
            printf("Linha[%d] - valor[%d] = '%c' -> ", numeroLinha, numeroValor, pontuacao);
            switch(pontuacao){
            case '+':       numeroValor ++; return MAIS; break;
            case '-':       numeroValor ++; return MENOS; break;
            case '=':       numeroValor ++; return IGUAL; break;
            case '*':       numeroValor ++; return MULT; break;
            case '/':       numeroValor ++; return DIV; break;
            case '(':       numeroValor ++; return LPAREN; break;
            case ')':       numeroValor ++; return RPAREN; break;
            case ';':       numeroValor ++; return PONTOVIRGULA; break;
            case ',':       numeroValor ++; return VIRGULA; break;
            case ':':       numeroValor ++; return DOISPONTOS; break;
            case '.':       numeroValor ++; return PONTO; break;
            case '>':       numeroValor ++; return MAIOR; break;
            case '<':       numeroValor ++; return MENOR; break;
            case '{':       numeroValor ++; return ABRECHAVE; break;
            case '}':       numeroValor ++; return FECHACHAVE; break;
            }
        }
    } else if (strcmp(palavra, "begin") == 0) {
            if(pontuacao == '\0'){
            printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
            numeroValor++; return BEGIN;
            } else {
                printf("Linha[%d] - valor[%d] = '%s' -> Tipo de dado: %s\n", numeroLinha, numeroValor, palavra, BEGIN);
                numeroValor++;
                printf("Linha[%d] - valor[%d] = '%c' -> ", numeroLinha, numeroValor, pontuacao);
            switch(pontuacao){
            case '+':       numeroValor ++; return MAIS; break;
            case '-':       numeroValor ++; return MENOS; break;
            case '=':       numeroValor ++; return IGUAL; break;
            case '*':       numeroValor ++; return MULT; break;
            case '/':       numeroValor ++; return DIV; break;
            case '(':       numeroValor ++; return LPAREN; break;
            case ')':       numeroValor ++; return RPAREN; break;
            case ';':       numeroValor ++; return PONTOVIRGULA; break;
            case ',':       numeroValor ++; return VIRGULA; break;
            case ':':       numeroValor ++; return DOISPONTOS; break;
            case '.':       numeroValor ++; return PONTO; break;
            case '>':       numeroValor ++; return MAIOR; break;
            case '<':       numeroValor ++; return MENOR; break;
            case '{':       numeroValor ++; return ABRECHAVE; break;
            case '}':       numeroValor ++; return FECHACHAVE; break;
            }
            }
            
        }
    else if (strcmp(palavra, "var") == 0) { 
        if(pontuacao == '\0'){
            printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
            numeroValor++; return VAR;
        } else {
            printf("Linha[%d] - valor[%d] = '%s' -> Tipo de dado: %s\n", numeroLinha, numeroValor, palavra, VAR);
            numeroValor++;
            printf("Linha[%d] - valor[%d] = '%c' -> ", numeroLinha, numeroValor, pontuacao);
            switch(pontuacao){
            case '+':       numeroValor ++; return MAIS; break;
            case '-':       numeroValor ++; return MENOS; break;
            case '=':       numeroValor ++; return IGUAL; break;
            case '*':       numeroValor ++; return MULT; break;
            case '/':       numeroValor ++; return DIV; break;
            case '(':       numeroValor ++; return LPAREN; break;
            case ')':       numeroValor ++; return RPAREN; break;
            case ';':       numeroValor ++; return PONTOVIRGULA; break;
            case ',':       numeroValor ++; return VIRGULA; break;
            case ':':       numeroValor ++; return DOISPONTOS; break;
            case '.':       numeroValor ++; return PONTO; break;
            case '>':       numeroValor ++; return MAIOR; break;
            case '<':       numeroValor ++; return MENOR; break;
            case '{':       numeroValor ++; return ABRECHAVE; break;
            case '}':       numeroValor ++; return FECHACHAVE; break;
            }
        }
     } else if (strcmp(palavra, "if") == 0) {
        if(pontuacao == '\0'){
            printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
            numeroValor++; return IF;
        } else {
            printf("Linha[%d] - valor[%d] = '%s' -> Tipo de dado: %s\n", numeroLinha, numeroValor, palavra, IF);
            numeroValor++;
            printf("Linha[%d] - valor[%d] = '%c' -> ", numeroLinha, numeroValor, pontuacao);
            switch(pontuacao){
            case '+':       numeroValor ++; return MAIS; break;
            case '-':       numeroValor ++; return MENOS; break;
            case '=':       numeroValor ++; return IGUAL; break;
            case '*':       numeroValor ++; return MULT; break;
            case '/':       numeroValor ++; return DIV; break;
            case '(':       numeroValor ++; return LPAREN; break;
            case ')':       numeroValor ++; return RPAREN; break;
            case ';':       numeroValor ++; return PONTOVIRGULA; break;
            case ',':       numeroValor ++; return VIRGULA; break;
            case ':':       numeroValor ++; return DOISPONTOS; break;
            case '.':       numeroValor ++; return PONTO; break;
            case '>':       numeroValor ++; return MAIOR; break;
            case '<':       numeroValor ++; return MENOR; break;
            case '{':       numeroValor ++; return ABRECHAVE; break;
            case '}':       numeroValor ++; return FECHACHAVE; break;
            }
        }
      } else if (strcmp(palavra, "else") == 0) {
        if(pontuacao == '\0'){
            printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
            numeroValor++; return ELSE;
        } else {
            printf("Linha[%d] - valor[%d] = '%s' -> Tipo de dado: %s\n", numeroLinha, numeroValor, palavra, ELSE);
            numeroValor++;
            printf("Linha[%d] - valor[%d] = '%c' -> ", numeroLinha, numeroValor, pontuacao);
            switch(pontuacao){
            case '+':       numeroValor ++; return MAIS; break;
            case '-':       numeroValor ++; return MENOS; break;
            case '=':       numeroValor ++; return IGUAL; break;
            case '*':       numeroValor ++; return MULT; break;
            case '/':       numeroValor ++; return DIV; break;
            case '(':       numeroValor ++; return LPAREN; break;
            case ')':       numeroValor ++; return RPAREN; break;
            case ';':       numeroValor ++; return PONTOVIRGULA; break;
            case ',':       numeroValor ++; return VIRGULA; break;
            case ':':       numeroValor ++; return DOISPONTOS; break;
            case '.':       numeroValor ++; return PONTO; break;
            case '>':       numeroValor ++; return MAIOR; break;
            case '<':       numeroValor ++; return MENOR; break;
            case '{':       numeroValor ++; return ABRECHAVE; break;
            case '}':       numeroValor ++; return FECHACHAVE; break;
            }
        }
       } else if (strcmp(palavra, "then") == 0) { 
        if(pontuacao == '\0'){
            printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
            numeroValor++; return THEN;
        } else {
            printf("Linha[%d] - valor[%d] = '%s' -> Tipo de dado: %s\n", numeroLinha, numeroValor, palavra, THEN);
            numeroValor++;
            printf("Linha[%d] - valor[%d] = '%c' -> ", numeroLinha, numeroValor, pontuacao);
            switch(pontuacao){
            case '+':       numeroValor ++; return MAIS; break;
            case '-':       numeroValor ++; return MENOS; break;
            case '=':       numeroValor ++; return IGUAL; break;
            case '*':       numeroValor ++; return MULT; break;
            case '/':       numeroValor ++; return DIV; break;
            case '(':       numeroValor ++; return LPAREN; break;
            case ')':       numeroValor ++; return RPAREN; break;
            case ';':       numeroValor ++; return PONTOVIRGULA; break;
            case ',':       numeroValor ++; return VIRGULA; break;
            case ':':       numeroValor ++; return DOISPONTOS; break;
            case '.':       numeroValor ++; return PONTO; break;
            case '>':       numeroValor ++; return MAIOR; break;
            case '<':       numeroValor ++; return MENOR; break;
            case '{':       numeroValor ++; return ABRECHAVE; break;
            case '}':       numeroValor ++; return FECHACHAVE; break;
            }
        }
        } else if (strcmp(palavra, "while") == 0) { 
        if(pontuacao == '\0'){
            printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
            numeroValor++; return WHILE;
        } else {
            printf("Linha[%d] - valor[%d] = '%s' -> Tipo de dado: %s\n", numeroLinha, numeroValor, palavra, WHILE);
            numeroValor++;
            printf("Linha[%d] - valor[%d] = '%c' -> ", numeroLinha, numeroValor, pontuacao);
            switch(pontuacao){
            case '+':       numeroValor ++; return MAIS; break;
            case '-':       numeroValor ++; return MENOS; break;
            case '=':       numeroValor ++; return IGUAL; break;
            case '*':       numeroValor ++; return MULT; break;
            case '/':       numeroValor ++; return DIV; break;
            case '(':       numeroValor ++; return LPAREN; break;
            case ')':       numeroValor ++; return RPAREN; break;
            case ';':       numeroValor ++; return PONTOVIRGULA; break;
            case ',':       numeroValor ++; return VIRGULA; break;
            case ':':       numeroValor ++; return DOISPONTOS; break;
            case '.':       numeroValor ++; return PONTO; break;
            case '>':       numeroValor ++; return MAIOR; break;
            case '<':       numeroValor ++; return MENOR; break;
            case '{':       numeroValor ++; return ABRECHAVE; break;
            case '}':       numeroValor ++; return FECHACHAVE; break;
            }
        }
         } else if (strcmp(palavra, "do") == 0) { 
        if(pontuacao == '\0'){
            printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
            numeroValor++; return DO;
        } else {
            printf("Linha[%d] - valor[%d] = '%s' -> Tipo de dado: %s\n", numeroLinha, numeroValor, palavra, DO);
            numeroValor++;
            printf("Linha[%d] - valor[%d] = '%c' -> ", numeroLinha, numeroValor, pontuacao);
            switch(pontuacao){
            case '+':       numeroValor ++; return MAIS; break;
            case '-':       numeroValor ++; return MENOS; break;
            case '=':       numeroValor ++; return IGUAL; break;
            case '*':       numeroValor ++; return MULT; break;
            case '/':       numeroValor ++; return DIV; break;
            case '(':       numeroValor ++; return LPAREN; break;
            case ')':       numeroValor ++; return RPAREN; break;
            case ';':       numeroValor ++; return PONTOVIRGULA; break;
            case ',':       numeroValor ++; return VIRGULA; break;
            case ':':       numeroValor ++; return DOISPONTOS; break;
            case '.':       numeroValor ++; return PONTO; break;
            case '>':       numeroValor ++; return MAIOR; break;
            case '<':       numeroValor ++; return MENOR; break;
            case '{':       numeroValor ++; return ABRECHAVE; break;
            case '}':       numeroValor ++; return FECHACHAVE; break;
            }
        }
          } else if (strcmp(palavra, "true") == 0) { 
        if(pontuacao == '\0'){
            printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
            numeroValor++; return TRUE;
        } else {
            printf("Linha[%d] - valor[%d] = '%s' -> Tipo de dado: %s\n", numeroLinha, numeroValor, palavra, TRUE);
            numeroValor++;
            printf("Linha[%d] - valor[%d] = '%c' -> ", numeroLinha, numeroValor, pontuacao);
            switch(pontuacao){
            case '+':       numeroValor ++; return MAIS; break;
            case '-':       numeroValor ++; return MENOS; break;
            case '=':       numeroValor ++; return IGUAL; break;
            case '*':       numeroValor ++; return MULT; break;
            case '/':       numeroValor ++; return DIV; break;
            case '(':       numeroValor ++; return LPAREN; break;
            case ')':       numeroValor ++; return RPAREN; break;
            case ';':       numeroValor ++; return PONTOVIRGULA; break;
            case ',':       numeroValor ++; return VIRGULA; break;
            case ':':       numeroValor ++; return DOISPONTOS; break;
            case '.':       numeroValor ++; return PONTO; break;
            case '>':       numeroValor ++; return MAIOR; break;
            case '<':       numeroValor ++; return MENOR; break;
            case '{':       numeroValor ++; return ABRECHAVE; break;
            case '}':       numeroValor ++; return FECHACHAVE; break;
            }
        }
           } else if (strcmp(palavra, "false") == 0) { 
            if(pontuacao == '\0'){
                printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
            numeroValor++; return FALSE;
        } else {
            printf("Linha[%d] - valor[%d] = '%s' -> Tipo de dado: %s\n", numeroLinha, numeroValor, palavra, FALSE);
            numeroValor++;
            printf("Linha[%d] - valor[%d] = '%c' -> ", numeroLinha, numeroValor, pontuacao);
            switch(pontuacao){
            case '+':       numeroValor ++; return MAIS; break;
            case '-':       numeroValor ++; return MENOS; break;
            case '=':       numeroValor ++; return IGUAL; break;
            case '*':       numeroValor ++; return MULT; break;
            case '/':       numeroValor ++; return DIV; break;
            case '(':       numeroValor ++; return LPAREN; break;
            case ')':       numeroValor ++; return RPAREN; break;
            case ';':       numeroValor ++; return PONTOVIRGULA; break;
            case ',':       numeroValor ++; return VIRGULA; break;
            case ':':       numeroValor ++; return DOISPONTOS; break;
            case '.':       numeroValor ++; return PONTO; break;
            case '>':       numeroValor ++; return MAIOR; break;
            case '<':       numeroValor ++; return MENOR; break;
            case '{':       numeroValor ++; return ABRECHAVE; break;
            case '}':       numeroValor ++; return FECHACHAVE; break;
            }
        }
            } else if (strcmp(palavra, "integer") == 0) { 
                if(pontuacao == '\0'){
                printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
                numeroValor++; return INTEGER;
        } else {
            printf("Linha[%d] - valor[%d] = '%s' -> Tipo de dado: %s\n", numeroLinha, numeroValor, palavra, INTEGER);
            numeroValor++;
            printf("Linha[%d] - valor[%d] = '%c' -> ", numeroLinha, numeroValor, pontuacao);
            switch(pontuacao){
            case '+':       numeroValor ++; return MAIS; break;
            case '-':       numeroValor ++; return MENOS; break;
            case '=':       numeroValor ++; return IGUAL; break;
            case '*':       numeroValor ++; return MULT; break;
            case '/':       numeroValor ++; return DIV; break;
            case '(':       numeroValor ++; return LPAREN; break;
            case ')':       numeroValor ++; return RPAREN; break;
            case ';':       numeroValor ++; return PONTOVIRGULA; break;
            case ',':       numeroValor ++; return VIRGULA; break;
            case ':':       numeroValor ++; return DOISPONTOS; break;
            case '.':       numeroValor ++; return PONTO; break;
            case '>':       numeroValor ++; return MAIOR; break;
            case '<':       numeroValor ++; return MENOR; break;
            case '{':       numeroValor ++; return ABRECHAVE; break;
            case '}':       numeroValor ++; return FECHACHAVE; break;
            }
        }
             } else if (strcmp(palavra, "real") == 0) { 
                if(pontuacao == '\0'){
                    printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
                    numeroValor++; return REAL;
                    } else {
                    printf("Linha[%d] - valor[%d] = '%s' -> Tipo de dado: %s\n", numeroLinha, numeroValor, palavra, REAL);
                    numeroValor++;
                    printf("Linha[%d] - valor[%d] = '%c' -> ", numeroLinha, numeroValor, pontuacao);
                    switch(pontuacao){
                    case '+':       numeroValor ++; return MAIS; break;
                    case '-':       numeroValor ++; return MENOS; break;
                    case '=':       numeroValor ++; return IGUAL; break;
                    case '*':       numeroValor ++; return MULT; break;
                    case '/':       numeroValor ++; return DIV; break;
                    case '(':       numeroValor ++; return LPAREN; break;
                    case ')':       numeroValor ++; return RPAREN; break;
                    case ';':       numeroValor ++; return PONTOVIRGULA; break;
                    case ',':       numeroValor ++; return VIRGULA; break;
                    case ':':       numeroValor ++; return DOISPONTOS; break;
                    case '.':       numeroValor ++; return PONTO; break;
                    case '>':       numeroValor ++; return MAIOR; break;
                    case '<':       numeroValor ++; return MENOR; break;
                    case '{':       numeroValor ++; return ABRECHAVE; break;
                    case '}':       numeroValor ++; return FECHACHAVE; break;
                        }
                    }
                }
    
    if(pontuacao == '\0'){
        printf("Linha[%d] - valor[%d] = '%s' -> ", numeroLinha, numeroValor, token);
        numeroValor ++;
        return VARIAVEL;
    } else {
            printf("Linha[%d] - valor[%d] = '%s' -> Tipo de dado: %s\n", numeroLinha, numeroValor, palavra, VARIAVEL);
            numeroValor++;
            printf("Linha[%d] - valor[%d] = '%c' -> ", numeroLinha, numeroValor, pontuacao);
            switch(pontuacao){
            case '+':       numeroValor ++; return MAIS; break;
            case '-':       numeroValor ++; return MENOS; break;
            case '=':       numeroValor ++; return IGUAL; break;
            case '*':       numeroValor ++; return MULT; break;
            case '/':       numeroValor ++; return DIV; break;
            case '(':       numeroValor ++; return LPAREN; break;
            case ')':       numeroValor ++; return RPAREN; break;
            case ';':       numeroValor ++; return PONTOVIRGULA; break;
            case ',':       numeroValor ++; return VIRGULA; break;
            case ':':       numeroValor ++; return DOISPONTOS; break;
            case '.':       numeroValor ++; return PONTO; break;
            case '>':       numeroValor ++; return MAIOR; break;
            case '<':       numeroValor ++; return MENOR; break;
            case '{':       numeroValor ++; return ABRECHAVE; break;
            case '}':       numeroValor ++; return FECHACHAVE; break;
            }
        }
}

void abrirarquivo(){
    const char nome_arquivo[] = "fonte.pas";
    FILE *ptr_file_in = fopen(nome_arquivo, "r");

    if (ptr_file_in == NULL)
    {
        printf("Erro ao abrir o arquivo: %s", nome_arquivo);
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), ptr_file_in))
    {
        linha[strcspn(linha, "\n")] = '\0';

        char *token;
        char *resultado;

        token = strtok(linha, " ");
        while (token != NULL) {
        char *resultado = recuperaTipoDado(token);
        printf("Tipo de dado: %s\n", resultado);
        token = strtok(NULL, " ");
        }

        numeroLinha ++;
        printf("\n");
        numeroValor = 0;
    }
    

    /*
    1 - Ler arquivo (.pas) identificando todos os TOKENS
    2 - Gerar arquivo (.lex) contendo todos os TOKENS identificados
    3 - Ler arquivo (.lex) construindo a arvore sintatica a cada TOKEN
    */
    
    fclose(ptr_file_in);
}