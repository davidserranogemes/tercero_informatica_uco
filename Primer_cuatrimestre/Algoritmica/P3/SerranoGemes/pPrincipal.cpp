#include <iostream>

#include <cstdlib>

#include "Conjunto.hpp"
#include "ClaseTiempo.hpp"
#include "maximoMinimo.hpp"

#define RANGE 10000
int main(){
	Clock timeCounter;

	Conjunto<int> vectorConjunto;
	int randomNumber;

	int max=0,min=0,curr=0;
	int nEle;
	uint nComp=0;
	
	do{
		std::cout<<"Introduce el numero de elementos que quiere en el vector aleatorio:"<<std::endl<<"Tamaños muy grandes puedes superar el maximo rango del tipo int."<<std::endl<<"Introduce 0 para apagar el programa."<<std::endl<<std::endl;
		std::cin>>nEle;
		system("clear");
		if(nEle!=0){
			srand(time(NULL));
			
			timeCounter.restart();
			for(int i=0;i<nEle;i++){
				randomNumber=rand()%RANGE+1;
				vectorConjunto.insert(randomNumber);
			}
			timeCounter.stop();

			std::cout<<"Vector creado:"<<std::endl<<"Tiempo:"<<timeCounter.elapsed()/1000000.0<<" segundos"<<std::endl<<std::endl;

			timeCounter.restart();
			maxMinDivVen(vectorConjunto ,0,vectorConjunto.size()-1,max,min,nComp);
			timeCounter.stop();

			std::cout<<"Recursivo:"<<std::endl;
			std::cout<<"Max: "<<max<<std::endl<<"Min: "<<min<<std::endl<<"Tiempo:"<<timeCounter.elapsed()/1000000.0<<" segundos"<<std::endl<<"Numero de comparaciones: "<<nComp<<std::endl<<std::endl;

			nComp=0;
			timeCounter.restart();
			maxMinIter(vectorConjunto,max,min,nComp);
			timeCounter.stop();

			std::cout<<"Iterativo:"<<std::endl;
			std::cout<<"Max: "<<max<<std::endl<<"Min: "<<min<<std::endl<<"Tiempo:"<<timeCounter.elapsed()/1000000.0<<" segundos"<<std::endl<<"Numero de comparaciones: "<<nComp<<std::endl<<std::endl;

			//Resets necesarios		
			vectorConjunto.cleanConj();
			max=0;
			min=0;
			nComp=0;
		}
	}while(nEle!=0);

	return 0;
}