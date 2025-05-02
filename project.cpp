#include<iostream>
#include<algorithm>
#include "classes.h"
using namespace std;


int main(){
    Prison prison;
    prison.mainMenu();   //starts from here and then goes from function to function


    
    return 0;
}



bool intCheck()
{
    
    if (cin.fail()) //if something other than integer has been entered;  cin.fail() gives true
    {
        cin.clear(); //delete the input
        cin.ignore(100, '\n'); //ignore any characters left
        cout << ">>> Please Enter valid input <<<" << endl;
        return false; 
    }
    else{
        return true;
    }
}
// converts a string with capital alphabets to lower alphabets
string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}
// checks if a name is valid or not (if name has integers then its invalid)
bool stringcheck(string &value)
{   
    // Check if string is empty
    if (value.empty())
    {
        return false;
    }else{
        // Check each character, if only one is integer, return false
        for (char x : value)
        {
            if (isdigit(x))
            {
                return false;
            }
        } //if false not returned means name is valid, return true
        return true;
    }
}

