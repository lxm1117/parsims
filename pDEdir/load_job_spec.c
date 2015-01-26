/* ========================================================================
   pDE: Parallel version of Storn and Price's Differential evolution 
   applied to NEURON modeling

   c2005 Jose Ambros-Ingerson jose@kiubo.net
   
   $Id: load_job_spec.c,v 1.53 2008/12/06 00:13:00 jose Exp $

   ======================================================================== */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mpi.h>

#include "jLib.h"
#include "pDE.h"

/* ------------------------------------------------------------------------ */
void load_job_spec( int argc, char *argv[], pRun *pRn )
{
  char	*Fname="load_job_spec";
  char	Case[256], buf[1024];
  FILE	*fpin_ptr;
  jString	*Line;
  int		fLimN;
  FitParm	*fLim[FPSZ];

  sprintf( pRn->tmp_dir, "/tmp" );		/* default values */
  pRn->idebug = 0;
  pRn->abort_on_eval_error = 0;		/* default no abort */
  pRn->fit_lims[0] = '\0';
  sprintf( pRn->Pop_init, "Pop-init uniform noset" );

  pRn->pB->n = 1;	/* size of pBest array */
  pRn->sA->Pop_f = 2;
  pRn->sA->Best_Rad_Pcnt = 0.05;

  pRn->fParN = pRn->sParN = pRn->fCaseN = pRn->ParmOrderN = fLimN = 0;

  if( (NULL==(pRn->HOME=getenv("HOME"))) && pRn->rank==0 ){
    printf("\n\n\tWARNING HOME variable is not set\n" );
  }
  if( (NULL==(pRn->PWD=getenv("PWD"))) && pRn->rank==0 ){
    printf("\n\n\tWARNING PWD variable is not set\n" );
  }

  if( argc < 2 || argc > 3 ){
    if( pRn->rank==0 ) printf("\n\tUsage pDE input-file [log-file]\n" );
    exit( 1 ); 
  }

  resolve_path( pRn, argv[1], pRn->input_file );

  if( NULL==(fpin_ptr=fopen( pRn->input_file, "r" )) ){
    if( pRn->rank==0 ) printf("%s: Cannot open input file >>%s<<\n", Fname, pRn->input_file );
    exit( 1 );
  }
  if( argc == 3 ) strcpy( pRn->log_name, argv[2] );
  else {
    jTime_now( buf, 256, "%d%b%g-%H-%M-%S" );
    sprintf( pRn->log_name, "%s_%s.log", pRn->input_file, buf );
  }

  get_ids( pRn );

  if ( pRn->rank==0 )
    if( NULL==(pRn->log_fp=fopen( pRn->log_name, "a" )) ){
      printf("%s: Cannot open log file %s\n", Fname, argv[1]);
      exit( 1 );
    }
  /* sprintf( pRn->hoc_best, "%s-best.hoc", pRn->log_name ); */
  sprintf( pRn->hoc_best, "%s-cbest.hoc", pRn->log_name ); /* cbest includes hoc_main code */

  Line = jString_new();
  while( EOF != jLine_read( fpin_ptr, Line ) ){
    if( 1 == sscanf( Line->s, "%s", Case )){

      if( strEQ( Case, "Tmp-dir" )){
	if( 2 == sscanf( Line->s, "%s %s", Case, pRn->tmp_dir ) )
	  resolve_path( pRn, pRn->tmp_dir, pRn->tmp_dir );
	else {
	  if( pRn->rank==0 ) 
	    fprintf( stdout, "\n\n%s ERROR: Tmp-dir line invalid \n>>%s<<\n", Fname, Line->s );
	  exit( 1 );
	}
      }

      else if( strEQ( Case, "VERBATIM" )) do_verbatim( pRn, fpin_ptr );
      else if( strEQ( Case, "abort_on_eval_error" )) pRn->abort_on_eval_error = 1;

      else if( strEQ( Case, "Pop-init" )){
	strcpy( pRn->Pop_init, Line->s );
      }

      else if( strEQ( Case, "Fit-SA" )){
	if( 3 != sscanf( Line->s, "%s %lf %lf", Case, &pRn->sA->Pop_f, &pRn->sA->Best_Rad_Pcnt ))
	  if( pRn->rank==0 ){
	    fprintf( stdout, "\n\n%s ERROR: Fit-SA line invalid \n>>%s<<\n", Fname, Line->s );
	    exit( 1 );
	  }
      }
      
      else if( strEQ( Case, "Fit-lims" )){
	if( 2 == sscanf( Line->s, "%s %s", Case, pRn->fit_lims ) )
	  resolve_path( pRn, pRn->fit_lims, pRn->fit_lims );
	else {
	  if( pRn->rank==0 ) 
	    fprintf( stdout, "\n\n%s ERROR: Fit-lims line invalid \n>>%s<<\n", Fname, Line->s );
	  exit( 1 );
	}
      }

      else if( strEQ( Case, "nBest" )){
	if( 2 == sscanf( Line->s, "%s %d", Case, &pRn->pB->n ) ){}
	else {
	  if( pRn->rank==0 ) 
	    fprintf( stdout, "\n\n%s ERROR: nBest line invalid \n>>%s<<\n", Fname, Line->s );
	  exit( 1 );
	}
      }

      else if( strEQ( Case, "Fit" )){
	if( 10 == sscanf( Line->s, "%s %s %d %d %d %d %lf %lf %s %s", 
			      Case, pRn->name, &pRn->seed, &pRn->genmax, &pRn->NpD, 
			       &pRn->strategy, &pRn->F, &pRn->CR, pRn->var_lim_stgy, pRn->hoc_main )){
	  if( strNE(pRn->var_lim_stgy, "clip") && 
	      strNE(pRn->var_lim_stgy, "bounceP") && 
	      strNE(pRn->var_lim_stgy, "randE") && 
	      pRn->rank==0 ){
	    fprintf( stdout, "\n\n\t\t%s ERROR: Fit line invalid for var_lim_stgy\n\t\t>>%s<<\n\n\n", Fname, Line->s );
	    exit( -1 );
	  }
	  resolve_path( pRn, pRn->hoc_main, pRn->hoc_main );
	}
	else if( 9 == sscanf( Line->s, "%s %s %d %d %d %d %lf %lf %s", 
			      Case, pRn->name, &pRn->seed, &pRn->genmax, &pRn->NpD, 
			       &pRn->strategy, &pRn->F, &pRn->CR, pRn->hoc_main )){
	  sprintf( pRn->var_lim_stgy, "clip" );
	  resolve_path( pRn, pRn->hoc_main, pRn->hoc_main );
	}
	else {
	  if( pRn->rank==0 ) 
	    fprintf( stdout, "\n\n%s ERROR: Fit line invalid \n>>%s<<\n", Fname, Line->s );
	  exit( 1 );
	}
      }

      else if( strEQ( Case, "Fit-case" )){
	if( pRn->fCaseN >= FPSZ ){
	  if( pRn->rank==0) 
	    fprintf( stdout, "\n\n%s ERROR: to many Fit-case cases. Increase FPSZ and recompile\n", Fname );
	  exit( 1 );
	}
	FitCase *aP;
	aP = (FitCase *) xmalloc( sizeof( FitCase ) );
	if( 11 == sscanf( Line->s, "%s %s %s %s %s %s %s %s %s %s %s", 
			 Case, aP->name, aP->template, aP->func, aP->scale, 
			 aP->hoc_var, aP->hoc_before, aP->hoc_after, aP->tgt_files,
			 aP->tgt_before, aP->tgt_after )){

	  pRn->fCase[pRn->fCaseN++] = aP;
	}
	else {
	  if( pRn->rank==0 ) 
	    fprintf( stdout, "\n\n%s ERROR: Fit-case line invalid \n>>%s<<\n", Fname, Line->s );
	  exit( 1 );
	}
      }

      else if( strEQ( Case, "Fit-parm" ) || strEQ( Case, "Fit-parmLog" )){
	if( pRn->fParN >= FPSZ ){
	  if( pRn->rank==0) 
	    fprintf( stdout, "\n\n%s ERROR: to many Fit-parm cases. Increase FPSZ and recompile\n", Fname );
	  exit( 1 );
	}
	FitParm *aP;
	aP = (FitParm *) xmalloc( sizeof( FitParm ) );
	if( strEQ( Case, "Fit-parmLog" ) ) aP->logT=1;
	else aP->logT=0;
	if( 5 == sscanf( Line->s, "%s %s %lf %lf:%lf", 
			 Case, aP->name, &aP->init, &aP->lo, &aP->hi )){
	  if( aP->lo > aP->hi ){
	    if( pRn->rank==0 ) 
	      printf( "ERROR lower limit >>%g<< is greater than upper limit >>%g<< in Line >>%s<<\n", 
		      aP->lo, aP->hi, Line->s );
	    exit( 1 );
	  }
	  pRn->ParmOrder[pRn->ParmOrderN++] = pRn->fParN;
	  pRn->fPar[pRn->fParN++] = aP;
	}
	else {
	  if( pRn->rank==0 ) 
	    fprintf( stdout, "\n\n%s ERROR: Fit-parm line invalid \n>>%s<<\n", Fname, Line->s );
	  exit( 1 );
	}
      }

      else if( strEQ( Case, "Subs-parm" )){	/* Subs-parm SubParm Parm_1 .. Parm_n (n>=1) */
	if( pRn->subParN >= FPSZ ){
	  if( pRn->rank==0) 
	    fprintf( stdout, "\n\n%s ERROR: to many Subs-parm cases. Increase FPSZ and recompile\n", Fname );
	  exit( 1 );
	}
	SubsParm *aP; int ia, ncA; char **cA;
	aP = (SubsParm *) xmalloc( sizeof( SubsParm ) );
	cA = split_into_char_array( Line->s, &ncA );
	if( ncA >= 3 ){
	  aP->subname = cA[1]; 
	  aP->n = ncA - 2;
	  aP->name = (char **) xmalloc( aP->n * sizeof( char *));
	  for( ia=0; ia<aP->n; ia++ ) aP->name[ia] = cA[ia+2];
	  pRn->subPar[ pRn->subParN++ ] = aP;
	}
	else {
	  if( pRn->rank==0 ) 
	    fprintf( stdout, "\n\n%s ERROR: Subs-parm line invalid \n>>%s<<\n", Fname, Line->s );
	  exit( 1 );
	}
      }

      else if( strEQ( Case, "Fit-lim" )){
	if( fLimN >= FPSZ ){
	  if( pRn->rank==0) 
	    fprintf( stdout, "\n\n%s ERROR: to many Fit-lim cases. Increase FPSZ and recompile\n", Fname );
	  exit( 1 );
	}
	FitParm *aP;
	aP = (FitParm *) xmalloc( sizeof( FitParm ) );
	if( 4 == sscanf( Line->s, "%s %s %lf %lf", 
			 Case, aP->name, &aP->lo, &aP->hi )){
	  if( aP->lo > aP->hi ){
	    if( pRn->rank==0 ) 
	      printf( "ERROR lower limit >>%g<< is greater than upper limit >>%g<< in Line >>%s<<\n", 
		      aP->lo, aP->hi, Line->s );
	    exit( 1 );
	  }
	  int fi, fi_found;
	  fi_found = 0;
	  for( fi=0; fi<fLimN && !fi_found; ++fi )
	    if( strEQ( fLim[fi]->name, aP->name )){
	      fLim[fi]->lo = aP->lo;
	      fLim[fi]->hi = aP->hi;
	      fi_found = 1;
	    }
	  if( !fi_found ) fLim[fLimN++] = aP;
	}
	else {
	  if( pRn->rank==0 ) 
	    fprintf( stdout, "\n\n%s ERROR: Fit-lim line invalid \n>>%s<<\n", Fname, Line->s );
	  exit( 1 );
	}
      }

      else if( strEQ( Case, "Set-parm" )){
	if( pRn->sParN >= FPSZ ){
	  if( pRn->rank==0) 
	    fprintf( stdout, "\n\n%s ERROR: to many Set-parm cases. Increase FPSZ and recompile\n", Fname );
	  exit( 1 );
	}
	FitParm *aP;
	aP = (FitParm *) xmalloc( sizeof( FitParm ) );
	if( 5 == sscanf( Line->s, "%s %s %lf %lf:%lf", 
			 Case, aP->name, &aP->init, &aP->lo, &aP->hi )){
	  pRn->ParmOrder[pRn->ParmOrderN++] = ( pRn->sParN + 1 ) * 1000;
	  pRn->sPar[pRn->sParN++] = aP;
	}
	else {
	  if( pRn->rank==0 ) fprintf( stdout, "\n\n%s ERROR: Set-parm line invalid \n>>%s<<\n", Fname, Line->s );
	  exit( 1 );
	}
      }
      /* TO DO: else check if comment or blank line; if not signal error */
    }
  }

  if( pRn->rank==0 ) load_fit_lims( pRn );
  if( pRn->rank==0 ) apply_lims( pRn, fLimN, fLim );

  pRn->D = pRn->fParN;
  pRn->NP = pRn->D * pRn->NpD;

  fclose( fpin_ptr );
}

/* -------------------------------------------------------------------------------- */
void log_job( pRun *pRn ){
  char buf[128];
  int i;
  
  if( pRn->rank != 0 ) return;		/* only master logs run */

  fprintf( pRn->log_fp, "========================================\n" );
  jTime_now( buf, 128, "%F %H:%M:%S" );
  fprintf( pRn->log_fp, "pDE-v%d.%d log started on %s\n", pDE_MV, pDE_mV, buf );
  fflush( pRn->log_fp );

  fprintf( pRn->log_fp, "\nFiles & environment --------------\n" );
  fprintf( pRn->log_fp, "%15s >>%s<<\n%15s >>%s<<\n%15s >>%s<<\n%15s >>%s<<\n", 
	   "input_file", pRn->input_file, "Tmp-dir", pRn->tmp_dir,
	   "HOME", pRn->HOME, "PWD", pRn->PWD );

  fprintf( pRn->log_fp, "\nProcesses ----------\n" );
  fprintf( pRn->log_fp, "%4s %8s %23s\n", "rank", "pid", "hostname" );
  for( i=0; i<pRn->Nproc; ++i ) 
    fprintf( pRn->log_fp, "%4d %8d %23s\n", i, pRn->pHosts[i].pid, pRn->pHosts[i].hostname );
  fflush( pRn->log_fp );

  fprintf( pRn->log_fp, "\npDE job spec ----------\n" );
  fprintf( pRn->log_fp, "===== Fit >>%s<<\n", pRn->name );
  fprintf( pRn->log_fp, "%15s   %-d\n%15s   %-d\n%15s   %-d\n",
	   "seed", pRn->seed, "genmax", pRn->genmax, "NpD", pRn->NpD );
  fprintf( pRn->log_fp, "%15s   %-d\n%15s   %-g\n%15s   %-g\n%15s   %-s\n%15s   %-s\n%15s   %-d\n",
	   "strategy", pRn->strategy, "F", pRn->F, "CR", pRn->CR, "var_lim_stgy", pRn->var_lim_stgy, 
	   "hoc_main", pRn->hoc_main, "abort_on_eval_error", pRn->abort_on_eval_error );

  fprintf( pRn->log_fp, "%15s   %-d\n",
	   "nBest", pRn->pB->n );

  fprintf( pRn->log_fp, "%15s   Pop_f %g Best_Rad_Pcnt %g\n",
	   "Fit-SA", pRn->sA->Pop_f, pRn->sA->Best_Rad_Pcnt );

  fprintf( pRn->log_fp, "\n%s\n", pRn->Pop_init );

  for( i=0; i<pRn->fCaseN; ++i ){
    FitCase *aP;
    aP = pRn->fCase[i];
    fprintf( pRn->log_fp, "\n   == Fit-case >>%s<<\n", aP->name );
    fprintf( pRn->log_fp, "%15s   %-10s\n", "template", aP->template );
    fprintf( pRn->log_fp, "%15s   %-10s\n", "func", aP->func );
    fprintf( pRn->log_fp, "%15s   %-10s\n", "scale", aP->scale );
    fprintf( pRn->log_fp, "%15s   %-10s\n", "hoc_var", aP->hoc_var );
    fprintf( pRn->log_fp, "%15s   %-10s\n", "hoc_before", aP->hoc_before );
    fprintf( pRn->log_fp, "%15s   %-10s\n", "hoc_after", aP->hoc_after );
    fprintf( pRn->log_fp, "%15s   %-10s\n", "tgt_files", aP->tgt_files );
    fprintf( pRn->log_fp, "%15s   %-10s\n", "tgt_before", aP->tgt_before );
    fprintf( pRn->log_fp, "%15s   %-10s\n", "tgt_after", aP->tgt_after );
  }
  fflush( pRn->log_fp );

  fprintf( pRn->log_fp, "\nFit-lims >>%s<<\n", pRn->fit_lims );

  fprintf( pRn->log_fp, "\n" );
  fprintf( pRn->log_fp, "%20s %10s %12s\n", "hoc_name", "init", "lims" );
  fprintf( pRn->log_fp, "Set-parm\n" );
  for( i=0; i<pRn->sParN; ++i ){
    FitParm *aP;
    aP = pRn->sPar[i];
    fprintf( pRn->log_fp, "%20s %10g %10g:%-10g\n", 
	   aP->name, aP->init, aP->lo, aP->hi );
  }
  fflush( pRn->log_fp );
  fprintf( pRn->log_fp, "Fit-parm\n" );
  for( i=0; i<pRn->fParN; ++i ){
    FitParm *aP;
    aP = pRn->fPar[i];
    fprintf( pRn->log_fp, "%20s%3d %10g %10g:%-10g", 
	       aP->name, i+1, aP->init, aP->lo, aP->hi );
    if( aP->logT == 1 ) fprintf( pRn->log_fp, "%10s", "LogT" );
    fprintf( pRn->log_fp, "\n" );
  }
  fflush( pRn->log_fp );

  fprintf( pRn->log_fp, "Subs-parm\n" );
  for( i=0; i<pRn->subParN; ++i ){
    SubsParm *aP; int ia;
    aP = pRn->subPar[i];
    fprintf( pRn->log_fp, "%20s => ", aP->subname );
    for( ia=0; ia<aP->n; ia++ ) fprintf( pRn->log_fp, "%20s ", aP->name[ia] );
    fprintf( pRn->log_fp, "\n" );
  }
  fflush( pRn->log_fp );

  fprintf( pRn->log_fp, "\n------VERBATIM---------\n%s------ENDVERBATIM-------", pRn->hoc_verbatim );

  /* Copy hoc_main to log file */
  fprintf( pRn->log_fp, "\n------hoc_main--->>%s<<---------------\n", pRn->hoc_main );
  write_file_content( pRn, pRn->log_fp, pRn->hoc_main );
  fprintf( pRn->log_fp, 
	   "------end_hoc_main--------------------------------------------------------------------\n" );
  /* Copy pDE_spec to log file */
  fprintf( pRn->log_fp, "\n------pDE_spec--->>%s<<---------------\n", pRn->input_file );
  write_file_content( pRn, pRn->log_fp, pRn->input_file );
  fprintf( pRn->log_fp, 
	   "------end_pDE_spec--------------------------------------------------------------------\n" );

  print_Headers( pRn, pRn->log_fp );
}

/* -------------------------------------------------------------------------------- */
void print_Headers( pRun *pRn, FILE *fp )
{
  int i;

  fprintf( fp, "%3s ", "n" );    
  for( i=0; i<pRn->D; ++i )
    fprintf( fp, "%6s ", pRn->fPar[i]->name );

  fprintf( fp, "%6s", "cost-total " );
  for( i=0; i<pRn->fCaseN; ++i )
    fprintf( fp, "%6s ", pRn->fCase[i]->name );

  fprintf( fp, "\n" );

  fflush( fp );
}

/* -------------------------------------------------------------------------------- */
void get_ids( pRun *pRn )
{
  char res[STR_SZ];
  int iproc, mypid, tag;
  MPI_Status status;

  tag = 1;
  if( pRn->rank == 0 ){
    pRn->pHosts = (pHost *) xmalloc( pRn->Nproc * sizeof( pHost ));
    pRn->pHosts[0].pid = getpid();
    for( iproc=0; iproc<pRn->Nproc; ++iproc ) pRn->pHosts[iproc].nErr = 0;
    iproc = 1;
    while( iproc < pRn->Nproc ){
      MPI_Recv( &mypid, 1, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status );
      pRn->pHosts[status.MPI_SOURCE].pid = mypid;
      iproc++;
    }
  }
  else {
    mypid = getpid();
    MPI_Send( &mypid, 1, MPI_INT, 0, tag, MPI_COMM_WORLD );
  }

  tag = 2;
  if( pRn->rank == 0 ){
    gethostname( pRn->pHosts[0].hostname, STR_SZ );

    iproc = 1;
    while( iproc < pRn->Nproc ){
      MPI_Recv( res, STR_SZ, MPI_CHAR, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status );
      strcpy( pRn->pHosts[status.MPI_SOURCE].hostname, res );
      iproc++;
    }
    for( iproc=0; iproc<pRn->Nproc; ++iproc )
      printf( "rank %d pid %d hostname >>%s<<\n", iproc, pRn->pHosts[iproc].pid, pRn->pHosts[iproc].hostname );
  }
  else {
    gethostname( res, STR_SZ );
    MPI_Send( res, STR_SZ, MPI_CHAR, 0, tag, MPI_COMM_WORLD );
  }
}
  
/* --------------------------------------------------------------------------------
   read lims from file and over-ride values in fPar
   -------------------------------------------------------------------------------- */
void load_fit_lims( pRun *pRn )
{
  FILE *fp;
  char  Case[256];
  FitParm *lPar[256], *aP;
  jString	*Line;
  int lParN;

  lParN = 0;

  if( strEQ( pRn->fit_lims, "" ) ) return;

  if( NULL==(fp=fopen( pRn->fit_lims, "r" )) ){
    if( pRn->rank==0 ) printf("Cannot open fit-lims >>%s<<\n", pRn->fit_lims );
    exit( 1 );
  }
  Line = jString_new();
  while( EOF != jLine_read( fp, Line ) ){
    if( 1 == sscanf( Line->s, "%s", Case )){

      if( strEQ( Case, "Lims-parm" )){
	aP = (FitParm *) xmalloc( sizeof( FitParm ) );
	if( 4 == sscanf( Line->s, "%s %s %lf %lf", Case, aP->name, &aP->lo, &aP->hi )){
	  lPar[lParN++] = aP;
	  if( aP->lo > aP->hi ){
	    if( pRn->rank==0 ) 
	      printf( "ERROR lower limit >>%g<< is greater than upper limit >>%g<< in Line >>%s<<\n", 
		      aP->lo, aP->hi, Line->s );
	    exit( 1 );
	  }
	}
	else {
	  if( pRn->rank==0 ) fprintf( stdout, "\n\nERROR: Fit-lims line invalid \n>>%s<<\n", Line->s );
	  exit( 1 );
	}
      }
    }
  }
  fclose( fp );
  
  apply_lims( pRn, lParN, lPar );

}

/* --------------------------------------------------------------------------------
   over-ride lim values on fPar
   -------------------------------------------------------------------------------- */
void apply_lims( pRun *pRn, int fLimN, FitParm **fLim )
{
  int fi, li;

  for( fi=0; fi<pRn->fParN; ++fi ){
    for( li=0; li<fLimN; ++li ){
      if( strEQ( fLim[li]->name, pRn->fPar[fi]->name )){
	pRn->fPar[fi]->lo = fLim[li]->lo;
	pRn->fPar[fi]->hi = fLim[li]->hi;
	break;
      }
    }
  }
  for( li=0; li<fLimN; ++li )
    xfree( (char *) fLim[li] );
}

/* --------------------------------------------------------------------------------
   Add HOME if path does not start with '/'
   -------------------------------------------------------------------------------- */
void resolve_path( pRun *pRn, char *path, char *res_path )
{
  char buf[2056];

  strcpy( buf, path );
  if( path[0] != '/' ) 
    sprintf( buf, "%s/%s", pRn->HOME, path );
  strcpy( res_path, buf );
}

/* -------------------------------------------------------------------------------- */
void write_file_content( pRun *pRn, FILE *fp, char *fname )
{
  FILE *fpin_ptr;
  jString	*Line;

  if( NULL==(fpin_ptr=fopen( fname, "r" )) ){
    printf("write_file_content: Cannot open file >>%s<<\n", fname );
    exit( 1 );
  }
  Line = jString_new();
  while( EOF != jLine_read( fpin_ptr, Line ) )
    fprintf( fp, "%s\n", Line->s );
  fclose( fpin_ptr );
}

/* -------------------------------------------------------------------------------- */
void do_verbatim( pRun *pRn, FILE *fp )
{
  char *vb;
  int  vbsz, ivb;
  jString *Line;

  Line = jString_new();
  vbsz = 2048*2;
  vb = (char *) xmalloc( vbsz *sizeof(char));
  vb[0] = '\0';

  while( EOF != jLine_read( fp, Line ) 
	 && 0!= strncmp( "ENDVERBATIM", Line->s, strlen("ENDVERBATIM"))){
    while( strlen(Line->s)+strlen(vb) > vbsz ){
      vbsz *= 2;
      vb = xrealloc( vb, vbsz );
    }
    strcat( vb, Line->s );
    ivb = strlen(vb);
    vb[ivb] = '\n';
    vb[ivb+1] = '\0';
  }
  pRn->hoc_verbatim = vb;
}
