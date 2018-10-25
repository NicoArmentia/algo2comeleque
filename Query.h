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
#include "types.h"

using namespace std;

#ifndef _QUERY_H_INCLUDED_
#define _QUERY_H_INCLUDED_

template <typename T>
class Query{

	string IDs;
	size_t ids_len=0;
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

	void CalcMin(const Array<T> &);
	const T & GetMin() const;

	void CalcMax(const Array<T> &);
	const T & GetMax() const;

	void CalcProm(const Array<T> &);
	const T & GetProm() const;

	void SetState(const qstate_t &);
	const qstate_t & GetState();

	void SetQuery(stringstream &,char delimiter);

	void SetDataQuery(const Array<Data<T>> &,Array<T>&); //Para el uso de esta funcion es necesario tener init_pos y fin_pos
	void SetDataQuery(const Array<Array<Data<T>>> &,Array<T>&);

	void DoQuery(const Array<Data<T>> &);
	void DoQuery(const SegTree<Data<T>> &);
	void DoQuery(const Sensor<Data<T>> &);

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

		if(aux_init > aux_fin)
			state = BAD_QUERY;

		else if(aux_init == aux_fin)
			state = NO_DATA;
			
		else{
			SetInitPos(aux_init);
			SetFinPos(aux_fin);
			state = OK;
		}
	}
	
	else{
		 state = BAD_QUERY;
		 return;
	}

	return;
}

template <typename T>
void Query<T>::SetDataQuery(const Array<Data<T>> & data_arr,Array<T>& qdata){

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

	if(!j)
		state = NO_DATA;

	data_len = j;


	return;
}

template <typename T>
void Query<T>::SetDataQuery(const Array<Array<Data<T>>> & d_arr,Array<T> & qdata){

	size_t d_len = (d_arr[0]).GetUsedLen();
	size_t d_arr_len = d_arr.GetTotalLen();
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

		if(count)
			qdata.push_back(aux/=count);   //Se valido si algun sensor tiene algun dato en esa posicion
	}

	data_len = qdata.GetUsedLen();

	if(!data_len) 
		state = NO_DATA;

	return;
}

template <typename T>
bool Query<T>::SearchIDFromSensor(const SensorNet<T>& sensor_net,size_t & position){

	for(size_t j=0;j<sensor_net.GetLen();j++){

		if(sensor_net[j].GetID() == GetID()){
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
	
		os << q.prom << ',';
		os << q.min << ',';
		os << q.max << ',';
		os << q.data_len << endl;
	}
	return os;
}


template <typename T>
void Query<T>::CalcMin(const Array<T> & qdata){
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
void Query<T>::CalcMax(const Array<T> & qdata){
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
void Query<T>::CalcProm(const Array<T> & qdata){
	prom=0;
	for(size_t i = 0;i<data_len;i++){
		prom += qdata[i];
	}
	prom = prom/data_len;
}

template <typename T>
void Query<T>::DoQuery(const Array<Data<T>> & data){

	Array<T> aux_data;
	SetDataQuery(data,aux_data);	
	if(state != OK) return;

	CalcMin(aux_data);
	CalcMax(aux_data);
	CalcProm(aux_data);

	return;
}

/*template <typename T>
void Query<T>::DoQuery(const SegTree<Data<T>> & seg_tree){

	Data<T> dmin,dmax,dprom,dlen;

	seg_tree.SearchSegTree(init_pos,fin_pos,dmin,dmax,dprom,dlen);

	min = dmin.GetData();
	max = dmax.GetData();
	prom = dprom.GetData();
	data_len = dlen.GetData();
}*/

template <typename T>
void Query<T>::DoQuery(const Sensor<Data<T>> & sensor){

	Data<T> dmin,dmax,dprom,dlen;

	sensor.GetSegTree().SearchSegTree(init_pos,fin_pos,dmin,dmax,dprom,dlen);

	min = dmin.GetData();
	max = dmax.GetData();
	prom = dprom.GetData();
	data_len = dlen.GetData();
}


/**************************************************************************************************************/

template <typename T>
int GetQuery(istream & infile,const SensorNet<T> & sensor_net,char delimiter,ostream & output_stream)
{

	string str;
	size_t i=0;
	Query<T> aux_query;
	size_t position;
	bool ID_found;
	extern rmq_mode_t rmq_mode;

	while(getline(infile,str)){
	
		if(str != ""){
		
			stringstream str_st(str);

			aux_query.SetQuery(str_st,delimiter);

			if(aux_query.GetState() == OK){
			
				ID_found = aux_query.SearchIDFromSensor(sensor_net,position);

				if(ID_found == true){

					if(rmq_mode == rmq_segtree) aux_query.DoQuery(sensor_net[position]);
					else aux_query.DoQuery(sensor_net[position].GetArray());
				}

				else if (aux_query.GetID() == "-" || aux_query.GetID() == ""){ 
					
					if(rmq_mode == rmq_segtree) aux_query.DoQuery(sensor_net.GetSensorProm());
					else aux_query.DoQuery(sensor_net.GetSensorProm().GetArray());
				}

				else aux_query.SetState(UNKNOWN_ID);
			}

			i++;
			output_stream << aux_query << endl;

		}
	}
	

	return 0;
}

#endif
