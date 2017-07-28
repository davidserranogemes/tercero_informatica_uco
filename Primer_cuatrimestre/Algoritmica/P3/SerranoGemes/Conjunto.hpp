#ifndef CONJUNTO_HPP
#define CONJUNTO_HPP 


#include <vector>
#include <cassert>

template <class T>

class Conjunto {
	private:
		std::vector<T> v_;
		int size_;
	public:
		Conjunto(){
			size_=0;
		}
		inline void insert(T t){v_.push_back(t);size_++;};
		
		inline void deletePos(int pos){//Desde 0 a size-1
			assert(size_>0);
			assert(pos>=0 and pos<size_);
			std::vector<T> aux;

			aux.resize(size_-1);
			for(int i=0,auxSel=0;i<size_;i++){
				if(i!=pos){
					aux[auxSel]=v_[i];
					auxSel++;
				}
			}

			v_=aux;
			size_--;
			}
		inline T at(int pos){
			assert(size_>0);
			assert(pos>=0 and pos<size_);
			return v_[pos];
		}

		inline void cleanConj(){
			/*while(size_>0){
				deletePos(0);
			}*/
			v_.clear();
			size_=0;
		};

		inline int size(){
			return size_;
		}

/*
		inline void maxMinDivVen(int i, int j, T &max, T &min,uint &numComp){		//void Conjunto<T>::maxMinDivVen(int i, int j, T &max, T &min){
			int mitad;
			T min1,min2;
			T max1, max2;

			numComp++;
			if( i==j){
				max=at(i);
				min=at(j);

			}else{
				numComp++;
				if(i == (j-1)){
					numComp++;
					if(at(i)>at(j)){
						max=at(i);
						min=at(j);
					}else{
						max=at(j);
						min=at(i);
					}
				}else{
					mitad=(i+j)/2;
					maxMinDivVen(i,mitad,max1, min1,numComp);
					maxMinDivVen(mitad+1,j,max2,min2,numComp);
					numComp++;
					if(max1>max2){
						max=max1;
					}else{
						max=max2;
					}
					numComp++;
					if(min1<min2){
						min=min1;
					}else{
						min=min2;
					}
					//std::cout<<"MAX: "<<max<<" MIN: "<<min<<std::endl;
				}	
			}

		}



		inline void maxMinIter(T &max, T &min,uint &numComp){
			T curr=0;
			max=this->at(0);
			min=this->at(0);
	
			for(int i=1;i<this->size();i++){
				curr=this->at(i);

				numComp++;
				if(curr>max){
					max=curr;
				}
				numComp++;
				if(curr<min){
					min=curr;
				}
			}
		}
		*/
};




#endif