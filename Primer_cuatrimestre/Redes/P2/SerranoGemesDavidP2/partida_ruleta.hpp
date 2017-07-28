#ifndef PARTIDA_RULETA
#define PARTIDA_RULETA

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "constant.hpp"


class partida_ruleta{
private:
	bool partida_individual;
	bool partida_empezada;
	uint numJugadores;

	std::vector<int> jugadores;

	std::string panelResuelto;
	std::string panelOculto;

	uint turn;

public:
	partida_ruleta(bool individual=true){
		std::ifstream stream;

		std::vector<std::string> refranes;
		std::string aux;

		if(individual){
			jugadores.resize(1);
		}else{
			jugadores.resize(3);
		}
		partida_individual=individual;

		stream.open("listaRefranes.txt");

		if(!stream.is_open()){
			std::cout<<"Error critico, es obligatorio el fichero listaRefranes.txt"<<std::endl;
		}

		while(getline(stream, aux,'\n')){
			refranes.push_back(aux);
		}
		srand(time(NULL));

		int selector=rand()%refranes.size();

		panelResuelto=refranes[selector];

		panelOculto.resize(panelResuelto.size(),'-');
		
		for(uint i=0;i<panelOculto.size();i++)	{
			if(isalnum(panelResuelto[i])==0){
				panelOculto[i]=panelResuelto[i];
			}
		}
		partida_empezada=false;
		numJugadores=0;
		turn=0;
	}

	inline std::string getPanelOculto(){return panelOculto;};
	inline std::string getPanelResuelto(){return panelResuelto;};

	inline bool partidaStarted(){return partida_empezada;};

	bool addJugador(int sd);
	bool delJugador(int sd);//Por si un jugador se desconecta del servidor
	bool isInThisGame(int sd);

	int isLetra(char c);

	bool resolver(std::string solucion){if(solucion==panelResuelto){return true;}else{return false;}};

	inline std::vector<int> getJugadores(){return jugadores;};
	inline int getTam(){return numJugadores;};

	inline bool checkTurn(int sd){if(jugadores[turn]!=sd){return false;}else{return true;}};

	inline int getTurn(){return jugadores[turn];};
	inline void turnPlus(){turn=(turn+1)%numJugadores;};

};

#endif