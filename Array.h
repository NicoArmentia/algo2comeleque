#ifndef _ARRAY_H_INCLUDED_
#define _ARRAY_H_INCLUDED_


#include <cassert>
#include <iostream>
#include <stdio.h>
#include <cstdlib>

using namespace std;

#define DEFAULT_LEN 10
#define ARRAY_GROWTH_RATE 2

template <class T>
class Array
{
	size_t total_len;
	size_t used_len;
	T * p;
	void resize(size_t);

public:

			Array();
			Array(size_t);
			Array(const Array<T> &); 
			~Array();
	size_t 		GetTotalLen() const;
	size_t 		GetUsedLen() const; 
	Array<T> & 	operator=(const Array<T> &);
	bool 		operator==(const Array<T> &) const; 
	bool 		operator!=(const Array<T> &) const;
	T & 		operator[](const size_t &);
	const T &	operator[](const size_t &) const;
	void 		push_back(const T &);
	void 		clear();
	template <typename TT>
	friend std::ostream& operator<<(std::ostream&,const Array<TT>&);
	template <typename TT>
	friend std::istream & operator>> (std::istream&,Array<TT>&);
};

template <class T>
Array<T>::Array(){
	used_len = 0;
	total_len = DEFAULT_LEN;
	p = new T[total_len];
}

/* En caso de especificar contruir un arreglo de longitud cero, se crea a p apuntando a NULL */

template <class T>
Array<T>::Array(size_t t){
	if(!t){
		total_len=0;
		used_len=0;
		p = NULL;
	}
	else{
		total_len = t;
		used_len = 0;
		p = new T[total_len];
	}
}

template <class T>
Array<T>::Array(const Array<T> & a_init){
	size_t i;
	
	total_len = a_init.GetTotalLen();
	used_len = a_init.GetUsedLen();
	p = new T[total_len];
	for(i=0;i<used_len;i++)
		p[i]=(a_init.p)[i];
}

template <class T>
Array<T>::~Array(){if(p) delete []p;}

template <class T>
size_t Array<T>::GetUsedLen() const {return used_len; }

template <class T>
size_t Array<T>::GetTotalLen() const {return total_len; }

template <typename T> 
Array<T> & Array<T>::operator=(const Array<T> & rhs){
	T * aux;
	if (&rhs == this) {
		return *this;
	}
	if (total_len != rhs.total_len){
		aux = new T[rhs.total_len]; 
		delete [] p; 
		p = aux;
		total_len = rhs.total_len; 
		used_len = rhs.used_len;
	}
	used_len = rhs.used_len;
	for (size_t i = 0;i < used_len;i++)
		p[i] = rhs.p[i]; 
	return *this;
}
template <typename T> 
bool Array<T>::operator==(const Array<T> & rhs) const{
	if (used_len != rhs.used_len)
		return false; 
	else{
		for(size_t i = 0;i < used_len;i++){
			if (p[i] != rhs.p[i])
       				return false; 
		}
	}
       	return true; 
}

template <typename T> 
bool Array<T>::operator!=(const Array<T> & rhs) const{
	if (rhs == *this)
		return false;
	else
		return true;
}

template <class T>
T & Array<T>::operator [](const size_t & pos){return p[pos];}

template <class T>
T const & Array<T>::operator[](const size_t & pos) const{return p[pos];}

template <typename T> 
std::ostream & operator<< (std::ostream& os,const Array<T> & arr){
	// Escribe el arreglo en el formato (T1,T2,T3 ... Tn)
	// Se asume que existe el operador << para la clase T	
	if( arr.GetUsedLen() == 0 ){
		os << "()";
		return os;
	}
	os << "(";
	for(size_t i=0; i<arr.GetUsedLen()-1; ++i){
		os << arr[i] << ",";
	}
	os << arr[arr.GetUsedLen()-1];
	os << ")";
	return os;
}

/***************************** FUNCIONES HECHAS EN CLASE ***************************************/
template <typename T> 
void Array<T>::clear(){
	delete[] p;
	total_len = DEFAULT_LEN;
	used_len = 0;
	p = new T[total_len];
}


template <typename T> 
void Array<T>::resize(size_t new_size){
	// Redimensiono el arreglo, y copio todo hasta donde puedo.
	// Desde afuera no se ve el redimensionamiento
	T *aux;
		
	aux = new T[new_size];
	if( new_size < used_len ){
		used_len = new_size;
	}
	for( size_t i=0;i<used_len;++i){
		aux[i] = p[i];
	}
	if(p!=NULL) delete [] p;
	p = aux;
	total_len = new_size;
}

template <typename T> 
void Array<T>::push_back(const T & new_thing){
	// Si es necesario agrandar el arreglo ya que no queda más espacio, lo
	// agrando por 2.
	// La decisión de cuando agrandar puede variar, ya que puede ser cuando 
	// el tamaño es la mitad del reservado, por ejemplo.
	// Al agrandar, copio todos los elementos del arreglo
	if(total_len == used_len){
		this->resize(total_len*ARRAY_GROWTH_RATE);
	}	
	p[used_len] = new_thing;
	used_len++;
}


template <typename T>
std::istream & operator>> (std::istream& is,Array<T>& arr){
	// Limpio el arreglo y leo en formato (T1,T2,...,Tn) de is. Si no se hace conforme a lo
	// esperado, limpio el arreglo (devuelvo uno sin elementos)
	// Si llega a EOF, marcará en el istream
	T aux = 0;
	char ch = 0;
	
	arr.clear();
	if( (is >> ch) && (ch == '(') && (is >> aux) ){
		arr.push_back(aux);
		while( (is >> ch) && (ch == ',') && (is >> aux) ){
			arr.push_back(aux);
		}
	} 
	if ( ch != ')' ){
		arr.clear();
	}
	return is;
}

/* ****************************************************************************************** */

#endif
