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


/************************************** Almacenamiento de IDs *************************************/

int ParseString(ifstream & infile,string ** string_array,size_t * len,char delimiter)
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

	*len = delimit_number+1;

	*string_array = new string[*len];

	infile.seekg(0, ios::beg);

	for(i=0;i<(*len)-1;i++)
		getline(infile,(*string_array)[i],delimiter);

	getline(infile,(*string_array)[i]);

	return 0;
}

template <class T>
int CreateFromIDArray(Array<Sensor<T>> * & red,string * string_array,size_t len)
{

	red = new Array<Sensor<T>>(len);
	
	for(size_t i=0;i<len;i++)
		(*red)[i].SetID(string_array[i]);

	return 0;
}

/*****************************  ALMACENAMIENTO DE DATOS  ************************************/
template <class T>
int get_data(ifstream & infile,Array<Sensor<Data<T>>> * sensor_arr,char delimiter,size_t len)
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

		while(!str_st.eof()){
			 	
			if(str_st >> ch && ch == delimiter){

				aux_data.SetData(0); //limpio data con un valor por default
				aux_data.DisableData();
				good = true;
				cout << "sin datos" << endl;
			}


			else{
				str_st.putback(ch);
					
				if(str_st >> aux_data){
					
					cout << "dato leido: " << aux_data << endl;


						aux_data.EnableData();
						good = true;

				}

				else bad = true;
				str_st >> ch;
			}
					 

			if(good) (*sensor_arr)[i].push_back(aux_data); 

			if(bad){ 
				cout << "NO DATA" << endl;
				return 1;
			}	

			i++;
		}

		i = 0;
		str.clear();
	}

	return 0;	

}

/*******************************  QUERY  **************************************/
/*
template <class T>
int get_data(ifstream & infile,Array<Sensor<Data<T>>> * sensor_arr,char delimiter,size_t len)
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

		while(str_st >> aux_data){
			 
	
			if(str_st.eof()){
				if (i != len-1)
					bad = true;

				else{
					good = true;
					aux_data.EnableData();
				}
			}

			else if(str_st >> ch && ch == delimiter){

				aux_data.EnableData();
				good = true;
			}
					 
			else bad = true;

			if(good) (*sensor_arr)[i].push_back(aux_data); 

			if(bad){ 
				cout << "NO DATA" << endl;
				return 1;
			}	

			i++;
		}

		i = 0;
		str.clear();
	}

	return 0;	

}
*/
#endif
