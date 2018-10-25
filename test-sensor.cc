#include <iostream>
#include "Sensor.h"
#include <limits>

using namespace std;

int main(void)
{

	Sensor<double> sensor;
	string st;
	double data;
	char c;
	size_t index;

	cout << "TEST MODE: SENSOR" << endl;
	cout << "P: print, S: set ID, D: set data, A: append, L: get length, C: clear, I: index" << endl;

	while(cin >> c){

		switch(c){

			case 'P': //print

				cout << "Print" << endl;
				cout << "ID: " << sensor.GetID() << endl;
				cout << "Data: " << sensor.GetArray() << endl;
				break;

			case 'S': //set id

				cout << "Set ID" << endl;
				cout << "Insert ID" << endl;
				cin >> st;
				sensor.SetID(st);
				break;

			case 'D': //set data

				cout << "Set Data" << endl;
				cout << "Insert Data" << endl;
				cin >> data;
				cout << "Insert Index" << endl;
				if(!(cin >> index)){
					cerr << "Invalid Index" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					break;
				}
				if(index > sensor.GetLength()){
					cerr << "Invalid Position" << endl;
					break;
				}
				sensor.SetData(data,index);
				break;

			case 'A': //append

				cout << "Append Data" << endl;
				cout << "Insert Data" << endl;
				cin >> data;
				sensor.push_back(data);
				break;

			case 'L': //get length

				cout << "GetLength" << endl;
				cout << "Length: " << sensor.GetLength() << endl;
				break;

			case 'C': //clear

				cout << "Clear" << endl;	
				sensor.clear();
				break;

			case 'I': //index

				cout << "Index" << endl;
				cout << "Insert index" << endl;
				if(!(cin >> index)){
					cerr << "Invalid Index" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					break;
				}
				if(index > sensor.GetLength()){
					cerr << "Invalid Position" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					break;
				}
				cout << "DataArr[" << index << "]: " << sensor[index] << endl;
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
