#ifndef _HELP_MESSAGES_INCLUDED_
#define _HELP_MESSAGES_INCLUDED_

#define PROGRAM_HELP " This program takes a data file with sensor IDs and a data set from every sensor. The data file is defined with its respective command line argument and is mandatory. It then displays in an output file the minimum, maximum and mean values taken from a subset of the data, defined in the input file.\n The list and explanation of the command line argument options follows:\n short name | long name |  \n"

#define DATA_OPT_HELP "\n\t | -d \"_\" | --data \"_\" | MANDATORY \n\n"
#define DATA_OPT_EXP " The data file must be a CSV file containing the sensor IDs on the first line, and the corresponding  data set of every sensor on the same column. A missing value on the data set will not terminate the program.\n The data file must have the following format:\n SENSOR1ID,SENSOR2ID,...,SENSORNID\nSENSOR1DATA1,SENSOR2DATA1,...,SENSORNDATA1\n...\n"

#define INPUT_OPT_HELP "\n\t | -i \"_\" | --input \"_\" | DEFAULT = cin \n\n"
#define INPUT_OPT_EXP " The input file must be a CSV file containing a query that specifies which subset of the data should be used to obtain the minimum, maximum and mean. If not specified the standard input stream is taken as the input file for the program. \n The input file must have the following format:\n SENSOR_ID,INITIAL_POS,FINAL_POS\n...\n"

#define OUTPUT_OPT_HELP "\n\t | - o \"_\" | --output \"_\" | DEFAULT = cout \n\n"
#define OUTPUT_OPT_EXP " The data file must be a CSV file containing the sensor IDs on the first line, and the corresponding  data set of every sensor on the same column. A missing value on the data set will not terminate the program.\n The data file must have the following format:\n SENSOR1ID,SENSOR2ID,...,SENSORNID\nSENSOR1DATA1,SENSOR2DATA1,...,SENSORNDATA1\n...\n"




#endif
