#include <iostream>
#include <string>
#include <stdio.h>
#include "Types.h"

#define CHAR    c.at(0)

#define ISNUMB  ( (c <= '9') && (c >= '0') )
#define ISALPH_LOWER  ( (c >='a') && (c <='z') )
#define ISALPH_UPPER  ( (c >='A') && (c <='Z') )
#define ISALPH  ( ISALPH_LOWER || ISALPH_UPPER )

#define ISOP_COMP    ( (c=='>') || (c=='<') )
#define ISOP_MATH    ( (c=='+') || (c=='-') || (c=='*') || (c=='/') || (c=='^') || (c=='.') || (c=='>') || (c=='<') || (c=='=') )
#define ISOP_ASSIGN  (c=='=')

#define ISOP_DQUOTE  (c=='\"')
#define ISOP_SQUOTE  (c=='\'')
#define ISOP_QUOTE   ( (ISOP_DQUOTE || ISOP_SQUOTE ) )
#define ISOP_BRACE   ( (c=='(') || (c==')') || (c=='{') || (c=='}') || (c=='[') || (c==']') || (c=='\"') || (c=='\''))
#define ISOP_SPECIAL ( (c=='#') || (c=='%') || (c=='@') || (c=='&') || (c=='!') || (c=='_') || (c=='~') || (c=='|') || (c=='?') || (c==':') || (c==';'))
#define ISOP_SEMI     (c==';')
#define ISOP         ( ISOP_MATH || ISOP_ASSIGN || ISOP_BRACE || ISOP_QUOTE || ISOP_SPECIAL)

#define IS_ESC_NEWLINE    ( (c=='\n') || (c=='\r') || (c=='\f') )
#define IS_ESC_WHITE      ( (c==' ') || (c=='\t') )
#define IS_ESC_CNTR    ( (c=='\b') || (c=='\v') )
#define IS_ESC       ( IS_ESC_NEWLINE || IS_ESC_CNTR || IS_ESC_WHITE)

#define IS_VALID    ( ISNUMB && ISALPH && ISOP && IS_ESC && IS_ESC_WHITE && ISOP_QUOTE )
#define IS_INVALID  ( !ISNUMB && !ISALPH && !ISOP && !IS_ESC && !IS_ESC_WHITE && !ISOP_QUOTE )


Types::Types()
{

}

Types::~Types()
{

}


//======================= BROARD CAT ===============================
//test for broad categories
bool Types::is_White(const char c)
{
    return ( IS_ESC_WHITE  );
}

bool Types::is_Invalid(const char c)
{
    return ( IS_INVALID  );
}

bool Types::is_Valid(const char c)
{
    return ( IS_VALID );
}

bool Types::is_Newline(const char c)
{
    return ( IS_ESC_NEWLINE );
}

bool Types::is_Esc(const char c)
{
    return ( IS_ESC );
}

bool Types::is_Digit(const char c)
{
    return ( ISNUMB );
}

bool Types::is_Alpha(const char c)
{
    return ( ISALPH );
}

bool Types::is_Op(const char c)
{
    return ( ISOP );
}

bool Types::is_Brace(const char c)
{
    return ( ISOP_BRACE );
}

//======================= NAME DETAIL ===============================
//test for more detail
string Types::Name(const char c)
{


  //=======================ALPHA DIGIT
   if(is_Alpha(c)) { ident += c; return "ID"; };
   if(is_Digit(c)) { number += c; return "NUMBER"; };

  //=======================MATH
  op += c;
   if(ISOP_MATH) {
    switch(c)
    {
      case '+':
         return "OP_PLUS";
      break;

      case '-':
         return "OP_MINUS";
      break;

      case '*':
         return "OP_MUL";
      break;

      case '/':
         return "OP_DIV";
      break;

      case '^':
         return "OP_POW";
      break;

      case '.':
         return "OP_DOT";
      break;

      case '>':
         return "OP_GT";
      break;

      case '<':
         return "OP_LT";
      break;

      case '=':
         return "OP_ASSIGN";
      break;
      }//SWITCH
    }//MATH

    //=======================BRACE
    if(ISOP_BRACE) {
    switch(c)
    {
      case '(':
         return "OP_LPAREN";
      break;

      case ')':
         return "OP_RPAREN";
      break;

      case '[':
         return "OP_LBRAC";
      break;

      case ']':
         return "OP_RBRAC";
      break;

      case '{':
         return "OP_LCURL";
      break;

      case '}':
         return "OP_RCURL";
      break;

      case '\"':
         return "OP_DQUOTE";
      break;

      case '\'':
         return "OP_SQUOTE";
      break;
      }//SWITCH
    }//BRACE

    //==========================ESC
  if(IS_ESC){
      if(IS_ESC_NEWLINE){ return "NEWLINE"; };
      if(IS_ESC_WHITE ){ return "WHITESPACE"; };
      if(IS_ESC_CNTR ){ return "CONTROL"; };
      return "ESCAPE";
    }//ESC
    //==========================SPECIAL
  if(ISOP_SPECIAL){
    if(c == '#'){ return "OP_POUND"; };
    if(c == '%'){ return "OP_PERCENT"; };
    if(c == '@'){ return "OP_AT"; };
    if(c == '&'){ return "OP_AMPER"; };
    if(c == '!'){ return "OP_EXCLA"; };
    if(c == '_'){ return "OP_UNDER_SCORE"; };
    if(c == '~'){ return "OP_TILDA"; };
    if(c == '|'){ return "OP_PIKE"; };
    if(c == '?'){ return "OP_QUESTION"; };
    if(c == ':'){ return "OP_COLEN"; };
    if(ISOP_SEMI){ return "OP_SEMI"; };
   }//SPECIAL

   //to satisfy my compiler
   return "OP_UNKNOWN";

}

string Types::Brace_Name(const char c)
{

    return "Brace";
}

string Types::Esc_Name(const char c)
{

    return "Esc";
}
