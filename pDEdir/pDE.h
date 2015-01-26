/* ========================================================================
   pDE: Parallel version of Storn and Price's Differential evolution 
   applied to NEURON modeling

   c2005 Jose Ambros-Ingerson jose@kiubo.net
   
   $Id: pDE.h,v 1.62 2008/12/06 00:13:00 jose Exp $

   ======================================================================== */

#ifndef _I_pDE
#define _I_pDE 1

#define ROUND(r) (int)( r+0.5 )

#define pDE_MV 1
#define pDE_mV 0

#define WORKTAG 1
#define DIETAG 2
#define DTAG 3

#define FPSZ 256
#define STR_SZ 1024
/* ------------------------------------------------------------------------ */
typedef struct CORR {
  double        b;	/* intercept */
  double        m;	/* slope */
  double        r;	/* correlation */
  double	SEb;	/* standard error */
  double	SEm;
  double	rs;	/* Spearman rank order correlation */
  double	Prst;	/* 2 sided significance of rs using t statistic */
  double	PrsD;	/* 2 sided significance of rs using D statistic */
} cOrr;

typedef struct STAT {
  double        mean;
  double	median;
  double        sd;
  double        cv;
  double        min;
  double        max;
  double	sdr;	/* robust equiv of sd; sdr = 1.4826 * MAD; median absolute deviation */
  double	cvr;	/* robust equiv of cv; sdr/median agrees with cv if normally distributed */
} sTat;

typedef struct FITPARM {
  char		name[STR_SZ];
  double	lo;
  double	hi;
  double	init;
  int		logT;		/* flag to indicate log transform */
  double	logT_add; 	/* add factor for log transform */
} FitParm;

typedef struct SUBSPARM {
  char*		subname;       /* Substitute name */
  int		n;
  char** 	name;	       /* Array of Parms that can be substituted by subname */
} SubsParm;

typedef struct FITCASE {
  char 		name[STR_SZ];
  char		template[STR_SZ];
  char		func[STR_SZ];
  char		scale[STR_SZ];
  char		hoc_var[STR_SZ];
  char		hoc_before[STR_SZ];
  char		hoc_after[STR_SZ];
  char		tgt_files[STR_SZ];
  char		tgt_before[STR_SZ];
  char		tgt_after[STR_SZ];

} FitCase;

typedef struct PHOST {
  char		hostname[STR_SZ];
  int		pid;
  int		nErr;
} pHost;

typedef struct SADATA {			/* Sensitivity analysis data */
  double	Pop_f;		/* nMax = pRn->NP * Pop_f */
  double	Best_Rad_Pcnt;	/* Pcnt of best as sA sphere radius */
  int		n;		/* members in Pop */
  int		nMax;
  double	**Pop;
  sTat		*sT;
  cOrr		**cO;
  int		*idx;		/* sort index */
  double	*sv;		/* sorted score values */
} sAdata;

typedef struct PBEST {			/* Population best data */
  int		n;		/* members in Pop Best */
  int		*b;		/* Pointers to best n in population */
} pBest;

typedef struct PRUN {
  int		idebug;
  int 		abort_on_eval_error;	/* 1=> Abort on any eval error. Useful for debugging */
  int		rank;
  int		pid;		/* process id */
  int		Nproc;
  char		*HOME;
  char		*PWD;
  pHost		*pHosts;	/* Allocated only in master */

  char		name[STR_SZ];
  int		seed;
  int		D;
  int		NpD;
  int		NP;		/* D*NpD */
  int		strategy;
  double	F;
  double	CR;
  char		hoc_main[STR_SZ];	
  char		*hoc_verbatim;		/* Holds verbatim hoc code from job_spec */
  char		var_lim_stgy[STR_SZ];		/* variable limit strategy */

  char		tmp_dir[STR_SZ];	/* for temporary files; ie .hoc */

  char		input_file[STR_SZ];
  char		log_name[STR_SZ];
  FILE		*log_fp;
  char		hoc_best[STR_SZ];
  int		nfeval;
  int		genmax;

  int		fCaseN;		/* Fit-case */
  FitCase	*fCase[FPSZ];
  int		fParN;		/* Fit-parm */
  FitParm	*fPar[FPSZ];
  int		sParN;		/* Set-parm */
  FitParm	*sPar[FPSZ];
  int		subParN;	/* Subs-parm */
  SubsParm	*subPar[FPSZ];
  char		fit_lims[STR_SZ];	/* fit limits override file */
  int		ParmOrder[FPSZ];	/* Parm order in spec file */
  int		ParmOrderN;

  int		gen_N;

  char		Pop_init[STR_SZ];	/* Initial Pop instructions */

  double	**Pop;
  int		Pop_D;			/* Pop array augmented Dimension */
  /* ----------------------------------------------------------------------
     Pop member

     0:D-1				genotype with D dimensions
     D:D+fCaseN-1	P_errD		Error detail per fCase
     D+fCaseN		P_errS		Error sum
     D+fCaseN+1		P_nfeval	nfeval
     D+fCaseN+2		P_etime		eTime
     D+fCaseN+3		P_ipop		ipop (for use in slave<->master comms)
     D+fCaseN+4		P_ESerrN	Error number returned by evaluateN (eval_slave)

     Pop_D = D+fCaseN+5
    ---------------------------------------------------------------------- */
  int		Pop_ibest;
  sTat		*Pop_sT;	/* First order stats for each pop member */
  cOrr		**Pop_cO;	/* Correlations & etc for each pop member */
  int		P_errD;
  int		P_errS;
  int		P_nfeval;
  int		P_etime;
  int		P_ipop;
  int		P_ESerrN;	/* Eval Slave Error No */
  double	*Pop_buf;	/* for master<->slave comm */

  int		nESerr;		/* number of eval slave errors */
  int		nWin;
  double	pWin;
  double	time_eavg1;	/* exponential time average of all evaluations */
  double	time_eavg2;
  double	*best_ever;
  double	*cbest_ever;

  sAdata	*sA;		/* Sensitivity Analysis data */
  pBest		*pB;		/* Population best data */

} pRun;


/* ---------- main.c ----------------------------------------------------- */
void master( pRun *pRn );
void alloc_master( pRun *pRn );
void free_master( pRun *pRn );
void evolve_member( pRun *pRn, int ipop );

/* ---------- pop.c ------------------------------------------------------ */
void do_Pop_init( pRun *pRn );
void do_Pop_Ngen( pRun *pRn, char *fname, int nGen );
char ** split_into_char_array( char *str, int *nAp );
void do_Pop_fp( pRun *pRn, FILE	*fp );
void Pop_buf_update_pBest( pRun *pRn );
void Pop_buf_update_sA( pRun *pRn );

void Pop_load_init( pRun *pRn );
void Pop_add_log( pRun *pRn, int rank );
void do_cOrr( int N, double *x, double *y, cOrr *cO );
void do_sTat( int N, double *p, sTat *sT );
void mean_sd( int N, double *p, double *mean, double *sd );
void do_sTat_Pop( pRun *pRn );
void printMem( pRun *pRn, FILE *fp, double *pop );
void printGen( pRun *pRn, FILE *fp, double **pop );
void log_Gen( pRun *pRn );
void var_lims( pRun *pRn, double *pop, int ipop );
void hoc_best( pRun *pRn );
void randoms( pRun *pRn, int *r, int n, int ix );
void assignd(int D, double *a, double *b );
void alloc_array1d( double **a, int sz );
void alloc_array2d( double ***a, int x, int y );
void xfree_array2d( double **a, int x );
void hoc_write_pop_buf( pRun *pRn, char *fname, double pop_buf[] );
void write_fit_var_list_hoc( FILE *fp, pRun *pRn );

/* ---------- eval_slave.c ----------------------------------------------- */
void eval_slave( pRun *pRn );
void evaluateN( pRun *pRn );
int  do_hoc_asg( char *fname, pRun *pRn, double val[] );
int  write_hoc_asg( FILE *fp, pRun *pRn, double val[] );
int  save_hoc_fit( char *fname, char *txt_res, pRun *pRn );
void write_eval_hoc( FILE *fp, pRun *pRn );

/* ---------- load_job_spec.c ----------------------------------------------- */
void load_job_spec( int argc, char *argv[], pRun *pRn );
void log_job( pRun *pRn );
void print_Headers( pRun *pRn, FILE *fp );
void get_ids( pRun *pRn );
void get_hostname( char *res );
void load_fit_lims( pRun *pRn );
void apply_lims( pRun *pRn, int fLimN, FitParm **fLim );
void resolve_path( pRun *pRn, char *path, char *res_path );
void write_file_content( pRun *pRn, FILE *fp, char *fname );
void do_verbatim( pRun *pRn, FILE *fp );

#endif /* _I_pDE */
