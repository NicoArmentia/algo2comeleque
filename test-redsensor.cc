#include <cassert>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "Array.h"
#include "Sensor.h"
#include "Data.h"
#include "RedSensores.h"
#include <limits>

using namespace std;

int main(void)
{

/**************************** Apertura de archivo **********************************/

	string s_file = "/home/julian/Documents/TP1/data.txt";
	static ifstream dfs;
	static istream * data_stream = 0;

	dfs.open(s_file,ios::in);
	data_stream = &dfs;
	if(!data_stream->good()){
		cerr << "Error al abrir el archivo " << s_file << endl;
		exit(1);
	}

/******************* Declaracion de datos necesarios para test ********************/

	size_t index,i;
	size_t len;
	char c;	
	Array<string> string_array;

	string_array.ParseString(*data_stream,',');
	len = string_array.GetUsedLen();

	SensorNet<double> red(string_array,len);
	red.GetData(*data_stream,',');
	

	cout << "TEST MODE: SENSORNET" << endl;
	cout << "P: Print, D: Get Data, I: Get ID, L: Get Length, S: Sensor Prom" << endl;

	while(cin >> c){

		switch(c){

			case 'P': 
				cout << "Print" << endl;
				for(i=0;i<len;i++)
					cout << "SensorNet[" << i << "]: " << 
						red[i].GetID() << ": " << red[i].GetArray() << endl;
				break;

			case 'D':
				cout << "Get Data" << endl;

				cout << "Insert index" << endl;
				if(!(cin >> index)){
					cerr << "Invalid Index" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					break;
				}
				if(index > len){
					cerr << "Invalid Position" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					break;
				}
				cout << "SensorNet[" << index << "]: " << red[index].GetArray() << endl;
				break;

			case 'I':
				cout << "Get ID" << endl;

				cout << "Insert index" << endl;
				if(!(cin >> index)){
					cerr << "Invalid Index" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					break;
				}
				if(index > len){
					cerr << "Invalid Position" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					break;
				}
				cout << "SensorNet[" << index << "]: "  << red[index].GetID() << endl;
				break;

			case 'L': 
				cout << "Get Length" << endl;
				cout << len << endl;
				break;

			case 'S':
				cout << "Sensor Prom" << endl;
				cout << (red.GetSensorProm()).GetArray() << endl;
				break;

			default: 

				cerr << "Error: unknown command (";
				cerr << c;
				cerr << ")";
				cerr << endl;
				break;
		}
	}

	cout << "TEST MODE FINISHED" << endl;

	return 0;
}
