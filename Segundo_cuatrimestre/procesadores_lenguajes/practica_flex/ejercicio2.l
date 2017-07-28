/**Zona de declaraciones o definiciones*/
%{
#include <stdio.h>
#include <math.h>
double es_multiplo(float num);

%}
numero -?[0-9]+\.?[0-9]*
/* Zona de reglas */

%%

{numero} {fprintf(yyout,"%f",es_multiplo(atof(yytext)));}
.|\n {fprintf(yyout,"%s",yytext);}
%%
/**Zona de funciones auxiliares */

extern FILE *yyin, *yyout;
int sumador, divisor;

double es_multiplo(float num){
	double check= fmod((double)num,(double)divisor);
	printf("%f\n",check );
	if (check>-0.0000000001 && check<0.00000000001 && num>=0){
		return num+sumador;
	}else{
		return num;
	}
}

void main(int argc, char* argv[]){
	if(argc!=5){
		printf("Syntax error. El formato es:\n./ejercicio2 fichero_entrada fichero_salida sumador divisor\n");
	}else{
		yyin=fopen(argv[1],"r");
		yyout=fopen(argv[2],"w");
		sumador=atoi(argv[3]);
		divisor=atoi(argv[4]);
		yylex();
	}


}



