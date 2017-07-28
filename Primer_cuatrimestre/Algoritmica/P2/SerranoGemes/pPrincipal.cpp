#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>


#include "funcionesMatriz.hpp"
#include "minimosCuadrados2n.hpp"
#include "minimosCuadradosPolinomico.hpp"
#include "ClaseTiempo.hpp"
#include "funcionesFichero.hpp"
#include "recursivoSimple.hpp"
#include "datosEstimadosPolinomio.hpp"
#include "datosEstimados2n.hpp"
#include "hanoi.hpp"
using std::vector;

int main (){
	int option;
	int min,max,inc;
	long double result;
	long double tiempoAcumulado;
	long double auxLong=0;
	vector<vector<int>> anillo;

	std::ifstream streamAuxiliar;

	vector<vector<long double>> tablaResultados;

	Clock time;
	
	int n=0;
	long double tiempoEstimadoCombinatorio=0;

	struct tiempoUsado aux;
	
	std::list<struct tiempoUsado> listaTiempos;
	
	std::string nombreFichero;

	std::vector<long double> aCombinatorio;
	std::vector<long double> aTabla;
	std::vector<long double> aIterativo;
	std::vector<long double> aHanoi;

	bool checkTabla=false,checkCombinatorio=false, checkIterativo=false,checkHanoi=false; 


	system("clear");



	do{
		std::cout<<std::endl;
		std::cout<<std::endl;
		std::cout<<std::endl;
		do{ 
			if(option!=1 and option!=2){
				std::cout<<"Introduzca 1-10"<<std::endl;
			}
			std::cout<<"Selecione que tiempo desea estimar: "<<std::endl;
			std::cout<<"0. Salir del programa:"<<std::endl;
			std::cout<<"1. Preparar ajuste numero Combinatorio recursivo simple :"<<std::endl;
			std::cout<<"2. Preparar ajuste numero Combinatorio recursivo con tabla"<<std::endl;
			std::cout<<"3. Preparar ajuste numero Combinatorio iterativamente: "<<std::endl;
			std::cout<<"4. Estimar numero Combinatorio recursivo simple:"<<std::endl;
			std::cout<<"5. Estimar numero Combinatorio recursivo con tabla: "<<std::endl;
			std::cout<<"6. Estimar numero Combinatorio iterativamente: "<<std::endl;
			std::cout<<"7. Preparar ajuste hanoi:"<<std::endl;
			std::cout<<"8. Estimar el tiempo necesario para hanoi de n discos: "<<std::endl;	
			std::cout<<"9. Mostrar proceso de hanoi. "<<std::endl;
			std::cout<<"10. Informacion del programa. "<<std::endl;

			std::cin>>option;

		}while(option<0 and option>11);
		min=-1;
		max=-1;
		inc=-1;
		result=0;
		switch(option){	
			case 1:	
					do{
						std::cout<<"Pruebas consecutivas del calculo del numero combinatorio n sobre k."<<std::endl<<"Metodo recursivo simple."<<std::endl;
						std::cout<<"Por favor introduzca un valor minimo para n :"<<std::endl;
						std::cin>>min;
						std::cout<<"Por favor introduzca un valor maximo para n:"<<std::endl;
						std::cin>>max;
						std::cout<<"Por favor introduzca un valor para el incremento del n:"<<std::endl;
						std::cin>>inc;
					}while(min>max or min<0 or max<0 or inc<0);

					nombreFichero="DatosPrevios2n.txt";
					aux.tiempoEstimado=-1;
					std::cout<<"Calculando..."<<std::endl;
					for(int i=min;i<=max;i=i+inc){
						aux.tiempo=0;
						aux.valor=i;
						for(int j=0;j<i;j++){
							time.restart();
							result=combinatorioRecursivoSimple(i, j);
							time.stop();
							aux.tiempo=aux.tiempo+time.elapsed();
						}
						tiempoAcumulado=aux.tiempo;
						aux.tiempo=aux.tiempo/(i+1);

						std::cout <<"Para n="<<aux.valor<<" Valores k desde 0 hasta n." << " Tiempo medio: " << aux.tiempo << " microsegundos. "<<" Tiempo acumulado: "<<tiempoAcumulado<<" microsegundos"<<std::endl;
						listaTiempos.push_back(aux);

					}
					escribirFichero(listaTiempos,nombreFichero);
					listaTiempos.clear();
					minimosCuadrados2n();
					datosEstimados2n();

					streamAuxiliar.open("componentes2n.txt");
					if(streamAuxiliar.is_open()){
						aCombinatorio.clear();
						while(!streamAuxiliar.eof()){
							streamAuxiliar>>auxLong;
							if(!streamAuxiliar.eof()){
								aCombinatorio.push_back(auxLong);
							}
						}
						checkCombinatorio=true;
						streamAuxiliar.close();
					}else{
						std::cout<<"Error en la apertura del fichero componentes2n.txt"<<std::endl;
					}
				
					break;
			case 2:
					do{
						std::cout<<"Pruebas consecutivas de calculo del numero combinatorio n sobre k."<<std::endl<<"Metodo recursivo con tabla."<<std::endl;
						std::cout<<"Por favor introduzca un valor minimo para n :"<<std::endl;
						std::cin>>min;
						std::cout<<"Por favor introduzca un valor maximo para n:"<<std::endl;
						std::cin>>max;
						std::cout<<"Por favor introduzca un valor para el incremento del n:"<<std::endl;
						std::cin>>inc;
					}while(min>max or min<0 or max<0 or inc<0);		

					tablaResultados.resize(max+1);
					for(int i=0;i<=max;i++){
						tablaResultados[i].resize(max+1,-1);
					}


					nombreFichero="DatosPolinomico.txt";
					aux.tiempoEstimado=-1;
					std::cout<<"Calculando..."<<std::endl;
					for(int i=min;i<=max;i=i+inc){
						aux.tiempo=0;
						aux.valor=i;
						for(int j=0;j<i;j++){
							time.restart();
							result=combinatorioRecursivoTabla(i, j,tablaResultados);
							time.stop();
							aux.tiempo=aux.tiempo+time.elapsed();
							//Vacia la tabla para la siguiente ejecucion
							for(int k=0;k<=i;k++){
								for(int l=0;l<=i;l++){
									tablaResultados[k][l]=-1;
								}
							}
						}
						tiempoAcumulado=aux.tiempo;
						aux.tiempo=aux.tiempo/(i+1);

						std::cout <<"Para n="<<aux.valor<<" Valores k desde 0 hasta n." << " Tiempo medio: " << aux.tiempo << " microsegundos. "<<" Tiempo acumulado: "<<tiempoAcumulado<<" microsegundos"<<std::endl;
						listaTiempos.push_back(aux);


					}
					escribirFichero(listaTiempos,nombreFichero);
					listaTiempos.clear();
					minimosCuadradosPolinomico();
					datosEstimadosPolinomio();
					
					streamAuxiliar.open("componentesPolinomio.txt");
					if(streamAuxiliar.is_open()){
						aTabla.clear();
						while(!streamAuxiliar.eof()){
							streamAuxiliar>>auxLong;
								aTabla.push_back(auxLong);
						}
					streamAuxiliar.close();
					checkTabla=true;

					}else{
						std::cout<<"Error en la apertura del fichero componentesPolinomio.txt"<<std::endl;
					}


					break;					
						
			case 3:
					do{
						std::cout<<"Pruebas consecutivas del calculo del numero combinatorio n sobre k."<<std::endl<<"Metodo iterativo."<<std::endl;
						std::cout<<"Por favor introduzca un valor minimo para n :"<<std::endl;
						std::cin>>min;
						std::cout<<"Por favor introduzca un valor maximo para n:"<<std::endl;
						std::cin>>max;
						std::cout<<"Por favor introduzca un valor para el incremento del n:"<<std::endl;
						std::cin>>inc;
					}while(min>max or min<0 or max<0 or inc<0);	

	
					nombreFichero="DatosPolinomico.txt";
					aux.tiempoEstimado=-1;
					std::cout<<"Calculando..."<<std::endl;
					for(int i=min;i<=max;i=i+inc){
						aux.tiempo=0;
						aux.valor=i;
						for(int j=0;j<i;j++){
							time.restart();
							result=combinatorioNoRecursivo(i, j);
							time.stop();
							aux.tiempo=aux.tiempo+time.elapsed();
						}
						tiempoAcumulado=aux.tiempo;
						aux.tiempo=aux.tiempo/(i+1);

						std::cout <<"Para n="<<aux.valor<<" Valores k desde 0 hasta n." << " Tiempo medio: " << aux.tiempo << " microsegundos. "<<" Tiempo acumulado: "<<tiempoAcumulado<<" microsegundos"<<std::endl;
						listaTiempos.push_back(aux);

					}
					escribirFichero(listaTiempos,nombreFichero);
					listaTiempos.clear();
					minimosCuadradosPolinomico();
					datosEstimadosPolinomio();

					streamAuxiliar.open("componentesPolinomio.txt");
					if(streamAuxiliar.is_open()){
						aIterativo.clear();
						while(!streamAuxiliar.eof()){

							streamAuxiliar>>auxLong;
								aIterativo.push_back(auxLong);
						}
						checkIterativo=true;
						streamAuxiliar.close();
					}else{
						std::cout<<"Error en la apertura del fichero componentesPolinomio.txt"<<std::endl;
					}


					break;
		
			case 4: 
				if(checkCombinatorio){
					tiempoEstimadoCombinatorio=0;
					n=0;
					do{
						do{
							std::cout<<"Elija un numero n para estimar el tiempo medio necesario para calcular su combinatorio. Coef. Det: "<<aCombinatorio[aCombinatorio.size()-1]<<std::endl;
							std::cout<<"Introduzca 0 para salir."<<std::endl;
							std::cin>>n;

						}while(n<0);
						
						if(n!=0){
							tiempoEstimadoCombinatorio=aCombinatorio[0]+aCombinatorio[1]*pow(2,n);
							std::cout<<"El tiempo medio estimado para calcular el combinatorio de "<<n<<" es: "<<tiempoEstimadoCombinatorio<<std::endl;
						}
					}while(n!=0);
				}else{
					system("clear");

					std::cout<<"Ejecute primero la opcion 1"<<std::endl;
				}

				break;
			case 5:
				if(checkTabla){
					tiempoEstimadoCombinatorio=0;
					n=0;
					do{
						do{
							tiempoEstimadoCombinatorio=0;

							std::cout<<"Elija un numero n para estimar e tiempo medio necesario para calcular su combinatorio con tabla. Coef. Det: "<<aTabla[aTabla.size()-1]<<std::endl;
							std::cout<<"Introduzca 0 para salir."<<std::endl;
							std::cin>>n;

						}while(n<0);
						if(n!=0){
							for(uint i=0;i<aTabla.size()-1;i++){
								tiempoEstimadoCombinatorio=tiempoEstimadoCombinatorio+aTabla[i]*pow(n,i);	
							}
							std::cout<<"El tiempo medio estimado para calcular el combinatorio de "<<n<<" es: "<<tiempoEstimadoCombinatorio<<std::endl;
						}
					}while(n!=0);

				}else{
					system("clear");

					std::cout<<"Ejecute primero la opcion 2"<<std::endl;
				}
				break;	
			
			case 6:
				if(checkIterativo){
					tiempoEstimadoCombinatorio=0;
					n=0;
					do{
						do{
							tiempoEstimadoCombinatorio=0;

							std::cout<<"Elija un numero n para estimar e tiempo medio necesario para calcular su combinatorio con tabla. Coef. Det: "<<aIterativo[aIterativo.size()-1]<<std::endl;
							std::cout<<"Introduzca 0 para salir."<<std::endl;
							std::cin>>n;

						}while(n<0);
						if(n!=0){
							for(uint i=0;i<aIterativo.size()-1;i++){
								tiempoEstimadoCombinatorio=tiempoEstimadoCombinatorio+aIterativo[i]*pow(n,i);	
							}
					
							std::cout<<"El tiempo medio estimado para calcular el combinatorio de "<<n<<" es: "<<tiempoEstimadoCombinatorio<<std::endl;
						}
					}while(n!=0);


				}else{
					system("clear");

					std::cout<<"Ejecute primero la opcion 3"<<std::endl;
				}
				break;	
		
			case 7:
				do{
						std::cout<<"Pruebas consecutivas del calculo de hanoi de n elementos."<<std::endl;
						std::cout<<"Por favor introduzca un valor minimo para n :"<<std::endl;
						std::cin>>min;
						std::cout<<"Por favor introduzca un valor maximo para n:"<<std::endl;
						std::cin>>max;
						std::cout<<"Por favor introduzca un valor para el incremento del n:"<<std::endl;
						std::cin>>inc;
					}while(min>max or min<0 or max<0 or inc<0);

					nombreFichero="DatosPrevios2n.txt";
					aux.tiempoEstimado=-1;
					std::cout<<"Calculando..."<<std::endl;
					for(int i=min;i<=max;i=i+inc){
						aux.tiempo=0;
						aux.valor=i;
						time.restart();
						hanoi(i,1,2,result);
						time.stop();
						aux.tiempo=time.elapsed();
						
						std::cout <<"Para n="<<aux.valor<<" Tiempo: " << aux.tiempo << " microsegundos. "<<std::endl;
						listaTiempos.push_back(aux);

					}
					escribirFichero(listaTiempos,nombreFichero);
					listaTiempos.clear();
					minimosCuadrados2n();
					datosEstimados2n();

					streamAuxiliar.open("componentes2n.txt");
					if(streamAuxiliar.is_open()){
						aHanoi.clear();
						while(!streamAuxiliar.eof()){
							streamAuxiliar>>auxLong;
							if(!streamAuxiliar.eof()){
								aHanoi.push_back(auxLong);
							}
						}
						checkHanoi=true;
						streamAuxiliar.close();
					}else{
						std::cout<<"Error en la apertura del fichero componentes2n.txt"<<std::endl;
					}
				

				break;
		
			case 8:
				if(checkHanoi){
					tiempoEstimadoCombinatorio=0;
					n=0;
					do{
						do{
							std::cout<<"Elija un numero n para estimar el tiempo medio necesario para calcular hanoi. Coef. Det: "<<aHanoi[aHanoi.size()-1]<<std::endl;
							std::cout<<"Introduzca 0 para salir."<<std::endl;
							std::cin>>n;

						}while(n<0);
						if(n!=0){
							tiempoEstimadoCombinatorio=aHanoi[0]+aHanoi[1]*pow(2,n);
							std::cout<<"El tiempo medio estimado para calcular hanoi de "<<n<<" elementos es: "<<tiempoEstimadoCombinatorio<<std::endl;
						}

					}while(n!=0);
				}else{
					system("clear");

					std::cout<<"Ejecute primero la opcion 7"<<std::endl;
				}

				break;
		
			case 9://mostrar hanoi
				anillo.resize(3);
				int m;

				std::cout<<"¿Cual es el tamaño que quiere visualizar de hanoi?"<<std::endl;
				std::cout<<"AVISO: numeros muy grandes tienen un tiempo muy largo de ejecucion debido a la representacion en pantalla."<<std::endl;
				std::cin>>m;

					
				for(int i=1;i<=m;i++){
					anillo[0].push_back(i);
				}
	
				hanoiVisual(m,1,2,result,anillo);
				
				std::cout<<"Estado: "<<result<<std::endl;
				verEstadoHanoi(anillo);

				std::cout<<"Numero de movimientos necesarios: "<<result<<std::endl;

				break;
		
			case 10:
				system("clear");
				std::cout<<"Para salir del programa introduzca 0 en el menu principal."<<std::endl;
				std::cout<<"Para ejecutar la opciones 1, 2, 3 o 7 es necesario haber ejecutado previamente la opcion 4, 5, 6 u 8 respectivamente."<<std::endl;
				std::cout<<"Una vez hechas las pruebas se puede estimar tantas veces como quiera."<<std::endl;
				std::cout<<"Las estimaciones deben realizarse con muestras suficientemente grandes y con valores lo suficientemente separados. "<<std::endl;
				std::cout<<"para obtener una buena estimacion. Es decir, una muestra suficientemente grande y lo suficientemente espaciada."<<std::endl;
				std::cout<<"Para realizar la estimacion se recomienda usar un grado 2 o 4."<<std::endl;
				std::cout<<"Al realizar una estimacion se genera un fichero Datos.txt que puede ser introducido en GNUPLOT para observar las graficas."<<std::endl;
				std::cout<<"La visualizacion de hanoi muestra los discos como un numero entero siendo 1 el mas pequeño."<<std::endl;
				std::cout<<"La visualizacion de hanoi tarda mucho con valores muy  altos."<<std::endl;

				break;
		}
		
	}while(option!=0);

}