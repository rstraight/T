	
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


char* typeStr[20] ={  "type", "id", "int", "eq", "rp", "lp", "or", "comma", "plus", "minus", "eof", "end" , "LC", "RC", "CMD"};

#define TYPE   0
#define ID   1
#define INT  2
#define EQ   3
#define RP   4
#define LP   5
#define OR   6
#define COMMA   7
#define PLUS   8
#define MINUS  9
#define EOF  10
#define END  11

#define LC  12
#define RC  13
#define CMD  14


#define DEBUG 1
#define ECHO(id)  printf(" %d \n", id)

#define DISPLAY(s)  printf(" %s, \n currType %d, \n  currPos %d \n",s, currType, currPos )

//int fileArray[10] = {ID, EQ,ID, END, EOF};
//int fileArray[10] = {ID, PLUS,INT, END};
int fileArray[10] = { ID, EQ,ID, END, EOF};


//forward decl
bool expr();

int currType = 0;
int currPos = 0;
int savePos = 0;
int saveType = 0;

void savePosition(){
	 savePos = currPos;
	 saveType = currType;
	 DISPLAY("\n.savePosition ");
	 ECHO(currPos);
	 
};

void restorePosition(){
	 currPos = savePos;
	 currType = saveType;
	 DISPLAY(".restorePosition ");
	 ECHO(currPos);
	 
};


bool match(int t){
	return (currType == t);
}

int getNext(){
	
	 currType = fileArray[currPos++];
	 printf(" %s \n", typeStr[currType]);
	if(currType==NULL){ DISPLAY(" NULL "); exit(0); }
   if(currType==EOF){ DISPLAY(" EOF "); exit(0); }
	return currType ;
}



/*
	
	<program> --> (<vardecl> ¦ <func> )* <main>
	 <vardecl> --> TYPE ID END
	 <func> --> TYPE ID LP RP <stmblock> END
	 <main> --> VOID MAIN LP RP <stmblock> END
	 <stmblock>  --> LC ( <expr> END ¦ <cmd> END )* RC
	 <expr> -->.  <arithmetic> ¦ assignment ¦ var
    < assignment  > --> ID EQ (ID ¦ INT ¦ <expr> )
    <arithmetic> --> ID (PLUS ¦ MINUS ) (ID ¦ INT)
    var  --> ID
*/

////////////////////
bool assignment(){  
	bool r;
	// savePosition();
	if(!match(ID)){ 
		// restorePosition(); 
		return false;}
	getNext();
	 if(!match(EQ)){ 
	 //	 restorePosition(); 
	 	return false;}
	getNext();
	 switch(currType){
		case ID:
		 DISPLAY(".ASSG ID. ");
		break;
		case INT:
		 DISPLAY(".ASSG INT ");
		break;
		
		} 	
		if(!expr()){  return false;  }
	 getNext(); 	
		
	 if(!match(END)) {     //  restorePosition(); 
	 
	 return false;}
	else{ DISPLAY(".ASSG FOUND \n "); }
	return true;
};

bool arithmetic(){  
	bool r;
	// savePosition();
	if(!match(ID)){ 
		// restorePosition(); 
		return false;}
	getNext();
	switch(currType){
		case PLUS:
		 DISPLAY(". +  ");
		break;
		case MINUS:
		 DISPLAY(". -  ");
		break;
		default:
		// restorePosition(); 
		 return false;
		break;
		}
		
		getNext();
	 switch(currType){
		case ID:
		 DISPLAY(". ID. ");
		break;
		case INT:
		 DISPLAY(". INT ");
		break;
		default:
	//	 restorePosition(); 
		 return false;
		break;
		} 	
		
		 getNext();
	 if(!match(END)) { 
	 	// restorePosition(); 
	 	return false;}
	 else{ DISPLAY(".ARITH FOUND \n "); }
	return true;
};

bool var(){
	
	 getNext();
	 if(!match(ID)) { 
	 	
	 	return false;}
	 
	 else{ DISPLAY(".VAR FOUND \n "); }
	return true;
};

bool expr(){
	bool r ;
	//int pos = currPos;
	savePosition();
	getNext();
	
	 if(assignment()) { DISPLAY(".---------assign "); ECHO(currPos); return true;}

 else { 
 	restorePosition(); 
 	 getNext();
 	}	
	 
	 if(arithmetic()){ DISPLAY(".--------- arithmetic "); ECHO(currPos); return true;}
	 
 else { 
 	restorePosition(); 
 	 getNext();
 	}	
	 
	 
   if(var()) { DISPLAY(".---------var "); ECHO(currPos); return true;}
else { 
 	restorePosition(); 
 	 getNext();
 	}	
 
	return false;
}
	
//////////
//    
//   
//
//
	

	 
	  

////////
void main(){
	
	expr();
	/*
	savePosition();
	int i = 0;
	for(i=0; i<5; i++){
		 getNext();
		 ECHO(i);
		}
		 restorePosition(); 
		 
		 	//expr();
	savePosition();
	i = 0;
	for(i=0; i<5; i++){
		 getNext();
		 ECHO(i); ECHO(currType);
		} 
		*/
	// assignment();
	 //arithmetic();
	 
	 
	 //assignment();
};