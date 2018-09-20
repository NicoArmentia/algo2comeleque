#ifndef _SENSOR_INCLUDED_
#define _SENSOR_INCLUDED_

#include <iostream>
#include <string>
#include "array.h"

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
	T &	GetData(const size_t &);	// Devuelve el dato sub i del Array como []
	void	push_back(const T &);	// Agrega un dato al final del Array
	void	SetArray(const Array<T> &);
	const Array<T> & GetArray()const;	// Devuelve el Array de datos (const o no)
	
//	Array<T> & 	operator=( const Array<T> & ); 
//	bool 		operator==( const Array<T> & ) const; 
//	bool 		operator!=( const Array<T> & ) const; 
	
	T &	operator[](const size_t &);	// Devuelve el dato sub i del Array
	T const & operator[](const size_t &)const;	// Idem arriba
	size_t	GetLength()const;	// Devuelve la cantidad de datos del sensor
	void	clear();	// Limpia el sensor
	
};

template <typename T>	// Constructor por defecto
Sensor<T>::Sensor(){cout << "Sensor()\n";}

template <typename T>	// Constructor por copia de ID
Sensor<T>::Sensor(const string & s){
	cout << "Sensor(string="<<s<<")\n";
	ID = s;
}

template <typename T>	// Constructor por copia de datos
Sensor<T>::Sensor(const Array<T> & A){
	cout << "Sensor(array="<<A<<")\n";
	data = A;
}

template <typename T>	// Constructor completo
Sensor<T>::Sensor(const string & s, const Array<T> & A){
	cout << "Sensor(string="<<s<<" y array="<<A<<")\n";
	ID = s;
	data = A;
}

template <typename T>	// Constructor por copia del mismo tipo
Sensor<T>::Sensor(const Sensor & init){
	cout << "Sensor(sensor)\n";
	ID = init.GetID();
	data = init.GetArray();
	cout << "ID = "<<ID<<'\n';
	cout << "array = "<<data<<'\n';
}

template <typename T>	// Destructor
Sensor<T>::~Sensor(){cout << "~Sensor()\n";}

template <typename T>	// Setea el ID del sensor
void Sensor<T>::SetID(const string & s){ID=s; cout<<"seteo ID ="<<s<<'\n';}	

template <typename T>	// Devuelve el ID del sensor
string Sensor<T>::GetID()const{cout<<"return ID = "<<ID<<'\n';return ID;}

template <typename T>	// Setea el dato sub i del Array
void Sensor<T>::SetData(const T & x,const size_t & i){cout<<"setdata[i]=x ("<<i<<','<<x<<")\n";data[i]=x;}

template <typename T>	// Devuelve el dato sub i del Array, como []
T & Sensor<T>::GetData(const size_t & i){cout<<"getdata i="<<i<<'\n';return data[i];}

template <typename T>	// Agrega un dato al final del Array
void Sensor<T>::push_back(const T & x){cout<<"pushback de x = "<<x<<'\n';data.push_back(x);}

template <typename T>	// Seteo el array de datos
void Sensor<T>::SetArray(const Array<T> & A){cout<<"SetArray()\n";data = A;}

template <typename T>	// Devuelve el Array de datos (const o no)
const Array<T> & Sensor<T>::GetArray()const{cout<<"GetArray()\n";return data;}

template <typename T>	// Devuelve el dato sub i del Array
T & Sensor<T>::operator[](const size_t & i){cout<<"operator[]\n";return data[i];}

template <typename T>	// Devuelve el dato sub i del Array
T const & Sensor<T>::operator[](const size_t & i)const{"operator[]const\n";return data[i];}



template <typename T>	// Devuelve la cantidad de datos del sensor
size_t Sensor<T>::GetLength()const{cout<<"GetLength\n";return data.GetUsedLen();}

template <typename T>	// Limpia el sensor
void	Sensor<T>::clear(){
	cout<<"clear de ID y datos\n";
	ID.clear();
	data.clear();
}

#endif
