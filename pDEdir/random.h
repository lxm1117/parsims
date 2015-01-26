/* ========================================================================
   pDE: Parallel version of Storn and Price's Differential evolution 
   applied to NEURON modeling

   c2005 Jose Ambros-Ingerson jose@kiubo.net
   
   $Date: 2005/06/01 20:54:31 $ $Log: random.h,v $
   $Date: 2005/06/01 20:54:31 $ Revision 1.2  2005/06/01 20:54:31  jose
   $Date: 2005/06/01 20:54:31 $ worked out most warnings in biowulf.biosci.ohiou.edu
   $Date: 2005/06/01 20:54:31 $
   $Date: 2005/06/01 20:54:31 $ Revision 1.1.1.1  2005/05/20 19:49:14  jose
   $Date: 2005/06/01 20:54:31 $ Parallel Differential Evolution
   $Date: 2005/06/01 20:54:31 $

   ======================================================================== */

#ifndef I_random
#define I_random 1

void set_seed( int new_seed );
int see_seed( void );

double	du_dev0( void );
double du_dev( double min, double max );
int iu_dev( int min, int max );

double	dexp_dev0( void );
double dexp_dev( double lambda );

double 	dgauss_dev0( void );
double dgauss_dev( double mean, double sdev );

#endif
