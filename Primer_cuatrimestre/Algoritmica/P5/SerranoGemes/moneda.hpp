#ifndef MONEDA_HPP
#define MONEDA_HPP

#include <string>

class moneda {
private:
	int valor_;
	std::string etiqueta_;

public:
	moneda(int valor=1, std::string etiqueta="moneda"){
		valor_=valor;
		etiqueta_=etiqueta;
		}

	//Observadores

	inline int getValor()const{return valor_;};
	inline std::string getEtiqueta()const{return etiqueta_;};
	//inline bool getUsado()const{return usado_;};


	//Modificadores

	inline bool setValor(float valor){if(valor<0){return false;}else{valor_=valor;return true;}};
	inline bool setEtiqueta(std::string etiqueta){if(etiqueta!="moneda" and etiqueta!="billete"){return false;}else{etiqueta_=etiqueta;return true;}};

//Modificador
	moneda& operator=(const moneda& m);


};

#endif