#include "fichero.hpp"


bool leerFichero(std::string nombreFich, std::vector<material> &v){
	std::ifstream stream;
	
	material auxMat;
	int auxVal;

	int lastEt=-1;
	stream.open(nombreFich.c_str());
	if(stream.is_open()){
		v.clear();
		while(!stream.eof()){
			stream>>auxVal;
			auxMat.setEtiqueta(auxVal);
			
			stream>>auxVal;
			auxMat.setVolumen(auxVal);
			
			stream>>auxVal;
			auxMat.setValor(auxVal);

			
			if(lastEt!=auxMat.getEtiqueta()){
				v.push_back(auxMat);
			}
			lastEt=auxMat.getEtiqueta();
		}

		stream.close();
		return true;
	}else{
		return false;
	}
}



bool leerFichero(std::string nombreFich, std::vector<moneda> &v){
		std::ifstream stream;
	
	moneda auxMon;
	int auxVal;
	std::string auxEti;

	int lastEt=-1;
	stream.open(nombreFich.c_str());

	if(stream.is_open()){
		v.clear();
		while(!stream.eof()){
			stream>>auxEti;
			auxMon.setEtiqueta(auxEti);
						
			stream>>auxVal;
			auxMon.setValor(auxVal);

			if(lastEt!=auxMon.getValor()){
				v.push_back(auxMon);
			}
			lastEt=auxMon.getValor();
		}

		stream.close();
		return true;
	}else{
		return false;
	}
}
