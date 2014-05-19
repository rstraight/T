	
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define ID   100
#define INT  200
#define EQ   300
#define END  1000

#define AND  5000
#define OR   5500

#define ECHO(id)  printf(" %d ", id)

int fileArray[10] = {ID, EQ, INT, END};

int currType = 0;
int currPos = 0;

bool match(int t){
	return (currType == t);
}

int getNext(){
	int result;
	result = fileArray[currPos++];
	if(result==NULL){ exit(0); }
	return result;
}
/*     ex. and(&match(int), 3, ID,   EQ,  DIGIT);   */
bool and(  bool (*functionPtr)(int),  int  num_args, ...){
	 int ntype;
	 va_list ap; 
	 int loop;
	 
	va_start(ap, num_args );
   
	for(loop=0; loop<num_args; loop++){
		ntype = va_arg(ap, int);
		if(!(*functionPtr)(ntype)){ 
			 return false;
			 }
		else{
			 ECHO(ntype);
			}
		}
	 va_end(ap);
     return true;
};


/*     ex. or(&match(int), 2, ID, DIGIT);   */
bool or(  bool (*functionPtr)(int),  int  num_args, ...){
	 int ntype;
	 va_list ap; 
	 int loop;
	 
	va_start(ap, num_args );
   
	for(loop=0; loop<num_args; loop++){
		ntype = va_arg(ap, int);
		if((*functionPtr)(ntype)){ 
			ECHO(ntype);
			 return true;
			 }
		}
	 va_end(ap);
   	return false;
};


bool assignment(){  
	return (and(&match,2, ID, EQ) && or(&match,2, ID, INT));
};


void main(){
	 	ECHO(88);
	 assignment();
};