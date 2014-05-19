/////////////////////////////////////////////////////////////////////
//
//              Tebug trace functions & macros
//              1-2-14
//
/////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TRUE		0b00000001
#define FALSE		0b00000010
#define ON		0b00000001
#define OFF	 	0b00000010

////////////////////////////TERMINAL OUT/////////////////////////////////////////
#define TRACE         printf ("FUNCTION = %s  ", __FUNCTION__); printf ("RET = %x\n", (unsigned int) __builtin_return_address(0))
#define TRACE_FILE    printf ("FILE = %s \n",  __FILE__)

#define ADDR(A)       printf("\n The address of " #A " is %x \n", (int) &A);

#define TRACE_STR(id)   printf(" " #id " %s\n", id)
#define TRACE_INT(id)   printf(" " #id " %d\n", id)
#define TRACE_FLOAT(id) printf(" " #id " %f\n", (double)id)


// A = Buffer
#define APPEND_STR(A, B)    sprintf(A + strlen(A), B)
#define APPEND_INT(A, B)    sprintf(A + strlen(A), "%d", (int)B)
#define APPEND_FLOAT(A, B)  sprintf(A + strlen(A), "%f", (double)B)
#define APPEND_HEX(A, B)    sprintf(A + strlen(A), "%.2x", (unsigned int)B)
#define CLEAR_BUFFER(A)     memset(A, 0, strlen(A))  


//////////////////////////////LOG FILE/////////////////////////////////////////////
char TBuffer[100];
FILE * pFile;

void openLog(char *fileName){
  pFile = fopen(fileName ,"w");
  if(pFile == NULL){
    printf("\nError opening file %s\n", fileName);
  }
}

void closeLog(){
 fclose (pFile);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////

#define LOG_LINE_BREAK  	fprintf(pFile,"\n//============================================================//");
#define LOG_COMMENT     	fprintf(pFile,"\n//" );
#define LOG_NEW_LINE    	fprintf(pFile,"\n" );
#define LOG_NEW_NEW_LINE   	fprintf(pFile,"\n\n" );
#define LOG_TAB     	        fprintf(pFile,"\t" );

/////////////////////////////////////////////////////////////////////////////////////////////////////
// dot -Tpng input.dot > output.png
int graph_index = 0;

#define GRAPH_START	  	openLog("func_calls.dot"); fprintf(pFile,"\n graph g {\n");
#define GRAPH_END	  	fprintf(pFile,"\n}\n"); closeLog();
#define GRAPH_A                fprintf(pFile,"\t%s -- ",  __FUNCTION__); graph_index++; 
#define GRAPH_B                fprintf(pFile,"%s;\n",  __FUNCTION__); graph_index = 0; 
#define GRAPH_CALL      	if(graph_index == 0) { GRAPH_A } else { GRAPH_B }



/////////////////////////////////////////////////////////////////////////////////////////////////////

#define LOG_STR_STR(A, B)     	fprintf(pFile,"    %s   %s", A, B);
#define LOG_STR(A)  	        fprintf(pFile," %s ",A );
#define LOG_INT(A)  	        fprintf(pFile," %d ",A );
#define LOG_FLOAT(A)  	        fprintf(pFile," %0.4f ",A );




/////////////////////////////////////////////////////////////////////////////////////////////////////

