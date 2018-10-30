#include <cassert>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

#ifndef _TYPES_H_INCLUDED_
#define _TYPES_H_INCLUDED_

typedef enum {rmq_standard=0,rmq_segtree=1} rmq_mode_t;

typedef enum {OK=0,INVALID_REQUEST=1,NO_DATA=2,UNKNOWN_ID=3,INVALID_INDEX=4,INVALID_INTERVAL=5,EMPTY_INTERVAL=6} qstate_t;

typedef enum {VALID_DATA=0,INVALID_DATA=1,EMPTY_DATA=2,REPEATED_SENSOR=3,MISSING_SENSOR=4,EXTRA_DATA=5,MISSING_DATA=6} sensornet_state_t;

static string State_Dict[] = {"OK","INVALID_REQUEST","NO_DATA","UNKNOWN_ID","INVALID INDEX","INVALID INTERVAL","EMPTY INTERVAL"};

static string SNet_State_Dict[] = {"OK","INVALID DATA BASE","EMPTY DATA BASE",
				"DUPLICATED SENSOR ID","MISSING SENSOR","EXTRA DATA","MISSING DATA"};

#endif
