/**Zona de declaraciones o definiciones*/

%{
#include <stdio.h>
int es_multiplo(int num);

%}
/* Zona de reglas */
numero [0-9]+

%%
{numero} {fprintf(yyout,"%d",es_multiplo(atoi(yytext)));}
.|\n   {fprintf(yyout,"%s",yytext);}
%%

/**Zona de funciones auxiliares */
extern FILE *yyin, *yyout;

int es_multiplo(int num){
	if(num%3==0){
		return 0;
	}else{
		return num;
	}
}

void main(int argc, char *argv[]){
	
	if(argc!=3){
		printf("Syntax error. El formato es:\n./ejercicio1 fichero_entrada fichero_salida\n");
	}else{
		yyin=fopen(argv[1],"r");
		yyout=fopen(argv[2],"w");
		yylex();
	}
}