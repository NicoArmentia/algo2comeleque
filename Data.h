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
	Data<T> & operator=(const T&);

	template <typename TT>
	friend ostream& operator<<(ostream&,const Data<TT>&);
	template <typename TT>
	friend istream& operator>>(istream&,const Data<TT>&);
	template <typename TT>
	friend bool	operator==(Data<T> const &,Data<T> const &);//const;
	template <typename TT>
	friend bool	operator==(Data<T> const &,T const &);//const;
	template <typename TT>
	friend bool	operator!=(Data<TT> const &,Data<TT> const &);//const;
	template <typename TT>
	friend bool	operator<(Data<TT> const &,Data<TT> const &);//const;
	template <typename TT>
	friend bool	operator>(Data<TT> const &,Data<TT> const &);//const;
	template <typename TT>
	friend bool	operator<=(Data<TT> const &,Data<TT> const &);//const;
	template <typename TT>
	friend bool	operator>=(Data<TT> const &,Data<TT> const &);//const;
	template <typename TT>
	friend Data<TT> operator+(const Data<TT> &,const Data<TT> &);
	template <typename TT>
	friend Data<TT> operator/(Data<TT> const &,Data<TT> const &);
	
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

	if(d.GetState() == false) os << "Disabled";

	else os << d.data;
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

template <typename T>
Data<T> & Data<T>::operator=(const T & d){
	data = d;
	enabled = true;
	return *this;
}

template <typename T>
bool	operator==(Data<T> const & d1,Data<T> const & d2){
	if(d1.enabled && d2.enabled)
		return d1.data == d2.data;
	return false;
}

template <typename T>
bool	operator==(Data<T> const & d1,T const & d2){
	if(d1.GetState())
		return d1.GetData() == d2;
	return false;
}

template <typename T>
bool	operator!=(Data<T> const & d1,Data<T> const & d2){
	if(d1.enabled && d2.enabled)
		return d1.data != d2.data;
	return true;
}

template <typename T>
bool	operator<(Data<T> const & d1,Data<T> const & d2){
	if(d1.enabled && d2.enabled)
		return d1.data < d2.data;
	return false;
}

template <typename T>
bool	operator>(Data<T> const & d1,Data<T> const & d2){
	if(d1.enabled && d2.enabled)
		return d1.data > d2.data;
	return false;
}

template <typename T>
bool	operator>=(Data<T> const & d1,Data<T> const & d2){
	if(d1.enabled && d2.enabled)
		return d1.data >= d2.data;
	return false;
}

template <typename T>
bool	operator<=(Data<T> const & d1,Data<T> const & d2){
	if(d1.enabled && d2.enabled)
		return d1.data <= d2.data;
	return false;
}

template <typename T>
Data<T> operator+(const Data<T> & d1, const Data<T> & d2){
	Data<T> aux;
	if(d1.enabled && d2.enabled)
		aux= d1.data + d2.data;
	else if(d1.enabled)
		aux = d1;
	else if(d2.enabled)
		aux = d2;
	else
		aux = 0.0;
	return aux;
}

template <typename T>
Data<T> operator/(Data<T> const & d1,Data<T> const & d2){
	Data<T> aux;
	if(d1.enabled && d2.enabled)
		aux = d1.data/d2.data;
	else if(d1.enabled)
		aux = d1;
	else if(d2.enabled)
		aux = d2;
	else
		aux = 0.0;
	return aux;
	//Data<T> aux(d1.data/d2.data,d1.enabled && d2.enabled);
	//return aux;
}

	

#endif
