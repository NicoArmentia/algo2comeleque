#ifndef _HELP_MESSAGES_INCLUDED_
#define _HELP_MESSAGES_INCLUDED_

#define PROGRAM_HELP " This program takes a data file with sensor IDs and a data set from every sensor. The data file is defined with its respective command line argument and is mandatory. It then displays in an output file the mean, minimum and maximum values taken from a subset of the data, defined in the input file.\n The list and explanation of the command line argument options follows:\n short name | long name |  \n"

#define DATA_OPT_HELP "\n\t | -d \"_\" | --data \"_\" | MANDATORY \n\n"
#define DATA_OPT_EXP " The data file must be a CSV file containing the sensor IDs on the first line, and the corresponding  data set of every sensor on the same column. A missing value on the data set will not terminate the program. A wrong data set will terminate de program.\n The data file must have the following format:\n SENSOR_1_ID,SENSOR_2_ID,...,SENSOR_N_ID\nSENSOR_1_DATA_1,SENSOR_2_DATA_1,...,SENSOR_N_DATA_1\n...\nSENSOR_1_DATA_M,SENSOR_2_DATA_M,...,SENSOR_N_DATA_M\n"

#define INPUT_OPT_HELP "\n\t | -i \"_\" | --input \"_\" | OPTIONAL \n\n"
#define INPUT_OPT_EXP " The input file must be a CSV file containing a query that specifies which subset of the data should be used to obtain the minimum, maximum and mean. If not specified the standard input stream is taken as the input file for the program. If the query requires all sensors to be taken into account, then it must contain a \"-\". \n The input file must have the following format:\n SENSOR_ID,INITIAL_POS,FINAL_POS\n...\n"

#define OUTPUT_OPT_HELP "\n\t | - o \"_\" | --output \"_\" | OPTIONAL \n\n"
#define OUTPUT_OPT_EXP " The output file contains the results of the querys. If not specified, the standard output stream is taken as the output file for the program.\n The output file has the following format:\n MEAN,MINIMUM,MAXIMUM,AMMOUNT_OF_DATA_USED\n...\n"

#define MODE_OPT_HELP "\n\t | - m \"_\" | --mode \"_\" | OPTIONAL \n\n"
#define MODE_OPT_EXP " Option for definition of search method. The default method is linear search. There are two modes: 'linear' (default) and 'tree' which uses a segmente tree to obtain the results of querys."



#endif
