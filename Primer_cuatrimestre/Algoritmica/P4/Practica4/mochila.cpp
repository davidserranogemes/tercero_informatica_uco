#include "mochila.hpp"

#include <iostream>

bool mochila::addMaterial(material &m){
	if(volumen_usado_!=capacidadMax_){
		material auxMaterial;
		if(getVolumenRestante()>m.getVolumen()){	
			//Cabe todo
			m.setEstado("usado");
			auxMaterial=m;
			volumen_usado_=volumen_usado_+auxMaterial.getVolumen();

		}else{//No cabe todo
			m.setEstado("parcial");
			auxMaterial=m;
			auxMaterial.setVolumen(capacidadMax_-volumen_usado_);
			volumen_usado_=capacidadMax_;
		}
		conjuntoMateriales.push_back(auxMaterial);
	
		return true;
	}else{
		return false;
	}
}
void mochila::llenarMochila(std::vector<material> &materiales){
	
	int precioMaximo;
	int materialMaximo;
	bool materialDisponible;

	material auxMaterial;
	
	vaciarMochila();

	for(uint i=0;i<materiales.size();i++){
		materiales[i].setEstado("no_usado");
	}
	do{
		precioMaximo=0;
		materialMaximo=0;
		materialDisponible=false;

		for(uint i=0;i<materiales.size();i++){
			if(materiales[i].getEstado()=="no_usado"){
				materialDisponible=true;
				if(materiales[i].getValor()>precioMaximo){
					materialMaximo=i;
					precioMaximo=materiales[i].getValor();
				}
			}
		}
		if(materialDisponible){
			addMaterial(materiales[materialMaximo]);
		}
	}while(getVolumenRestante()!=0 and materialDisponible);

}


float mochila::getValorMochila(){
	std::list<material>::iterator it;
	float valor=0.0;

	for(it=conjuntoMateriales.begin();it!=conjuntoMateriales.end();it++){
		valor=valor+it->getValor()*it->getVolumen();
	}
	return valor;

}

void mochila::contenidoMochila(){
	std::list<material>::iterator it;
	

	for(it=conjuntoMateriales.begin();it!=conjuntoMateriales.end();it++){
		std::cout<<"ID: "<<it->getEtiqueta()<<std::endl;
		std::cout<<"\tPrecio unidad: "<<it->getValor()<<std::endl;
		std::cout<<"\tVolumen: "<<it->getVolumen()<<std::endl;
		std::cout<<"\tEstado: "<<it->getEstado()<<std::endl;
		std::cout<<"\tValor total: "<<it->getVolumen()*it->getValor()<<std::endl<<std::endl;

	}
}


void mochila::vaciarMochila(){
	volumen_usado_=0;

	conjuntoMateriales.clear();
}