#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "material.hpp"
#include "mochila.hpp"
#include "moneda.hpp"
#include "cambio.hpp"
#include "fichero.hpp"

int main(){
	int cap;
	int cant;
	int opcion=0;

	std::vector<material> vectorMateriales;
	std::string nombreFich="materiales.txt";

	std::vector<moneda> vectorMonedas;
	std::string nombreFichMonedas="monedas.txt";
	do{
		system("clear");
		do{
			if(opcion<0 or opcion>2){
				std::cout<<"Introduzca una de las tres opciones."<<std::endl;
			}
			std::cout<<"Elija una problema:"<<std::endl;
			std::cout<<"\t1-Problema de la mochila."<<std::endl;
			std::cout<<"\t2-Problema del cambio."<<std::endl;
			std::cout<<"\t0-Salir del programa."<<std::endl;
			std::cin>>opcion;
		}while(opcion<0 or opcion>2);

		switch(opcion){

			case 1:
				do{

					std::cout<<"Introduce la capacidad de la mochila. Introducir 0 o menos termina el programa: ";
					std::cin>>cap;

					if(cap>0){
						mochila m(cap);

						if(leerFichero(nombreFich, vectorMateriales)){
							std::vector<std::vector<int>> tablaMochila;

							m.llenarMochila(vectorMateriales,tablaMochila);
							m.obtenerSolucion(vectorMateriales,tablaMochila);
							std::cout<<std::endl<<"El precio de la mochila es: "<<m.getValorMochila()<<std::endl;
							std::cout<<"Materiales que contiene:"<<std::endl;

							m.contenidoMochila();
						}else{
							std::cout<<"El fichero "<<nombreFich<<" es necesario para la ejecucion."<<std::endl;
						}

					}
				}while(cap>0);

				break;
			case 2:
				do{
					std::cout<<"Introduce la cantidad a cambiar en centimos. Introducir 0 o menos te devuelve al menu: ";
					std::cin>>cant;
					system("clear");

					if(cant>0){
						cambio c(cant);

						if(leerFichero(nombreFichMonedas, vectorMonedas)){
							std::vector<std::vector<int>> tablaCambio;
							c.realizarCambio(vectorMonedas,tablaCambio);
							c.obtenerSolucion(vectorMonedas,tablaCambio);

							std::cout<<std::endl<<"El cambio que se pide es: "<<c.getCambioTotal()<<std::endl;
							std::cout<<"Monedas que se usan:"<<std::endl;
							c.monedasUsadas();
						}else{
							std::cout<<"El fichero "<<nombreFich<<" es necesario para la ejecucion."<<std::endl;
						}

					}
				}while(cant>0);


				break;
			default:
				std::cout<<"Saliendo del programa..."<<std::endl;
		}

	}while(opcion!=0);
}


