
//
// Created by tomtom on 15/02/19.
//

//Libraries---------------------------------
#include <string>
#include <vector>
#include<iostream>
#include<iomanip>

//Namespaces--------------------------------
using namespace std;

//Definitions-------------------------------
const string WHITE_SPACES = " \t\n\r\f\v";

//-------------------------------------------------------------------------------------//
//Trimming functions, slightly altered this code : https://stackoverflow.com/a/25385766//
//-------------------------------------------------------------------------------------//

// trim from end of string (right)
inline std::string &rtrim(std::string &s) {
    s.erase(s.find_last_not_of(WHITE_SPACES) + 1);
    return s;
}

// trim from beginning of string (left)
inline std::string &ltrim(std::string &s) {
    s.erase(0, s.find_first_not_of(WHITE_SPACES));
    return s;
}

// trim from both ends of string (right then left)
inline std::string &trim(std::string &s) { return ltrim(rtrim(s)); }
