#include <cmath>
#include <iostream>
#include <cstdlib>
#include <locale>
#include <list>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

//#include "funcionesAux.hpp"
#include "funcionesFichero.hpp"

bool datosEstimadosPolinomio(){

	std::list<struct tiempoUsado> listaTiempos;
	std::list<struct tiempoUsado> listaTiemposComp;
	long double auxFichero;

	struct tiempoUsado aux;

	std::string nombreFichero="DatosPolinomico.txt";
	std::string nombreFicheroGnu="Datos.txt";

	std::ifstream stream;
	std::ofstream streamFinal;

	int tam;
	
	std::vector<long double> a;
	long double t=0;
	long double mediaReal=0;
	long double mediaEsp=0;
	long double varEsp=0, varReal=0, R=0;

	stream.open("componentesPolinomio.txt");
	if(stream.is_open()){
		while(!stream.eof()){
			stream>>auxFichero;
			if(!stream.eof()){
				a.push_back(auxFichero);
			}
		}
		//std::cout<<a.size()<<std::endl;

		stream.close();

		listaTiempos=leerFichero(nombreFichero);
		tam=listaTiempos.size();
		while(listaTiempos.size()!=0){
			t=0;
			aux=listaTiempos.front();
			listaTiempos.pop_front();
			for(uint i=0;i<a.size();i++){
				t=t+a[i]*pow(aux.valor,i);
			}
		//	t= a0 + a1*aux.valor+a2*pow(aux.valor,2)+a3*pow(aux.valor,3)+a4*pow(aux.valor,4);		
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
		std::cout<<"Fallo en la apertura del fichero: "<<"componentesPolinomio.txt"<<std::endl;
		return false;
	}

	std::cout<<"Coeficiente: "<<R<<std::endl;

	streamFinal.open("componentesPolinomio.txt");
	if(streamFinal.is_open()){
		for(uint i=0; i<a.size();i++){
			streamFinal<<a[i]<<"\n";
		}
		streamFinal<<R;

//		streamFinal<<a0<<"\n"<<a1<<"\n"<<a2<<"\n"<<a3<<"\n"<<a4<<"\n"<<R;
	}else{
		std::cout<<"Fallo en la apertura del fichero: "<<"componentesPolinomio.txt"<<std::endl;
			exit(-1);
	}
	streamFinal.close();
	return true;
}