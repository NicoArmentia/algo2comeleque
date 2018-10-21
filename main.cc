#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>

#include "SegTree.h"
#include "Sensor.h"
#include "RedSensores.h"
#include "Query.h"
#include "Array.h"
#include "cmdline.h"
#include "cmdline.cc"
#include "help.h"

#define DBG(x) cerr << #x << ":" << (x) << endl
#define DELIMITER ','

/*

#define PROGRAM_HELP " This program takes a data file with sensor IDs and a data set from every sensor. The data file is defined with its respective command line argument and is mandatory. It then displays in an output file the minimum, maximum and mean values taken from a subset of the data, defined in the input file.\n The list and explanation of the command line argument options follows:\n short name | long name |  \n"

#define DATA_OPT_HELP "\n\t | -d \"_\" | --data \"_\" | MANDATORY \n\n"
#define DATA_OPT_EXP " The data file must be a CSV file containing the sensor IDs on the first line, and the corresponding  data set of every sensor on the same column. A missing value on the data set will not terminate the program.\n The data file must have the following format:\n SENSOR1ID,SENSOR2ID,...,SENSORNID\nSENSOR1DATA1,SENSOR2DATA1,...,SENSORNDATA1\n...\n"

#define INPUT_OPT_HELP "\n\t | -i \"_\" | --input \"_\" | DEFAULT = cin \n\n"
#define INPUT_OPT_EXP " The input file must be a CSV file containing a query that specifies which subset of the data should be used to obtain the minimum, maximum and mean. If not specified the standard input stream is taken as the input file for the program. \n The input file must have the following format:\n SENSOR_ID,INITIAL_POS,FINAL_POS\n...\n"

#define OUTPUT_OPT_HELP "\n\t | - o \"_\" | --output \"_\" | DEFAULT = cout \n\n"
#define OUTPUT_OPT_EXP " The data file must be a CSV file containing the sensor IDs on the first line, and the corresponding  data set of every sensor on the same column. A missing value on the data set will not terminate the program.\n The data file must have the following format:\n SENSOR1ID,SENSOR2ID,...,SENSORNID\nSENSOR1DATA1,SENSOR2DATA1,...,SENSORNDATA1\n...\n"

*/

using namespace std;




static void opt_data(string const &arg);
static void opt_input(string const &arg);
static void opt_output(string const &arg);
static void opt_help(string const &arg);

static option_t options[] = {
	{1, "d", "data" , "-" , opt_data , OPT_MANDATORY},
	{1, "i", "input" , "-" , opt_input , OPT_DEFAULT},
	{1, "o", "output" , "-" , opt_output , OPT_DEFAULT},
	{0, "h", "help" , "-" , opt_help , OPT_DEFAULT},
	{0, }
};

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
	}
}


/*********************************************** MAIN *************************************************/

int main(int argc, char * const argv[])
{
	cmdline cmdl(options);
	Array<Query<double>> queryx;
	Array<string> * string_array;
	size_t len;
	size_t len_q;
	/*string ID;
	size_t i;
	size_t init,fin,valid_data;*/

	
	cmdl.parse(argc, argv);

	ParseString(*data_stream,string_array,len,DELIMITER);
	
	//cout << "---------------------String Array---------------------" << endl;
	//for(size_t k=0;k<len;k++) cout << (*string_array)[k] << endl;


	//cout << "----------------CreateFromIDArray---------------------" << endl;

	SensorNet<double> red(*string_array,len);

	//cout << "---------------------Sensor Array---------------------" << endl;
	//for(i=0;i<len;i++) cout << (*red)[i].GetID() << endl;

	
	//cout << "-----------------------Get data-----------------------" << endl;
	red.GetData(*data_stream,DELIMITER);

	//cout << "---------------------Data vectors---------------------" << endl;
	//for(i=0;i<len;i++) cout << (*red)[i].GetArray() << endl;

	//cout << "--------------------- Get Query ---------------------" << endl;

	get_query_arr(*input_stream,queryx,red,&len_q,DELIMITER);

	for(size_t k=0;k<len_q;k++){
		 queryx[k].DoQuery();
		 *output_stream << queryx[k];
	}
	
	float pepe;
	Array<float> juan;
	cin >> pepe;
	while(pepe != 17){
		juan.push_back(pepe);
		cin >> pepe;
	}	 
	SegTree<float> ricardoarias(juan);
	
	float min_, max_, num_, prom_;
	size_t init_pos, fin_pos;
	int pepe2=1;
	for(size_t j=0; j<4;j++){
			cout << endl << " \t[" ;
			for(size_t l=0;l<15;l++)
				cout << ((*(ricardoarias.ST))[l])[j] << ',';
			cout  <<"]"<< endl;
		}
	while(pepe2 == 1){
		cout << "ingresa init_pos y fin_pos" << endl;
		cin >> init_pos >> fin_pos;
		ricardoarias.SearchSegTree(init_pos,fin_pos,min_,max_,prom_,num_);
		cout << "minimo := " << min_ << "\t maximo := "<< max_ << "\t prom := "<< prom_;
		cout << "\t num := " << num_ << endl;
		cout << "Para seguir presione 1 para salir presione -1" << endl;
		cin >> pepe2;
	}
	/*cout << "Query arr length: " << len_q << endl;
	ID = (queryx[0]).GetID();
	init = (queryx[0]).GetInitPos();
	fin = (queryx[0]).GetFinPos();
	valid_data = (queryx[0]).GetLength();
	cout << "ID: " << ID << endl;   
	cout << "Initial Position: " << init << endl;
	cout << "Final Position: " << fin << endl;
	cout << "Number of valid data: " << valid_data << endl;
	cout << State_Dict[queryx[0].GetState()] << endl;
	size_t qdata_len = queryx[0].GetLength();
	cout << "qdata_arr len: " << qdata_len << endl;

	queryx[0].DoQuery();

	cout << "data query: " << queryx[0] << endl;
 

	
	cout << "Query arr length: " << len_q << endl;
	ID = (queryx[1]).GetID();
	init = (queryx[1]).GetInitPos();
	fin = (queryx[1]).GetFinPos();
	valid_data = (queryx[1]).GetLength();
	cout << "ID: " << ID << endl;   
	cout << "Initial Position: " << init << endl;
	cout << "Final Position: " << fin << endl;
	cout << "Number of valid data: " << valid_data << endl;
	cout << State_Dict[queryx[1].GetState()] << endl;
	qdata_len = queryx[1].GetLength();
	cout << "qdata_arr len: " << qdata_len << endl;

	queryx[1].DoQuery();

	cout << "data query: " << queryx[1] << endl;*/

	delete string_array;	

	dfs.close();
	ifs.close();
	ofs.close();

	return 0;
}





