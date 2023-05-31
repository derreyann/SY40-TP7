//=============================================================================//
//										prg1.h
//===============================================================================//

	#include <stdio.h>
	#include <unistd.h>
	#include <stdlib.h>

/* prg1.h : implementation de semaphores et des */
/*          operations P et V avec les tubes    */

typedef int Semaphore[2];

void initSem(Semaphore S, int cpt) 
{
   int i;
   char c;
   pipe(S);
   c='a';
   for (i=0; i<cpt; i++) 
	   write(S[1], &c,1);
}

void P(Semaphore S) 
{
   char c;
   read(S[0], &c, 1);
}

void V(Semaphore S) 
{
   char c='a';
   write(S[1], &c, 1);
}
