#include <cassert>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "Array.h"
#include "Data.h"
#include "Sensor.h"

using namespace std;

#ifndef _QUERY_H_INCLUDED_
#define _QUERY_H_INCLUDED_

typedef enum {OK=0,BAD_QUERY=1,NO_DATA=2,UNKNOWN_ID=3} qstate_t;

static string State_Dict[4] = {"OK","BAD_QUERY","NO_DATA","UNKNOWN_ID"};

template <typename T>
class Query{

	string IDs;
	Array<T> qdata;
	size_t len=0;
	size_t init_pos;
	size_t fin_pos;
	T min;
	T max;
	T prom;
	qstate_t state;

public:

	Query();
	Query(const string * &);
	Query(const string * &,size_t,size_t); 

	Query<T> & operator=(const Query<T> &); 

	void SetID(const string &);
	const string & GetID()const;

	bool SearchIDFromSensor(const Array<Sensor<Data<T>>>&,size_t &);

	size_t GetLength() const;
	
	void SetInitPos(size_t);
	size_t GetInitPos() const;

	void SetFinPos(size_t);
	size_t GetFinPos() const;

	void CalcMin();
	const T & GetMin() const;

	void CalcMax();
	const T & GetMax() const;

	void CalcProm();
	const T & GetProm() const;

	void SetState(const qstate_t &);
	const qstate_t & GetState();

	void SetQuery(stringstream &,char delimiter);

	void SetDataQuery(const Array<Data<T>> &); //Para el uso de esta funcion es necesario tener init_pos y fin_pos


	template <typename TT>
	friend ostream& operator<<(ostream&,const Query<TT>&);

};

/**************************************** METODOS DE CLASE ****************************************/

template <typename T>
Query<T>::Query(){}

template <typename T>
Query<T>::Query(const string * & s){IDs = s;}

template <typename T>
Query<T>::Query(const string * & s,size_t init,size_t fin){

	IDs = s;
	init_pos = init;
	fin_pos = fin;
}

template <typename T>
Query<T> & Query<T>::operator=(const Query<T> & q){

	IDs = q.IDs;
	qdata = q.qdata;
	len = q.len;
	init_pos = q.init_pos;
	fin_pos = q.fin_pos;
	min = q.min;
	max = q.max;
	prom = q.prom;
	state = q.state;
	
	return *this;
}

template <typename T>
void Query<T>::SetDataQuery(const Array<Data<T>> & data_arr){

	size_t data_len = data_arr.GetUsedLen();
	size_t i=0,j=0;

	if(data_len < init_pos){

		state = NO_DATA;
		return;
	}

	size_t aux_len = fin_pos - init_pos;

	for(i=0;i<aux_len;i++){

		if(data_arr[i].GetState() == true){
			qdata.push_back(data_arr[i].GetData());	
			j++;
		}
	}

	len = j;


	return;
}

template <typename T>
size_t Query<T>::GetLength() const{return len;}	
	
template <typename T>
void Query<T>::SetID(const string & s){IDs = s;}

template <typename T>
const string & Query<T>::GetID()const{return IDs;}

template <typename T>
void Query<T>::SetInitPos(size_t pos){init_pos = pos;}

template <typename T>
size_t Query<T>::GetInitPos() const{return init_pos;}

template <typename T>
void Query<T>::SetFinPos(size_t pos){fin_pos = pos;}

template <typename T>
size_t Query<T>::GetFinPos() const{return fin_pos;}

template <typename T>
const T & Query<T>::GetMin() const{return min;}

template <typename T>
const T & Query<T>::GetMax() const{return max;}

template <typename T>
const T & Query<T>::GetProm() const{return prom;}

template <typename T>
void Query<T>::SetState(const qstate_t & new_state){state = new_state;}

template <typename T>
const qstate_t & Query<T>::GetState(){return state;}

template <typename T>
void Query<T>::SetQuery(stringstream & infile,char delimiter){

	char ch;
	size_t aux_init;
	size_t aux_fin;
	string aux_s;

	if(getline(infile,aux_s,delimiter) && infile >> aux_init && infile >> ch
		 && ch == delimiter && infile >> aux_fin){

		SetID(aux_s);
		SetInitPos(aux_init);
		SetFinPos(aux_fin);
		SetState(OK);

	}
	
	else{
		 state = BAD_QUERY;
		 return;
	}

	return;
}

template <typename T>
bool Query<T>::SearchIDFromSensor(const Array<Sensor<Data<T>>>& sensor_arr,size_t & position){

	for(size_t j=0;j<sensor_arr.GetTotalLen();j++){

		if(sensor_arr[j].GetID() == GetID()){
			position = j;
			return true;
		}
	}

	return false;			
}		


template <typename T>
ostream& operator<<(ostream & os,const Query<T> & q){

	cout << q.qdata;
	return os;
}

#endif
