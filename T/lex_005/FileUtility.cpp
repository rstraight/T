#include <iostream>
#include <sstream>
#include <deque>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileUtility.h"

using namespace std;

FileUtility::FileUtility()
{
    //ctor
}

FileUtility::~FileUtility()
{
    //dtor
}

//==================================================================
string FileUtility::readFile(char* file_name)
{


    source = fopen(file_name,"r");
    if (source==NULL)
    {
        fprintf(stderr,"File %s not found\n",file_name);
    }
    else
    {
        do
        {

            c = fgetc(source);
            filestr += c;

        }
        while(c != EOF);

        groupChars(filestr, ", ");

        fclose(source);


    }

    return filestr;
}//end readfile

//========================================================================
void FileUtility::writeOutputFile(char* file_name)
{
    writeFile(file_name, outstr);
}//end writeOutputFile

//========================================================================
void FileUtility::writeFile(char* file_name, string file_string)
{
    //write output file
    output = fopen(file_name, "w+");
    fputs(file_string.c_str() , output);
    fclose(output);
}//end writeFile

//========================================================================
string FileUtility::displayInputFile()
{

    if(!filestr.empty())
    {
        cout << "\n ----------------------------Input File-------------------------------------\n" << filestr << endl;
        return filestr;
    }

    return "Input file empty";
}//end displayInputFile

//========================================================================
string FileUtility::displayOutputFile()
{
    if(!outstr.empty())
    {
        cout << "\n ----------------------------Output File-------------------------------------\n" << outstr << endl;
        return outstr;
    }

    return "Output file empty";
}//end displayOutputFile


//========================================================================
int FileUtility::loadKeywords(deque<string> keywords)
{
    //check if list is empty
    if(keyword_list.size() < 1)
    {
        keyword_list = keywords;
        return 0;
    }

    //list not empty
    return -1;
}

//========================================================================
int FileUtility::loadTypes(deque<string> types)
{
    //check if list is empty
    if(types_list.size() < 1)
    {
        types_list = types;
        return 0;
    }

    //list not empty
    return -1;
}

//========================================================================
int FileUtility::unloadKeywords(deque<string> keywords)
{
    //check if list is empty
    if(keyword_list.size() < 1)
    {

        return -1;
    }

    //list not empty
    keyword_list.clear();
    return 0;

}


//========================================================================
string FileUtility::keyword_check(string test_str)
{
    string result = "ID";
    if(keyword_list.empty() || types_list.empty()){ return "----"; };
    //check keyword list for match
    unsigned int i = 0;
    for(i=0; i < keyword_list.size()-1; i++)
    {
        if( test_str == keyword_list[i] )
        {
            result = "KEYWORD";
        };
    }

    //check types list for match
    for(i=0; i < types_list.size()-1; i++)
    {
        if( test_str == types_list[i] )
        {
            result = "TYPE";
        };
    }

    //match not found return default ID
    return result;

}//end keyword_check

//=========================================================================
int FileUtility::keyword_location(string test_str)
{
    //find keyword
    unsigned int i = 0;
    for(i=0; i < keyword_list.size()-1; i++)
    {
        if( test_str == keyword_list[i] )
        {
            return i;
        };
    }

    //match not found
    return -1;

}//end keyword_location

//=========================================================================
char FileUtility::getNextChar()
{
    //eof check
    if(cpos < filestr.length()-1)
    {
        ++cpos;
        c = filestr.at(cpos);
        return c;
    }

    //error
    return -1;

}//end getNextChar

//=========================================================================
char FileUtility::lookAheadChar()
{
    //eof check
    if(cpos < filestr.length()-1)
    {
        c = filestr.at(cpos+1);
        return c;
    }

    //error
    return -1;

}//end lookAheadChar

//=========================================================================
char FileUtility::getNextChar(string str)
{
    //eof check
    if(cpos < str.length()-1)
    {
        ++cpos;
        c = str.at(cpos);
        return c;
    }

    //error
    return -1;

}//end getNextChar str

//=========================================================================
char FileUtility::lookAheadChar(string str)
{
    //eof check
    if(cpos < str.length()-1)
    {
        c = str.at(cpos+1);
        return c;
    }

    //error
    return -1;

}//end lookAheadChar str

//=========================================================================
int FileUtility::getCurrentPosition()
{
    return cpos;
}

//=========================================================================
int FileUtility::setCurrentPosition(int position)
{
    //eof check
    if(cpos < filestr.length()-1)
    {
        c = filestr.at(cpos+1);
        return c;
    }

    //error
    return -1;
}

//==========================================================================
void FileUtility::groupChars(string str, string delim)
{

    unsigned int i = 0;
    unsigned int tch = 0;

    //write header
    outstr += "VALUE";
    outstr += delim;
    outstr += "TYPE";
    outstr += '\n';

    do
    {

        c = getNextChar(str);

        //eat whitespace
        while(is_White(c) && (c != EOF))
        {
            c = getNextChar(str);
        }

        //capture newline
        if(is_Newline(c))
        {
            outstr += "NEWLINE";
            outstr += delim;
            outstr += "NEWLINE";
            outstr += '\n';

            line_number++;

            storeToken("NEWLINE", "NEWLINE");
        }

        //keyword ID type
        if(is_Alpha(c))
        {
            string tkw;
            tch = c;

            while(is_Alpha(c))
            {
                outstr += c;
                tkw += c;
                c = getNextChar(str);
            }

            outstr += delim;
            //value
            string new_tok_val = tkw;
            tok_val.push_back(new_tok_val);

            //check for KEYWORD or ID
            //then check for TYPE
            outstr += keyword_check(tkw);
            outstr += '\n';
            //type
            string new_tok_typ = keyword_check(tkw);
            tok_typ.push_back(new_tok_typ);



        }//alpha

        //digits
        if(is_Digit(c))
        {
            string tdigit;  //val
            tch = c;   //type

            while(is_Digit(c))
            {
                outstr += c;
                tdigit += c;
                c = getNextChar(str);
            }
            outstr += delim;
            //val
            string new_tok_val = "";
            new_tok_val += tdigit;
            tok_val.push_back(new_tok_val);


            outstr += Name(tch);
            outstr += '\n';
            //type
            string new_tok_typ = Name(tch);
            tok_typ.push_back(new_tok_typ);
        }//Digit

        //op
        if(is_Op(c))
        {

            outstr += c;
            outstr += delim;


            outstr += Name(c);
            outstr += '\n';
            //value
            string new_tok_val ="";
            new_tok_val = c;

            //type
            //string new_tok_typ = Name(c);
            //tok_typ.push_back(new_tok_typ);
            storeToken(new_tok_val, Name(c));

        }//Op


    } while(c != -1);

}//end groupChars

//==========================================================================
//                           TOKENS
//==========================================================================
int FileUtility::getNumberTokens()
{
    return tok_val.size();
}

//==========================================================================
void FileUtility::storeToken(string val, string typ)
{
    storeTokenValue(val);
    storeTokenType(typ);
}

//==========================================================================
void FileUtility::storeTokenValue(string val)
{
    //value
    string new_tok_val = val;
    tok_val.push_back(new_tok_val);
}

//==========================================================================
void FileUtility::storeTokenType(string typ)
{
    //type
    string new_tok_typ = typ;
    tok_typ.push_back(new_tok_typ);

}

//==========================================================================
string FileUtility::getToken(int position)
{
    string result;

  if(!tok_val.empty() && (position < tok_val.size()) )
    {
    result += getTokenValueString(position);
    result += " ";
    result += getTokenTypeString(position);
    result += " ";
    return result;
    }

    return "Out of range";
}

//==========================================================================
string FileUtility::getTokenValueString(int position)
{
    if(!tok_val.empty() && (position < tok_val.size()) )
    {
        return tok_val[position];
    }

    return "Out of Range";
}

//==========================================================================
string FileUtility::getTokenTypeString(int position)
{
    if(!tok_typ.empty() && (position < tok_typ.size()) )
    {
        return tok_typ[position];
    }

    return "Out of Range";

}


