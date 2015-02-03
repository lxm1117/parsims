/* ========================================================================
   pDE: Parallel version of Storn and Price's Differential evolution 
   applied to NEURON modeling

   c2005 Jose Ambros-Ingerson jose@kiubo.net
   
   $Id: pDE.c,v 1.32 2007/11/15 18:34:42 jose Exp $

   ======================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include <time.h>
#include <mpi.h>
#include <sys/types.h>
#include <unistd.h>

#include "jLib.h"
#include "pDE.h"
#include "random.h"

/* ======================================================================== */
int main( int argc, char *argv[] )
{
  int 	i;
  pRun	*pRn;

  pRn = (pRun *) xmalloc( sizeof( pRun ) );
  pRn->sA = (sAdata *) xmalloc( sizeof( sAdata ));
  pRn->pB = (pBest *) xmalloc( sizeof( pBest ));

  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &pRn->rank );
  MPI_Comm_size( MPI_COMM_WORLD, &pRn->Nproc );
  
  pRn->pid = getpid();   //structure pointer
 
  load_job_spec( argc, argv, pRn );		/* load parms into all processes */

  //check
  printf("checkmark");

  pRn->P_errD = pRn->D;
  pRn->P_errS = pRn->D + pRn->fCaseN;
  pRn->P_etime = pRn->P_errS + 1;
  pRn->P_nfeval = pRn->P_errS + 2;
  pRn->P_ipop = pRn->P_errS + 3;
  pRn->P_ESerrN = pRn->P_errS + 4;

  pRn->Pop_D = pRn->D + pRn->fCaseN + 5;

  alloc_array1d( &pRn->Pop_buf, pRn->Pop_D );

  if( pRn->rank == 0 ) {
    log_job( pRn );
    master( pRn );

    for( i=1; i<pRn->Nproc; ++i ){		/* ask all eval_slave's to return */
      MPI_Send( pRn->Pop_buf, pRn->Pop_D, MPI_DOUBLE, i, DIETAG, MPI_COMM_WORLD );
    }
  }
  else eval_slave( pRn ); 
  //check
  printf("checkmark2");

  xfree( (char *) pRn->pB );
  xfree( (char *) pRn->sA );
  xfree( (char *) pRn->Pop_buf );
  xfree( (char *) pRn );

  MPI_Finalize();
  return 0;
}

/* ======================================================================== */
void master( pRun *pRn )
{
  int   Nworking, ipop;
  MPI_Status status;

  alloc_master( pRn );

  set_seed( pRn->seed );
  do_Pop_init( pRn ); 	/* Pop_load_init( pRn ); */
  pRn->nfeval = 0;

  Nworking = 1;

  for( pRn->gen_N=0; pRn->gen_N < pRn->genmax; pRn->gen_N++ ){
    pRn->nWin = pRn->pWin = 0.0;

    for( ipop=0; ipop<pRn->NP; ++ipop ){
      ++pRn->nfeval;
      
      if( Nworking < pRn->Nproc ){
	evolve_member( pRn, ipop );		/* evolve ipop into Pop_buf and send to eval_slave */
	MPI_Send( pRn->Pop_buf, pRn->Pop_D, MPI_DOUBLE, Nworking, WORKTAG, MPI_COMM_WORLD );
	++Nworking;
      }
      else {
	MPI_Recv( pRn->Pop_buf, pRn->Pop_D, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
	Pop_add_log( pRn, status.MPI_SOURCE );

	evolve_member( pRn, ipop );		/* evolve ipop into Pop_buf */
	MPI_Send( pRn->Pop_buf, pRn->Pop_D, MPI_DOUBLE, status.MPI_SOURCE, WORKTAG, MPI_COMM_WORLD );
      }
    }
    log_Gen( pRn );
  }

  while( Nworking > 1 ){			/* wind down pending requests */
    MPI_Recv( pRn->Pop_buf, pRn->Pop_D, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
    Pop_add_log( pRn, status.MPI_SOURCE );
    --Nworking;
  }
  log_Gen( pRn );

  free_master( pRn );
}

/* -------------------------------------------------------------------------------- */
void alloc_master( pRun *pRn )
{ 
  int i;

  alloc_array2d( &pRn->Pop, pRn->NP, pRn->Pop_D );
  alloc_array1d( &pRn->best_ever, pRn->Pop_D );
  pRn->Pop_sT = (sTat *) xmalloc( pRn->Pop_D * sizeof( sTat ));
  
  pRn->Pop_cO = (cOrr **) xmalloc( pRn->D * sizeof( cOrr * ));
  for( i=0; i<pRn->D; ++i )
    pRn->Pop_cO[i] = (cOrr *) xmalloc( pRn->D * sizeof( cOrr ) );

  pRn->sA->n = 0;
  pRn->sA->nMax = pRn->NP* pRn->sA->Pop_f;
  if( pRn->sA->Pop_f > 0 ){
    alloc_array2d( &pRn->sA->Pop, pRn->sA->nMax, pRn->Pop_D );
    pRn->sA->idx = (int *) xmalloc( pRn->sA->nMax * sizeof( int ));
    pRn->sA->sv = (double *) xmalloc( pRn->sA->nMax * sizeof( double ));
    pRn->sA->sT = (sTat *) xmalloc( pRn->Pop_D * sizeof( sTat ));
    pRn->sA->cO = (cOrr **) xmalloc( pRn->D * sizeof( cOrr * ));
    for( i=0; i<pRn->D; ++i )
      pRn->sA->cO[i] = (cOrr *) xmalloc( pRn->D * sizeof( cOrr ) );
  }
    
  if( pRn->pB->n > pRn->NP || pRn->pB->n < 1 ) {
    fprintf( stdout, "\n\n ERROR: invalided nBest >>%d<< \n\n", pRn->pB->n );
    exit( -1 );
  }
  pRn->pB->b = (int *) xmalloc( pRn->pB->n * sizeof( int ));

}

void free_master( pRun *pRn )
{
  int i;

  for( i=0; i<pRn->D; ++i ) xfree( (char *) pRn->Pop_cO[i] );
  xfree( (char *) pRn->Pop_cO );

  xfree( (char *) pRn->Pop_sT );
  xfree( (char *) pRn->best_ever );
  xfree_array2d( pRn->Pop, pRn->NP );
}

/* --------------------------------------------------------------------------------
   Evolve ipop member of Pop; place result in Pop_buf
   -------------------------------------------------------------------------------- */
void evolve_member( pRun *pRn, int ipop )
{
  int i, n, L, ran[5];
  double *pRan[5], *pBest, *pBestRand;

  pRn->Pop_buf[pRn->P_nfeval] = (int) pRn->nfeval;
  pRn->Pop_buf[pRn->P_ipop] = (int) ipop;

  if( pRn->gen_N == 0 ){
    assignd( pRn->D, pRn->Pop_buf, pRn->Pop[ipop] );
  }
  else {
    pBest = pRn->Pop[ pRn->Pop_ibest];
    pBestRand = pRn->Pop[ pRn->pB->b[ iu_dev( 0, pRn->pB->n-1 ) ]];
    randoms( pRn, ran, 5, ipop );
    for( i=0; i<5; ++i ) pRan[i] = pRn->Pop[ran[i]];

/*=======Choice of strategy===============================================================*/
/*=======We have tried to come up with a sensible naming-convention: DE/x/y/z=============*/
/*=======DE :  stands for Differential Evolution==========================================*/
/*=======x  :  a string which denotes the vector to be perturbed==========================*/
/*=======y  :  number of difference vectors taken for perturbation of x===================*/
/*=======z  :  crossover method (exp = exponential, bin = binomial)=======================*/
/*                                                                                        */
/*=======There are some simple rules which are worth following:===========================*/
/*=======1)  F is usually between 0.5 and 1 (in rare cases > 1)===========================*/
/*=======2)  CR is between 0 and 1 with 0., 0.3, 0.7 and 1. being worth to be tried first=*/
/*=======3)  To start off NP = 10*D is a reasonable choice. Increase NP if misconvergence=*/
/*           happens.                                                                     */
/*=======4)  If you increase NP, F usually has to be decreased============================*/
/*=======5)  When the DE/best... schemes fail DE/rand... usually works and vice versa=====*/


/*=======EXPONENTIAL CROSSOVER============================================================*/
/*-------DE/best/1/exp--------------------------------------------------------------------*/
/*-------Our oldest strategy but still not bad. However, we have found several------------*/
/*-------optimization problems where misconvergence occurs.-------------------------------*/
    if( pRn->strategy == 1 ){ /* strategy DE0 (not in our paper) */

      assignd( pRn->D, pRn->Pop_buf, pRn->Pop[ipop] );
      n = iu_dev( 0, pRn->D-1 );
      L = 0;
      do {                       
	pRn->Pop_buf[n] = pRn->Pop[ pRn->Pop_ibest ][n] + pRn->F*(pRn->Pop[ran[1]][n] - pRn->Pop[ran[2]][n]);
	n = (n+1) % pRn->D;
	L++;
      }
      while( (du_dev0() < pRn->CR) && (L < pRn->D));
    }
/*-------DE/rand/1/exp-------------------------------------------------------------------*/
/*-------This is one of my favourite strategies. It works especially well when the-------*/
/*-------"bestit[]"-schemes experience misconvergence. Try e.g. F=0.7 and CR=0.5---------*/
/*-------as a first guess.---------------------------------------------------------------*/
    else if( pRn->strategy == 2 ){ 	/* strategy DE1 in the techreport */
      double *pBuf, af;
      pBuf = pRn->Pop_buf;
      assignd( pRn->D,pRn->Pop_buf,pRn->Pop[ipop]);
      n = iu_dev( 0, pRn->D-1 );
      L = 0;
      do {                       	/* v_new = v_r0 + F*( v_r1 - v_r2 ) */
	if( pRn->fPar[n]->logT == 1 ){ 
	  af = pRn->fPar[n]->logT_add;
	  pBuf[n] = (pRan[0][n]+af) * pow( ( (pRan[1][n]+af) / (pRan[2][n]+af)), pRn->F ) - af;

	  /*pRn->Pop_buf[n] = pRn->Pop[ran[0]][n] *
	    pow( ( pRn->Pop[ran[1]][n] / pRn->Pop[ran[2]][n]), pRn->F ); */

	}
	else
	  pRn->Pop_buf[n] = pRn->Pop[ran[0]][n] + 
	                  pRn->F*( pRn->Pop[ran[1]][n] - pRn->Pop[ran[2]][n]);
	n = (n+1) % pRn->D;
	L++;
      }
      while( (du_dev0() < pRn->CR) && (L < pRn->D));
    }
/*-------DE/rand-to-best/1/exp-----------------------------------------------------------*/
/*-------This strategy seems to be one of the best strategies. Try F=0.85 and CR=1.------*/
/*-------If you get misconvergence try to increase NP. If this doesn't help you----------*/
/*-------should play around with all three control variables.----------------------------*/
    else if( pRn->strategy == 3 ){ 	/* similiar to DE2 but generally better */
      double *pBuf, af;
      pBuf = pRn->Pop_buf;
      assignd( pRn->D, pRn->Pop_buf, pRn->Pop[ipop] );
      n = iu_dev( 0, pRn->D-1 );
      L = 0;
      do { 				/* v_new = v_old + F*( v_best - v_old + v_r0 - v_r1 ) */
	if( pRn->fPar[n]->logT == 1 ){ 
	  af = pRn->fPar[n]->logT_add;
	  pBuf[n] = (pBuf[n]+af) * 
	            pow( (pBest[n]+af) / (pBuf[n]+af) * (pRan[0][n]+af) / (pRan[1][n]+af), pRn->F ) - af;

	  /*pRn->Pop_buf[n] = pRn->Pop_buf[n] *
   	    		    pow( (pRn->Pop[ pRn->Pop_ibest ][n] * pRn->Pop[ran[0]][n] /
			    ( pRn->Pop_buf[n] * pRn->Pop[ran[1]][n] )), pRn->F );*/

	}
	else
	  pRn->Pop_buf[n] = pRn->Pop_buf[n] + 
	                     pRn->F * (pRn->Pop[ pRn->Pop_ibest ][n] - pRn->Pop_buf[n]) + 
	                     pRn->F * (pRn->Pop[ran[0]][n] - pRn->Pop[ran[1]][n]);
	n = (n+1)%pRn->D;
	L++;
      }
      while( (du_dev0() < pRn->CR) && (L < pRn->D));
    }

    /*-------DE/rand-to-best/1/exp choosing random from several best (JAI variation) --------*/
    else if( pRn->strategy == 13 ){
      double *pBuf, af;
      pBuf = pRn->Pop_buf;
      assignd( pRn->D, pRn->Pop_buf, pRn->Pop[ipop] );
      n = iu_dev( 0, pRn->D-1 );
      L = 0;
      do { 				/* v_new = v_old + F*( v_best - v_old + v_r0 - v_r1 ) */
	if( pRn->fPar[n]->logT == 1 ){ 
	  af = pRn->fPar[n]->logT_add;
	  pBuf[n] = (pBuf[n]+af) * 
	            pow( (pBestRand[n]+af) / (pBuf[n]+af) * (pRan[0][n]+af) / (pRan[1][n]+af), pRn->F ) - af;
	}
	else
	  pRn->Pop_buf[n] = pRn->Pop_buf[n] + 
	                     pRn->F * (pBestRand[n] - pRn->Pop_buf[n]) + 
	                     pRn->F * (pRn->Pop[ran[0]][n] - pRn->Pop[ran[1]][n]);
	n = (n+1)%pRn->D;
	L++;
      }
      while( (du_dev0() < pRn->CR) && (L < pRn->D));
    }
/*-------DE/best/2/exp is another powerful strategy worth trying--------------------------*/
    else if( pRn->strategy == 4 ) { 
      assignd( pRn->D,pRn->Pop_buf,pRn->Pop[ipop] );
      n = iu_dev( 0, pRn->D-1 );
      L = 0;
      do {                           
	pRn->Pop_buf[n] = pRn->Pop[ pRn->Pop_ibest ][n] + 
	                     pRn->F * (pRn->Pop[ran[0]][n] + pRn->Pop[ran[1]][n] -
				       pRn->Pop[ran[2]][n] - pRn->Pop[ran[3]][n]);
	n = (n+1) % pRn->D;
	L++;
      }
      while( (du_dev0() < pRn->CR) && (L < pRn->D));
    }
/*-------DE/rand/2/exp seems to be a robust optimizer for many functions-------------------*/
    else if( pRn->strategy == 5) { 
      assignd( pRn->D,pRn->Pop_buf,pRn->Pop[ipop] );
      n = iu_dev( 0, pRn->D-1 );
      L = 0;
      do {                           
	pRn->Pop_buf[n] = pRn->Pop[ran[4]][n] + 
	                     pRn->F * (pRn->Pop[ran[0]][n] + pRn->Pop[ran[1]][n] -
				       pRn->Pop[ran[2]][n] - pRn->Pop[ran[3]][n] );
	n = (n+1) % pRn->D;
	L++;
      }
      while( (du_dev0() < pRn->CR) && (L < pRn->D));
    }

/*=======Essentially same strategies but BINOMIAL CROSSOVER===============================*/

/*-------DE/best/1/bin--------------------------------------------------------------------*/
    else if( pRn->strategy == 6 ){
      assignd( pRn->D,pRn->Pop_buf,pRn->Pop[ipop] );
      n = iu_dev( 0, pRn->D-1 );
      for( L=0; L<pRn->D; L++ ){ /* perform D binomial trials */
	if((du_dev0() < pRn->CR) || L == (pRn->D-1)){ /* change at least one parameter */
	  pRn->Pop_buf[n] = pRn->Pop[ pRn->Pop_ibest ][n] + 
	                       pRn->F*( pRn->Pop[ran[1]][n] - pRn->Pop[ran[2]][n] );
	}
	n = (n+1) % pRn->D;
      }
    }
/*-------DE/rand/1/bin-------------------------------------------------------------------*/
    else if( pRn->strategy == 7 ){
      assignd( pRn->D,pRn->Pop_buf,pRn->Pop[ipop] );
      n = iu_dev( 0, pRn->D-1 );
      for( L=0; L<pRn->D; L++ ){ /* perform D binomial trials */
	if((du_dev0() < pRn->CR) || L == (pRn->D-1)){ /* change at least one parameter */
	  pRn->Pop_buf[n] = pRn->Pop[ran[0]][n] + 
	                       pRn->F * ( pRn->Pop[ran[1]][n] - pRn->Pop[ran[2]][n] );
	}
	n = (n+1) % pRn->D;
      }
    }
/*-------DE/rand-to-best/1/bin-----------------------------------------------------------*/
    else if( pRn->strategy == 8 ) { 
      assignd( pRn->D,pRn->Pop_buf,pRn->Pop[ipop] );
      n = iu_dev( 0, pRn->D-1 );
      for( L=0; L<pRn->D; L++ ){ /* perform D binomial trials */
	if((du_dev0() < pRn->CR) || L == (pRn->D-1)){ /* change at least one parameter */
	  pRn->Pop_buf[n] = pRn->Pop_buf[n] + 
	                       pRn->F * ( pRn->Pop[ pRn->Pop_ibest ][n] - pRn->Pop_buf[n] ) + 
	                       pRn->F * ( pRn->Pop[ran[0]][n] - pRn->Pop[ran[1]][n] );
	}
	n = (n+1) % pRn->D;
      }
    }
/*-------DE/best/2/bin--------------------------------------------------------------------*/
    else if( pRn->strategy == 9 ) { 
      assignd( pRn->D,pRn->Pop_buf,pRn->Pop[ipop] );
      n = iu_dev( 0, pRn->D-1 );
      for( L=0; L<pRn->D; L++ ){ /* perform D binomial trials */
	if((du_dev0() < pRn->CR) || L == (pRn->D-1)){ /* change at least one parameter */
	  pRn->Pop_buf[n] = pRn->Pop[ pRn->Pop_ibest ][n] + 
	                       pRn->F * ( pRn->Pop[ran[0]][n] + pRn->Pop[ran[1]][n] -
					  pRn->Pop[ran[2]][n] - pRn->Pop[ran[3]][n] );
	}
	n = (n+1) % pRn->D;
      }
    }
/*-------DE/rand/2/bin--------------------------------------------------------------------*/
    else { 
      assignd( pRn->D,pRn->Pop_buf,pRn->Pop[ipop] );
      n = iu_dev( 0, pRn->D-1 );
      for( L=0; L<pRn->D; L++ ){ /* perform D binomial trials */
	if((du_dev0() < pRn->CR) || L == (pRn->D-1)){ /* change at least one parameter */
	  pRn->Pop_buf[n] = pRn->Pop[ran[4]][n] + 
	                       pRn->F * ( pRn->Pop[ran[0]][n] + pRn->Pop[ran[1]][n] - 
					  pRn->Pop[ran[2]][n] - pRn->Pop[ran[3]][n] );
	}
	n = (n+1) % pRn->D;
      }
    }
    var_lims( pRn, pRn->Pop_buf, ipop );
  }
}


    

  
