#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 7777


int main(int argc, char **argv){
//Recibe la IP y el timeout como argumentos


	char IP[16];
	bzero(IP,sizeof(IP));
	int timeout=5;
	int intento;
	int Client_Socket;
	int Data;
	int opcion;

	int checkSelect;

	char mensaje[20];
	char respuesta[1500];
	bzero(respuesta,sizeof(respuesta));

	struct sockaddr_in Server;
	struct timeval timeoutcheck;
	fd_set fds;

	timeoutcheck.tv_sec=timeout;

	socklen_t Server_Lenght;

	if(argc!=3){
		printf("Fallo de sintaxis: ./<nombre de programa> <direccion IP> <timeout>\n");
		exit(-1);
	}
	
	strcpy(IP,argv[1]);
	timeout=atoi(argv[2]);

	Client_Socket=socket(AF_INET, SOCK_DGRAM, 0);
	if(Client_Socket==-1){
		printf ("No se puede abrir el socket cliente\n");
    	exit (-1);	
	}
	printf("%s\n",IP );
	Server.sin_family = AF_INET;
	Server.sin_port = htons(PORT);
	Server.sin_addr.s_addr = inet_addr(IP);
	Server_Lenght= sizeof(Server);

	//ENVIAMOS COSA
			system("clear");

do{

	do{
		printf("1. Recibe el día, mes y año.\n");
		printf("2. Recibe la hora.\n");
		printf("3. Recibe el día, mes, año y hora.\n");
		printf("\n0. Sal del programa.\n");
		scanf("%d", &opcion);

	switch (opcion){
		case 1:
			strcpy(mensaje,"DAY\0");
			break;
		case 2:
			strcpy(mensaje,"TIME\0");

			break;
		case 3:
			strcpy(mensaje,"DAYTIME\0");

			break;
		case 0:
			//salir
			printf("Cerrando cliente.\n");

			break;


	}
}while((opcion<0) || (opcion>3));
intento=0;
checkSelect=0;
while(intento<3 && checkSelect == 0 && opcion!=0){

	if(opcion!=0){
		int enviado = sendto (Client_Socket, (char *) &mensaje, sizeof(mensaje), 0,
					(struct sockaddr *) &Server, Server_Lenght);
   
   	if (enviado < 0){
			printf("Error al solicitar el servicio\n");
	}else{
		
			FD_SET(Client_Socket,&fds);
			timeoutcheck.tv_sec=timeout;
			timeoutcheck.tv_usec=0;
//std::cout<<timeoutcheck.tv_sec<<std::endl;   			//printf("ESPERANDO...");
		
		/*----------------------------------------------------------------------
			Esperamos la respuesta del Server
			----------------------------------------------------------------------- */ 
			if((checkSelect=select(Client_Socket+1,&fds,NULL,NULL, &timeoutcheck))){
				int recibido = recvfrom (Client_Socket, (char *)&respuesta, sizeof(respuesta), 0,	(struct sockaddr *) &Server, &Server_Lenght);

   				if (recibido > 0){
   					system("clear");
      				printf ("%s\n", respuesta);

	   			}else{
    	  			printf ("Error al leer del servidor\n");
				}
		
			}else{
					printf("Tiempo de espera superado. Reenviando.\n");
					intento++;

			}
		}
	}
}


}while(opcion!=0);

		close(Client_Socket);
}