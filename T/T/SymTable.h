#ifndef SYMTABLE_H
#define SYMTABLE_H

#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

class SymTable
{
    public:

        SymTable();
       ~SymTable();

       int addSymbol(string name, string value);
       int setSymbol(string name, string value);
       int setSymbol(string name, int value);
       string getSymbol(string name);

       int getSymbolInt(string name);

    private:

        deque<string> sym;
        deque<string> val;
};

#endif // SYMTABLE_H
