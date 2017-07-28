#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>

#include "funcionesFichero.hpp"
#include "funcionesMatriz.hpp"
using std::vector;

bool minimosCuadradosFib(){

	std::list<struct tiempoUsado> listaTiempos;
	struct tiempoUsado aux;
	std::string nombreFichero="DatosPreviosFibonacci.txt";

	listaTiempos=leerFichero(nombreFichero);
	if(listaTiempos.size()==0){
		std::cout<<"Hay un fallo en la lectura del fichero "<<nombreFichero<<", puede estar vacio o no existir."<<std::endl;
		return false;
	}
	int nEle=listaTiempos.size();
	long double det,deta0,deta1;
	vector < vector < long double > >matrizDet;
	vector<vector<long double>> matrizA0;
	vector<vector<long double>> matrizA1;
	long double sumatorioX=0;
	long double sumatorioX2=0;
	long double sumatorioXY=0;
	long double sumatorioY=0;

	long double a0;
	long double a1=0;

	while(!listaTiempos.empty()){

		aux=listaTiempos.front();
		listaTiempos.pop_front();
	
		sumatorioX=sumatorioX+pow(2,aux.valor);//Recordemos que hemos hecho la transformacion 2^n=z
		sumatorioX2=sumatorioX2+pow(pow(2,aux.valor),2);
		sumatorioXY=sumatorioXY+pow(2,aux.valor)*aux.tiempo;
		sumatorioY=sumatorioY+aux.tiempo;
	}
	matrizDet.resize(2);
	matrizA0.resize(2);
	matrizA1.resize(2);
	
	 for (int i = 0; i < 2; i++){
  		matrizDet[i].resize(2);
		matrizA0[i].resize(2);
		matrizA1[i].resize(2);
	 }

	matrizA0[0][0]=sumatorioY;
	matrizA0[0][1]=sumatorioX;
	matrizA0[1][0]=sumatorioXY;
	matrizA0[1][1]=sumatorioX2;

	matrizA1[0][0]=nEle;
	matrizA1[0][1]=sumatorioY;
	matrizA1[1][0]=sumatorioX;
	matrizA1[1][1]=sumatorioXY;

	matrizDet[0][0]=nEle;
	matrizDet[0][1]=sumatorioX;
	matrizDet[1][0]=sumatorioX;
	matrizDet[1][1]=sumatorioX2;

	det=determinante(matrizDet);
	deta0=determinante(matrizA0);
	deta1=determinante(matrizA1);

	a0=deta0/det;
	a1=deta1/det;

	std::cout<<"Polinomio: t= "<<a0<<" + "<<a1<<" * 2^n"<<std::endl;

	std::ofstream stream;

	stream.open("componentesFibonacci.txt");
	if(stream.is_open()){
		stream<<a0<<"\n";
		stream<<a1<<"\n";
		stream.close();
	}else{
		std::cout<<"Fallo en la apertura del fichero: "<<"componentesFibonacci.txt"<<std::endl;
		exit(-1);
	}

 	return true;
}
