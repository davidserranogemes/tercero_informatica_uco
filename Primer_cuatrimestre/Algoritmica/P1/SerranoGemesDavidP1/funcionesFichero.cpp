#include "funcionesFichero.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
std::list<struct tiempoUsado> leerFichero(std::string nombreFichero){

	std::list<struct tiempoUsado> tiempos;
	struct tiempoUsado aux;
	std::ifstream stream;
	int lastVal=0;;

	stream.open(nombreFichero.c_str());
	if(stream.is_open()){
		while(!stream.eof()){
			stream>>aux.valor;
			stream>>aux.tiempo;
			stream>>aux.tiempoEstimado;
			if(lastVal!=aux.valor){
				tiempos.push_back(aux);
			}
			lastVal=aux.valor;
		}
	stream.close();
	}else{
		std::cout<<"Fallo en la apertura del fichero: "<<nombreFichero<<std::endl;
		return tiempos;//Vacia
	}

	return tiempos;

}

void escribirFichero(std::list<struct tiempoUsado> listaTiempos,std::string nombreFichero){

	struct tiempoUsado aux;
	std::ofstream stream;

	stream.open(nombreFichero.c_str());
	if(stream.is_open()){

		while(listaTiempos.size()!=0){

			aux=listaTiempos.front();
	
			stream<<aux.valor<<"\t";
			stream<<aux.tiempo<<"\t";

			stream<<aux.tiempoEstimado<<"\n";

			listaTiempos.pop_front();
		
		}
		stream.close();
	}else{
		std::cout<<"Fallo en la apertura del fichero: "<<nombreFichero.c_str()<<std::endl;
		exit(-1);
	}
}