/* ========================================================================
   pDE: Parallel version of Storn and Price's Differential evolution 
   applied to NEURON modeling

   c2005 Jose Ambros-Ingerson jose@kiubo.net
   
   $Id: pop.c,v 1.90 2008/12/06 03:17:57 jose Exp $

   ======================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include <sys/types.h>
#include <unistd.h>

#include <mpi.h>

#include "jLib.h"
#include "pDE.h"
#include "random.h"
#include "NumRec.h"

/* --------------------------------------------------------------------------------
   Pop-init uniform|normal=XX set|noset
   Pop-init uniform|normal=XX set|noset Ngen file.log XX
   Pop-init uniform|normal=XX set|noset Ngen2 file.log XX1 file.log XX2
   
   [file: 1st line headers; one line per member
          as in pDE log file 
	    nextGen gen_N XX
	      columns headers
	      pop data
	    end_nextGen genN XX ]

   Initial population is generated
     1. random using Fit-parm parameters. 
        uniform -> Uniform in fit-lims
	normal  -> Normal with mean=set and SD is percent XX of fit-lims
	set|noset to indicate using the set (or not) value for first member
     2. The data file.log substitues the one randomly generated
        using the headers to match columns

   -------------------------------------------------------------------------------- */
typedef struct POP_OP {
  char		rantype[STR_SZ];
  double	ran_SDp;
  char		set[STR_SZ];
  char		file_opt[STR_SZ];
  char		fname[STR_SZ];
  int		nGen;
  char		fname2[STR_SZ];
  int		nGen2;
} pop_Op;

void parse_Pop_init( pRun *pRn, pop_Op *pO ){
  int itok;
  char tok[STR_SZ];

  itok=0;
  itok=strtoken( pRn->Pop_init, " ", itok, tok );	/* Pop-init */ 

  itok=strtoken( pRn->Pop_init, " ", itok, pO->rantype );
  if( itok < 0 ){ printf( "\t\tPop-init ERROR >>%s<<\n\n", pRn->Pop_init ); exit( 1 ); }
  if( strNE( pO->rantype, "uniform" )){
    if( 1 != sscanf( pO->rantype, "normal=%lf", &(pO->ran_SDp) )){
      printf( "\t\tPop-init ERROR >>%s<<\n\n", pRn->Pop_init ); exit( 1 );
    }
    sprintf( pO->rantype, "normal" );
  }

  itok=strtoken( pRn->Pop_init, " ", itok, pO->set );
  if( itok < 0 ){ printf( "\t\tPop-init ERROR >>%s<<\n\n", pRn->Pop_init ); exit( 1 ); }
  if( strNE( pO->set, "set" ) && strNE( pO->set, "noset" )){
    printf( "\t\tPop-init ERROR >>%s<<\n\n", pRn->Pop_init ); exit( 1 );
  }

  itok=strtoken( pRn->Pop_init, " ", itok, pO->file_opt );
  if( itok < 0 ) return;
  itok=strtoken( pRn->Pop_init, " ", itok, pO->fname );
  if( itok < 0 ){ printf( "\t\tPop-init ERROR >>%s<<\n\n", pRn->Pop_init ); exit( 1 ); }

  /*  if( strNE( pO->file_opt, "pop" ) && strNE( pO->file_opt, "Ngen" ) && strNE( pO->file_opt, "Ngen2" )) */
  if( strNE( pO->file_opt, "Ngen" ) && strNE( pO->file_opt, "Ngen2" ))
    { printf( "\t\tPop-init ERROR >>%s<<\n\n", pRn->Pop_init ); exit( 1 ); }

  itok=strtoken( pRn->Pop_init, " ", itok, tok );
  /* if( itok<0 && strEQ( pO->file_opt, "pop" ) ) return; We drop pop option */
  if( 1 != str2int( tok, &(pO->nGen) ) )
    { printf( "\t\tPop-init ERROR >>%s<<\n\n", pRn->Pop_init ); exit( 1 ); }
  
  itok=strtoken( pRn->Pop_init, " ", itok, pO->fname2 );
  if( itok < 0 && strEQ( pO->file_opt, "Ngen") ) return;
  if( itok < 0 ){ printf( "\t\tPop-init ERROR >>%s<<\n\n", pRn->Pop_init ); exit( 1 ); }

  itok=strtoken( pRn->Pop_init, " ", itok, tok );
  if( 1 != str2int( tok, &(pO->nGen2) ) )
    { printf( "\t\tPop-init ERROR >>%s<<\n\n", pRn->Pop_init ); exit( 1 ); }
  
}

/* --------------------------------------------------------------------------------
   -------------------------------------------------------------------------------- */
void do_Pop_init( pRun *pRn ){
  int ipop, j;
  double add;
  FitParm *fPj;
  pop_Op pO;
  
  parse_Pop_init( pRn, &pO );
  /* printf( "\t>>rantype %s ran_SDp %g set >%s< file_opt >%s< fname >%s< nGen %d fname2 >%s< nGen2 %d\n\n",
     pO.rantype, pO.ran_SDp, pO.set, pO.file_opt, pO.fname, pO.nGen, pO.fname2, pO.nGen2 );*/

  /* First generate random values for all Pop members and all parms */
  for( ipop=0; ipop<pRn->NP; ++ipop ){
    pRn->Pop[ipop][pRn->P_errS] = 1e90;		/* So that Pop_add_log does the right thing */
    if( strEQ( pO.rantype, "uniform" )){
      for( j=0; j<pRn->D; ++j ){
	fPj = pRn->fPar[j];
	if( fPj->logT == 1 ){ 
	  add = fPj->logT_add = ( fPj->lo > 0.0 ) ? 0 : -1 * fPj->lo + 1;
	  pRn->Pop[ipop][j] = exp( du_dev( log(fPj->lo + add), log( fPj->hi + add ) ) ) - add;
	}
	else pRn->Pop[ipop][j] = du_dev( fPj->lo, fPj->hi );
      }
    }
    else if( strEQ( pO.rantype, "normal" ))    
      for( j=0; j<pRn->D; ++j ) 
	pRn->Pop[ipop][j] = dgauss_dev( fPj->init, pO.ran_SDp*0.01 * (fPj->hi-fPj->lo) );
    else {
      printf( "\n\t\tERROR do_Pop_init unrecognized rantype >>%s<<\n\n", pO.rantype );
      exit( 1 );
    }
  }
  /* set values for Pop if "set" */
  if( strEQ( pO.set, "set" )) for( j=0; j<pRn->D; ++j ) pRn->Pop[0][j] = pRn->fPar[j]->init;

  /* Now read Ngen file values for Pop */
  if( strEQ( pO.file_opt, "Ngen" ) || strEQ( pO.file_opt, "Ngen2" )) 
    do_Pop_Ngen( pRn, pO.fname, pO.nGen );

  if( strEQ( pO.file_opt, "Ngen2" )) 
    do_Pop_Ngen( pRn, pO.fname2, pO.nGen2 );

  /* Deal with limits on parm values */
  for( ipop=0; ipop<pRn->NP; ++ipop ) var_lims( pRn, pRn->Pop[ipop], -1 );
  log_Gen( pRn );
}

/* --------------------------------------------------------------------------------
   -------------------------------------------------------------------------------- */
void do_Pop_Ngen( pRun *pRn, char *fname, int nGen ){
  int	gfound, go_on, iGen;
  jString *Line;
  FILE 	*fp;

  resolve_path( pRn, fname, fname );
  printf( "reading gen %d from %s\n", nGen, fname );
  if( NULL==(fp=fopen( fname, "r" )) ){ 
    printf("ERROR do_Pop_Ngen Cannot open file >>%s<<\n", fname ); exit( 1 );
  }
  Line = jString_new();
  gfound = 0; go_on = 1;
  while( go_on ){
    if( EOF == jLine_read( fp, Line ) ) go_on = 0;
    else {
      if( 1 == sscanf( Line->s, "nextGen gen_N %d", &iGen ) && iGen==nGen ){
	go_on = 0; gfound = 1;
      }
    }
  }
  if( gfound == 0 ){ printf("ERROR do_Pop_Ngen gen %d not found in >>%s<<\n", nGen, fname ); exit( 1 );}

  printf( "Found gen %d in %s\n", nGen, fname );
  do_Pop_fp( pRn, fp );

  fclose( fp );
}

/* -------------------------------------------------------------------------------- */
char ** split_into_char_array( char *str, int *nAp ){
  int itok, iA, nA;
  char tok[STR_SZ], **cA;

  itok=0; nA=0;
  while( -1 != ( itok=strtoken( str, " \t", itok, tok ))) ++nA;
  cA = (char **) xmalloc( nA * sizeof( char *));

  itok=0; iA=0;
  while( -1 != ( itok=strtoken( str, " \t", itok, tok ))){
    cA[iA] = (char *) xmalloc( 1+ strlen( tok ) * sizeof( char ));
    strcpy( cA[iA], tok );
    ++iA;
  }
  *nAp = nA;
  return cA;
}

/* --------------------------------------------------------------------------------
   -------------------------------------------------------------------------------- */
void do_Pop_fp( pRun *pRn, FILE	*fp ){
  char **hD, tok[STR_SZ];
  int i, j, k, l, ipop, itok, nhD, popFn, go_on, iD, ipF;
  double **popF;
  jString *Line;

  Line = jString_new();
  if( EOF == jLine_read( fp, Line ))
    { printf("ERROR do_Pop_fp missing header on first line\n" ); exit( 1 );}

  if( pRn->idebug ) printf( "\nDEBUG do_Pop_fp >>%s<<\n\n", Line->s );

  hD = split_into_char_array( Line->s, &nhD );
  if( pRn->idebug ) {
    printf( "DEBUG header found:\n" );
    for(i=0;i<nhD;++i ) printf( "DEBUG do_Pop_fp i %d %s\n", i, hD[i] );
  }
  alloc_array2d( &popF, pRn->NP, nhD );

  popFn=0; go_on=1;
  while( go_on ){
    if( EOF == jLine_read( fp, Line ) || popFn>=pRn->NP ) go_on = 0;
    else {
      if( 1 == sscanf( Line->s, "end_nextGen gen_N %d", &i ) ) go_on = 0; 
      itok=0; iD=0;      
      while( iD<nhD && (-1 != (itok=strtoken( Line->s, " ", itok, tok )))){
	if( -1 == str2double( tok, &(popF[popFn][iD]) )) popF[popFn][iD] = 0.0;
	++iD;
      }
      ++popFn;
    }
  }
  if( pRn->idebug ){
    printf( "DEBUG do_Pop_fp population read was:\n" );
    for( ipop=0; ipop<popFn; ++ipop ){
      if(ipop==0){ for(j=0;j<nhD;++j ) printf( "%13s ", hD[j] ); printf( "\n" );}
      for( j=0; j<nhD; ++j ) printf( "%13g ", popF[ipop][j] );
      printf( "\n" );
    }
  }

  FitParm* aP; 
  for( iD=0; iD<pRn->D; ++iD ){		/* For each Fit-parm ... */
    int p_look=1;
    aP = pRn->fPar[iD]; 
    for( j=0; j<nhD && p_look; ++j ) {		/* Iterate over parm names in log file */
      if( strEQ( aP->name, hD[j] )){	/* Exact match; use values */
	printf( "matched %d %20s in Pop with %d %20s from file\n", iD, aP->name, j, hD[j] );
	ipF = 0;
	for( ipop=0; ipop<pRn->NP; ++ipop ){
	  if( ipF >= popFn ) ipF = 0;
	  pRn->Pop[ipop][iD] = popF[ipF][j];
	  ++ipF;
	}
	p_look=0; 
	break;
      }
    }
    if( p_look ){		/* No exact match; look at Subs-parm matches */
      SubsParm* sP; 
      printf( "No exact match for %d >>%s<<; Looking for substitutions\n", iD, aP->name );
      for( j=0; j<pRn->subParN && p_look; j++ ){
	sP = pRn->subPar[j]; 
	for( k=0; k<sP->n && p_look; k++ ){
	  /* printf( ">%s< looking at j %d k %d >%s<\n", aP->name, j, k , sP->name[k] ); */
	  if( strEQ( aP->name, sP->name[k] )){ /* matched a subs */
	    printf( "\tmatched >%s< with >%s<%d,%d; look for %s substitution\n", 
		    aP->name, sP->name[k], j, k, sP->subname );
	    for( l=0; l<nhD && p_look; ++l )
	      if( strEQ( sP->subname, hD[l] )){	/* matched subs to parm in log file */
		printf( "\tmatched %d %20s in Pop with %d %20s from file\n", 
			iD, aP->name, l, hD[l] );
		ipF = iu_dev( 0, pRn->NP-1 ); /* ipF = 0; */
		for( ipop=0; ipop<pRn->NP; ++ipop ){
		  if( ipF >= popFn ) ipF = 0;
		  pRn->Pop[ipop][iD] = popF[ipF][l];
		  ++ipF;
		}
		p_look=0;
	      }
	  }
	}
      }
      if( p_look ) printf( "\tNo substitutes found for %d %s\n", iD, aP->name );
    }
  }
}

/* --------------------------------------------------------------------------------
   -------------------------------------------------------------------------------- */
void do_Pop_fp_old( pRun *pRn, FILE	*fp ){
  char **hD, tok[STR_SZ];
  int i, ipop, j, itok, nhD, popFn, go_on, iD, ipF;
  double **popF;
  jString *Line;

  Line = jString_new();
  if( EOF == jLine_read( fp, Line ))
    { printf("ERROR do_Pop_fp missing header on first line\n" ); exit( 1 );}

  if( pRn->idebug ) printf( "\nDEBUG do_Pop_fp >>%s<<\n\n", Line->s );

  hD = split_into_char_array( Line->s, &nhD );
  if( pRn->idebug ) {
    printf( "DEBUG header found:\n" );
    for(i=0;i<nhD;++i ) printf( "DEBUG do_Pop_fp i %d %s\n", i, hD[i] );
  }
  alloc_array2d( &popF, pRn->NP, nhD );

  popFn=0; go_on=1;
  while( go_on ){
    if( EOF == jLine_read( fp, Line ) || popFn>=pRn->NP ) go_on = 0;
    else {
      if( 1 == sscanf( Line->s, "end_nextGen gen_N %d", &i ) ) go_on = 0; 
      itok=0; iD=0;      
      while( iD<nhD && (-1 != (itok=strtoken( Line->s, " ", itok, tok )))){
	if( -1 == str2double( tok, &(popF[popFn][iD]) )) popF[popFn][iD] = 0.0;
	++iD;
      }
      ++popFn;
    }
  }
  if( pRn->idebug ){
    printf( "DEBUG do_Pop_fp population read was:\n" );
    for( ipop=0; ipop<popFn; ++ipop ){
      if(ipop==0){ for(j=0;j<nhD;++j ) printf( "%13s ", hD[j] ); printf( "\n" );}
      for( j=0; j<nhD; ++j ) printf( "%13g ", popF[ipop][j] );
      printf( "\n" );
    }
  }

  for( iD=0; iD<pRn->D; ++iD ){
    for( j=0; j<nhD; ++j ) {
      if( strEQ( pRn->fPar[iD]->name, hD[j] )){
	printf( "matched %d %20s in Pop with %d %20s from file\n", iD, pRn->fPar[iD]->name, j, hD[j] );
	ipF = 0;
	for( ipop=0; ipop<pRn->NP; ++ipop ){
	  if( ipF >= popFn ) ipF = 0;
	  pRn->Pop[ipop][iD] = popF[ipF][j];
	  ++ipF;
	}
	break;
      }
    }
  }
}

/* ------------------------------------------------------------------------
   update the list of pointers to best n members of Pop
  ------------------------------------------------------------------------ */
void Pop_buf_update_pBest( pRun *pRn )
{
  static int inserted=0;
  int insrt, i, ipop;
  double Pop_errS;
  pBest *pB;

  Pop_errS = pRn->Pop_buf[ pRn->P_errS ];
  ipop = lrint( pRn->Pop_buf[ pRn->P_ipop ] );
  pB = pRn->pB;
  
  if( inserted < pB->n || Pop_errS <= pRn->Pop[ pB->b[ inserted-1 ]][pRn->P_errS] ){
    printMem( pRn, stdout, pRn->Pop_buf );
    fprintf( stdout, "New_pBest\n" );

    for( insrt=0; insrt < inserted; insrt++ ) 
      if( Pop_errS <= pRn->Pop[ pB->b[insrt] ][pRn->P_errS] ) break;
    for( i=pB->n-2; i>=insrt; i-- ) pB->b[i+1] = pB->b[i];
    pB->b[insrt] = ipop;
    if( inserted < pB->n ) ++inserted;
    for( i=0; i<inserted; i++ ){
      printMem( pRn, stdout, pRn->Pop[ pB->b[i]] );
      fprintf( stdout, "pBest %i\n", i );
    }
  }
}

/* --------------------------------------------------------------------------------
   -------------------------------------------------------------------------------- */
void Pop_buf_update_sA( pRun *pRn )
{
  int	i, ilast, inew, iinew;
  double cilast, cbest, cnew;
  sAdata *sA;

  if( pRn->sA->Pop_f == 0 ) return;
  sA = pRn->sA;

  if( sA->n < sA->nMax ){
    assignd( pRn->Pop_D, sA->Pop[sA->n], pRn->Pop_buf );
    ++sA->n;
    if( sA->n == sA->nMax ){	/* just filled up; initialize sort index */
      for( i=0; i<sA->n; ++i ){
	sA->idx[i] = i;
	sA->sv[i]  = sA->Pop[i][pRn->P_errS];
      }
      shell_sort_i( sA->n, sA->sv, sA->idx );		/* Pop[sdx[i]] is i-th in score after sort */
      /*shell2_i( sA->n, sA->sv -1, sA->idx -1 );*/
    }
  }
  else {
    ilast = sA->idx[sA->n-1];			/* largest score is ilast */
    cilast = sA->Pop[ilast][pRn->P_errS];
    cbest = pRn->Pop[pRn->Pop_ibest][pRn->P_errS];
    cnew  = pRn->Pop_buf[pRn->P_errS];

    if( cnew < cilast ){
      /* Now commited to insert */
      if( cilast > cbest * (1.0+sA->Best_Rad_Pcnt) ){ 
	/* ilast outside disk =>insert to reduce disk */
	printMem( pRn, stdout, pRn->Pop_buf ); fprintf( stdout, "NewSA ilast %d\n", ilast );
	printMem( pRn, pRn->log_fp, pRn->Pop_buf ); fprintf( pRn->log_fp, "NewSA ilast %d\n", ilast );

	assignd( pRn->Pop_D, sA->Pop[ilast], pRn->Pop_buf );
	sA->sv[sA->n-1] = cnew;
	shell_sort_i( sA->n, sA->sv, sA->idx );
	/* shell2_i( sA->n, sA->sv -1, sA->idx -1 );*/
      }      
      else { /* ilast inside disk. Insert to its place */
	if( cnew -cbest < 0.0 ) {
	  printf( "Pop_buf_update_sA: ERROR in keeping track of Pop_ibest\n" );
	  exit( 1 );
	}
	inew = floor( pow( (cnew-cbest)/(cbest*sA->Best_Rad_Pcnt), pRn->D ) * sA->n );
	iinew = sA->idx[inew];
	printMem( pRn, pRn->log_fp, pRn->Pop_buf ); fprintf( pRn->log_fp, "NewSA_inDisk inew %d iinew %d\n", inew, iinew );
	printMem( pRn, pRn->log_fp, sA->Pop[iinew] ); fprintf( pRn->log_fp, "To Replace iinew %d\n", iinew );
	assignd( pRn->Pop_D, sA->Pop[iinew], pRn->Pop_buf );
	sA->sv[inew] = cnew;
	shell_sort_i( sA->n, sA->sv, sA->idx );
	/*shell2_i( sA->n, sA->sv -1, sA->idx -1 );*/
      }
    }
  }
  fflush( stdout ); fflush( pRn->log_fp );
}

/* ------------------------------------------------------------------------
   ------------------------------------------------------------------------ */
void Pop_buf_update_sA_old( pRun *pRn )
{
  int	i, ilast;
  sAdata *sA;

  sA = pRn->sA;

  if( sA->n < sA->nMax ){
    assignd( pRn->Pop_D, sA->Pop[sA->n], pRn->Pop_buf );
    ++sA->n;
    if( sA->n == sA->nMax ){	/* just filled up; initialize sort index */
      for( i=0; i<sA->nMax; ++i ){
	sA->idx[i] = i;
	sA->sv[i]  = sA->Pop[i][pRn->P_errS];
      }
      shell_sort_i( sA->nMax, sA->sv, sA->idx );	/* Pop[sdx[i]] is i-th in score after sort */
    }
  }
  else {
    ilast = sA->idx[sA->nMax-1];			/* largest score is ilast */
    if( pRn->Pop_buf[pRn->P_errS] < sA->Pop[ilast][pRn->P_errS] ){ 
      printMem( pRn, stdout, pRn->Pop_buf ); fprintf( stdout, "NewSA\n\n" );
      printMem( pRn, pRn->log_fp, pRn->Pop_buf ); fprintf( pRn->log_fp, "NewSA\n" );

      assignd( pRn->Pop_D, sA->Pop[ilast], pRn->Pop_buf );
      sA->sv[sA->nMax-1] = pRn->Pop_buf[pRn->P_errS];
      shell_sort_i( sA->nMax, sA->sv, sA->idx );	
    }      
  }
  fflush( stdout ); fflush( pRn->log_fp );
}

/* ------------------------------------------------------------------------
   Evaluate Pop_buf, add to Pop if appropriate, log if appropriate
   ------------------------------------------------------------------------ */
void Pop_add_log( pRun *pRn, int rank )
{
  static int First=1;
  int ipop, nfeval, ErrNo;
  double Pop_errS, etime;

  Pop_errS = pRn->Pop_buf[ pRn->P_errS ];
  ipop = lrint( pRn->Pop_buf[ pRn->P_ipop ] );
  nfeval = lrint( pRn->Pop_buf[ pRn->P_nfeval ] );
  etime = pRn->Pop_buf[ pRn->P_etime ];
  ErrNo = lrint( pRn->Pop_buf[ pRn->P_ESerrN ] );

  /* Short term ~NP and long term ~NPx10 exponential averages */
  pRn->time_eavg1 = pRn->time_eavg1 + 2.0/(double)pRn->NP * ( etime - pRn->time_eavg1 );
  pRn->time_eavg2 = pRn->time_eavg2 + 0.5/(double)pRn->NP * ( etime - pRn->time_eavg2 );

  if( First ){
    First = 0;
    pRn->best_ever[pRn->P_errS] = Pop_errS + 1e4; /* so that below does right thing */
    pRn->Pop_ibest = ipop;
  }

  if( ErrNo ){
    printf( "\neval_slave ERROR %d for ipop rank-pid %d %d-%d\n\n", 
	    ErrNo, ipop, rank, pRn->pHosts[rank].pid );
    fprintf( pRn->log_fp, "eval_slave ERROR %d for ipop rank-pid %d %d-%d\n", 
	     ErrNo, ipop, rank, pRn->pHosts[rank].pid );
    ++pRn->pHosts[rank].nErr;

    if( ErrNo < 0 ) exit( 1 );	/* catastrophic error */
  }

  /* Pop_buf gets into Pop if its better or equal than current */
  if( Pop_errS <= pRn->Pop[ipop][pRn->P_errS] ){
    ++pRn->nWin;
    pRn->pWin += 1 - Pop_errS / pRn->Pop[ipop][pRn->P_errS];

    assignd( pRn->Pop_D, pRn->Pop[ipop], pRn->Pop_buf );
  }

  /* Keep track of best in population */
  if( Pop_errS <= pRn->Pop[pRn->Pop_ibest][pRn->P_errS] )
    pRn->Pop_ibest = ipop;

  /* Keep track of best ever and log if new */
  if( Pop_errS < pRn->best_ever[pRn->P_errS] ){
    assignd( pRn->Pop_D, pRn->best_ever, pRn->Pop_buf );

    printf( "%3d-%d ", ipop, rank );
    printMem( pRn, stdout, pRn->best_ever );
    fprintf( stdout, "NewBst nfeval %d gen_N %d", nfeval, pRn->gen_N );
    fprintf( stdout, "\n\n" );

    fprintf( pRn->log_fp, "%d-%d ", ipop, rank );
    printMem( pRn, pRn->log_fp, pRn->best_ever );
    fprintf( pRn->log_fp, "NewBst nfeval %d gen_N %d", nfeval, pRn->gen_N );
    fprintf( pRn->log_fp, "\n" );
    fflush( pRn->log_fp );

    hoc_best( pRn );
  }
  else {
    printf( "e%d-%d ", ipop, rank );
    printMem( pRn, stdout, pRn->Pop_buf );

    fprintf( stdout, "nfeval %d etime %g\n", nfeval, etime );
  }

  Pop_buf_update_sA( pRn );
  Pop_buf_update_pBest( pRn );

  fflush( stdout );
}


/* ------------------------------------------------------------------------ */
void do_cOrr( int N, double *x, double *y, cOrr *cO )
{
  int i;
  double n, s, xm, ym, Sxx, Syy, Sxy, SSxx, SSyy, SSxy;
  double D, zD;

  spear( x-1, y-1, N, &D, &zD, &(cO->PrsD), &(cO->rs), &(cO->Prst) );

  xm = ym = Sxx = Syy = Sxy = 0.0;
  n = (double) N;

  for( i=0; i<N; ++i ){
    xm += x[i]; Sxx += x[i]*x[i]; 
    ym += y[i]; Syy += y[i]*y[i]; 
    Sxy += x[i] * y[i];
  }
  xm = xm / n; SSxx = Sxx - n*xm*xm;
  ym = ym / n; SSyy = Syy - n*ym*ym;
  SSxy = Sxy - n*xm*ym;

  cO->m = SSxy / SSxx;
  if( isnan( cO->m ) || isinf( cO->m )) cO->m = 0.0;
  cO->b = ym - cO->m * xm;
  cO->r = SSxy / sqrt( SSxx * SSyy );
  if( isnan( cO->r ) || isinf( cO->r )) cO->r = 0.0;
  s = 0; if( N > 2 ) s = sqrt( (SSyy - cO->b * SSxy)/(n-2));
  cO->SEb = s * sqrt( 1/n + xm*xm / SSxx );
  if( isnan( cO->SEb ) || isinf( cO->SEb )) cO->SEb = 0.0;
  cO->SEm = s / sqrt( SSxx );
  if( isnan( cO->SEm ) || isinf( cO->SEm )) cO->SEm = 0.0;
}

/* ------------------------------------------------------------------------ */
void do_sTat( int N, double *p, sTat *sT ){
  int i;
  double *buf;

  sT->mean = sT->sd = sT->cv = sT->sdr = sT->cvr = 0.0;
  sT->min = sT->max = p[0];
  for( i=0; i<N; ++i ){
    sT->mean += p[i];
    if( p[i] > sT->max ) sT->max = p[i];
    if( p[i] < sT->min ) sT->min = p[i];
  }
  sT->mean = sT->mean / (double) N;
  for( i=0; i<N; ++i ) sT->sd += (sT->mean - p[i]) * (sT->mean - p[i]);
  sT->sd = (N<=1 ? 0.0: sqrt( sT->sd / (double) (N-1) ));
  if( fabs( sT->mean ) > 1e-50 ) sT->cv = 100.0*fabs( sT->sd / sT->mean );

  sT->median = nr_select( N/2, N, p-1 );	/* Watch it! it modifies the order in p */

  buf = (double *) xmalloc( (N) *sizeof( double ));  
  for( i=0; i<N; ++i ) buf[i] = fabs( sT->median - p[i] ); 	/* compute median deviations */
  sT->sdr = 1.4826 * nr_select( N/2, N, buf-1 );		/* median of median deviations MAD */
  if( fabs( sT->median ) > 1e-50 ) sT->cvr = 100.0*fabs( sT->sdr / sT->median );
  xfree((char *) buf );    
}

/* ------------------------------------------------------------------------ */
void do_sTat_Pop( pRun *pRn ){
  int i, j, k;
  double *buf, *buf2;

  buf = (double *) xmalloc( (pRn->NP) *sizeof( double ));
  buf2 = (double *) xmalloc( (pRn->NP) *sizeof( double ));

  for( j=0; j<pRn->Pop_D; ++j ){
    for( i=0; i<pRn->NP; ++i ){
      buf[i] = pRn->Pop[i][j];
    }
    do_sTat( pRn->NP, buf, &pRn->Pop_sT[j] );

    if( j < pRn->D ){ 	/* Correlations only for fit variables */
      for( k=0; k < pRn->D; ++k ){	
	for( i=0; i<pRn->NP; ++i )
	  buf2[i] = pRn->Pop[i][k];
	do_cOrr( pRn->NP, buf, buf2, &pRn->Pop_cO[j][k] );
      }
    }
  }
  xfree((char *) buf2 );  
  xfree((char *) buf );  
}

/* ------------------------------------------------------------------------ */
void printMem( pRun *pRn, FILE *fp, double *pop )
{
  int j;

  for( j=0; j<pRn->D; ++j ) fprintf( fp, "%.10g ", pop[j] );
  fprintf( fp, "%10.6g ", pop[pRn->P_errS] );
  for( j=0; j<pRn->fCaseN; ++j ) fprintf( fp, "%6.3g ", pop[pRn->P_errD + j] );
  fprintf( fp, "%6.3g sec ", pop[pRn->P_etime] );
}

/* ------------------------------------------------------------------------ */
void printGen( pRun *pRn, FILE *fp, double **pop )
{
  int i;

  for( i=0; i<pRn->NP; i++ ){
    fprintf( fp, "%3d ", i );    
    printMem( pRn, fp, pop[i] );
    fprintf( fp, "\n" );
  }
}

/* ------------------------------------------------------------------------ */
void do_sTat_SA_Pop( pRun *pRn ){
  int i, j, k;
  double *buf, *buf2;
  sAdata *sA;    

  if( pRn->sA->Pop_f == 0 ) return;

  sA = pRn->sA;
  buf = (double *) xmalloc( (sA->n) *sizeof( double ));
  buf2 = (double *) xmalloc( (sA->n) *sizeof( double ));

  for( j=0; j<pRn->Pop_D; ++j ){
    for( i=0; i<sA->n; ++i ){
      buf[i] = sA->Pop[i][j];
    }
    do_sTat( sA->n, buf, &sA->sT[j] );
    
    if( j < pRn->D ){ 	
      for( k=0; k < pRn->D; ++k ){	
	for( i=0; i<sA->n; ++i )
	  buf2[i] = sA->Pop[i][k];
	do_cOrr( sA->n, buf, buf2, &sA->cO[j][k] );
      }
    }
  }
  xfree((char *) buf2 );  
  xfree((char *) buf );  
}

/* ------------------------------------------------------------------------ */
void log_SA_Pop_detail( pRun *pRn, FILE *fp )
{
  char buf[128];
  int i;

  if( pRn->sA->Pop_f == 0 ) return;

  jTime_now( buf, 128, "%F %H:%M:%S" );
  fprintf( fp, "SA_Pop_begin gen_N %d %s ----------\n", pRn->gen_N, buf );
  print_Headers( pRn, fp );
  for( i=0; i<pRn->sA->n; i++ ){
    fprintf( fp, "%3d ", i );    
    if( pRn->sA->n == pRn->sA->nMax ) printMem( pRn, fp, pRn->sA->Pop[pRn->sA->idx[i]] );
    else printMem( pRn, fp, pRn->sA->Pop[i] );
    fprintf( fp, "\n" );
  }
  fprintf( fp,"SA_Pop_end gen_N %d\n", pRn->gen_N );
}

/* ------------------------------------------------------------------------ */
void log_SA_Pop_summ( pRun *pRn, FILE *fp )
{
  int ipar, jpar;
  cOrr *cO;
  sAdata *sA;
  /* fprintf( pRn->log_fp, "%20s %12s %12s %12s %12s %12s %12s %12s %12s\n", 
     "Fit-parm", "bst_evr","bst_gen", "median", "mean", "SD", "CV%", "min", "max", "lims" ); */  

  if( pRn->sA->Pop_f == 0 ) return;
  do_sTat_SA_Pop( pRn );
  sA = pRn->sA;

  fprintf( pRn->log_fp, "%20s %3s|\n", "SA_Correlations", "---" );
  for( ipar=0; ipar<pRn->D; ipar++ ){
    fprintf( pRn->log_fp, "%20s %3d|", pRn->fPar[ipar]->name, ipar );
    for( jpar=0; jpar<=ipar; jpar++ ){
      fprintf( pRn->log_fp, " %3.0f", 100*sA->cO[ipar][jpar].r );
    }
    fprintf( pRn->log_fp, "\n" );
  }
  fprintf( pRn->log_fp, "%20s %3s|", "End_SA_Correlations", "---" );
  for( ipar=0; ipar<pRn->D; ipar++ ) fprintf( pRn->log_fp, " %3d", ipar );
  fprintf( pRn->log_fp, " |---\n" );

  fprintf( pRn->log_fp, "%20s %3s|\n", "SR_Correlations", "---" );
  for( ipar=0; ipar<pRn->D; ipar++ ){
    fprintf( pRn->log_fp, "%20s %3d|", pRn->fPar[ipar]->name, ipar );
    for( jpar=0; jpar<=ipar; jpar++ ){
      cO = &(sA->cO[ipar][jpar]);
      fprintf( pRn->log_fp, " %3.0f", 100*cO->rs );
      if( cO->Prst < 1e-6 && cO->PrsD < 1e-6 ) fprintf( pRn->log_fp, "^6" );
      else if( cO->Prst < 1e-5 && cO->PrsD < 1e-5 ) fprintf( pRn->log_fp, "^5" );
      else if( cO->Prst < 1e-4 && cO->PrsD < 1e-4 ) fprintf( pRn->log_fp, "^4" );
      else if( cO->Prst < 1e-3 && cO->PrsD < 1e-3 ) fprintf( pRn->log_fp, "^3" );
      else fprintf( pRn->log_fp, "  " );
    }
    fprintf( pRn->log_fp, "\n" );
  }
  fprintf( pRn->log_fp, "%20s %3s|", "End_SR_Correlations", "---" );
  for( ipar=0; ipar<pRn->D; ipar++ ) fprintf( pRn->log_fp, " %3d  ", ipar );
  fprintf( pRn->log_fp, " |---\n" );


  for( ipar=0; ipar < pRn->fParN; ++ipar ){
    fprintf( fp, "%20s %12g %12g %12g %11g %12g %12.2f %12g %12g %10g:%-10g\n", 
	     pRn->fPar[ipar]->name,
	     pRn->best_ever[ipar], 
	     pRn->Pop[pRn->Pop_ibest][ipar],
	     sA->sT[ipar].median,
	     sA->sT[ipar].mean, sA->sT[ipar].sd, sA->sT[ipar].cv, 
	     sA->sT[ipar].min, sA->sT[ipar].max,
	     pRn->fPar[ipar]->lo, pRn->fPar[ipar]->hi );
  }

  fprintf( fp, "--------------------\n" );
  fprintf( fp, "%20s %12g %12g %12g %12g %12g %12g %12g %12.2f\n", 
           "cost-total",
           pRn->best_ever[pRn->P_errS],
           pRn->Pop[pRn->Pop_ibest][pRn->P_errS],
	   sA->sT[pRn->P_errS].median,
           sA->sT[pRn->P_errS].mean, sA->sT[pRn->P_errS].sd, sA->sT[pRn->P_errS].cv,
	   sA->sT[pRn->P_errS].min, sA->sT[pRn->P_errS].max );


  for( ipar=0; ipar<pRn->fCaseN; ++ipar )
    fprintf( fp, "%20s %12g %12g %12g %12g %12g %12g %12g %12.2f\n", 
             pRn->fCase[ipar]->name,
             pRn->best_ever[pRn->P_errD+ipar],
             pRn->Pop[pRn->Pop_ibest][pRn->P_errD+ipar],
	     sA->sT[pRn->P_errD+ipar].median,
             sA->sT[pRn->P_errD+ipar].mean, sA->sT[pRn->P_errD+ipar].sd, sA->sT[pRn->P_errD+ipar].cv,
             sA->sT[pRn->P_errD+ipar].min, sA->sT[pRn->P_errD+ipar].max );

}

/* ------------------------------------------------------------------------ */
void log_Gen( pRun *pRn ){
  char buf[128];
  int ipar, jpar, opar_i, iproc;
  static double cost_avg_prev;
  jRandom jR;

  hoc_best( pRn );	/* update fit_var values in hoc_best file */

  jTime_now( buf, 128, "%F %H:%M:%S" );

  fprintf( pRn->log_fp, "nextGen gen_N %d %s ----------\n", pRn->gen_N, buf );
  print_Headers( pRn, pRn->log_fp );
  printGen( pRn, pRn->log_fp, pRn->Pop );
  do_sTat_Pop( pRn );
  fprintf( pRn->log_fp,
	   "end_nextGen gen_N %4d %s nWin %3d %5.3g%% avg_imprv %5.3g%% cost-best %8.5g cost-total-avg %8.5g time_eavg %3.0f %3.0f\n", 
           pRn->gen_N, buf, pRn->nWin, 100.0*(double)pRn->nWin/(double)pRn->NP, 
	   (pRn->nWin > 0) ? 100.0*pRn->pWin/(double)pRn->nWin: 0.0,
	   pRn->best_ever[pRn->P_errS], pRn->Pop_sT[pRn->P_errS].mean,
	   pRn->time_eavg1, pRn->time_eavg2 );

  log_SA_Pop_detail( pRn, pRn->log_fp );

  for( iproc=0; iproc<pRn->Nproc; ++iproc )
    if( pRn->pHosts[iproc].nErr )
      fprintf( pRn->log_fp, "eval_slave ERRORs %s %d\n", 
	       pRn->pHosts[iproc].hostname, pRn->pHosts[iproc].nErr );

  fprintf( pRn->log_fp, "%20s %3s|\n", "Correlations", "---" );
  for( ipar=0; ipar<pRn->D; ipar++ ){
    fprintf( pRn->log_fp, "%20s %3d|", pRn->fPar[ipar]->name, ipar );
    for( jpar=0; jpar<=ipar; jpar++ ){
      fprintf( pRn->log_fp, " %3.0f", 100*pRn->Pop_cO[ipar][jpar].r );
    }
    fprintf( pRn->log_fp, "\n" );
  }
  fprintf( pRn->log_fp, "%20s %3s|", "EndCorrelations", "---" );
  for( ipar=0; ipar<pRn->D; ipar++ ) fprintf( pRn->log_fp, " %3d", ipar );
  fprintf( pRn->log_fp, " |---\n" );


  fprintf( pRn->log_fp, "%30s %12s %12s %12s %12s %8s %12s %12s %8s %10s %10s %10s\n", 
           "Fit-parm", "bst_evr","bst_gen", "median", "SDr", "CVr%", "mean", "SD", "CV%", "min", "max", "lims" );
  sTat sTa;
  for( opar_i=0; opar_i< pRn->ParmOrderN; opar_i++ ){
    if( pRn->ParmOrder[opar_i] < 1000 ){
      ipar = pRn->ParmOrder[opar_i];
      sTa = pRn->Pop_sT[ipar];
      
      fprintf( pRn->log_fp, "%30s %12g %12g %12g %12g %8.2f %12g %12g %8.2f %10g %10g %10g:%-10g\n", 
	       pRn->fPar[ipar]->name,
	       pRn->best_ever[ipar], 
	       pRn->Pop[pRn->Pop_ibest][ipar],
	       pRn->Pop_sT[ipar].median, pRn->Pop_sT[ipar].sdr, pRn->Pop_sT[ipar].cvr,
	       pRn->Pop_sT[ipar].mean, pRn->Pop_sT[ipar].sd, pRn->Pop_sT[ipar].cv, 
	       pRn->Pop_sT[ipar].min, pRn->Pop_sT[ipar].max,
	       pRn->fPar[ipar]->lo, pRn->fPar[ipar]->hi );

    }
    else {
      ipar = pRn->ParmOrder[opar_i] / 1000 - 1;
      fprintf( pRn->log_fp, "%30s %12g\n", 
	       pRn->sPar[ipar]->name,
	       pRn->sPar[ipar]->init );
    }
  }

  fprintf( pRn->log_fp, "--------------------\n" );
  fprintf( pRn->log_fp, "%30s %12g %12g %12g %12g %8.2f %12g %12g %8.2f %10g %10g\n", 
           "cost-total",
           pRn->best_ever[pRn->P_errS],
           pRn->Pop[pRn->Pop_ibest][pRn->P_errS],
	   pRn->Pop_sT[pRn->P_errS].median, pRn->Pop_sT[pRn->P_errS].sdr, pRn->Pop_sT[pRn->P_errS].cvr,
           pRn->Pop_sT[pRn->P_errS].mean, pRn->Pop_sT[pRn->P_errS].sd, pRn->Pop_sT[pRn->P_errS].cv,
	   pRn->Pop_sT[pRn->P_errS].min, pRn->Pop_sT[pRn->P_errS].max ); 

  for( ipar=0; ipar<pRn->fCaseN; ++ipar )
    fprintf( pRn->log_fp, "%30s %12g %12g %12g %12g %8.2f %12g %12g %8.2f %10g %10g\n", 
             pRn->fCase[ipar]->name,
             pRn->best_ever[pRn->P_errD+ipar],
             pRn->Pop[pRn->Pop_ibest][pRn->P_errD+ipar],
	     pRn->Pop_sT[pRn->P_errD+ipar].median, pRn->Pop_sT[pRn->P_errD+ipar].sdr, pRn->Pop_sT[pRn->P_errD+ipar].cvr,
             pRn->Pop_sT[pRn->P_errD+ipar].mean, pRn->Pop_sT[pRn->P_errD+ipar].sd, pRn->Pop_sT[pRn->P_errD+ipar].cv,
             pRn->Pop_sT[pRn->P_errD+ipar].min, pRn->Pop_sT[pRn->P_errD+ipar].max );

  fprintf( pRn->log_fp, "%30s %12g %12g %12g %12g %8.2f %12g %12g %8.2f %10g %10g\n", 
	   "elapsed-time",
	   pRn->best_ever[pRn->P_etime],
	   pRn->Pop[pRn->Pop_ibest][pRn->P_etime],
	   pRn->Pop_sT[pRn->P_etime].median, pRn->Pop_sT[pRn->P_etime].sdr, pRn->Pop_sT[pRn->P_etime].cvr,
	   pRn->Pop_sT[pRn->P_etime].mean, pRn->Pop_sT[pRn->P_etime].sd, pRn->Pop_sT[pRn->P_etime].cv,
	   pRn->Pop_sT[pRn->P_etime].min, pRn->Pop_sT[pRn->P_etime].max );

  save_random_state( &jR );
  fprintf( pRn->log_fp, "%20s %ld\n", "random.n_count", jR.n_count );

  log_SA_Pop_summ( pRn, pRn->log_fp );

  fflush( pRn->log_fp );
  cost_avg_prev = pRn->Pop_sT[pRn->P_errS].mean;	/* previous cost total avg */  
}

/* ------------------------------------------------------------------------ */
void var_lims( pRun *pRn, double *pop, int ipop )
{
  int i;

  if( strEQ( pRn->var_lim_stgy, "randE" )){
    for( i=0; i<pRn->D; ++i ){
      if( pop[i] < pRn->fPar[i]->lo ) {
	if( ipop < 0 )
	  pop[i] = du_dev( pRn->fPar[i]->lo, pRn->fPar[i]->hi );
	else 
	  pop[i] = du_dev( pRn->fPar[i]->lo, pRn->Pop[ipop][i] );
      }
      else if( pop[i] > pRn->fPar[i]->hi ) {
	if( ipop < 0 ) 
	  pop[i] = du_dev( pRn->fPar[i]->lo, pRn->fPar[i]->hi );
	else 
	  pop[i] = du_dev( pRn->Pop[ipop][i], pRn->fPar[i]->hi );
      }
    }
  }
  else if( strEQ( pRn->var_lim_stgy, "clip" )){
    for( i=0; i<pRn->D; ++i ){
      if( pop[i] < pRn->fPar[i]->lo ) pop[i] = pRn->fPar[i]->lo;
      if( pop[i] > pRn->fPar[i]->hi ) pop[i] = pRn->fPar[i]->hi;
    }
  }
  else if( strEQ( pRn->var_lim_stgy, "bounceP" )){
    for( i=0; i<pRn->D; ++i ){
      if( pop[i] < pRn->fPar[i]->lo ) pop[i] = pRn->fPar[i]->lo + ( pRn->fPar[i]->lo - pop[i] ) * du_dev0();
      if( pop[i] > pRn->fPar[i]->hi ) pop[i] = pRn->fPar[i]->hi - ( pop[i] - pRn->fPar[i]->hi ) * du_dev0();
    }
  }
  else {
    printf( "\n\n\t\tERROR var_lims invalid var_lim_stgy >>%s<<\n\n", pRn->var_lim_stgy );
    exit( 1 );
  }
}

/* ------------------------------------------------------------------------
   Create hoc file to read into nrngui for best fit
   ------------------------------------------------------------------------ */
void hoc_best( pRun *pRn )
{
  FILE *fp;

  if( NULL == (fp = fopen( pRn->hoc_best, "w" ))){
    printf("\nERROR Cannot write to file >>%s<<\n", pRn->hoc_best );
    exit( 1 );
  }
  /* Copy hoc_main */
  fprintf( fp, "\n\n// ------hoc_main--->>%s<<---------------\n", pRn->hoc_main );
  write_file_content( pRn, fp, pRn->hoc_main );
  fprintf( fp, "\n// ------end hoc_main------\n\n" );

  write_hoc_asg( fp, pRn, pRn->best_ever );
  fprintf( fp, "\n{ load_file( \"nrngui.hoc\" ) }\n" );

  write_fit_var_list_hoc( fp, pRn );

  write_eval_hoc( fp, pRn );

  fprintf( fp, "\n\
dfc_plot_all()\n\
\n\n" );   
  
  fclose( fp );
}

/* ------------------------------------------------------------------------
   Create hoc file to run a pop_buf
   ------------------------------------------------------------------------ */
void hoc_write_pop_buf( pRun *pRn, char *fname, double pop_buf[] )
{
  FILE *fp;

  if( NULL == (fp = fopen( fname, "w" ))){
    printf("\nERROR hoc_write_pop_buf Cannot write to file >>%s<<\n", fname );
    exit( 1 );
  }
  /* Copy hoc_main */
  fprintf( fp, "\n\n// ------hoc_main--->>%s<<---------------\n", pRn->hoc_main );
  write_file_content( pRn, fp, pRn->hoc_main );
  fprintf( fp, "\n// ------end hoc_main------\n\n" );

  write_hoc_asg( fp, pRn, pop_buf );
  fprintf( fp, "\n{ load_file( \"nrngui.hoc\" ) }\n" );
  write_eval_hoc( fp, pRn );

  fprintf( fp, "\n\
dfc_plot_all()\n\
\n\n" );   
  
  fclose( fp );
}

/* -------------------------------------------------------------------------------- */
void write_fit_var_list_hoc( FILE *fp, pRun *pRn )
{
  int ipar, jpar;

  do_sTat_Pop( pRn );
  fprintf( fp, "\n// ---------- write_fit_var_list ----------\n\
begintemplate pDE_FitVar\n\
  strdef name\n\
  objref r, m, b\n\
  public name, best, mean, SD, CV, min, max, low, hi, median, r, m, b\n\
  proc init(){\n\
    name = $s1\n\
    best = $2\n\
    mean = $3\n\
    SD = $4\n\
    CV = $5\n\
    min = $6\n\
    max = $7\n\
    low = $8\n\
    hi = $9\n\
    median = $10\n\
    r = new Vector()\n\
    m = new Vector()\n\
    b = new Vector()\n\
  }\n\
  public add_r\n\
  proc add_r(){ local i\n\
    for i=1,numarg() r.append( $i )\n\
  }\n\
  public add_m\n\
  proc add_m(){ local i\n\
    for i=1,numarg() m.append( $i )\n\
  }\n\
  public add_b\n\
  proc add_b(){ local i\n\
    for i=1,numarg() b.append( $i )\n\
  }\n\
endtemplate pDE_FitVar\n\
\n\
objref pDE_fv\n\
pDE_fv = new List()\n\n" );

  for( ipar=0; ipar < pRn->D; ++ipar ){

    fprintf( fp, "{\n  pDE_fv.append( new pDE_FitVar( \"%s\", %g, %g, %g, %g, %g, %g, %g, %g, %g ))\n",
	     pRn->fPar[ipar]->name,
	     pRn->best_ever[ipar], 
	     pRn->Pop_sT[ipar].median,
	     pRn->Pop_sT[ipar].mean, pRn->Pop_sT[ipar].sd, pRn->Pop_sT[ipar].cv, 
	     pRn->Pop_sT[ipar].min, pRn->Pop_sT[ipar].max,
	     pRn->fPar[ipar]->lo, pRn->fPar[ipar]->hi );

    fprintf( fp, "  pDE_fv.o(pDE_fv.count-1).add_r( %g", pRn->Pop_cO[ipar][0].r );
    for( jpar=1; jpar < pRn->D; ++jpar ) fprintf( fp, ", %g", pRn->Pop_cO[ipar][jpar].r );
    fprintf( fp, " )\n" );

    fprintf( fp, "  pDE_fv.o(pDE_fv.count-1).add_m( %g", pRn->Pop_cO[ipar][0].m );
    for( jpar=1; jpar < pRn->D; ++jpar ) fprintf( fp, ", %g", pRn->Pop_cO[ipar][jpar].m );
    fprintf( fp, " )\n" );

    fprintf( fp, "  pDE_fv.o(pDE_fv.count-1).add_b( %g", pRn->Pop_cO[ipar][0].b );
    for( jpar=1; jpar < pRn->D; ++jpar ) fprintf( fp, ", %g", pRn->Pop_cO[ipar][jpar].b );
    fprintf( fp, " )\n}\n" );
  }
}

/* --------------------------------------------------------------------------------
 generate n random non-repeating numbers in [0,NP-1] and all different from ix
 -------------------------------------------------------------------------------- */
void randoms( pRun *pRn, int *r, int n, int ix )
{ 
  int i, j, good;

  if( n >= pRn->NP ){
    printf( "randoms: ERROR NP=%d is too small; need at least %d\n", pRn->NP, n+1 );
    exit( 1 );
  }
  i = 0;
  while( i < n ){
    r[i] = iu_dev( 0, pRn->NP-1 );
    good = 1;
    for( j=0; j<i; ++j ) {
      if( r[i] == r[j] || ( r[i] == ix) ) {
	good = 0;
	break;
      }
    }
    if( good ) i += 1;
  }
}

/* ------------------------------------------------------------------------ */
void  assignd(int D, double *a, double *b )
{
  int j;
  for (j=0; j<D; j++) a[j] = b[j];
}

/* ======================================================================== */
void alloc_array1d( double **a, int sz )
{
  *a = (double *) xmalloc( sz * sizeof( double ));
}

/* ------------------------------------------------------------------------ */
void alloc_array2d( double ***a, int x, int y )
{
  int i;
  double **aa;
  aa = (double **) xmalloc( x * sizeof( double * ));
  for( i=0; i<x; ++i ) 
    aa[i] = (double *) xmalloc( y * sizeof( double ));
  *a = aa;
}

void xfree_array2d( double **a, int x ){
  int i;
  for( i=0; i<x; ++i ) xfree( (char *) a[i] );
  xfree( (char *) a );
}

 
