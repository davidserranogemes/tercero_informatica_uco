#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>

class material{

private:
	int etiqueta_;
	float valor_;
	int volumen_;
	std::string estado_;//Solo acepta usado, parcial, no_usado
	
public:
	//Constructor
		material(int etiqueta=-1,float valor=-1.0, int volumen=-1,std::string estado="usado"){
			etiqueta_=etiqueta;
			valor_=valor;
			volumen_=volumen;
			estado_=estado;
		}
	//Observadores
		inline int getEtiqueta()const{return etiqueta_;};
		inline int getVolumen()const{return volumen_;};
		inline float getValor()const{return valor_;};
		inline std::string getEstado()const{return estado_;};

	//Modificadores
		inline void setEtiqueta(int etiqueta){etiqueta_=etiqueta;};
		inline bool setValor(float valor){if(valor<0){return false;}else{valor_=valor;return true;}};
		inline bool setVolumen(int volumen){if(volumen<0){return false;}else{volumen_=volumen;return true;}};
		inline bool setEstado(std::string estado){if(estado!="usado" and estado!="parcial" and estado!="no_usado"){return false;}else{estado_=estado;return true;}};

	//Sobrecarga
		material& operator=(const material& m);


};


#endif
