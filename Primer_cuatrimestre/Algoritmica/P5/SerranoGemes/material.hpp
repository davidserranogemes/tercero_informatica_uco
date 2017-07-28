#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>

class material{

private:
	int etiqueta_;
	float valor_;
	int volumen_;
	
public:
	//Constructor
		material(int etiqueta=-1,float valor=-1.0, int volumen=-1){
			etiqueta_=etiqueta;
			valor_=valor;
			volumen_=volumen;
			//estado_=estado;
		}
	//Observadores
		inline int getEtiqueta()const{return etiqueta_;};
		inline int getVolumen()const{return volumen_;};
		inline float getValor()const{return valor_;};

	//Modificadores
		inline void setEtiqueta(int etiqueta){etiqueta_=etiqueta;};
		inline bool setValor(float valor){if(valor<0){return false;}else{valor_=valor;return true;}};
		inline bool setVolumen(int volumen){if(volumen<0){return false;}else{volumen_=volumen;return true;}};

	//Sobrecarga
		material& operator=(const material& m);


};


#endif
