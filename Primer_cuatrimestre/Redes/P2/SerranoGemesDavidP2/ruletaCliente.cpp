#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


#include "constant.hpp"
#include <string>
#include <iostream>

int main(int argc, char**argv){

	int sd;
	struct sockaddr_in sockname;
	char buffer[MSG_SIZE];
	socklen_t len_sockname;
    fd_set readfds, auxfds;
    int salida;
    int fin = 0;
    char IP[16];
    bzero(IP,sizeof(IP));

    if(argc!=2){
    	std::cout<<"-Err. Sintaxis erronea. ./programa ipServidor"<<std::endl;
    	exit(-1);
    }
    strcpy(IP,argv[1]);

    sd = socket (AF_INET, SOCK_STREAM, 0);
	if (sd == -1)
	{
		std::cerr<<"-Err. No se puede abrir el socket cliente."<<std::endl;
    		exit (1);	
	}
	sockname.sin_family = AF_INET;
	sockname.sin_port = htons(PORT);
	sockname.sin_addr.s_addr =  inet_addr(IP);

	len_sockname = sizeof(sockname);

	if (connect(sd, (struct sockaddr *)&sockname, len_sockname) == -1)
	{
		std::cerr<<"-Err. Error de conexion"<<std::endl;
		exit(1);
	}
    
    FD_ZERO(&auxfds);
    FD_ZERO(&readfds);
    
    FD_SET(0,&readfds);
    FD_SET(sd,&readfds);
std::cout<<"Escriba \" HELP \" para obtener ayuda sobre los comandos."<<std::endl;
	do
	{  
//        system("clear");

        auxfds = readfds;
        salida = select(sd+1,&auxfds,NULL,NULL,NULL);
        
        //Tengo mensaje desde el servidor
        if(FD_ISSET(sd, &auxfds)){
            
            bzero(buffer,sizeof(buffer));
            recv(sd,buffer,sizeof(buffer),0);
            
            printf("\n%s\n",buffer);
            
            if(strcmp(buffer,"-Err. Demasiados clientes conectados, intentelo mas tarde.\n") == 0)
                fin =1;
            
            if(strcmp(buffer,"+Ok. Desconexion del servidor\n") == 0)
                fin =1;
            
        }
        else
        {
            
            //He introducido información por teclado
            if(FD_ISSET(0,&auxfds)){
                bzero(buffer,sizeof(buffer));
                
                fgets(buffer,sizeof(buffer),stdin);
                
                if(strcmp(buffer,"HELP\n")==0){
                    std::cout<<"REGISTRO -u (nombre-usuario) -p (password)"<<std::endl;
                    std::cout<<"USUARIO (nombre-usuario)"<<std::endl;
                    std::cout<<"PASSWORD (password) --> Debe usar USUARIO previamente."<<std::endl;
                    std::cout<<"PARTIDA_INDIVIDUAL --> Juego en solitario"<<std::endl;
                    std::cout<<"PARTIDA_GRUPO --> Espera a dos personas mas para competir con ellos"<<std::endl;
                    std::cout<<"VOCAL (vocal) --> Muestra la vocal elegida en el panel. En partida grupal requiere al menos 50 puntos"<<std::endl;
                    std::cout<<"CONSONANTE (consonante) --> Muestra la consonante elegida en el panel. En partda grupal da 50 puntos por coincidencia"<<std::endl;
                    std::cout<<"RESOLVER (frase secreta) --> Si se resuelve, se gana la partida. Si se falla al resolver se pierde automaticamente."<<std::endl;
                    std::cout<<"SALIR -> Se sale del servidor."<<std::endl;

                }else{
                    if(strcmp(buffer,"SALIR\n") == 0){
                        fin = 1;
                    }
                
                
                send(sd,buffer,sizeof(buffer),0);
                }
            }
            
            
        }
        
        
				
    }while(fin == 0);
		
    close(sd);

}