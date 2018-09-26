#ifndef _SENSOR_H_INCLUDED_
#define _SENSOR_H_INCLUDED_

#include <iostream>
#include <string>
#include "Array.h"

using namespace std;


template <typename T>
class Sensor{
// Atributos privados
private:

	string ID;	// Nombre, cadena de caracteres
	Array<T> data;	//  Vector de datos
	
public:
		Sensor();	// Constructor por defecto
		Sensor(const string &);	// Constructor por copia de ID
		Sensor(const Array<T> &);	// Constructor por copia de datos
		Sensor(const string &,const Array<T> &);	// Constructor completo
		Sensor(const Sensor &);	// Constructor por copia del mismo tipo
		~Sensor();	// Destructor
	void	SetID(const string &);	// Setea el ID del sensor
	string	GetID()const;	// Devuelve el ID del sensor
	void	SetData(const T &,const size_t &);	// Setea el dato sub i del Array
	void	push_back(const T &);	// Agrega un dato al final del Array

//	Array<T> & 	operator=( const Array<T> & ); 
//	bool 		operator==( const Array<T> & ) const; 
//	bool 		operator!=( const Array<T> & ) const; 
	
	T &	operator[](const size_t &);	// Devuelve el dato sub i del Array
	T const & operator[](const size_t &)const;	// Idem arriba
	const Array<T> & GetArray()const;	// Devuelve el Array de datos (const o no)
	size_t	GetLength()const;	// Devuelve la cantidad de datos del sensor
	void	clear();	// Limpia el sensor
	
};

template <typename T>	// Constructor por defecto
Sensor<T>::Sensor(){}

template <typename T>	// Constructor por ID
Sensor<T>::Sensor(const string & s){ID = s;}

template <typename T>	// Constructor por datos
Sensor<T>::Sensor(const Array<T> & A){data = A;}

template <typename T>	// Constructor completo
Sensor<T>::Sensor(const string & s, const Array<T> & A){
	ID = s;
	data = A;
}

template <typename T>	// Constructor por copia
Sensor<T>::Sensor(const Sensor & init){
	ID = init.GetID();
	data = init.GetArray();
}

template <typename T>	// Destructor
Sensor<T>::~Sensor(){}

template <typename T>	// Setea el ID del sensor
void Sensor<T>::SetID(const string & s){ID=s;}	

template <typename T>	// Devuelve el ID del sensor
string Sensor<T>::GetID()const{return ID;}

template <typename T>	// Setea el dato sub i del Array
void Sensor<T>::SetData(const T & x,const size_t & i){data[i]=x;}

template <typename T>	// Agrega un dato al final del Array
void Sensor<T>::push_back(const T & x){data.push_back(x);}

template <typename T>	// Devuelve el dato sub i del Array
T & Sensor<T>::operator[](const size_t & i){return data[i];}

template <typename T>	// Devuelve el dato sub i del Array
T const & Sensor<T>::operator[](const size_t & i)const{return data[i];}

template <typename T>	// Devuelve el Array de datos (const o no)
const Array<T> & Sensor<T>::GetArray()const{return data;}

template <typename T>	// Devuelve la cantidad de datos del sensor
size_t Sensor<T>::GetLength()const{return data.GetUsedLen();}

template <typename T>	// Limpia el sensor
void	Sensor<T>::clear(){
	ID.clear();
	data.clear();
}

#endif
