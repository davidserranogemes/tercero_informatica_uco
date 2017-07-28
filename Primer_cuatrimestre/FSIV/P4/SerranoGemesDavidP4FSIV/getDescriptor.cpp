#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include <string>
#include <cmath>
#include <list>
#include <fstream>
//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <cv.h>

using namespace cv;

int main(int argc,char ** argv){

	bool fflag=false;
	int fValue=10;


	int optvalue;

	while((optvalue = getopt(argc,argv,"f:"))!=-1 ){
		switch(optvalue){
			case 'f':
				fflag=true;
				fValue=atoi(optarg);
				break;
			
			case '?':
			
			if(optopt=='n'){
					std::cerr<<"La opcion "<<optopt<<" requiere un argumento"<<std::endl;
					abort();
				}else{
					if(isprint (optopt)){
						std::cerr<<"Opción desconocida '-"<<optopt<<"'"<<std::endl;
    			  		exit(-1);
    					}else{
							//std::cerr<<"Error desconocido."<<std::endl;
	            			
						}
				}
		}
		
	}

	std::string nombreFichEntrada;
	std::string nombreFichSalida;
	switch(argc){
		case 2:
			nombreFichEntrada=argv[1];
			break;
		case 3:
			nombreFichEntrada=argv[2];
			break;
		default:
			std::cout<<"Error de sintaxis, utilice ./getDescriptor [-f <int>=10] cont.txt"<<std::endl;
			exit(-1);

	}

	nombreFichSalida="descriptor_"+nombreFichEntrada;
	std::ifstream fichEntrada;
	std::ofstream fichSalida;

	fichEntrada.open(nombreFichEntrada);

	std::vector<Point2f> contour;
	std::vector<Point2f> contourConvex;
	std::vector<Point2f> fourier;
	Point auxPoint, prevPoint;

	if(fichEntrada.is_open()){

		do{
			fichEntrada>>auxPoint.x;
			fichEntrada>>auxPoint.y;
			
			if(prevPoint!=auxPoint){
				contour.push_back(auxPoint);	
			}

			prevPoint=auxPoint;
		}while(!fichEntrada.eof());

		std::cout<<"Cargados "<<contour.size()<<" puntos."<<std::endl;
		fichEntrada.close();

		double longitud=0;
		double diametro=0;
		double area=0;
		double ocupacion=0;
		double compacidad=0;
		double excentricidad=0;
		double ocupacionConvexa=0;
		double solidez=0;

		RotatedRect basicRectangle;
		Rect boundinRectangle=boundingRect(contour);

//Calculos
		
		//longitud
		longitud=arcLength(contour,true);
		
		//Area
		area=contourArea(contour,false);
		
		//Rectangulo basico
		basicRectangle=minAreaRect(contour);

		//Diametro
		for(int i=0;i<contour.size();i++){
			for(int j=i+1; j<contour.size();j++){
				double auxDist=0;
				auxDist=pow(contour[i].x-contour[j].x,2)+pow(contour[i].y-contour[j].y,2);
				auxDist=sqrt(auxDist);
				if(auxDist>diametro){
					diametro=auxDist;
				
				}
			}
		}

		//Excentricidad
		if(basicRectangle.size.height>basicRectangle.size.width){//Busco cual es el radio maximo
			excentricidad=basicRectangle.size.height/basicRectangle.size.width;
		}else{
			excentricidad=basicRectangle.size.width/basicRectangle.size.height;
		}

		//Ocupacion
		ocupacion=area/(boundinRectangle.height*boundinRectangle.width);

		//Compacidad
		compacidad=area/pow(longitud,2);

		//Ocupacion convexa
		convexHull(contour,contourConvex);
		double convexArea=contourArea(contourConvex,false);
		ocupacionConvexa=convexArea/(boundinRectangle.height*boundinRectangle.width);

		//Solidez
		solidez=area/convexArea;

		
		//Fourier
		int tamOptimo=getOptimalDFTSize(contour.size());
		//std::cout<<"Optimo: "<<tamOptimo<<std::endl;

		int lastTam=contour.size();

		contour.resize(tamOptimo);
		int k=0;
		for(int i=lastTam;i<tamOptimo;i++,k++){
			contour[i].x=contour[k].x;
			contour[i].y=contour[k].y;
		}

		dft(contour,fourier);

		std::vector<float> fourierDescriptor;
		fourierDescriptor.resize(fourier.size());
		float maxDescriptor=0;
		for(int i=0;i<fourier.size();i++){
			fourierDescriptor[i]=sqrt(pow(fourier[i].x,2)+pow(fourier[i].y,2));
			if(maxDescriptor<fourierDescriptor[i]){
				maxDescriptor=fourierDescriptor[i];
			}
		}

		for(int i=0;i<fourierDescriptor.size();i++){
			fourierDescriptor[i]=fourierDescriptor[i]/maxDescriptor;
		}

		fichSalida.open(nombreFichSalida);

		//Escritura
		/*
		Longitud.--
		Diámetro.--
		Rectángulo básico.--
		Excentricidad.--
		Área.--
		Ocupación.--
		Compacidad.--
		Ocupación convexa.--
		Solidez.--
		Los primeros n descriptores de Fourier. El valor por defecto es 10.
		*/

		fichSalida<<"Longitud: "<<longitud<<std::endl;
		fichSalida<<"Diametro: "<<diametro<<std::endl;
		fichSalida<<"Area: "<<area<<std::endl;
		fichSalida<<"Rect. basico: angulo: "<<basicRectangle.angle<<" centro: "<<"[ "<<basicRectangle.center.x<<" , "<<basicRectangle.center.y<<" ]"<<" lados: "<<basicRectangle.size<<std::endl; 
		fichSalida<<"Excentricidad: "<<excentricidad<<std::endl;

		fichSalida<<"Ocupacion: "<<ocupacion<<std::endl;
		fichSalida<<"Compacidad: "<<compacidad<<std::endl;
		fichSalida<<"Ocup. convexa: "<<ocupacionConvexa<<std::endl;
		fichSalida<<"Solidez: "<<solidez<<std::endl;
		fichSalida<<"[";
		for(int i=1;i<fValue+1;i++){
			fichSalida<<" "<<fourierDescriptor[i]<<" ";

		}
		fichSalida<<"]"<<std::endl;

		fichSalida.close();

	}else{
		std::cout<<"El fichero "<<fichEntrada<<" no existe."<<std::endl;
		exit(-1);
	}

}