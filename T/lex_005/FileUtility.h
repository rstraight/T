#ifndef FILEUTILITY_H
#define FILEUTILITY_H

#include <iostream>
#include <deque>
#include <stdio.h>
#include <string.h>

#include "Types.h"


using namespace std;

class FileUtility : Types
{
public:

    FileUtility();
    ~FileUtility();



    string filestr;  //string version of source set by readFile
    string outstr;   //string to be written to file

    int line_number;

    string readFile(char* file_name);                     //opens a file and returns it as a string and stores in filestr
    void writeOutputFile(char* file_name);               //writes outstr data to ascii file
    void writeFile(char* file_name, string file_string); //writes a file and returns write status as a string

    string displayInputFile();  //displays filestr
    string displayOutputFile(); //displays outstr

    int loadKeywords(deque<string> keywords);     //loads list of keywords, returns -1 for already loaded
    int loadTypes(deque<string> types);           //loads list of data types, returns -1 for already loaded
    int unloadKeywords(deque<string> keywords);   //clears list of keywords, returns -1 for error

    string keyword_check(string test_str);   //checks if keyword_list contains test_str, returns "KEYWORD" or "ID"
    int keyword_location(string test_str);  //returns the location of test_str in keyword_list, returns -1 for not found

    //=================================================
    //        Char functions
    //=================================================
    char getNextChar();  //returns the next char in filestr. cpos is used for position and is increamented
    char lookAheadChar();  //returns the next char in filestr without increamenting cpos

    //overloaded versions
    char getNextChar(string str);  //returns the next char in filestr. cpos is used for position and is increamented
    char lookAheadChar(string str);  //returns the next char in filestr without increamenting cpos

    int getCurrentPosition();  //returns read position (cpos), returns -1 for error
    int setCurrentPosition(int position);  //sets read position (cpos), returns -1 for out of range error

    void groupChars(string str, string delim); //removes whitespace and groups char by letters, numbers and op

    //=================================================
    //        Token
    //=================================================
    int getNumberTokens();
    void storeToken(string val, string typ);
    string getToken(int position);

    void storeTokenValue(string val);
    void storeTokenType(string typ);

    string getTokenValueString(int position);
    string getTokenTypeString(int position);





    int c;                    //current char
    unsigned int cpos;       //current position in file

    FILE *source;             //input stream
    FILE *output;             //output stream

    deque<string> keyword_list;   //list of keywords loaded by loadKeywords
    deque<string> types_list;     //list of data types loaded by loadTypes

    deque<string> tok_typ;       //list of token types
    deque<string> tok_val;       //list of token values


private:

};

#endif // FILEUTILITY_H
