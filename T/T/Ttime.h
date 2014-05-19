 //========================================================================== 
 //
 //                            File:     Ttime.h
 //                            Author:   Mostly Random Google pages
 //                            Date:     1-13-14
 //                            
 //                            Notes:    Timer functions and macros
 //                                      #include "Ttime.h" 
 //                                      
 //
 //
 //==========================================================================           

 
 /*
  
    Real Time Clock - The source of time and date for your OS. 1 second precision. The only time source in a standard PC that can be used to measure absolute time.

    8254 Counter/Timers - A standard counter/timer chip that has been present on motherboards since the dawn of PC (now a functional block inside the chipset). This is the traditional source of IRQ0, the timer interrupt that does task switching in most older OSes.

    RDTSC assembly instruction - Counts CPU clock cycles. See the answer Anon ymous posted for some usage details. Pretty much the highest level of precision you can find for a time source on x86. However, it has some gotchas with accuracy. Also the most convenient option if you are writing in assembly.

    RDTSCP assembly instruction - Similar to RDTSC, but is serialized, which resolves some of the accuracy issues with RDTSC. Only found on the newest processors.

    HPET - Introduced around the Core Duo era of PCs. Intended to be a replacement for the venerable 8254. Modern OSes will use this as their task scheduling interrupt (Vista and later)

    Proprietary Timers in the Chipset - Some chipsets have special timers built into them for Power Management and Multimedia functions. You can sometimes commandeer these for your own application, assuming you are dealing with a fixed-function embedded system and not a general purpose PC.

    */

#include <stdint.h>



static __inline__ unsigned long long rdtsc(void)
{
  
  #if defined(__x86_64__)
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
  #endif
  
  #if defined(__i386__)
  unsigned long long int x;
     __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
     return x;
  #endif
}


/* CPU_SPEED calculated over 1 second with call to getCpuSpeed() */
float cpu_speed_Hz = 0;
float cpu_speed_GHz = 0;

/* miliseconds between last Timer call */
unsigned int delta_t = 0;


/* Redefine FALSE and TRUE */
#ifndef FALSE
#define FALSE 0
#endif
 
#ifndef TRUE
#define TRUE 1
#endif    

void wait_ms(float milliseconds){
  unsigned long long a,b;
  float t;
  a = rdtsc();
  b = rdtsc();
  t = ((b-a)/cpu_speed_Hz);
  while( t < (milliseconds/1000)){   
    b = rdtsc();
    t = ((b-a)/cpu_speed_Hz);
  }//while
};//wait_ms

/* get cpu speed in GHz  */
float getCpuSpeed(){
  
  unsigned long long a,b;
  float t, o, result;
  a = rdtsc();
  b = rdtsc();
  t = (b-a);
  sleep(1);
  b = rdtsc();
  o = (b-a);
  cpu_speed_Hz = o;
  result = cpu_speed_GHz = ((o-t)/1000000000);
  return result;
 
};//getCpuSpeed