#include <cassert>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "Array.h"

using namespace std;

#ifndef _ARRAY_H_INCLUDED_
#define _ARRAY_H_INCLUDED_

typedef enum {OK,BAD_QUERY,NO_DATA,UNKNOWN_ID} qstate_t;

template <typename T>
class Query{

	string IDs;
	size_t init_pos;
	size_t fin_pos;
	T min;
	T max;
	T prom;
	qstate_t state;

public:

	Query();
	Query(const string * &);
	Query(const string * &,size_t,size_t);  

	SetID
	GetID
	
};



#endif
