%{

int num_caracteres=0;
int num_palabras=0;
int num_lineas=1;
%}
palabra [^ \n\t]+
linea \n
%%

{linea} {num_lineas++;num_caracteres++;}
{palabra} {num_palabras++;num_caracteres=num_caracteres+yyleng;}
.|\n {num_caracteres++;}
%%
extern FILE *yyin;
void main(int argc, char* argv[]){
	if(argc!=2){
		printf("Syntax error. El formato es:\n./ejercicio3 fichero_entrada.\n");
	}else{
		yyin=fopen(argv[1],"r");
		yylex();
		printf("El numero de caracteres es: %d\n",num_caracteres);
		printf("El numero de palabras es: %d\n",num_palabras);
		printf("El numero de lineas es: %d\n",num_lineas);
	}
}