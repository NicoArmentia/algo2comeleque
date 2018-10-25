#ifndef _DATA_H_INCLUDED_
#define _DATA_H_INCLUDED_

#include <cassert>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <limits>

using namespace std;

template <typename T>
class Data{

	T data;
	bool enabled;  // false: disabled , true: enabled

public:

	Data();
	Data(const T &);
	Data(const bool &);
	Data(const T &,const bool &);
	Data(const Data &);
	~Data();
	T GetData()const;
	void SetData(const T &);
	bool GetState()const;
	void EnableData();
	void DisableData();
	Data<T> & operator=(const Data<T> &);

	template <typename TT>
	friend ostream& operator<<(ostream&,const Data<TT>&);
	template <typename TT>
	friend istream& operator>>(istream&,const Data<TT>&);

};


/********************************* METODOS DE LA CLASE *********************************/
template <typename T>
Data<T>::Data(){data = 0; enabled = false;}

template <typename T>
Data<T>::Data(const T & d){data = d;}

template <typename T>
Data<T>::Data(const bool & state){enabled = state;}

template <typename T>
Data<T>::Data(const T & d,const bool & state){
	data = d;
	enabled = state;
}

template <typename T>
Data<T>::Data(const Data & init_data){

	data = init_data.data;
	enabled = init_data.enabled;
}

template <typename T>
Data<T>::~Data(){}

template <typename T>
T Data<T>::GetData()const{return data;}

template <typename T>
void Data<T>::SetData(const T & d) {data = d;}

template <typename T>
bool Data<T>::GetState()const{return enabled;}

template <typename T>
void Data<T>::EnableData(){enabled = true;}

template <typename T>
void Data<T>::DisableData(){enabled = false;}

template <typename T>
ostream& operator<<(ostream & os,const Data<T> & d){

	cout << d.data;
	return os;
}

template <typename T>
istream & operator>>(istream &is, Data<T> & d){

	bool good = false;
	bool bad = false;
	T aux_data;

	if(is >> aux_data) good = true;

	else bad = true;

	if(good) d.SetData(aux_data);

	if(bad) is.clear(ios::badbit);

	return is;
}

template <typename T>
Data<T> & Data<T>::operator=(const Data<T> & d){

	data = d.data;
	enabled = d.enabled;
	return *this;
}

#endif
