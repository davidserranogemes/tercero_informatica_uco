#include <iostream>
#include <fstream>

#include "ruleta_suerte.hpp"



bool ruleta_suerte::loadPlayers(){
	std::ifstream stream;
	string aux;

	struct player auxPlayer;

	stream.open("registredPlayers.txt");

	auxPlayer.isConected=false;

	if(!stream.is_open()){
		std::cout<<"There isnt players registred yet."<<std::endl;
		return false;
	}else{
		while(getline(stream,aux,'/')){
			
			auxPlayer.userName=aux;
			getline(stream,aux);
			auxPlayer.password=aux;

			playersOnline.push_back(auxPlayer);
		}
		std::cout<<"Hay "<<numPlayers()<<" jugadores registrados."<<std::endl;
		return true;
	}
}

bool ruleta_suerte::savePlayers(){
	std::ofstream stream;

	list<struct player>::iterator it;

	stream.open("registredPlayers.txt");

	if(!stream.is_open()){
		std::cout<<"Cant open registredPlayers.txt ."<<std::endl;
		return false;
	}else{
		for(it=playersOnline.begin();it!=playersOnline.end();it++){
			stream<<it->userName<<"/"<<it->password<<std::endl;
		}
		std::cout<<"Players saved on file."<<std::endl;
		playersFileUpdated=true;

		return true;
	}

}

bool ruleta_suerte::addPlayers(struct player p){
	uint check=playersOnline.size();
	list<struct player>::iterator it;

	
	for(it=playersOnline.begin();it!=playersOnline.end();it++){
		if((it->userName)==p.userName){
			std::cout<<p.userName<<" is already used on this server. Take other username please."<<std::endl;
			return false;
		}
	}


	playersOnline.push_back(p);
	if(check<playersOnline.size()){
		playersFileUpdated=false;

		return true;
	}else{
		return false;
	}
}


//Devuelve 0 si encuentra al usuario y le enlaza el sd
//Devuelve 1 si no lo encuentra
//Devuelve 2 si lo encuentra pero ya esta logeado
int ruleta_suerte::linkLogin(int sd, char * userName){
	list<struct player>::iterator it;

	
	for(it=playersOnline.begin();it!=playersOnline.end();it++){
		if((it->userName)==userName){
			if(it->isConected==false){
				it->sd=sd;
				return 0;
			}else{
				return 2;
			}
		}
	}
	return 1;

}
//Devuelve 0 si el sd tiene un username linked y la pass coincide
//Si no ocurre por cualquier cosa, elimina el link con el usuario
//Devuelve 1 si no habia un username linked
//Devuelve 2 si no coincide la contraseña
int ruleta_suerte::checkPassword(int sd, char * password){
	list<struct player>::iterator it;
	int i=0;
	for(it=playersOnline.begin();it!=playersOnline.end();it++,i++){
		if((it->sd)==sd){
			if(it->password==password){
				it->isConected=true;
				return 0;
			}else{
				it->sd=-1;
				return 2;
			}
		}
	}
	return 1;
}

bool ruleta_suerte::logoutUser(int sd){
	list<struct player>::iterator it;
	
	for(it=playersOnline.begin();it!=playersOnline.end();it++){
		if((it->sd)==sd){
			it->isConected=false;
			it->isInGame=false;
			it->sd=-1;
			return true;
		}
	}
	return false;
}

bool ruleta_suerte::endGameUser(int sd){
	list<struct player>::iterator it;
	
	for(it=playersOnline.begin();it!=playersOnline.end();it++){
		if((it->sd)==sd){
			it->isInGame=false;
			return true;
		}
	}
	return false;
}

//Devuelve true si lo encuentra en partida
//False si no
bool ruleta_suerte::isInGame(int sd){
	list<struct player>::iterator it;
	
	for(it=playersOnline.begin();it!=playersOnline.end();it++){
		if((it->sd)==sd){
			return it->isInGame;
		}
	}
	return false;
}

bool ruleta_suerte::actualizarIngame(int sd){
	list<struct player>::iterator it;
	
	for(it=playersOnline.begin();it!=playersOnline.end();it++){
		if((it->sd)==sd){
			if(it->isInGame)
				it->isInGame=false;
			else
				it->isInGame=true;
			return true;
		}
	}
	return false;
}

bool ruleta_suerte::isLoged(int sd){
	list<struct player>::iterator it;
	
	for(it=playersOnline.begin();it!=playersOnline.end();it++){
		if((it->sd)==sd){
			return it->isConected;
		}
	}
	return false;
}

std::string ruleta_suerte::getUserName(int sd){
		list<struct player>::iterator it;
	
	for(it=playersOnline.begin();it!=playersOnline.end();it++){
		if((it->sd)==sd){
			return (it->userName);
		}
	}
	return "";
}


int ruleta_suerte::getPuntos(int sd){
	list<struct player>::iterator it;
	
	for(it=playersOnline.begin();it!=playersOnline.end();it++){
		if((it->sd)==sd){
			return it->puntuacion;
		}
	}
	return -1;
}

bool ruleta_suerte::sumaPuntos(int sd,int nVeces,int cantidad){
	list<struct player>::iterator it;
	
	for(it=playersOnline.begin();it!=playersOnline.end();it++){
		if((it->sd)==sd){
			it->puntuacion=it->puntuacion+nVeces*cantidad;
			return true;
		}
	}
	return false;
}

bool ruleta_suerte::restaPuntos(int sd,int nVeces,int cantidad){
	list<struct player>::iterator it;
	
	for(it=playersOnline.begin();it!=playersOnline.end();it++){
		if((it->sd)==sd){
			if(it->puntuacion>=nVeces*cantidad){
				it->puntuacion=it->puntuacion-nVeces*cantidad;
				return true;
			}else{
				return false;
			}
		}
	}
	return false;
}

bool ruleta_suerte::zeroPuntos(int sd){
	list<struct player>::iterator it;
	
	for(it=playersOnline.begin();it!=playersOnline.end();it++){
		if((it->sd)==sd){
			it->puntuacion=0;
			return true;
		}
	}
	return false;	
}

bool ruleta_suerte::intentoPlus(int sd){
	list<struct player>::iterator it;
	
	for(it=playersOnline.begin();it!=playersOnline.end();it++){
		if((it->sd)==sd){
			it->intentos++;
			return true;
		}
	}
	return false;	
}

bool ruleta_suerte::intentoZero(int sd){
	list<struct player>::iterator it;
	
	for(it=playersOnline.begin();it!=playersOnline.end();it++){
		if((it->sd)==sd){
			it->intentos=0;
			return true;
		}
	}
	return false;	
}
int ruleta_suerte::getIntentos(int sd){
	list<struct player>::iterator it;
	
	for(it=playersOnline.begin();it!=playersOnline.end();it++){
		if((it->sd)==sd){
			return it->intentos;
		}
	}
	return -1;
}