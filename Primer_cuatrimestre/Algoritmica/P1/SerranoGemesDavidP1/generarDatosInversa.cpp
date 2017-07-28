#include <vector>
#include <list>

#include "generarDatosInversa.hpp"
#include "funcionesAux.hpp"
#include "funcionesMatriz.hpp"
#include "funcionesFichero.hpp"
#include "ClaseTiempo.hpp"


void generarDatosInversa(int min, int max, int inc){

	int val;

	vector< vector <double> > matriz;
	vector< vector <double> > inversaMatriz;

	Clock time;
	struct tiempoUsado aux;

	std::list<struct tiempoUsado> listaTiempos;
	std::string nombreFichero="DatosInversa.txt";

	for(val=min;val<=max;val=val+inc){
		matriz.resize(val);
		inversaMatriz.resize(val);

		for(int j=0; j<val; j++){
			matriz[j].resize(val,0);
			inversaMatriz[j].resize(val,0);
		}	
		genMatriz(val,matriz);
		time.restart();
//termino inversa
		invermat(val,matriz,inversaMatriz);
		aux.tiempoEstimado=-1;//Como no vamos a estimar el tiempo rellenamos con -1
		//if (time.isStarted()){
		time.stop();
		aux.tiempo=time.elapsed();
		aux.valor=val;

		std::cout <<"Para "<<val<<"x"<<aux.valor<<" Tiempo: " << aux.tiempo << " microsegundos \n";
		listaTiempos.push_back(aux);

		std::cout<<"Terminado: "<<val<<std::endl<<std::endl;
	}
	escribirFichero(listaTiempos,nombreFichero);
}