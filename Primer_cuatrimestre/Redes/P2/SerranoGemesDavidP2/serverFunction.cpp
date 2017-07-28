#include "serverFunction.hpp"
#include <iostream>

bool closeServer(std::vector<int> userDescriptor,int sd,fd_set *readfds,ruleta_suerte &ruleta){
	char buffer[MSG_SIZE];
 	bzero(buffer,sizeof(buffer));
 	sprintf(buffer,"+Ok. Desconexion del servidor\n");

 	if(!ruleta.isFileUpdated()){
 		ruleta.savePlayers();
 	}

	for(uint j=0;j<userDescriptor.size();j++){
		send(userDescriptor[j],buffer,strlen(buffer),0);
		close(userDescriptor[j]);
		FD_CLR(userDescriptor[j], readfds);
	}
	close(sd);
	return true;
}


bool salirCliente(int socket, fd_set * readfds, int &numClientes, std::vector<int> &userDescriptor){
	char buffer[MSG_SIZE];
	int j;

	close(socket);
	FD_CLR(socket,readfds);

	for(j=0;j<numClientes-1;j++){
		if(userDescriptor[j]==socket){
			break;
		}
	}
	for(;j<numClientes-1;j++){
		userDescriptor[j]=userDescriptor[j+1];
	}
	numClientes--;

    bzero(buffer,sizeof(buffer));
    sprintf(buffer,"+Ok. Desconexión del cliente: %d\n",socket);	
    
	std::cout<<buffer<<"Usuarios: "<<numClientes<<"/"<<MAX_CLIENTS<<std::endl;

    return true;
}

