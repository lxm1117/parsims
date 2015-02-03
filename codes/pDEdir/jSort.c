/* ================================================================================
   sort related utilities
   ================================================================================ */

#include <stdio.h>
#include <stdlib.h>
#include "jLib.h"

/* ================================================================================
   Shell sort (see Numerical recipes p 332 ). Adapted to used a[0:n-1] indexing
   Sort an array a[0..n-1] into ascending order by Shell's method.
   a is replaced on output by its sorted rearrangement.
   If n is less than the size of the array, only the first n elements are sorted
   ================================================================================ */
void shell_sort( int n, double a[] ){
  int i, j, inc;
  double v;
  
  inc = 1;
  do { inc *= 3; inc++; } while( inc <= n );
  
  do {
    inc /= 3;
    for( i=inc; i<n; i++ ){
      v = a[i];
      j = i;
      while( a[j-inc] > v ){
	a[j] = a[j-inc];
	j -= inc;
	if( j <= inc ) break;
      }
      a[j] = v;
    }
  } while( inc > 1 );
}

/* ================================================================================
   move associated integer array b along while sorting a
   ================================================================================ */
void shell_sort_i( int n, double a[], int b[] ){
  int i, j, inc, bv;
  double v;
  
  inc = 1;
  do { inc *= 3; inc++; } while( inc <= n );
  
  do {
    inc /= 3;
    for( i=inc; i<n; i++ ){
      v = a[i]; bv = b[i];
      j = i;
      while( a[j-inc] > v ){
	a[j] = a[j-inc]; b[j] = b[j-inc];
	j -= inc;
	if( j <= inc ) break;
      }
      a[j] = v; b[j] = bv;
    }
  } while( inc > 1 );
}

/* ================================================================================
   move associated double array b along while sorting a
   ================================================================================ */
void shell_sort_d( int n, double a[], double b[] ){
  int i, j, inc;
  double v, bv;
  
  inc = 1;
  do { inc *= 3; inc++; } while( inc <= n );
  
  do {
    inc /= 3;
    for( i=inc; i<n; i++ ){
      v = a[i]; bv = b[i];
      j = i;
      while( a[j-inc] > v ){
	a[j] = a[j-inc]; b[j] = b[j-inc];
	j -= inc;
	if( j <= inc ) break;
      }
      a[j] = v; b[j] = bv;
    }
  } while( inc > 1 );
}

#ifdef TEST_SORT /*================================================================================*/
main( int argc, char* argv[] ){ 
  int           i, n, st;
  double        *x, *b;

  x = (double *) malloc( 2048 * sizeof( double ));
  b = (double *) malloc( 2048 * sizeof( double ));
  n = 0;
  while( 2 == (st = scanf( "%lf %lf", &(x[n]), &(b[n]) ))) ++n;
  if( st != EOF ) {
    fprintf( stderr, "bad input format" );
    exit( 1 );
  }

  printf( ">> unsorted \n" );
  for( i=0; i<n; ++i ) printf( "%d %f %g\n", i, x[i], b[i] );
  shell_sort_d( n, x, b );
  printf( ">> sorted \n" );
  for( i=0; i<n; ++i ) printf( "%d %f %g\n", i, x[i], b[i] );

  x[n-1] *= 0.1;
  shell_sort_d( n, x, b );
  printf( ">> sorted2 \n" );
  for( i=0; i<n; ++i ) printf( "%d %f %g\n", i, x[i], b[i] );
}

#endif /* TEST ================================================================================*/

