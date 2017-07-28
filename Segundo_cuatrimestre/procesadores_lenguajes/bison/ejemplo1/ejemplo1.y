/*
 Ejemplo 1
 
 Interpreta expresiones aritméticas: suma, resta, multiplicación y división
 Permite expresiones entre paréntesis y el signo "-" unario

 No permite el signo "+" unario

 Las expresiones deben terminar con un salto de línea
 
  El programa finaliza pulsando Control + D
*/


%{ 
#include <stdio.h>

#include "ejemplo1.h"  /*  tipos de datos de la pila de yacc */


%}

%token NUMBER
%left '+' '-'   /* asociatividad a la izquierda; precedencia menor */
%left '*' '/'
%left UNARYMINUS /* maxima precedencia */ 

%%

list :       /* nada: epsilon - produccion */
        | list '\n'
        | list expr '\n'  {printf("\t%.8g\n",$2);}
        ;

expr :    NUMBER        {$$ = $1;}  /* $$ es el simbolo de expr y $1 el de NUMBER*/
        | expr '+' expr {$$ = $1 + $3;} /*$$ es el simbolo del primer expr, $1 el del 2º expr y $3 el de expr final */
        | expr '-' expr {$$ = $1 - $3;}
        | expr '*' expr {$$ = $1 * $3;}
        | expr '/' expr {$$ = $1 / $3;}
        | '(' expr ')'  {$$ = $2;}
        |'-' expr %prec UNARYMINUS { $$ = -$2; }
	;

%%

#include <stdio.h>
#include <ctype.h>

/* Depuracion
 1: habilitada
 0: no habilitada
 
 Se debe usar
  bison --debug ...
o
  bison -t
*/
int yydebug=0;
/*para seleccionar si depuramos o no*/

/* Nombre del programa */
char *progname;

/* Contador de líneas */
int lineno = 1;

int main(int argc, char *argv[])
{
 /* Nombre del programa */
 progname=argv[0];


/* Llamada al analizador sintáctico */
 yyparse();

 return 0;
}


/* Llamada en caso de error de sintaxis de yacc */
void yyerror(char *s)
{
 warning(s,(char *) 0);
}

/* Imprime mensajes de aviso */
void warning(char *s, char *t)
{
 fprintf(stderr,"%s: %s", progname,s);

 if (t) 
	fprintf(stderr," %s ",t);

 fprintf(stderr," en la linea %d \n",lineno);
}
