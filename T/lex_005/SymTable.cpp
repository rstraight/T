

#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SymTable.h"

using namespace std;

SymTable::SymTable()
{
    //ctor
}

SymTable::~SymTable()
{
    //dtor
}

//==================================================================
int SymTable::addSymbol(string name, string value)
{

    if(getSymbol(name) == "FREE"){
        sym.push_back(name);
        val.push_back(value);
        return 0;
    }

    return -1;
}

//==================================================================
int SymTable::setSymbol(string name, string value)
{
    for(int i = 0; i < sym.size(); i++){
       if(sym[i] == name){ val[i] = value; return 0; };
    }//for
    return -1;

}

//==================================================================
int SymTable::setSymbol(string name, int value)
{
    char buf[100];
    sprintf(buf, "%i", value);

    for(int i = 0; i < sym.size(); i++){
       if(sym[i] == name){ val[i] = buf; return 0; };
    }//for
    return -1;

}

//==================================================================
string SymTable::getSymbol(string name)
{
    for(int i = 0; i < sym.size(); i++){
       if(sym[i] == name){ return val[i]; };
    }//for
    return "FREE";

}

//==================================================================
int SymTable::getSymbolInt(string name)
{
    for(int i = 0; i < sym.size(); i++){
       if(sym[i] == name){
           char * ptr_end;
           int v = strtod(val[i].c_str(), &ptr_end);
           return v;
           };
    }//for
    return -1;

}
