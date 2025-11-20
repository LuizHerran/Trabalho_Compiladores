#include "sintaxico.h"


int main(void){

    //Nome do arquivo de entrada
    char *nome = "fonteInvalida3.pas";
    
    //Imprime e cria uma arquivo.lex fazendo a análise léxica
    printf("\n\t\tAnalisador lexico:\n");
    abrirarquivo(nome);

    //Imprime a árvore sintática
    printf("\n\n\n");
    printf("\t\tAnalisador sintatico:\n");
    programaEBloco(tk);
    
    return 0;
}
