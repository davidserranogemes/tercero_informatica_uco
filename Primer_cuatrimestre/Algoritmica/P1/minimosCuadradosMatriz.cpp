#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

#include "funcionesFichero.hpp"
#include "funcionesMatriz.hpp"

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

	long double det,deta0,deta1,deta2, deta3, deta4;

	vector<vector<long double>> matrizDet;
	vector<vector<long double>> matrizA0;
	vector<vector<long double>> matrizA1;
	vector<vector<long double>> matrizA2;
	vector<vector<long double>> matrizA3;
	vector<vector<long double>> matrizA4;

	vector<long double> sumatorioX;
	vector<long double> sumatorioXY;
	vector<long double> a;

	sumatorioX.resize(9,0);
	sumatorioXY.resize(5,0);
	a.resize(5,0);


	while(!listaTiempos.empty()){
		aux=listaTiempos.front();
		listaTiempos.pop_front();
		
		for(int i=0;i<=8;i++){
			sumatorioX[i]=sumatorioX[i]+pow(aux.valor,i);
		}

		for(int i=0;i<=4;i++){
			sumatorioXY[i]=sumatorioXY[i]+pow(aux.valor,i)*aux.tiempo;
		}
	
	}

	matrizDet.resize(5);
	matrizA0.resize(5);
	matrizA1.resize(5);
	matrizA2.resize(5);
	matrizA3.resize(5);
	matrizA4.resize(5);
	
	 for (int i = 0; i < 5; i++){
		matrizDet[i].resize(5);
		matrizA0[i].resize(5);
		matrizA1[i].resize(5);
		matrizA2[i].resize(5);
		matrizA3[i].resize(5);
		matrizA4[i].resize(5);
 	}

//Asignacion de valores
 // A todos se les da los mismo valores porque la unica diferencia que hay es entre las A* donde
 // se coloca la linea del sumatorio XY
 	for(int i=0;i<5;i++){
 		for(int j=0;j<5;j++){
 		
 			matrizDet[i][j]=sumatorioX[i+j];
			matrizA0[i][j]=sumatorioX[i+j];
			matrizA1[i][j]=sumatorioX[i+j];
			matrizA2[i][j]=sumatorioX[i+j];
			matrizA3[i][j]=sumatorioX[i+j];
			matrizA4[i][j]=sumatorioX[i+j];
		}
	}
//Aquí insertamos la linea del sumatorio del XY 
	for(int i=0;i<5;i++){
		matrizA0[i][0]=sumatorioXY[i];
		matrizA1[i][1]=sumatorioXY[i];
		matrizA2[i][2]=sumatorioXY[i];
		matrizA3[i][3]=sumatorioXY[i];
		matrizA4[i][4]=sumatorioXY[i];
	}


//gerena los determinantes para Cramer
	det=determinante(matrizDet);
	deta0=determinante(matrizA0);
	deta1=determinante(matrizA1);
	deta2=determinante(matrizA2);
	deta3=determinante(matrizA3);
	deta4=determinante(matrizA4);

//depuracion muestra los determinantes hechos por cramer



	a[0]=deta0/det;
	a[1]=deta1/det;
	a[2]=deta2/det;
	a[3]=deta3/det;
	a[4]=deta4/det;

//muestra polinomio de estimacion
	std::cout<<"Polinomio: t= "<<a[0]<<" + "<<a[1]<<"x "<<a[2]<<"x^2 "<<a[3]<<"x^3 "<<a[4]<<"x^4 "<<std::endl;

	std::ofstream stream;
	//guarda las componentes en un fichero para que datos Estimados Matriz los use
	stream.open("componentesMatriz.txt");
	if(stream.is_open()){
		stream<<a[0]<<"\n";
		stream<<a[1]<<"\n";
		stream<<a[2]<<"\n";
		stream<<a[3]<<"\n";
		stream<<a[4]<<"\n";
		stream.close();
	}else{
		std::cout<<"Fallo en la apertura del fichero: "<<"componentesMatriz.txt"<<std::endl;
	}
 	return true;
}
