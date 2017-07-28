%{
#include <ctype.h>

char *palabra;
int num_palabra=0;
void es_tu_palabra(char* text);
%}

palabra [^ \n\t]+
%%
{palabra} {es_tu_palabra(yytext);}
.|\n ;

%%
extern FILE *yyin;
void es_tu_palabra(char* text){
	int check=1;
	int different=0;
	int i=0;
	while(check){
		if(tolower(text[i])=='\0' || tolower(palabra[i])=='\0'){
			if(tolower(text[i])!=tolower(palabra[i])){
				different=1;
			}
			check=0;
		}else{
			if(tolower(text[i])!=tolower(palabra[i])){
				different=1;
				check=0;
			}
		}
		i++;
	}
	if(different==0){
		num_palabra++;
	}
}

void main(int argc, char* argv[]){
	if(argc!=3){
		printf("Syntax error. El formato es:\n./ejercicio4 fichero_entrada palabra\n");
	}else{
		yyin=fopen(argv[1],"r");
		palabra=argv[2];
		yylex();
		printf("El numero de ocurrencias es: %d\n",num_palabra);
	}
}
