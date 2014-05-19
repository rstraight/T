//========================================================================== 
//                            File:	Tflow
//                            Author:
//                            Date:	1-11-14
//                            
//                            Notes:    flow control macros/func (for switch if etc)
//
//                                      #include "Tflow.h"
//
//                                      gcc yoursource.cpp 
//                                      ./a.out -f filename.x
//==========================================================================                           

//========================================================================== 
//
//	DEFINES		T_FOR, T_CASE, T_SW, T_END , TRUE, FALSE
//      
//      FUNCTIONS	
//
//==========================================================================

/* Redefine FALSE and TRUE */
 
#ifndef FALSE
#define FALSE 0
#endif
 
#ifndef TRUE
#define TRUE 1
#endif

/* T_FOR(n, s)       n = limit, s = command */
#ifndef T_FOR
#define T_FOR(n, s)	int tindex = 0; for(tindex = 0; tindex < n; tindex++){ s }
#endif


/* T_CASE(c, s)       c = case, s = command */
#ifndef T_CASE
#define T_CASE(c, s)	case c: s break;
#endif

/* T_SW(t)  T_END     t = test    ex. ch = getc(); T_SW(ch) T_CASE('x', exit(0); ) T_END*/
#ifndef T_SW
#define T_SW(t)	switch(t){
#endif

/* T_END       generic multiline terminator */
#ifndef T_END
#define T_END }
#endif
