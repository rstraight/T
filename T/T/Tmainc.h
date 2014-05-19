//========================================================================== 
//                            File:	Tmainc
//                            Author:
//                            Date:	1-11-14
//                            
//                            
//                            Notes:    Handy functions and macros
//                                      #include "Tmainc.h"
//                                      gcc yoursource.cpp 
//                                      ./a.out -f filename.x
//==========================================================================                           

//========================================================================== 
//
//	DEFINES		T_USAGE, TRUE, FALSE, MAXBUFFER, MAXPARAM
//      VARIABLES       T_fileName, T_inputFile, T_ArgArray             
//      FUNCTIONS	T_printArgs, T_usage, T_getInputFile, T_getArgs
//
//==========================================================================
#pragma GCC system_header
#include "Tebug.h"

#define MAXPARAM	10
#define MAXBUFFER	100

/* Redefine FALSE and TRUE */
#ifndef FALSE
#define FALSE 0
#endif
 
#ifndef TRUE
#define TRUE 1
#endif

char T_fileName[MAXBUFFER];
char T_inputFile[MAXBUFFER];
char T_ArgArray[MAXBUFFER];
char T_UserArg[MAXBUFFER];

int numArgs   = 0;
char *delimit;
int T_saveFlag   = FALSE;
int T_argStatus  = 0b00000000;  //each bit represents an arg status

void T_loadArgs(int argc, char **argv, char *arguments);
int T_saveArgs(int argc, char **argv, char *delim );
char *T_getInputFile( int argc, char **argv );
int T_testParam(char flag);
void T_printArgs( int argc, char **argv );
void T_printArgs( int argc, char **argv );

/* command line usage message */
/* REDEFINE FOR SPECIFIC APPLICATION */
#ifndef T_USAGE
#define T_USAGE \
"\nUsage:  compiler [-x|-y] -f <file>\n"\
"\n"\
"The following are valid command-line options:\n"\
"\n"\
"  -x    TEXT FOR SWITCH.\n"\
"  -y    TEXT FOR SWITCH.\n"\
"\n"\
"  -f <filename>     Specify the source file.\n"
#endif



/* T_usage(FILE* location)             T_usage(stdout) or T_usage(pFile) */
void T_usage(FILE* location)
{   
    if(location == NULL){location = stdout;}
    fprintf(location, "Usage: %s \n", T_USAGE);
}

//========================================================================== 
//
//	Functions for managing command line args
//
//==========================================================================

/* T_printArgs       Prints command line args   ex. printArgs(argc, argv ); */
void T_printArgs( int argc, char **argv ){
  int i;
  for(i = 0; i < argc; i++){
    printf("arg %d = %s \n", i, argv[i]);
  }//for
}//printArgs



/* T_getArgs  Get command line args   ex. printf(" Args=%s \n", T_getArgs(argc, argv, " " )); */
char *T_getArgs( int argc, char **argv, char *delim ){
  int i;
  if(!T_saveFlag){ T_saveArgs(argc, argv, delim ); }
  if(argc <= 0){ return "No input args"; }
  if(argc > MAXPARAM){ return "Too many input args"; }
  for(i = 1; i < argc-1; i++){
    sprintf(T_ArgArray + strlen(T_ArgArray), (char*)argv[i]);
    sprintf(T_ArgArray + strlen(T_ArgArray), delim);
  }//for
 
  return T_ArgArray;
}//T_getArgs



/* T_getInputFile       Get command line args   ex. getArgs(argc, argv ); */
char *T_getInputFile( int argc, char **argv ){
  if(!T_saveFlag){ T_saveArgs(argc, argv, ", " ); }
  if(argc <= 0){ return "No input args"; }
  if(argc > MAXPARAM){ return "Too many input args"; }
  sprintf(T_inputFile + strlen(T_inputFile), (char*)argv[argc-1]);
  return T_inputFile;
}//T_getInputFile



/* T_saveArgs    stores args in T_inputFile, T_ArgArray */
int T_saveArgs( int argc, char **argv, char *delim ){
  int i;
  numArgs = argc;
  delimit = delim;
  if(argc <= 0){ fprintf(stderr, "No input args"); }
  if(argc > MAXPARAM){ fprintf(stderr, "Too many input args"); }
  else{
  T_saveFlag = TRUE;  
  sprintf(T_inputFile, "%s", T_getInputFile(argc, argv ));
  sprintf(T_ArgArray, "%s", T_getArgs(argc, argv, "," ));
 
  };
}//T_saveArgs



/* T_loadArgs    load app specific args as string       */
/*                ex. T_loadArgs(argc, argv, "fhuv");   */
/*                    for options f, h, u, v            */
void T_loadArgs(int argc, char **argv, char *arguments){
  if(T_saveFlag == FALSE){ T_saveArgs(argc, argv, ", " ); }
  sprintf(T_UserArg + strlen(T_UserArg), arguments);
}//T_loadArgs



/* T_testParam       test single command line arg   ex. if(T_testParam('u')){ */
int T_testParam(char flag){
  
  int size = 0;
  char testc = ' ';
  int result = FALSE;
  if(!T_saveFlag){ return FALSE; }
  if(numArgs <= 0){ return FALSE; }
  if(numArgs > MAXPARAM){ return FALSE; }
  else
  {
    TRACE_STR(T_ArgArray);
  size = sizeof(T_ArgArray);  
  for(int i = 0; i<size; i++){
    testc = T_ArgArray[i];
     if(testc == flag){  return TRUE; }
   }//for
  }//else
  return FALSE;
}//T_testParam


/* T_processArgs       returns value with bits set representing status   */
/*                     ex. T_loadArgs(argc, argv, "fh");                 */
/*                         int val = T_processArgs();                    */
/*                         if(val == 0b00000001){ //process f };         */
/*                         if(val == 0b00000010){ //process h };         */
int T_processArgs(){
   T_STR("in func T_processArgs\n");
   TRACE_INT(T_saveFlag);
   TRACE_INT(numArgs-2);
  
   //T_STR("T_saveArgs must be called prior to calling this function");
  // if(T_saveFlag == FALSE){ return FALSE; }
  int result = 0;
  char c = ' ';
 // sizeof(T_UserArg)
  for(int i = 0; i<3; i++){
    c = (char)T_UserArg[i];
    TRACE_INT(i);
    TRACE_CHAR(c);
    if(T_testParam(c) == TRUE){
      result = result + (1 << i);
   T_INT(result);
    }//if    
  }//for
  
  return result;
}//T_processArgs


