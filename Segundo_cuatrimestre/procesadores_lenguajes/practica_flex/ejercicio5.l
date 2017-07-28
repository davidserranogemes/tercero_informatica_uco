%{
#include <ctype.h>

char *palabra;
char *sustituta;

int num_palabra=0;
char *es_tu_palabra(char* text);
%}

palabra [^ \n\t]+
%%
{palabra} {fprintf(yyout,"%s",es_tu_palabra(yytext));}
.|\n {fprintf(yyout,"%s",yytext);}

%%
char *es_tu_palabra(char* text){
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
		return sustituta;
	}else{
		return text;
	}
}
void main(int argc, char* argv[]){

	switch(argc){
		case 2:
			palabra= malloc( 100 * sizeof(char) );
			sustituta= malloc( 100 * sizeof(char) );

			printf("Introduce la palabra a sustituir: \n");
			fgets (palabra, 100, stdin);
			palabra[strlen(palabra)-1]='\0';

			printf("Introduce la palabra que sustituye a: %s\n",palabra);
			fgets (sustituta, 100, stdin);
			sustituta[strlen(sustituta)-1]='\0';
			break;
		case 3:
			sustituta= malloc( 100 * sizeof(char) );
			palabra=argv[2];

			printf("Introduce la palabra que sustituye a: %s\n",palabra);
			fgets (sustituta, 100, stdin);
			sustituta[strlen(sustituta)-1]='\0';
			break;
		case 4:
			palabra=argv[2];
			sustituta=argv[3];
			break;
		default:
			printf("Syntax error. El formato es:\n./ejercicio4 fichero_entrada palabra_sustituir palabra_sustituta\n");
			break;
	}

		char tmp[100];
		char rm[200];
		strcpy(tmp,argv[1]);
		strcat(tmp,".tmp");

		strcpy(rm,"rm -f ");
		strcat(rm,tmp);
		yyin=fopen(argv[1],"r");
		yyout=fopen(tmp,"w");
		
		yylex();
		fclose(yyin);
		fclose(yyout);

		yyin=fopen(tmp,"r");
		yyout=fopen(argv[1],"w");
		system(rm);
		yylex();
	
}
