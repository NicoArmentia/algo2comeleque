#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include "RedSensores.h"

using namespace std;

int print_file(ifstream &);

int main(void)
{
	ifstream infile,infile2; 
	Array<Sensor<Data<double>>> * red;
	Array<Query<double>> queryx;
	string * string_array;
	size_t len,len_q;
	size_t i;
	string ID;
	size_t init,fin,valid_data;

   	infile.open("/home/julian/Desktop/Algo II/TP0/data.txt",ios::in);
	infile2.open("/home/julian/Desktop/Algo II/TP0/query.txt",ios::in);

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

	cout << "--------------------- Get Query ---------------------" << endl;

	get_query_arr(infile2,&queryx,*red,&len_q,',');
	cout << "Query arr length: " << len_q << endl;

	ID = (queryx[0]).GetID();
	init = (queryx[0]).GetInitPos();
	fin = (queryx[0]).GetFinPos();
	valid_data = (queryx[0]).GetDataNum();
	cout << "ID: " << ID << endl;   
	cout << "Initial Position: " << init << endl;
	cout << "Final Position: " << fin << endl;
	cout << "Number of valid data: " << valid_data << endl;
	cout << State_Dict[queryx[0].GetState()] << endl;

	size_t qdata_len = queryx[0].GetLength();
	cout << "qdata_arr len: " << qdata_len << endl;

	cout << "data query: " << queryx[0] << endl;
	
	infile.close();
	infile2.close();

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



