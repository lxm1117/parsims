/* Created by Language version: 6.2.0 */
/* NOT VECTORIZED */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scoplib.h"
#undef PI
 static void _difusfunc();
 
#include "md1redef.h"
#include "section.h"
#include "md2redef.h"

#if METHOD3
extern int _method3;
#endif

#undef exp
#define exp hoc_Exp
extern double hoc_Exp();
 
#define _threadargscomma_ /**/
#define _threadargs_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define cai0 _p[0]
#define ica_pmp _p[1]
#define ca (_p + 2)
#define CaBuffer (_p + 6)
#define Buffer (_p + 10)
#define pump _p[14]
#define pumpca _p[15]
#define ica _p[16]
#define cai _p[17]
#define cao _p[18]
#define ica_pmp_last _p[19]
#define parea _p[20]
#define Kd _p[21]
#define B0 _p[22]
#define Dca (_p + 23)
#define DCaBuffer (_p + 27)
#define DBuffer (_p + 31)
#define Dpump _p[35]
#define Dpumpca _p[36]
#define _g _p[37]
#define _ion_cao	*_ppvar[0]._pval
#define _ion_cai	*_ppvar[1]._pval
#define _ion_ica	*_ppvar[2]._pval
#define _ion_dicadv	*_ppvar[3]._pval
#define _style_ca	*((int*)_ppvar[4]._pvoid)
#define diam	*_ppvar[5]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 static int hoc_nrnpointerindex =  -1;
 /* external NEURON variables */
 /* declaration of user functions */
 static int _hoc_factors();
 static int _mechtype;
extern int nrn_get_mechtype();
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range();
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 ret(1.);
}
 /* connect user functions to hoc names */
 static IntFunc hoc_intfunc[] = {
 "setdata_cdp", _hoc_setdata,
 "factors_cdp", _hoc_factors,
 0, 0
};
 /* declare global and static user variables */
#define DCa DCa_cdp
 double DCa = 0.6;
#define TotalPump TotalPump_cdp
 double TotalPump = 1e-11;
#define TotalBuffer TotalBuffer_cdp
 double TotalBuffer = 0.003;
#define k4 k4_cdp
 double k4 = 0.005;
#define k3 k3_cdp
 double k3 = 1;
#define k2 k2_cdp
 double k2 = 0.005;
#define k1 k1_cdp
 double k1 = 1;
#define k2buf k2buf_cdp
 double k2buf = 0.1;
#define k1buf k1buf_cdp
 double k1buf = 100;
#define vrat vrat_cdp
 double vrat[4];
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "DCa_cdp", "um2/ms",
 "k1buf_cdp", "/mM-ms",
 "k2buf_cdp", "/ms",
 "TotalBuffer_cdp", "mM",
 "k1_cdp", "/mM-ms",
 "k2_cdp", "/ms",
 "k3_cdp", "/ms",
 "k4_cdp", "/mM-ms",
 "TotalPump_cdp", "mol/cm2",
 "vrat_cdp", "1",
 "cai0_cdp", "mM",
 "ca_cdp", "mM",
 "CaBuffer_cdp", "mM",
 "Buffer_cdp", "mM",
 "pump_cdp", "mol/cm2",
 "pumpca_cdp", "mol/cm2",
 "ica_pmp_cdp", "mA/cm2",
 0,0
};
 static double Buffer0 = 0;
 static double CaBuffer0 = 0;
 static double ca0 = 0;
 static double delta_t = 0.01;
 static double pumpca0 = 0;
 static double pump0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "DCa_cdp", &DCa_cdp,
 "k1buf_cdp", &k1buf_cdp,
 "k2buf_cdp", &k2buf_cdp,
 "TotalBuffer_cdp", &TotalBuffer_cdp,
 "k1_cdp", &k1_cdp,
 "k2_cdp", &k2_cdp,
 "k3_cdp", &k3_cdp,
 "k4_cdp", &k4_cdp,
 "TotalPump_cdp", &TotalPump_cdp,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 "vrat_cdp", vrat_cdp, 4,
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(), nrn_init(), nrn_state();
 static void nrn_cur(), nrn_jacob();
 
static int _ode_count(), _ode_map(), _ode_spec(), _ode_matsol();
 
#define _cvode_ieq _ppvar[6]._i
 static _ode_synonym();
 /* connect range variables in _p that hoc is supposed to know about */
 static char *_mechanism[] = {
 "6.2.0",
"cdp",
 "cai0_cdp",
 0,
 "ica_pmp_cdp",
 0,
 "ca_cdp[4]",
 "CaBuffer_cdp[4]",
 "Buffer_cdp[4]",
 "pump_cdp",
 "pumpca_cdp",
 0,
 0};
 static Symbol* _morphology_sym;
 static Symbol* _ca_sym;
 static int _type_ica;
 
static void nrn_alloc(_prop)
	Prop *_prop;
{
	Prop *prop_ion, *need_memb();
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 38, _prop);
 	/*initialize range parameters*/
 	cai0 = 5e-05;
 	_prop->param = _p;
 	_prop->param_size = 38;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 7, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_morphology_sym);
 	_ppvar[5]._pval = &prop_ion->param[0]; /* diam */
 prop_ion = need_memb(_ca_sym);
  _type_ica = prop_ion->_type;
 nrn_check_conc_write(_prop, prop_ion, 1);
 nrn_promote(prop_ion, 3, 0);
 	_ppvar[0]._pval = &prop_ion->param[2]; /* cao */
 	_ppvar[1]._pval = &prop_ion->param[1]; /* cai */
 	_ppvar[2]._pval = &prop_ion->param[3]; /* ica */
 	_ppvar[3]._pval = &prop_ion->param[4]; /* _ion_dicadv */
 	_ppvar[4]._pvoid = (void*)(&(prop_ion->dparam[0]._i)); /* iontype for ca */
 
}
 static _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 "ca_cdp", 1e-07,
 "CaBuffer_cdp", 1e-05,
 "Buffer_cdp", 1e-05,
 "pump_cdp", 1e-15,
 "pumpca_cdp", 1e-15,
 0,0
};
 static void _update_ion_pointer(Datum*);
 _cdp_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("ca", -10000.);
 	_morphology_sym = hoc_lookup("morphology");
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
  hoc_register_dparam_size(_mechtype, 7);
 	nrn_writes_conc(_mechtype, 0);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_synonym(_mechtype, _ode_synonym);
 	hoc_register_ldifus1(_difusfunc);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 cdp /home/ximi/Documents/from_axon/ca1n1-mod/x86_64/cdp.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 9.64853;
 static double PI = 3.14159;
 static double volo = 1e+10;
 static double _zfactors_done ;
 static double _zfrat [ 4 ] ;
 static double _zdsq , _zdsqvol ;
static int _reset;
static char *modelname = "Calcium ion accumulation with longitudinal and radial diffusion buffering and pumping";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static _modl_cleanup(){ _match_recurse=1;}
static factors();
 extern double *_getelm();
 
#define _MATELM1(_row,_col)	*(_getelm(_row + 1, _col + 1))
 
#define _RHS1(_arg) _coef1[_arg + 1]
 static double *_coef1;
 
#define _linmat1  0
 static void* _sparseobj1;
 static void* _cvsparseobj1;
 
static int _ode_spec1(), _ode_matsol1();
 static int _slist1[14], _dlist1[14]; static double *_temp1;
 static int state();
 
static int  factors (  )  {
   double _lr , _ldr2 ;
 _lr = 1.0 / 2.0 ;
   _ldr2 = _lr / ( 4.0 - 1.0 ) / 2.0 ;
   vrat [ 0 ] = 0.0 ;
   _zfrat [ 0 ] = 2.0 * _lr ;
   {int  _li ;for ( _li = 0 ; _li <= 4 - 2 ; _li ++ ) {
     vrat [ _li ] = vrat [ _li ] + PI * ( _lr - _ldr2 / 2.0 ) * 2.0 * _ldr2 ;
     _lr = _lr - _ldr2 ;
     _zfrat [ _li + 1 ] = 2.0 * PI * _lr / ( 2.0 * _ldr2 ) ;
     _lr = _lr - _ldr2 ;
     vrat [ _li + 1 ] = PI * ( _lr + _ldr2 / 2.0 ) * 2.0 * _ldr2 ;
     } }
    return 0; }
 
static int _hoc_factors() {
  double _r;
   _r = 1.;
 factors (  ) ;
 ret(_r);
}
 
static int state ()
 {_reset=0;
 {
   double b_flux, f_flux, _term; int _i;
 {int _i; double _dt1 = 1.0/dt;
for(_i=1;_i<14;_i++){
  	_RHS1(_i) = -_dt1*(_p[_slist1[_i]] - _p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
}  
_RHS1(13) *= ( ( 1e10 ) * parea) ;
_MATELM1(13, 13) *= ( ( 1e10 ) * parea);  
for (_i=0; _i < 4; _i++) {
  	_RHS1(_i + 1) *= ( diam * diam * vrat [ ((int) _i ) ]) ;
_MATELM1(_i + 1, _i + 1) *= ( diam * diam * vrat [ ((int) _i ) ]);  } 
for (_i=0; _i < 4; _i++) {
  	_RHS1(_i + 5) *= ( diam * diam * vrat [ ((int) _i ) ]) ;
_MATELM1(_i + 5, _i + 5) *= ( diam * diam * vrat [ ((int) _i ) ]);  } 
for (_i=0; _i < 4; _i++) {
  	_RHS1(_i + 9) *= ( diam * diam * vrat [ ((int) _i ) ]) ;
_MATELM1(_i + 9, _i + 9) *= ( diam * diam * vrat [ ((int) _i ) ]);  } }
 /* COMPARTMENT _li , diam * diam * vrat [ ((int) _i ) ] {
     ca CaBuffer Buffer }
   */
 /* COMPARTMENT ( 1e10 ) * parea {
     pump pumpca }
   */
 /* COMPARTMENT volo {
     }
   */
 /* LONGITUDINAL_DIFFUSION _li , DCa * diam * diam * vrat [ ((int) _i ) ] {
     ca }
   */
 /* ~ ca [ 0 ] + pump <-> pumpca ( k1 * parea * ( 1e10 ) , k2 * parea * ( 1e10 ) )*/
 f_flux =  k1 * parea * ( 1e10 ) * pump * ca [ 0] ;
 b_flux =  k2 * parea * ( 1e10 ) * pumpca ;
 _RHS1( 13) -= (f_flux - b_flux);
 _RHS1( 9 +  0) -= (f_flux - b_flux);
 
 _term =  k1 * parea * ( 1e10 ) * ca [ 0] ;
 _MATELM1( 13 ,13)  += _term;
 _MATELM1( 9 +  0 ,13)  += _term;
 _term =  k1 * parea * ( 1e10 ) * pump ;
 _MATELM1( 13 ,9 +  0)  += _term;
 _MATELM1( 9 +  0 ,9 +  0)  += _term;
 _term =  k2 * parea * ( 1e10 ) ;
 _MATELM1( 13 ,0)  -= _term;
 _MATELM1( 9 +  0 ,0)  -= _term;
 /*REACTION*/
  /* ~ pumpca <-> pump + cao ( k3 * parea * ( 1e10 ) , k4 * parea * ( 1e10 ) )*/
 f_flux =  k3 * parea * ( 1e10 ) * pumpca ;
 b_flux =  k4 * parea * ( 1e10 ) * cao * pump ;
 _RHS1( 13) += (f_flux - b_flux);
 
 _term =  k3 * parea * ( 1e10 ) ;
 _MATELM1( 13 ,0)  -= _term;
 _term =  k4 * parea * ( 1e10 ) * cao ;
 _MATELM1( 13 ,13)  += _term;
 /*REACTION*/
   /* pump + pumpca = TotalPump * parea * ( 1e10 ) */
 _RHS1(0) =  TotalPump * parea * ( 1e10 );
 _MATELM1(0, 0) = 1 * ( ( 1e10 ) * parea);
 _RHS1(0) -= pumpca * ( ( 1e10 ) * parea) ;
 _MATELM1(0, 13) = 1 * ( ( 1e10 ) * parea);
 _RHS1(0) -= pump * ( ( 1e10 ) * parea) ;
 /*CONSERVATION*/
 ica_pmp = 2.0 * FARADAY * ( f_flux - b_flux ) / parea ;
   /* ~ ca [ 0 ] < < ( - ( ica - ica_pmp_last ) * PI * diam / ( 2.0 * FARADAY ) )*/
 f_flux = b_flux = 0.;
 _RHS1( 9 +  0) += (b_flux =   ( - ( ica - ica_pmp_last ) * PI * diam / ( 2.0 * FARADAY ) ) );
 /*FLUX*/
  {int  _li ;for ( _li = 0 ; _li <= 4 - 2 ; _li ++ ) {
     /* ~ ca [ _li ] <-> ca [ _li + 1 ] ( DCa * _zfrat [ _li + 1 ] , DCa * _zfrat [ _li + 1 ] )*/
 f_flux =  DCa * _zfrat [ _li + 1 ] * ca [ _li] ;
 b_flux =  DCa * _zfrat [ _li + 1 ] * ca [ _li + 1] ;
 _RHS1( 9 +  _li) -= (f_flux - b_flux);
 _RHS1( 9 +  _li + 1) += (f_flux - b_flux);
 
 _term =  DCa * _zfrat [ _li + 1 ] ;
 _MATELM1( 9 +  _li ,9 +  _li)  += _term;
 _MATELM1( 9 +  _li + 1 ,9 +  _li)  -= _term;
 _term =  DCa * _zfrat [ _li + 1 ] ;
 _MATELM1( 9 +  _li ,9 +  _li + 1)  -= _term;
 _MATELM1( 9 +  _li + 1 ,9 +  _li + 1)  += _term;
 /*REACTION*/
  } }
   _zdsq = diam * diam ;
   {int  _li ;for ( _li = 0 ; _li <= 4 - 1 ; _li ++ ) {
     _zdsqvol = _zdsq * vrat [ _li ] ;
     /* ~ ca [ _li ] + Buffer [ _li ] <-> CaBuffer [ _li ] ( k1buf * _zdsqvol , k2buf * _zdsqvol )*/
 f_flux =  k1buf * _zdsqvol * Buffer [ _li] * ca [ _li] ;
 b_flux =  k2buf * _zdsqvol * CaBuffer [ _li] ;
 _RHS1( 1 +  _li) -= (f_flux - b_flux);
 _RHS1( 9 +  _li) -= (f_flux - b_flux);
 _RHS1( 5 +  _li) += (f_flux - b_flux);
 
 _term =  k1buf * _zdsqvol * ca [ _li] ;
 _MATELM1( 1 +  _li ,1 +  _li)  += _term;
 _MATELM1( 9 +  _li ,1 +  _li)  += _term;
 _MATELM1( 5 +  _li ,1 +  _li)  -= _term;
 _term =  k1buf * _zdsqvol * Buffer [ _li] ;
 _MATELM1( 1 +  _li ,9 +  _li)  += _term;
 _MATELM1( 9 +  _li ,9 +  _li)  += _term;
 _MATELM1( 5 +  _li ,9 +  _li)  -= _term;
 _term =  k2buf * _zdsqvol ;
 _MATELM1( 1 +  _li ,5 +  _li)  -= _term;
 _MATELM1( 9 +  _li ,5 +  _li)  -= _term;
 _MATELM1( 5 +  _li ,5 +  _li)  += _term;
 /*REACTION*/
  } }
   cai = ca [ 0 ] ;
     } return _reset;
 }
 
/*CVODE ode begin*/
 static int _ode_spec1() {_reset=0;{
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<14;_i++) _p[_dlist1[_i]] = 0.0;}
 /* COMPARTMENT _li , diam * diam * vrat [ ((int) _i ) ] {
   ca CaBuffer Buffer }
 */
 /* COMPARTMENT ( 1e10 ) * parea {
   pump pumpca }
 */
 /* COMPARTMENT volo {
   }
 */
 /* LONGITUDINAL_DIFFUSION _li , DCa * diam * diam * vrat [ ((int) _i ) ] {
   ca }
 */
 /* ~ ca [ 0 ] + pump <-> pumpca ( k1 * parea * ( 1e10 ) , k2 * parea * ( 1e10 ) )*/
 f_flux =  k1 * parea * ( 1e10 ) * pump * ca [ 0] ;
 b_flux =  k2 * parea * ( 1e10 ) * pumpca ;
 Dpump -= (f_flux - b_flux);
 Dca [ 0] -= (f_flux - b_flux);
 Dpumpca += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ pumpca <-> pump + cao ( k3 * parea * ( 1e10 ) , k4 * parea * ( 1e10 ) )*/
 f_flux =  k3 * parea * ( 1e10 ) * pumpca ;
 b_flux =  k4 * parea * ( 1e10 ) * cao * pump ;
 Dpumpca -= (f_flux - b_flux);
 Dpump += (f_flux - b_flux);
 
 /*REACTION*/
   /* pump + pumpca = TotalPump * parea * ( 1e10 ) */
 /*CONSERVATION*/
 ica_pmp = 2.0 * FARADAY * ( f_flux - b_flux ) / parea ;
 /* ~ ca [ 0 ] < < ( - ( ica - ica_pmp_last ) * PI * diam / ( 2.0 * FARADAY ) )*/
 f_flux = b_flux = 0.;
 Dca [ 0] += (b_flux =   ( - ( ica - ica_pmp_last ) * PI * diam / ( 2.0 * FARADAY ) ) );
 /*FLUX*/
  {int  _li ;for ( _li = 0 ; _li <= 4 - 2 ; _li ++ ) {
   /* ~ ca [ _li ] <-> ca [ _li + 1 ] ( DCa * _zfrat [ _li + 1 ] , DCa * _zfrat [ _li + 1 ] )*/
 f_flux =  DCa * _zfrat [ _li + 1 ] * ca [ _li] ;
 b_flux =  DCa * _zfrat [ _li + 1 ] * ca [ _li + 1] ;
 Dca [ _li] -= (f_flux - b_flux);
 Dca [ _li + 1] += (f_flux - b_flux);
 
 /*REACTION*/
  } }
 _zdsq = diam * diam ;
 {int  _li ;for ( _li = 0 ; _li <= 4 - 1 ; _li ++ ) {
   _zdsqvol = _zdsq * vrat [ _li ] ;
   /* ~ ca [ _li ] + Buffer [ _li ] <-> CaBuffer [ _li ] ( k1buf * _zdsqvol , k2buf * _zdsqvol )*/
 f_flux =  k1buf * _zdsqvol * Buffer [ _li] * ca [ _li] ;
 b_flux =  k2buf * _zdsqvol * CaBuffer [ _li] ;
 DBuffer [ _li] -= (f_flux - b_flux);
 Dca [ _li] -= (f_flux - b_flux);
 DCaBuffer [ _li] += (f_flux - b_flux);
 
 /*REACTION*/
  } }
 cai = ca [ 0 ] ;
 _p[_dlist1[0]] /= ( ( 1e10 ) * parea);
 for (_i=0; _i < 4; _i++) { _p[_dlist1[_i + 1]] /= ( diam * diam * vrat [ ((int) _i ) ]);}
 for (_i=0; _i < 4; _i++) { _p[_dlist1[_i + 5]] /= ( diam * diam * vrat [ ((int) _i ) ]);}
 for (_i=0; _i < 4; _i++) { _p[_dlist1[_i + 9]] /= ( diam * diam * vrat [ ((int) _i ) ]);}
 _p[_dlist1[13]] /= ( ( 1e10 ) * parea);
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol1() {_reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<14;_i++){
  	_RHS1(_i) = _dt1*(_p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
}  
_RHS1(0) *= ( ( 1e10 ) * parea) ;
_MATELM1(0, 0) *= ( ( 1e10 ) * parea); 
_RHS1(13) *= ( ( 1e10 ) * parea) ;
_MATELM1(13, 13) *= ( ( 1e10 ) * parea);  
for (_i=0; _i < 4; _i++) {
  	_RHS1(_i + 1) *= ( diam * diam * vrat [ ((int) _i ) ]) ;
_MATELM1(_i + 1, _i + 1) *= ( diam * diam * vrat [ ((int) _i ) ]);  } 
for (_i=0; _i < 4; _i++) {
  	_RHS1(_i + 5) *= ( diam * diam * vrat [ ((int) _i ) ]) ;
_MATELM1(_i + 5, _i + 5) *= ( diam * diam * vrat [ ((int) _i ) ]);  } 
for (_i=0; _i < 4; _i++) {
  	_RHS1(_i + 9) *= ( diam * diam * vrat [ ((int) _i ) ]) ;
_MATELM1(_i + 9, _i + 9) *= ( diam * diam * vrat [ ((int) _i ) ]);  } }
 /* COMPARTMENT _li , diam * diam * vrat [ ((int) _i ) ] {
 ca CaBuffer Buffer }
 */
 /* COMPARTMENT ( 1e10 ) * parea {
 pump pumpca }
 */
 /* COMPARTMENT volo {
 }
 */
 /* LONGITUDINAL_DIFFUSION _li , DCa * diam * diam * vrat [ ((int) _i ) ] {
 ca }
 */
 /* ~ ca [ 0 ] + pump <-> pumpca ( k1 * parea * ( 1e10 ) , k2 * parea * ( 1e10 ) )*/
 _term =  k1 * parea * ( 1e10 ) * ca [ 0] ;
 _MATELM1( 13 ,13)  += _term;
 _MATELM1( 9 +  0 ,13)  += _term;
 _MATELM1( 0 ,13)  -= _term;
 _term =  k1 * parea * ( 1e10 ) * pump ;
 _MATELM1( 13 ,9 +  0)  += _term;
 _MATELM1( 9 +  0 ,9 +  0)  += _term;
 _MATELM1( 0 ,9 +  0)  -= _term;
 _term =  k2 * parea * ( 1e10 ) ;
 _MATELM1( 13 ,0)  -= _term;
 _MATELM1( 9 +  0 ,0)  -= _term;
 _MATELM1( 0 ,0)  += _term;
 /*REACTION*/
  /* ~ pumpca <-> pump + cao ( k3 * parea * ( 1e10 ) , k4 * parea * ( 1e10 ) )*/
 _term =  k3 * parea * ( 1e10 ) ;
 _MATELM1( 0 ,0)  += _term;
 _MATELM1( 13 ,0)  -= _term;
 _term =  k4 * parea * ( 1e10 ) * cao ;
 _MATELM1( 0 ,13)  -= _term;
 _MATELM1( 13 ,13)  += _term;
 /* ~ ca [ 0 ] < < ( - ( ica - ica_pmp_last ) * PI * diam / ( 2.0 * FARADAY ) )*/
 /*FLUX*/
  {int  _li ;for ( _li = 0 ; _li <= 4 - 2 ; _li ++ ) {
 /* ~ ca [ _li ] <-> ca [ _li + 1 ] ( DCa * _zfrat [ _li + 1 ] , DCa * _zfrat [ _li + 1 ] )*/
 _term =  DCa * _zfrat [ _li + 1 ] ;
 _MATELM1( 9 +  _li ,9 +  _li)  += _term;
 _MATELM1( 9 +  _li + 1 ,9 +  _li)  -= _term;
 _term =  DCa * _zfrat [ _li + 1 ] ;
 _MATELM1( 9 +  _li ,9 +  _li + 1)  -= _term;
 _MATELM1( 9 +  _li + 1 ,9 +  _li + 1)  += _term;
 /*REACTION*/
  } }
 _zdsq = diam * diam ;
 {int  _li ;for ( _li = 0 ; _li <= 4 - 1 ; _li ++ ) {
 _zdsqvol = _zdsq * vrat [ _li ] ;
 /* ~ ca [ _li ] + Buffer [ _li ] <-> CaBuffer [ _li ] ( k1buf * _zdsqvol , k2buf * _zdsqvol )*/
 _term =  k1buf * _zdsqvol * ca [ _li] ;
 _MATELM1( 1 +  _li ,1 +  _li)  += _term;
 _MATELM1( 9 +  _li ,1 +  _li)  += _term;
 _MATELM1( 5 +  _li ,1 +  _li)  -= _term;
 _term =  k1buf * _zdsqvol * Buffer [ _li] ;
 _MATELM1( 1 +  _li ,9 +  _li)  += _term;
 _MATELM1( 9 +  _li ,9 +  _li)  += _term;
 _MATELM1( 5 +  _li ,9 +  _li)  -= _term;
 _term =  k2buf * _zdsqvol ;
 _MATELM1( 1 +  _li ,5 +  _li)  -= _term;
 _MATELM1( 9 +  _li ,5 +  _li)  -= _term;
 _MATELM1( 5 +  _li ,5 +  _li)  += _term;
 /*REACTION*/
  } }
 cai = ca [ 0 ] ;
   } return _reset;
 }
 
/*CVODE end*/
 
static int _ode_count(_type) int _type;{ return 14;}
 
static int _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  cao = _ion_cao;
  cai = _ion_cai;
  ica = _ion_ica;
  cai = _ion_cai;
     _ode_spec1 ();
  _ion_cai = cai;
  }}
 
static int _ode_map(_ieq, _pv, _pvdot, _pp, _ppd, _atol, _type) int _ieq, _type; double** _pv, **_pvdot, *_pp, *_atol; Datum* _ppd; { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 14; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 static _ode_synonym(_cnt, _pp, _ppd) int _cnt; double** _pp; Datum** _ppd; { 
 	int _i; 
	for (_i=0; _i < _cnt; ++_i) {_p = _pp[_i]; _ppvar = _ppd[_i];
 _ion_cai =  ca [ 0 ] ;
 }}
 
static int _ode_matsol(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  cao = _ion_cao;
  cai = _ion_cai;
  ica = _ion_ica;
  cai = _ion_cai;
 _cvode_sparse(&_cvsparseobj1, 14, _dlist1, _p, _ode_matsol1, &_coef1);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_ca_sym, _ppvar, 0, 2);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 1, 1);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 2, 3);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 3, 4);
 }
 static void* _difspace1;
extern double nrn_nernst_coef();
static double _difcoef1(int _i, double* _p, Datum* _ppvar, double* _pdvol, double* _pdfcdc, Datum* _thread, _NrnThread* _nt) {
   *_pdvol =  diam * diam * vrat [ ((int) _i ) ] ;
 if (_i ==  0) {
  *_pdfcdc = nrn_nernst_coef(_type_ica)*( ( - ( _ion_dicadv  - ica_pmp_last ) * PI * diam / ( 2.0 * FARADAY ) ));
 }else{ *_pdfcdc=0.;}
   return DCa * diam * diam * vrat [ ((int) _i ) ] ;
}
 static void _difusfunc(_f, _nt) void(*_f)(); _NrnThread* _nt; {int _i;
  for (_i=0; _i < 4; ++_i) _f(_mechtype, _difcoef1, &_difspace1, _i,  2, 23 , _nt);
 }

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
 for (_i=0; _i<4; _i++) Buffer[_i] = Buffer0;
 for (_i=0; _i<4; _i++) CaBuffer[_i] = CaBuffer0;
 for (_i=0; _i<4; _i++) ca[_i] = ca0;
  pumpca = pumpca0;
  pump = pump0;
 {
   if ( _zfactors_done  == 0.0 ) {
     _zfactors_done = 1.0 ;
     factors ( _threadargs_ ) ;
     }
   cai = cai0 ;
   Kd = k1buf / k2buf ;
   B0 = TotalBuffer / ( 1.0 + Kd * cai ) ;
   {int  _li ;for ( _li = 0 ; _li <= 4 - 1 ; _li ++ ) {
     ca [ _li ] = cai ;
     Buffer [ _li ] = B0 ;
     CaBuffer [ _li ] = TotalBuffer - B0 ;
     } }
   parea = PI * diam ;
   pump = TotalPump / ( 1.0 + ( cai * k1 / k2 ) ) ;
   pumpca = TotalPump - pump ;
   }
  _sav_indep = t; t = _save;

}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
  cao = _ion_cao;
  cai = _ion_cai;
  ica = _ion_ica;
  cai = _ion_cai;
 initmodel();
  _ion_cai = cai;
   nrn_wrote_conc(_ca_sym, (&(_ion_cai)) - 1, _style_ca);
}}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   ica_pmp_last = ica_pmp ;
   ica = ica_pmp ;
   }
 _current += ica;

} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
  cao = _ion_cao;
  cai = _ion_cai;
  ica = _ion_ica;
  cai = _ion_cai;
if (_nt->_vcv) { _ode_spec1(); }
 _g = _nrn_current(_v + .001);
 	{ double _dica;
  _dica = ica;
 _rhs = _nrn_current(_v);
  _ion_dicadv += (_dica - ica)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_cai = cai;
  _ion_ica += ica ;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}}

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type){
 double _break, _save;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 _break = t + .5*dt; _save = t;
 v=_v;
{
  cao = _ion_cao;
  cai = _ion_cai;
  ica = _ion_ica;
  cai = _ion_cai;
 { {
 for (; t < _break; t += dt) {
 error = sparse(&_sparseobj1, 14, _slist1, _dlist1, _p, &t, dt, state,&_coef1, _linmat1);
 if(error){fprintf(stderr,"at line 96 in file cdp.mod:\n	SOLVE state METHOD sparse\n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
 }  _ion_cai = cai;
 }}

}

static terminal(){}

static _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(pumpca) - _p;  _dlist1[0] = &(Dpumpca) - _p;
 for(_i=0;_i<4;_i++){_slist1[1+_i] = (Buffer + _i) - _p;  _dlist1[1+_i] = (DBuffer + _i) - _p;}
 for(_i=0;_i<4;_i++){_slist1[5+_i] = (CaBuffer + _i) - _p;  _dlist1[5+_i] = (DCaBuffer + _i) - _p;}
 for(_i=0;_i<4;_i++){_slist1[9+_i] = (ca + _i) - _p;  _dlist1[9+_i] = (Dca + _i) - _p;}
 _slist1[13] = &(pump) - _p;  _dlist1[13] = &(Dpump) - _p;
_first = 0;
}
