#ifndef _SEGTREE_H_INCLUDED_
#define _SEGTREE_H_INCLUDED_

#include <iostream>
#include <cstdlib>
#include <limits>
#include "func_template.h"
#include "Array.h"
#include "Data.h"

using namespace std;

#define	POS_NUM	0
#define	POS_SUM	1
#define	POS_MIN	2
#define	POS_MAX	3
#define INFINITY numeric_limits<double>::infinity()

static string string_arr[] = {"Count","Sum","Min","Max"}; 



template <typename T>
class SegTree{
// Atributos privados
private:
	Array<T[4]> * ST;	/* Arreglo de arreglo de datos. Es un arreglo que simula un arbol
				que en cada nodo(arreglo) tiene la cantidad efectiva de datos usados,
				 la suma de los segmentos 'hijos', el maximo y el minimo */
				
	size_t	len;		// Menor potencia de 2 mayor o igual a n
	
	SegTree();		// No debería haber un constructor sin un vector del cual generar 
				// el segment tree
	
size_t	GetLen()const;
Array<T[4]>  & GetTree()const;
	
public:

	SegTree(const Array<T> &);
	//SegTree(const SegTree &);	// Constructor por copia del mismo tipo
	~SegTree();	// Destructor
	int SearchSegTree(size_t,size_t,T&,T&,T&,T&)const;
	void SearchSegTree_(size_t,size_t,size_t,size_t,T * &,size_t)const;
	template<typename TT>
	friend std::ostream& operator<<(std::ostream&,const SegTree<TT> &);
};

template <typename T>
SegTree<T>::SegTree(){}


template <typename T>
SegTree<T>::SegTree(const Array<T> & v){
	size_t n = v.GetUsedLen(), n_ = n;
	size_t size;
	int pow = 1;	// Sirve para conseguir la menor potencia de 2 mayor o igual a n
	
	if(!n){
		ST = NULL;
		len = 0;
	}
	else{
		//	Busco la siguiente potencia de 2 mayor o igual a n_
		while(n_ >>= 1) ++pow;
		if(n<3)	len = n;
		else 	len = 1 << pow;
		//
		ST = new Array<T[4]>(size = 2*len - 1);
		for(size_t i = 0; i<len; i++){
			if(i<n){
				if(v[i].GetState() == true){ // Si el dato existe lo guardo
					((*ST)[len+i-1])[POS_NUM] = 1;
					((*ST)[len+i-1])[POS_SUM] = v[i].GetData();
					((*ST)[len+i-1])[POS_MIN] = v[i].GetData();
					((*ST)[len+i-1])[POS_MAX] = v[i].GetData();
				}
				else{
					((*ST)[len+i-1])[POS_NUM] = 0;
					((*ST)[len+i-1])[POS_SUM] = 0;
					((*ST)[len+i-1])[POS_MIN] = INFINITY;
					((*ST)[len+i-1])[POS_MAX] = -INFINITY;
				}
			}
			else{
				((*ST)[len+i-1])[POS_NUM] = 0;
				((*ST)[len+i-1])[POS_SUM] = 0;
				((*ST)[len+i-1])[POS_MIN] = INFINITY;
				((*ST)[len+i-1])[POS_MAX] = -INFINITY;
			}
		}
		for(size_t i = size-1; i>1; i=i-2){
			((*ST)[(i-1)/2])[POS_NUM] = ((*ST)[i])[POS_NUM] + ((*ST)[i-1])[POS_NUM];
			((*ST)[(i-1)/2])[POS_SUM] = ((*ST)[i])[POS_SUM] + ((*ST)[i-1])[POS_SUM];
			((*ST)[(i-1)/2])[POS_MIN] = Min<T>(((*ST)[i])[POS_MIN],((*ST)[i-1])[POS_MIN]);
			((*ST)[(i-1)/2])[POS_MAX] = Max<T>(((*ST)[i])[POS_MAX],((*ST)[i-1])[POS_MAX]);
		}
	}	
}


template <typename T>	// Destructor
SegTree<T>::~SegTree(){if(ST) delete ST;}



template <typename T>
int SegTree<T>::SearchSegTree(size_t init_pos, size_t fin_pos, T& min, T& max, T& prom, T& num)const{
	T * v = new T[4];
	if(!ST) return -1;
	
	if(fin_pos <= init_pos) return -1;	//Ver que hago con esto
	
	SearchSegTree_(init_pos,fin_pos,0,len,v,0);
	if(v[POS_NUM] == 0.0){
		delete []v;
		return -1;			//Ver que hago con esto
	}
	min = v[POS_MIN];
	max = v[POS_MAX];
	num = v[POS_NUM];
	prom = v[POS_SUM]/num;
	delete []v;
	return 0;
}


template <typename T>
void SegTree<T>::SearchSegTree_(size_t init_pos,size_t fin_pos,size_t lower,size_t upper,T * & v,size_t k)const{
	T * aux_left;
	T * aux_right;
	size_t m = (lower + upper)/2;	
	bool left = false;
	bool right = false;
	
	cout << "k:= " << k << endl;

	
	if(init_pos <= lower && fin_pos >= upper){
	
		cout << "entro ambas\t" << k << endl;
		cout << endl;
		//for(size_t j=0;j<4;j++) cout<<v[j];
		cout << endl;
		cout << "v :=" << v <<"\t&v := " << &v << endl;
		for(size_t j=0;j<4;j++) v[j] = ((*ST)[k])[j];
		cout << "(*ST)[k]:=" << (*ST)[k] << "\t&((*ST)[k]):=" <<&((*ST)[k]) <<  endl;
		cout << v << "\t" <<*v << endl;
		for(size_t j=0;j<4;j++) cout<<v[j];
		cout << endl;
		cout << v[POS_MIN] << "\t" << v[POS_MAX] << endl;
	
		for(size_t l=0;l<15;l++)
			cout << ((*ST)[l])[POS_MIN] << ',';
		cout << endl << v[POS_MIN] <<"\t"<< lower << "," << upper << "," << k << endl;
		return;
	}
	else{
		 if(init_pos < m){
			cout << "entro left\t" << k << endl;
			aux_left = new T[4];
			left = true;
			cout << endl;
			//for(size_t j=0;j<4;j++) cout<<aux_left[j];
			cout << endl;
			cout << "aux_left :=" << aux_left <<"\t&aux_left := " << &aux_left << endl;
			(*this).SearchSegTree_(init_pos, fin_pos, lower, m, aux_left,2*k+1);
			cout << "aux_left :=" << aux_left <<"\t&aux_left := " << &aux_left << endl;
			for(size_t j=0;j<4;j++) cout<<aux_left[j];
			cout << endl;
		}
		if(fin_pos > m){
			cout << "entro right\t" << k << endl;
			aux_right = new T[4];
			right = true;
			(*this).SearchSegTree_(init_pos, fin_pos, m, upper, aux_right, 2*k+2);
		}
	}	
		
	if(left && right){
		cout << "entro en combinar left && right" << endl;
		v[POS_MIN] = Min<T>(aux_left[POS_MIN],aux_right[POS_MIN]);
		cout << "aux_left:= " << aux_left[POS_MIN] << " aux_right:= ";
		cout << aux_right[POS_MIN] << " gano := " << v[POS_MIN] << endl;;
		v[POS_MAX] = Max<T>(aux_left[POS_MAX],aux_right[POS_MAX]);
		cout << "aux_left:= " << aux_left[POS_MAX] << " aux_right:= ";
		cout << aux_right[POS_MAX] << " gano := " << v[POS_MAX] << endl;;
		v[POS_NUM] = aux_left[POS_NUM] + aux_right[POS_NUM];
		cout << "aux_left:= " << aux_left[POS_NUM] << " aux_right:= ";
		cout << aux_right[POS_NUM] << " gano := " << v[POS_NUM] << endl;;
		v[POS_SUM] = (aux_left[POS_SUM] + aux_right[POS_SUM]);
		cout << "aux_left:= " << aux_left[POS_SUM] << " aux_right:= ";
		cout << aux_right[POS_SUM] << " gano := " << v[POS_SUM] << endl;;
	}
	else if(left){
		cout << "entro en combinar left" << endl;
		v[POS_MIN] = aux_left[POS_MIN];
		v[POS_MAX] = aux_left[POS_MAX];
		v[POS_NUM] = aux_left[POS_NUM];
		v[POS_SUM] = aux_left[POS_SUM];
	}
	else{
		v[POS_MIN] = aux_right[POS_MIN];
		cout << "entro en combinar right" << endl;
		v[POS_MAX] = aux_right[POS_MAX];
		v[POS_NUM] = aux_right[POS_NUM];
		v[POS_SUM] = aux_right[POS_SUM];
	}
	if(left) delete []aux_left;
	if(right) delete []aux_right;
	return;
}

template<typename T>
size_t	SegTree<T>::GetLen()const{ return len;}

template<typename T>
Array<T[4]>  & SegTree<T>::GetTree()const{return *ST;}

template<typename T>
std::ostream & operator<<(std::ostream& o,const SegTree<T> & S){
	size_t len; 
	len = S.GetLen();
	for(size_t i=0;i<4;i++){
		o << string_arr[i] << " : ";
		o << "(";
		for(size_t j=0;j<2*len-2;j++){
			o << (S.GetTree())[j][i] << ',';
		}
		o << (S.GetTree())[2*len-2][i] << ')' << endl;
	}
	return o;	
}

#endif
