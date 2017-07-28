#include "partida_ruleta.hpp"

bool partida_ruleta::addJugador(int sd){
	if((numJugadores==jugadores.size()) or partida_empezada){
		return false;
	}
	jugadores[numJugadores]=sd;
	numJugadores++;
	if(numJugadores==jugadores.size()){
		partida_empezada=true;
	}
	return true;
}

//devuelve true si quedan jugadores
//devuelve false si queda vacio
bool partida_ruleta::delJugador(int sd){
	uint i;
	
	for(i=0;i<jugadores.size()-1;i++){
		if(jugadores[i]==sd){
			break;
		}
	}
	//Corrige los turnos de la ruleta, que se ven afectados cuando se va el i <turnActual o si se va el ultimo
	if(i<turn){
		turn--;
	}else{
		if(turn==(numJugadores-1)){
			turn=0;
		}
	}

	for(;i<jugadores.size()-1;i++){
		jugadores[i]=jugadores[i+1];
	}
	numJugadores--;
	if(numJugadores==0){
		return false;
	}else{
		return true;
	}
}	

bool partida_ruleta::isInThisGame(int sd){
	for(uint i=0;i<jugadores.size();i++){
		if(jugadores[i]==sd){
			return true;
		}
	}
	return false;
}
//Devuelve el numero de coincidencias encontradas
//Devuelve -1 si ya se habia recibido
int partida_ruleta::isLetra(char c){
	int numC=0;

	for(uint i=0;i<panelResuelto.size();i++){
		if(panelOculto[i]==c){
			turn=(turn+1)%numJugadores; //pierdes eñ turno por no estar atento

			return -1;
		}
	}

	for(uint i=0;i<panelResuelto.size();i++){
		if(panelResuelto[i]==c){
			numC++;
			panelOculto[i]=c;
		}
	}
	turn=(turn+1)%numJugadores;
	return numC;
}
