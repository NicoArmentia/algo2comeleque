#include <cassert>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "Array.h"
#include "Sensor.h"
#include "Data.h"
#include "SegTree.h"

using namespace std;

#ifndef _REDSENSORES_H_INCLUDED_
#define _REDSENSORES_H_INCLUDED_


template <typename T>
class SensorNet{

	Array<Sensor<Data<T>>> * sensor_arr=NULL;
	size_t len;
	Sensor<Data<T>> sensor_prom;
	sensornet_state_t state = VALID_DATA;

	public:

	SensorNet();
	SensorNet(Array<string>& ,size_t);
	~SensorNet();

	void SetLen(size_t);
	size_t GetLen() const;
	
	sensornet_state_t GetData(istream &,char);

	sensornet_state_t GetState();

	void CreateSensorProm();
	const Sensor<Data<T>> & GetSensorProm()const;	

	Sensor<Data<T>> & operator[](const size_t &);
	Sensor<Data<T>> const & operator[](const size_t &)const;

};


/***************************************** Metodos de Clase ***************************************/
template <typename T>
SensorNet<T>::SensorNet(){}

template <typename T>
SensorNet<T>::SensorNet(Array<string> &string_array,size_t s_len)
{

	if(!s_len){

		state = EMPTY_DATA;
		return;
	}
	sensor_arr = new Array<Sensor<Data<T>>>(s_len);
	for(size_t i=0;i<s_len;i++){
		for(size_t j=0;j<i;j++){
			if(string_array[j]==string_array[i]){
				delete sensor_arr;
				state = REPEATED_SENSOR;
				len=0;
				return;
			}

			if(string_array[i].empty()){
				delete sensor_arr;
				state = MISSING_SENSOR;
				len = 0;
				return;
			}	
		}
		(*sensor_arr)[i].SetID(string_array[i]);
	}

	len = s_len;
	state = VALID_DATA;
}

template <typename T>
SensorNet<T>::~SensorNet(){if(sensor_arr)delete sensor_arr;}

template <typename T>
void SensorNet<T>::SetLen(size_t new_len){len = new_len;}

template <typename T>
size_t SensorNet<T>::GetLen() const{return len;}

template <typename T>
void SensorNet<T>::CreateSensorProm(){

	if(!sensor_arr) return;

	size_t sensor_len = (*sensor_arr)[0].GetLength();

	for(size_t i=0;i<sensor_len;i++){
		Data<T> aux = 0.0;
		size_t count=0;
		for(size_t j=0;j<len;j++){
				aux = aux + (((*sensor_arr)[j])[i]);
				if((*sensor_arr)[j][i].GetState()) count++;
		}
		if(count)
			aux = aux/(T)count;
		else aux.DisableData();
		sensor_prom.push_back(aux);   //Se valido si algun sensor tiene algun dato en esa posicion
	
	}
}

template <typename T>
const Sensor<Data<T>> & SensorNet<T>::GetSensorProm()const{return sensor_prom;}


template <typename T>
sensornet_state_t SensorNet<T>::GetData(istream & infile,char delimiter){

	extern rmq_mode_t rmq_mode;
	Data<T> aux_data;
	size_t i=0,count=0;
	char ch;
	string str;
	stringstream str_st;
	bool good = false;
	bool bad = false;
	
	if(state) return state;

	while(getline(infile,str)){

		if(str.back() == '\r')         //En caso que el archivo venga de Windows lo limpio antes de 
			str.pop_back();        //trabajar con la string

		if(!str.empty()){

			stringstream str_st (str);

			while(i<len){
				 	
				if(str_st >> ch && ch == delimiter){

					aux_data.SetData(0); //limpio data con un valor por default
					aux_data.DisableData();
					good = true;
				}

				
				else if(!isdigit(ch) && ch!=delimiter && ch!='-'){
					
					state = INVALID_DATA;
					return state;
				}
				
				else{

					str_st.putback(ch);
						
					if(str_st >> aux_data){
		
							aux_data.EnableData();
							good = true;

					}
					str_st >> ch;
				}

				if(good == false && i==len-1 && ch == delimiter){
						aux_data.SetData(0); //limpio data con un valor por default
						aux_data.DisableData();
						good = true;
				}

				else {
					state = MISSING_DATA;
					bad = true;
				}		
			
				if(!isdigit(ch) && ch!=delimiter && ch!= '-'){
					
					state = INVALID_DATA;
					bad = true;
				}
				
						 
				if(good) {(*sensor_arr)[i].push_back(aux_data);count++;}

				else if(bad){
					
					return state;
				}
				i++;
				good = false;
				bad = false;
			}
			if(str_st >> ch){

					state = EXTRA_DATA;
					return state;
			}

			i = 0;
			str.clear();
		}
	}

	CreateSensorProm();

	if(rmq_mode == rmq_segtree){

			for(size_t j=0;j<len;j++)					
				(*sensor_arr)[j].CreateSegTree();

			sensor_prom.CreateSegTree();
	}

	state = VALID_DATA;
	return state;	

}

template <typename T>
sensornet_state_t SensorNet<T>::GetState(){return state;}

template <typename T>
Sensor<Data<T>> & SensorNet<T>::operator[](const size_t & i){return (*sensor_arr)[i];}

template <typename T>
Sensor<Data<T>> const & SensorNet<T>::operator[](const size_t & i)const{return (*sensor_arr)[i];}


#endif
