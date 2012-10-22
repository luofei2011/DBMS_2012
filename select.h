#include<iostream>
#include<fstream>
#include<string>
#include "MatchSort.h"

using namespace std;

/***********a new idea**********************/
int _length[200] = {0}; //support 200 properties
string _position = "";   //return the position of each property

//str1 = target_property; str2 = table_name 
bool is_correct_property(string str1,string str2){
     int length_of_property = 0;
     int num_of_property = 0;
     char property_names[200] = {0};
     char name[9] = {0};
     char table_name[9] = {0};
     fstream binary_search;
     fstream binary_dictionary;
     binary_search.open("property_name.dat",ios::in | ios::binary);
     binary_dictionary.open("dictionary.dat",ios::in | ios::binary);
     while(!binary_dictionary.eof()){
              
              binary_dictionary.read((char*)&num_of_property,4);
              binary_dictionary.read(name,8);
              int i_1 = 0; 
              for(int i =0; i<9; i++){
                      if(name[i] != '0')
                                 table_name[i_1++] = name[i];
              }
              if(strcmp(str2.c_str(),table_name) == 0)
                       break;                          
              else
                  binary_dictionary.seekg(num_of_property*4,ios_base::cur);
              memset(table_name,0,9);
              memset(name,0,9);
              num_of_property = 0;
     }
     memset(table_name,0,9);
     memset(name,0,9);
     binary_dictionary.close();
     
     while(!binary_search.eof()){
              binary_search.read((char*)&length_of_property,4);
              //flit table_name,change the file pointer
              binary_search.read(name,8);
              int i_1 = 0; 
              for(int i =0; i<9; i++){
                      if(name[i] != '0')
                                 table_name[i_1++] = name[i];
              }
              if(strcmp(str2.c_str(),table_name) == 0){
                      binary_search.read(property_names,length_of_property);
                      string property_name_string = property_names;
                      for(int i=0; i<num_of_property; i++){
                              //cout << property_names.substr(0,property_names.find(" ")) << endl;
                              if(str1.compare(property_name_string.substr(0,property_name_string.find(" "))) == 0){
                                         binary_search.close();
                                         return true;                                                              
                              }                                                             
                              property_name_string = property_name_string.substr(property_name_string.find(" ")+1);                                   
                      } 
                      property_name_string = "";
              }
              else
                  binary_search.seekg(length_of_property,ios_base::cur);
              memset(table_name,0,9);
              memset(name,0,9);
     } 
     binary_search.close();
     return false;                       
}


//only support one and
int deal_condition(string str){
    transform(str.begin(),str.end(), str.begin(), ::toupper); 
    if(str.find("NOT") != str.npos)
                       return 1;
    else if(str.find("OR") != str.npos)
                       return 2;
    else if(str.find("AND") != str.npos)
                       return 3;
    else
        return 0;
                           
}

int deal_condition_next(string str){
    if(str.find('<') != str.npos){
            if(str.find('=') != str.npos)
                     return 1;
            return 2;                  
    }  
    else if(str.find('>') != str.npos){
         if(str.find('=') != str.npos)
                     return 3;
         return 4;     
    }  
    else if(str.find('=') != str.npos)
         return 5;
    else
        return 0;
}

int UseDictionary(string tableName){
     int num_of_property = 0;
     char name[9] = {0};
     char table_name[9] = {0};

     fstream binary_dictionary;
     binary_dictionary.open("dictionary.dat",ios::in | ios::binary);
     
     while(!binary_dictionary.eof()){
              
              binary_dictionary.read((char*)&num_of_property,4);
              binary_dictionary.read(name,8);
              int i_1 = 0; 
              for(int i =0; i<9; i++){
                      if(name[i] != '0')
                                 table_name[i_1++] = name[i];
              }
              if(strcmp(tableName.c_str(),table_name) == 0){
                      //
                      _length[0] = num_of_property;
                      for(int i=1; i<=num_of_property; i++){
                              int _num;
                              binary_dictionary.read((char*)&_num,4);
                              _length[i] = _num;
                              _num = 0;        
                      }   
                      break;                                     
              }                         
              else
                  binary_dictionary.seekg(num_of_property*4,ios_base::cur);
              memset(table_name,0,9);
              memset(name,0,9);
              num_of_property = 0;
     }
     binary_dictionary.close();
     return 0;
}

string InttoString(int i){
       char  csTemp[20]; 
       string  str; 
       sprintf(csTemp,"%d",i); 
       str = csTemp; 
       return str;       
}

int UseProperty_name(string tableName){
    
    fstream binary_name;
    binary_name.open("property_name.dat",ios::in | ios::binary);

    int num_all = 0;
    char name[9] = {0};
    char table_name[9] ={0};
    char _rest[256] = {0};
    int position = 1;
    
    while(!binary_name.eof()){
              
              binary_name.read((char*)&num_all,4);
              binary_name.read(name,8);
              int i_1 = 0; 
              for(int i =0; i<9; i++){
                      if(name[i] != '0')
                                 table_name[i_1++] = name[i];
              }
              if(strcmp(tableName.c_str(),table_name) == 0){
                       //
                       binary_name.read(_rest,num_all);
                       _position += "1";
                       for(int i=0; i<num_all; i++){
                             if(_rest[i] == ' '){
                                         position++;
                                         _position += InttoString(position);            
                             }
                             else
                                 _position += _rest[i];  
                       }
                       break;                          
              }
              else
                  binary_name.seekg(num_all,ios_base::cur);
              memset(table_name,0,9);
              memset(name,0,9);
     }
     binary_name.close();  
     return 0;      
}

int Position_(string str,string name){
    char position = str[str.find(name)-1];
    int pos = int(position)-48;
    return pos;    
}

int returnSum(int arr[]){
    int sum =0;
    for(int i=1; i<sizeof(arr)+1; i++)
            sum += arr[i];
    return sum;    
}

bool is_double(char ch[]){
     for(int i=0; i<strlen(ch); i++)
             if((ch[i] >= '.') && (ch[i] <= '9'))
                       return true;
     return false;     
}

bool is_int(char ch[]){
     for(int i=0; i<strlen(ch); i++)
             if((ch[i] >= '0') && (ch[i] <= '9'))
                       return true;
     return false;     
}

bool is_date(char ch[]){
     if((ch[4] == '-') && (ch[7] == '-'))
               return true;
     return false;
}

bool is_time(char ch[]){
     if((ch[2] == ':') && (ch[5] == ':'))
               return true;
     return false;
}

string removeQuotation(string str){
       string::size_type front;
       string::size_type rear;
       front = str.find('"');
       str = str.substr(front+1);
       rear = str.find('"');
       str = str.substr(0,rear);
       return str;       
}

void coutResult(string str,int length){
      char addr_of_temp[256];
      strcpy(addr_of_temp,name_of_database_for_table); 
      char *addr_of_temp_dat = strcat(addr_of_temp,"temp.dat");
      
      fstream binary_temp;
      binary_temp.open(addr_of_temp_dat,ios::in | ios::binary);
      
      char buff_1[100] = {0};
      int buff_2 = 0;
      double buff_3 = 0;
      
      cout << str << ":" << endl;
      
      while(!binary_temp.eof()){
               //
               if(length == 4){
                         binary_temp.read((char*)&buff_2,4);
                         if(buff_2 != 0)
                                   cout << buff_2 << endl;
                         buff_2 = 0;
               }
               else if(length == 8){
                         binary_temp.read((char*)&buff_1,8);
                         if(is_double(buff_1))
                                  if(atof(buff_1) != 0)
                                                  cout << atof(buff_1) << endl;
                         else{
                              if(strlen(buff_1) != 0)
                                      cout <<  buff_1 << endl;
                              memset(buff_1,0,100);
                         }
               }  
               else {       
                    binary_temp.read(buff_1,length);
                    if(strlen(buff_1) != 0)
                           cout << buff_1 << endl;
                    memset(buff_1,0,100); 
               }                         
      }
      binary_temp.close(); 
      
      //clear temp.dat
      fstream binary;
      binary.open(addr_of_temp_dat,ios::out | ios::binary);
      binary.close();
      
      //clear the Global variables
      memset(_length,0,200);
      _position = "";
}

//query_from_table(dictionary.dat,property_name.dat,table_name.dat)
bool query_from_table(string target_property,string table_name,string property_name,string values){
     
     /*************open temp.dat, table_name.dat*************/
     char addr_of_database[256];
     char addr_of_temp[256];
     strcpy(addr_of_database,name_of_database_for_table);
     strcpy(addr_of_temp,name_of_database_for_table);
     char *ch = strdup(table_name.data());
     char *addr_of_table = strcat(ch,".dat");
     char *addr_of_table_name = strcat(addr_of_database,addr_of_table);
     char *addr_of_temp_dat = strcat(addr_of_temp,"temp.dat");
     
     fstream binary_n;
     fstream binary_t;
     binary_n.open(addr_of_table_name,ios::in | ios::binary);
     binary_t.open(addr_of_temp_dat,ios::out | ios::binary | ios::app);
     
     UseDictionary(table_name);      
     int num = _length[0];
     UseProperty_name(table_name);
     int pos_1 = Position_(_position,target_property);
     int pos_2 = Position_(_position,property_name);
     
     string intoTemp = "";
     int intoLength = 0;
     char is_find = 'N';
     
     while(!binary_n.eof()){
              //
              for(int i=1; i<num+1; i++){
                      if(i == pos_1){
                           int length_1 = _length[i];
                           intoLength = length_1;
                           char _target[100] = {0};
                           binary_n.read(_target,length_1);
                           intoTemp += _target;     
                      }
                      else if(i == pos_2){
                           int length_2 = _length[i];
                           char _source[100] = {0};
                           binary_n.read(_source,length_2);
                           if(length_2 == 8){
                                 if(is_double(_source)){
                                         double _cmp = atof(_source); 
                                         if(atof(values.c_str()) == _cmp)
                                                 is_find = 'Y';                      
                                 } 
                                 else{
                                      values = removeQuotation(values);
                                      if(strcmp(_source,values.c_str()) == 0)
                                                 is_find = 'Y'; 
                                 }    
                           }
                           else if(length_2 == 4){
                                if(is_int(_source)){
                                       int _cmp = atoi(_source); 
                                       if((atoi(values.c_str())) == _cmp)
                                             is_find = 'Y';   
                                }  
                                else{
                                     values = removeQuotation(values);
                                     if(strcmp(_source,values.c_str()) == 0)
                                                 is_find = 'Y'; 
                                }
                           }
                           else{
                                values = removeQuotation(values);
                                if(strcmp(_source,values.c_str()) == 0)
                                       is_find = 'Y';     
                           }
                              
                      }  
                      else{
                           int offset = _length[i];
                           binary_n.seekg(offset,ios_base::cur);
                           offset = 0;  
                      }                        
              } 
              if(is_find == 'Y'){
                         binary_t.write(intoTemp.c_str(),intoLength);
                         is_find = 'N';
                         intoTemp = "";
              }                   
     }     
     binary_t.close();     
     coutResult(target_property,intoLength);
     
     binary_n.close();
     return true;
}

//select_function(target_property,table_name,select_condition); 
bool select_function(string str1,string str2,string str3){
     //only one property to search
     if(is_correct_property(str1,str2)){

            /****************deal select_condition****************************/ 
            int result = deal_condition(str3);
            int compare_con;
            string temp_condition = "";
            string table_property = "";
            string table_name = "";
            string property_name = "";
            string values = "";
            switch(result){
                           case 0:
                                temp_condition = str3;
                                compare_con = deal_condition_next(str3);
                                if(compare_con % 2 == 0)
                                                table_property = temp_condition.substr(0,temp_condition.find('=')-1);
                                else 
                                     table_property = temp_condition.substr(0,temp_condition.find('='));
                                values = temp_condition.substr(temp_condition.find('=')+1);
                                property_name = table_property;  
                                query_from_table(str1,str2,property_name,values);
                                break;
                           case 1://NOT
                                compare_con = deal_condition_next(str3);
                                break;
                           case 2://OR
                                compare_con = deal_condition_next(str3);
                                break;
                           case 3://AND  
                                int pos = str3.find("and")-1;
                                for(int i=0; i<2; i++){
                                        temp_condition = str3.substr(0,pos);
                                        compare_con = deal_condition_next(temp_condition);
                                        if(compare_con % 2 == 0)
                                                table_property = temp_condition.substr(0,temp_condition.find('=')-1);
                                        else 
                                             table_property = temp_condition.substr(0,temp_condition.find('='));
                                        values = temp_condition.substr(temp_condition.find('=')+2);
                                        if(table_property.find('.') != table_property.npos){
                                                table_name = table_property.substr(0,table_property.find('.'));
                                                property_name = table_property.substr(table_property.find('.')+1);                            
                                        }  
                                        else{
                                             property_name = table_property;     
                                        }  
                                        //get (table_name) property_name,values
                                        query_from_table(str1,table_name,property_name,values);
                                        temp_condition = "";
                                        str3 = str3.substr(str3.find("and")+4);
                                        if(str3.find("and") != str3.npos)
                                                continue;
                                        else
                                            pos = str3.size();
                                }
                                break;
                                           
            }
     }
     else
         return false;
     return true;     
}

string removeBlank(string str){
       string s = "";
       for(int i=0; i<str.size(); i++)
               if(str[i] != ' ')
                         s += str[i];
       return s;       
}

string TraversalTable(string tableName,string Col){
       UseDictionary(tableName);
       UseProperty_name(tableName);
       string result = "1";
       char temp[100] = "";
       int conter = 1;
       int position = Position_(_position,Col);
       int num = _length[0];
       
       //two pointer of file
       int front =0;
       int rear =0;
       
       //for front;
       for(int i=1; i<position; i++)
               front += _length[i];
       //for rear;
       for(int i=position+1; i<num+1; i++)
               rear += _length[i]; 
       
       char addr_of_database[256];
       strcpy(addr_of_database,name_of_database_for_table);
       char *ch = strdup(tableName.data());
       char *addr_of_table = strcat(ch,".dat");
       char *addr_of_table_name = strcat(addr_of_database,addr_of_table);
       
       fstream binary;
       binary.open(addr_of_table_name,ios::in | ios::binary);
       
       while(!binary.eof()){
                //
                binary.seekg(front,ios_base::cur);
                binary.read(temp,_length[position]);
                conter++;
                result += temp;
                result += InttoString(conter);
                memset(temp,0,100);
                binary.seekg(rear,ios_base::cur);                     
       } 
       memset(_length,0,100);
       _position = "";
       binary.close();
       return result;   
}
/*
void writeIntoTemp(string temp,int length){
     char addr_of_temp[256];
      strcpy(addr_of_temp,name_of_database_for_table); 
      char *addr_of_temp_dat = strcat(addr_of_temp,"temp.dat");
      
      fstream binary_temp;
      binary_temp.open(addr_of_temp_dat,ios::in | ios::binary);
      
      binary_temp.write(temp.c_str(),length);
      binary_temp.close();
      
}
*/
void WriteTemp(string tableName1,int conter,string tableName2,int pos){
     //
     char addr_of_database_1[256];
     strcpy(addr_of_database_1,name_of_database_for_table);
     char *ch_1 = strdup(tableName1.data());
     char *addr_of_table_1 = strcat(ch_1,".dat");
     char *addr_of_table_name_1 = strcat(addr_of_database_1,addr_of_table_1);
     
     char addr_of_database_2[256];
     strcpy(addr_of_database_2,name_of_database_for_table);
     char *ch_2 = strdup(tableName2.data());
     char *addr_of_table_2 = strcat(ch_2,".dat");
     char *addr_of_table_name_2 = strcat(addr_of_database_2,addr_of_table_2); 
     
     fstream binary_1;
     fstream binary_2;
     
     binary_1.open(addr_of_table_name_1,ios::in | ios::binary);
     binary_2.open(addr_of_table_name_2,ios::in | ios::binary);
     
     string result = "";
     char temp[100] ={0};
     /***********interrupt***********/
     memset(_length,0,100);
     _position = "";
     UseDictionary(tableName2);
     UseProperty_name(tableName2);
     int table_len2 = returnSum(_length);
     binary_2.seekg((pos-1)*table_len2,ios_base::cur);
     for(int i=1; i<_length[0]+1; i++){
             if(is_projection == 'Y'){
                              
             }
             else{
                  binary_2.read(temp,_length[i]);
                  result += temp;
                  result += " ";
                  memset(temp,0,100);
             }
     }
     result += "| ";
     /***********interrupt***********/
     memset(_length,0,100);
     _position = "";
     UseDictionary(tableName1);
     UseProperty_name(tableName1);
     int table_len1 = returnSum(_length);    
     binary_1.seekg((conter-1)*table_len1,ios_base::cur);
     for(int i=1; i<_length[0]+1; i++){
             if(is_projection == 'Y'){
                              
             }
             else{
                  binary_1.read(temp,_length[i]);
                  result += temp;
                  result += " ";
                  memset(temp,0,100);
             }
     }
     cout << result << endl;
     
     is_projection = 'N';
     binary_1.close();
     binary_2.close();
     
     
              
}

void Equi_Join_(string tableName1,string Col1,string tableName2,string Col2){
     string _compare = TraversalTable(tableName2,Col2); 
     
     char addr_of_database[256];
     strcpy(addr_of_database,name_of_database_for_table);
     char *ch = strdup(tableName1.data());
     char *addr_of_table = strcat(ch,".dat");
     char *addr_of_table_name = strcat(addr_of_database,addr_of_table);
     
     fstream binary;
     binary.open(addr_of_table_name,ios::in | ios::binary);
     
     UseDictionary(tableName1);
     UseProperty_name(tableName1);
     int num = _length[0];
     int position = Position_(_position,Col1);
     string _cmp = "";
     char temp[100] = "";
     int conter = 0;

     //two pointer of file
     int front =0;
     int rear =0;
       
     //for front;
     for(int i=1; i<position; i++)
               front += _length[i];
     //for rear;
     for(int i=position+1; i<num+1; i++)
               rear += _length[i]; 
     
     string compare_cpy = "";
     while(!binary.eof()){
                conter++;
                binary.seekg(front,ios_base::cur);
                binary.read(temp,_length[position]);
                _cmp = temp;
                
                if((_compare.find(_cmp) != _compare.npos) && (_cmp.size() != 0)){
                         compare_cpy = _compare;
                         int pos = Position_(compare_cpy,_cmp);
                         while(compare_cpy.find(_cmp) != compare_cpy.npos){
                                    //if(_compare.find(_cmp) != _compare.npos)
                                    WriteTemp(tableName1,conter,tableName2,pos);
                                    compare_cpy = compare_cpy.substr(compare_cpy.find(_cmp)+_length[position]);
                         
                         }
                         compare_cpy = "";
                }
                if(_cmp.size() == 0)
                               break;
                _cmp = "";
                memset(temp,0,100);
                binary.seekg(rear,ios_base::cur);                
     }
     memset(_length,0,100);
     _position = "";
     binary.close();
              
}

void Equi_Join(string condition){
     //
     string con1 = condition.substr(0,condition.find('='));
     string con2 = condition.substr(condition.find('=')+1);
     
     string _con1 = removeBlank(con1);
     string _con2 = removeBlank(con2);
     
     //get tableName1,tableName2,Col1,Col2
     string tableName1 = _con1.substr(0,_con1.find('.'));
     string Col1 = _con1.substr(_con1.find('.')+1);
     string tableName2 = _con2.substr(0,_con2.find('.'));
     string Col2 = _con2.substr(_con2.find('.')+1);
     Equi_Join_(tableName1,Col1,tableName2,Col2);
          
}

string keyValue(char table_name[]){
       string tableName = table_name;
       UseDictionary(tableName);
       int length = _length[1];
       int offset = returnSum(_length); 
       
       char addr_of_database[256];
       strcpy(addr_of_database,name_of_database_for_table);
       char *name_of_table_dat = strcat(table_name,".dat");
       char *addr_of_model = strcat(addr_of_database,name_of_table_dat);
       
       fstream binary;
       binary.open(addr_of_model,ios::in | ios::binary);
       
       string result = "";
       char temp[100] = {0};
       
       while(!binary.eof()){
               binary.read(temp,length);
               if(strlen(temp) !=0 ){
                      result += temp;
                      result += " ";  
                      memset(temp,0,100);
               }
               binary.seekg(offset-length,ios_base::cur);                   
       } 
       memset(_length,0,100);
       binary.close();
       return result;     
}

bool updateTable(string tableName,string set_condition,string find_condition)
{


    string find_col = "";
    //string table_name = "";
    string set_col="";
    //string property_name = "";
    string set_values="";
    string find_values = "";
    char is_fit='N';
    char is_find='N';
    UseDictionary(tableName);
    UseProperty_name(tableName);


    if(find_condition.find('=') != find_condition.npos&&set_condition.find('=')!=set_condition.npos){
        is_fit='Y';

        find_col = find_condition.substr(0,find_condition.find('='));
        find_values = find_condition.substr(find_condition.find('=')+1);
        set_col=set_condition.substr(0,set_condition.find('='));
        set_values=set_condition.substr(set_condition.find('=')+1);
        set_values = removeQuotation(set_values);
        //query_from_table(set_col,tableName,find_col,find_values);
    }


    char addr_of_database[256];
    strcpy(addr_of_database,name_of_database_for_table);
    char *ch = strdup(tableName.data());
    char *addr_of_table = strcat(ch,".dat");
    char *addr_of_table_name = strcat(addr_of_database,addr_of_table);

    fstream binary_n;
    binary_n.open(addr_of_table_name,ios::in | ios::binary);

    int pos_1=Position_(_position,set_col);
    int pos_2=Position_(_position,find_col);
    int num = _length[0];
    //int len=0;

    //string intoTemp = "";
    int intoLength = 0;
    int count[200]= {0};
    int m=0;
    int key =0;
    for(int i=1; i<pos_1; i++)
    {
        intoLength+=_length[i];
    }
    int _intoLength = intoLength;
    while(!binary_n.eof())
    {

        for(int i=1; i<num+1; i++)
        {

            /*if(i == pos_1)
            {
                int length_1 = _length[i];
                intoLength = length_1;

                char _target[100] = {0};
                binary_n.read(_target,length_1);
                cout<<_target;
                intoTemp += _target;

            }*/
            if(i == pos_2)
            {
                int length_2 = _length[i];
                char _source[100] = {0};
                binary_n.read(_source,length_2);
                if(length_2 == 8)
                {
                    if(is_double(_source))
                    {
                        double _cmp = atof(_source);
                        if(atof(find_values.c_str()) == _cmp)
                            is_find = 'Y';
                    }
                    else
                    {
                        find_values = removeQuotation(find_values);
                        if(strcmp(_source,find_values.c_str()) == 0)
                            is_find = 'Y';
                    }
                }
                else if(length_2 == 4)
                {
                    if(is_int(_source))
                    {
                        int _cmp = atoi(_source);
                        if((atoi(find_values.c_str())) == _cmp)
                            is_find = 'Y';
                    }
                    else
                    {
                        find_values = removeQuotation(find_values);
                        if(strcmp(_source,find_values.c_str()) == 0)
                            is_find = 'Y';
                    }
                }
                else
                {
                    find_values = removeQuotation(find_values);
                    if(strcmp(_source,find_values.c_str()) == 0)
                        is_find = 'Y';
                }

            }
            else
            {
                int offset = _length[i];
                binary_n.seekg(offset,ios_base::cur);
                offset = 0;
            }
        }

        if(is_find == 'Y')
        {
            //binary_t.write(intoTemp.c_str(),intoLength);
            key++;
            count[m++]=intoLength;
            //binary_n.write(intoTemp.c_str(),intoLength);
            is_find = 'N';
           // intoTemp = "";
        }
        intoLength+=returnSum(_length);
    }
    binary_n.close();
    
    fstream binary_;
    binary_.open(addr_of_table_name,ios::out | ios::binary | ios::in);
    for(int i=0; i<key; i++)
    {
        binary_.seekg(count[i],ios::beg);
        binary_.write(set_values.c_str(),_length[pos_1]);
        //
        //char _temp[100] = {0};
        //binary_.seekg(-(_intoLength+_length[pos_1]),ios_base::cur);
        //bianry_.read(_temp,returnSum(_length));
        //string into_temp = _temp;
        //memset(_temp,0,100);
        //
        //writeIntoTemp(into_temp)
    }
    _position = "";
    memset(_length,0,100);

    binary_.close();


}

void discribleTable(string tableName){
     char addr_of_database[256];
     strcpy(addr_of_database,name_of_database_for_table);
     char *addr_of_model = strcat(addr_of_database,"model.dat");
     fstream binary_model;
     binary_model.open(addr_of_model,ios::in | ios::binary); 
     int length = 0;
     char name[9] = {0};
     char table_name[9] = {0};
     
     
     while(!binary_model.eof()){
            //
            binary_model.read((char*)&length,4);
            binary_model.read(name,8);
            int i_1 =0;
            for(int i=0;i<9;i++){
                    if((name[i] != '0') && (name[i] != '\0'))
                                table_name[i_1++] = name[i];                 
            }  
            if(strcmp(table_name,tableName.c_str()) == 0){
                    char temp[100] = {0};
                    binary_model.read(temp,length-8);
                    cout << temp << endl;
                    break;                                
            }
            else{
                      binary_model.seekg(length-8,ios_base::cur);
                      memset(name,0,9);
                      memset(table_name,0,9);
                      length = 0;
            }                         
     } 
     binary_model.close();    
}
