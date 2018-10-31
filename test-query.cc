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
#include "types.h"
#include "Query.h"

#define DELIMITER ','
#define ERR_DATA_PREFIX "ERROR DATA BASE: "

using namespace std;

rmq_mode_t rmq_mode = rmq_segtree;

int main(void)
{

/**************************** Apertura de archivo **********************************/

	string data_file = "/home/julian/Documents/TP1/data.txt";
	static ifstream dfs;
	static istream * data_stream = 0;

	dfs.open(data_file,ios::in);
	data_stream = &dfs;
	if(!data_stream->good()){
		cerr << "Error al abrir el archivo " << data_file << endl;
		exit(1);
	}


	string query_file = "/home/julian/Documents/TP1/query.txt";
	static ifstream qfs;
	static istream * query_stream = 0;

	qfs.open(query_file,ios::in);
	query_stream = &qfs;
	if(!query_stream->good()){
		cerr << "Error al abrir el archivo " << query_file << endl;
		exit(1);
	}

	ostream * out_stream = &cout;

/******************* Declaracion de datos necesarios para test ********************/

	size_t len;
	char c;	
	Array<string> string_array;
	string aux_string;
	sensornet_state_t state;

	string_array.ParseString(*data_stream,',');
	len = string_array.GetUsedLen();

	SensorNet<double> red(string_array,len);

	if((state = red.GetData(*data_stream,DELIMITER))){

			dfs.close();
			qfs.close();
			cerr << ERR_DATA_PREFIX << SNet_State_Dict[state] << endl;
			return 1;
	}

	cout << "TEST MODE: QUERY" << endl;
	cout << "F: Print from File, C: Print from Console" << endl;

	while(cin >> c){

		switch(c){

			case 'F':
				cout << "Print Query from File" << endl;
				GetQuery(*query_stream,red,DELIMITER,out_stream);
				break;

			case 'C':{
				cout << "Print Query from Console" << endl;
				cout << "Insert Query manually" << endl;
				cin >> aux_string;
				stringstream str_st(aux_string);

				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				GetQuery(str_st,red,DELIMITER,out_stream);
				break;}

			default: 
				cerr << "Error: unknown command (";
				cerr << c;
				cerr << ")";
				cerr << endl;
				break;

		}

	}

	cout << "TEST MODE FINISHED" << endl;

	dfs.close();
	qfs.close();

	return 0;

}



