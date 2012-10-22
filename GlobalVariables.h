#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string message = "";
char *name_of_database;
char name_of_database_for_table[256] = "E:\\Mysql\\DBMS_2012\\DBMS_NAME\\";
//List all created databasename
string database_name_list_clear = "";
ofstream table_file;
string now_used_database = "";
string model_content = "";
/********************two common used avi*****************************/
string null_of_in = " ";
string enter_return = "\n";
/***************a list of some flags*********************************/
char is_used_database = 'N';
char is_in_table = 'N';
char is_projection = 'N';
