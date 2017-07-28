/*Cadena es mejorable intentar que al mostrar por pantalla no muestr \' sino ' 
Segun se coloque el - delante de un numero es un numero negativo o la operacion menos y un numero
*/

%{
#include <ctype.h>
#include "reserved_word_code.h"
int getToken(char* palabra_reservada);
%}

reserved_word (?i:inicio)|(?i:fin)|(?i:__mod)|(?i:__o)|(?i:__y)|(?i:__no)|(?i:leer)|(?i:escribir)|(?i:si)|(?i:entonces)|(?i:si_no)|(?i:fin_si)|(?i:mientras)|(?i:hacer)|(?i:fin_mientras)|(?i:repetir)|(?i:hasta_que)|(?i:para)|(?i:desde)|(?i:hasta)|(?i:paso)|(?i:fin_para)

identificador [a-z|A-Z]([a-z|A-Z|0-9]*_?[a-z|A-Z|0-9]*)*
one_letter_identificator [a-z|A-Z]

numero_real [0-9]+(\.[0-9]+|[0-9]*)
numero_cientifico {numero_real}e-?{numero_real}+
numero -?({numero_real}|{numero_cientifico}) 

%x ESTADO_CADENA

asignacion :=

suma \+
resta -
producto \*
division \/
modulo __mod
potencia \*\*

concatenacion \|\|

menor_que <
menor_igual_que <=
mayor_que >
mayor_igual_que >=
igual ==
distinto <>

disyuncion_logica __o
conjuncion_logica __y
negacion_logica __no

comentario_simple #.*
%x ESTADO_COMENTARIO

fin_sentencia ;
parentesis_izquierdo \(
parentesis_derecho \)

/* Posibles malos identificadores */
double_underline [a-z|A-Z]([a-z|A-Z|0-9]*__+[a-z|A-Z|0-9]*)*
wrong_init [0-9|_]([a-z|A-Z|0-9]*_?[a-z|A-Z|0-9])*
bad_end [a-z|A-Z]([a-z|A-Z|0-9]*_?[a-z|A-Z|0-9])*_

/* Hay que hacer todas las combinaciones para que lo detecte integramente como un unico error*/
du_wi [0-9|_]([a-z|A-Z|0-9]*__+[a-z|A-Z|0-9]*)*
du_be [a-z|A-Z]([a-z|A-Z|0-9]*__+[a-z|A-Z|0-9]*)*_
wi_be [0-9|_]([a-z|A-Z|0-9]*_?[a-z|A-Z|0-9])*_

du_wi_be [0-9|_]([a-z|A-Z|0-9]*__+[a-z|A-Z|0-9]*)*_

/* Fin malos identificadores*/
bad_identificator ({double_underline}|{wrong_init}|{bad_end}|{du_wi}|{du_be}|{wi_be}|{du_wi_be})


/* Malos numeros */
double_dot [0-9]+\.[0-9]*\.([0-9]*\.?[0-9]*)*
double_exp {numero_real}e-?{numero_real}*(e-?{numero_real}*)+

/* combinaciones y mezclas extrañas */
double_dot_in_exp {numero_real}e-?{double_dot}
double_dot_in_exp_num {double_dot}e-?[0-9]+
double_dot_in_both {double_dot}e-?{double_dot}
double_dot_with_double_exp {numero_real}e-?[0-9]*(e-?{double_dot}*)+

bad_num ({double_dot}|{double_exp}|{double_dot_in_exp}|{double_dot_in_exp_num}|{double_dot_in_both}|{double_dot_with_double_exp})

%%
{modulo} {printf("Operacion aritmetica: modulo \n");}
{disyuncion_logica} {printf("Operacion logica: disyuncion\n");}
{conjuncion_logica} {printf("Operacion logica: conjuncion\n");}
{negacion_logica} {printf("Operacion logica: negacion \n");}
{concatenacion} {printf("Operación alfanumerica: concatenación \n");}
{bad_num} {printf("Numero erroneo: %s\n",yytext);}
{numero} {printf("Numero: %s\n",yytext);}
{one_letter_identificator} {printf("Identificador: %s\n",yytext);}
{bad_identificator} {printf("Identificador erroneo: %s\n",yytext);}
{reserved_word} {printf("Palabra reservada: %s -->token %d\n",yytext,getToken(yytext));}
{identificador} {printf("Identificador: %s\n",yytext);}
{asignacion} {printf("Operacion de asignacion: =\n");}
{suma} {printf("Operacion aritmetica: +\n");}
{resta} {printf("Operacion aritmetica: -\n");}
{producto} {printf("Operacion aritmetica: *\n");}
{division} {printf("Operacion aritmetica: /\n");}
{potencia} {printf("Operacion aritmetica: potencia \n");}
{menor_que} {printf("Operacon relacional: menor que\n");}
{menor_igual_que} {printf("Operacon relacional: menor o igual que\n");}
{mayor_que} {printf("Operacon relacional: mayor que\n");}
{mayor_igual_que} {printf("Operacon relacional: mayor o igual que\n");}
{igual} {printf("Operacon relacional: igual que\n");}
{distinto} {printf("Operacon relacional: distinto que\n");}
{comentario_simple} {printf("Comentario de una sola linea: %s\n",yytext);}
{fin_sentencia} {printf("Final de sentencia\n");}
{parentesis_izquierdo} {printf("Apertura de parentesis\n");}
{parentesis_derecho} {printf("Cierre de parentesis\n");}


"(*" {BEGIN ESTADO_COMENTARIO;}
<ESTADO_COMENTARIO>"*)" {/*Fin de comentario*/
						BEGIN 0;
						yytext[yyleng-2]='\0'; //El -2 hace que se elimine el *)
						printf("Comentario de varias lineas: %s\n",yytext);
						}
<ESTADO_COMENTARIO>. {yymore();}
<ESTADO_COMENTARIO>\n {yymore();}


"'" {BEGIN ESTADO_CADENA;}
<ESTADO_CADENA>"'" {/*Fin de la cadena*/
					BEGIN 0;
			    	yytext[yyleng-1]='\0'; //El -1 hace que se elimine el ''
			    	printf("Cadena: %s\n",yytext);
					}
<ESTADO_CADENA>"\\\'"     {yymore();}

<ESTADO_CADENA>.          {yymore();}

<ESTADO_CADENA>\n         {yymore();}

[ |\t|\n] ;
. {printf("Parasito encontrado! El caracter: %s no esta permitido.\n",yytext);}

%%

void main(int argc, char* argv[]){
	if(argc!=2){
		printf("Error de sintaxis.\nSe debe escribir: ./ejercicio7 nombre-fichero\n");
	}else{
		yyin=fopen(argv[1],"r");
		yylex();
	}
}


int getToken(char* palabra_reservada){
	int i=0;
	while(palabra_reservada[i]){
		palabra_reservada[i]=tolower(palabra_reservada[i]);
		i++;
	}
	//printf("%s\n",palabra_reservada);

	if(strcmp(palabra_reservada,"inicio")==0){
		return INICIO;
	}
	if(strcmp(palabra_reservada,"fin")==0){
		return FIN;
	}
	if(strcmp(palabra_reservada,"__mod")==0){
		return __MOD;
	}
	if(strcmp(palabra_reservada,"__o")==0){
		return __O;
	}
	if(strcmp(palabra_reservada,"__y")==0){
		return __Y;
	}
	if(strcmp(palabra_reservada,"__no")==0){
		return __NO;
	}
	if(strcmp(palabra_reservada,"leer")==0){
		return LEER;
	}
	if(strcmp(palabra_reservada,"escribir")==0){
		return ESCRIBIR;
	}
	if(strcmp(palabra_reservada,"si")==0){
		return SI;
	}
	if(strcmp(palabra_reservada,"entonces")==0){
		return ENTONCES;
	}
	if(strcmp(palabra_reservada,"si_no")==0){
		return SI_NO;
	}
	if(strcmp(palabra_reservada,"fin_si")==0){
		return FIN_SI;
	}
	if(strcmp(palabra_reservada,"mientras")==0){
		return MIENTRAS;
	}
	if(strcmp(palabra_reservada,"hacer")==0){
		return HACER;
	}
	if(strcmp(palabra_reservada,"fin_mientras")==0){
		return FIN_MIENTRAS;
	}
	if(strcmp(palabra_reservada,"repetir")==0){
		return REPETIR;
	}
	if(strcmp(palabra_reservada,"hasta_que")==0){
		return HASTA_QUE;
	}
	if(strcmp(palabra_reservada,"para")==0){
		return PARA;
	}
	if(strcmp(palabra_reservada,"desde")==0){
		return DESDE;
	}
	if(strcmp(palabra_reservada,"hasta")==0){
		return HASTA;
	}
	if(strcmp(palabra_reservada,"paso")==0){
		return PASO;
	}
	if(strcmp(palabra_reservada,"fin_para")==0){
		return FIN_PARA;
	}
	return -1;
}

