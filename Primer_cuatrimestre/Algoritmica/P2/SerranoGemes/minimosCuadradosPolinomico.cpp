#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

#include "funcionesFichero.hpp"
#include "funcionesMatriz.hpp"
#include "minimosCuadradosPolinomico.hpp"

using std::vector;

bool minimosCuadradosPolinomico(){

	std::list<struct tiempoUsado> listaTiempos;
	struct tiempoUsado aux;
	std::string nombreFichero="DatosPolinomico.txt";

	listaTiempos=leerFichero(nombreFichero);
	if(listaTiempos.size()==0){
		std::cout<<"Hay un fallo en la lectura del fichero "<<nombreFichero<<", puede estar vacio o no existir."<<std::endl;
		return false;
	}

	unsigned int grado;
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
		
		for(unsigned int i=0;i<=grado*2;i++){
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
//Aquí insertamos la linea del sumatorio del XY 
	for(unsigned int i=0;i<grado+1;i++){
		for(unsigned int j=0;j<grado+1;j++){
			matrizA[i][j][i]=sumatorioXY[j];
		}
	}



//genera los determinantes para Cramer
	for(unsigned int i=0;i<grado+1;i++){
		determinantesA[i]=determinante(matrizA[i]);
	}
	det=determinante(matrizDet);



//depuracion muestra los determinantes hechos por cramer

for(unsigned int i=0;i<grado+1;i++){
	a[i]=determinantesA[i]/det;
}

//muestra polinomio de estimacion


	std::ofstream stream;
	//guarda las componentes en un fichero para que datos Estimados Matriz los use
	stream.open("componentesPolinomio.txt");
	if(stream.is_open()){
		for(unsigned int i=0;i<a.size();i++){
			std::cout<<"Componente a"<<i<<" : "<<a[i]<<std::endl;
			stream<<a[i]<<"\n";
	}
		std::cout<<std::endl;
		stream.close();
	}else{
		std::cout<<"Fallo en la apertura del fichero: "<<"componentesPolinomio.txt"<<std::endl;
	}
 	return true;
}
