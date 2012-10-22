#include<iostream>
#include<fstream>
#include <direct.h>
#include<string>
#include<cstring>
#include<io.h>
#include "GlobalVariables.h"
#include "select.h"
//#include "MatchSort.h"
//#include "updateTable.h"
using namespace std;

//enum sort {INT, CHAR, DATE, FLOAT, DOUBLE,TIME};

void InitDatabaseName(){
     string database_name_list = "";
     int i = 0;
     _finddata_t file;
     long lf;
     //cin the addr of file
     if((lf = _findfirst("E:\\Mysql\\DBMS_2012\\DBMS_NAME\\*", &file))==-1)
            cout<<"No Database Had Been Created!"<<endl;
     else{
            //cout<<"DatabaseName List:"<<endl;
            while(_findnext( lf, &file)==0){
                             // cout<<file.name<<"  " <<endl;
                             // cout << typeid(file.name).name()<<endl;
                             database_name_list += file.name;
                             database_name_list += ' ';
                             //cout << database_name_list[i] << endl;
                             // i++;
            }
            // cout << endl;
            database_name_list_clear = database_name_list.substr(3);
            //cout << database_name_list_clear <<endl;
     }
     _findclose(lf);     
}

void InitTemp(){
     char name_of_database_for_table_2[256];
     strcpy(name_of_database_for_table_2,name_of_database_for_table);
     char *source_addr_temp = strcat(name_of_database_for_table_2,"temp.dat");
     table_file.open(source_addr_temp);
     table_file.close();    
}

void InitModel(){ 
     char name_of_database_for_table_3[256];
     strcpy(name_of_database_for_table_3,name_of_database_for_table);
     char *source_addr_model = strcat(name_of_database_for_table_3,"model.dat");
     table_file.open(source_addr_model);
     table_file.close();      
}

bool InitTempModel(){
     _finddata_t file;
     long lf;
     char name_of_database_for_table_1[256];
     strcpy(name_of_database_for_table_1,name_of_database_for_table);
     char *create_addr = strcat(name_of_database_for_table_1,"*.dat");
     //cin the addr of file
     if((lf = _findfirst(create_addr, &file))==-1){
            InitTemp();
            InitModel();       
     }
     else
            return false;
     _findclose(lf);
     return true;      
}

void createDatabase(char databaseName[]){
     char str[] = "E://Mysql//DBMS_2012//DBMS_NAME//";
     name_of_database = strcat(str,databaseName);
     mkdir(name_of_database);
     //create a database ,update the database_name_list_clear
     database_name_list_clear += databaseName;
     database_name_list_clear += ' ';     
}

void update_table_addr(string now_used_database){
     int j = 29;
     for(int i=0,; i<now_used_database.size(); i++){
             name_of_database_for_table[j++]=now_used_database[i];                
     }
     int now_length = strlen(name_of_database_for_table);
     name_of_database_for_table[now_length] = '\\';
     name_of_database_for_table[now_length+1] = '\\';
     //char *con_database = strcat(name_of_database_for_table,now_used_database_ch);
     //name_of_database_for_table =  con_database;     
}

void createTable(char tableName[]){ 
     //set name_of_database_for_table a copy cant directly change name_of_database_for_table's value
     char cpy_name[256];
     strcpy(cpy_name,name_of_database_for_table);   
     char *name_of_table = strcat(cpy_name,tableName);
     table_file.open(name_of_table);
     table_file.close();     
}

int propertyStore(string str){
        string primary_key = "primary key";
        string is_primary_key = str.substr(0,11);
        if(primary_key == is_primary_key){
                       //do               
        }
        else{
             //get property name
             string name,sort;
             int i,j=0;
             for(i; str[i] != ' '; i++){
                          name[i] = str[i];     
             }
             //store name  
             //get property sort
             while(str[i] != ' '){
                          sort[j++] = str[i];             
             }   
        }
        
}

int returnNum(string str){
    int sum = 0;
    for(int i=0; i<str.size(); i++)
            if(str[i] == ',')
                      sum ++;  
     return (sum+1);  
}

bool formatMatch(string str,char table_name[]){
     cout << table_name << endl;
    int size = 0;
    int size_of_model_content = 0;
    string sort_num;
    char is_wrong_grammer = 'Y';
    string property_name = "";
    string tableBody = "";
    string property_sort = "";
    string store_for_property_name = "";
    string::size_type position_left;
    string::size_type position_right;
    position_left = str.find("(");
    position_right = str.find(")");
    tableBody = str.substr(position_left+1);
    size = tableBody.size();
    int sum = returnNum(tableBody);
    
    /********write dictionary.dat for select*************/
    int each_num = 0;
    fstream binary_dictionary;
    binary_dictionary.open("dictionary.dat",ios::out | ios::binary | ios::app);
    binary_dictionary.write((char*)&sum,4);
    binary_dictionary.write(table_name,8);
    if((position_left != str.npos) && (position_right != str.npos)){
                      
                      int m =0;
                      for(m;m<size;m++){
                                 for(m; m<size; m++){
                                         if((tableBody[m] != ' ') && (tableBody[m] != ','))
                                                 property_name += tableBody[m];
                                         else if(tableBody[m] == ' '){
                                                 break;
                                         }            
                                 }
                                 store_for_property_name += property_name;
                                 store_for_property_name += " ";
                                 for(m; m<size; m++){
                                        if((tableBody[m] != ',') && (tableBody[m] != '(')){
                                                 if((tableBody[m] != ' ') && (tableBody[m] != ')')){
                                                        property_sort += tableBody[m];
                                                 }
                                        }
                                        else if ((tableBody[m] == ',') || (tableBody[m] == '('))
                                             break;                  
                                 }
                                 transform(property_sort.begin(),property_sort.end(), property_sort.begin(), ::toupper);
                                 if(property_sort == "CHAR"){
                                        for(m; m<size; m++){
                                               if(tableBody[m] != ')'){
                                                     if(tableBody[m] == '(')
                                                                  m++;
                                                     sort_num  += tableBody[m];               
                                               }
                                               else
                                                   break;
                      
                                        } 
                                        each_num = atoi(sort_num.c_str());
                                        binary_dictionary.write((char*)&each_num,4);
                                        each_num = 0;                
                                 }
                                 else if(property_sort == "INT"){
                                      each_num = 4;
                                      binary_dictionary.write((char*)&each_num,4);
                                      each_num = 0;     
                                 }
                                 else if(property_sort == "DATE"){
                                      each_num = 10;
                                      binary_dictionary.write((char*)&each_num,4);
                                      each_num = 0;     
                                 }
                                 else if(property_sort == "TIME"){
                                      each_num = 8;
                                      binary_dictionary.write((char*)&each_num,4);
                                      each_num = 0;     
                                 }
                                 else if(property_sort == "DOUBLE"){
                                      each_num = 8;
                                      binary_dictionary.write((char*)&each_num,4);
                                      each_num = 0;     
                                 }
                                 //sort_num_int = atoi(sort_num.c_str());
                                 //cout << sort_num <<endl; 
                                 if((property_sort == "INT") || (property_sort == "CHAR") || (property_sort == "DATE") || (property_sort == "TIME") || (property_sort == "DOUBLE")){
                                                 is_wrong_grammer = 'N';  
                                                 model_content += property_name;
                                                 if(property_sort == "CHAR")
                                                                  model_content += sort_num;
                                                 model_content += property_sort;                    
                                 }
                                 //clear the value of the list of 
                                 property_name = "";
                                 property_sort = "";
                                 sort_num = "";
                                 //sort_num_int = 0;
                                 
                                 if(is_wrong_grammer == 'Y'){
                                          cout << "WRONG DATA TYPES!" <<endl;
                                          return false;                 
                                 }  
                      }
    }   
    else{
         cout<<"ERROR"<<endl;
         return false;     
    }
    binary_dictionary.close();
    /***********write property_name.dat file for select*****************/
    fstream binary_property;
    binary_property.open("property_name.dat",ios::out | ios::binary | ios::app);
    //only property_name's length except table_name's length
    int len_of_property = store_for_property_name.size();
    binary_property.write((char*)&len_of_property,4);
    binary_property.write(table_name,8);
    binary_property.write(store_for_property_name.c_str(),store_for_property_name.size());
    binary_property.close();
    store_for_property_name = "";
    
    size_of_model_content = model_content.size();
    char addr_of_database[256];
    strcpy(addr_of_database,name_of_database_for_table);
    char *addr_of_model = strcat(addr_of_database,"model.dat");
    fstream binaryio_model;
    binaryio_model.open(addr_of_model,ios::out | ios::app | ios::binary);
    //write the name of table 
    binaryio_model.write((char*)&size_of_model_content,sizeof(size_of_model_content));
   // cout << size_of_model_content << "size :" << sizeof(size_of_model_content) << endl;
    binaryio_model.write(model_content.c_str(),model_content.size());
    binaryio_model.close();
    //set value=0
    model_content = "";
    size_of_model_content = 0;
    return true;
}
/*
int readInt(){
    int size =0;
    char addr_of_database[256];
    strcpy(addr_of_database,name_of_database_for_table);
    char *addr_of_model = strcat(addr_of_database,"model.dat");
    fstream binary_int(addr_of_model,ios::binary | ios::in);
    binary_int.read((char*)&size,4);
    binary_int.close();
    return size;    
}
*/

bool insertInto(char name_of_table[],string str){
     /*
     int p_num = propertyNum(str.substr(str.find('(')));
     string nameOfTable = name_of_table;
     UseDictionary(nameOfTrable);
     if(p_num < _length[0]){
              memset(_length,0,100);
              cout << "insert into error!" << endl;
              return false;         
     }
     memset(_length,0,100);
     else{
              
     
     */
     int size_of_table=0;
     int num_of_property = 0;
     //string str_rest = "";
     /*************order recorde each property***************/
     int sort_of_table[20]={0};
     int pos = 0;
     /**********************/
     char num_of_char[4]={0};
     int pos_num = 0;
     int num_of_int[20]={0};
     int pos_int = 0;
     
     char name[9]={0};
     char table_name[9]={0};
     char read_temp[256]={0};
     char is_correct_table_name = 'N'; 
     char addr_of_database[256];
     strcpy(addr_of_database,name_of_database_for_table);
     char *addr_of_model = strcat(addr_of_database,"model.dat");
     fstream binary_model;
     binary_model.open(addr_of_model,ios::in | ios::binary); 
     
     while(!binary_model.eof()){
            //size_of_table = readInt();
            //cout << "size:" << size_of_table << endl;
            binary_model.read((char*)&size_of_table,4);
            //cout << "size:" << size_of_table << endl;
            binary_model.read(name,8);
            int l_2 =0;
            for(int l_1=0; l_1<9; l_1++){
                    if(name[l_1] != '0')
                               table_name[l_2++]=name[l_1];        
            } 
            //binary_model.read((char*)&str_rest,size_of_table-8);
            //cout << str_rest << endl;                         
            if(strcmp(table_name,name_of_table) == 0){
                          is_correct_table_name = 'Y';
                          binary_model.read(read_temp,size_of_table-8);
                          for(int l_3=0; l_3<size_of_table-1; l_3++){
                                  
                                  if((read_temp[l_3]=='I') && (read_temp[l_3+1]=='N') && (read_temp[l_3+2]=='T')){
                                          sort_of_table[pos++] = 1;
                                          l_3 += 2;
                                          num_of_property++;
                                  }
                                  else if((read_temp[l_3]=='D') && (read_temp[l_3+1]=='A') && (read_temp[l_3+2]=='T') && (read_temp[l_3+3]=='E')){
                                          sort_of_table[pos++] = 3;
                                          l_3 += 3;
                                          num_of_property++;
                                  }
                                  else if((read_temp[l_3]=='T') && (read_temp[l_3+1]=='I') && (read_temp[l_3+2]=='M') && (read_temp[l_3+3]=='E')){
                                          sort_of_table[pos++] = 4;
                                          l_3 += 3;
                                          num_of_property++;
                                  }
                                  else if((read_temp[l_3]=='D') && (read_temp[l_3+1]=='O') && (read_temp[l_3+2]=='U') && (read_temp[l_3+3]=='B') && (read_temp[l_3+4]=='L') && (read_temp[l_3+5]=='E')){
                                          sort_of_table[pos++] = 5;
                                          l_3 += 5;
                                          num_of_property++;
                                  }
                                  else if((read_temp[l_3] < 'A') && (read_temp[l_3] != '\0')){
                                       while(read_temp[l_3] != 'C'){
                                                            num_of_char[pos_num++] = read_temp[l_3];
                                                            l_3++;
                                       }
                                       l_3+=3;
                                       num_of_property++;
                                       num_of_int[pos_int] = atoi(num_of_char);
                                       pos_int++;
                                       //Empty the intermediate variables
                                       memset(num_of_char,0,4);
                                       pos_num = 0;
                                       
                                       sort_of_table[pos++] = 2;
                                  }
                                  else
                                       continue;            
                          }
                          pos = 0;
                          pos_int = 0;
                          
                          break;
            }
            binary_model.seekg(size_of_table-8,ios_base::cur); 
            //memset(table_name,0,9);       
     }
     binary_model.close(); 
     
     memset(addr_of_database,0,256);
     memset(addr_of_model,0,sizeof(addr_of_model));
        
     if(is_correct_table_name == 'Y'){
                              
           //get all key property's value
           string key_value = keyValue(name_of_table);
     
           string::size_type pos_of_l;
           string::size_type pos_of_r;
           string::size_type pos_seg;
           pos_of_l = str.find('(');
           pos_of_r = str.find(')');
           int isKey = 1;
           if((pos_of_l != str.npos) && (pos_of_r != str.npos)){
                        /********get table_name.dat then write in it*********/
                        char addr_of_database[256];
                        strcpy(addr_of_database,name_of_database_for_table);
                        //char *name_of_table_dat = strcat(name_of_table,".dat");
                        char *addr_of_model = strcat(addr_of_database,name_of_table);
                        /***************************************************/
                        fstream binary_insert;
                        binary_insert.open(addr_of_model,ios::out | ios::binary | ios::app);
                        
                        
                        char is_end_loop = 'N';
                        string temp_values = "";
                        string insert_values = str.substr(pos_of_l+1,pos_of_r-pos_of_l-1);
                        //at least 2 property
                        pos_seg = insert_values.find_first_of(',');
                        //while(pos_seg != insert_values.npos){
                        for(int i=0; i<num_of_property; i++){
                                      temp_values = insert_values.substr(0,pos_seg);
                                     // for(int i=0;i<num_of_property;i++){
                                              switch(sort_of_table[pos]){
                                                         case 1:
                                                              if(isInt(temp_values)){
                                                                      if(isKey ==1){
                                                                               // binary_insert.write((char*)&is_delete,1);
                                                                               if(temp_values.size() == 0){
                                                                                       cout << "The Value Of Primary key Can't Null" << endl;
                                                                                       return false;        
                                                                               }
                                                                               if(key_value.find(temp_values) != key_value.npos){
                                                                                       cout << "This Value is The Same With Primary key " << endl;
                                                                                       return false;                       
                                                                               }          
                                                                               else 
                                                                                    binary_insert.write(temp_values.c_str(),4);     
                                                                               isKey++;   
                                                                      }
                                                                      else
                                                                          binary_insert.write(temp_values.c_str(),4);
                                                              }
                                                              break;
                                                         case 2:
                                                              if(isChar(temp_values)){
                                                                     if(isKey ==1){
                                                                               if(temp_values.size() == 0){
                                                                                       cout << "The Value Of Primary key Can't Null" << endl;
                                                                                       return false;        
                                                                               }
                                                                               if(key_value.find(removeQuotation(temp_values)) != key_value.npos){
                                                                                       cout << "This Value is The Same With Primary key " << endl;
                                                                                       return false;     
                                                                               }    
                                                                               else
                                                                                   binary_insert.write(temp_values.substr(temp_values.find('"')+1,temp_values.size()-2).c_str(),num_of_int[pos_int++]);
                                                                               isKey++;   
                                                                      }  
                                                                      else
                                                                          binary_insert.write(temp_values.substr(temp_values.find('"')+1,temp_values.size()-2).c_str(),num_of_int[pos_int++]);
                                                              }                      
                                                              break;
                                                         case 3:
                                                              if(isDate(temp_values)){
                                                                     if(isKey ==1){
                                                                               // binary_insert.write((char*)&is_delete,1);
                                                                               if(temp_values.size() == 0){
                                                                                       cout << "The Value Of Primary key Can't Null" << endl;
                                                                                       return false;        
                                                                               }
                                                                               if(key_value.find(removeQuotation(temp_values)) != key_value.npos){
                                                                                       cout << "This Value is The Same With Primary key " << endl;
                                                                                       return false;     
                                                                               }       
                                                                               else
                                                                                   binary_insert.write(temp_values.substr(temp_values.find('"')+1,temp_values.size()-2).c_str(),10);
                                                                               isKey++;   
                                                                      } 
                                                                      else
                                                                          binary_insert.write(temp_values.substr(temp_values.find('"')+1,temp_values.size()-2).c_str(),10);  
                                                              }                     
                                                              break;
                                                         case 4:
                                                              if(isTime(temp_values)){
                                                                     if(isKey ==1){
                                                                               // binary_insert.write((char*)&is_delete,1);
                                                                               if(temp_values.size() == 0){
                                                                                       cout << "The Value Of Primary key Can't Null" << endl;
                                                                                       return false;        
                                                                               }
                                                                               if(key_value.find(removeQuotation(temp_values)) != key_value.npos){
                                                                                    cout << "This Value is The Same With Primary key " << endl;
                                                                                    return false;     
                                                                               }
                                                                               else
                                                                                   binary_insert.write(temp_values.substr(temp_values.find('"')+1,temp_values.size()-2).c_str(),8);
                                                                               isKey++;   
                                                                      }
                                                                      else
                                                                          binary_insert.write(temp_values.substr(temp_values.find('"')+1,temp_values.size()-2).c_str(),8);
                                                              }
                                                              break;
                                                         case 5:
                                                              if(isDouble(temp_values)){
                                                                     if(isKey ==1){
                                                                               // binary_insert.write((char*)&is_delete,1);
                                                                               if(temp_values.size() == 0){
                                                                                       cout << "The Value Of Primary key Can't Null" << endl;
                                                                                       return false;        
                                                                               }
                                                                               if(key_value.find(temp_values) != key_value.npos)
                                                                               {
                                                                                    cout << "This Value is The Same With Primary key " << endl;
                                                                                    return false;     
                                                                               }      
                                                                               else
                                                                                   binary_insert.write(temp_values.c_str(),8);  
                                                                               isKey++;   
                                                                      }
                                                                      else
                                                                          binary_insert.write(temp_values.c_str(),8);  
                                                              }                  
                                                              break;
                                                         default:
                                                                 cout << "error" <<endl;
                                              }
                                              pos++;                  
                                      //}
                                      
                                      //prepare for while loop
                                      pos_of_l = pos_seg;
                                      temp_values = "";
                                      if(is_end_loop == 'N'){
                                                     insert_values = insert_values.substr(pos_seg+1);
                                                     pos_seg = 0;
                                                     pos_seg = insert_values.find_first_of(','); 
                                                     if(pos_seg != insert_values.npos) 
                                                                continue;
                                                     else{
                                                         pos_seg = insert_values.size(); 
                                                         is_end_loop = 'Y';
                                                     }
                                      } 
                                      else
                                          break;                            
                        }
                        binary_insert.close();           
           }
           return true;                   
     }
     else{
          cout << "Wrong Table Name!" <<endl;
          return false;     
     } 
     num_of_property=0;
         
}

//Is the correct select format?
bool is_correct_select(string str){
     transform(str.begin(),str.end(), str.begin(), ::toupper);
     if((str.find("FROM") != str.npos) && (str.find("WHERE") != str.npos))
                          return true;
     else{
          cout << "Syntax error!" << endl;
          return false;
     }     
}

bool is_correct_update(string str){
      transform(str.begin(),str.end(), str.begin(), ::toupper); 
      if((str.find("SET") != str.npos) && (str.find("WHERE") != str.npos))
                          return true;
      else {
           cout << "Syntax error!" << endl;
           return false;     
      }   
}

bool loop_for_tableName(string tableName){
     char tableNameChar[9] = {0};
     char table_name[9] = {0};
     int size_of_table = 0;
     char name[9]={0};
     int i_1 = 0;
     for(int i=0; i<tableName.size(); i++){
             if(tableName[i] != ' ')
                             tableNameChar[i_1++] = tableName[i];        
     }     

     char addr_of_database[256];
     strcpy(addr_of_database,name_of_database_for_table);
     char *addr_of_model = strcat(addr_of_database,"model.dat");
     
     fstream binary_tableModel;
     binary_tableModel.open(addr_of_model,ios::in | ios::binary);
     
     while(!binary_tableModel.eof()){
            binary_tableModel.read((char*)&size_of_table,4);
            //cout << "size:" << size_of_table << endl;
            binary_tableModel.read(name,8);
            int i_2 = 0;
            for(int i=0; i<9; i++){
                    if(name[i] != '0')
                               table_name[i_2++]=name[i];        
            } 
            if(strcmp(table_name,tableNameChar) == 0){
                          binary_tableModel.close();
                          return true;
            }
            memset(table_name,0,9);
            binary_tableModel.seekg(size_of_table-8,ios_base::cur); 
     }
     binary_tableModel.close();
     return false;
     
}

//Is the correct table name?
bool is_correct_table_name(string table_names){
     // string table_name = str.substr(str.find("from")+5,str.find("where")-str.find("from")-6);
     string table_name = "";
     char is_end = 'N';
     int pos = table_names.find(',');
     for(int i=0; i<table_names.size(); i++){
              table_name = table_names.substr(0,pos);
              if(loop_for_tableName(table_name))
                                       return true;
              if(is_end == 'N'){
                        table_name = "";
                        table_names = table_names.substr(pos+1);
                        pos = table_names.find(',');
                        if(pos != table_names.npos)
                               continue;
                        else{
                             pos = table_names.size();
                             is_end = 'Y';     
                        }
              }
              else 
                   break;
     }
     cout << "Please enter correct table name!" << endl;
     return false;         
}

int judgeSort(string str)
{
      string str_copy = str;
      string table = "CREATE TABLE";
      string database = "CREATE DATABASE";
      string use = "USE";
      string show_database = "SHOW DATABASE";
      string insert_into = "INSERT INTO";
      string select = "SELECT";
      string delete_ = "DELETE";
      string update = "UPDATE";
      string discrible = "DISCRIBLE";
      string table_in = str.substr(0,12);
      string database_in = str.substr(0,15); 
      string use_in = str.substr(0,3);
      string insert_into_in = str.substr(0,11);
      string select_in = str.substr(0,6);
      string delete_in = str.substr(0,6);
      string update_in = str.substr(0,6);
      string discrible_in = str.substr(0,9);
      transform(table_in.begin(),table_in.end(), table_in.begin(), ::toupper);
      transform(database_in.begin(),database_in.end(), database_in.begin(), ::toupper);
      transform(use_in.begin(),use_in.end(), use_in.begin(), ::toupper);
      transform(str_copy.begin(),str_copy.end(), str_copy.begin(), ::toupper); 
      transform(insert_into_in.begin(),insert_into_in.end(), insert_into_in.begin(), ::toupper);
      transform(select_in.begin(),select_in.end(), select_in.begin(), ::toupper); 
      transform(delete_in.begin(),delete_in.end(), delete_in.begin(), ::toupper);
      transform(update_in.begin(),update_in.end(), update_in.begin(), ::toupper);
      transform(discrible_in.begin(),discrible_in.end(), discrible_in.begin(), ::toupper);
      
      
      //create table name (property sort...)
      if(table_in == table ) {
                  if(is_used_database == 'Y'){
                            InitTempModel();
                            //cout << is_used_database <<endl;
                            int i = 13,j=0,k=0;
                            //set a flag for find "(";
                            char is_find_l = 'N';
                            char name_of_table[100]={0};
                            char name_of_table_property[100]={0};
                            string table_in_last = "";
                            //substr(0,end) or substr(X,X)get address X length is X's char
                            table_in_last = str.substr(13,str.find('\n'));
                  
                            for(int i=0; i<table_in_last.length();i++){
                                     if(table_in_last[i] == '(')
                                                 is_find_l = 'Y';
                                     if((is_find_l == 'N') && (table_in_last[i] != ' ')){
                                                   name_of_table[j] = table_in_last[i]; //i j not sync
                                                   name_of_table_property[k++] = table_in_last[i];
                                                   model_content += table_in_last[i];
                                                   j++;
                                     }
                                     else if(is_find_l == 'Y'){
                                          if(strlen(name_of_table_property) <= 8)
                                                   for(int i=0; i<8-strlen(name_of_table_property); i++)
                                                           name_of_table_property[k++] = '0';
                                          //create table use .dat file
                                          name_of_table[j++] = '.';
                                          name_of_table[j++] = 'd';
                                          name_of_table[j++] = 'a';
                                          name_of_table[j] = 't';
                                          break;
                                     } 
                            }
                            if(model_content.size() <=8){
                                  int rest_of = 8 - model_content.size();
                                  for(int i=0; i<rest_of; i++)
                                          model_content += "0";                  
                            }
                            else if(model_content.size() > 8){
                                 cout << "The size of table name is lager than 8 bit" << endl;
                                 model_content = "";
                                 return 0;     
                            }
                            // cout << name_of_table <<endl;
                            if(formatMatch(str,name_of_table_property)){
                                                 createTable(name_of_table);     
                                                 cout << "CREATE TABLE: " << name_of_table << " SUCCESS!" <<endl; 
                            } 
                  }
                  else{
                       cout << "Please enter 'use database name' first!" <<endl;
                       return 0;     
                  }     
                  return 1;
      } 
      //create database Name
      if(database_in == database){
                     char ch[10]={0}; //permission most amount of databaseName 
                     string databaseName = str.substr(16,str.find('\n'));
                     for(int i=0; i<databaseName.size();i++){
                             ch[i] = databaseName[i];      
                     }
                     //const char* ch = databaseName.c_str();  //string --> char
                     createDatabase(ch);         
                     cout << "DatabaseName:" << ch << "CREATE DATABASE SECCESS!" <<endl;      
                     return 2;
      }
      else if(str_copy == show_database){
           if(database_name_list_clear == ""){
                     cout << "No Database Has Been created!" <<endl;                            
           }         
           else 
                     cout << database_name_list_clear <<endl;
      }
      //use databaseName
      else if(use_in == use){
                char is_exists_database = 'N';
                int i = 3;
                string::size_type pos; 
                string use_database_name;
                string data;
                int size = database_name_list_clear.length();
                for(i; i<str.size();i++){
                       data = str[i];
                       if((data.compare(null_of_in) != 0) && (data.compare(enter_return) !=0)){
                                  use_database_name += data;                       
                       }          
                }
                //return database_name
                //handle all database name and compare with user_in database_name
                for(int j=0; j<size; j++){
                        pos = database_name_list_clear.find(' ',j);
                        if(pos < size){
                               string s = database_name_list_clear.substr(j,pos-j);
                               if(use_database_name == s){
                                                    now_used_database = s; 
                                                    j = pos;
                                                    is_exists_database = 'Y';                   
                               }
                                      
                        }                 
                }
                if(is_exists_database == 'N'){
                                      cout << "database name not exists!" <<endl;
                                      return 0;
                }
                else{
                     is_used_database = 'Y'; 
                     update_table_addr(use_database_name);    
                }
                
      }
      //insert into name values ();
      else if(insert_into == insert_into_in){
           if(is_used_database = 'Y'){
                 int size_of_insert_into = 0;
                 char table_name_ch[100]={0};
                 size_of_insert_into = str.size();
                 char is_find_values = 'N';
                 if((str.find("values") < size_of_insert_into) || (str.find("VALUES") <size_of_insert_into)){
                       if((str.find('(') < size_of_insert_into) && (str.find(')') < size_of_insert_into))
                                         is_find_values = 'Y';                
                 }
                 if(is_find_values == 'Y'){
                                   int table_name_length = str.find("values") - 12;
                                   string table_name = "";
                                   table_name = str.substr(12,table_name_length);
                                   //get the name of table
                                   int len_2 =0;
                                   int table_name_size = table_name.size();
                                   for(int len_1=0; len_1<table_name_size; len_1++){
                                           if(table_name[len_1] != ' ')
                                                            table_name_ch[len_2++] = table_name[len_1];         
                                   }
                                   //searchFromModel(table_name_char);
                                   if(insertInto(table_name_ch,str)) 
                                          cout << "Insert data success!" << endl;                 
                 }
                 else{
                      cout << "Grammer Error!" <<endl;     
                 }
                                                  
           }     
           else{
                cout << "Please enter 'use database_name' first!" <<endl;
                return 0;        
           }
      }
      else if(select == select_in){
           if(is_used_database = 'Y'){
                               string table_name = str.substr(str.find("from")+5,str.find("where")-str.find("from")-6);
                               if(table_name.find('.') != table_name.npos){
                                     is_projection = 'Y';
                                     string tableName = "";
                                     char is_end = 'N';
                                     int pos = table_name.find(',');
                                     for(int i=0; i<table_name.size(); i++){
                                             tableName = table_name.substr(0,pos);
                                             if(tableName.size() > 0){
                                                    tableName = removeBlank(tableName);
                                                    cout << tableName << "    ";
                                             }
                                             if(is_end == 'N'){
                                                       table_name = table_name.substr(table_name.find(',')+1);
                                                       if(table_name.find(',') != table_name.npos)
                                                              continue;
                                                       else{ 
                                                             is_end = 'Y';
                                                             pos = table_name.size();
                                                       } 
                                             }
                                             else 
                                                  break;
                                     } 
                                     cout << endl;
                                     string _condition = str.substr(str.find("where")+6);
                                     Equi_Join(_condition);                        
                               }
                               else if(str.find('*') != str.npos){
                                     //
                                     string _condition = str.substr(str.find("where")+6);
                                     Equi_Join(_condition);         
                               }
                               else{
                                    if(is_correct_select(str) && is_correct_table_name(table_name)){
                                            string target_property = str.substr(7,str.find("from")-8);
                                            string select_condition = str.substr(str.find("where")+6); 
                                            select_function(target_property,table_name,select_condition);                                                                 
                                    }
                               }
           }
           else{
                cout << "Please enter 'use database_name' first!" <<endl;
                return 0; 
           }          
      }
      else if(delete_.compare(delete_in) == 0){
           string delete_tableName = str.substr(str.find("from")+5,str.find("where")-str.find("from")-6);
           if(is_correct_table_name(delete_tableName) && is_correct_select(str))
                   cout << "delete" << endl;
                   string delete_condition = str.substr(str.find("where")+6);
                   //deleteTable(delete_tableName,delete_condition);
               
      }
      else if(update.compare(update_in) == 0){
           string update_tableName = str.substr(7,str.find("set")-8);
           if(is_correct_table_name(update_tableName) && is_correct_update(str)){
                  string set_condition = str.substr(str.find("set")+4,str.find("where")-str.find("set")-5);
                  string find_condition = str.substr(str.find("where")+6);
                  updateTable(update_tableName,set_condition,find_condition);
           }
      }
      else if(discrible.compare(discrible_in) ==0){
           if(is_used_database = 'Y'){
                string tableName = str.substr(10);
                if(is_correct_table_name(tableName)){
                         //
                         discribleTable(tableName);                                     
                }               
           }
           else{
                cout << "Please enter 'use database_name' first!" <<endl;
                return 0; 
           }         
      }
      else {
           cout << "ERROR" <<endl;
           return 0;     
      }
      str="";
}



int main (){
    // cout << name_of_database_for_table[28] <<endl;
    //InitTemp();
    //InitModel();
    InitDatabaseName();
    while(1){
             getline(cin,message);
             judgeSort(message);
             message = "";
    }
//cout<<message << endl ;
//string a = message.substr(0,12);

//cout << a <<endl;

   system("pause");
   return 0;   
}

