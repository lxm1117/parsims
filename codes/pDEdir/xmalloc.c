/* ========================================================================
   pDE: Parallel version of Storn and Price's Differential evolution 
   applied to NEURON modeling

   c2005 Jose Ambros-Ingerson jose@kiubo.net
   
   $Date: 2005/05/20 19:49:14 $ $Log: xmalloc.c,v $
   $Date$ Revision 1.1.1.1  2005/05/20 19:49:14  jose
   $Date$ Parallel Differential Evolution
   $Date$

   ======================================================================== */

#include <stdio.h>
#include <stdlib.h>
/* #include <malloc.h> This is part of stdlib.h in mac OSX */
#include "jLib.h"

#define MAGIC   (double)1234567890.1234456789

/* ================================================================================== */
static void xmfatal( str )
     char *str;
{
  (void) fprintf( stderr,"%s\n", str );
  exit( 1 );
}

/* ===================================================================================
   A safer saner malloc, for careless programmers
   =================================================================================== */
char *xmalloc( int n )
{
  register char *ptr;

  if( (ptr = malloc((unsigned)(n + sizeof(double)) )) == NULL)
    xmfatal("xmalloc: no memory");
  *((double *) ptr) = MAGIC;              /* magic number */
  return(ptr + sizeof(double));
}

/* ================================================================================ */
/* we make sure realloc will do a malloc if needed */
char *xrealloc( char *ptr, int n )
{
  if (ptr == NULL)
    return(xmalloc(n));

  ptr -= sizeof(double);
  if (*((double *) ptr) != MAGIC)
    xmfatal("xrealloc: storage not xmalloc'ed");

  if ((ptr = realloc(ptr, (unsigned)(n + sizeof(double)) )) == NULL)
    xmfatal("xmalloc: no memory");
  *((double *) ptr) = MAGIC;		/* magic number */
  return(ptr + sizeof(double));
}

/* ================================================================================== */
void xfree( char *p )
{
  if (p == NULL)
    xmfatal("xfree: NULL pointer");
  p -= sizeof(double);
  if (*((double *) p) != MAGIC)
    xmfatal("xfree: storage not xmalloc'ed");
  free(p);
}
