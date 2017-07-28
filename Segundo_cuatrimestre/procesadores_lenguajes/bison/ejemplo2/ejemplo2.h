#ifndef EJEMPLO2_H
#define EJEMPLO2_H

/*  Tipo de datos de la pila de YACC */
#define YYSTYPE double  

/* Analizador léxico */
int yylex();

/* Informa de la detección de un error sintáctico */
void yyerror(char *s);

/*  Escribe por pantalla información sobre un error sintáctico */
void warning(char *s, char *t);

#endif
