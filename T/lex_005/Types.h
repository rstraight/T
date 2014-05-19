/*
====================================================================
        Project:   Lex
        Module:    Types

        Purpose:   Classify characters and  (isDigit, isCommentStart, symbol etc)


        Revisions: 11-07-13 creation

====================================================================
*/
#ifndef TYPES_H
#define TYPES_H

#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

class Types
{
    public:

        Types();
        virtual ~Types();

        //test for broad categories (quicker)
        bool is_White(const char c);

        bool is_Digit(const char c);
        bool is_Alpha(const char c);

        bool is_Op(const char c);
        bool is_Brace(const char c);
        bool is_Esc(const char c);

        bool is_Invalid(const char c);
        bool is_Valid(const char c);

        bool is_Newline(const char c);

        //test for more detailed name
        string Name(const char c);
        string Brace_Name(const char c);
        string Esc_Name(const char c);

        string ident;
        string number;
        string op;
  //  private:







};

#endif // TYPES_H
