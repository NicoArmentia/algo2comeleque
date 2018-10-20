#include <cassert>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "Array.h"
#include "Data.h"
#include "Sensor.h"
#include "RedSensores.h"
#include "func_template.h"

using namespace std;

#ifndef _QUERY_H_INCLUDED_
#define _QUERY_H_INCLUDED_

typedef enum {OK=0,BAD_QUERY=1,NO_DATA=2,UNKNOWN_ID=3} qstate_t;

static string State_Dict[4] = {"OK","BAD_QUERY","NO_DATA","UNKNOWN_ID"};

template <typename T>
class Query{

	string IDs;
	size_t ids_len=0;
	Array<T> qdata;
	size_t data_len=0;
	size_t init_pos=0;
	size_t fin_pos=0;
	T min;
	T max;
	T prom;
	qstate_t state=OK;

public:

	Query();
	Query(const string * &);
	Query(const string * &,size_t,size_t); 

	Query<T> & operator=(const Query<T> &); 

	void SetID(const string &);
	const string & GetID()const;

	bool SearchIDFromSensor(const SensorNet<T>&,size_t &);

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
	void SetDataQuery(const Array<Array<Data<T>>> &,size_t);

	void DoQuery();


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
	data_len = q.data_len;
	init_pos = q.init_pos;
	fin_pos = q.fin_pos;
	min = q.min;
	max = q.max;
	prom = q.prom;
	state = q.state;
	
	return *this;
}

template <typename T>
size_t Query<T>::GetLength() const{return data_len;}	
	
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

	if(getline(infile,aux_s,delimiter)) SetID(aux_s);

	if(infile >> aux_init && infile >> ch && ch == delimiter && infile >> aux_fin){

			
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
void Query<T>::SetDataQuery(const Array<Data<T>> & data_arr){

	size_t data_len_aux = data_arr.GetUsedLen();
	size_t i=0,j=0;

	if(data_len_aux < init_pos){

		state = NO_DATA;
		return;
	}

	qdata.clear();

	if(data_len_aux<fin_pos) fin_pos = data_len_aux;

	for(i=init_pos;i<fin_pos;i++){

		if(data_arr[i].GetState() == true){
			qdata.push_back(data_arr[i].GetData());	
			j++;
		}
	}

	data_len = j;


	return;
}

template <typename T>
void Query<T>::SetDataQuery(const Array<Array<Data<T>>> & d_arr,size_t d_arr_len){

	size_t d_len = (d_arr[0]).GetUsedLen();
	size_t i,j,count = 0;
	T	aux;

	if(d_len < init_pos){

		state = NO_DATA;
		return;
	}

	qdata.clear();

	if(d_len<fin_pos) fin_pos = d_len;

	for(i=init_pos;i<fin_pos;i++){
		aux = 0;
		count = 0;
		for(j=0;j<d_arr_len;j++){
			if( ((d_arr[j])[i]).GetState() == true ){
				aux += ((d_arr[j])[i]).GetData();
				count++;
			}
		}
		aux/=count;
		qdata.push_back(aux);
	}

	data_len = qdata.GetUsedLen();

	return;
}

template <typename T>
bool Query<T>::SearchIDFromSensor(const SensorNet<T>& sensor_arr,size_t & position){

	for(size_t j=0;j<sensor_arr.GetLen();j++){

		if(sensor_arr[j].GetID() == GetID()){
			position = j;
			return true;
		}
	}

	return false;			
}		


template <typename T>
ostream& operator<<(ostream & os,const Query<T> & q){
	if(q.state != OK)
		os<<State_Dict[q.state]<<endl;
	else{
	
		//os << q.qdata << endl;
		os << q.prom << ',';
		os << q.min << ',';
		os << q.max << ',';
		os << q.data_len << endl;
	}
	return os;
}


template <typename T>
void Query<T>::CalcMin(){
	bool min_set = false;
	for(size_t i = 0;i<data_len;i++){
		if(min_set == true)
			min = Min<T>(min,qdata[i]);
		else{
			min = qdata[i];
			min_set = true;
		}
	}
}

template <typename T>
void Query<T>::CalcMax(){
	bool max_set = false;
	for(size_t i = 0;i<data_len;i++){
		if(max_set == true)
			max = Max<T>(max,qdata[i]);
		else{
			max = qdata[i];
			max_set = true;
		}
	}
}

template <typename T>
void Query<T>::CalcProm(){
	for(size_t i = 0;i<data_len;i++){
		prom += qdata[i];
	}
	prom = prom/data_len;
}

template <typename T>
void Query<T>::DoQuery(){

	CalcMin();
	CalcMax();
	CalcProm();
}

template <typename T>
int get_query_arr(istream & infile,Array<Query<T>> & query_arr,const SensorNet<T> & sensor_arr,size_t * qlen,char delimiter)
{

	string str;
	size_t i=0,j;
	Query<T> aux_query;
	size_t position;
	bool ID_found;
	Array<Array<Data<T>>> * aux_arr;
	size_t aux_len = sensor_arr.GetLen();

	while(getline(infile,str)){
		
		stringstream str_st(str);

		aux_query.SetQuery(str_st,delimiter);

		if(aux_query.GetState() == OK){
		
			ID_found = aux_query.SearchIDFromSensor(sensor_arr,position);

			if(ID_found == true) aux_query.SetDataQuery(sensor_arr[position].GetArray());

			else if (aux_query.GetID() == "-"){ 
				
				aux_arr = new Array<Array<Data<T>>>(aux_len);

				for(j=0;j<aux_len;j++) 
					(*aux_arr).push_back(sensor_arr[j].GetArray());

				aux_query.SetDataQuery(*aux_arr,aux_len);

				delete aux_arr;
			}

			else aux_query.SetState(UNKNOWN_ID); 
		}
		
		query_arr.push_back(aux_query);

		i++;
	}
	
	*qlen = i;

	return 0;
}

#endif
