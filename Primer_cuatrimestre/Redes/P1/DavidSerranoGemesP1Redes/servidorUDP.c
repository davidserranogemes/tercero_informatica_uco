#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define PORT 7777

int main(){
	int Server_Socket;
	struct sockaddr_in Server;
	char option[1500];
	char respuesta[1500];
	int received;
	int messa=0;
	struct sockaddr_in Client;
	socklen_t Client_Lenght;
	struct tm *info;
	time_t rawtime;

	bzero(option,sizeof(option));
	bzero(respuesta,sizeof(respuesta));

	if((Server_Socket= socket(AF_INET,SOCK_DGRAM,0))==-1){
		printf("No se puedo abrir el socket del servidor. Saliendo.\n");
		exit(-1);
	}

	Server.sin_family=AF_INET;
	Server.sin_port=htons(PORT);
	Server.sin_addr.s_addr=htonl(INADDR_ANY);

	if(bind(Server_Socket,(struct sockaddr*)&Server, sizeof(Server))==-1){
		close(Server_Socket);
		exit(-1);

	}

	Client_Lenght=sizeof(Client);

	while(1){
		//Ejecucion completa del DAYTIME
		printf("ESPERANDO...\n");

		received=recvfrom (Server_Socket, option,sizeof(option),0,(struct sockaddr *) &Client,&Client_Lenght);
		if(received>0){
			printf("%s\n",option);

			if(strcmp("DAY\0",option)==0){
				messa=1;
			}else{
				if(strcmp("TIME\0",option)==0){
					messa=2;
				}else{
					if(strcmp("DAYTIME\0",option)==0){
						messa=3;
					}else{
						messa=0;
					}
				}
			}
			time( &rawtime);
			info = localtime( &rawtime );
			switch(messa){
				case 1://DAY

					strftime(respuesta,1500,"%A, %e de %B de %Y ",info);
					break;

				case 2://TIME

					strftime(respuesta,1500,"%H:%M:%S",info);

					break;

				case 3://DAYTIME

					strftime(respuesta,1500,"%A,%e de %B de %Y%e, %H:%M:%S",info);

					break;

				case 0:
			//salir
					printf("Error! Recibido un mensaje extranio.\n");

					break;

			}
			printf("Enviando respuesta.\n");
			printf("%s\n",respuesta);


			int send = sendto (Server_Socket, respuesta,sizeof(respuesta),0,(struct sockaddr *) &Client, Client_Lenght);
		}
		
		
	}
	close(Server_Socket);
}