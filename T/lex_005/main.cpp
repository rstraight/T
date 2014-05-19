//==================================================================================================
//                        Project: lex
//
//                        Notes 11-08-13: currently main is being used as a test bed
//                                        As functions are validated I will move them in to class files
//
//                        Types:       tests char Type and Value, returns string ( LETTER, DIGIT, OP_ASSIGN etc. )
//                        FileUtiliy:  stores the Type/Value pairs in an stl deque structure
//
//                        FileUtiliy:  inherents Types. reads/writes ascii files. uses string type for input and output
//
//                        SymTable:    holds list of ID/Value pairs
//
//                        ToDo 11-09-13:
//                                      need to transfer Token functions to new class
//                                      need to track line and col info for error reporting
//==================================================================================================


#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <stdio.h>
#include <string.h>

#include "Types.h"
#include "FileUtility.h"
#include "SymTable.h"

using namespace std;


string expression = "NUMBER OP";
FileUtility f;
SymTable variable;

int main( int argc, char * argv[] )
{

    char pgm[120]; /* source code file name */
    if (argc != 2)
    {
        cout << "\n-----FileUtility test-----\n" <<  endl;

        deque<string> keywords;
        keywords.push_back("if");
        keywords.push_back("while");
        keywords.push_back("return");
        keywords.push_back("printf");
        f.loadKeywords(keywords);

        deque<string> types;
        types.push_back("int");
        types.push_back("void");
        types.push_back("char");
        types.push_back("float");
        f.loadTypes(types);


        f.readFile("d.c");

        f.displayInputFile();
        f.displayOutputFile();
        f.writeOutputFile("output_2.csv");

        cout << "\n----------------\n" << f.getToken(0) << endl;
        cout << "\n----------------\n" << f.getToken(1) << endl;
        cout << "\n----------------\n" << f.getToken(2) << endl;

        cout << "\n-----Number of tokens-----\n" << f.getNumberTokens() << endl;



        cout << "\n-----SymTable test-----\n" <<  endl;

        cout << "\n----- Adding symbols a, b and c -----\n" <<  endl;
        variable.addSymbol("a", "13");
        variable.addSymbol("b", "200");
        variable.addSymbol("c", "300");


        cout << "\t\t\t a as str = " << variable.getSymbol("a") << endl;
        cout << "\t\t\t b as str = " << variable.getSymbol("b") << endl;
        cout << "\t\t\t c as str = " << variable.getSymbol("c") << endl;

        cout << "\n\n" <<  endl;

        int a = variable.getSymbolInt("a");
        int c = a * 100;
        variable.setSymbol("c", c);

        cout << "\t\t\t c = a * 100 " << variable.getSymbolInt("c") << endl;
    }//if (argc != 2)



    return 0;
}
