#include "lexico.h"

#define TOKEN_MAIS         "+"
#define TOKEN_MENOS        "-"
#define TOKEN_IGUAL        "="
#define TOKEN_MULT         "*"
#define TOKEN_DIV          "/"
#define TOKEN_LPAREN       "("
#define TOKEN_RPAREN       ")"
#define TOKEN_INT          "NUM_INT: "
#define TOKEN_FLOAT        "NUM_REAL: "
#define TOKEN_PONTOVIRGULA ";"
#define TOKEN_VIRGULA      ","
#define TOKEN_DOISPONTOS   ":"
#define TOKEN_PONTO        "."
#define TOKEN_MAIOR        ">"
#define TOKEN_MENOR        "<"
#define TOKEN_PROGRAM      "program"
#define TOKEN_VARIAVEL     "VARIAVEL"
#define TOKEN_BEGIN        "begin"
#define TOKEN_VAR          "var"
#define TOKEN_IF           "if"
#define TOKEN_ELSE         "else"
#define TOKEN_THEN         "then"
#define TOKEN_WHILE        "while"
#define TOKEN_DO           "do"
#define TOKEN_TRUE         "true"
#define TOKEN_FALSE        "false"
#define TOKEN_ABRECHAVE    "{"
#define TOKEN_FECHACHAVE   "}"
#define TOKEN_DOISPONTOIGUAL ":="
#define TOKEN_MAIORIGUAL     ">="
#define TOKEN_MENORIGUAL     "<="
#define TOKEN_INTEGER        "integer"
#define TOKEN_REAL           "real"
#define TOKEN_FIM
#define TOKEN_ERRO         "ERRO"
#define TOKEN_END          "END"

//VERIFICAÇÃO SE UMA VARIAVEL ATENDE: COMEÇAR COM LETRA ------------------------------------------------

void comandoComposto(){

}

//lista de identificadores
void listaDeIdentificadores(leituraDeLinha tk, int lugar){
    if(tk[lugar].simbolo == ','){
        printf("Simbolo-[%c] - ", tk[lugar].simbolo);
        declaracaoDeVariavel(tk, (lugar+1));
    } else {
        //Verifica se o proximo caracter é :
        if(tk[lugar].simbolo == ':'){
            //Verifica se o proximo caracter é um tipo
            if(tk[lugar+1].palavraReservada == TOKEN_INTEGER || tk[lugar+1].palavraReservada == TOKEN_REAL){
                printf("Palavra reservada-[%s] - ");

            } else {
                //Se não for um tipo
                printf("Erro de Syntax: 'TIPO' esperada no lugar de: !\n\n");
                //Mostra oq foi escrito no lugar
                for(int k = (lugar+1); k < (lugar+2); k++) {
                    if (tk[k].palavraReservada != NULL) {
                        printf("palavra Reservada-[%s] - ", tk[k].palavraReservada);
                        } 
                        else if (tk[k].variavel != NULL) {
                            printf("Variavel-[%s] - ", tk[k].variavel);
                        } 
                        else if (tk[k].simbolos != NULL) {
                            printf("Simbolo Duplo-[%s] - ", tk[k].simbolos);
                        } 
                        else if (tk[k].simbolo != 0) {
                            printf("Simbolo simples-[%c] - ", k, tk[k].simbolo);
                        } 
                        else if (tk[k].real != 0.0f) {
                            printf("Numero Real[%.2f] - ", k, tk[k].real);
                        } 
                        else {
                            printf("Numero inteiro-[%d] - ", k, tk[k].num);
                        }
            }
            }
        }
    }
}

//Declaração de variavel
declaracaoDeVariavel(leituraDeLinha tk, int lugar){

    //verifica se é uma variavel:
    if (tk[lugar].variavel != NULL) {
            printf("Variavel-[%s] - ", tk[lugar].variavel);
        }else{
            printf("Erro de Syntax: 'variavel' esperada no lugar de: !\n\n");
            //Mostra oq foi escrito no lugar
            for(int k = lugar; k < (lugar+1); k++) {
                if (tk[k].palavraReservada != NULL) {
                    printf("palavra Reservada-[%s] - ", tk[k].palavraReservada);
                    } 
                    else if (tk[k].variavel != NULL) {
                        printf("Variavel-[%s] - ", tk[k].variavel);
                    } 
                    else if (tk[k].simbolos != NULL) {
                        printf("Simbolo Duplo-[%s] - ", tk[k].simbolos);
                    } 
                    else if (tk[k].simbolo != 0) {
                        printf("Simbolo simples-[%c] - ", k, tk[k].simbolo);
                    } 
                    else if (tk[k].real != 0.0f) {
                        printf("Numero Real[%.2f] - ", k, tk[k].real);
                    } 
                    else {
                        printf("Numero inteiro-[%d] - ", k, tk[k].num);
                    }
            }
        }

    //Verifica se tem , e mais possiveis variaveis:
    listaDeIdentificadores(tk, (lugar+1));

    }

//Parte de declaração de variáveis
void parteDeclaracaoDeVariaveis(leituraDeLinha tk, int lugar){

    //Verificar se começa com var:
    if (tk[lugar].palavraReservada != NULL) {
            printf("Palavra Reservada-[%s] - ", tk[lugar].palavraReservada);
        }else{
            printf("Erro de Syntax: 'Var' esperada no lugar de: !\n\n");
            //Mostra oq foi escrito no lugar
            for(int k = lugar; k < (lugar+1); k++) {
                if (tk[k].palavraReservada != NULL) {
                    printf("palavra Reservada-[%s] - ", tk[k].palavraReservada);
                    } 
                    else if (tk[k].variavel != NULL) {
                        printf("Variavel-[%s] - ", tk[k].variavel);
                    } 
                    else if (tk[k].simbolos != NULL) {
                        printf("Simbolo Duplo-[%s] - ", tk[k].simbolos);
                    } 
                    else if (tk[k].simbolo != 0) {
                        printf("Simbolo simples-[%c] - ", k, tk[k].simbolo);
                    } 
                    else if (tk[k].real != 0.0f) {
                        printf("Numero Real[%.2f] - ", k, tk[k].real);
                    } 
                    else {
                        printf("Numero inteiro-[%d] - ", k, tk[k].num);
                    }
            }
        }

    //verifica se em seguida vem uma ou mais variaveis
    declaracaoDeVariavel(tk, (lugar +1));
    //Verificar se o proximo é ; se não cabo

}

void bloco(){
    //parte de declaração de variaveis
    parteDeclaracaoDeVariaveis();
    //comando composto
    comandoComposto();
}
//Verifica se é uma variavel
void identificador(leituraDeLinha tk, int lugar){

    if (tk[lugar].variavel != NULL) {
            printf("Variavel-[%s] - ", tk[lugar].variavel);
        }else{
            printf("Erro de Syntax: 'varivael' esperada no lugar de: !\n\n");
            //Mostra oq foi escrito no lugar
            for(int k = lugar; k < (lugar+1); k++) {
                if (tk[k].palavraReservada != NULL) {
                    printf("palavra Reservada-[%s] - ", tk[k].palavraReservada);
                    } 
                    else if (tk[k].variavel != NULL) {
                        printf("Variavel-[%s] - ", tk[k].variavel);
                    } 
                    else if (tk[k].simbolos != NULL) {
                        printf("Simbolo Duplo-[%s] - ", tk[k].simbolos);
                    } 
                    else if (tk[k].simbolo != 0) {
                        printf("Simbolo simples-[%c] - ", k, tk[k].simbolo);
                    } 
                    else if (tk[k].real != 0.0f) {
                        printf("Numero Real[%.2f] - ", k, tk[k].real);
                    } 
                    else {
                        printf("Numero inteiro-[%d] - ", k, tk[k].num);
                    }
            }
        }
}

//verifica um simbolo especifico
void identificadorDeSimbolos(leituraDeLinha tk, char simbolo, int lugar){
    if (tk[lugar].simbolo != NULL) {
            printf("Simbolo-[%s] - ", tk[lugar].simbolo);

            //Verifica se é o simbolo esperado
            if(tk[lugar].simbolo != simbolo){
                printf("Erro de Syntax: '%c' esperado!\n\n", simbolo);

                //mostra oq foi escrito no lugar de program:
                for(int k = lugar; k < 1; k++) {
                    if (tk[k].palavraReservada != NULL) {
                        printf("palavra Reservada-[%s] - ", tk[k].palavraReservada);
                        } 
                        else if (tk[k].variavel != NULL) {
                            printf("Variavel-[%s] - ", tk[k].variavel);
                        } 
                        else if (tk[k].simbolos != NULL) {
                            printf("Simbolo Duplo-[%s] - ", tk[k].simbolos);
                        } 
                        else if (tk[k].simbolo != 0) {
                            printf("Valor[%d] - %c - Simbolo simples!\n", k, tk[k].simbolo);
                        } 
                        else if (tk[k].real != 0.0f) {
                            printf("Valor[%d] - %.2f - Numero real!\n", k, tk[k].real);
                        } 
                        else {
                            printf("%d - Numero inteiro!\n", k, tk[k].num);
                        }
                }
            }
        }else{
            printf("\tErro de Syntax: 'simbolo' esperado no lugar de: \n\n");
            //Mostra oq foi escrito no lugar
            for(int k = lugar; k < (lugar+1); k++) {
                if (tk[k].palavraReservada != NULL) {
                    printf("palavra Reservada-[%s] - ", tk[k].palavraReservada);
                    } 
                    else if (tk[k].variavel != NULL) {
                        printf("Variavel-[%s] - ", tk[k].variavel);
                    } 
                    else if (tk[k].simbolos != NULL) {
                        printf("Simbolo Duplo-[%s] - ", tk[k].simbolos);
                    } 
                    else if (tk[k].simbolo != 0) {
                        printf("Valor[%d] - %c - Simbolo simples!\n", k, tk[k].simbolo);
                    } 
                    else if (tk[k].real != 0.0f) {
                        printf("Valor[%d] - %.2f - Numero real!\n", k, tk[k].real);
                    } 
                    else {
                        printf(" %d - Numero inteiro!\n", k, tk[k].num);
                    }
            }
        }
}

//Inicia um programa e um bloco
void programaEBloco(leituraDeLinha tk){
    //program <identificador> ; <bloco> .

    //Verifica se iniciou o programa com program:
    if (tk[0].palavraReservada != NULL) {
            printf("palavra Reservada-[%s] - ", tk[0].palavraReservada);

            //Se a primeira palavra não for program apresenta msg de erro!
            if(tk[0].palavraReservada != TOKEN_PROGRAM){
            printf("Erro de Syntax: titulo 'program' esperado!\n\n");

            //mostra oq foi escrito no lugar de program:
            for(int k = 0; k < 1; k++) {
                if (tk[k].palavraReservada != NULL) {
                    printf("palavra Reservada-[%s] - ", tk[k].palavraReservada);
                    } 
                    else if (tk[k].variavel != NULL) {
                        printf("Variavel-[%s] - ", tk[k].variavel);
                    } 
                    else if (tk[k].simbolos != NULL) {
                        printf("Simbolo Duplo-[%s] - ", tk[k].simbolos);
                    } 
                    else if (tk[k].simbolo != 0) {
                        printf("Valor[%d] - %c - Simbolo simples!\n", k, tk[k].simbolo);
                    } 
                    else if (tk[k].real != 0.0f) {
                        printf("Valor[%d] - %.2f - Numero real!\n", k, tk[k].real);
                    } 
                    else {
                        printf(" %d - Numero inteiro!\n", k, tk[k].num);
                    }
            }
            }
        } 

    //Verifica se a segunda palavra é uma variavel:
    identificador(tk, 1);

    //Verifica se depois da variavel veio ;
    identificadorDeSimbolos(tk, ';', 2);
    printf("\n");

    //bloco:
    bloco();
    
    //Lendo a Struct que passa oq foi lido do código.
    for(int k = 0; k < contador; k++) {
        if (tk[k].palavraReservada != NULL) {
            printf("palavra Reservada-[%s] - ", tk[k].palavraReservada);

            //Se a primeira palavra não for program apresenta msg de erro!
            if(tk[0].palavraReservada != TOKEN_PROGRAM){
            printf("Erro de Syntax: titulo 'program' esperado!\n\n");
            printf("palavra Reservada-[%s] - ", tk[k].palavraReservada);
            }
        } 
        else if (tk[k].variavel != NULL) {
            printf("Variavel-[%s] - ", tk[k].variavel);
        } 
        else if (tk[k].simbolos != NULL) {
            printf("Simbolo Duplo-[%s] - ", tk[k].simbolos);
        } 
        else if (tk[k].simbolo != 0) {
            printf("Valor[%d] - %c - Simbolo simples!\n", k, tk[k].simbolo);
        } 
        else if (tk[k].real != 0.0f) {
            printf("Valor[%d] - %.2f - Numero real!\n", k, tk[k].real);
        } 
        else {
            printf(" %d - Numero inteiro!\n", k, tk[k].num);
        }
    }
}

void validadorSintaxico(leituraDeLinha tk){

    printf("//=======================================================\\\\\n");

    


    if(tk[0].palavraReservada != TOKEN_PROGRAM){
            printf("\nErro de Syntax: titulo 'program' esperado!\n");
    }

    
}