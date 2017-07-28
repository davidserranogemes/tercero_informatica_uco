#include <cmath>
#include <iostream>
#include <cstdlib>
#include <locale>
#include <list>
#include <fstream>
#include <cstdlib>
#include <string>

//#include "funcionesAux.hpp"
#include "funcionesFichero.hpp"
#include "datosEstimados2n.hpp"


bool datosEstimados2n(){

	std::list<struct tiempoUsado> listaTiempos;
	std::list<struct tiempoUsado> listaTiemposComp;

	struct tiempoUsado aux;

	std::string nombreFichero="DatosPrevios2n.txt";
	std::string nombreFicheroGnu="Datos.txt";

	std::ifstream stream;
	std::ofstream streamFinal;



	int tam;
	
	long double a0;
	long double a1;
	long double t;
	long double mediaReal=0;
	long double mediaEsp=0;
	long double varEsp=0, varReal=0, R=0;

	
	stream.open("componentes2n.txt");
	
	if(stream.is_open()){
		stream>>a0;
		stream>>a1;
		stream.close();

		listaTiempos=leerFichero(nombreFichero);
		tam=listaTiempos.size();

		while(listaTiempos.size()!=0){
			aux=listaTiempos.front();
			listaTiempos.pop_front();

			t= a0 + a1*pow(2,aux.valor);		
			aux.tiempoEstimado=t;

		//	std::cout<<"Tiempo estimado para el elemento "<<aux.valor<<"  : t= "<<t/1000000<<" segundos."<<std::endl;
			
			listaTiemposComp.push_back(aux);


			mediaReal=mediaReal + aux.tiempo;
			mediaEsp=mediaEsp+aux.tiempoEstimado;

		}
		escribirFichero(listaTiemposComp, nombreFicheroGnu);

		mediaReal=mediaReal/tam;
		mediaEsp=mediaEsp/tam;
		listaTiempos=leerFichero(nombreFicheroGnu);

		while(listaTiempos.size()!=0){
			aux=listaTiempos.front();
			listaTiempos.pop_front();
			varEsp=varEsp+pow(aux.tiempoEstimado,2);
			varReal=varReal+pow(aux.tiempo,2);
		}
	
		varReal=(varReal/tam)-pow(mediaReal,2);
		varEsp=(varEsp/tam)-pow(mediaEsp,2);

		R=varEsp/varReal;
	}else{
		std::cout<<"Fallo en la apertura del fichero: "<<"componentes2n.txt"<<std::endl;

	return false;
	}

	std::cout<<"Coeficiente: "<<R<<std::endl;
	streamFinal.open("componentes2n.txt");
	
	if(streamFinal.is_open()){
		streamFinal<<a0<<"\n"<<a1<<"\n"<<R<<"\n";
	}else{
		std::cout<<"Fallo en la apertura del fichero: "<<"componentes2n.txt"<<std::endl;
		return false;
	}
	streamFinal.close();

	return true;

}