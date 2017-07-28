%{
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "ipe.h"
#include "macros.h"

#define code2(c1,c2)         code(c1); code(c2)
#define code3(c1,c2,c3)      code(c1); code(c2); code(c3)
%}

%union{             
       Symbol *sym;    /* puntero a la tabla de simbolos */
       Inst *inst;     /* instruccion de maquina */
}

%token <sym> NUMBER CADENA VAR CONSTANTE FUNCION0_PREDEFINIDA FUNCION1_PREDEFINIDA FUNCION2_PREDEFINIDA INDEFINIDA PRINT PRINT_CADENA WHILE DO END_WHILE IF THEN ELSE END_IF READ READ_CADENA REPEAT UNTIL BORRAR LUGAR FOR FROM STEP END_FOR
%type <inst> stmt asgn expr stmtlist cond while if variable repeat end for
%right ASIGNACION
%left O_LOGICO
%left Y_LOGICO
%left MAYOR_QUE MENOR_QUE MENOR_IGUAL MAYOR_IGUAL DISTINTO IGUAL
%left '+' '-' CONCATENAR
%left '*' '/' MODULO DIVISION_ENTERA
%left UNARIO NEGACION
%right POTENCIA  
%%

list :    /* nada: epsilon produccion */ 
        | list stmt  ';' {code(STOP); return 1;}
        | list error ';'   {yyerrok;} 
        ;

stmt :    /* nada: epsilon produccion */  {$$=progp;}
        | asgn          {code(pop2);}
	    | PRINT expr    {code(escribir); $$ = $2;}
        | BORRAR { code(borrar);}
        | LUGAR '(' expr ',' expr ')' {code(lugar);}
        | PRINT_CADENA expr   {code(escribir_cadena); $$ = $2;}
        | READ '(' VAR ')'    {code2(leervariable,(Inst)$3);}
        | READ_CADENA '(' VAR ')'    {code2(leervariablecadena,(Inst)$3);}
        | while cond DO stmtlist END_WHILE end  
                  {
                   ($1)[1]=(Inst)$4; /* cuerpo del bucle */
                   ($1)[2]=(Inst)$6; /* siguiente instruccion al bucle */
                  }
        | if cond THEN stmtlist END_IF end /* proposicion if sin parte else */
                  {
                   ($1)[1]=(Inst)$4; /* cuerpo del if */
                   ($1)[3]=(Inst)$6; /* siguiente instruccion al if */
                  }
        | if cond THEN stmtlist end ELSE stmtlist END_IF end /* proposicion if con parte else */
                  {
                   ($1)[1]=(Inst)$4; /* cuerpo del if */
                   ($1)[2]=(Inst)$7; /* cuerpo del else */
                   ($1)[3]=(Inst)$9; /* siguiente instruccion al if-else */
                  }
        | if cond stmtlist end ELSE stmtlist END_IF	end {execerror("Se se necesita la particula entonces tras la condicion del si.", (char * )0);}
        | if cond stmtlist END_IF end {execerror("Se se necesita la particula entonces tras la condicion del si.", (char * )0);}

        | repeat stmtlist end UNTIL cond end 
                  {
                    ($1)[1]=(Inst)$5; /* cuerpo del bucle */
                    ($1)[2]=(Inst)$6; /* siguiente instruccion al bucle */
                  }
        | for variable FROM expr end UNTIL expr end STEP expr end DO stmtlist END_FOR end
        		{
        			($1)[1]=(Inst)$4; /* Punto de partida de la variable*/
        			($1)[2]=(Inst)$7; /* Limite */
        			($1)[3]=(Inst)$10; /* Tamaño de paso */
        			($1)[4]=(Inst)$13; /* Lineas a repetir*/
        			($1)[5]=(Inst)$15; /* Siguiente instruccion al bucle para */
        		}
        ;


asgn :    VAR ASIGNACION expr { $$=$3; code3(varpush,(Inst)$1,assign);}
        | CONSTANTE ASIGNACION expr 
          {execerror(" NO se pueden asignar datos a constantes ",$1->nombre);}
	;

cond :    '(' expr ')' {code(STOP); $$ =$2;}
        ;
repeat   :    REPEAT         {$$=code3(dowhilecode,STOP,STOP);}

while:    WHILE      {$$= code3(whilecode,STOP,STOP);}
        ;

if:       IF         {$$= code(ifcode); code3(STOP,STOP,STOP);}
        ;
for: 	  FOR 		 {$$= code3(paracode,STOP,STOP); code3(STOP,STOP,STOP); }

end :    /* nada: produccion epsilon */  {code(STOP); $$ = progp;}
        ;

stmtlist:  /* nada: prodcuccion epsilon */ {$$=progp;}
        | stmtlist stmt ';'
        ;

expr :    NUMBER     		{$$=code2(constpush,(Inst)$1);}
		| CADENA     		{$$=code2(constpush_cadena,(Inst)$1);}
        | VAR        		{$$=code3(varpush,(Inst)$1,eval);} 
        | CONSTANTE      	{$$=code3(varpush,(Inst)$1,eval);}
        | asgn 
        | FUNCION0_PREDEFINIDA '(' ')'      {code2(funcion0,(Inst)$1->u.ptr);}
        | FUNCION1_PREDEFINIDA '(' expr ')' {$$=$3;code2(funcion1,(Inst)$1->u.ptr);}
        | FUNCION2_PREDEFINIDA '(' expr ',' expr ')'
                                            {$$=$3;code2(funcion2,(Inst)$1->u.ptr);}
        | '(' expr ')'  	{$$ = $2;}
        | expr CONCATENAR expr   {code(concatenar);}
        | expr '+' expr 	{code(sumar);}
        | expr '-' expr 	{code(restar);}
        | expr '*' expr 	{code(multiplicar);}
        | expr '/' expr 	{code(dividir);}
        | expr DIVISION_ENTERA expr {code(dividir_entera);}
        | expr MODULO expr 	{code(modulo);}
        | expr POTENCIA expr 	{code(potencia);}
        |'-' expr %prec UNARIO 	{$$=$2; code(negativo);}
        |'+' expr %prec UNARIO 	{$$=$2; code(positivo);}
        | expr MAYOR_QUE expr 	{code(mayor_que);}
        | expr MAYOR_IGUAL expr {code(mayor_igual);}
        | expr MENOR_QUE expr 	{code(menor_que);}
        | expr MENOR_IGUAL expr {code(menor_igual);}
        | expr IGUAL expr 	{code(igual);}
        | expr DISTINTO expr 	{code(distinto);}
        | expr Y_LOGICO expr 	{code(y_logico);}
        | expr O_LOGICO expr 	{code(o_logico);}
        | NEGACION expr 	{$$=$2; code(negacion);}
      	;
variable: VAR {code((Inst)$1);$$ = progp;}
	;
%%

#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <setjmp.h>

/* Depuracion
 1: habilitada
 0: no habilitada
 
 Se debe usar
  bison --debug ...
o
  bison -t
*/
int yydebug=0;

/* Nombre del programa */
char *progname;

/* Contador de líneas */
int lineno = 1;

/* Permite la recuperación de errores */
jmp_buf begin;

/* Dispositivo de entrada estándar de yylex() */
extern FILE * yyin;


int main(int argc, char *argv[])
{
 /* Si se invoca el intérprete con un fichero de entrada */
 /* entonces se establece como dispositivo de entrada para yylex() */
 if (argc == 2){
    if(argv[1][strlen(argv[1])-1]!='e' || argv[1][strlen(argv[1])-2]!='.'){
      printf("Mal formato de entrada. El fichero debe ser .e\n");
      exit(-1);
    }
    yyin = fopen(argv[1],"r");
    if(yyin==NULL){
      printf("El fichero %s no existe.\n",argv[1]);
      exit(-1);
    }
 }

 progname=argv[0];

 /* inicializacion de la tabla de simbolos */
 init();

/* Establece un estado viable para continuar despues de un error */
 setjmp(begin);

 /* Establece cual va a ser la funcion para tratar errores de punto flotante */
 signal(SIGFPE,fpecatch); /* Excepcion de punto flotante*/

/* initcode inicializa el vector de intrucciones y la pila del interprete */
 for (initcode(); yyparse(); initcode()) execute(prog);

 return 0;

}

void yyerror(char *s)
{
 warning(s,(char *) 0);
}

void warning(char *s, char *t)
{
 fprintf(stderr," ** %s : %s", progname,s);
 if (t) fprintf(stderr," ---> %s ",t);
 fprintf(stderr,"  (linea %d)\n",lineno);
}

void execerror(s,t) /* recuperacion de errores durante la ejecucion */
char *s,*t;
{
 warning(s,t);
  longjmp(begin,0);
}

void fpecatch()     /*  atrapa errores de punto flotante */
{
 execerror("error de punto flotante ",(char *)0);
}

