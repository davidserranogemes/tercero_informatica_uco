#ifndef EJEMPLO3_H
#define EJEMPLO3_H

/* Analizador léxico */
int yylex();

/* Informa de la detección de un error sintáctico */
void yyerror(char *s);

/* Recuperacion de errores durante la ejecucion */
void execerror(char *s,char *t);

/*  Escribe por pantalla información sobre un error sintáctico */
void warning(char *s, char *t);

/* Captura de errores de punto flotante */
void fpecatch();

#endif
