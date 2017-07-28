#ifndef CAMBIO_HPP
#define CAMBIO_HPP


#include <list>
#include <vector>
#include <cassert>

#include "moneda.hpp"


struct monedaNum{
	int numeroMonedas;
	moneda m;

};


class cambio{
private:
	int cambioTotal_;
	std::list<monedaNum> listaCambio_;

public: 
	cambio(int cambioTotal=100){
		cambioTotal_=cambioTotal;
	}

	//observadores

	inline int getCambioTotal()const{return cambioTotal_;};
	inline monedaNum getMoneda(uint i){
		assert(i>0 and i<listaCambio_.size());
		uint j=0;
		for(std::list<monedaNum>::iterator it=listaCambio_.begin();it!=listaCambio_.end();it++,j++){
			if(i==j){
				return *it;
			}
		}
	}

	void monedasUsadas();
	//Modificadores

	inline bool setCambio(int cambio){if(cambio<0){return false;}else{cambioTotal_=cambio;return true;}};

	bool addMoneda(moneda &m, int cantidad);
	void realizarCambio(std::vector<moneda> &monedas,std::vector<std::vector<int>> &tablaCambio);
	void obtenerSolucion(std::vector<moneda> monedas,std::vector<std::vector<int>> &tablaCambio);



};
#endif