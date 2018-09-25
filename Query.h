#include <cassert>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include "Array.h"

using namespace std;

#ifndef _QUERY_H_INCLUDED_
#define _QUERY_H_INCLUDED_

typedef enum {OK,BAD_QUERY,NO_DATA,UNKNOWN_ID} qstate_t;

template <typename T>
class Query{

	string IDs;
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

	void SetID(const string &);
	const string & GetID()const;
	
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

	void SetQuery(ifstream &,char delimiter);

};

/**************************************** METODOS DE CLASE ****************************************/

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
void Query<T>::SetQuery(ifstream & infile,char delimiter){

	char ch;
	size_t aux_init;
	size_t aux_fin;
	string aux_s;


	if(getline(infile,aux_s,delimiter) && infile >> aux_init && infile >> aux_init
			 && infile >> ch && ch == delimiter && infile >> aux_fin){

		IDs = aux_s;
		init_pos = aux_init;
		fin_pos = aux_fin;
	}
	
	else{
		 state = BAD_QUERY;
		 return;
	}

}

		


#endif
