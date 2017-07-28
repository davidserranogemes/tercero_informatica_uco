 #include "cambio.hpp"

#include <iostream>


bool cambio::addMoneda(moneda &m, int cantidad){
	struct monedaNum coin;

	coin.numeroMonedas=cantidad;
	coin.m=m;
	listaCambio_.push_back(coin);

	return true;

}

void cambio::realizarCambio(std::vector<moneda> &monedas,std::vector<std::vector<int>> &tablaCambio){
	
	//Ordenacion del vector de monedas segun valor minimo necesario para aplicar el algoritmo
	for(uint i=0;i<monedas.size();i++){
		int min=monedas[i].getValor();
		int posMin=i;
		for(uint j=i+1;j<monedas.size();j++){
			if(monedas[j].getValor()<min){
				posMin=j;
				min=monedas[j].getValor();
			}
		}
		moneda auxMoneda;
		auxMoneda=monedas[i];
		monedas[i]=monedas[posMin];
		monedas[posMin]=auxMoneda;
	}

	//Preparar tabla
	tablaCambio.resize(monedas.size());

	for(uint i=0;i<monedas.size();i++){
		tablaCambio[i].resize(getCambioTotal()+1,0);
	}

	for(int i=1;i<getCambioTotal()+1;i++){
		if(i>=monedas[0].getValor()){
			tablaCambio[0][i]=monedas[0].getValor()+tablaCambio[0][i-monedas[0].getValor()];
		}
	}

	for(uint i=1;i<monedas.size();i++){
		for(int j=1;j<getCambioTotal()+1;j++){

			if(j<monedas[i].getValor()){
				tablaCambio[i][j]=tablaCambio[i-1][j];
			}else{
				if(tablaCambio[i-1][j]<1+tablaCambio[i][j-monedas[i].getValor()]){
					tablaCambio[i][j]=tablaCambio[i-1][j];
				}else{
					tablaCambio[i][j]=1+tablaCambio[i][j-monedas[i].getValor()];

				}
			}
		}
	}

	//Para ver la tabla;
	/*
	for(uint i=0;i<monedas.size();i++){
		std::cout<<"VAL: "<<monedas[i].getValor()<<"\t";
		for(int j=0;j<getCambioTotal()+1;j++){
			std::cout<<"["<<tablaCambio[i][j]<<"]";
		}
		std::cout<<std::endl;
	}
*/

}

void cambio::obtenerSolucion(std::vector<moneda> monedas,std::vector<std::vector<int>> &tablaCambio){
	int cambioRestante=getCambioTotal();

	int cantidadMonedas=0;
	int valorMoneda=0;
	int i=monedas.size()-1;


	while(cambioRestante!=0 and tablaCambio[i][cambioRestante]!=0){
		if(i>0){
			if(tablaCambio[i][cambioRestante]==tablaCambio[i-1][cambioRestante]){
				if(cantidadMonedas!=0){
					moneda aux(valorMoneda,monedas[i].getEtiqueta());
					addMoneda(aux,cantidadMonedas);
					cantidadMonedas=0;
				}
				i--;
			}else{
				cantidadMonedas++;
				valorMoneda=monedas[i].getValor();

				cambioRestante-=monedas[i].getValor();
			}
		}else{
			cantidadMonedas++;
			valorMoneda=monedas[i].getValor();
			cambioRestante-=monedas[i].getValor();
		}

	}
	if(cantidadMonedas!=0){
		moneda aux(valorMoneda,monedas[i].getEtiqueta());
		addMoneda(aux,cantidadMonedas);
		cantidadMonedas=0;
	}



}

void cambio::monedasUsadas(){
	std::list<monedaNum>::iterator it;
	int numMonedas=0;
	int numBilletes=0;
	int cantidadCambio=0;	

	for(it=listaCambio_.begin();it!=listaCambio_.end();it++){
		std::cout<<"Valor: "<<it->m.getValor()<<" centimos"<<std::endl;
		std::cout<<"\tTipo: "<<it->m.getEtiqueta()<<std::endl;
		std::cout<<"\tCantidad: "<<it->numeroMonedas<<std::endl;
		std::cout<<"\tTotal= "<<it->m.getValor()*it->numeroMonedas<<" centimos"<<std::endl<<std::endl;
		
		if(it->m.getEtiqueta()=="billete"){
			numBilletes+=it->numeroMonedas;
		}else{
			numMonedas+=it->numeroMonedas;
		}


		cantidadCambio+=it->numeroMonedas*it->m.getValor();
	}
	if(numMonedas>0)
		std::cout<<"El numero total de monedas es "<<numMonedas<<std::endl;
	if(numBilletes>0)
		std::cout<<"El numero total de billetes es "<<numBilletes<<std::endl;

	if(cantidadCambio!=getCambioTotal()){
		std::cout<<"No se puede devolver la cantidad exacta. Devolvemos "<<cantidadCambio<<" centimos."<<std::endl<<std::endl;
	}else{
		std::cout<<"Se devuelve la cantidad exacta. Devolvemos "<<cantidadCambio<<" centimos."<<std::endl<<std::endl;
	}

}