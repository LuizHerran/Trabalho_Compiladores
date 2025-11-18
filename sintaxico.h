#include "lexico.h"

#define TOKEN_MAIS         '+'
#define TOKEN_MENOS        '-'
#define TOKEN_IGUAL        '='
#define TOKEN_MULT         '*'
#define TOKEN_DIV          '/'
#define TOKEN_INT          "NUM_INT: "
#define TOKEN_FLOAT        "NUM_REAL: "
#define TOKEN_PONTOVIRGULA ';'
#define TOKEN_VIRGULA      ','
#define TOKEN_DOISPONTOS   ':'
#define TOKEN_PONTO        '.'
#define TOKEN_MAIOR        '>'
#define TOKEN_MENOR        '<'
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
#define TOKEN_DOISPONTOIGUAL ":="
#define TOKEN_MAIORIGUAL     ">="
#define TOKEN_MENORIGUAL     "<="
#define TOKEN_INTEGER        "integer"
#define TOKEN_REAL           "real"
#define TOKEN_ERRO           "ERRO"
#define TOKEN_END            "END"

int lugarVariavel = 0; //Variavel global para controle de posição na análise sintática

//funções declaradas
void declaracaoDeVariavel(leituraDeLinha tk[], int lugar);
void expressao(leituraDeLinha tk[], int lugar);
void comandoComposto(leituraDeLinha tk[], int lugar);
void identificadorDeSimbolos(leituraDeLinha tk[], char simbolo, int lugar);
void identificador(leituraDeLinha tk[], int lugar);
void listaDeIdentificadores(leituraDeLinha tk[], int lugar);

//identificador de erro:
void palavraNaoEsperada(leituraDeLinha tk[], int lugar){
    for(int k = lugar; k < (lugar+1); k++){
        if (tk[k].palavraReservada != NULL){
            printf("palavra Reservada-[%s] -> ", tk[k].palavraReservada);
            } else if (tk[k].variavel != NULL){
                printf("Variavel-[%s] -> ", tk[k].variavel);
            } else if (tk[k].simbolos != NULL){
                printf("Simbolo Duplo-[%s] -> ", tk[k].simbolos);
            } else if (tk[k].simbolo != '\0'){
                printf("Simbolo simples-[%c] -> ", tk[k].simbolo);
            } else if (tk[k].real != 0.0f){
                printf("Numero Real[%.2f] -> ", tk[k].real);
            } else {printf("Numero inteiro-[%d] -> ", tk[k].num);}
    }lugarVariavel++;
}

//sinal 
void sinal(leituraDeLinha tk[], int lugar){
    // + | - | 𝜀
    if(tk[lugar].simbolo != '\0'){
        //Se existir um simbolo precisas ser + ou -
        if(tk[lugar].simbolo == TOKEN_MAIS){
            printf("Variavel-[%c] - ", tk[lugar].simbolo);
            lugarVariavel++;
        } else if(tk[lugar].simbolo == TOKEN_MENOS){
            printf("Variavel-[%c] - ", tk[lugar].simbolo);
            lugarVariavel++;
        } else {
            printf("Erro de Syntax: '+ ou -' esperada no lugar de: \n\n");
            //Mostra oq foi escrito no lugar
            palavraNaoEsperada(tk, lugar);
            lugarVariavel++;
        }
    }
}

//número 
void numero(leituraDeLinha tk[], int lugar){
//   <sinal><inteiro sem sinal> | <sinal><real sem sinal>
    sinal(tk, lugar);
    if(tk[lugarVariavel].num != 0){
        printf("Numero inteiro-[%d] - ", tk[lugarVariavel].num);
        lugarVariavel++;
    } else if(tk[lugarVariavel].real != 0.0f){
        printf("Numero real-[%d] - ", tk[lugar].num);
        lugarVariavel++;
    } else {
        printf("Erro de Syntax: 'número' esperada no lugar de: \n\n");
            //Mostra oq foi escrito no lugar
            palavraNaoEsperada(tk, lugarVariavel);
            
    }
}

//Relação 
void relacao(leituraDeLinha tk[], int lugar){
// = | == | < | <= | >= | >
    if(tk[lugar].simbolo == '='){
        printf("Simbolo-[%c] - ", tk[lugar].simbolo);
        lugarVariavel++;
    } else if(tk[lugar].simbolo == '<'){
        printf("Simbolo-[%c] - ", tk[lugar].simbolo);
        lugarVariavel++;
    } else if(tk[lugar].simbolo == '>'){
        printf("Simbolo-[%c] - ", tk[lugar].simbolo);
        lugarVariavel++;
    } else if(strcmp(tk[lugarVariavel].simbolos, TOKEN_MAIORIGUAL) == 0 || strcmp(tk[lugarVariavel].simbolos, TOKEN_MENORIGUAL) == 0){
        printf("Simbolos-[%s] - ", tk[lugar].simbolos);
        lugarVariavel++;
    } else {
        //Se não for =, ==, <=, >=, <, >
        printf("Erro de Syntax: '=, ==, <=, >=, <, >' esperada no lugar de: \n\n");
        //Mostra oq foi escrito no lugar
        palavraNaoEsperada(tk, lugarVariavel);
        lugarVariavel++;
    }
}

//Fator 
void fator(leituraDeLinha tk[], int lugar){
// <variável> | <número> | ( <expressão> );

    if(tk[lugar].variavel != NULL){
        identificador(tk, lugar);
    } else if(tk[lugar].num != 0){
        numero(tk, lugar);
    } else if(tk[lugar].real != 0.0f){
        numero(tk, lugar);
    }
}

//Termo 
void termo(leituraDeLinha tk[], int lugar){
// <fator> { ( * | / ) <fator> };

    fator(tk, lugar);

    while(tk[lugarVariavel].simbolo != '\0'){
        for(int k = lugarVariavel; k < lugarVariavel+1; k++){
            if(tk[k].simbolo == TOKEN_MULT){
                printf("Simbolo-[%c] -> ", tk[k].simbolo);
            } else if(tk[k].simbolo == TOKEN_DIV){
                printf("Simbolo-[%c] -> ", tk[k].simbolo);
            } else if(tk[k].simbolo == TOKEN_IGUAL){
                printf("Simbolo-[%c] -> ", tk[k].simbolo);
            } else if(tk[k].simbolo == TOKEN_MAIOR){
                printf("Simbolo-[%c] -> ", tk[k].simbolo);
            } else if(tk[k].simbolo == TOKEN_MENOR){
                printf("Simbolo-[%c] -> ", tk[k].simbolo);
            } else if(tk[k].simbolo == TOKEN_MAIS){
                printf("Simbolo-[%c] -> ", tk[k].simbolo);
            } else if(tk[k].simbolo == TOKEN_MENOS){
                printf("Simbolo-[%c] -> ", tk[k].simbolo);
            } else if(tk[k].simbolo == TOKEN_DOISPONTOIGUAL){
                printf("Simbolo-[%c] -> ", tk[k].simbolo);
            } else if(tk[k].simbolo == TOKEN_PONTOVIRGULA){
            } else {palavraNaoEsperada(tk, lugarVariavel);}
        }
        lugarVariavel++;
        fator(tk, lugarVariavel);
    }
}


// Expressão simples 
void expressaoSimples(leituraDeLinha tk[], int lugar){
// [ + | - ] <termo> { ( + | - ) <termo> }


    if(tk[lugar].simbolo == TOKEN_MAIS || tk[lugar].simbolo == TOKEN_MENOS){
    printf("Simbolo-[%c] - ", tk[lugar].simbolo);
    lugarVariavel++; 
    }
        
    termo(tk, lugarVariavel);
    while(tk[lugarVariavel].simbolo != '\0'){
        if(tk[lugarVariavel].simbolo == TOKEN_MAIS || tk[lugarVariavel].simbolo == TOKEN_MENOS){
            printf("Simbolo-[%c] - ", tk[lugarVariavel].simbolo);
            lugarVariavel++;
            termo(tk, lugarVariavel);}
    }

}

//Expressão 
void expressao(leituraDeLinha tk[], int lugar){
// <expressão simples> [ <relação> <expressão simples> ]
 
    expressaoSimples(tk, lugar);
    
    if(tk[lugarVariavel].simbolo != '\0' || tk[lugarVariavel].simbolos != NULL){
        relacao(tk, lugarVariavel);
        expressaoSimples(tk, lugarVariavel);
    }
}

//Comando ------------------------------------------------------- problema aqui!
void comando(leituraDeLinha tk[], int lugar){
// <atribuição> | <comando composto> | <comando condicional> | <comando repetitivo>

    if (tk[lugar].palavraReservada == NULL){tk[lugar].palavraReservada = "oi";}

    if(strcmp(tk[lugar].palavraReservada, TOKEN_BEGIN) == 0){
        comandoComposto(tk, lugar);
        lugarVariavel++;

    } else if(strcmp(tk[lugar].palavraReservada, TOKEN_IF) == 0){
        // if <expressão> then <comando> [ else <comando> ] -- <Comando condicional>
        printf("palavra Reservada-[%s] -> ", tk[lugar].palavraReservada);
        lugarVariavel++;
        
        expressao(tk, lugarVariavel);
        
        //Verifica se a proxima palavra é then:
        if(strcmp(tk[lugarVariavel].palavraReservada, TOKEN_THEN) == 0){
            printf("palavra Reservada-[%s] -> ", tk[lugarVariavel].palavraReservada);
            printf("\n");
            lugarVariavel++;

            comando(tk, lugarVariavel);
            identificadorDeSimbolos(tk, ';', lugarVariavel);
            
            //Verifica se tem else (não é borigado a ter);
            if(strcmp(tk[lugarVariavel].palavraReservada, TOKEN_ELSE) == 0){
                printf("palavra Reservada-[%s] - ", tk[lugarVariavel].palavraReservada);
                lugarVariavel++;
                printf("\n");
                comando(tk, lugarVariavel);
            }
        } else {
            //Se não for then
            printf("Erro de Syntax: 'then' esperada no lugar de: \n\n");
            //Mostra oq foi escrito no lugar
            palavraNaoEsperada(tk, lugarVariavel);
        }
    } else if(strcmp(tk[lugar].palavraReservada, TOKEN_WHILE) == 0){
        // while <expressão> do <comando> -----> <Comando repetitivo>

        printf("palavra Reservada-[%s] - ", tk[lugar].palavraReservada);
        lugarVariavel++;
        expressao(tk, lugarVariavel);
        if(strcmp(tk[lugarVariavel].palavraReservada, TOKEN_DO) == 0){
            printf("palavra Reservada-[%s] - ", tk[lugarVariavel].palavraReservada);
            lugarVariavel++;
        } else {
        //Se não for do
        printf("Erro de Syntax: 'do' esperada no lugar de: \n\n");
        //Mostra oq foi escrito no lugar
        palavraNaoEsperada(tk, lugarVariavel);   
    }
        comando(tk, lugarVariavel);

    } else if(tk[lugar].variavel != NULL){
        // <variável> := <expressão> ----------> <atribuição>
        printf("Variavel-[%s] -> ", tk[lugar].variavel);
        lugarVariavel++;

        //Verifica se a proxima palavra é :=
        if(strcmp(tk[lugarVariavel].simbolos, TOKEN_DOISPONTOIGUAL) == 0){
            printf("Variavel-[%s] -> ", tk[lugarVariavel].simbolos);
            lugarVariavel++;
            expressao(tk, lugarVariavel);
            identificadorDeSimbolos(tk, ';', lugarVariavel);

        } else {
            //Se não for :=
                    printf("Erro de Syntax: ':=' esperada no lugar de: \n\n");
                    //Mostra oq foi escrito no lugar
                    palavraNaoEsperada(tk, lugar);
        }
    } else {
        //Se não for Beguin, if, while ou variavel
        printf("Erro de Syntax: 'atribuicao, comando composto, comando condicional ou comando repetitico' esperada no lugar de: \n\n");
        //Mostra oq foi escrito no lugar
        palavraNaoEsperada(tk, lugar);
    }
}

//Comandos Compostos 
void comandoComposto(leituraDeLinha tk[], int lugar){
// begin <comando> { ; <comando> } end

    //Verifica se a palavra é begin:
    if (tk[lugar].palavraReservada != NULL) {
            printf("palavra Reservada-[%s] - ", tk[lugar].palavraReservada);
            lugarVariavel++;

            //Se a primeira palavra não for begin apresenta msg de erro!
            if(strcmp(tk[lugar].palavraReservada, TOKEN_BEGIN) != 0){
            printf("Erro de Syntax: 'begin' esperado!\n\n");

                //Mostra oq foi escrito no lugar
                palavraNaoEsperada(tk, lugar);
            }
    } else {
        //Mostra oq foi escrito no lugar da palavra reservada
        palavraNaoEsperada(tk, lugar);
    }

    comando(tk, lugarVariavel);
    
    while(tk[lugarVariavel].simbolo == ';'){
        printf("Simbolo Duplo-[%s] - ", tk[lugarVariavel].simbolos);
        lugarVariavel++;
        comando(tk,lugarVariavel);
    }

    //Verifica se a palavra é end
    if (tk[lugarVariavel].palavraReservada != NULL) {
        printf("palavra Reservada-[%s] - ", tk[lugarVariavel].palavraReservada);
        
        //Se a primeira palavra não for program apresenta msg de erro!
        if(strcmp(tk[lugarVariavel].palavraReservada, TOKEN_END) != 0){
        printf("Erro de Syntax: 'end' esperado!\n\n");}

        //mostra oq foi escrito no lugar de program:
        palavraNaoEsperada(tk, lugarVariavel);
        } else {
            //Mostra oq estava escrito no lugar da palvara reservada
            printf("\tErro de Syntax: 'end' esperado no lugar de: \n\n");
            palavraNaoEsperada(tk, lugarVariavel);
        }
}



//Verifica se existe uma ou mais variaveis
void declaracaoDeVariavel(leituraDeLinha tk[], int lugar){
// <lista de identificadores> : <tipo>

    //verifica se é uma variavel:
    identificador(tk, lugar);

    //Verifica se tem , e mais possiveis variaveis também trazendo o TIPO
    listaDeIdentificadores(tk, lugarVariavel);
    while(tk[lugarVariavel].variavel != NULL){
        identificador(tk, lugarVariavel);
        listaDeIdentificadores(tk, lugarVariavel);
    }
}

//lista de identificadores - verifica se tem ',' e mais variaveis a frente ou ':' e um TIPO finalizando com ';'
void listaDeIdentificadores(leituraDeLinha tk[], int lugar){
    // { , <identificador> };

    if(tk[lugar].simbolo == ','){
        printf("Simbolo-[%c] -> ", tk[lugar].simbolo);
        lugarVariavel++;
        declaracaoDeVariavel(tk, lugarVariavel);
    } else {
        
        //Verifica se o proximo caracter é :
        if(tk[lugarVariavel].simbolo == ':'){
                printf("Simbolo-[%c] -> ", tk[lugarVariavel].simbolo);
                lugarVariavel++;

                //Verifica se o proximo caracter é um tipo;
                if(strcmp(tk[lugarVariavel].palavraReservada, TOKEN_INTEGER) == 0){
                    printf("Palavra reservada-[%s] - ", tk[lugarVariavel].palavraReservada);
                    lugarVariavel++;

                    //verifica se tem ';'
                    identificadorDeSimbolos(tk, ';', lugarVariavel);
                    printf("\n");

                }else if(strcmp(tk[lugarVariavel].palavraReservada, TOKEN_REAL) == 0){
                    printf("Palavra reservada-[%s] - ", tk[lugarVariavel].palavraReservada);
                    lugarVariavel++;

                    //verifica se tem ';'
                    identificadorDeSimbolos(tk, ';', lugarVariavel);
                    printf("\n");

                } else {
                 //Se não for um tipo;
                    printf("Erro de Syntax: 'integer ou real' esperada no lugar de: \n\n");
                    //Mostra oq foi escrito no lugar;
                    palavraNaoEsperada(tk, lugarVariavel);

                    //verifica se tem ';'
                    identificadorDeSimbolos(tk, ';', lugarVariavel);
                }
        } else {
            //Falta do :
            printf("Erro de Syntax: ':' esperada no lugar de: \n\n");
            //Mostra oq foi escrito no lugar;
            palavraNaoEsperada(tk, lugarVariavel);
        }
     }
}

//Parte de declaração de variáveis  
void parteDeclaracaoDeVariaveis(leituraDeLinha tk[], int lugar){
// { var <declaração de variáveis> {; <declaração de variáveis>} ; }

    //Verificar se começa com var:
    if (tk[lugar].palavraReservada != NULL) {
            if(strcmp(tk[lugar].palavraReservada, TOKEN_VAR) == 0){
                printf("Palavra Reservada-[%s]\n", tk[lugar].palavraReservada);
                lugarVariavel++;
            } else {
                printf("Erro de Syntax: 'Var' esperada no lugar de: \n\n");
                //Mostra oq foi escrito no lugar
                palavraNaoEsperada(tk, lugar);}
        } else {
            printf("Erro de Syntax: 'Var' esperada no lugar de: \n\n");
            //Mostra oq foi escrito no lugar
            palavraNaoEsperada(tk, lugar);
            printf("\n");
        }

        //ATÉ AQUI TUDO OK
    declaracaoDeVariavel(tk, lugarVariavel);
    //Verificar se tem mais variaveis:
    
}

//Bloco 
void bloco(leituraDeLinha tk[]){
    // <parte de declarações de variáveis> <comando composto>

    //parte de declaração de variaveis
    parteDeclaracaoDeVariaveis(tk, lugarVariavel);

    //comando composto
    comandoComposto(tk, lugarVariavel);
}

//Verifica se é uma variavel 
void identificador(leituraDeLinha tk[], int lugar){
    // <letra> ( <letra> | <dígito> ) * ----> {Varivael}

    if (tk[lugar].variavel != NULL) {
            printf("Variavel-[%s] - ", tk[lugar].variavel);
            lugarVariavel++;
        }else{
            printf("Erro de Syntax: 'varivael' esperada no lugar de: \n\n");
            //Mostra oq foi escrito no lugar
            palavraNaoEsperada(tk, lugarVariavel);
        }
}

//verifica um simbolo especifico 
void identificadorDeSimbolos(leituraDeLinha tk[], char simbolo, int lugar){

    if (tk[lugar].simbolo != '\0') {
        printf("Simbolo - [%c] -> ", tk[lugar].simbolo);
        lugarVariavel++;

        //Verifica se é o simbolo esperado
        if(tk[lugar].simbolo != simbolo){
            printf("Erro de Syntax: '%c' esperado!\n\n", simbolo);

            //mostra oq foi escrito no lugar de program:
            palavraNaoEsperada(tk, lugarVariavel);
        }
    } else { 
        printf("\tErro de Syntax: 'simbolo' esperado no lugar de: \n\n");
        //Mostra oq foi escrito no lugar
        palavraNaoEsperada(tk, lugarVariavel);
    }
}

//Inicia um programa e um bloco 
void programaEBloco(leituraDeLinha tk[]){
    //program <identificador> ; <bloco> .

    //Verifica se iniciou o programa com program:
    if (tk[lugarVariavel].palavraReservada != NULL) {


        if(strcmp(tk[lugarVariavel].palavraReservada, TOKEN_PROGRAM) == 0){
            printf("palavra Reservada-[%s] -> ", tk[0].palavraReservada);
            lugarVariavel++;
            
          } else {
            printf("Erro de Syntax: titulo 'program' esperado!\n\n");
            palavraNaoEsperada(tk, lugarVariavel);
          }
        } else {
            printf("Erro de Syntax: 'program' esperado no lugar de: \n\n");
            //Mostra oq foi escrito no lugar
            palavraNaoEsperada(tk, lugarVariavel);
        }

    //Verifica se a segunda palavra é uma variavel:
    identificador(tk, lugarVariavel);

    //Verifica se depois da variavel veio ;
    identificadorDeSimbolos(tk, ';', lugarVariavel);
    printf("\n");

    //bloco:
    bloco(tk);
    //Verifica se atem um . no final
    if(tk[lugarVariavel].simbolo == TOKEN_PONTO){
        printf("Simbolo simples-[%c] - ", tk[lugarVariavel].simbolo);
    } else {
        printf("Erro de Syntax: '.' esperada no lugar de: \n\n");
            //Mostra oq foi escrito no lugar
            palavraNaoEsperada(tk, lugarVariavel);
    }
}
