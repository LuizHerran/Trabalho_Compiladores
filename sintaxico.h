#include "lexico.h"

#define TOKEN_MAIS         '+'
#define TOKEN_MENOS        '-'
#define TOKEN_IGUAL        '='
#define TOKEN_MULT         '*'
#define TOKEN_DIV          '/'
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
#define TOKEN_END            "end"

//Variaveis globais:
int lugarVariavel = 0; //Responsavel por controle de posição na análise sintática
int contadorEnd = 0;   //Responsável por contar quantos end são necessários e finalizar o programa corretamente
int x = 0;             //Responsável pelo controle de colunas na impressão da árvore sintática

//funções declaradas
void declaracaoDeVariavel(leituraDeLinha tk[], int lugar);
void expressao(leituraDeLinha tk[], int lugar);
void comandoComposto(leituraDeLinha tk[], int lugar);
void identificadorDeSimbolos(leituraDeLinha tk[], char simbolo, int lugar);
void identificador(leituraDeLinha tk[], int lugar);
void listaDeIdentificadores(leituraDeLinha tk[], int lugar);

//Para o controle de colunas no print
void controleDeColunas(int q){
    for(int i = 0; i < q; i++){
        printf("    %c", 179);
    }
    printf("    %c%c%c", 195, 196, 196);
}

//Identifica a palavra que não era esperada
void palavraNaoEsperada(leituraDeLinha tk[], int lugar){
    for(int k = lugar; k < (lugar+1); k++){
        if (tk[k].palavraReservada != NULL){
            printf(" Palavra Reservada: %s\n", tk[k].palavraReservada);
            } else if (tk[k].variavel != NULL){
                printf(" Variavel: %s\n", tk[k].variavel);
            } else if (tk[k].simbolos != NULL){
                printf(" Simbolo Duplo: %s\n", tk[k].simbolos);
            } else if (tk[k].simbolo != '\0'){
                printf(" Simbolo simples: %c\n", tk[k].simbolo);
            } else if (tk[k].real != 0.0f){
                printf(" Numero Real: %.2f\n", tk[k].real);
            } else {printf(" Numero inteiro: %d\n", tk[k].num);}
    }lugarVariavel++;
    exit(0);
}

//sinal Verifica + e -
void sinal(leituraDeLinha tk[], int lugar){
    // + | - | 𝜀
    
    if(tk[lugar].simbolo != '\0'){
        //Se existir um simbolo precisas ser + ou -
        printf(" SINAL\n");
        x++;
        controleDeColunas(x);
        if(tk[lugar].simbolo == TOKEN_MAIS){
            printf(" Variavel: %c\n", tk[lugar].simbolo);
            lugarVariavel++;
        } else if(tk[lugar].simbolo == TOKEN_MENOS){
            printf(" Variavel: %c\n", tk[lugar].simbolo);
            lugarVariavel++;
        } else {
            printf(" Linha: %d - Erro de Syntax: '+ ou -' esperada no lugar de: ", tk[lugar].linha);
            //Mostra oq foi escrito no lugar
            palavraNaoEsperada(tk, lugar);
        }
        x--;
    }
}

//número Verrifica o tipo de número real ou inteiro
void numero(leituraDeLinha tk[], int lugar){
//   <sinal><inteiro sem sinal> | <sinal><real sem sinal>
    printf(" NUMERO\n");
    x++;
    controleDeColunas(x);

    sinal(tk, lugar);
    if(tk[lugarVariavel].num != 0){
        printf(" Numero inteiro: %d\n", tk[lugarVariavel].num);
        lugarVariavel++;
    } else if(tk[lugarVariavel].real != 0.0f){
        printf(" Numero real: %.2f\n", tk[lugar].real);
        lugarVariavel++;
    } else {printf(" Linha: %d - Erro de Syntax: 'numero' esperada no lugar de: ", tk[lugar].linha);
            palavraNaoEsperada(tk, lugarVariavel); 
    }
    x--;
}

//Relação Verifica se é { = | == | < | <= | >= | > }
void relacao(leituraDeLinha tk[], int lugar){
    printf(" RELACAO\n");
    x++;
    controleDeColunas(x);

    if(tk[lugar].simbolo == '='){
        printf(" Simbolo: %c\n", tk[lugar].simbolo);
        lugarVariavel++;
    } else if(tk[lugar].simbolo == '<'){
        printf(" Simbolo: %c\n", tk[lugar].simbolo);
        lugarVariavel++;
    } else if(tk[lugar].simbolo == '>'){
        printf(" Simbolo: %c\n", tk[lugar].simbolo);
        lugarVariavel++;
    } else if(strcmp(tk[lugarVariavel].simbolos, TOKEN_MAIORIGUAL) == 0 || strcmp(tk[lugarVariavel].simbolos, TOKEN_MENORIGUAL) == 0){
        printf(" Simbolo: %s\n", tk[lugar].simbolos);
        lugarVariavel++;
    }else if(strcmp(tk[lugarVariavel].simbolos, TOKEN_DOISPONTOIGUAL) == 0){
        x--;
        return;
    } else {printf(" Linha: %d - Erro de Syntax: '=, ==, <=, >=, <, >,' esperada no lugar de: ", tk[lugar].linha);
        palavraNaoEsperada(tk, lugarVariavel);
    }
    x--;
}

//Fator - Verifica se é uma variavel ou número
void fator(leituraDeLinha tk[], int lugar){
// <variável> | <número> | ( <expressão> );
    printf(" FATOR\n");
    x++;
    controleDeColunas(x);
    if(tk[lugar].variavel != NULL){
        identificador(tk, lugar);
    } else if(tk[lugar].num != 0){numero(tk, lugar);
    } else if(tk[lugar].real != 0.0f){numero(tk, lugar);}
    x--;
}

//Termo Verifica variaveis e sinais entre elas
void termo(leituraDeLinha tk[], int lugar){
// <fator> { ( * | / ) <fator> };
    printf(" TERMO\n");
    x++;

    controleDeColunas(x);
    fator(tk, lugar);

    while(tk[lugarVariavel].simbolo != '\0'){
        controleDeColunas(x);
        for(int k = lugarVariavel; k < lugarVariavel+1; k++){
            if(tk[k].simbolo == TOKEN_MULT){ printf(" Simbolo: %c\n", tk[k].simbolo);
            } else if(tk[k].simbolo == TOKEN_DIV){ printf(" Simbolo: %c\n", tk[k].simbolo);
            } else if(tk[k].simbolo == TOKEN_IGUAL){ printf(" Simbolo: %c\n", tk[k].simbolo);
            } else if(tk[k].simbolo == TOKEN_MAIOR){ printf(" Simbolo: %c\n", tk[k].simbolo);
            } else if(tk[k].simbolo == TOKEN_MENOR){ printf(" Simbolo: %c\n", tk[k].simbolo);
            } else if(tk[k].simbolo == TOKEN_MAIS){ printf(" Simbolo: %c\n", tk[k].simbolo);
            } else if(tk[k].simbolo == TOKEN_MENOS){ printf(" Simbolo: %c\n", tk[k].simbolo);
            } else if(tk[k].simbolo == TOKEN_PONTOVIRGULA){lugarVariavel++; x--; return;}
        }
        lugarVariavel++;
        controleDeColunas(x);
        fator(tk, lugarVariavel);
    }
    x--;
}

// Expressão simples                      ---- a ser verificado
void expressaoSimples(leituraDeLinha tk[], int lugar){
// [ + | - ] <termo> { ( + | - ) <termo> }
printf(" EXPRESSAO SIMPLES\n");
x++;
controleDeColunas(x);

    if(tk[lugar].simbolo == TOKEN_MAIS || tk[lugar].simbolo == TOKEN_MENOS){
        printf(" Simbolo: %c\n", tk[lugar].simbolo);
        lugarVariavel++; 
    }
        
    termo(tk, lugarVariavel);
    while(tk[lugarVariavel].simbolo != '\0'){
        if(tk[lugarVariavel].simbolo == TOKEN_MAIS || tk[lugarVariavel].simbolo == TOKEN_MENOS){
            controleDeColunas(x);
            printf(" Simbolo: %c\n", tk[lugarVariavel].simbolo);
            lugarVariavel++;
            controleDeColunas(x);
            termo(tk, lugarVariavel);}
    }
x--;
}

//Expressão 
void expressao(leituraDeLinha tk[], int lugar){
// <expressão simples> [ <relação> <expressão simples> ]
 printf(" EXPRESSAO\n");
    x++;
    controleDeColunas(x);
    expressaoSimples(tk, lugar);
    
    if(tk[lugarVariavel].simbolo != '\0' || tk[lugarVariavel].simbolos != NULL){
        controleDeColunas(x);
        relacao(tk, lugarVariavel);
        controleDeColunas(x);
        expressaoSimples(tk, lugarVariavel);
    }
    x--;
}

//Comando 
void comando(leituraDeLinha tk[], int lugar){
// <atribuição> | <comando composto> | <comando condicional> | <comando repetitivo>

printf(" COMANDO\n");
x++;
controleDeColunas(x);
    if (tk[lugar].palavraReservada == NULL){tk[lugar].palavraReservada = "Vazia";}

    if(strcmp(tk[lugar].palavraReservada, TOKEN_BEGIN) == 0){
        comandoComposto(tk, lugar);

    } else if(strcmp(tk[lugar].palavraReservada, TOKEN_IF) == 0){
        // if <expressão> then <comando> [ else <comando> ] -- <Comando condicional>

        
        printf(" CONTROLE CONDICIONAL\n");
        x++;
        controleDeColunas(x);
        printf(" Palavra Reservada: %s\n", tk[lugar].palavraReservada);
        lugarVariavel++;
        controleDeColunas(x);
        expressao(tk, lugarVariavel);
        
        //Verifica se a proxima palavra é then:
        if (tk[lugarVariavel].palavraReservada == NULL){tk[lugarVariavel].palavraReservada = "Vazia";}
        if(strcmp(tk[lugarVariavel].palavraReservada, TOKEN_THEN) == 0){

            controleDeColunas(x);
            printf(" Palavra Reservada: %s\n", tk[lugarVariavel].palavraReservada);
            lugarVariavel++;

            controleDeColunas(x);
            comando(tk, lugarVariavel);
            identificadorDeSimbolos(tk, ';', lugarVariavel);
            
            //Verifica se tem else (não é obrigado a ter);
            if(strcmp(tk[lugarVariavel].palavraReservada, TOKEN_ELSE) == 0){
                controleDeColunas(x);
                printf(" Palavra Reservada: %s\n", tk[lugarVariavel].palavraReservada);
                lugarVariavel++;
                x++;
                controleDeColunas(x);
                comando(tk, lugarVariavel);
                x--;
            }

        } else {
            //Se não for then
            printf(" Linha: %d - Erro de Syntax: 'then' esperada no lugar de: ", tk[lugarVariavel].linha);
            //Mostra oq foi escrito no lugar
            palavraNaoEsperada(tk, lugarVariavel);
        }
        
    } else if(strcmp(tk[lugar].palavraReservada, TOKEN_WHILE) == 0){
        // while <expressão> do <comando> -----> <Comando repetitivo>
        printf(" COMANDO REPETITIVO\n");
        x++;
        controleDeColunas(x);
        printf(" Palavra Reservada: %s\n", tk[lugar].palavraReservada);
        lugarVariavel++;
        controleDeColunas(x);
        expressao(tk, lugarVariavel);
        
        if(strcmp(tk[lugarVariavel].palavraReservada, TOKEN_DO) == 0){
            controleDeColunas(x);
            printf(" Palavra Reservada: %s\n", tk[lugarVariavel].palavraReservada);
            lugarVariavel++;
            x++;
        } else {
        //Se não for do
        printf(" Linha: %d - Erro de Syntax: 'do' esperada no lugar de: ", tk[lugar].linha);
        //Mostra oq foi escrito no lugar
        palavraNaoEsperada(tk, lugarVariavel);   
        }
    
    controleDeColunas(x);
    comando(tk, lugarVariavel);
    
    x--;
    } else if(tk[lugar].variavel != NULL){
        // <variável> := <expressão> ----------> <atribuição>
        printf(" ATRIBUICAO\n");
        x++;
        controleDeColunas(x);
        printf(" Variavel: %s\n", tk[lugar].variavel);
        lugarVariavel++;

        //Verifica se a proxima palavra é :=
        if(strcmp(tk[lugarVariavel].simbolos, TOKEN_DOISPONTOIGUAL) == 0){
            controleDeColunas(x);
            printf(" Simbulo Duplo: %s\n", tk[lugarVariavel].simbolos);
            lugarVariavel++;
            controleDeColunas(x);
            expressao(tk, lugarVariavel);
            lugarVariavel--;
            
        } else {
            //Se não for :=
                    controleDeColunas(x);
                    printf(" Linha: %d - Erro de Syntax: ':=' esperada no lugar de: ", tk[lugar].linha);
                    //Mostra oq foi escrito no lugar
                    palavraNaoEsperada(tk, lugar);
        }
        x--;
    } else {
        //Se não for Beguin, if, while ou variavel
        controleDeColunas(x);
        printf(" Linha: %d - Erro de Syntax: 'atribuicao, comando composto, comando condicional ou comando repetitico' esperada no lugar de: ", tk[lugar].linha);
        //Mostra oq foi escrito no lugar
        palavraNaoEsperada(tk, lugar);
    }
    x--;
}

//Comandos Compostos 
void comandoComposto(leituraDeLinha tk[], int lugar){
// begin <comando> { ; <comando> } end

printf(" COMANDO COMPOSTO\n");
x++;
controleDeColunas(x);

    //Verifica se a palavra é begin:
    if (tk[lugar].palavraReservada != NULL){
            contadorEnd++;
            printf(" Palavra Reservada: %s\n", tk[lugar].palavraReservada);
            lugarVariavel++;
            x++;            

            //Se a primeira palavra não for begin apresenta msg de erro!
            if(strcmp(tk[lugar].palavraReservada, TOKEN_BEGIN) != 0){
            printf(" Linha: %d - Erro de Syntax: 'begin' esperado!\n", tk[lugar].linha);
            exit(0);
            }
    } else {
        //Mostra oq foi escrito no lugar da palavra reservada
        printf(" Linha: %d - Erro de Syntax: 'begin' esperado no lugar de: ", tk[lugar].linha);
        palavraNaoEsperada(tk, lugar);
    }
    
    controleDeColunas(x);
    comando(tk, lugarVariavel);
    x--;
    
    while(tk[lugarVariavel].simbolo == ';'){
        
        printf(" Simbolo: %c\n", tk[lugarVariavel].simbolo);
        lugarVariavel++;

        if((tk[lugarVariavel].palavraReservada != NULL && strcmp(tk[lugarVariavel].palavraReservada, TOKEN_END) == 0)){break;}
        
        controleDeColunas(x);
        comando(tk,lugarVariavel);
        
    }
    x--;
    

    //Verifica se a palavra é end
    if (tk[lugarVariavel].palavraReservada != NULL) {
        
        if(contadorEnd ==1){x = 0;}
        controleDeColunas(x);
        printf(" Palavra Reservada: %s\n", tk[lugarVariavel].palavraReservada, x);
        lugarVariavel++;
        contadorEnd--;
        
        if(contadorEnd == 0){return;}
        
        //Se a primeira palavra não for program apresenta msg de erro!
        if(strcmp(tk[lugarVariavel].palavraReservada, TOKEN_END) != 0){
            controleDeColunas(x);
            printf(" Erro de Syntax: 'end' esperado!\n");
            exit(0);}
    } else {
        //Mostra oq estava escrito no lugar da palvara reservada
        controleDeColunas(x);
        printf(" Linha: %d - Erro de Syntax: 'end' esperado no lugar de: ", tk[lugar].linha);
        palavraNaoEsperada(tk, lugarVariavel);
    }
    x--;
}

//Verifica se existe uma ou mais variaveis
void declaracaoDeVariavel(leituraDeLinha tk[], int lugar){
// <lista de identificadores> : <tipo>
    printf(" DECLARACAO DE VARIAVEIS\n");
    x++;

    controleDeColunas(x);
    listaDeIdentificadores(tk, lugarVariavel);

    //Verifica se o proximo caracter é : e qual tipo {integer ou real}
    if(tk[lugarVariavel].simbolo == ':'){

            controleDeColunas(x);
            printf(" Simbolo: %c\n", tk[lugarVariavel].simbolo);
            lugarVariavel++;
            
            controleDeColunas(x);
            //Verifica se o proximo caracter é um tipo;
            if(strcmp(tk[lugarVariavel].palavraReservada, TOKEN_INTEGER) == 0){
                printf(" Palavra reservada: %s\n", tk[lugarVariavel].palavraReservada);
                lugarVariavel++;
                
            }else if(strcmp(tk[lugarVariavel].palavraReservada, TOKEN_REAL) == 0){
                printf(" Palavra reservada: %s\n", tk[lugarVariavel].palavraReservada);
                lugarVariavel++;

            } else {
                //Se não for um tipo;
                printf(" Linha: %d - Erro de Syntax: 'integer ou real' esperada no lugar de: ", tk[lugarVariavel].linha);
                //Mostra oq foi escrito no lugar;
                palavraNaoEsperada(tk, lugarVariavel);
            }
    } else {
        //Falta do :
        printf(" Linha: %d - Erro de Syntax: ':' esperada no lugar de: ", tk[lugarVariavel].linha);
        //Mostra oq foi escrito no lugar;
        palavraNaoEsperada(tk, lugarVariavel);
    }
    x--;
}

//lista de identificadores - verifica se tem ',' e mais variaveis a frente ou ':' e um TIPO finalizando com ';'
void listaDeIdentificadores(leituraDeLinha tk[], int lugar){
    //  <identificador> { , <identificador> }

    printf(" LISTA DE IDENTIFICADORES\n");
    x++;
    controleDeColunas(x);
    identificador(tk, lugarVariavel);

    while(tk[lugarVariavel].simbolo == ','){
        controleDeColunas(x);
        printf(" Simbolo: %c\n", tk[lugarVariavel].simbolo);
        lugarVariavel++;
        controleDeColunas(x);
        identificador(tk, lugarVariavel);
    }
    x--;
}

//Parte de declaração de variáveis  
void parteDeclaracaoDeVariaveis(leituraDeLinha tk[], int lugar){
// { var <declaração de variáveis> {; <declaração de variáveis>} ; }
printf(" PARTE DECLARACAO DE VARIAVEIS\n");
x++;
controleDeColunas(x);

    //Verificar se começa com var:
    if (tk[lugar].palavraReservada != NULL) {
            if(strcmp(tk[lugar].palavraReservada, TOKEN_VAR) == 0){
                printf(" Palavra Reservada: %s\n", tk[lugar].palavraReservada);
                lugarVariavel++;
            } else {
                printf(" Linha: %d - Erro de Syntax: 'Var' esperada no lugar de: ", tk[lugar].linha);
                //Mostra oq foi escrito no lugar
                palavraNaoEsperada(tk, lugar);}
        } else {
            printf(" Linha: %d - Erro de Syntax: 'Var' esperada no lugar de: ", tk[lugar].linha);
            //Mostra oq foi escrito no lugar
            palavraNaoEsperada(tk, lugar);
            printf("\n");
        }

controleDeColunas(x);
declaracaoDeVariavel(tk, lugarVariavel);

controleDeColunas(x);
identificadorDeSimbolos(tk, ';', lugarVariavel);

while(tk[lugarVariavel].variavel != NULL){
        controleDeColunas(x);
        declaracaoDeVariavel(tk, lugarVariavel);
        controleDeColunas(x);
        printf(" Simbolo: %c\n", tk[lugarVariavel].simbolo);
        lugarVariavel++;
}

x--;
}

//Bloco 
void bloco(leituraDeLinha tk[]){
    // <parte de declarações de variáveis> <comando composto>
    printf(" BLOCO\n");
    x++;
    controleDeColunas(x);

    //parte de declaração de variaveis
    parteDeclaracaoDeVariaveis(tk, lugarVariavel);
    //comando composto 
    controleDeColunas(x);
    comandoComposto(tk, lugarVariavel);
    x--;
}

//Verifica se é uma variavel 
void identificador(leituraDeLinha tk[], int lugar){
    // <letra> ( <letra> | <dígito> ) * ----> {Varivael}
    if (tk[lugar].variavel != NULL) {
            printf(" Variavel: %s\n", tk[lugar].variavel);
            lugarVariavel++;
        }else{
            printf(" Linha: %d - Erro de Syntax: 'varivael' esperada no lugar de: ", tk[lugar].linha);
            //Mostra oq foi escrito no lugar
            palavraNaoEsperada(tk, lugarVariavel);
        }
}

//verifica um simbolo especifico 
void identificadorDeSimbolos(leituraDeLinha tk[], char simbolo, int lugar){

    if (tk[lugar].simbolo != '\0') {
        printf(" Simbolo: '%c'\n", tk[lugar].simbolo);
        lugarVariavel++;

        //Verifica se é o simbolo esperado
        if(tk[lugar].simbolo != simbolo){
            printf(" Linha: %d - Erro de Syntax: '%c' esperado!\n\n", tk[lugarVariavel].linha, simbolo);
            //mostra oq foi escrito no lugar de program:
            palavraNaoEsperada(tk, lugarVariavel);
        }
    } else { 
        printf(" Linha: %d - Erro de Syntax: 'simbolo' esperado no lugar de: ", tk[lugar].linha);
        //Mostra oq foi escrito no lugar
        palavraNaoEsperada(tk, lugarVariavel);
    }
}

//Inicia um programa e um bloco 
void programaEBloco(leituraDeLinha tk[]){
    //program <identificador> ; <bloco> .
    x = 0;
    printf("PROGRAMA E BLOCO\n");
    controleDeColunas(x);

    //Verifica se iniciou o programa com program:
    if (tk[lugarVariavel].palavraReservada != NULL) {

        if(strcmp(tk[lugarVariavel].palavraReservada, TOKEN_PROGRAM) == 0){
            printf(" %s\n", tk[0].palavraReservada);
            lugarVariavel++;
            
          } else {
            printf(" Linha: %d - Erro de Syntax: titulo 'program' esperado! ", tk[lugarVariavel].linha);
            exit(0);
          }
        } else {
            printf(" Linha: %d - Erro de Syntax: 'program' esperado no lugar de: ", tk[lugarVariavel].linha);
            //Mostra oq foi escrito no lugar
            palavraNaoEsperada(tk, lugarVariavel);
        }

    //Verifica se a segunda palavra é uma variavel:
    controleDeColunas(x);
    identificador(tk, lugarVariavel);


    //Verifica se depois da variavel veio ;
    controleDeColunas(x);
    identificadorDeSimbolos(tk, ';', lugarVariavel);

    //bloco:
    controleDeColunas(x);
    bloco(tk);
    //Verifica se atem um . no final
    x--;
    controleDeColunas(x);
    if(tk[lugarVariavel].simbolo == TOKEN_PONTO){
        
        printf(" Simbolo simples: %c\n", tk[lugarVariavel].simbolo);
        
    } else {
        printf(" Linha: %d - Erro de Syntax: '.' esperada no lugar de: ", tk[lugarVariavel].linha);
            //Mostra oq foi escrito no lugar
            palavraNaoEsperada(tk, lugarVariavel);
    }
    
}
