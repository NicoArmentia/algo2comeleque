#include <iostream>
#include "Array.h"
#include <limits>

using namespace std;

int main(void)
{

	Array<int> arr;
	Array<int> aux_arr;
	int aux;
	char c;
	size_t index;

	cout << "TEST MODE: ARRAY" << endl;
	cout << "P: print, A: add, U: used length, T: total length, C: clear, I: index, K: copy" << endl;

	while(cin >> c){

		switch(c){

			case 'P': //print
				
				cout << "Print" << endl;
				cout << arr << endl;
				break;

			case 'A': //add

				cout << "Add" << endl;
				cout << "Insert value" << endl;
				cin >> aux;
				arr.push_back(aux);
				break;
			
			case 'U': //used length

				cout << "Used Length" << endl;
				cout << arr.GetUsedLen() << endl;
				break;

			case 'T': //total length

				cout << "Used Length" << endl;
				cout << arr.GetUsedLen() << endl;
				break;

			case 'C': //clear

				cout << "Clear" << endl;
				arr.clear();
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
				if(index > arr.GetUsedLen()){
					cerr << "Invalid Position" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					break;
				}
				cout << "Arr[" << index << "]: " << arr[index] << endl;
				break;

			case 'K': //copy

				cout << "Copy" << endl;
				cout << "Insert array" << endl;
				if(!(cin >> aux_arr)){
					cerr << "Invalid Array" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					break;
				}
				arr = aux_arr;
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


