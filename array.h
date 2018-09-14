#include <cassert>
#include <iostream>
#include <stdio.h>
#include <cstdlib>

using namespace std;

#ifndef _ARRAY_H_INCLUDED_
#define _ARRAY_H_INCLUDED_

#define DEFAULT_LEN 10

template <class T>
class Array
{
	int total_len;
	int used_len;
	T * p;
public:

	Array();
	Array(int);
	Array(const Array<T> &); 
	~Array();
	int GetTotalLen() const;
	int GetUsedLen() const; 
	Array<T>&operator=( const Array<T> & ); 
	T &operator[](int);
	void print();
};

template <class T>
Array<T>::Array(){

	used_len = 0;
	total_len = DEFAULT_LEN;
	p = new T[total_len];
}

template <class T>
Array<T>::Array(int t){

	total_len = t;
	used_len = 0;
	p = new T[total_len];
}

template <class T>
Array<T>::Array(const Array<T> & a_init){

	int i;
	
	total_len = a_init.GetTotalLen();
	used_len = a_init.GetUsedLen();
	
	p = new T[total_len];

	for(i=0;i<used_len;i++)
		p[i]=(a_init.p)[i];

}

template <class T>
Array<T>::~Array(){

	delete []p;
}

template <class T>
int Array<T>::GetUsedLen() const { return used_len; }

template <class T>
int Array<T>::GetTotalLen() const { return total_len; }


template <class T>
T & Array<T>::operator [](int pos){

	return p[pos];
}

template <class T>
void Array<T>::print(){
	for(int i=0;i<3;i++){
		cout << p[i] << endl;
	}
}

#endif
