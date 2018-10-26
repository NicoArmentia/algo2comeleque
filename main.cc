#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <ctime>	// Para probar cuanto tarda cada prueba

#include "Sensor.h"
#include "RedSensores.h"
#include "Query.h"
#include "Array.h"
#include "cmdline.h"
#include "cmdline.cc"
#include "help.h"
#include "types.h"

#define DBG(x) cerr << #x << ":" << (x) << endl
#define DELIMITER ','

using namespace std;


static void opt_data(string const &arg);
static void opt_input(string const &arg);
static void opt_output(string const &arg);
static void opt_mode(string const &arg);
static void opt_help(string const &arg);

static option_t options[] = {
	{1, "d", "data" , "-" , opt_data , OPT_MANDATORY},
	{1, "i", "input" , "-" , opt_input , OPT_DEFAULT},
	{1, "o", "output" , "-" , opt_output , OPT_DEFAULT},
	{1, "m", "mode" , "-" , opt_mode , OPT_DEFAULT},
	{0, "h", "help" , "-" , opt_help , OPT_DEFAULT},
	{0, }
};

rmq_mode_t rmq_mode;
static ifstream dfs;
static istream * data_stream = 0;
static ifstream ifs;
static istream * input_stream = 0;
static ofstream ofs;
static ostream * output_stream = 0;

static void opt_data(string const &arg){
	dfs.open(arg.c_str(),ios::in);
	data_stream = &dfs;
	if(!data_stream->good()){
		cerr << "Error al abrir el archivo " << arg << endl;
		exit(1);
	}
}
static void opt_input(string const &arg){
	if(arg == "-"){
		input_stream = &cin;
	}
	else{
		ifs.open(arg.c_str(), ios::in);
		input_stream = &ifs;
	}

	if(!input_stream->good()){
		cerr << "Error al abrir archivo " << arg << endl;
		exit(1);
	}
}
static void opt_output(string const &arg){
	if(arg == "-"){
		output_stream = &cout;
	}
	else{
		ofs.open(arg.c_str(), ios::out | ios::app);
		output_stream = &ofs;
	}
	if(!output_stream->good()){
		ofs.open(arg.c_str(), ios::out | ios::trunc);
		output_stream = &ofs;
	}
}
static void opt_mode(string const &arg){
	if(arg == "-") rmq_mode = rmq_standard;
	else if(arg == "linear") rmq_mode = rmq_standard;
	else if(arg == "tree") rmq_mode = rmq_segtree;
}
static void opt_help(string const &arg){
	if(arg == "-"){
	}
	else{
		cout << PROGRAM_HELP;
		cout << DATA_OPT_HELP;
		cout << DATA_OPT_EXP;
		cout << INPUT_OPT_HELP;
		cout << INPUT_OPT_EXP;
		cout << OUTPUT_OPT_HELP;
		cout << OUTPUT_OPT_EXP;
		cout << MODE_OPT_HELP;
		cout << MODE_OPT_EXP;
	}
}


/*********************************************** MAIN *************************************************/

int main(int argc, char * const argv[])
{
	cmdline cmdl(options);
	Array<Query<double>> queryx;
	Array<string> string_array;
	size_t len;

	
	cmdl.parse(argc, argv);

	string_array.ParseString(*data_stream,DELIMITER);
	len = string_array.GetUsedLen();	

	//cout << "---------------------String Array---------------------" << endl;
	//for(size_t k=0;k<len;k++) cout << string_array[k] << endl;


	//cout << "----------------CreateFromIDArray---------------------" << endl;

	SensorNet<double> red(string_array,len);

	//cout << "---------------------Sensor Array---------------------" << endl;
	//for(i=0;i<len;i++) cout << (*red)[i].GetID() << endl;

	
	//cout << "-----------------------Get data-----------------------" << endl;
	if(red.GetData(*data_stream,DELIMITER)){
		dfs.close();
		ifs.close();
		ofs.close();
		cerr << "INVALID DATABASE" << endl;
		return 1;
	}
		

	//cout << "---------------------Data vectors---------------------" << endl;
	//for(i=0;i<len;i++) cout << (*red)[i].GetArray() << endl;

	//cout << "--------------------- Get Query ---------------------" << endl;

	clock_t time_init;
	clock_t time_fin;

	time_init = clock();
	GetQuery(*input_stream,red,DELIMITER,*output_stream);
	time_fin = clock();
	if (time_init == ((clock_t)-1) || time_fin == ((clock_t)-1)){
		cerr << "Unable to calculate elapsed time" << endl;
	}
	else{
		size_t total_time_ticks = (size_t)(time_fin - time_init);
		cout << "Query execution time : " << 1e6*total_time_ticks/CLOCKS_PER_SEC << " [us]" << endl;
	}



	dfs.close();
	ifs.close();
	ofs.close();

	return 0;
}





