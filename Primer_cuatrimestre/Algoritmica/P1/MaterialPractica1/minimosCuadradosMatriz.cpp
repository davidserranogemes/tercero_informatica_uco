#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

#include "funcionesFichero.hpp"
#include "funcionesMatriz.hpp"
#include "minimosCuadradosMatriz.hpp"

using std::vector;

bool minimosCuadradosMatriz(){

	std::list<struct tiempoUsado> listaTiempos;
	struct tiempoUsado aux;
	std::string nombreFichero="DatosInversa.txt";

	listaTiempos=leerFichero(nombreFichero);
	if(listaTiempos.size()==0){
		std::cout<<"Hay un fallo en la lectura del fichero "<<nombreFichero<<", puede estar vacio o no existir."<<std::endl;
		return false;
	}
					std::cout<<listaTiempos.size()<<std::endl;

	unsigned int grado;
	//long double det,deta0,deta1,deta2, deta3, deta4;
	long double det;
	vector<long double> determinantesA;

	vector<vector<vector<long double>>> matrizA;// [i][j][k]
												// i elige la matriz A(numero), j y k acceden a los elementos
	vector<vector<long double>> matrizDet;
	vector<long double> sumatorioX;
	vector<long double> sumatorioXY;
	vector<long double> a;

	do{
		std::cout<<"Introduzca el grado del polinomio con el que desea estimar: (>0)"<<std::endl;
		std::cin>>grado;
	}while(grado<1);

	sumatorioX.resize(grado*2+1,0); //desde sumatorio x^0 hasta x^grado*2-2
	sumatorioXY.resize(grado+1,0);//desde a0 hasta a(grado)
	a.resize(grado+1,0);
	determinantesA.resize(grado+1,0);
	matrizDet.resize(grado+1);
	matrizA.resize(grado+1);


	for (unsigned int i = 0; i < matrizDet.size(); i++){
		matrizDet[i].resize(grado+1);
	}

	for(unsigned int i=0; i<matrizA.size();i++){
		matrizA[i].resize(grado+1);
		for(unsigned int j=0; j<matrizA.size();j++){
			matrizA[i][j].resize(grado+1,0);
		}
	}


	while(!listaTiempos.empty()){
		aux=listaTiempos.front();
		listaTiempos.pop_front();
		
		for(unsigned int i=0;i<sumatorioX.size();i++){
			sumatorioX[i]=sumatorioX[i]+pow(aux.valor,i);
		}


		for(unsigned int i=0;i<sumatorioXY.size();i++){
			sumatorioXY[i]=sumatorioXY[i]+pow(aux.valor,i)*aux.tiempo;
		}
	
	}



//Asignacion de valores
 // A todos se les da los mismo valores porque la unica diferencia que hay es entre las A* donde
 // se coloca la linea del sumatorio XY
 	for(unsigned int i=0;i<grado+1;i++){
 		for(unsigned int j=0;j<grado+1;j++){
 			matrizDet[i][j]=sumatorioX[i+j];
 			for(unsigned int k=0; k<grado+1;k++){
 				matrizA[i][j][k]=sumatorioX[j+k];

 			}
 		}
	}
	/*
	for(uint i=0;i<grado+1;i++){
		for(uint j=0;j<grado+1;j++){
			for(uint k=0;k<grado+1;k++){
				std::cout<<"["<<matrizA[i][j][k]<<"]";
			}
			std::cout<<std::endl;
		}
					std::cout<<std::endl;
			std::cout<<std::endl;

	}
	for(uint j=0;j<grado+1;j++){
			for(uint k=0;k<grado+1;k++){
				std::cout<<"["<<matrizDet[j][k]<<"]";
			}
			std::cout<<std::endl;
		}	*/

//Aquí insertamos la linea del sumatorio del XY 
	for(unsigned int i=0;i<grado+1;i++){
		for(unsigned int j=0;j<grado+1;j++){
			matrizA[i][j][i]=sumatorioXY[j];
		}
	}
	for(uint i=0;i<grado+1;i++){
		for(uint j=0;j<grado+1;j++){
			for(uint k=0;k<grado+1;k++){
				std::cout<<"["<<matrizA[i][j][k]<<"]";
			}
			std::cout<<std::endl;
		}
					std::cout<<std::endl;
			std::cout<<std::endl;

	}
		for(uint j=0;j<grado+1;j++){
			for(uint k=0;k<grado+1;k++){
				std::cout<<"["<<matrizDet[j][k]<<"]";
			}
			std::cout<<std::endl;
		}


//genera los determinantes para Cramer
	for(unsigned int i=0;i<grado+1;i++){
		determinantesA[i]=determinante(matrizA[i]);
	}
	det=determinante(matrizDet);


	
	for(unsigned int i=0;i<a.size();i++){
			std::cout<<"Componente a"<<i<<" : "<<determinantesA[i]<<std::endl;
	
	}
			std::cout<<"Componente det"<<" : "<<det<<std::endl;


//depuracion muestra los determinantes hechos por cramer

for(unsigned int i=0;i<grado+1;i++){
	a[i]=determinantesA[i]/det;
}

//muestra polinomio de estimacion


	std::ofstream stream;
	//guarda las componentes en un fichero para que datos Estimados Matriz los use
	stream.open("componentesMatriz.txt");
	if(stream.is_open()){
		for(unsigned int i=0;i<a.size();i++){
			std::cout<<"Componente a"<<i<<" : "<<a[i]<<std::endl;
			stream<<a[i]<<"\n";
	}
		stream.close();
	}else{
		std::cout<<"Fallo en la apertura del fichero: "<<"componentesPolinomio.txt"<<std::endl;
	}
 	return true;
}
