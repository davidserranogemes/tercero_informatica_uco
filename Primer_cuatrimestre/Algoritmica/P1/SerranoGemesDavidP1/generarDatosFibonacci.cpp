#include "generarDatosFibonacci.hpp"



void generarDatosFibonacci(int min, int max, int inc){

	int val;
	
	double long result;
	
	Clock time;
	
	struct tiempoUsado aux;
	
	std::list<struct tiempoUsado> listaTiempos;
	
	std::string nombreFichero="DatosPreviosFibonacci.txt";

	for(val=min;val<=max;val=val+inc){
	time.restart();
	
	std::cout<<"Calculando fibonacci de :"<<val<<std::endl;
	result=fibonacci(val);
	
	aux.tiempoEstimado=-1;//Como no vamos a estimar el tiempo rellenamos con -1
	if (time.isStarted()){
			time.stop();
			aux.tiempo=time.elapsed();
			aux.valor=val;

			std::cout <<"Para n="<<aux.valor<<" Resultado :"<<result << " Tiempo: " << aux.tiempo << " microsegundos \n";
			listaTiempos.push_back(aux);

	}	

}
std::cout<<listaTiempos.size()<<std::endl;
escribirFichero(listaTiempos,nombreFichero);





}