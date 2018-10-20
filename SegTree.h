#ifndef _SEGTREE_H_INCLUDED_
#define _SEGTREE_H_INCLUDED_

#include <iostream>
#include <cstdlib>
#include <limits>
#include "func_template.h"
#include "Array.h"

#define	POS_NUM	0
#define	POS_SUM	1
#define	POS_MIN	2
#define	POS_MAX	3


using namespace std;


template <typename T>
class SegTree{
// Atributos privados
private:
			/* Arreglo de arreglo de datos. Es un arreglo que simula un arbol
				que en cada nodo(arreglo) tiene la cantida efectiva de datos usados,
				 la suma de los segmentos 'hijos', el maximo y el minimo */
				
       //size_t	n;		// Cantidad de datos que tiene el vector del cual se crea el ST
	size_t	len;		// Menor potencia de 2 mayor o igual a n
	
	SegTree();		// No debería haber un constructor sin un vector del cual generar 
				// el segment tree
	
public:
		Array<T[4]> ST;
		SegTree(const Array<T> &);
		//SegTree(const SegTree &);	// Constructor por copia del mismo tipo
		~SegTree();	// Destructor

	/*
//	Array<T> & 	operator=( const Array<T> & ); 
//	bool 		operator==( const Array<T> & ) const; 
//	bool 		operator!=( const Array<T> & ) const; 
	T &	operator[](const size_t &);	// Devuelve el dato sub i del Array
	T const & operator[](const size_t &)const;	// Idem arriba
	const Array<T> & GetArray()const;	// Devuelve el Array de datos (const o no)
	*/
	void SearchSegTree(size_t,size_t,T&,T&,T&,T&);
	void SearchSegTree_(size_t,size_t,size_t,size_t,T*,size_t);
	
};

template <typename T>
SegTree<T>::SegTree(){}

template <typename T>
SegTree<T>::SegTree(const Array<T> & v){
	size_t n = v.GetUsedLen(), n_ = n;
	size_t size;
	int pow = 1;	// Sirve para conseguir la menor potencia de 2 mayor o igual a n
	
	//cout << "Vector de entrada \t" << v << endl;
	
	if(!n){
		Array<T[4]> ST(0);
	}
	else{
		while(n_ >>= 1) ++pow;
		
		if(n<3)
			len = n;
		else
			len = 1 << pow;
			
		Array<T[4]> ST(size = 2*len - 1);
		
//			cout << "pow vale :" << pow <<endl;
//			cout << "n vale :" << n << endl;
//			cout << "len vale : " << len << endl;
//			cout << "size vale : " << size << endl;
	
		for(size_t i = 0; i<len; i++){
			if(i<n){
//				cout << i << '\t' << len+i-1 << endl;
//				cout << "v[i] := " << v[i] << endl;
				(ST[len+i-1])[POS_NUM] = 1;
				(ST[len+i-1])[POS_SUM] = v[i];
				(ST[len+i-1])[POS_MIN] = v[i];
				(ST[len+i-1])[POS_MAX] = v[i];
			}
			else{
				(ST[len+i-1])[POS_NUM] = 0;
				(ST[len+i-1])[POS_SUM] = 0;
				(ST[len+i-1])[POS_MIN] = 1E5;
				(ST[len+i-1])[POS_MAX] = -1E5;
			}
		

		
			for(size_t j=0; j<4;j++){
				cout << endl << "vec sub i = " << i << " \t[" ;
				for(size_t l=0;l<size;l++)
					cout << (ST[l])[j] << ',';
				
				cout <<"]"<<  endl;
			}
		
		
		}
		for(size_t i = size-1; i>1; i=i-2){
			(ST[(i-1)/2])[POS_NUM] = (ST[i])[POS_NUM] + (ST[i-1])[POS_NUM];
			(ST[(i-1)/2])[POS_SUM] = (ST[i])[POS_SUM] + (ST[i-1])[POS_SUM];
			(ST[(i-1)/2])[POS_MIN] = Min<T>((ST[i])[POS_MIN],(ST[i-1])[POS_MIN]);
			(ST[(i-1)/2])[POS_MAX] = Max<T>((ST[i])[POS_MAX],(ST[i-1])[POS_MAX]);
			
		
			for(size_t j=0; j<4;j++){
				cout << endl << "vec sub i = " << i << " \t[" ;
				for(size_t l=0;l<size;l++)
					cout << (ST[l])[j] << ',';
				cout  <<"]"<< endl;
			}
		
		
		}
	}
	
}

template <typename T>	// Destructor
SegTree<T>::~SegTree(){}


template <typename T>
void SegTree<T>::SearchSegTree(size_t init_pos, size_t fin_pos, T& min, T& max, T& prom, T& num){
	size_t k = 0, m;
	T aux_left[4], aux_right[4];
	bool left = false, right = false;
	if(init_pos == 0 && fin_pos >= len){
		min = (ST[k])[POS_MIN];
		max = (ST[k])[POS_MAX];
		num = (ST[k])[POS_NUM];
		prom = (ST[k])[POS_SUM]/num;
		return;
	}
	
	m = len/2;
	if(init_pos < m){
		left = true;
		(*this).SearchSegTree_(init_pos, fin_pos, 0, m, aux_left,2*k+1);
	}
	if(fin_pos >= m){
		right = true;
		(*this).SearchSegTree_(init_pos, fin_pos, m, len, aux_right, 2*k+2);
	}
	if(left && right){
		min = Min<T>(aux_left[POS_MIN],aux_right[POS_MIN]);
		max = Max<T>(aux_left[POS_MAX],aux_right[POS_MAX]);
		num = aux_left[POS_NUM] + aux_right[POS_NUM];
		prom = (aux_left[POS_SUM] + aux_right[POS_SUM])/num;
		return;
	}
	else if(left){
		min = aux_left[POS_MIN];
		max = aux_left[POS_MAX];
		num = aux_left[POS_NUM];
		prom = aux_left[POS_SUM]/num;
	}
	else{
		min = aux_right[POS_MIN];
		max = aux_right[POS_MAX];
		num = aux_right[POS_NUM];
		prom = aux_right[POS_SUM]/num;
	}
	
	/*
		validar fin_pos > init_pos
		SearchSegTree(ini_pos,fin_pos,0,len,v,0)
		min = v[min]
		max = v[max]
		num = v[num]
		prom = v[prom]
		return
	*/
	return;
}

template <typename T>
void SegTree<T>::SearchSegTree_(size_t init_pos,size_t fin_pos,size_t lower,size_t upper,T* v,size_t k){
	T aux_left[4], aux_right[4];
	size_t m = (lower + upper)/2;
	bool left = false, right = false;
	
	if(k>100) return;
	
	//cout << "k := "<< k << "\tlower := " << lower << "\tm := " << m << "\tupper := " << upper << endl;
	//cout << "\tinit_pos := " << init_pos << "\tfin_pos := " << fin_pos << endl;
	//cout << " \tinit pos <= lower? " << (init_pos <= lower) << "\t fin_pos >= upper ?";
	//cout << (fin_pos >= upper) <<"\t fin - upper" <<fin_pos - upper << endl;
	if(init_pos <= lower && fin_pos >= upper){
		//cout << "entro aca" << endl;
		v = ST[k];
		//cout << v[POS_MIN] << "\t" << v[POS_MAX] << endl;
		for(size_t l=0;l<15;l++)
			cout << (ST[l])[POS_MIN] << ',';
		cout << endl << v[POS_MIN] <<"\t"<< lower << "," << upper << endl;
		return;
	}
	if(init_pos < m){
		left = true;
		(*this).SearchSegTree_(init_pos, fin_pos, lower, m, aux_left,2*k+1);
	}
	if(fin_pos >= m){
		right = true;
		(*this).SearchSegTree_(init_pos, fin_pos, m, upper, aux_right, 2*k+2);
	}
	
	
	if(left && right){
		v[POS_MIN] = Min<T>(aux_left[POS_MIN],aux_right[POS_MIN]);
		v[POS_MAX] = Max<T>(aux_left[POS_MAX],aux_right[POS_MAX]);
		v[POS_NUM] = aux_left[POS_NUM] + aux_right[POS_NUM];
		v[POS_SUM] = (aux_left[POS_SUM] + aux_right[POS_SUM])/v[POS_NUM];
	}
	else if(left){
		v[POS_MIN] = aux_left[POS_MIN];
		v[POS_MAX] = aux_left[POS_MAX];
		v[POS_NUM] = aux_left[POS_NUM];
		v[POS_SUM] = aux_left[POS_SUM]/v[POS_NUM];
	}
	else{
		v[POS_MIN] = aux_right[POS_MIN];
		v[POS_MAX] = aux_right[POS_MAX];
		v[POS_NUM] = aux_right[POS_NUM];
		v[POS_SUM] = aux_right[POS_SUM]/v[POS_NUM];
	}
	return;
}


#endif
