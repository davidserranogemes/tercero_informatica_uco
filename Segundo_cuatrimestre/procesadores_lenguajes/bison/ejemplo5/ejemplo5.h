/*!
	\file ejemplo5.h 
	\brief Prototipos de funciones auxiliares
*/

#ifndef EJEMPLO5_H
#define EJEMPLO5_H

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

/* Inicializa la tabla de símbolos */
void init();

typedef struct Symbol { /* entrada en la tabla de simbolos */
	               char *nombre;
	               short tipo;  /* VAR, FUNCION, INDEFINIDA */ 
	               union {
		              double val;        /* si es VAR */
		              double (*ptr)();   /* si es FUNCION */
		             } u;
                       struct Symbol * siguiente;
	              } Symbol;


/* Instala en la tabla de símbolos */
Symbol *install(char *s, int t, double);

/* Busca en la tabla de símbolos */
Symbol *lookup(char *s);

#endif
