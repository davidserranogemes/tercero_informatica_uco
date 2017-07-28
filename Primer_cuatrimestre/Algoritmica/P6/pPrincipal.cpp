#include <iostream>
#include <vector>
#include <string>


#include "ochoReinas.hpp"


int main(){

	int dim;
	int opcion;
	std::vector<std::vector<int>> soluciones;
	std::vector<int> numSoluciones;
	numSoluciones.resize(1000,-1);
	do{
		//system("clear");
		soluciones.clear();
		do{
			if(opcion<0 or opcion>3){
				std::cout<<"Introduzca una de las tres opciones."<<std::endl;
			}
			std::cout<<"Elija una problema:"<<std::endl;
			std::cout<<"\t1-8 Reinas por backtracking."<<std::endl;
			std::cout<<"\t2-8 Reinas por algoritmo de las Vegas."<<std::endl;
			std::cout<<"\t3-Todas las soluciones segun las Vegas"<<std::endl;
			std::cout<<"\t0-Salir del programa."<<std::endl;
			std::cin>>opcion;

		}while(opcion<0 or opcion>3);

		switch(opcion){

			case 1:
				do{
					soluciones.clear();

					do{
						std::cout<<"Obtencion las soluciones por backtracking."<<std::endl;
						std::cout<<"Introduce las dimensiones del tablero. Si introduce 0 sale de la opcion."<<std::endl;
						std::cin>>dim;
						system("clear");
					}while(dim<0);
					if(dim!=0){
						ochoReinasBacktracking(dim,soluciones);
						mostrarSoluciones(soluciones);
						numSoluciones[dim]=soluciones.size();
					}
				}while(dim!=0);
				break;
			case 2:
				do{
					do{
						std::cout<<"Obtencion de una solucion por algoritmo de las Vegas."<<std::endl;
						std::cout<<"Introduce las dimensiones del tablero. Si se introduce 0 se sale de la opcion."<<std::endl;
						std::cin>>dim;
						system("clear");
					}while(dim<0);

					if(dim!=0){
						std::vector<int> solucion;
						int fallos=0;
						while(!ochoReinasVegas(dim,solucion)){
							//std::cout<<"Falla."<<std::endl;
							fallos++;
							solucion.clear();
						}

						std::cout<<"[";
						for(uint j=0;j<solucion.size();j++){
							std::cout<<" "<<solucion[j]+1;
						}
						std::cout<<" ]"<<std::endl;

						std::cout<<"Ha fallado "<<fallos<<" veces antes de dar la solucion"<<std::endl;
						solucion.clear();
					}
					
				}while(dim!=0);

				break;
			case 3:
				do{
					soluciones.clear();
					do{
						//std::cout<<"SOON TM"<<std::endl;
						std::cout<<"Obtencion todas las soluciones por algoritmo de las vegas."<<std::endl;
						std::cout<<"Introduce las dimensiones del tablero. Si introduce 0 se sale del programa."<<std::endl;
						std::cin>>dim;
						system("clear");
					}while(dim<0);

					if(dim!=0 and numSoluciones[dim]!=-1){
						//Hacer algorimto
						std::cout<<"Se inicia la busqueda de todas las soluciones para un tablero de "<<dim<<"x"<<dim<<" según el algoritmo de las Vegas."<<std::endl<<"Puede demorarse."<<std::endl;
						long double fallos=0;
						long double repetido=0;
						long double contador=0;

						std::vector<int> solucion;

						while(soluciones.size()!=numSoluciones[dim]){
							contador++;
							while(!ochoReinasVegas(dim,solucion)){
								//std::cout<<"Falla."<<std::endl;
								fallos++;
								solucion.clear();
							}

							if(!insertSolucionUnica(soluciones,solucion)){
								repetido++;
								//std::cout<<"Repetida:"<<std::endl;
							}else{
								std::cout<<"Encontrada nueva solucion unica."<<std::endl;
								std::cout<<soluciones.size()<<"/"<<numSoluciones[dim]<<" encontradas."<<std::endl;	
							}

							solucion.clear();
						}

						if(soluciones.size()>0){
							mostrarSoluciones(soluciones);
							std::cout<<"Encontradas "<<soluciones.size()<<" soluciones."<<std::endl;
							std::cout<<"Necesitadas: "<<contador<<" soluciones correctas."<<std::endl;
							std::cout<<"Vegas ha fallado "<<fallos<<" veces."<<std::endl;
							std::cout<<"La solución ha colisionado "<<repetido<<" veces."<<std::endl;
							std::cout<<"Vegas se ha ejecutado "<<contador+fallos<<" veces."<<std::endl;
						}else{
							std::cout<<"No hay soluciones para un tablero de "<<dim<<"x"<<dim<<std::endl;						}

					}else{
						std::cout<<"Todavia no se ha intentado resolver por backtracking."<<std::endl;
						std::cout<<"Seleccione primero la opción 1 para ejecutar esta version."<<std::endl;
					}
				}while(dim!=0); 

				break;
			default:
				std::cout<<"Saliendo del programa..."<<std::endl;
		}

	}while(opcion!=0);


}
