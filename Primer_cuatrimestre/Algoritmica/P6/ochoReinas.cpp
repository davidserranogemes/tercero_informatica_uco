#include <cmath>
#include <iostream>

#include <cstdlib>

//Para num aleatorio
#include <chrono>
#include <random>


#include "ochoReinas.hpp"



bool lugar(int k, std::vector <int> x){

	for(int i=0;i<k;i++){
		//std::cout<<"x[i]:"<<x[i]<<" x[k]: "<<x[k]<<" i: "<<i<<" k: "<<k<<std::endl;

		if(x[i]==x[k] or std::abs(x[i]-x[k])==std::abs(i-k)){
			//std::cout<<"x[i]:"<<x[i]<<" x[k]: "<<x[k]<<" i: "<<i<<" k: "<<k<<std::endl;

			//std::cout<<"NO"<<std::endl;
			return false;
		}
//		std::cout<<"x[i]:"<<x[i]<<" x[k]: "<<x[k]<<" i: "<<i<<"k: "<<std::endl;
	}
	return true;
}



void ochoReinasBacktracking(int n, std::vector<std::vector<int>> &soluciones){

	std::vector<int> x;
	x.resize(n,-1);
	std::cout<<n<<std::endl;
	int k=0;

	while(k>-1){
		x[k]++;
		while(x[k]<n and lugar(k,x)==false){
			x[k]++;
		}
		if(x[k]<n){
			if(k==(n-1)){//Puede dar un seg fault aqui
		//		std::cout<<"x[k]: "<<x[k]<<" n: "<<n<<" k: "<<k<<std::endl;
				soluciones.push_back(x);
				/**
				for(int i=1; i<x.size();i++){
					std::cout<<" "<<x[i];
				}
				std::cout<<std::endl;
				exit(-1);
				*/
			}else{
				k++;
				x[k]=-1;
			}
		}else{
			k--;
		}
	}
}


bool ochoReinasVegas(int n, std::vector<int> &solucion){
	srand(time(NULL));
	solucion.resize(n,-1);
	std::vector<int> posibles;
	posibles.resize(n,-1);


	int contador=0;

	for(int k=0;k<n;k++){
		contador=0;
		for(int j=0;j<n;j++){
			solucion[k]=j;
			if(lugar(k,solucion)){
				posibles[contador]=j;
				contador++;

			}
		}
		//std::cout<<"contador: "<<contador<<std::endl;
		/*for(int i=0;i<posibles.size();i++){
			std::cout<<posibles[i]<<"  ";
		}
		std::cout<<std::endl;
		*/
		if(contador==0){
			return false;
		}
		int aleatorio=std::abs(num_aleatorio(0,9954983)*rand())%contador;
		//std::cout<<"ale: "<<aleatorio<<std::endl;
		int columna=posibles[aleatorio];
		//std::cout<<"col: "<<columna<<std::endl;
		/*
		if(columna>=n){
			std::cout<<"contador: "<<contador<<std::endl;
			std::cout<<"ale: "<<aleatorio<<std::endl;
			std::cout<<"col: "<<columna<<std::endl;
			for(uint i=0;i<posibles.size();i++){
				std::cout<<posibles[i]<<"  ";
		}
		std::cout<<std::endl;
		
		}*/	
		solucion[k]=columna;
		//std::cout<<k<<" "<<std::endl;
	}
	//std::cout<<std::endl;
	if(contador==0){
		return false;
	}else{
		return true;
	}
}



void mostrarSoluciones(std::vector<std::vector<int>> &soluciones){

	for(uint i=0;i<soluciones.size();i++){
		std::cout<<"[";
		for(uint j=0;j<soluciones[i].size();j++){
			std::cout<<" "<<soluciones[i][j]+1;
		}
		std::cout<<" ]"<<std::endl;
	}
}


bool insertSolucionUnica(std::vector<std::vector<int>> &soluciones,std::vector<int> &solucion){
	uint check=0;
	//std::cout<<"STUCK"<<std::endl;

	//std::cout<<"check: "<<check<<"   soluciones size: "<<soluciones.size()<<std::endl;
	for(uint i=0;i<soluciones.size();i++){
		for(uint j=0;j<soluciones[i].size();j++){
	//		std::cout<<"  "<<soluciones[i][j]<<"  "<<solucion[j];
			if(soluciones[i][j]!=solucion[j]){
				j=soluciones[i].size();
				//break;
				check++;
	//			std::cout<<std::endl<<"check: "<<check<<"   soluciones size: "<<soluciones.size()<<std::endl;
			}
		}
		//std::cout<<std::endl;
	}
	//std::cout<<"check: "<<check<<"   soluciones size: "<<soluciones.size()<<std::endl;

	if(check==soluciones.size()){//Todas son distintas
		soluciones.push_back(solucion);
		return true;
	}else{
		return false;
	}
}




int num_aleatorio(const uint &lim_inf, const uint &lim_sup) {
    unsigned seed; // semilla para la generacion aleatoria

    // Obtenemos un generador aleatorio basado en el reloj del sistema
    seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    // Especificamos el rango de la distribucion [lim_inf, lim_sup)
    std::uniform_int_distribution<int> distribution(lim_inf, lim_sup);
    // Generacion de valor aleatorio
    return distribution(generator);
} // inicializar_conjunto_aleatorio