/* ========================================================================
   pDE: Parallel version of Storn and Price's Differential evolution 
   applied to NEURON modeling

   c2005 Jose Ambros-Ingerson jose@kiubo.net
   
   $Date: 2006/07/06 15:11:22 $ $Log: jTime.c,v $
   $Date: 2006/07/06 15:11:22 $ Revision 1.4  2006/07/06 15:11:22  jose
   $Date: 2006/07/06 15:11:22 $ fixed error in added include jLib.h
   $Date: 2006/07/06 15:11:22 $
   $Date: 2006/07/06 15:11:22 $ Revision 1.3  2006/07/06 15:09:32  jose
   $Date: 2006/07/06 15:11:22 $ added include jLib.h
   $Date: 2006/07/06 15:11:22 $
   $Date: 2006/07/06 15:11:22 $ Revision 1.2  2006/07/03 16:24:26  jose
   $Date: 2006/07/06 15:11:22 $ fixed jTime declaration
   $Date: 2006/07/06 15:11:22 $
   $Date: 2006/07/06 15:11:22 $ Revision 1.1.1.1  2005/05/20 19:49:14  jose
   $Date: 2006/07/06 15:11:22 $ Parallel Differential Evolution
   $Date: 2006/07/06 15:11:22 $

   ======================================================================== */

#include <time.h>
#include <string.h>
#include "jLib.h"

void jTime_now( char *buf, int bufsz, char *format ){
  time_t Time;

  time( &Time );
  strftime( buf, bufsz, format, localtime( &Time ) );
}
