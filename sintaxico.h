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
int lugarVariaveis = 3;
//VERIFICAÇÃO SE UMA VARIAVEL ATENDE: COMEÇAR COM LETRA ------------------------------------------------

//Relação --------------- a ser criado
void relacao(leituraDeLinha tk, int lugar){
// = | <> | < | <= | >= | >
}

//Fator ---------------- a ser criado
void fator(leituraDeLinha tk, int lugar){
// <variável> | <número> | ( <expressão> )
}

//Termo 
void termo(leituraDeLinha tk, int lugar){
// <fator> { ( * | / ) <fator> }
    fator(tk, lugar);
    int ver = 1;
    while(tk[lugar+ver].simbolo != NULL){
        if(tk[lugar+ver].simbolo == TOKEN_MULT || tk[lugar+ver].simbolo == TOKEN_DIV){
            printf("Simbolo-[%c] - ", tk[lugar+ver].simbolo);
            fator(tk, lugar+ver+1);
            ver++;
        }
    }

}

// Expressão simples
void expressaoSimples(leituraDeLinha tk, int lugar){
// [ + | - ] <termo> { ( + | - ) <termo> }
    if(tk[lugar].simbolo == TOKEN_MAIS || tk[lugar].simbolo == TOKEN_MENOS){
    printf("Simbolo-[%c] - ", tk[lugar].simbolo);   

        termo(tk, lugar+1);
        int ver = 2;
        while(tk[lugar+ver].simbolo != NULL){
            if(tk[lugar+ver].simbolo == TOKEN_MAIS || tk[lugar+ver].simbolo == TOKEN_MENOS){
                printf("Simbolo-[%c] - ", tk[lugar+ver].simbolo); 
                termo(tk, lugar+ver+1);
                ver++;
            }
        }
    } else {
        //Se não for + ou -
        printf("Erro de Syntax: '+ | -' esperada no lugar de: !\n\n");
        //Mostra oq foi escrito no lugar
        for(int k = (lugar+1); k < (lugar+2); k++) {
            if (tk[k].palavraReservada != NULL) {
            printf("palavra Reservada-[%s] - ", tk[k].palavraReservada);
            } else if (tk[k].variavel != NULL) {
                printf("Variavel-[%s] - ", tk[k].variavel);
            } else if (tk[k].simbolos != NULL) {
                printf("Simbolo Duplo-[%s] - ", tk[k].simbolos);
            } else if (tk[k].simbolo != 0) {
                printf("Simbolo simples-[%c] - ", k, tk[k].simbolo);
            } else if (tk[k].real != 0.0f) {
                printf("Numero Real[%.2f] - ", k, tk[k].real);
            } else {printf("Numero inteiro-[%d] - ", k, tk[k].num);}
        }
    }
}

//Expressão ----------------- a ser verificado
void expressao(leituraDeLinha tk, int lugar){
// <expressão simples> [ <relação> <expressão simples> ]
    expressaoSimples(tk, lugar);
    relacao(tk, lugar+1);
    expressaoSimples(tk, lugar+2);
}

//Comando 
void comando(leituraDeLinha tk, int lugar){
// <atribuição> | <comando composto> | <comando condicional> | <comando repetitivo>
    if(tk[lugar].palavraReservada == TOKEN_BEGIN){
        comandoComposto(tk, lugar);

    } else if(tk[lugar].palavraReservada == TOKEN_IF){
        // if <expressão> then <comando> [ else <comando> ]

        printf("palavra Reservada-[%s] - ", tk[lugar].palavraReservada);
        expressao(tk, lugar);
        if(tk[lugar+1].palavraReservada == TOKEN_THEN){
            printf("palavra Reservada-[%s] - ", tk[lugar+1].palavraReservada);
            comando(tk, lugar+2);
            
            if(tk[lugar+3].palavraReservada == TOKEN_ELSE){
                printf("palavra Reservada-[%s] - ", tk[lugar+3].palavraReservada);
                comando(tk, lugar+4);
            }
        }
    } else if(tk[lugar].palavraReservada == TOKEN_WHILE){
        // while <expressão> do <comando>

        printf("palavra Reservada-[%s] - ", tk[lugar].palavraReservada);
        expressao(tk, lugar+1);
        if(tk[lugar+2].palavraReservada == TOKEN_DO){
            printf("palavra Reservada-[%s] - ", tk[lugar+2].palavraReservada);
        }
        comando(tk, lugar+3);
    } else if(tk[lugar].variavel != NULL){
        // atribuição = <variável> := <expressão>
        printf("Variavel-[%s] - ", tk[lugar].variavel);
        if(tk[lugar+1].simbolos == TOKEN_DOISPONTOIGUAL){
            printf("Variavel-[%s] - ", tk[lugar+1].simbolos);
            expressao(tk, lugar+2);
        } else {
            //Se não for :=
                    printf("Erro de Syntax: ':=' esperada no lugar de: !\n\n");
                    //Mostra oq foi escrito no lugar
                    for(int k = (lugar+1); k < (lugar+2); k++) {
                        if (tk[k].palavraReservada != NULL) {
                        printf("palavra Reservada-[%s] - ", tk[k].palavraReservada);
                        } else if (tk[k].variavel != NULL) {
                            printf("Variavel-[%s] - ", tk[k].variavel);
                        } else if (tk[k].simbolos != NULL) {
                            printf("Simbolo Duplo-[%s] - ", tk[k].simbolos);
                        } else if (tk[k].simbolo != 0) {
                            printf("Simbolo simples-[%c] - ", k, tk[k].simbolo);
                        } else if (tk[k].real != 0.0f) {
                            printf("Numero Real[%.2f] - ", k, tk[k].real);
                        } else {printf("Numero inteiro-[%d] - ", k, tk[k].num);}
                    }
            
        }
    } else{
        //Se não for Beguin, if, while ou variavel
        printf("Erro de Syntax: 'atribuicao, comando composto, comando condicional ou comando repetitico' esperada no lugar de: !\n\n");
        //Mostra oq foi escrito no lugar
        for(int k = (lugar+1); k < (lugar+2); k++) {
            if (tk[k].palavraReservada != NULL) {
            printf("palavra Reservada-[%s] - ", tk[k].palavraReservada);
            } else if (tk[k].variavel != NULL) {
                printf("Variavel-[%s] - ", tk[k].variavel);
            } else if (tk[k].simbolos != NULL) {
                printf("Simbolo Duplo-[%s] - ", tk[k].simbolos);
            } else if (tk[k].simbolo != 0) {
                printf("Simbolo simples-[%c] - ", k, tk[k].simbolo);
            } else if (tk[k].real != 0.0f) {
                printf("Numero Real[%.2f] - ", k, tk[k].real);
            } else {printf("Numero inteiro-[%d] - ", k, tk[k].num);}
        }    
    }

}

//Comandos Compostos
void comandoComposto(leituraDeLinha tk, int lugar){
// begin <comando> { ; <comando> } end

    //Verifica se a palavra é begin:
    if (tk[lugar].palavraReservada != NULL) {
            printf("palavra Reservada-[%s] - ", tk[lugar].palavraReservada);

            //Se a primeira palavra não for program apresenta msg de erro!
            if(tk[0].palavraReservada != TOKEN_BEGIN){
            printf("Erro de Syntax: 'begin' esperado!\n\n");

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
        } else {
            printf("\tErro de Syntax: 'begin' esperado no lugar de: \n\n");
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

    comando(tk, lugar+1);
    int i = 2;
    while(tk[lugar+i].simbolo == ';'){
        comando(tk,lugar+(i+1));
        i++;
    }

    //Verifica se a palavra é end
    if (tk[lugar].palavraReservada != NULL) {
            printf("palavra Reservada-[%s] - ", tk[0].palavraReservada);

            //Se a primeira palavra não for program apresenta msg de erro!
            if(tk[0].palavraReservada != TOKEN_END){
            printf("Erro de Syntax: 'end' esperado!\n\n");
            }
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
        } else {
            printf("\tErro de Syntax: 'end' esperado no lugar de: \n\n");
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
                    } else {printf(" %d - Numero inteiro!\n", k, tk[k].num);}
            }
        }
}

//lista de identificadores - verifica se tem , e mais variaveis a frente ou : e um TIPO na frente
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
                        } else if (tk[k].variavel != NULL) {
                            printf("Variavel-[%s] - ", tk[k].variavel);
                        } else if (tk[k].simbolos != NULL) {
                            printf("Simbolo Duplo-[%s] - ", tk[k].simbolos);
                        } else if (tk[k].simbolo != 0) {
                            printf("Simbolo simples-[%c] - ", k, tk[k].simbolo);
                        } else if (tk[k].real != 0.0f) {
                            printf("Numero Real[%.2f] - ", k, tk[k].real);
                        } else {printf("Numero inteiro-[%d] - ", k, tk[k].num);}
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

    //Verificar se o proximo é ; 
    identificadorDeSimbolos(tk, ';', (lugar + 2));
    printf("\n");

    //Verificar se tem mais variaveis:
    while(tk[lugar+lugarVariaveis].variavel != NULL){
        identificador(tk, (lugarVariaveis));
        identificadorDeSimbolos(tk, ';', lugarVariaveis+1);
        printf("\n");
        lugarVariaveis++;
    }
    
}

void bloco(){
    //parte de declaração de variaveis
    parteDeclaracaoDeVariaveis(tk, 3);

    //comando composto
    comandoComposto(tk, lugarVariaveis);
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
                        } else if (tk[k].variavel != NULL) {
                            printf("Variavel-[%s] - ", tk[k].variavel);
                        } else if (tk[k].simbolos != NULL) {
                            printf("Simbolo Duplo-[%s] - ", tk[k].simbolos);
                        } else if (tk[k].simbolo != 0) {
                            printf("Valor[%d] - %c - Simbolo simples!\n", k, tk[k].simbolo);
                        } else if (tk[k].real != 0.0f) {
                            printf("Valor[%d] - %.2f - Numero real!\n", k, tk[k].real);
                        } else {
                            printf("%d - Numero inteiro!\n", k, tk[k].num);}
                }
            }
        } else {
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
                    } else if (tk[k].variavel != NULL) {
                        printf("Variavel-[%s] - ", tk[k].variavel);
                    } else if (tk[k].simbolos != NULL) {
                        printf("Simbolo Duplo-[%s] - ", tk[k].simbolos);
                    } else if (tk[k].simbolo != 0) {
                        printf("Valor[%d] - %c - Simbolo simples!\n", k, tk[k].simbolo);
                    } else if (tk[k].real != 0.0f) {
                        printf("Valor[%d] - %.2f - Numero real!\n", k, tk[k].real);
                    } else {printf(" %d - Numero inteiro!\n", k, tk[k].num);}
            }
            }
        } else {
            printf("\tErro de Syntax: 'program' esperado no lugar de: \n\n");
            //Mostra oq foi escrito no lugar
            for(int k = 0; k < (k+1); k++) {
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