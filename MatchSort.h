#include<iostream>
#include<string>
using namespace std;

//find two """;
bool findTwoQuotation(string str){
    if((str[0] == '"') && (str[str.size()-1] == '"'))
               return true;                    
    else
        return false;    
}

bool isInt(string str){
     /*for(int i=0; i<str.size(); i++){
             if((str[i] >= "0") && (str[i] <= "9"))
                        return true;
             else 
                  return false;        
     } */
     return true;    
}

bool isChar(string str){
     if(findTwoQuotation(str))
         return true;
     else
         return false;     
}

bool isDate(string str){
     if(findTwoQuotation(str))
//         if((str[4] == "-") && (str[7] == "-"))
                    return true;
     else
         return false;     
}

bool isTime(string str){
     if(findTwoQuotation(str))
//         if((str[2] == ":") && (str[5] == ":"))
                    return true;
     else
         return false;     
}

bool isDouble(string str){
     /*for(int i=0; i<str.size(); i++){
             if((str[i] >= '.') && (str[i] <= '9'))
                        return true;
             else 
                  return false;        
     }    */
     return true;  
}

