#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include "RedSensores.h"

using namespace std;

int print_file(ifstream &);

int main(void)
{
	ifstream infile; 
	Array<Sensor<Data<double>>> * red;
	string * string_array;
	size_t	 len;
	size_t i;

   	infile.open("/home/julian/Desktop/Algo II/TP0/data.txt",ios::in);

	ParseString(infile,&string_array,&len,',');
	
	cout << "---------------------String Array---------------------" << endl;
	for(i=0;i<len;i++) cout << string_array[i] << endl;


	cout << "----------------CreateFromIDArray---------------------" << endl;

	CreateFromIDArray(red,string_array,len);


	cout << "---------------------Sensor Array---------------------" << endl;
	for(i=0;i<len;i++) cout << (*red)[i].GetID() << endl;

	
	cout << "-----------------------Get data-----------------------" << endl;
	get_data(infile,red,',',len);


	cout << "---------------------Data vectors---------------------" << endl;
	for(i=0;i<len;i++) cout << (*red)[i].GetArray() << endl;


	infile.close();

	return 0;
}



/************************************ DEFINICION DE FUNCIONES *****************************************/

int print_file(ifstream & infile){

	int data;

	infile >> data;

	while(!infile.eof())
	{
		cout << data << endl;
		infile >> data;
	}

	return 0;
}


