escribir_cadena('Introduzca el primer operando: ');
leer(dato);

escribir_cadena('\nIntroduzca el segundo operando: ');
leer(dato3);

escribir_cadena('Suma:');
res_suma:=dato+dato3;
escribir (res_suma);
escribir_cadena('\n');

escribir_cadena('Suma unaria:');
res_suma :=  +dato;
escribir (res_suma);
escribir_cadena('\n');

escribir_cadena('Resta:');
res_resta:=dato-dato3;
escribir (res_resta);
escribir_cadena('\n');

escribir_cadena('Resta unaria: ');
res_resta:=-dato;
escribir (res_resta);
escribir_cadena('\n');

escribir_cadena('Producto: ');
res_producto:=dato*dato3;
escribir(res_producto);
escribir_cadena('\n');

escribir_cadena('Division: ');
res_division := dato/dato3;
escribir (res_division);
escribir_cadena('\n');


escribir_cadena('Division entera: ');
res_div_entera := dato _div dato3;
escribir (res_div_entera);
escribir_cadena('\n');


escribir_cadena('Módulo:');
res_div_mod := dato _mod dato3;
escribir (res_div_mod);
escribir_cadena('\n');

escribir_cadena('Potencia:');
res_exp := dato ** dato3;
escribir (res_exp);
escribir_cadena('\n');

escribir_cadena('\nOperadores logicos:\n');


escribir_cadena('AND->  1=0 _y 0=0 \n');
res_y := 1=0 _y 0=0;
escribir (res_y);
escribir_cadena('\n');


escribir_cadena('OR->  1=0 _o 0=0 \n');
res_o := 1=0 _o 0=0;
escribir (res_o);
escribir_cadena('\n');


escribir_cadena('NOT->  _no 0 \n');
res_no := _no 0;
escribir(res_no);
escribir_cadena('\n');


escribir_cadena('\nOperador concatenacion:\n');
escribir_cadena('Introduzca la primera cadena: ');
leer_cadena(dato);

escribir_cadena('\nIntroduzca la segunda cadena: ');
leer_cadena(dato3);

escribir_cadena('Primera || segunda \n');
cadena:=dato || dato3;
escribir_cadena(cadena || '\n');

escribir_cadena('Segunda || primera \n');
cadena:=dato3 || dato;
escribir_cadena(cadena || '\n');



