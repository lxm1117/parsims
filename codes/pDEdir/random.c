/* ========================================================================
   pDE: Parallel version of Storn and Price's Differential evolution 
   applied to NEURON modeling

   c2005 Jose Ambros-Ingerson jose@kiubo.net
   
   $Date: 2006/07/20 15:28:54 $ $Log: random.c,v $
   $Date: 2006/07/20 15:28:54 $ Revision 1.4  2006/07/20 15:28:54  jose
   $Date: 2006/07/20 15:28:54 $ Added save_random_state and restore_random_state
   $Date: 2006/07/20 15:28:54 $
   $Date: 2006/07/20 15:28:54 $ Revision 1.3  2006/07/06 15:13:02  jose
   $Date: 2006/07/20 15:28:54 $ added include jLib.h
   $Date: 2006/07/20 15:28:54 $
   $Date: 2006/07/20 15:28:54 $ Revision 1.2  2006/07/03 16:27:47  jose
   $Date: 2006/07/20 15:28:54 $ added stdlib.h to declare exit()
   $Date: 2006/07/20 15:28:54 $
   $Date: 2006/07/20 15:28:54 $ Revision 1.1.1.1  2005/05/20 19:49:14  jose
   $Date: 2006/07/20 15:28:54 $ Parallel Differential Evolution
   $Date: 2006/07/20 15:28:54 $

   ======================================================================== */

/* ================================================================================
   from C recipes Chapter 7. pp 204 ff.
   ================================================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "jLib.h"

#define True	1
#define False	0

static int	seed = 27;
static int	first = True;
static long	n_count = 0;

void set_seed( int new_seed ){
  seed = (new_seed > 0) ? new_seed : seed;	/* make sure seed is positive */
  first = True;
}

void save_random_state( jRandom *jR ){
  jR->seed = seed;
  jR->n_count = n_count;
}

void restore_random_state( jRandom *jR ){
  int i;
  seed = jR->seed;
  first = True;
  for( i=0; i < jR->n_count; ++i ) du_dev0();
}

/* ================================================================================
   return a uniform deviate in (0.0,1.0)
     corresponds to ran1 of c-recipes 
   ================================================================================ */
#define M1	259200
#define IA1	7141
#define IC1	54733
#define RM1	(1.0/M1)
#define M2	134456
#define IA2	8121
#define IC2	28411
#define RM2	(1.0/M2)
#define M3	243000
#define IA3	4516
#define IC3	51349

#define DU1_DEV_SZ	98

double du_dev0()
{
  char		*Fname = "du_dev0";
  int		i;
  double	temp;
  static long	ix1, ix2, ix3;
  static double	r[DU1_DEV_SZ];

  if( first ){
    first = False;
    n_count = 0;
    ix1 = (IC1 + seed)	% M1;
    ix1 = (IA1*ix1+IC1)	% M1;
    ix2 = ix1		% M2;
    ix1 = (IA1*ix1+IC1)	% M1;
    ix3 = ix1		% M3;
    for( i=1; i<DU1_DEV_SZ; ++i ){
      ix1 = (IA1*ix1+IC1)	% M1;
      ix2 = (IA2*ix2+IC2)	% M2;
      r[i] = (ix1+ix2*RM2)*RM1;
    }
  }
  ++n_count;
  ix1 = (IA1*ix1+IC1)	% M1;
  ix2 = (IA2*ix2+IC2)	% M2;
  ix3 = (IA3*ix3+IC3)	% M3;
  i = 1 + (((DU1_DEV_SZ-1)*ix3)/M3);
  if( i > (DU1_DEV_SZ-1) || i < 1 ){
    fprintf( stderr, "%s: this should not happen (1)\n", Fname );
    exit( 1 );
  }
  temp = r[i];
  r[i] = (ix1+ix2*RM2)*RM1;
  return( temp );
}

/* ================================================================================
   return a uniform deviate in (min,max)
   ================================================================================ */
double du_dev( double min, double max )
{
  return( min + (max-min)*du_dev0() );
}

/* ================================================================================
   return an integer uniform deviate in [min,max]
   ================================================================================ */
int iu_dev( int min, int max )
{
  return( (int)((double)min + (double)(max-min+1)*du_dev0()) );
}

/* ================================================================================
   Returns an exponentially distributed, positive random deviate of unit mean,
   using du_dev1 as the source of uniform deviates
   ================================================================================ */
double dexp_dev0()
{
  return( -log( du_dev0() ));
}

/* ================================================================================
   p(x) = lambda e^{-lambda x}
   ================================================================================ */
double dexp_dev( double lambda )
{
  return( dexp_dev0()/lambda );
}

/*======================================================================
  generate pseudorandom numbers according to normal distribution with
  mean 0 and std dev 1.
  We use algorithm C, page 117 of Knuth's Seminumerical Algorithms
  ======================================================================*/
double dgauss_dev0()
{
  static int    NotHave=True;
  static double X2;
  double        V1, V2, S, LS;

  if( NotHave ) {
    NotHave = False;
    do {
      V1 = 2.0 * du_dev0() - 1.0;
      V2 = 2.0 * du_dev0() - 1.0;
    } while( (S = V1*V1 + V2*V2) > 1.0 );

    LS = sqrt( (-2.0 * log( S )) / S );
    X2 = V2 * LS;
    return( V1 * LS );
  }
  else {
    NotHave = True;
    return( X2 );
  }
}

/*======================================================================
  generate pseudorandom numbers according to normal distribution with
  mean mean and std dev sdev.
  We use algorithm C, page 117 of Knuth's Seminumerical Algorithms
  ======================================================================*/
double dgauss_dev( double mean, double sdev )
{
  return( dgauss_dev0()*sdev + mean );
}

/* ================================================================================
   Returns an integer value that is random deviate drawm from a binomial 
   distribution of n trials each with probability pp, using dunif_dev0()
   as a source for uniform random deivates
   ================================================================================ */
/*
int bnldev( pp, n, dunif_dev0 )
     int	n;
     double	pp;
     double	(*dunif_dev0)();

*/
