#include <iostream>
#include "Data.h"
#include <limits>

using namespace std;

int main(void){


	Data<double> data;
	Data<double> aux;
	double d;
	bool state;
	char c;
	

	cout << "TEST MODE: DATA" << endl;
	cout << "E: enable, D: disable, N: new data, S: get state, G: get data P: print data" << endl;

	while(cin >> c){

		switch(c){

			case 'E': //enable data

				cout << "Enable Data" << endl;
				data.EnableData();
				break;
	
			case 'D':

				cout << "Disable Data" << endl;
				data.DisableData();
				break;

			case 'S': //get state

				cout << "State" << endl;
				state = data.GetState();
				if(state) cout << "Enabled" << endl;
				else cout << "Disabled" << endl;
				break;

			case 'G': //get data
	
				cout << "Data" << endl;
				cout << data.GetData() << endl;
				break;

			case 'N': //set data

				cout << "New Data" << endl;
				cout << "Insert Value" << endl;
				cin >> d;
				data.SetData(d);
				cout << "Insert State: 0:disabled, 1:enabled" << endl;
				cin >> d;
				if(!d) data.DisableData();
				else if(d==1) data.EnableData();
				else{
					cerr << "Invalid State" << endl;
					break;
				}
				break;

			case 'P': //print data
				
				cout << "Print Data" << endl;
				cout << "Data: " << data.GetData() << endl;
				state = data.GetState();
				if(state) cout << "State: " << "Enabled" << endl;
				else cout << "State: " << "Disabled" << endl;
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
