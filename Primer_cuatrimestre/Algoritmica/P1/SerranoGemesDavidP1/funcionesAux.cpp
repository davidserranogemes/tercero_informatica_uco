#include <locale>
#include <string>

#include "funcionesAux.hpp"
using std::string;

bool checkCadenaIsDigit(string cadena){
	bool NUMBER=true;

	for(unsigned int i=0;i<cadena.size();i++){
			if(!isdigit(cadena[i])){
					NUMBER=false;
			}
	}
	return NUMBER;
}

bool checkCadenaIsDigit(char *cadena){
	string cad=cadena;
	bool NUMBER=true;

	for(unsigned int i=0;i<cad.size();i++){
			if(!isdigit(cad[i])){
					NUMBER=false;
			}
	}
	return NUMBER;

}