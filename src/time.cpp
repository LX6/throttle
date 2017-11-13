/* time example */
/* 86400 */
#include <stdio.h>      /* printf */
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */
#include <curses.h>
//#include <stdlib.h>     /* for itoa */

#include "vdata.h"

#define WSECS 32400
#define WDS 22
#define WHS 9
//#define WS 0.33
#define WS 0.5
#define MYR 10000

#define XDS 30		// average
#define XE_LIMIT 0.13	// estimate exp/m

/*
int bin2(int n)
{
char buffer [33];
   itoa (n,buffer,2);
   printw ("\nbinary: %s\n",buffer);
}
*/

// Conversion to bin from decimal
int bin(int n)
{
   /* step 1 */
   if (n > 1)
       bin(n/2);
   /* step 2 */
   printw("%d", n % 2);
//   return (n % 2);
}


int kbhit(void)    /* comment */ 
{ 
    int ch, r; 
 
    // turn off getch() blocking and echo 
    nodelay(stdscr, TRUE); 
    noecho(); 
 
    // check for input 
    ch = getch(); 
    if( ch == ERR)      // no input 
            r = FALSE; 
    else if( ch == 'q') 
    {
      r = TRUE; 
      ungetch(ch); 
    }
    else                // input 
    { 
            r = FALSE; 
     //       ungetch(ch); 
    } 
 
    // restore block and echo 
    echo(); 
    nodelay(stdscr, FALSE); 
    return(r); 
} 

int main ()
{

  time_t timer, t = time(NULL);
  struct tm y2k = {0}, y2n = {0}, tm = *localtime(&t);
  double seconds, primes;

  y2k.tm_hour = 8;   y2k.tm_min = 0; y2k.tm_sec = 0;
  y2k.tm_year = 117; y2k.tm_mon = 8; y2k.tm_mday = 18;
  tm.tm_hour = 9;   tm.tm_min = 0; tm.tm_sec = 0;
//  Commenting out this, as only today does matter
//  tm.tm_year = 117; tm.tm_mon = 8; tm.tm_mday = 18;

  y2n.tm_hour = 15;   y2n.tm_min = 0;  y2n.tm_sec = 0;
  y2n.tm_year = 117; y2n.tm_mon = 10; y2n.tm_mday = 2;

  initscr();
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_BLACK);

  attron(COLOR_PAIR(1));
 
  time(&timer);  /* get current time; same as: timer = time(NULL)  */

  long i;
  int primes_m, primes_h;
  long m = timer / 86400;
  struct Days DS = {0., 0., 0.};
  printw("**\n");

  seconds = difftime(timer,mktime(&y2k));

  DS = display( 3, m*86400, (m-1)*86400, (m-2)*86400, (m-3)*86400 );

  for (i=86400;i<=seconds;i+=86400)
  {
    
  }
  
  printw ("%.f seconds since January 1, 2000 in the current timezone\n", (i-seconds));
  printw ("%.f seconds since January 1, 2000 in the current timezone\n", seconds);

//  tm.tm_mday = 28;
  time(&timer);
  seconds = difftime(timer,mktime(&tm));
//  percent = seconds; 
  printw ("%2.2f/%2.2f seconds %d since January 1, 2000 in the current timezone\n", 100-100*(WSECS-seconds)/WSECS, 100*(WSECS-seconds)/WSECS, tm.tm_wday);
//  int tmt = tm.tm_wday-1;
  printw ("%2.2f seconds %d since January 1, 2000 in the current timezone\n", 100*((tm.tm_wday-1)*WSECS+seconds)/(5*WSECS), tm.tm_wday);
  printw ("%.f seconds since January 1, 2000 in %2.4f the current timezone\n", (WSECS-seconds), (WSECS-seconds)/3600);

  printw("now: %d-%d-%d %d:%d:%d--%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_wday);

    printw("This should be printed in black with a red background!\n");

    attron(COLOR_PAIR(2));
    printw("And this in a green background!\n");
   
    while(!kbhit()) 
    {
    time(&timer);
    seconds = difftime(timer,mktime(&tm));
    primes = difftime(mktime(&y2n),timer);

    move (3,33);
    printw("%.f in %2.4f    ", (primes), 300+(primes)/3600);
    primes_m = primes/60, primes_h = primes_m/60;
    printw("%d : %d : %d,  %2.3f\n", primes_h, int(primes_m)%60, int(primes)%60, 100-100*primes/259200 );

    move (9,5);
    printw("%.f in %2.4f\n", (WSECS-seconds), (WSECS-seconds)/3600);
    attron(COLOR_PAIR(1));
    printw("out A%4.2fA", (WS*MYR*seconds)/(WDS*WHS*3600));
    printw("out b%4.2fb", (WS*MYR*seconds)/(WDS*WHS*3600)-DS.xpen1);
    printw("out V%4.2fV", (WS*MYR*seconds)/(WDS*WHS*3600)-DS.xpen1-DS.xpen2);
    //printw("outA %16d", bin(((int)100*WS*MYR*seconds)/(WDS*WHS*3600)));
    printw("\nS1 %4.2f", DS.xpen1);
    printw("\nS2 %4.2f", DS.xpen2);
    printw("\nS3 %4.2f", DS.xpen3);
    printw("\nS4 %4.2f\n", DS.xpen4);

    attron(COLOR_PAIR(3));
    bin(((int)100*WS*MYR*seconds)/(WDS*WHS*3600));
//    bin2(((int)100*WS*MYR*seconds)/(WDS*WHS*3600));
    attron(COLOR_PAIR(1));
    printw("xout Q%6.2fQ\n", ((tm.tm_mday-1)*WS*MYR)/32+(WS*MYR*seconds)/(WDS*WHS*3600));
    attron(COLOR_PAIR(2));
    
    printw ("%2.2f/%2.2f seconds %d since January 1, 2000 in the current timezone\n", 100-100*(WSECS-seconds)/WSECS, 100*(WSECS-seconds)/WSECS, tm.tm_wday);
//  int tmt = tm.tm_wday-1;
    printw ("%2.2f seconds |__| %d since January 1, 2000 in the current timezone\n", 100*((tm.tm_wday-1)*WSECS+seconds)/(5*WSECS), tm.tm_wday);

    move (0,0);
    printw ( "/||\\" );
    move (1,0);
    printw ( "|__|");

    refresh();
    
//    getch();
    }
  
  endwin();

  return 0;
}

