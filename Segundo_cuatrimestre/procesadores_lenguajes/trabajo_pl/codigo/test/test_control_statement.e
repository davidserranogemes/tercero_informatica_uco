a:=1;
b:=2;
c:='cadena';

escribir_cadena('SENTENCIAS IF: \n');
si (a=1)
entonces
	escribir_cadena('Esta bien inicializado \n');
si_no
	a:=1;
	escribir_cadena('No esta bien inicializado \n');
fin_si;

si (c)
entonces
	escribir_cadena('Si no evalua cadenas, ¿como has llegado aqui? \n');
si_no
	a:=1;
	escribir_cadena('Si no evalua cadenas, ¿como has llegado aqui? \n');
fin_si;

si (a=1)
	escribir_cadena('Esta bien inicializado \n');
si_no
	a:=1;
fin_si;

si (a=1)
	escribir_cadena('Esta bien inicializado \n');
fin_si;

escribir_cadena('\n\nBUCLE MIENTRAS:');
mientras(a<10) hacer
	escribir_cadena('\nSe repite hasta que a sea mayor que 10 ---> a=');
	a:=a+1;
	escribir(a);
fin_mientras;

escribir_cadena('\n\nBUCLE REPETIR:');
repetir
	escribir_cadena('\n Se repite hasta que a sea menor que b \n---> a=');
	a:=a+1;
	escribir(a);
	escribir_cadena('---> b=');
	b:=b*2;
	escribir(b);
hasta(b>a);

escribir_cadena('\n\nBUCLES PARA:\n');
para i desde 0 hasta 10 paso -1 hacer
	escribir_cadena('Este bucle no debe ejecutarse \n');
fin_para;
para i desde 0 hasta 10 paso 0 hacer
	escribir_cadena('Este bucle no debe ejecutarse \n');
fin_para;

para i desde 10 hasta 0 paso 1 hacer
	escribir_cadena('Este bucle no debe ejecutarse \n');
fin_para;

para i desde 1 hasta 3 paso 1 hacer
	escribir_cadena('Esta sentencia debe aparecer 3 veces \n');
fin_para;
