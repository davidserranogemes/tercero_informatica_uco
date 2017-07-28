%{
#include "macros.h"
#include "ejemplo6.h"
#include "ejemplo6.tab.h"

extern char *progname;
extern int lineno;

%}
/* definiciones regulares */
numero        [0-9]
letra         [a-zA-Z]
identificador {letra}({letra}|{numero})*

%%
[ \t] { ; } /* saltar los espacios y los tabuladores */

{numero}+\.?|{numero}*\.{numero}+ { sscanf(yytext,"%lf",&yylval.val); 
				    return NUMBER;}

{identificador} { Symbol *s;
                   if ((s=lookup(yytext)) == 0)
                               s = install (yytext, INDEFINIDA, 0.0);
                    yylval.sym = s;
                    return s->tipo == INDEFINIDA ? VAR : s->tipo;}

:=      {return ASIGNACION;}
^#       { 
 	  CLEAR_SCREEN; 
	  LUGAR(10,10);
		IYELLOW;
	  printf(">>>>>>> Fin del programa <<<<<<<\n");
	  RESET;
	  LUGAR(12,1);

  	  return 0;
	}
;       {return FIN ;} 
\n      {lineno++; return FIN;} 
.       {return yytext[0];}
