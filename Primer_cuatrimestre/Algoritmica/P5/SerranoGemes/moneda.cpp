#include "moneda.hpp"

moneda& moneda::operator=(const moneda& m){

	this->setValor(m.getValor());
	this->setEtiqueta(m.getEtiqueta());

	return *this;


}
