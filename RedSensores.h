#include <cassert>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "Array.h"
#include "Sensor.h"
#include "Data.h"
#include "Query.h"

using namespace std;

#ifndef _REDSENSORES_H_INCLUDED_
#define _REDSENSORES_H_INCLUDED_


/************************************** Almacenamiento de IDs *************************************/

int ParseString(istream & infile,Array<string> * & string_array,size_t & len,char delimiter)
{

	size_t i=0;
	size_t delimit_number=0;
	string aux;

	getline(infile,aux);

	while(aux[i]!='\0')
	{

		if(aux[i]==delimiter)
			delimit_number++;
		i++;
	}

	len = delimit_number+1;

	string_array = new Array<string>(len);

	infile.seekg(0, ios::beg);

	for(i=0;i<len-1;i++)
		getline(infile,(*string_array)[i],delimiter);

	getline(infile,(*string_array)[i]);

	return 0;
}

template <class T>
int CreateFromIDArray(Array<Sensor<T>> * & red,const Array<string> & string_array,size_t len)
{

	red = new Array<Sensor<T>>(len);
	
	for(size_t i=0;i<len;i++)
		(*red)[i].SetID(string_array[i]);

	return 0;
}

/*****************************  ALMACENAMIENTO DE DATOS  ************************************/
template <class T>
int get_data(istream & infile,Array<Sensor<Data<T>>> * sensor_arr,char delimiter,size_t len)
{

	Data<T> aux_data;
	size_t i=0;
	char ch;
	string str;
	stringstream str_st;
	bool good = false;
	bool bad = false;

	while(getline(infile,str)){

		stringstream str_st (str);

		while(i<len){
			 	
			if(str_st >> ch && ch == delimiter){

				aux_data.SetData(0); //limpio data con un valor por default
				aux_data.DisableData();
				good = true;
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
			}

			else bad = true;

			str_st >> ch;
					 
			if(good) (*sensor_arr)[i].push_back(aux_data);

			else if(bad){ 
				cerr << "Invalid data base" << endl;
				return 1;
			}	

			i++;
			good = false;
			bad = false;
		}

		i = 0;
		str.clear();
	}

	return 0;	

}

/*******************************  QUERY  **************************************/
template <typename T>
int get_query_arr(istream & infile,Array<Query<T>> & query_arr,const Array<Sensor<Data<T>>> & sensor_arr,size_t * qlen,char delimiter)
{

	string str;
	size_t i=0,j=0;
	Query<T> aux_query;
	size_t position;
	bool ID_found;
	Array<Array<Data<T>>> * aux_arr;
	size_t aux_len = sensor_arr.GetTotalLen();

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
