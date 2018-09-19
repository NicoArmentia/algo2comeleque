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
	Array<Sensor<double>> * red;
	string * string_array;
	size_t	 len;
	size_t i,j;
	int check;
	/*double datos[3][3];
	char ch;*/

   	infile.open("/home/julian/Desktop/Algo II/TP0/data.txt",ios::in);

	ParseString(infile,&string_array,&len,',');
	
	cout << "---------------------String Array---------------------" << endl;
	for(i=0;i<len;i++) cout << string_array[i] << endl;
	cout << "------------------------------------------------------" << endl;


	cout << "----------------CreateFromIDArray---------------------" << endl;

	CreateFromIDArray(red,string_array,len);

	cout << "------------------------------------------------------" << endl;

	cout << "---------------------Sensor Array---------------------" << endl;
	for(i=0;i<len;i++) cout << (*red)[i].GetID() << endl;
	cout << "------------------------------------------------------" << endl;
	
	cout << "-----------------------Get data-----------------------" << endl;
	get_data(infile,red,',',len);
	cout << "------------------------------------------------------" << endl;

	cout << "---------------------Data vectors---------------------" << endl;
	for(i=0;i<len;i++) cout << (*red)[i].GetArray() << endl;
	cout << "------------------------------------------------------" << endl;

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



/*****************************  ALMACENAMIENTO DE DATOS  ************************************/

/*int get_data(ifstream & infile,double string_vector[][3],char delimiter,int len)
{

	char ch;
	bool bad = false;
	bool good = false;
	bool endline = false;
	double data;
	int i=0;
	int j=0;


	while(!infile.eof()){


		if(i == len) return 0;		
	
		if(infile >> data)
		{
			if(infile >> ch && ch == delimiter)
				good = true;

			else if(infile.good()){
				infile.putback(ch);				
				endline =true;
				good=true;
			}
		}
		
		else bad = true;

		if(good)
			 string_vector[i][j] = data;	
					
		if(bad){
			 cout << "NO DATA" << endl;
			 return 1;
		}
			 
		j++;
		
		if(endline == true){
			
			i++;
			j=0;
			endline = false;
		}
	}

	return 0;
}*/

