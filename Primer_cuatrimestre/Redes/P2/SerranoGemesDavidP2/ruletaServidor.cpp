#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#include <vector>
#include <iostream>
#include <list>
#include <algorithm>

#include "constant.hpp"
#include "serverFunction.hpp"
#include "ruleta_suerte.hpp"
#include "partida_ruleta.hpp"

void manejador(int signum);


int main(){

	ruleta_suerte ruleta;
	std::list<partida_ruleta> listaPartidas;

	bool BAD_MSG=false;

	int sd, new_sd;//sd recibe las peticiones, new_sd es el nuevo descriptor para cada usuario se debe meter en el vector
	std::vector<int> userDescriptor;
	struct player new_player;
	userDescriptor.resize(MAX_CLIENTS);	
	
	struct sockaddr_in sockname, from;
	char buffer[MSG_SIZE];
	socklen_t from_len;
    fd_set readfds, auxfds;
    int salida;
    int recibido;
    int numClientes = 0;
    int on, ret;

    int passCheck=-1;

    int salidaSelect;

    char REGISTRO[20];
    char user[30];
    char password[30];


    sd= socket (AF_INET,SOCK_STREAM,0);
    if(sd==-1){
    	std::cerr<<"No se puede abrir el socket para recibir clientes."<<std::endl;
    	exit(-1);
    }

    on=1;
    ret =setsockopt(sd, SOL_SOCKET,SO_REUSEADDR,&on, sizeof(on));

    sockname.sin_family =AF_INET;
    sockname.sin_port =htons(PORT);
    sockname.sin_addr.s_addr= INADDR_ANY;

    if(bind (sd,(struct sockaddr *) &sockname, sizeof(sockname)) == -1){
    	std::cerr<<"Error en la operacion bind"<<std::endl;
    	exit(-1);
    }

    from_len = sizeof(from);

    if(listen(sd,1) == -1){
    	std::cerr<<"Error en la operacion de listen"<<std::endl;
    	exit(-1);
    }
    
    FD_ZERO(&readfds);
    FD_ZERO(&auxfds);
    FD_SET(sd,&readfds);
    FD_SET(0,&readfds);//escucha el teclado

    signal(SIGINT,manejador);

    if(!ruleta.loadPlayers()){
    	std::cout<<"No existe el fichero registredPlayers.txt"<<std::endl;
    }else{
    	std::cout<<"Jugadores registrados cargados con exito."<<std::endl;
    }

    while(1){
    	BAD_MSG=true;
    	auxfds=readfds;

    	salidaSelect=select(FD_SETSIZE,&auxfds,NULL,NULL,NULL);

		if(salidaSelect>0){

			for(int i=0;i<FD_SETSIZE;i++){
				if(FD_ISSET(i,&auxfds)){//¿Que socket ha abierto?

					if(i==sd){//Nueva conexion, manejar nueva conexion
						std::cout<<"Nueva conexion: "<<std::endl;
						 if((new_sd = accept(sd, (struct sockaddr *)&from, &from_len)) == -1){
                              std::cerr<<"Error con el manejo de peticiones"<<std::endl;
                        }else{
                        	if(numClientes<MAX_CLIENTS){
                        		userDescriptor[numClientes]=new_sd;
                        		numClientes++;
                        		FD_SET(new_sd,&readfds);

								bzero(buffer,sizeof(buffer));

                        		strcpy(buffer, "+Ok. Usuario conectado\n");

                        		send(new_sd,buffer,strlen(buffer),0);
                        		std::cout<<buffer<<"Usuarios: "<<numClientes<<"/"<<MAX_CLIENTS<<std::endl;

                        		//Este bucle avisa a todos los usuarios, por ejemplo se podria poner un control para no avisar a quien este en partida
                        		/*
                        		for(int j=0; j<numClientes-1;j++){
	                                bzero(buffer,sizeof(buffer));
	                                sprintf(buffer,"Nuevo usuario conectado.");
	                                send(userDescriptor.[j].sd,buffer,strlen(buffer),0);

                        		}
                        		*/

                        	}else{
                        		bzero(buffer,sizeof(buffer));
                        		sprintf(buffer,"-Err. Demasiados clientes conectados, intentelo mas tarde.\n");
                        		send(new_sd,buffer,strlen(buffer),0);
                        		close(new_sd);
                        	}
                        }

					}else{
						if( i==0){//Mensaje del servidor, por teclado
							std::cout<<"+Ok. Mensaje recibido por teclado: "<<std::endl;
							bzero(buffer,sizeof(buffer));
							fgets(buffer,sizeof(buffer),stdin);

							if(strcmp(buffer,"SALIR\n") == 0){
								//Funcion cerrar servidor
								closeServer(userDescriptor,sd, &auxfds,ruleta);
								exit(-1);
							}else{
								std::cout<<"-Err. Mensaje no reconocido del servidor: "<<buffer<<std::endl;
							}

						}else{//Mensaje recibido de un usuario ya conectado
							//Detectar qué usuario ha mandado el mensaje
							//Comprobar si esta registrado y logueado
							//Permitir que se registre/loguee
							//Inscripcion a una partida
							//Turno partida, controlar turno

							bzero(buffer,sizeof(buffer));

							recibido=recv(i,buffer,sizeof(buffer),0);

							if(recibido>0){
								//Comparadciones multiples segun todo lo quye puede hacer, por ahora solo mostrar para testear
								std::cout<<"+Ok. Mensaje recibido: "<<buffer<<std::endl;
							
								if((strcmp(buffer,"SALIR\n"))==0){
									BAD_MSG=false;
									bzero(buffer,sizeof(buffer));
									strcpy(buffer,"+Ok. Ha salido del servidor.\n");
									send(i,buffer,strlen(buffer),0);

									list<partida_ruleta>::iterator it;
									for(it=listaPartidas.begin();it!=listaPartidas.end();it++){
										if(it->isInThisGame(i)){
											if(!it->delJugador(i)){
												std::cout<<"+Ok. Partida vacia y eliminada."<<std::endl;
												listaPartidas.erase(it);
												break;
											}else{
												std::vector<int> auxVector=it->getJugadores();

											//	if(it->getTurn()==i){
										//			it->turnPlus();
										//		}
												for(int r=0;r<it->getTam();r++){
													if(it->partidaStarted()){
														bzero(buffer,sizeof(buffer));
														sprintf(buffer,"-Ok. Un jugador se ha desconectado, quedan %d jugadores.\n Turno de: %s\n",it->getTam(),ruleta.getUserName(it->getTurn()).c_str());
														send(auxVector[r],buffer,strlen(buffer),0);	
													}else{
														bzero(buffer,sizeof(buffer));
														sprintf(buffer,"-Ok. Un jugador se ha desconectado, esperando %d jugadores.\n",3-it->getTam());
														send(auxVector[r],buffer,strlen(buffer),0);	
													}
													//si solo queda un jugador permitirle salir de la partida eligiendo la opcion
													if(it->getTam()==1){
														bzero(buffer,sizeof(buffer));
														sprintf(buffer,"+Ok. Solo queda usted, puede continuar solo o salir.");
														send(auxVector[r],buffer,strlen(buffer),0);	
													}
												}
												break;
											}

										}else{
											std::cout<<"+Ok. El cliente no estaba en partida."<<std::endl;
										}
									}
									ruleta.intentoZero(i);
									ruleta.zeroPuntos(i);
									
									ruleta.logoutUser(i);

									salirCliente(i,&readfds,numClientes,userDescriptor);

								}

								if((strncmp(buffer,"REGISTRO",8))==0){
									BAD_MSG=false;									
									bzero(user,sizeof(user));
									bzero(REGISTRO,sizeof(REGISTRO));
									bzero(password,sizeof(password));

									if((sscanf(buffer,"%s -u %s -p %s",REGISTRO,user,password))==3){
									//	std::cout<<"USUARIO: "<<user<<" PASS: "<<password<<std::endl;
										new_player.userName=user;
										new_player.password=password;
										//new_player.sd=i;

										if(!ruleta.addPlayers(new_player)){
											bzero(buffer,sizeof(buffer));
											strcpy(buffer,"-Err. Nombre de usuario en uso.\n");
											send(i,buffer,strlen(buffer),0);
										}else{
											//Tratamiento
											bzero(buffer,sizeof(buffer));
											strcpy(buffer,"+Ok. Registro completado. Puede hacer login.\n");
											send(i,buffer,strlen(buffer),0);											
										}

									}else{
										bzero(buffer,sizeof(buffer));
										strcpy(buffer,"-Err. Formato erroneo.\n");
										send(i,buffer,strlen(buffer),0);
									}
								}

								if((strncmp(buffer,"USUARIO",7))==0){
									BAD_MSG=false;
									bzero(user,sizeof(user));
									bzero(REGISTRO,sizeof(REGISTRO));
									bzero(password,sizeof(password));

									if(ruleta.isLoged(i)){
										bzero(buffer,sizeof(buffer));
										sprintf(buffer,"-Err. Ya se ha logeado.\n");
										send(i,buffer,strlen(buffer),0);	
									}else{

										if((sscanf(buffer,"%s %s",REGISTRO,user))==2){


											passCheck=ruleta.linkLogin(i,user);

											switch(passCheck){
												case 0:
													bzero(buffer,sizeof(buffer));
													strcpy(buffer,"+Ok. Usuario valido. Introduzca contraseña.\n");
													send(i,buffer,strlen(buffer),0);
													break;
												case 1:
													bzero(buffer,sizeof(buffer));
													strcpy(buffer,"-Err. No existe el usuario, registrese primero.\n");
													send(i,buffer,strlen(buffer),0);

													break;
												case 2:
													bzero(buffer,sizeof(buffer));
													strcpy(buffer,"-Err. Usuario ya logeado.\n");
													send(i,buffer,strlen(buffer),0);											
													break;
											}
										}else{
                                       	    bzero(buffer,sizeof(buffer));
                                            strcpy(buffer,"-Err. Mal formato de comando.\n");
                                            send(i,buffer,strlen(buffer),0); 
										}
									}
								}

								if((strncmp(buffer,"PASSWORD",8))==0){
									BAD_MSG=false;
									bzero(user,sizeof(user));
									bzero(REGISTRO,sizeof(REGISTRO));
									bzero(password,sizeof(password));

									if(ruleta.isLoged(i)){
										bzero(buffer,sizeof(buffer));
										sprintf(buffer,"-Err. Ya se ha logeado.\n");
										send(i,buffer,strlen(buffer),0);	
									}else{

										if((sscanf(buffer,"%s %s",REGISTRO,password))==2){

											passCheck=ruleta.checkPassword(i,password);

											switch(passCheck){
												case 0:
													bzero(buffer,sizeof(buffer));
													strcpy(buffer,"+Ok. Validacion correcta. Ya puede jugar.\n");
													send(i,buffer,strlen(buffer),0);
													break;
												case 1:

													bzero(buffer,sizeof(buffer));
													strcpy(buffer,"Err. No ha introducido ningun username.\n");
													send(i,buffer,strlen(buffer),0);
											
													break;
												case 2:
													bzero(buffer,sizeof(buffer));
													strcpy(buffer,"Err. La contraseña no coincide Reintroduzca los datos.\n");
													send(i,buffer,strlen(buffer),0);							
													break;
											}
										}else{
											bzero(buffer,sizeof(buffer));
                                        	strcpy(buffer,"-Err. Mal formato de comando.\n");
                                            send(i,buffer,strlen(buffer),0); 
										}
									}
								}

								//SIGUIENTE ORDEN
								//PARTIDA-INDIVIDUAL

								if((strcmp(buffer,"PARTIDA_INDIVIDUAL\n"))==0){
									BAD_MSG=false;
									if(!ruleta.isLoged(i)){
										bzero(buffer,sizeof(buffer));
										sprintf(buffer,"-Err. Debe logearse para jugar.\n");
										send(i,buffer,strlen(buffer),0);
									}else{
										if(!ruleta.isInGame(i)){
												partida_ruleta new_partida(true);
												new_partida.addJugador(i);
												listaPartidas.push_back(new_partida);
												ruleta.actualizarIngame(i);

												std::string panel;
												panel=new_partida.getPanelOculto();

												bzero(buffer,sizeof(buffer));	
												strcpy(buffer,"+Ok. Creada nueva partida individual. Ya puede jugar\n");
												send(i,buffer,strlen(buffer),0);

												bzero(buffer,sizeof(buffer));	
												sprintf(buffer,"Ok. Panel: %s\n",panel.c_str());
												send(i,buffer,strlen(buffer),0);
										}else{
												bzero(buffer,sizeof(buffer));	
												strcpy(buffer,"-Err. Ya se encuentra en partida.\n");
												send(i,buffer,strlen(buffer),0);
										}
									}



								}


								//PARTIDA GRUPO

								if((strcmp(buffer,"PARTIDA_GRUPO\n"))==0){
									BAD_MSG=false;
									if(!ruleta.isLoged(i)){
										bzero(buffer,sizeof(buffer));
										sprintf(buffer,"-Err. Debe logearse para jugar.\n");
										send(i,buffer,strlen(buffer),0);	
									}else{


										if(!ruleta.isInGame(i)){
											bool inGame=false;
											list<partida_ruleta>::iterator it;
											for(it=listaPartidas.begin();it!=listaPartidas.end();it++){
												if(it->addJugador(i)){
													inGame=true;
												
													bzero(buffer,sizeof(buffer));
													strcpy(buffer,"+Ok. Ha ingresado en una partida.\n");
													send(i,buffer,strlen(buffer),0);	

													std::vector<int> jugadoresPartida=it->getJugadores();
													std::string panel;
													panel=it->getPanelOculto();
													if(it->partidaStarted()){
														for(uint r=0;r<jugadoresPartida.size();r++){
															ruleta.actualizarIngame((it->getJugadores())[r]);

															bzero(buffer,sizeof(buffer));
															sprintf(buffer,"+Ok. Sala completa, comienza la partida. Es el %dº en jugar\n",r+1);
															send(jugadoresPartida[r],buffer,strlen(buffer),0);	
															
															bzero(buffer,sizeof(buffer));
															sprintf(buffer,"Ok. Panel: %s\nTurno para: %s",panel.c_str(),ruleta.getUserName(it->getTurn()).c_str());
															send((it->getJugadores())[r],buffer,strlen(buffer),0);

														}

													}else{
														for(uint r=0;r<jugadoresPartida.size();r++){
															if(jugadoresPartida[r]!=i){
																bzero(buffer,sizeof(buffer));
																strcpy(buffer,"+Ok. Usuario añadido a la sala.\n");
																send(jugadoresPartida[r],buffer,strlen(buffer),0);	
															}
														}													
													}
													break;
												}
											}
											if(!inGame){
												partida_ruleta new_partida(false);
												new_partida.addJugador(i);
												listaPartidas.push_back(new_partida);
												//ruleta.actualizarIngame(i);

												bzero(buffer,sizeof(buffer));	
												strcpy(buffer,"+Ok. Creada nueva partida, esperando jugadores.\n");
												send(i,buffer,strlen(buffer),0);												

											}
										}else{
											bzero(buffer,sizeof(buffer));
											strcpy(buffer,"Err. Ya está en partida.\n");
											send(i,buffer,strlen(buffer),0);							
										}
									}
								}

								//CONSONANTE
								if((strncmp(buffer,"CONSONANTE",10))==0){
									BAD_MSG=false;
									char consonante;
									bzero(REGISTRO,sizeof(REGISTRO));
									

									if((sscanf(buffer,"%s %c",REGISTRO,&consonante))==2){
										if(ruleta.isInGame(i)){
											list<partida_ruleta>::iterator it;
											for(it=listaPartidas.begin();it!=listaPartidas.end();it++){
												if(it->isInThisGame(i)){
													if(it->checkTurn(i)){
														if(consonante!='a' and consonante!='e' and consonante!='i' and consonante!='o' and consonante!='u'){
															int numCoincidencias;
															numCoincidencias=it->isLetra(consonante);
															std::string panel;
															panel=it->getPanelOculto();

															if(numCoincidencias>0){
																bzero(buffer,sizeof(buffer));
																strcpy(buffer,"+Ok. La consonante existe.\n");
																send(i,buffer,strlen(buffer),0);

																//Tratamiento puntos
																if((it->getJugadores()).size()==3){
																	ruleta.sumaPuntos(i,CONS_VAL,numCoincidencias);
																}else{
																	ruleta.intentoPlus(i);
																}

															}else{
																if(numCoincidencias==0){
																	ruleta.intentoPlus(i);

																	bzero(buffer,sizeof(buffer));
																	strcpy(buffer,"+Ok. La consonante no existe. \n");
																	send(i,buffer,strlen(buffer),0);
																}else{
																	ruleta.intentoPlus(i);
									
																	bzero(buffer,sizeof(buffer));
																	strcpy(buffer,"+Ok. La consonante ya se uso. \n");
																	send(i,buffer,strlen(buffer),0);
																}
															}
													
															for(int r=0; r<it->getTam();r++){
																bzero(buffer,sizeof(buffer));
																sprintf(buffer,"+Ok. Panel: %s\nTurno para: %s\n",panel.c_str(),ruleta.getUserName(it->getTurn()).c_str());
																send((it->getJugadores())[r],buffer,strlen(buffer),0);

																if((it->getJugadores()).size()==3){
																	bzero(buffer,sizeof(buffer));
																	sprintf(buffer,"+Ok. Puntos: %i",ruleta.getPuntos(it->getJugadores()[r]));
																	send((it->getJugadores())[r],buffer,strlen(buffer),0);
																}else{
																	bzero(buffer,sizeof(buffer));
																	sprintf(buffer,"+Ok. Intentos: %i",ruleta.getIntentos(it->getJugadores()[r]));
																	send((it->getJugadores())[r],buffer,strlen(buffer),0);																	
																}
															}
														}else{
															bzero(buffer,sizeof(buffer));
															strcpy(buffer,"-Err. CONSONANTE solo admite consonantes #kappa.\n");
															send(i,buffer,strlen(buffer),0);
														}
													}else{//No es tu turno
														bzero(buffer,sizeof(buffer));
														sprintf(buffer,"-Err. No es su turno. Turno de %s",ruleta.getUserName(it->getTurn()).c_str());
														send(i,buffer,strlen(buffer),0);
													}
													break;
												}
											}
										}else{
											bzero(buffer,sizeof(buffer));
											strcpy(buffer,"-Err. La partida no ha empezado todavia.\n");
											send(i,buffer,strlen(buffer),0);
										}

									}

								}
								//VOCAL

                                if((strncmp(buffer,"VOCAL",5))==0){
                                    BAD_MSG=false;
                                    char vocal;
                                    bzero(REGISTRO,sizeof(REGISTRO));
                                    

                                    if((sscanf(buffer,"%s %c",REGISTRO,&vocal))==2){
                                        if(ruleta.isInGame(i)){
                                            list<partida_ruleta>::iterator it;
                                            for(it=listaPartidas.begin();it!=listaPartidas.end();it++){
                                                if(it->isInThisGame(i)){
                                                    if(it->checkTurn(i)){
                                                        if(ruleta.getPuntos(i)<VOCAL_VAL and (it->getJugadores()).size()==3){
                                                            bzero(buffer,sizeof(buffer));
                                                            strcpy(buffer,"-Err. No tiene suficientes puntos para pedir vocal. \n");
                                                            send(i,buffer,strlen(buffer),0);
                                                        }else{
                                                            if(vocal=='a' or vocal=='e' or vocal=='i' or vocal=='o' or vocal=='u'){
                                                                int numCoincidencias;
                                                                numCoincidencias=it->isLetra(vocal);
                                                                std::string panel;
                                                                panel=it->getPanelOculto();

                                                                if(numCoincidencias>0){
                                                                    bzero(buffer,sizeof(buffer));
                                                                    strcpy(buffer,"+Ok. La vocal existe.\n");
                                                                    send(i,buffer,strlen(buffer),0);

                                                                //Tratamiento puntos
                                                                   if((it->getJugadores()).size()==3){
                                                                        ruleta.restaPuntos(i,1,VOCAL_VAL);
                                                                    }else{

                                                                        ruleta.intentoPlus(i);
                                                                    }

                                                                }else{
                                                                    if(numCoincidencias==0){
                                                                        if((it->getJugadores()).size()==3){
                                                                            ruleta.restaPuntos(i,1,VOCAL_VAL);
                                                                        }
                                                                        ruleta.intentoPlus(i);

                                                                        bzero(buffer,sizeof(buffer));
                                                                        strcpy(buffer,"+Ok. La vocal no existe. \n");
                                                                        send(i,buffer,strlen(buffer),0);
                                                                    }else{
                                                                        ruleta.intentoPlus(i);
                                    
                                                                        bzero(buffer,sizeof(buffer));
                                                                        strcpy(buffer,"+Ok. La vocal ya se uso. \n");
                                                                        send(i,buffer,strlen(buffer),0);
                                                                    }
                                                                }
                                                    
                                                                for(int r=0; r<it->getTam();r++){
                                                                    bzero(buffer,sizeof(buffer));
                                                                    sprintf(buffer,"+Ok. Panel: %s\nTurno para: %s\n",panel.c_str(),ruleta.getUserName(it->getTurn()).c_str());
                                                                    send((it->getJugadores())[r],buffer,strlen(buffer),0);

                                                                    if((it->getJugadores()).size()==3){
                                                                        bzero(buffer,sizeof(buffer));
                                                                        sprintf(buffer,"+Ok. Puntos: %i",ruleta.getPuntos(it->getJugadores()[r]));
                                                                        send((it->getJugadores())[r],buffer,strlen(buffer),0);
                                                                    }else{
                                                                        bzero(buffer,sizeof(buffer));
                                                                        sprintf(buffer,"+Ok. Intentos: %i",ruleta.getIntentos(it->getJugadores()[r]));
                                                                        send((it->getJugadores())[r],buffer,strlen(buffer),0);                                                                  
                                                                    }
                                                                }
                                                            }else{
                                                                bzero(buffer,sizeof(buffer));
                                                                strcpy(buffer,"-Err. VOCAL solo admite vocales #kappa.\n");
                                                                send(i,buffer,strlen(buffer),0);
                                                            }
                                                        }

                                                    }else{//No es tu turno
                                                        bzero(buffer,sizeof(buffer));
                                                        sprintf(buffer,"-Err. No es su turno. Turno de %s",ruleta.getUserName(it->getTurn()).c_str());
                                                        send(i,buffer,strlen(buffer),0);
                                                    }
                                                    break;
                                                }
                                            }
                                        }else{
                                            bzero(buffer,sizeof(buffer));
                                            strcpy(buffer,"-Err. La partida no ha empezado todavia.\n");
                                            send(i,buffer,strlen(buffer),0);
                                        }

                                    }

                                }
								//RESOLVER
                                if((strncmp(buffer,"RESOLVER",8))==0){
                                    BAD_MSG=false;
                                    char refran[250];
                                    bzero(REGISTRO,sizeof(REGISTRO));
                                    bzero(refran,sizeof(refran));
                                    int scan;
                                    if((scan=sscanf(buffer,"%s %[^\n]",REGISTRO,refran))==2){
										if(ruleta.isInGame(i)){
                                            list<partida_ruleta>::iterator it;
                                            for(it=listaPartidas.begin();it!=listaPartidas.end();it++){
                                                if(it->isInThisGame(i)){
                                                    if(it->checkTurn(i)){
                                                    	string auxRespuesta=refran;
                                                    	std::transform(auxRespuesta.begin(), auxRespuesta.end(), auxRespuesta.begin(), tolower);
                                                    	std::string panel;
														panel=it->getPanelResuelto();
                                                    	if(it->resolver(auxRespuesta)){//Comprobar si es correcto, si lo es gana

                                                    		for(int r=0; r<it->getTam();r++){
                                                                bzero(buffer,sizeof(buffer));
                                                                sprintf(buffer,"+Ok. Panel:%s\nGanador, por resolver el panel: %s\n",panel.c_str(),ruleta.getUserName(i).c_str());
                                                                send((it->getJugadores())[r],buffer,strlen(buffer),0);

                                                                if((it->getJugadores()).size()==3){
                                                                    bzero(buffer,sizeof(buffer));
                                                                    sprintf(buffer,"+Ok. Puntos: %i",ruleta.getPuntos(it->getJugadores()[r]));
                                                                    send((it->getJugadores())[r],buffer,strlen(buffer),0);
                                                                }else{
                                                                	int puntosInd;
                                                                	if(ruleta.getIntentos(it->getJugadores()[r])<5){
                                                                		puntosInd=150;
                                                                	}else{
                                                                		if(ruleta.getIntentos(it->getJugadores()[r])<9){
                                                                			puntosInd=100;
                                                                		}else{
                                                                			if(ruleta.getIntentos(it->getJugadores()[r])<12){
                                                                				puntosInd=70;
                                                                			}else{
                                                                				if(ruleta.getIntentos(it->getJugadores()[r])<16){
                                                                					puntosInd=50;
                                                                				}else{
                                                                					puntosInd=0;
                                                                				}
                                                                			}
                                                                		}
                                                                	}
                                                                    bzero(buffer,sizeof(buffer));
                                                                    sprintf(buffer,"+Ok. Ha necesitado %i intentos. Recibe %i puntos",ruleta.getIntentos(it->getJugadores()[r]),puntosInd);
                                                                    send((it->getJugadores())[r],buffer,strlen(buffer),0);                                                                  
                                                                }
                                                            }
                                                    	}else{//si no pierde y tiene que revisar en la partida multi quien tiene mas puntos

                                                            ruleta.zeroPuntos(i);

                                                            int auxPuntos=-1;			
                                                            int winner=-1;												
															for(uint s=0;s<it->getJugadores().size();s++){
																if(auxPuntos<ruleta.getPuntos(it->getJugadores()[s])){
																	auxPuntos=ruleta.getPuntos(it->getJugadores()[s]);
																	winner=it->getJugadores()[s];
																}
															}

															for(int r=0; r<it->getTam();r++){
                                                                bzero(buffer,sizeof(buffer));
                                                                sprintf(buffer,"+Ok. Panel:%s\n%s ha fallado al resolver el panel. ¡Queda con 0 puntos!\n",panel.c_str(),ruleta.getUserName(i).c_str());
                                                                send((it->getJugadores())[r],buffer,strlen(buffer),0);
                                                                
                                                                if((it->getJugadores()).size()==3){
                                                                	bzero(buffer,sizeof(buffer));
                                                                	sprintf(buffer,"+Ok. Gana: %s con %d puntos. \n",ruleta.getUserName(winner).c_str(),ruleta.getPuntos(winner));
                                                              		send((it->getJugadores())[r],buffer,strlen(buffer),0);
                                                                    
                                                                    bzero(buffer,sizeof(buffer));
                                                                    sprintf(buffer,"+Ok. Tenias %d puntos. ",ruleta.getPuntos(it->getJugadores()[r]));
                                                                    send((it->getJugadores())[r],buffer,strlen(buffer),0);
                                                                }else{
                                                                    bzero(buffer,sizeof(buffer));
                                                                    sprintf(buffer,"+Ok. Fallas el panel \n Intentos: %i",ruleta.getIntentos(it->getJugadores()[r]));
                                                                    send((it->getJugadores())[r],buffer,strlen(buffer),0);                                                                  
                                                                }
                                                            }
                                                    	}
													for(int r=0; r<it->getTam();r++){
														ruleta.intentoZero(it->getJugadores()[r]);
														ruleta.zeroPuntos(it->getJugadores()[r]);
														ruleta.endGameUser(it->getJugadores()[r]);

													}
													listaPartidas.erase(it);

                                                   	}else{//No es tu turno
                                                        bzero(buffer,sizeof(buffer));
                                                        sprintf(buffer,"-Err. No es su turno. Turno de %s",ruleta.getUserName(it->getTurn()).c_str());
                                                        send(i,buffer,strlen(buffer),0);
                                                    }
                                                    break;
                                                }
                                            }
                                        }else{
                                            bzero(buffer,sizeof(buffer));
                                            strcpy(buffer,"-Err. La partida no ha empezado todavia.\n");
                                            send(i,buffer,strlen(buffer),0);
                                        }
                                    }else{
                                       	    bzero(buffer,sizeof(buffer));
                                            strcpy(buffer,"-Err. Mal formato de comando.\n");
                                            send(i,buffer,strlen(buffer),0); 
                                    }

                                }

								//ERROR MSG
								if(BAD_MSG){
									bzero(buffer,sizeof(buffer));
									strcpy(buffer,"Err. Comando desconocido.\n");
									send(i,buffer,strlen(buffer),0);		
								}

							}
							if(recibido==0){//ha recibido una señal ctrl+c
								std::cout<<"+Ok. El cliente "<<i<<" ha introducido ctrl+c"<<std::endl;
								
								list<partida_ruleta>::iterator it;
									for(it=listaPartidas.begin();it!=listaPartidas.end();it++){
										if(it->isInThisGame(i)){
											if(!it->delJugador(i)){
												std::cout<<"+Ok. Partida vacia y eliminada."<<std::endl;
												listaPartidas.erase(it);
												break;
											}else{
												std::vector<int> auxVector=it->getJugadores();

												if(it->getTurn()==i){
													it->turnPlus();
												}

												for(int r=0;r<it->getTam();r++){
													if(it->partidaStarted()){
														bzero(buffer,sizeof(buffer));
														sprintf(buffer,"-Ok. Un jugador se ha desconectado, quedan %d jugadores.\n Turno de: %s",it->getTam(),ruleta.getUserName(it->getTurn()).c_str());
														send(auxVector[r],buffer,strlen(buffer),0);	
													}else{
														bzero(buffer,sizeof(buffer));
														sprintf(buffer,"-Ok. Un jugador se ha desconectado, esperando %d jugadores.\n",3-it->getTam());
														send(auxVector[r],buffer,strlen(buffer),0);	
													}
													//si solo queda un jugador permitirle salir de la partida eligiendo la opcion
													if(it->getTam()==1){
														bzero(buffer,sizeof(buffer));
														sprintf(buffer,"-Ok. Solo queda usted, puede continuar solo o salir.");
														send(auxVector[r],buffer,strlen(buffer),0);	
													}
												}
												break;
											}

										}else{
											std::cout<<"+Ok. El cliente no estaba en partida."<<std::endl;
										}
									}

								ruleta.intentoZero(i);
								ruleta.zeroPuntos(i);
								ruleta.logoutUser(i);

								salirCliente(i,&readfds,numClientes,userDescriptor);
								//Tratamiento salida del cliente
							}

						}
					}
				}
			}

		}
}    
 
}



void manejador(int signum){
	std::cout<<std::endl<<"Recibida señal: "<<signum<<std::endl<<"Para salir utilice la orden SALIR"<<std::endl;
	

}
