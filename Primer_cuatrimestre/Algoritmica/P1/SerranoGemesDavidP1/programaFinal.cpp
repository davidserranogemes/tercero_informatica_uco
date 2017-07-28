#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

#include "generarDatosInversa.hpp"
#include "generarDatosFibonacci.hpp"
#include "minimosCuadradosMatriz.hpp"
#include "minimosCuadradosFib.hpp"
#include "datosEstimadosMatriz.hpp"
#include "datosEstimadosFib.hpp"

int main(){

	std::ifstream stream;

	std::string nombreFib="componentesFibonacci.txt";
	std::string nombreMatriz="componentesMatriz.txt";
	std::string GNUPLOT;

	std::vector < long double > a;

	long double coeficienteR, t; 
	long double const microsegDia=8.64e+10;
	
	int valor;
	int option=1;
	int min=0,max=0, inc=1;
	system("clear");

do{
	std::cout<<std::endl;
	std::cout<<std::endl;
	std::cout<<std::endl;
	do{ //Tienes que hacer que vuelva salvo que pulse 0
		if(option!=1 and option!=2){
			std::cout<<"Introduzca 1-10"<<std::endl;
		}
		std::cout<<"Selecione que tiempo desea estimar: "<<std::endl;
		std::cout<<"0. Salir del programa:"<<std::endl;
		std::cout<<"1. Calculo del elemento n de la sucesion de Fibonacci recursivamente:"<<std::endl;
		std::cout<<"2. Calculo de la matriz inversa de dimensiones nxn "<<std::endl;
		std::cout<<"3. Preparacion completa para poder estimar tiempos de la matriz inversa: "<<std::endl;
		std::cout<<"4. Preparacion completa para poder estimar tiempos de la sucesion de Fibonacci:"<<std::endl;
		std::cout<<"5. Obtener valores reales de matriz inversa: "<<std::endl;
		std::cout<<"6. Obtener valores reales de sucesion de Fibonacci: "<<std::endl;
		std::cout<<"7. Obtener ecuacion de estimacion para la matriz inversa. Requiere tener datos previos:"<<std::endl;
		std::cout<<"8. Obtener ecuacion de estimacion para la sucesion de Fibonacci. Requiere tener datos previos:"<<std::endl;
		std::cout<<"9. Obtener el coeficiente de determinacion de la ecuacion de la inversa y crear grafica GNUPLOT"<<std::endl;
		std::cout<<"10. Obtener el coeficiente de determinacion de la ecuacion de la Fibonacci y crear grafica GNUPLOT"<<std::endl;

		std::cin>>option;
	}while(option<0 and option>11);

	switch(option){
		case 1:	

			stream.open(nombreFib);
			if(stream.is_open()){
				a.resize(2);

				stream>>a[0];		
				stream>>a[1];
				stream>>coeficienteR;
				stream.close();
				do{
					std::cout<<std::endl;

					std::cout<<"Introduzca un valor n positivo. 0 para acabar de estimar."<<std::endl;
					std::cout<<"Coeficiente de determinacion: "<<coeficienteR<<std::endl;
					std::cout<<"Nota: valores muy pequeños no dan valores reales."<<std::endl;
					std::cout<<"t= "<<a[0]<<" + "<<a[1]<<" * 2^n"<<std::endl;
					std::cin>>valor;
					if(valor!=0){
						t= a[0] + a[1]*pow(2,valor);		
						std::cout<<"Tiempo estimado: "<<t/microsegDia<<" dias."<<std::endl;
					}
					std::cout<<std::endl;

				}while(valor!=0);
			}else{
				std::cout<<"No existen el fichero componentesFibonacci.txt. Sin el no se pueden hacer los calculos."<<std::endl;
				std::cout<<"Ejecute las opciones 6 8 y 10 en ese orden si desea comprobar paso a paso."<<std::endl;
				std::cout<<"Ejecute la opcion 4 para trabajar automaticamente."<<std::endl;
			}		
			break;
		case 2:
			stream.open(nombreMatriz);
			if(stream.is_open()){
				std::cout<<std::endl;

				a.resize(5);

				stream>>a[0];
				stream>>a[1];
				stream>>a[2];
				stream>>a[3];
				stream>>a[4];
				stream>>coeficienteR;
				stream.close();
				do{
					std::cout<<"Introduzca un valor n positivo. 0 para acabar de estimar."<<std::endl;
					std::cout<<"Coeficiente de determinacion: "<<coeficienteR<<std::endl;
					std::cout<<"Nota: valores muy pequeños no dan valores reales."<<std::endl;
					std::cout<<"t= "<<a[0]<<" + "<<a[1]<<" * n + "<<a[2]<<" * n^2 + "<<a[3]<<" * n^3 + "<<a[4]<<" * n^4"<<std::endl;
					std::cin>>valor;
					if(valor!=0){
						t= a[0] + a[1]*valor+a[2]*pow(valor,2)+a[3]*pow(valor,3)+a[4]*pow(valor,4);		
						std::cout<<"Tiempo estimado: "<<t/microsegDia<<" dias."<<std::endl;
					}
				}while(valor!=0);
				std::cout<<std::endl;

	
			}else{
				std::cout<<"No existen el fichero componentesMatriz.txt. Sin el no se pueden hacer los calculos."<<std::endl;
				std::cout<<"Ejecute las opciones 5 7 y 9 en ese orden si desea comprobar paso a paso."<<std::endl;
				std::cout<<"Ejecute la opcion 3 para trabajar automaticamente. "<<std::endl;
			}
			break;
		
		case 3:
			//Preparacion completa de matriz inversa, todo solo!
			do{
			std::cout<<"Se recomienda que los valores min y maximo sean valores lo suficientemente grandes como para que el tiempo no se vea afectado en gran medida por las rutinas del ordenador."<<std::endl;
			std::cout<<"Por favor introduzca un valor para la dimension minima de la matriz:"<<std::endl;
			std::cin>>min;
			std::cout<<"Por favor introduzca un valor para la dimension maxima de la matriz:"<<std::endl;
			std::cin>>max;
			std::cout<<"Por favor introduzca un valor para el incremento de la dimensiond de la matriz:"<<std::endl;
			std::cin>>inc;
			}while(min>max or min<0 or max<0 or inc<0);
			generarDatosInversa(min,max,inc);
			minimosCuadradosMatriz();
			datosEstimadosInversa();

			std::cout<<"Ahora puede usar GNUPLOT"<<std::endl;


			break;
		
		case 4:
			//Preparacion completa de fibonacci, todo solo!
			//METERVALORES POR DEFECTO A min max e inc
			do{
			std::cout<<"Se recomienda que los valores min y maximo sean valores lo suficientemente grandes como para que el tiempo no se vea afectado en gran medida por las rutinas del ordenador."<<std::endl;
			std::cout<<"Por favor introduzca un valor para el elemento minimo de la sucesion de Fibonacci que desea calcular: "<<std::endl;
			std::cin>>min;
			std::cout<<"Por favor introduzca un valor para el elemento maximo de la sucesion de Fibonacci que desea calcular:"<<std::endl;
			std::cin>>max;
			std::cout<<"Por favor introduzca un valor para el incremento de los terminos de la sucesiond de Fibonacci:"<<std::endl;
			std::cin>>inc;
			}while(min>max or min<0 or max<0 or inc<0);
			generarDatosFibonacci(min, max, inc);
			minimosCuadradosFib();
			datosEstimadosFib();

			std::cout<<"Ahora puede usar GNUPLOT"<<std::endl;


			break;
		case 5:
		//datos inversa		
			do{
			std::cout<<"Se recomienda que los valores min y maximo sean valores lo suficientemente grandes como para que el tiempo no se vea afectado en gran medida por las rutinas del ordenador."<<std::endl;
			std::cout<<"Por favor introduzca un valor para la dimension minima de la matriz:"<<std::endl;
			std::cin>>min;
			std::cout<<"Por favor introduzca un valor para la dimension maxima de la matriz:"<<std::endl;
			std::cin>>max;
			std::cout<<"Por favor introduzca un valor para el incremento de la dimensiond de la matriz:"<<std::endl;
			std::cin>>inc;
			}while(min>max or min<0 or max<0 or inc<0);

			generarDatosInversa(min,max,inc);

			break;	
		
		case 6:
				//datos fibonacci
			do{
			std::cout<<"Se recomienda que los valores min y maximo sean valores lo suficientemente grandes como para que el tiempo no se vea afectado en gran medida por las rutinas del ordenador."<<std::endl;
			std::cout<<"Por favor introduzca un valor para el elemento minimo de la sucesion de Fibonacci que desea calcular: "<<std::endl;
			std::cin>>min;
			std::cout<<"Por favor introduzca un valor para el elemento maximo de la sucesion de Fibonacci que desea calcular:"<<std::endl;
			std::cin>>max;
			std::cout<<"Por favor introduzca un valor para el incremento de los terminos de la sucesiond de Fibonacci:"<<std::endl;
			std::cin>>inc;
			}while(min>max or min<0 or max<0 or inc<0);

			generarDatosFibonacci(min, max, inc);

			break;
		
		case 7:
				//minimos cuadrados inversa
			if(!minimosCuadradosMatriz()){
				std::cout<<"Ejecute primero la opcion 3 o 5. Esta funcion requiere tener datos previos para trabajar."<<std::endl;
			}
			break;
		
		case 8:
				//minimos cuadrados fib
			if(!minimosCuadradosFib()){
				std::cout<<"Ejecute primero la opcion 4 o 6. Esta funcion requiere tener datos previos para trabajar."<<std::endl;
			}
			break;
		
		case 9:
				//obtener coeficiente determinacion inversa y gnuplot
			
			if(!datosEstimadosInversa()){
				std::cout<<"Ejecute primero la opcion 3 o 7. Esta funcion requiere tener datos previos para trabajar."<<std::endl;
			}
			std::cout<<"Ahora puede usar GNUPLOT"<<std::endl;

			break;
		
		case 10:
				//obtener coeficiente determionacion fibonacci y gnuplot
			if(!datosEstimadosFib()){
				std::cout<<"Ejecute primero la opcion 4 o 8. Esta funcion requiere tener datos previos para trabajar."<<std::endl;
			}
			std::cout<<"Ahora puede usar GNUPLOT"<<std::endl;

			break;
		

	}
}while(option!=0);
}