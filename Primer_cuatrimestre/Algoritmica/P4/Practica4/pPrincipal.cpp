#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "material.hpp"
#include "mochila.hpp"

bool leerFichero(std::string nombreFich, std::vector<material> &v);

int main(){
	int cap;

	std::vector<material> vectorMateriales;
	std::string nombreFich="materiales.txt";

	do{

		std::cout<<"Introduce la capacidad de la mochila. Introducir 0 o menos termina el programa: ";
		std::cin>>cap;

		if(cap>0){
			mochila m(cap);

			if(leerFichero(nombreFich, vectorMateriales)){
				m.llenarMochila(vectorMateriales);

				std::cout<<std::endl<<"El precio de la mochila es: "<<m.getValorMochila()<<std::endl;
				std::cout<<"Materiales que contiene:"<<std::endl;

				m.contenidoMochila();
			}else{
				std::cout<<"El fichero "<<nombreFich<<" es necesario para la ejecucion."<<std::endl;
			}

		}
	}while(cap>0);

}

bool leerFichero(std::string nombreFich, std::vector<material> &v){
	std::ifstream stream;
	
	material auxMat;
	int auxVal;

	int lastEt=-1;
	stream.open(nombreFich.c_str());
	if(stream.is_open()){
		v.clear();
		while(!stream.eof()){
			stream>>auxVal;
			auxMat.setEtiqueta(auxVal);
			
			stream>>auxVal;
			auxMat.setVolumen(auxVal);
			
			stream>>auxVal;
			auxMat.setValor(auxVal);

			auxMat.setEstado("no_usado");

			if(lastEt!=auxMat.getEtiqueta()){
				v.push_back(auxMat);
			}
			lastEt=auxMat.getEtiqueta();
		}

		stream.close();
		return true;
	}else{
		return false;
	}
}
