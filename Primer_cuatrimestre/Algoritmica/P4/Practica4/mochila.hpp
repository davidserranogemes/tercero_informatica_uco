#ifndef MOCHILA_HPP
#define MOCHILA_HPP

#include <list>
#include <vector>

#include "material.hpp"

class mochila{
private:
	int capacidadMax_;
	int volumen_usado_;
	std::list<material> conjuntoMateriales;

public:
	//Constructor
	mochila(int capacidad=100){
		if(capacidad>0){
			capacidadMax_=capacidad;
			volumen_usado_=0;
		}else{
			volumen_usado_=0;
		}
	}

	//Observadores
	inline int getCapacidadMax()const{return capacidadMax_;};
	inline int getVolumenRestante()const{return (capacidadMax_-volumen_usado_);};
	inline std::list<material> getConjuntoMateriales()const{return conjuntoMateriales;};

	float getValorMochila();
	void contenidoMochila();

	//Modificadores

	inline bool setCapacidadMax(int capMax){if(capMax>0){capacidadMax_=capMax;return true;}else{return false;}};

	bool addMaterial(material &m);
	void llenarMochila(std::vector<material> &materiales);
	void vaciarMochila();


};
#endif