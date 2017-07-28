#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#define MSG_SIZE 250
#define MAX_CLIENTS 50
#define PORT 2050

#define CONS_VAL 50
#define VOCAL_VAL 50

#include <string>

struct player{
	std::string userName;
	std::string password;
	bool isConected=false;
	int sd=-1;
	bool isInGame=false;
	int intentos=0;
	int puntuacion=0;
};



#endif