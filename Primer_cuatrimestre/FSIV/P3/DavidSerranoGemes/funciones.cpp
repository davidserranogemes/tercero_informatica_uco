#include <cmath>

#include <iostream>
#include "funciones.hpp"
#include "Region.hpp"

struct Adyacentes{
	float dist;
	bool active;
};

int tablaCodigoUniforme(int valorLBP);


int computeLBP(const char a, const char b, const char c, const char d, const char e, const char f, const char g, const char h, const char i , bool uniform){
	int valorLBP=0;
	int vectorLBP[8];
	int valorLBPUniformed=0;

	for(int i=0;i<8;i++){
		vectorLBP[i]=0;
	}
	if(a>=i){
		vectorLBP[7]=1;
	}
	if(b>=i){
		vectorLBP[6]=1;	
	}
	if(c>=i){
		vectorLBP[5]=1;
	}
	if(d>=i){
		vectorLBP[4]=1;
	}
	if(e>=i){
		vectorLBP[3]=1;
	}
	if(f>=i){
		vectorLBP[2]=1;
	}
	if(g>=i){
		vectorLBP[1]=1;
	}
	if(h>=i){
		vectorLBP[0]=1;
	}

	for(int i=0;i<8;i++){
		if(vectorLBP[i]){
			valorLBP=valorLBP+pow(2,i);
		}
	}

	if(uniform){
		valorLBPUniformed=tablaCodigoUniforme(valorLBP);
		return valorLBPUniformed;
	}else{
		return valorLBP;
	}
}



cv::Mat computeLBPImage(const cv::Mat& img, bool uniform){
	cv::Mat LBPImage(img.rows, img.cols, CV_8UC1);
	for(int j=0;j<LBPImage.cols;j++){
		for(int k=0;k<LBPImage.rows;k++){
			LBPImage.at<uchar>(k,j)=0;
		}
	}

	for(int j=1;j<LBPImage.cols-1;j++){
		for(int k=1;k<LBPImage.rows-1;k++){
			LBPImage.at<uchar>(k,j)=computeLBP(img.at<uchar>(k-1,j-1),(int)img.at<uchar>(k-1,j),(int)img.at<uchar>(k,j+1),(int)img.at<uchar>(k,j+1),(int)img.at<uchar>(k+1,j+1),(int)img.at<uchar>(k+1,j),(int)img.at<uchar>(k+1,j-1),(int)img.at<uchar>(k,j-1),(int)img.at<uchar>(k,j),uniform);

		}
	}


	return LBPImage;
}


cv::Mat computeLBPHist(const cv::Mat& lbpImg, const cv::Rect& roi, const cv::Mat mask, bool normalize,bool LBPU){	//Prepara la imagen a tratar
	cv::Mat imgMask;

	cv::Mat imgPrepared(lbpImg,roi);
	cv::Mat hist(1, 256, CV_32F);
	bool uniformed=true;

	for(int j=0;j<256;j++){
		hist.at<float>(j)=0;
	}
	int razon=0;
	float accumm=0;
	for(int j=0;j<imgPrepared.cols;j++){
		for(int k=0;k<imgPrepared.rows;k++){
			hist.at<float>((int)imgPrepared.at<uchar>(k,j))=hist.at<float>((int)imgPrepared.at<uchar>(k,j))+1;
			razon++;

		}
	}
	
	if(LBPU){
		cv::Mat histUniformed(1, 59, CV_32F);
		for(int j=0;j<59;j++){
			histUniformed.at<float>(j)=hist.at<float>(j);
		}

		if(normalize){
			for(int j=0;j<59;j++){
			
				histUniformed.at<float>(j)=histUniformed.at<float>(j)/razon;
				accumm=accumm+histUniformed.at<float>(j);
			}
		}
		return histUniformed;


	}else{

		if(normalize){
			for(int j=0;j<256;j++){

				hist.at<float>(j)=hist.at<float>(j)/razon;
				accumm=accumm+hist.at<float>(j);
			}
		}
		return hist;

	}

}


float computeHistogramDistance(const cv::Mat& h1, const cv::Mat& h2){
	double result=cv::compareHist(h1,h2,CV_COMP_CHISQR);
	return result;
}



std::vector<Region> splitRegion(const Region& r){
	std::vector<Region> splitted;
	
	cv::Rect insert;
	cv::Rect rectAux=r.rects()[0];
	int rectsX,rectsWid,rectsY,rectsHei;

	rectsX=rectAux.x;
	rectsY=rectAux.y;
	rectsWid=rectAux.width;
	rectsHei=rectAux.height;

	insert.x=rectsX;
	insert.y=rectsY;
	insert.width=rectsWid/2;
	insert.height=rectsHei/2;
	cv::Mat mask;
	Region reg1(insert,mask);
	splitted.push_back(reg1);

	insert.x=rectsX;
	insert.y=(rectsHei/2)+rectsY;

	if(rectsHei%2==0){
		insert.height=rectsHei/2;//
	}else{
		insert.height=rectsHei/2 +1;//
	}
	insert.width=rectsWid/2;//

	Region reg2(insert,mask);
	splitted.push_back(reg2);



	
	insert.x=(rectsWid/2)+rectsX;
	insert.y=rectsY;

	if(rectsWid%2==0){
		insert.width=rectsWid/2;//
	}else{
		insert.width=rectsWid/2 +1;//
	}
	insert.height=rectsHei/2;
	Region reg3(insert,mask);
	splitted.push_back(reg3);



	insert.x=(rectsWid/2)+rectsX;
	insert.y=(rectsHei/2)+rectsY;
	if(rectsWid%2==0){
		insert.width=rectsWid/2;//
	}else{
		insert.width=rectsWid/2 +1;//

	}
	if(rectsHei%2==0){
		insert.height=rectsHei/2;//
	}else{
		insert.height=rectsHei/2 +1;//

	}

	Region reg4(insert,mask);
	splitted.push_back(reg4);	
	
	return splitted;
}


float computeSplitCoeff(const std::vector<Region>& rs){
	float ratio;
	float dist;
	float max;
	float min;
	dist=computeHistogramDistance(rs[0].hist(),rs[1].hist());

	max=dist;
	min=dist;
	for(int i=0;i<3;i++){
		for(int j=i+1;j<4;j++){
			dist=computeHistogramDistance(rs[i].hist(),rs[j].hist());
			if(dist>max){
				max=dist;
			}else{
				if(dist<min){
					min=dist;
				}
			}

		}
	}
	ratio=max/min;
	return ratio;
}


float computeMICoeff(const Region& r1, const Region& r2){
	float dist=computeHistogramDistance(r1.hist(),r2.hist());

	if(r1.size()<r2.size()){
		return r1.size()*dist;
	}else{
		return r2.size()*dist;
	}
}


float findNextRegionsToMerge (const std::vector<Region>& regions, int& r1, int& r2){
	float minDist=9999999999;
	float auxDist;
	for(int i=0;i<regions.size();i++){
		for(int j=0;j<regions.size();j++){
			auxDist=computeMICoeff(regions[i],regions[j]);
			if(auxDist<minDist){
				r1=i;
				r2=j;
			}
		}
	}
	return minDist;
}

void fillRegion(const Region& r, cv::Mat &img,int valueEtiqueta){
	std::vector<cv::Rect> auxRects=r.rects();
	int x,y,h,w;
	for(int i=0;i<auxRects.size();i++){
		x=auxRects[i].x;
		y=auxRects[i].y;
		h=auxRects[i].height;
		w=auxRects[i].width;
		
		for(int j=x;j<x+w;j++){
			for(int k=y;k<y+h;k++){
				img.at<uchar>(k,j)=valueEtiqueta;
			}
		}
	}
}

cv::Mat generatelSegmentedImage(const cv::Size& imageSize, const std::vector<Region>& regs){
	cv::Mat segmentedImage(imageSize,CV_8UC1);//No se puede usar CV_16I, CV_16U falla dejando la mitad de la pantalla en negro, provisionalmente uso CV_8UC1

	for(int i=0;i<regs.size();i++){
		fillRegion(regs[i],segmentedImage,(i*3)%255);//Posible soluciona no tener mas de 255 etiquetas, evita que se pongan al final varias etiquetas con el mismo valor
	}
	return segmentedImage;
}


cv::Mat getBorders (const cv::Mat segImg){
	cv::Mat borderImg(segImg.rows,segImg.cols,CV_8UC1);

	for(int j=1;j<borderImg.cols-1;j++){
		for(int k=1;k<borderImg.rows-1;k++){
			if(segImg.at<uchar>(k,j)!=segImg.at<uchar>(k+1,j+1) or segImg.at<uchar>(k,j)!=segImg.at<uchar>(k+1,j) or segImg.at<uchar>(k,j)!=segImg.at<uchar>(k+1,j-1) or segImg.at<uchar>(k,j)!=segImg.at<uchar>(k,j+1) or segImg.at<uchar>(k,j)!=segImg.at<uchar>(k,j-1) or segImg.at<uchar>(k,j)!=segImg.at<uchar>(k-1,j+1) or segImg.at<uchar>(k,j)!=segImg.at<uchar>(k-1,j) or segImg.at<uchar>(k,j)!=segImg.at<uchar>(k-1,j-1)){
				//Es frontera
				borderImg.at<uchar>(k,j)=255;
			}else{
				borderImg.at<uchar>(k,j)=0;
			}
		}
	}

	return borderImg;
}


void split(const cv::Mat& lbpImg, float sTh, float minSize, std::vector<Region>& regions, bool LBPU){
	std::vector<Region> pila;
	cv::Rect rectAux(0,0,lbpImg.cols,lbpImg.rows);
	cv::Mat hist(1,256,CV_8UC1);
	Region regAux(rectAux,hist);
	pila.push_back(regAux);

	float coefSplit;
	cv::Mat auxMat;

	cv::Mat hist1, hist2, hist3, hist4;
	cv::Mat lbp;
	cv::Mat mask;

	cv::Mat border;
	std::vector<Region> auxRegVec;
	lbp=computeLBPImage(lbpImg,LBPU);
	std::cout<<"Mostrando imagen LBP, pulse enter para continuar."<<std::endl;
	cv::imshow("LBP",lbp);
	cv::waitKey(0);
	do{

		auxRegVec=splitRegion(pila.back());

		hist1=computeLBPHist(lbp,auxRegVec[0].rects()[0],mask,true,LBPU);
		auxRegVec[0].setHist(hist1);
		hist2=computeLBPHist(lbp,auxRegVec[1].rects()[0],mask,true,LBPU);
		auxRegVec[1].setHist(hist2);
		hist3=computeLBPHist(lbp,auxRegVec[2].rects()[0],mask,true,LBPU);
		auxRegVec[2].setHist(hist3);
		hist4=computeLBPHist(lbp,auxRegVec[3].rects()[0],mask,true,LBPU);
		auxRegVec[3].setHist(hist4);


		coefSplit=computeSplitCoeff(auxRegVec);
		if(coefSplit>sTh){
			if(pila.back().size()>minSize){
				pila.pop_back();

				for(int i=0;i<auxRegVec.size();i++){
					pila.push_back(auxRegVec[i]);
				}
			}else{
				regions.push_back(pila.back());
				pila.pop_back();


			}
		}else{
			//Es Homogeneo
			regions.push_back(pila.back());
			pila.pop_back();

		}
	}while(!pila.empty());
}


void merge(std::vector<Region>& regions, float miTh, unsigned minIters,float sTh){

	float ratioSalida;
	int currIter=0;
	float MI_cur=0,MI_max=0,MI_min;
	std::vector<std::vector<Adyacentes>> Adyacent;
	bool adyacentBoolean=false;
	bool salir=false;
	bool checker=true;

	int itI, itJ;

	Adyacent.resize(regions.size());
	for(int i=0;i<regions.size();i++){
		Adyacent[i].resize(regions.size());
	}

	for(int i=0;i<regions.size();i++){	
		for(int j=i+1;j<regions.size();j++){
			Adyacent[i][j].dist=999999999;
			Adyacent[i][j].active=true;

		}
	}


//Busqueda de adyacencias
	MI_max=0.01;
	std::vector<Region>::iterator it;
	std::cout<<"Inicio del proceso merge, se puede demorar."<<std::endl;
	int counterInactive=0;
	cv::Mat border;
	do{

		itI=-1;
		itJ=-1;

		MI_max;
		MI_cur=0;
		MI_min=99999999999;
		currIter++;
		
		for(uint i=0; i<regions.size();i++){
			for(uint j=i+1;j<regions.size();j++){
				adyacentBoolean=regions[i].areAdjacents(regions[j]);
				if(adyacentBoolean){
				//if(true){
					MI_cur=computeMICoeff(regions[i],regions[j]);
					if(MI_cur<MI_min){
						itI=i;
						itJ=j;
						MI_min=MI_cur;
					}

				}
			}
		}
		
		
		if(itI==-1 or itJ==-1){
			salir=true;
			std::cout<<"No quedan mas regiones adyacentes, activas."<<std::endl;
		}else{
			if(esHomogenea(regions[itI],regions[itJ],sTh)){//Son homogeneas
				MI_cur=MI_min;
				
				regions[itI].merge(regions[itJ]);
				int x;
				for(it=regions.begin(),x=0;it!=regions.end();x++,it++){
					if(x==itJ){
						std::cout<<"ItI: "<<itI<<" ITJ: "<<itJ<<std::endl;
						std::cout<<"Borramos la region "<<itJ<<" Quedan "<<regions.size()<<" regiones"<<std::endl;
						regions.erase(it);
						break;
					}
				}
			}else{
				salir=true;
			}

		if(MI_cur!=0 and checker){
			MI_max=MI_cur;
			checker=false;
		}
		ratioSalida=MI_cur/MI_max;

		std::cout<<"MI_cur: "<<MI_cur<<" MI_max: "<<MI_max<<" MI_min: "<<MI_min<<std::endl;
		std::cout<<"ratioSalida: "<<ratioSalida<<" miTh: "<<miTh<<" Curr iter: "<<currIter<<std::endl<<std::endl;


		if(MI_cur>MI_max){
			MI_max=MI_cur;
		}
	}
		


	}while((ratioSalida<=miTh or minIters>currIter) and !salir);
	if(salir){
		std::cout<<"Se salio porque no quedan imagenes homogeneas."<<std::endl;

	}
}


bool esHomogenea(const Region& r1, const Region& r2,float sTh){
	float dist=computeHistogramDistance(r1.hist(),r2.hist());
	std::cout<<"dist: "<<dist<<" sTh: "<<sTh<<std::endl; 
	if(dist>sTh){//No son homogeneas
		return false;
	}else{
		return true;
	}
}

int tablaCodigoUniforme(int valorLBP){
	int valorLBPUniformed=-1;
	switch(valorLBP){//Los case son el resultado de evaluar el valor del vector de los patrones aceptados
			case 0:
				valorLBPUniformed=0;
				break;
			case 16:
				valorLBPUniformed=1;
				break;
		
			case 8:
				valorLBPUniformed=2;
				break;
			
			case 4:
				valorLBPUniformed=3;
				break;
			
			case 2:
				valorLBPUniformed=4;
				break;
			
			case 1:
				valorLBPUniformed=5;
				break;
			
			case 128:
				valorLBPUniformed=6;
				break;
			
			case 64:
				valorLBPUniformed=7;
				break;
			
			case 32:
				valorLBPUniformed=8;
				break;
			
			case 24:
				valorLBPUniformed=9;
				break;
			
			case 12:
				valorLBPUniformed=10;
				break;
			
			case 6:
				valorLBPUniformed=11;
				break;
			
			case 3:
				valorLBPUniformed=12;
				break;
			
			case 129:
				valorLBPUniformed=13;
				break;
			
			case 192:
				valorLBPUniformed=14;
				break;
			
			case 96:
				valorLBPUniformed=15;
				break;
			
			case 48:
				valorLBPUniformed=16;
				break;
			
			case 56:
				valorLBPUniformed=17;
				break;
			
			case 28:
				valorLBPUniformed=18;
				break;
			
			case 14:
				valorLBPUniformed=19;
				break;
			
			case 7:
				valorLBPUniformed=20;
				break;
			
			case 131:
				valorLBPUniformed=21;
				break;
			
			case 193:
				valorLBPUniformed=22;
				break;
			
			case 224:
				valorLBPUniformed=23;
				break;
			
			case 112:
				valorLBPUniformed=24;
				break;
			
			case 60:
				valorLBPUniformed=25;
				break;
			
			case 30:
				valorLBPUniformed=26;
				break;
			
			case 15:
				valorLBPUniformed=27;
				break;
			
			case 135:
				valorLBPUniformed=28;
				break;
			
			case 195:
				valorLBPUniformed=29;
				break;
			
			case 225:
				valorLBPUniformed=30;
				break;
			
			case 240:
				valorLBPUniformed=31;
				break;
			
			case 120:
				valorLBPUniformed=32;
				break;
			
			case 124:
				valorLBPUniformed=33;
				break;
			
			case 62:
				valorLBPUniformed=34;
				break;
			
			case 31:
				valorLBPUniformed=35;
				break;
			
			case 143:
				valorLBPUniformed=36;
				break;
			
			case 199:
				valorLBPUniformed=37;
				break;
			
			case 227:
				valorLBPUniformed=38;
				break;
			
			case 241:
				valorLBPUniformed=39;
				break;
			
			case 248:
				valorLBPUniformed=40;
				break;
			
			case 126:
				valorLBPUniformed=41;
				break;
			
			case 63:
				valorLBPUniformed=42;
				break;
			
			case 159:
				valorLBPUniformed=43;
				break;
			
			case 207:
				valorLBPUniformed=44;
				break;
			
			case 231:
				valorLBPUniformed=45;
				break;
			
			case 243:
				valorLBPUniformed=46;
				break;
			
			case 249:
				valorLBPUniformed=47;
				break;
			
			case 252:
				valorLBPUniformed=48;
				break;
			
			case 254:
				valorLBPUniformed=49;
				break;
			
			case 127:
				valorLBPUniformed=50;
				break;
			
			case 191:
				valorLBPUniformed=51;
				break;
			
			case 223:
				valorLBPUniformed=52;
				break;
			
			case 239:
				valorLBPUniformed=53;
				break;
			
			case 247:
				valorLBPUniformed=54;
				break;
			
			case 251:
				valorLBPUniformed=55;
				break;
			
			case 253:
				valorLBPUniformed=56;
				break;
			
			case 255:
				valorLBPUniformed=57;
				break;
			
			default:
				valorLBPUniformed=58;
				break;
		}
		return valorLBPUniformed;
}