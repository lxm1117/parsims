/* ========================================================================
   pDE: Parallel version of Storn and Price's Differential evolution 
   applied to NEURON modeling

   c2005 Jose Ambros-Ingerson jose@kiubo.net
   
   $Date: 2006/10/07 00:39:28 $ $Log: jLib.h,v $
   $Date: 2006/10/07 00:39:28 $ Revision 1.5  2006/10/07 00:39:28  jose
   $Date: 2006/10/07 00:39:28 $ Added code to include a population of the best in the run for
   $Date: 2006/10/07 00:39:28 $ Sensitivity Analysis
   $Date: 2006/10/07 00:39:28 $
   $Date: 2006/10/07 00:39:28 $ Revision 1.4  2006/07/20 15:28:54  jose
   $Date: 2006/10/07 00:39:28 $ Added save_random_state and restore_random_state
   $Date: 2006/10/07 00:39:28 $
   $Date: 2006/10/07 00:39:28 $ Revision 1.3  2006/07/06 15:17:35  jose
   $Date: 2006/10/07 00:39:28 $ added random.h
   $Date: 2006/10/07 00:39:28 $
   $Date: 2006/10/07 00:39:28 $ Revision 1.2  2005/06/01 20:54:31  jose
   $Date: 2006/10/07 00:39:28 $ worked out most warnings in biowulf.biosci.ohiou.edu
   $Date: 2006/10/07 00:39:28 $
   $Date: 2006/10/07 00:39:28 $ Revision 1.1.1.1  2005/05/20 19:49:14  jose
   $Date: 2006/10/07 00:39:28 $ Parallel Differential Evolution
   $Date: 2006/10/07 00:39:28 $

   ======================================================================== */

#ifndef _I_jLib1
#define _I_jLib1 1

#include <stdio.h>
#include <string.h>

/* ================================================================================
   jBasic.h
   ================================================================================ */
#define strEQ(A,B)      (! strcmp((A),(B)))
#define strNE(A,B)      (  strcmp((A),(B)))
#define DIGIT(s)        ((int)(s) >= '0' && (int)(s) <= '9' )

typedef char*           AnyPointer;

/* ================================================================================
   xmalloc.h
   ================================================================================ */
char *xmalloc( int n );
char *xrealloc( char *ptr, int n );
void xfree( char *ptr );

/* ================================================================================
   random.h
   ================================================================================ */
typedef struct JRANDOM {
  int  seed;
  long n_count;
} jRandom;

void set_seed( int new_seed );
int see_seed( void );
void save_random_state( jRandom *jR );
void restore_random_state( jRandom *jR );
double	du_dev0( void );
double du_dev( double min, double max );
int iu_dev( int min, int max );

double	dexp_dev0( void );
double dexp_dev( double lambda );

double 	dgauss_dev0( void );
double dgauss_dev( double mean, double sdev );

/* ================================================================================
   jTime
   ================================================================================ */
void jTime_now( char *buf, int bufsz, char *strftimeFormat );

/* ================================================================================
   jString.h
   ================================================================================ */
typedef struct JSTRING {
  int	sz;
  char	*s;
} jString;

jString* jString_new( void );
void jString_free( jString* jS );
int jLine_read( FILE *fp, jString *Ln );
int str2int( char *s, int *i );
int str2short( char *s, short *si );
int str2double( char *s, double *d );
int str2float( char *s, float *f );
int strtoken( char *str, char *delims, int s, char *tok );
int fp_token( FILE *fp, char *delims, char *tok, int *end_del );
int xfp_token( FILE *fp, char *delims, char **tokp, int *end_del );


/* ================================================================================
   ParseArgs.h
   ================================================================================ */
extern char pa_err_msg[];

/* ================================================================================
   betai.c
   ================================================================================ */
void nerror( char *msg );
double betai( double a, double b, double x );
double betacf( double a, double b, double x );

/* ================================================================================
   gammq.c
   ================================================================================ */
double gammp( double a, double x );
double gammq( double a, double x );
void gser( double *gamser, double a, double x, double *gln );
void gcf( double *gammcf, double a, double x, double *gln );
double gammln( double xx );
double erf( double x );
double erfc( double x );
double erfcc( double x );

/* ================================================================================
   jSort.c
   ================================================================================ */
void shell_sort( int n, double a[] );
void shell_sort_i( int n, double a[], int b[] );


/* ================================================================================
   Macros to swap bytes between machines of different endian-ness
   swaping is done in place.

   USAGE
     char	*cA;
     short	*sA;
     int	*iA;
     float	*fA;
     
     cA = (char *) xmalloc( SIZE * sizeof(char));
     sA = (short *) cA;
     iA = (int *) cA;
     fA = (float *) cA;

     read( fd, cA, SIZE );
     FIX_SHORT( sA[0] );
     FIX_INT( iA[2] );
     FIX_FLOAT( fA[3] );
   ================================================================================ */
  
#define SWAP_2(x) ( (((x) & 0xff) << 8) | ((unsigned short)(x) >> 8) )

#define SWAP_4(x) ( ((x) << 24) | \
         (((x) << 8) & 0x00ff0000) | \
         (((x) >> 8) & 0x0000ff00) | \
         ((x) >> 24) )

#define FIX_SHORT(x) (*(unsigned short *)&(x) = SWAP_2(*(unsigned short *)&(x)))

#define FIX_INT(x)   (*(unsigned int *)&(x)   = SWAP_4(*(unsigned int *)&(x)))

#define FIX_FLOAT(x) FIX_INT(x)

#endif /* _I_jLib1 */
