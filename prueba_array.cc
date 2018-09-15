#include <iostream>
#include "Sensor.h"
#include "array.h"

using namespace std;

int main(void){
	double a = 3.0;
	Array<double> pepito;	//Array()
	pepito.push_back(a);	//pushback
	Array<double> caca = pepito;	//Array(Array<T> &)
	Array<double> * juan = new Array<double>();	
	size_t pepe = juan->GetTotalLen() + 1;
	for(size_t i=0;i<pepe;i++){
		cout << "ingresa numero cagasaurio\n";
		cin >> a;
		(*juan).push_back(a); //(*juan)[i] = a;
		cout << (*juan)[i] << endl;
		i++;
		juan->push_back(a); // juan[i] no funciona, me escribe en cualquier lugar
	}
	Array<double> munieco[3];
	Array<double> disney(14);
	munieco[1] = disney;
	Array<double> orlando(*juan);
	cout<<orlando<<'\n';
	cout<<(orlando==(*juan))<<'\n';
	cout<<(orlando!=pepito)<<'\n';
	orlando.clear();
	cout<<(orlando==(*juan))<<'\n';
	delete juan;
	return 0;
}
