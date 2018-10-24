#include <cassert>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

typedef enum {rmq_standard=0,rmq_segtree=1} rmq_mode_t;

typedef enum {OK=0,BAD_QUERY=1,NO_DATA=2,UNKNOWN_ID=3} qstate_t;

static string State_Dict[4] = {"OK","BAD_QUERY","NO_DATA","UNKNOWN_ID"};
