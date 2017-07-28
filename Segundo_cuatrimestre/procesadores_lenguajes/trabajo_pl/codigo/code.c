#include <stdio.h>
#include  <math.h>
#include <stdlib.h>
#include <string.h>

#include "ipe.h"
#include "ipe.tab.h"

#include "macros.h"

#define NSTACK 256              /* Dimension maxima de la pila */
static Datum stack[NSTACK];     /* La pila */
static Datum *stackp;           /* siguiente lugar libre en la pila */

#define NPROG 2000 
Inst prog[NPROG];  /* La maquina */
Inst *progp;       /* Siguiente lugar libre para la generacion de codigo */

Inst *pc; /* Contador de programa durante la ejecucion */

void initcode() /* inicializacion para la generacion de codigo */
{
 stackp = stack;
 progp = prog;
}

void push(Datum d) /* meter d en la pila */
{
 
/* Comprobar que hay espacio en la pila para el nuevo valor o variable */
 
 if (stackp >= &stack[NSTACK])
     execerror (" Desborde superior de la pila ", (char *) 0);
 
 *stackp++ =d; /* Apilar la variable o el numero y */
               /* desplazar el puntero actual de la pila */
}


Datum pop() /* sacar y devolver de la pila el elemento de la cima */
{
 
/* Comprobar que no se intenta leer fuera de la pila */ 
/* En teoria no ocurrira nunca */
 
 if (stackp <= stack)
     execerror (" Desborde inferior de la pila ", (char *) 0);
 
 --stackp;          /* Volver hacia atras una posicion en la pila */
 return(*stackp);   /* Devolver variable o numero */
}

void pop2() /* sacar y  NO devolver el elemento de la cima de la pila */
{
 
/* Comprobar que no se intenta leer fuera de la pila */ 
/* En teoria no ocurrira nunca */
 
 if (stackp <= stack)
     execerror (" Desborde inferior de la pila ", (char *) 0);
 
 --stackp;          /* Volver hacia atras una posicion en la pila */
}

Inst *code(Inst f) /* Instalar una instruccion u operando */
{
 Inst *oprogp = progp;   /* Puntero auxiliar */
 
/* Comprobar que hay espacio en el vector de instrucciones */ 

 if (progp >= &prog[NPROG])
     execerror (" Programa demasiado grande", (char *) 0);
 
 *progp=f;        /* Asignar la instruccion o el puntero a la estructura */
 progp++;         /* Desplazar una posicion hacia adelante */
 return (oprogp);
}


void execute(Inst *p)  /* Ejecucion con la maquina */
{
 
/* El contador de programa pc se inicializa con la primera instruccion a */ 
/* ejecutar */
 
 for (pc=p; *pc != STOP;   )
    (*(*pc++))();              /* Ejecucion de la instruccion y desplazar */
}                              /* el contador de programa pc */

/****************************************************************************/
/****************************************************************************/

void assign() /* asignar el valor superior al siguiente valor */
{
 Datum d1,d2;

 d1=pop();    /* Obtener variable */
 d2=pop();    /* Obtener numero o cadena  */

 if (d1.sym->tipo != VAR && d1.sym->tipo != INDEFINIDA)
   execerror(" asignacion a un elemento que no es una variable ", 
	     d1.sym->nombre);

  if(d2.subtipo==NUMBER){

	  d1.sym->u.val=d2.val;   /* Asignar valor   */
	  d1.sym->tipo=VAR;
	  d1.sym->subtipo=NUMBER;
	  d1.tipo=VAR;
	  d1.subtipo=NUMBER;


	}else{
		if(d2.subtipo==CADENA){

			/* Reservamos memoria */
			free(d1.sym->u.cadena);
			d1.sym->u.cadena = (char*) calloc (strlen(d2.cadena)+1,sizeof(char));

			strcpy(d1.sym->u.cadena,d2.cadena);
			d1.sym->tipo=VAR;
			d1.sym->subtipo=CADENA;
			d1.tipo=VAR;
	  		d1.subtipo=CADENA;

		}else{
			execerror("Error de inicialización del subtipo. Se esta intentado asignar a algo que no es una variable de numero o de cadena ", (char * )0);
		}
	}

  push(d2);               /* Apilar variable */
}

void constpush()  /* meter una constante en la pila */
{
 Datum d;
 
 d.val= ((Symbol *)*pc++)->u.val;
 d.tipo=NUMBER;
 d.subtipo=NUMBER;
 push(d);
}

void constpush_cadena()  /* meter una cadena en la pila */
{
 Datum d;
 /* REservar memoria y introducir valor de la cadena, llorar fuertemente*/
 int i;
 char * aux=((Symbol *)*pc++)->u.cadena;
 
 d.cadena =(char*) calloc(strlen(aux)+1, sizeof(char));
 
 	for(i=0;i<strlen(aux);i++){
	  	d.cadena[i]=aux[i];
 	}
 d.tipo=CADENA;
 d.subtipo=CADENA;
 push(d);
}

void borrar(){
  CLEAR_SCREEN;
}

void lugar(){
  Datum d1, d2;
  d2=pop();
  d1=pop();

  if(d1.subtipo==NUMBER && d2.subtipo==NUMBER){
      LUGAR((int)d1.val,(int)d2.val);
  }else{
    execerror("Error de syntaxis, lugar solo acepta 2 numeros", (char *) 0);
  }
}

void dividir() /* dividir los dos valores superiores de la pila */
{
 Datum d1,d2;
 
 d2=pop();      /* Obtener el primer numero  */
 d1=pop();      /* Obtener el segundo numero */
 
/* Comprobar si hay division por 0 */ 
 if(d1.subtipo==NUMBER && d2.subtipo==NUMBER){
     if (d2.val == 0.0)
      execerror (" Division por cero ", (char *) 0);
 
      d1.val = d1.val / d2.val;    /* Dividir             */
      push(d1);                    /* Apilar el resultado */
  }else{
    execerror("Error de syntaxis, la division solo acepta 2 numeros", (char *) 0);
  }

}

void dividir_entera() /* dividir de forma entera los dos valores superiores de la pila */
{
 Datum d1,d2;
 
 d2=pop();      /* Obtener el primer numero  */
 d1=pop();      /* Obtener el segundo numero */
 
/* Comprobar si hay division por 0 */ 
 
 if(d1.subtipo==NUMBER && d2.subtipo==NUMBER){
     if (d2.val == 0.0)
      execerror (" Division por cero ", (char *) 0);
 
      d1.val = d1.val / d2.val;    /* Dividir             */
      d1.val=(int)d1.val;			/* Fuerza a que la division sea entera */
      push(d1);                    /* Apilar el resultado */
  }else{
    execerror("Error de syntaxis, la division entera solo acepta 2 numeros", (char *) 0);
  }
}

void escribir() /* sacar de la pila el valor superior y escribirlo */
{
 Datum d;
 d=pop();  /* Obtener numero */
 if(d.subtipo==NUMBER){
 	printf("%.8g",d.val);
 }else{
 	printf("Syntax error, no es un numero\n");

 }
}

void escribir_cadena() /* sacar de la pila el valor superior y escribirlo */
{
 Datum d;
 
 d=pop();  /* Obtener numero */
 if(d.subtipo==CADENA){
 	printf("%s",d.cadena);
 }else{
 	printf("Syntax error, no es una cadena\n");

 }
}

void eval() /* evaluar una variable en la pila */
{
 Datum d;
 
 d=pop();  /* Obtener variable de la pila */
 
/* Si la variable no esta definida */ 
 if (d.sym->tipo == INDEFINIDA) 
     execerror (" Variable no definida ", d.sym->nombre);
 
 
 if(d.sym->subtipo==NUMBER){
 	d.val=d.sym->u.val;  /* Sustituir variable por valor */
 	d.subtipo=NUMBER;
 }else{
 	if(d.sym->subtipo==CADENA)
 		d.subtipo=CADENA;

		d.cadena = (char*) calloc (strlen(d.sym->u.cadena)+1,sizeof(char));
		strcpy(d.cadena,d.sym->u.cadena);

 }
 push(d);             /* Apilar valor */
}

void funcion0() /* evaluar una funcion predefinida sin parametros */
{
 Datum d;
 
 d.val= (*(double (*)())(*pc++))();
 push(d);
}

void funcion1() /* evaluar una funcion predefinida con un parametro */
{
 Datum d;
 
 d=pop();  /* Obtener parametro para la funcion */

 d.val= (*(double (*)())(*pc++))(d.val);
 push(d);
}

void funcion2() /* evaluar una funcion predefinida con dos parametros */
{
 Datum d1,d2;
 
 d2=pop();  /* Obtener parametro para la funcion */
 d1=pop();  /* Obtener parametro para la funcion */

 d1.val= (*(double (*)())(*pc++))(d1.val,d2.val);
 push(d1);
}

/* resto de la division entera del segundo valor de la pila */
/* por el valor de la cima */
void modulo() 
{
 Datum d1,d2;
 
 d2=pop();      /* Obtener el divisor */
 d1=pop();      /* Obtener el dividendo */
 
/* Comprobar si hay division por 0 */ 
 if(d1.subtipo==NUMBER && d2.subtipo==NUMBER){
     if (d2.val == 0.0)
      execerror (" Division por cero ", (char *) 0);
 
 d1.val = (int) d1.val % (int)  d2.val;  /* Resto */
      push(d1);                    /* Apilar el resultado */
  }else{
    execerror("Error de syntaxis, el modulo solo acepta 2 numeros", (char *) 0);
  }
}

void multiplicar() /* multiplicar los dos valores superiores de la pila */
{
 Datum d1,d2;
 
 d2=pop();                   /* Obtener el primer numero  */
 d1=pop();                   /* Obtener el segundo numero */
 if(d1.subtipo==NUMBER && d2.subtipo==NUMBER){
        d1.val = d1.val * d2.val;   /* Producto                    */
        push(d1);                   /* Apilar el resultado       */
  }else{
    execerror("Error de syntaxis, el producto solo acepta 2 numeros", (char *) 0);
  }                  
}

void negativo() /* negacion del valor superior de la pila */
{
 Datum d1;
 
 d1=pop();              /* Obtener numero   */
 if(d1.subtipo==NUMBER){
   d1.val = - d1.val;     /* Aplicar menos    */
   push(d1);              /* Apilar resultado */
 }else{
    execerror("Error de syntaxis, el negativo solo acepta numeros", (char *) 0);

 }
}

/* Esta funcion se puede omitir   */
void positivo() /* tomar el valor positivo del elemento superior de la pila */
{
 Datum d1;
 
  d1=pop();              /* Obtener numero   */
 if(d1.subtipo==NUMBER){
    push(d1);              /* Apilar resultado */
 }else{
    execerror("Error de syntaxis, el positivo solo acepta numeros", (char *) 0);
 }            /* Apilar resultado */
}

void potencia()  /* exponenciacion de los valores superiores de la pila */
{
 Datum d1,d2;
 
 d2=pop();                      /* Obtener exponente   */
 d1=pop();                      /* Obtener base        */
 
if(d1.subtipo==NUMBER && d2.subtipo==NUMBER){
    if ( (d1.val>=0) || ((int)d2.val == d2.val) )
    {
     d1.val = pow(d1.val,d2.val);   /* Elevar a potencia   */
     push(d1);                      /* Apilar el resultado */
    }
   else 
    {
     char digitos[20];
     sprintf(digitos,"%lf",d1.val);
     execerror(" Radicando negativo ", digitos);
    }
  }else{
     execerror("Error de syntaxis, la potencia solo acepta 2 numeros", (char *) 0);

  }
}

void restar()   /* restar los dos valores superiores de la pila */
{
 Datum d1,d2;
 
 d2=pop();                   /* Obtener el primer numero  */
 d1=pop();                   /* Obtener el segundo numero */
if(d1.subtipo==NUMBER && d2.subtipo==NUMBER){
        d1.val = d1.val - d2.val;   /* Restar                     */
        push(d1);                   /* Apilar el resultado       */
  }else{
    execerror("Error de syntaxis, la resta solo acepta 2 numeros", (char *) 0);
  }                    /* Apilar el resultado       */
}

void sumar()   /* sumar los dos valores superiores de la pila */
{
 Datum d1,d2;
 
 d2=pop();                   /* Obtener el primer numero  */
 d1=pop();

  if(d1.subtipo==NUMBER && d2.subtipo==NUMBER){
        d1.val = d1.val + d2.val;   /* Sumar                     */
        push(d1);                   /* Apilar el resultado       */
  }else{
    execerror("Error de syntaxis, la suma solo acepta 2 numeros", (char *) 0);
  }                   /* Obtener el segundo numero */

}

void concatenar(){
  Datum d1, d2;
  char cadena1[100];
  char cadena2[100];
  char cadena_end[201];
  d2=pop();
  d1=pop();
  if(d1.subtipo==NUMBER){
    sprintf(cadena1, "%g",d1.val);
  }else{
    strcpy(cadena1,d1.cadena);
  }
  if(d2.subtipo==NUMBER){
    sprintf(cadena2, "%g",d2.val);
  }else{
    strcpy(cadena2,d2.cadena);
  }

  d1.subtipo=CADENA;

  strcpy(cadena_end,strcat(cadena1,cadena2));
  free(d1.cadena);
  d1.cadena = (char*) calloc (strlen(cadena_end)+1,sizeof(char));
  strcpy(d1.cadena,cadena_end);
  push(d1);

}

void varpush()  /* meter una variable en la pila */
{
 Datum d;

 d.sym=(Symbol *)(*pc++);
 push(d);
}
/****************************************************************************/
/****************************************************************************/

void leervariable() /* Leer una variable numerica por teclado */
{
 Symbol *variable;
 char c;

 variable = (Symbol *)(*pc); 

 /* Se comprueba si el identificador es una variable */ 
  if ((variable->tipo == INDEFINIDA) || (variable->tipo == VAR))
    { 
    while((c=getchar())=='\n') ;
    ungetc(c,stdin);
    scanf("%lf",&variable->u.val);
    variable->tipo=VAR;
    variable->subtipo=NUMBER;
    pc++;

   }
 else
     execerror("No es una variable",variable->nombre);
}



void leervariablecadena() /* Leer una variable numerica por teclado */
{
 Symbol *variable;
 char c;

 variable = (Symbol *)(*pc); 

 /* Se comprueba si el identificador es una variable */ 
  if ((variable->tipo == INDEFINIDA) || (variable->tipo == VAR))
    { 
    while((c=getchar())=='\n') ;
    ungetc(c,stdin);
    char auxiliar[100];


 	fgets(auxiliar, 100, stdin);
 	auxiliar[strlen(auxiliar)-1]='\0';

 	/*Convierte los  \' en ' */
 	int j=0;
  	int i;
	for(i=0;i<strlen(auxiliar) && j<strlen(auxiliar);i++){
		if(auxiliar[j]=='\\' && auxiliar[j+1]=='\''){
				j++;
				
				}
		auxiliar[i]=auxiliar[j];
		if(j==strlen(auxiliar)-1 && i!=j){
				auxiliar[i+1]='\0';
			}
			j++;
		}

	/*Convierte los \n y \t, en los caracteres reales de tabulacion y salto de linea*/
  	j=0;
    for(i=0;i<strlen(auxiliar) && j<strlen(auxiliar);i++){
      if(auxiliar[j]=='\\' && auxiliar[j+1]=='n'){
        auxiliar[i]='\n';
        j++;
      }else{
        if(auxiliar[j]=='\\' && auxiliar[j+1]=='t'){
          auxiliar[i]='\t';
          j++;
        }else{
          auxiliar[i]=auxiliar[j];
        }
      }
      j++;
    }
    auxiliar[i]='\0';

	auxiliar[strlen(auxiliar)]='\0';

	free(variable->u.cadena);
 	variable->u.cadena=(char*) calloc (strlen(auxiliar)+1,sizeof(char));

 	strcpy(variable->u.cadena,auxiliar);

 	variable->tipo=VAR;
    variable->subtipo=CADENA;
    pc++;

   }
 else
     execerror("No es una variable",variable->nombre);
}  


void mayor_que()
{
 Datum d1,d2;
 int aux_cmp=0;

 d2=pop();   /* Obtener el primer numero  */
 d1=pop();   /* Obtener el segundo numero */
 if(d1.subtipo==NUMBER && d2.subtipo==NUMBER){
   if (d1.val > d2.val)
     d1.val= 1;
   else
     d1.val=0;
  push(d1);  /* Apilar resultado */
 }else{
  if(d1.subtipo==CADENA && d2.subtipo==CADENA){
    aux_cmp=strcmp(d1.cadena,d2.cadena);
    if(aux_cmp<0){
      /* Cadena izq menor que la derecha */
      d1.val=0;
    }else{
      if(aux_cmp>0){
        /* Cadena izq mayor que la derecha */
        d1.val=1;
      }else{
        if(aux_cmp==0){
          /* Cadena izq igual que la derecha */
        d1.val=0;

        }
      }
    }
    d1.subtipo=NUMBER;
    d1.sym->subtipo==NUMBER;
    push(d1);
  }else{
    execerror("No se pueden comparar numeros y cadenas",(char * ) 0);
  }
 }
 
}


void menor_que()
{
 Datum d1,d2;
 int aux_cmp;

 d2=pop();    /* Obtener el primer numero  */
 d1=pop();    /* Obtener el segundo numero */
 
  if(d1.subtipo==NUMBER && d2.subtipo==NUMBER){
   if (d1.val < d2.val)
     d1.val= 1;
   else
     d1.val=0;
  push(d1);  /* Apilar resultado */
 }else{
  if(d1.subtipo==CADENA && d2.subtipo==CADENA){
    aux_cmp=strcmp(d1.cadena,d2.cadena);
    if(aux_cmp<0){
      /* Cadena izq menor que la derecha */
      d1.val=1;
    }else{
      if(aux_cmp>0){
        /* Cadena izq mayor que la derecha */
        d1.val=0;
      }else{
        if(aux_cmp==0){
          /* Cadena izq igual que la derecha */
        d1.val=0;

        }
      }
    }
    d1.subtipo=NUMBER;
     d1.sym->subtipo==NUMBER;
    push(d1);
  }else{
    execerror("No se pueden comparar numeros y cadenas",(char * ) 0);
  }
 }
}


void igual()
{
 Datum d1,d2;
 int aux_cmp;

 d2=pop();    /* Obtener el primer numero  */
 d1=pop();    /* Obtener el segundo numero */
 
  if(d1.subtipo==NUMBER && d2.subtipo==NUMBER){
   if (d1.val == d2.val)
     d1.val= 1;
   else
     d1.val=0;
  push(d1);  /* Apilar resultado */
 }else{
  if(d1.subtipo==CADENA && d2.subtipo==CADENA){
    aux_cmp=strcmp(d1.cadena,d2.cadena);
    if(aux_cmp<0){
      /* Cadena izq menor que la derecha */
      d1.val=0;
    }else{
      if(aux_cmp>0){
        /* Cadena izq mayor que la derecha */
        d1.val=0;
      }else{
        if(aux_cmp==0){
          /* Cadena izq igual que la derecha */
        d1.val=1;

        }
      }
    }
    d1.subtipo=NUMBER;
     d1.sym->subtipo==NUMBER;
    push(d1);
  }else{
    execerror("No se pueden comparar numeros y cadenas",(char * ) 0);
  }
 }
}

void mayor_igual()
{
 Datum d1,d2;
 int aux_cmp;

 d2=pop();    /* Obtener el primer numero  */
 d1=pop();    /* Obtener el segundo numero */
 
  if(d1.subtipo==NUMBER && d2.subtipo==NUMBER){
   if (d1.val >= d2.val)
     d1.val= 1;
   else
     d1.val=0;
  push(d1);  /* Apilar resultado */
 }else{
  if(d1.subtipo==CADENA && d2.subtipo==CADENA){
    aux_cmp=strcmp(d1.cadena,d2.cadena);
    if(aux_cmp<0){
      /* Cadena izq menor que la derecha */
      d1.val=0;
    }else{
      if(aux_cmp>0){
        /* Cadena izq mayor que la derecha */
        d1.val=1;
      }else{
        if(aux_cmp==0){
          /* Cadena izq igual que la derecha */
        d1.val=1;

        }
      }
    }
    d1.subtipo=NUMBER;
     d1.sym->subtipo==NUMBER;
    push(d1);
  }else{
    execerror("No se pueden comparar numeros y cadenas",(char * ) 0);
  }
 }
}


void menor_igual()
{
 Datum d1,d2;
 int aux_cmp;

 d2=pop();     /* Obtener el primer numero  */
 d1=pop();     /* Obtener el segundo numero */
 
  if(d1.subtipo==NUMBER && d2.subtipo==NUMBER){
   if (d1.val <= d2.val)
     d1.val= 1;
   else
     d1.val=0;
  push(d1);  /* Apilar resultado */
 }else{
  if(d1.subtipo==CADENA && d2.subtipo==CADENA){
    aux_cmp=strcmp(d1.cadena,d2.cadena);
    if(aux_cmp<0){
      /* Cadena izq menor que la derecha */
      d1.val=1;
    }else{
      if(aux_cmp>0){
        /* Cadena izq mayor que la derecha */
        d1.val=0;
      }else{
        if(aux_cmp==0){
          /* Cadena izq igual que la derecha */
        d1.val=1;
        }
      }
    }
    d1.subtipo=NUMBER;
     d1.sym->subtipo==NUMBER;
    push(d1);
  }else{
    execerror("No se pueden comparar numeros y cadenas",(char * ) 0);
  }
 }
}

void distinto()
{
 Datum d1,d2;
 int aux_cmp;

 d2=pop();    /* Obtener el primer numero  */
 d1=pop();    /* Obtener el segundo numero */
 
  if(d1.subtipo==NUMBER && d2.subtipo==NUMBER){
   if (d1.val != d2.val)
     d1.val= 1;
   else
     d1.val=0;
  push(d1);  /* Apilar resultado */
 }else{
  if(d1.subtipo==CADENA && d2.subtipo==CADENA){
    aux_cmp=strcmp(d1.cadena,d2.cadena);
    if(aux_cmp<0){
      /* Cadena izq menor que la derecha */
      d1.val=1;
    }else{
      if(aux_cmp>0){
        /* Cadena izq mayor que la derecha */
        d1.val=1;
      }else{
        if(aux_cmp==0){
          /* Cadena izq igual que la derecha */
        d1.val=0;

        }
      }
    }
    d1.subtipo=NUMBER;
     d1.sym->subtipo==NUMBER;
    push(d1);
  }else{
    execerror("No se pueden comparar numeros y cadenas",(char * ) 0);
  }
 }
}


void y_logico()
{
 Datum d1,d2;
 
 d2=pop();    /* Obtener el primer numero  */
 d1=pop();    /* Obtener el segundo numero */
 
 if(d1.subtipo==NUMBER && d2.subtipo==NUMBER){
	 if (d1.val==1 && d2.val==1)
	   d1.val= 1;
	 else 
	   d1.val=0;
	 
	 push(d1);    /* Apilar el resultado */
 }else{
 	execerror("Esta operación solo acepta valores numericos",(char *) 0);
 }
}


void o_logico()
{
 Datum d1,d2;
 
 d2=pop();    /* Obtener el primer numero  */
 d1=pop();    /* Obtener el segundo numero */
  if(d1.subtipo==NUMBER && d2.subtipo==NUMBER){
	 if (d1.val==1 || d2.val==1)
	   d1.val= 1;
	 else 
	   d1.val=0;
	 
	 push(d1);    /* Apilar el resultado */
 }else{
 	execerror("Esta operación solo acepta valores numericos",(char *) 0);
 }
}


void negacion()
{
 Datum d1;
 
 d1=pop();   /* Obtener numero */
 if(d1.subtipo==NUMBER){
 	if (d1.val==0)
 	  	d1.val= 1;
 	else
   		d1.val=0;
 
 	push(d1);   /* Apilar resultado */
 }else{
 	execerror("Esta operación solo acepta valores numericos",(char *) 0);
 }
}

void dowhilecode()
{
 Datum d;
 Inst *savepc = pc;    /* Puntero auxiliar para guardar pc */

 
 
 do  
    {
     execute(savepc+2);               /* Ejecutar codigo */
     execute(*((Inst **)(savepc)));   /* Ejecutar condicion */
      d=pop();              /* Obtener el resultado de la condicion */
    }while(!d.val); /* Mientras no se cumpla la condicion */
 
/* Asignar a pc la posicion del vector de instrucciones que contiene */  
/* la siguiente instruccion a ejecutar */ 
 
 pc= *((Inst **)(savepc+1));  
}
void whilecode()
{
 Datum d;
 Inst *savepc = pc;    /* Puntero auxiliar para guardar pc */

 execute(savepc+2);    /* Ejecutar codigo de la condicion */
 
 d=pop();    /* Obtener el resultado de la condicion de la pila */
 
 while(d.val)   /* Mientras se cumpla la condicion */
    {
     execute(*((Inst **)(savepc)));   /* Ejecutar codigo */
     execute(savepc+2);               /* Ejecutar condicion */
     d=pop();              /* Obtener el resultado de la condicion */
    }
 
/* Asignar a pc la posicion del vector de instrucciones que contiene */  
/* la siguiente instruccion a ejecutar */ 
 
 pc= *((Inst **)(savepc+1));  
}

void ifcode()
{
 Datum d;
 Inst *savepc = pc;   /* Puntero auxiliar para guardar pc */

 execute(savepc+3);   /* Ejecutar condicion */
 d=pop();             /* Obtener resultado de la condicion */
 
 
/* Si se cumple la condición ejecutar el cuerpo del if */
 if(d.subtipo!=CADENA){
  if(d.val)
   execute(*((Inst **)(savepc)));
 
/* Si no se cumple la condicion se comprueba si existe parte else   */
/* Esto se logra ya que la segunda posicion reservada contendria el */
/* puntero a la primera instruccion del cuerpo del else en caso de  */
/* existir, si no existe sera\A0 STOP, porque a la hora de generar    */
/* codigo se inicializa con STOP.                                   */

 else if  (*((Inst **)(savepc+1)))  /* parte else */
   execute(*((Inst **)(savepc+1)));
 }else{
    execerror("'Si' necesita de una condición evaluable numericamente. No se admiten cadenas.",(char *) 0);
 }
 
 

/* Asignar a pc la posicionel vector de instrucciones que contiene */  
/* la siguiente instruccion a ejecutar */ 
 
 pc= *((Inst **)(savepc+2));
}

void paracode(){
	Datum from, until, step;
	Symbol * var;
	Inst *savepc =pc; /* puntero auxiliar para guardar pc */


	/* Variable  bucle para*/
	var= *((Symbol**)(savepc+5));

	var->tipo=VAR;

	var->subtipo=NUMBER;

	/*FROM*/
	execute(*((Inst **)(savepc)));
	from=pop();

	/*UNTIL*/
	execute(*((Inst **)(savepc+1)));
	until=pop();
  
  /*STEP*/
  execute(*((Inst **)(savepc+2)));
  step=pop();
   
  if(from.val<until.val && step.val<=0){
    execerror("Para infinito, parametro DESDE no alcanza nunca a HASTA porque decrece en vez de crecer. ",(char * )0);
  }else{
    if(from.val>until.val && step.val>=0){
      execerror("Para infinito, parametro DESDE no alcanza nunca a HASTA porque crece en vez de decrecer. ",(char * )0);
    }else{
      for(var->u.val=from.val;var->u.val<=until.val;var->u.val=var->u.val+step.val){
        execute(*((Inst **)(savepc+3)));
      }
    }
  }

 
	

	
	/* Asignar a pc la posicionel vector de instrucciones que contiene */  
	/* la siguiente instruccion a ejecutar */ 
	pc=*((Inst **)(savepc+4));
}


