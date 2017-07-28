#include "material.hpp"

material& material::operator=(const material& m){
	this->setEtiqueta(m.getEtiqueta());
	this->setValor(m.getValor());
	this->setVolumen(m.getVolumen());
	this->setEstado(m.getEstado());

	return *this;
}