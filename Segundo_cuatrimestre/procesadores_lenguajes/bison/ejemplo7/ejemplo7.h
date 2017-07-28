/*!
	\file ejemplo7.h 
	\brief Prototipos de funciones auxiliares
*/

#ifndef EJEMPLO7_H
#define EJEMPLO7_H

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

typedef union Datum { /* tipo de la pila del interprete */ 
                     double val;
                     Symbol *sym;
                    } Datum;


/* Función que introduce un dato de la pila de valores */
void push(Datum d);

/* Funciones que sacan un dato de la pila de valores */
extern Datum pop();
extern void pop2();

typedef void (*Inst)(); /* instruccion maquina */
#define STOP (Inst) 0

/* Vector de instrucciones */
extern Inst prog[];

/* Función que inicializa el vector de instrucciones */
void initcode();

/* Función que inserta una instucción en el vector de instrucciones */
Inst *code(Inst f);

/* Función que ejecuta una función del vector de instrucciones */
void execute(Inst *p);

/* Prototipos de funciones auxiliares */
extern void assign();
extern void constpush();
void dividir();
void escribir();
void eval();
void funcion();
void modulo();
void multiplicar();
void negativo();
void positivo();
void potencia(); 
void restar();
void sumar();
void varpush();

#endif