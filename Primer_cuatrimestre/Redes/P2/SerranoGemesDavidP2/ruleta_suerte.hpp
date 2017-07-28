#ifndef RULETA_SUERTE_HPP
#define RULETA_SUERTE_HPP

#include <list>
#include <string>

#include "constant.hpp"

using std::string;
using std::list;





class ruleta_suerte{

	private:
		list<struct player> playersOnline;
		bool playersFileUpdated=true;


	public:
		bool loadPlayers();

		bool savePlayers();

		bool addPlayers(struct player p);

		int linkLogin(int sd, char * userName);

		int checkPassword(int sd, char * password);

		bool logoutUser(int n);
		bool endGameUser(int sd);


		bool isLoged(int sd);

		inline int numPlayers(){return playersOnline.size();};

		inline bool isFileUpdated(){return playersFileUpdated;};

		bool isInGame(int sd);

		bool actualizarIngame(int sd);

		std::string getUserName(int sd);

		int getPuntos(int sd);

		bool sumaPuntos(int sd,int nVeces,int cantidad);

		bool restaPuntos(int sd,int nVeces,int cantidad);

		bool zeroPuntos(int sd);

		bool intentoPlus(int sd);

		bool intentoZero(int sd);

		int getIntentos(int sd);
	};


#endif