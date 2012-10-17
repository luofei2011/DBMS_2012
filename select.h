#include<iostream>
#include<fstream>
#include<string>
using namespace std;

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
     binary_dictionary.read((char*)&num_of_property,4);
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
                              if(str1.compare(property_name_string.substr(0,property_name_string.find(" "))) == 0)
                                         return true;                                                                                                                           
                              property_name_string = property_name_string.substr(property_name_string.find(" ")+1);                                   
                      } 
                      property_name_string = "";
              }
              else
                  binary_search.seekg(length_of_property,ios_base::cur);
              memset(table_name,0,9);
              memset(name,0,9);
     } 
     return false;                       
}

int deal_condition(string str){
    transform(str.begin(),str.end(), str.begin(), ::toupper); 
    if(str.find("NOT") != str.npos)
                       return 1;
    else if(str.find("OR") != str.npos)
                       return 2;
    else if(str.find("AND") != str.npos)
                       return 3;
    else if(str.find('<') != str.npos){
         if(str.find('='))
                          return 7;
         return 4;
    }
    else if(str.find('=') != str.npos)
                       return 5;
    else if(str.find('>') != str.npos){
         if(str.find('=') != str.npos)
                          return 8;
         return 6;
    }
    else
        return 0;
                           
}

//select_function(target_property,table_name,select_condition); 
bool select_function(string str1,string str2,string str3){
     //only one property to search
     if(is_correct_property(str1,str2)){
            
            /****************deal select_condition****************************/ 
            int result = deal_condition(str3);
            /*****open dictionary.dat, property_name.dat, table_name.dat******/
            char addr_of_database[256];
            strcpy(addr_of_database,name_of_database_for_table);
            char *addr_of_model = strcat(addr_of_database,"model.dat");
            fstream binary_d;
            fstream binary_p;
            fstream binary_n;
            
            binary_d.open("dictionary.dat",ios::in | ios::binary);
            binary_p.open("property_name.dat",ios::in | ios::binary);
            binary_n.open(addr_of_model,ios::in | ios::binary);
            
            while(!binary_n.eof()){
                                          
            }
            
            binary_d.close();
            binary_p.close();
            binary_n.close();
     }
     else
         return false;
     return true;     
}
