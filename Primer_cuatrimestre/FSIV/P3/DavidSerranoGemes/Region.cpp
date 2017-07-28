#include "Region.hpp"

float Region::size() const{
	float sizeReg=0;
	for(int i=0;i<_rs.size();i++){
		sizeReg=sizeReg+((_rs[i].width)*(_rs[i].height));
	}
	return sizeReg;
}


const cv::Mat& Region::hist() const{
	return _hist;
}

const std::vector<cv::Rect>& Region::rects() const{
	return _rs;
}

bool Region::areAdjacents(const Region& other) const{
	bool isconected=false;
    std::vector<cv::Rect> rectangulosThis=this->rects();
    std::vector<cv::Rect> rectangulosOther=other.rects();

    int xThis, yThis, wThis, hThis;
    int xOther, yOther, wOther, hOther;

	for(int i=0;i<rectangulosThis.size();i++){
		xThis=rectangulosThis[i].x;
		yThis=rectangulosThis[i].y;
		wThis=rectangulosThis[i].width;
		hThis=rectangulosThis[i].height;
		
		for(int j=0;j<rectangulosOther.size();j++){
			xOther=rectangulosOther[j].x;
			yOther=rectangulosOther[j].y;
			wOther=rectangulosOther[j].width;
			hOther=rectangulosOther[j].height;
		

			//Comprobar adyacencia
			if((xOther+wOther)<xThis or (xThis+wThis)<xOther){
				//No es adyacente porque esta demasido lejos en la componente lateral
				return false;
			}else{//Puede ser adyacente esta en rango
				if((yOther+hOther)<yThis or (yThis+hThis)<yOther){
					//No es adyacente demasiado lejos en la componente vertical
					return false;
				}else{
					//Es adyacente
					return true;
				}
			}


		}
	}
}

void Region::merge(const Region& other){
	_hist=(_hist+other.hist())/2;

	for(int i=0;i<other.rects().size();i++){
		_rs.push_back(other.rects()[i]);
	}
}