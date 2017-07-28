#ifndef SERVERFUNCTION_HPP
#define SERVERFUNCTION_HPP

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <vector>
#include <unistd.h>

#include "ruleta_suerte.hpp"
#include "constant.hpp"

bool closeServer(std::vector<int> userDescriptor,int sd,fd_set *readfds,ruleta_suerte &ruleta);
bool salirCliente(int socket, fd_set * readfds, int  &numClientes, std::vector<int> &userDescriptor);

#endif