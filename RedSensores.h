#include <cassert>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "Array.h"
#include "Sensor.h"
#include "Data.h"

using namespace std;

#ifndef _REDSENSORES_H_INCLUDED_
#define _REDSENSORES_H_INCLUDED_


template <typename T>
class SensorNet{

	Array<Sensor<Data<T>>> * sensor_arr;
	size_t len;

	public:

	SensorNet();
	SensorNet(Array<string>& ,size_t);
	~SensorNet();

	void SetLen(size_t);
	size_t GetLen() const;
	
	int GetData(istream &,char);	

	Sensor<Data<T>> & operator[](const size_t &);
	Sensor<Data<T>> const & operator[](const size_t &)const;


};


/***************************************** Metodos de Clase ***************************************/
template <typename T>
SensorNet<T>::SensorNet(){}

template <typename T>
SensorNet<T>::SensorNet(Array<string> &string_array,size_t s_len)
{

	sensor_arr = new Array<Sensor<Data<T>>>(s_len);
	
	for(size_t i=0;i<s_len;i++)
		(*sensor_arr)[i].SetID(string_array[i]);

	len = s_len;
}

template <typename T>
SensorNet<T>::~SensorNet(){delete sensor_arr;}

template <typename T>
void SensorNet<T>::SetLen(size_t new_len){len = new_len;}

template <typename T>
size_t SensorNet<T>::GetLen() const{return len;}

template <typename T>
int SensorNet<T>::GetData(istream & infile,char delimiter){

	extern rmq_mode_t rmq_mode;
	Data<T> aux_data;
	size_t i=0;
	char ch;
	string str;
	stringstream str_st;
	bool good = false;
	bool bad = false;

	while(getline(infile,str)){

		if(str.back() == '\r')         //En caso que el archivo venga de Windows lo limpio antes de 
			str.pop_back();        //trabajar con la string

		stringstream str_st (str);

		while(i<len){
			 	
			if(str_st >> ch && ch == delimiter){

				aux_data.SetData(0); //limpio data con un valor por default
				aux_data.DisableData();
				good = true;
				cout << "sin datos" << endl;
			}

			
			else{

				str_st.putback(ch);
					
				if(str_st >> aux_data){
	


						aux_data.EnableData();
						good = true;

				}
			}

			if(good == false && i==len-1){

					aux_data.SetData(0); //limpio data con un valor por default
					aux_data.DisableData();
					good = true;
					cout << "sin datos" << endl; 
			}

			else bad = true;

			str_st >> ch;
					 
			if(good) (*sensor_arr)[i].push_back(aux_data);

			else if(bad){ 
				cout << "NO DATA" << endl;
				return 1;
			}	

			if(rmq_mode = rmq_segtree)
				(*sensor_arr)[i].CreateSegTree();

			i++;
			good = false;
			bad = false;
		}

		i = 0;
		str.clear();
	}

	return 0;	

}

template <typename T>
Sensor<Data<T>> & SensorNet<T>::operator[](const size_t & i){return (*sensor_arr)[i];}

template <typename T>
Sensor<Data<T>> const & SensorNet<T>::operator[](const size_t & i)const{return (*sensor_arr)[i];}


#endif
