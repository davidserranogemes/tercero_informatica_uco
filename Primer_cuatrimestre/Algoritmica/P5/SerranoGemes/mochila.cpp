#include "mochila.hpp"

#include <iostream>

bool mochila::addMaterial(material &m){
	volumen_usado_+=m.getVolumen();
	conjuntoMateriales.push_back(m);

return true;
}

/*


*/
void mochila::llenarMochila(std::vector<material> &materiales, std::vector<std::vector<int> > &tablaMochila){
	
	//Ordenar no es necesario en la mochila, al contrario que en el del cambio
/*
	for(uint i=0;i<materiales.size();i++){
		int min=materiales[i].getValor();
		int posMin=i;
		for(uint j=i+1;j<materiales.size();j++){
			if(materiales[j].getValor()<min){
				posMin=j;
				min=materiales[j].getValor();
			}
		}
		material auxMaterial;
		auxMaterial=materiales[i];
		materiales[i]=materiales[posMin];
		materiales[posMin]=auxMaterial;
	}

*/

	//Preparar tabla
	tablaMochila.resize(materiales.size());

	for(uint i=0;i<materiales.size();i++){
		tablaMochila[i].resize(getCapacidadMax()+1,0);
	}
	


	for(int i=0;i<getCapacidadMax()+1;i++){
		if(i>=materiales[0].getVolumen()){
			tablaMochila[0][i]=materiales[0].getVolumen()*materiales[0].getValor();
		}
	}

	for(uint i=1;i<materiales.size();i++){
		for(int j=1;j<getCapacidadMax()+1;j++){
			if(j<materiales[i].getVolumen()){
				tablaMochila[i][j]=tablaMochila[i-1][j];
			}else{
				if(tablaMochila[i-1][j]>materiales[i].getValor()*materiales[i].getVolumen()+tablaMochila[i-1][j-materiales[i].getVolumen()]){
					tablaMochila[i][j]=tablaMochila[i-1][j];				
				}else{
					tablaMochila[i][j]=materiales[i].getValor()*materiales[i].getVolumen()+tablaMochila[i-1][j-materiales[i].getVolumen()];
				}
			}
		}
	}

//Mostrar tabla
/*
	for(uint i=0;i<materiales.size();i++){
		std::cout<<"VAL: "<<materiales[i].getValor()<<"\t";
		for(int j=0;j<getCapacidadMax()+1;j++){
			std::cout<<"["<<tablaMochila[i][j]<<"]";
		}
		std::cout<<std::endl;
	}
*/
}

void mochila::obtenerSolucion(std::vector<material> &materiales, std::vector<std::vector<int> > &tablaMochila){
	int capacidadRestante=getCapacidadMax();

	int i=materiales.size()-1;
	bool salir=false;

	while(capacidadRestante!=0 and tablaMochila[i][capacidadRestante]!=0 and !salir){
		if(i>0){
			if(tablaMochila[i][capacidadRestante]==tablaMochila[i-1][capacidadRestante]){
				i--;
			}else{
				if(tablaMochila[i][capacidadRestante]>0){
					capacidadRestante-=materiales[i].getVolumen();
					addMaterial(materiales[i]);
					i--;
				}
			}
		}else{
			if(capacidadRestante>materiales[i].getVolumen()){
				capacidadRestante-=materiales[i].getVolumen();
				addMaterial(materiales[i]);
				salir=true;
			}
		}
	}
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
	std::cout<<"El volumen utilizado :"<<volumen_usado_<<"/"<<getCapacidadMax()<<std::endl;

	for(it=conjuntoMateriales.begin();it!=conjuntoMateriales.end();it++){
		std::cout<<"ID: "<<it->getEtiqueta()<<std::endl;
		std::cout<<"\tPrecio unidad: "<<it->getValor()<<std::endl;
		std::cout<<"\tVolumen: "<<it->getVolumen()<<std::endl;
		std::cout<<"\tValor total: "<<it->getVolumen()*it->getValor()<<std::endl<<std::endl;

	}
}


void mochila::vaciarMochila(){
	volumen_usado_=0;

	conjuntoMateriales.clear();
}