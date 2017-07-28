%{
#include <ctype.h>
#include <stdio.h>

#include "macros.h"
#include "ipe.h"
#include "ipe.tab.h"
extern char *progname;
extern int lineno;
%}
/* definiciones regulares */
/* Para la cadena hacer como en el eje 7 de flex, luego crear un install cadena e instalar la cadena como se instala el numero pero en vez de d yytext*/

numero        [0-9]
letra         [a-zA-Z]
identificador {letra}({letra}|{numero}|_?({letra}|{numero}))*

id_doble_barra_baja {letra}({letra}|{numero}|__+({letra}|{numero}))*
id_inicio_barra_baja _({letra}|{numero}|_?({letra}|{numero}))*
id_inicio_numero {numero}({letra}|{numero}|_?({letra}|{numero}))*

negacion (?i:_no)
o_logico (?i:_o)
y_logico (?i:_y)
modulo (?i:_mod)
division_entera (?i:_div)
comentario_simple @.*

borrar (?i:_borrar)
lugar (?i:_lugar)


%x ESTADO_CADENA
%x ESTADO_COMENTARIO


%%
{borrar} {return BORRAR;}
{lugar} {return LUGAR;}
{comentario_simple} { ; } 

{negacion}	{return NEGACION;}
{o_logico}	{return O_LOGICO;}
{y_logico}	{return Y_LOGICO;}
{modulo} {return MODULO;}
{division_entera} {return DIVISION_ENTERA;}



[ \t] { ; } /* saltar los espacios y los tabuladores */

{numero}+(\.{numero}+)?([e|E][\+|-]?{numero}+)?		{double d;  
                            sscanf(yytext,"%lf",&d);
                            /* Instala el numero en la tabla de simbolos */
				   			yylval.sym=install("",NUMBER,d); 

				   return NUMBER;}




{identificador} { Symbol *s;
					int i=0;
					while(yytext[i]){
						yytext[i]=tolower(yytext[i]);
						i++;
					}

                   if ((s=lookup(yytext)) == 0)
                               s = install (yytext, INDEFINIDA, 0.0);
                    yylval.sym = s;


                    return s->tipo == INDEFINIDA ? VAR : s->tipo;}

{id_inicio_barra_baja} {printf("Error lexico, no se permite empezar un identificador con barra baja.\n");}
{id_doble_barra_baja} {printf("Error lexico, no se permiten dos barras bajas seguidas.\n");}
{id_inicio_numero} {printf("Error lexico, no se permite empezar un identificador con numero.\n");}


"<"	{return MENOR_QUE;}
"<="	{return MENOR_IGUAL;}
">"	{return MAYOR_QUE;}
">="	{return MAYOR_IGUAL;}
"="	{return IGUAL;}
"<>"	{return DISTINTO;}


":="      {return ASIGNACION;}

"**"	{return POTENCIA;}
"||"	{return CONCATENAR;}


"'" {BEGIN ESTADO_CADENA;}
<ESTADO_CADENA>"'" { /*Fin de la cadena */
					BEGIN 0;
					yytext[yyleng-1]='\0';
					/*El -1 hace que se elimine el ''*/
					
					
					int j=0;
					int i;
					for(i=0;i<strlen(yytext) && j<strlen(yytext);i++){

						if(yytext[j]=='\\' && yytext[j+1]=='\''){
	 						j++;
	 					}
	 					
						yytext[i]=yytext[j];
						
						if(j==strlen(yytext)-1 && i!=j){
	 						yytext[i+1]='\0';
	 					}
	 					j++;
 					}
 				
					yytext[strlen(yytext)]='\0';								

					j=0;
					for(i=0;i<strlen(yytext) && j<strlen(yytext);i++){
						if(yytext[j]=='\\' && yytext[j+1]=='n'){
							yytext[i]='\n';
							j++;
						}else{
							if(yytext[j]=='\\' && yytext[j+1]=='t'){
								yytext[i]='\t';
								j++;
							}else{
								yytext[i]=yytext[j];
							}
						}
						j++;
					}
					yytext[i]='\0';								


					yylval.sym=install_cadena("",CADENA,yytext); /**/
				   	return CADENA;
					}
<ESTADO_CADENA>"\\\'" {yymore();}
<ESTADO_CADENA>. {yymore();}
<ESTADO_CADENA>\n {yymore();}




"#" {BEGIN ESTADO_COMENTARIO;}
<ESTADO_COMENTARIO>"#" { /*Fin de comentario*/
					BEGIN 0;
					{ ; }
					}
<ESTADO_COMENTARIO>. {yymore();}
<ESTADO_COMENTARIO>\n {yymore();}						

 	 
\n      {lineno++; } /* no se devuelve nada, continúa el analisis léxico */
"&" {printf("Error caracter no valido: %c . Linea: %d", yytext[0],lineno);return yytext[0];}
"!" {printf("Error caracter no valido: %c . Linea: %d", yytext[0],lineno);return yytext[0];}
"¿" {printf("Error caracter no valido: %c . Linea: %d", yytext[0],lineno);return yytext[0];}
"¡" {printf("Error caracter no valido: %c . Linea: %d", yytext[0],lineno);return yytext[0];}
"?" {printf("Error caracter no valido: %c . Linea: %d", yytext[0],lineno);return yytext[0];}

.       {return yytext[0];}
