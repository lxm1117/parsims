/* Created by Language version: 6.2.0 */
/* VECTORIZED */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scoplib.h"
#undef PI
 
#include "md1redef.h"
#include "section.h"
#include "md2redef.h"

#if METHOD3
extern int _method3;
#endif

#undef exp
#define exp hoc_Exp
extern double hoc_Exp();
 
#define _threadargscomma_ _p, _ppvar, _thread, _nt,
#define _threadargs_ _p, _ppvar, _thread, _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 /* Thread safe. No static _p or _ppvar. */
 
#define t _nt->_t
#define dt _nt->_dt
#define gtcabar _p[0]
#define gncabar _p[1]
#define glcabar _p[2]
#define e_ca _p[3]
#define gtca _p[4]
#define gnca _p[5]
#define glca _p[6]
#define ca_i _p[7]
#define a _p[8]
#define b _p[9]
#define c _p[10]
#define d _p[11]
#define e _p[12]
#define ica _p[13]
#define i _p[14]
#define Dca_i _p[15]
#define Da _p[16]
#define Db _p[17]
#define Dc _p[18]
#define Dd _p[19]
#define De _p[20]
#define v _p[21]
#define _g _p[22]
#define _ion_ica	*_ppvar[0]._pval
#define _ion_dicadv	*_ppvar[1]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 static int hoc_nrnpointerindex =  -1;
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
 /* external NEURON variables */
 /* declaration of user functions */
 static int _hoc_alphae();
 static int _hoc_alphad();
 static int _hoc_alphac();
 static int _hoc_alphab();
 static int _hoc_alphaa();
 static int _hoc_betae();
 static int _hoc_betad();
 static int _hoc_betac();
 static int _hoc_betab();
 static int _hoc_betaa();
 static int _hoc_exponential();
 static int _hoc_f();
 static int _hoc_logistic();
 static int _mechtype;
extern int nrn_get_mechtype();
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range();
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 ret(1.);
}
 /* connect user functions to hoc names */
 static IntFunc hoc_intfunc[] = {
 "setdata_Ca", _hoc_setdata,
 "alphae_Ca", _hoc_alphae,
 "alphad_Ca", _hoc_alphad,
 "alphac_Ca", _hoc_alphac,
 "alphab_Ca", _hoc_alphab,
 "alphaa_Ca", _hoc_alphaa,
 "betae_Ca", _hoc_betae,
 "betad_Ca", _hoc_betad,
 "betac_Ca", _hoc_betac,
 "betab_Ca", _hoc_betab,
 "betaa_Ca", _hoc_betaa,
 "exponential_Ca", _hoc_exponential,
 "f_Ca", _hoc_f,
 "logistic_Ca", _hoc_logistic,
 0, 0
};
#define alphae alphae_Ca
#define alphad alphad_Ca
#define alphac alphac_Ca
#define alphab alphab_Ca
#define alphaa alphaa_Ca
#define betae betae_Ca
#define betad betad_Ca
#define betac betac_Ca
#define betab betab_Ca
#define betaa betaa_Ca
#define exponential exponential_Ca
#define f f_Ca
#define logistic logistic_Ca
 extern double alphae();
 extern double alphad();
 extern double alphac();
 extern double alphab();
 extern double alphaa();
 extern double betae();
 extern double betad();
 extern double betac();
 extern double betab();
 extern double betaa();
 extern double exponential();
 extern double f();
 extern double logistic();
 /* declare global and static user variables */
#define cao cao_Ca
 double cao = 2;
#define ca0 ca0_Ca
 double ca0 = 7e-05;
#define tau tau_Ca
 double tau = 9;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "ca0_Ca", "mM",
 "cao_Ca", "mM",
 "tau_Ca", "ms",
 "gtcabar_Ca", "S/cm2",
 "gncabar_Ca", "S/cm2",
 "glcabar_Ca", "S/cm2",
 "ca_i_Ca", "mM",
 "e_ca_Ca", "mV",
 "gtca_Ca", "S/cm2",
 "gnca_Ca", "S/cm2",
 "glca_Ca", "S/cm2",
 0,0
};
 static double a0 = 0;
 static double b0 = 0;
 static double c0 = 0;
 static double ca_i0 = 0;
 static double delta_t = 0.01;
 static double d0 = 0;
 static double e0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "ca0_Ca", &ca0_Ca,
 "cao_Ca", &cao_Ca,
 "tau_Ca", &tau_Ca,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(), nrn_init(), nrn_state();
 static void nrn_cur(), nrn_jacob();
 
static int _ode_count(), _ode_map(), _ode_spec(), _ode_matsol();
 
#define _cvode_ieq _ppvar[2]._i
 /* connect range variables in _p that hoc is supposed to know about */
 static char *_mechanism[] = {
 "6.2.0",
"Ca",
 "gtcabar_Ca",
 "gncabar_Ca",
 "glcabar_Ca",
 0,
 "e_ca_Ca",
 "gtca_Ca",
 "gnca_Ca",
 "glca_Ca",
 0,
 "ca_i_Ca",
 "a_Ca",
 "b_Ca",
 "c_Ca",
 "d_Ca",
 "e_Ca",
 0,
 0};
 static Symbol* _ca_sym;
 
static void nrn_alloc(_prop)
	Prop *_prop;
{
	Prop *prop_ion, *need_memb();
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 23, _prop);
 	/*initialize range parameters*/
 	gtcabar = 0.01;
 	gncabar = 0.01;
 	glcabar = 0.01;
 	_prop->param = _p;
 	_prop->param_size = 23;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_ca_sym);
 	_ppvar[0]._pval = &prop_ion->param[3]; /* ica */
 	_ppvar[1]._pval = &prop_ion->param[4]; /* _ion_dicadv */
 
}
 static _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _update_ion_pointer(Datum*);
 _Ca_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("ca", -10000.);
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
  hoc_register_dparam_size(_mechtype, 3);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Ca /home/ximi/Documents/from_axon/ca1n1-mod/x86_64/Ca.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double B = .26;
 static double F = 96485.3;
 static double R = 8.31342;
 static double TEMP = 25.0;
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static _modl_cleanup(){ _match_recurse=1;}
 
static int _ode_spec1(), _ode_matsol1();
 static int _slist1[6], _dlist1[6];
 static int state();
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset = 0; {
   Dca_i = - B * ica - ( ca_i - ca0 ) / tau ;
   Da = alphaa ( _threadargscomma_ v ) * ( 1.0 - a ) - betaa ( _threadargscomma_ v ) * a ;
   Db = alphab ( _threadargscomma_ v ) * ( 1.0 - b ) - betab ( _threadargscomma_ v ) * b ;
   Dc = alphac ( _threadargscomma_ v ) * ( 1.0 - c ) - betac ( _threadargscomma_ v ) * c ;
   Dd = alphad ( _threadargscomma_ v ) * ( 1.0 - d ) - betad ( _threadargscomma_ v ) * d ;
   De = alphae ( _threadargscomma_ v ) * ( 1.0 - e ) - betae ( _threadargscomma_ v ) * e ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
 Dca_i = Dca_i  / (1. - dt*( ( - ( ( 1.0 ) ) / tau ) )) ;
 Da = Da  / (1. - dt*( (alphaa ( _threadargscomma_ v ))*(( ( - 1.0 ) )) - (betaa ( _threadargscomma_ v ))*(1.0) )) ;
 Db = Db  / (1. - dt*( (alphab ( _threadargscomma_ v ))*(( ( - 1.0 ) )) - (betab ( _threadargscomma_ v ))*(1.0) )) ;
 Dc = Dc  / (1. - dt*( (alphac ( _threadargscomma_ v ))*(( ( - 1.0 ) )) - (betac ( _threadargscomma_ v ))*(1.0) )) ;
 Dd = Dd  / (1. - dt*( (alphad ( _threadargscomma_ v ))*(( ( - 1.0 ) )) - (betad ( _threadargscomma_ v ))*(1.0) )) ;
 De = De  / (1. - dt*( (alphae ( _threadargscomma_ v ))*(( ( - 1.0 ) )) - (betae ( _threadargscomma_ v ))*(1.0) )) ;
}
 /*END CVODE*/
 static int state (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) { {
    ca_i = ca_i + (1. - exp(dt*(( - ( ( 1.0 ) ) / tau ))))*(- ( (- B)*(ica) - ( ( ( - ca0 ) ) ) / tau ) / ( ( - ( ( 1.0 ) ) / tau) ) - ca_i) ;
    a = a + (1. - exp(dt*((alphaa ( _threadargscomma_ v ))*(( ( - 1.0 ) )) - (betaa ( _threadargscomma_ v ))*(1.0))))*(- ( (alphaa ( _threadargscomma_ v ))*(( 1.0 )) ) / ( (alphaa ( _threadargscomma_ v ))*(( ( - 1.0) )) - (betaa ( _threadargscomma_ v ))*(1.0) ) - a) ;
    b = b + (1. - exp(dt*((alphab ( _threadargscomma_ v ))*(( ( - 1.0 ) )) - (betab ( _threadargscomma_ v ))*(1.0))))*(- ( (alphab ( _threadargscomma_ v ))*(( 1.0 )) ) / ( (alphab ( _threadargscomma_ v ))*(( ( - 1.0) )) - (betab ( _threadargscomma_ v ))*(1.0) ) - b) ;
    c = c + (1. - exp(dt*((alphac ( _threadargscomma_ v ))*(( ( - 1.0 ) )) - (betac ( _threadargscomma_ v ))*(1.0))))*(- ( (alphac ( _threadargscomma_ v ))*(( 1.0 )) ) / ( (alphac ( _threadargscomma_ v ))*(( ( - 1.0) )) - (betac ( _threadargscomma_ v ))*(1.0) ) - c) ;
    d = d + (1. - exp(dt*((alphad ( _threadargscomma_ v ))*(( ( - 1.0 ) )) - (betad ( _threadargscomma_ v ))*(1.0))))*(- ( (alphad ( _threadargscomma_ v ))*(( 1.0 )) ) / ( (alphad ( _threadargscomma_ v ))*(( ( - 1.0) )) - (betad ( _threadargscomma_ v ))*(1.0) ) - d) ;
    e = e + (1. - exp(dt*((alphae ( _threadargscomma_ v ))*(( ( - 1.0 ) )) - (betae ( _threadargscomma_ v ))*(1.0))))*(- ( (alphae ( _threadargscomma_ v ))*(( 1.0 )) ) / ( (alphae ( _threadargscomma_ v ))*(( ( - 1.0) )) - (betae ( _threadargscomma_ v ))*(1.0) ) - e) ;
   }
  return 0;
}
 
double alphaa ( _p, _ppvar, _thread, _nt, _lv ) double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt; 
	double _lv ;
 {
   double _lalphaa;
 _lalphaa = f ( _threadargscomma_ 2.0 , 0.1 , _lv , 19.26 ) ;
   
return _lalphaa;
 }
 
static int _hoc_alphaa() {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  alphaa ( _p, _ppvar, _thread, _nt, *getarg(1) ) ;
 ret(_r);
}
 
double betaa ( _p, _ppvar, _thread, _nt, _lv ) double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt; 
	double _lv ;
 {
   double _lbetaa;
 _lbetaa = exponential ( _threadargscomma_ 0.009 , - 0.045393 , _lv , 0.0 ) ;
   
return _lbetaa;
 }
 
static int _hoc_betaa() {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  betaa ( _p, _ppvar, _thread, _nt, *getarg(1) ) ;
 ret(_r);
}
 
double alphab ( _p, _ppvar, _thread, _nt, _lv ) double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt; 
	double _lv ;
 {
   double _lalphab;
 _lalphab = exponential ( _threadargscomma_ 1e-6 , - 0.061501 , _lv , 0.0 ) ;
   
return _lalphab;
 }
 
static int _hoc_alphab() {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  alphab ( _p, _ppvar, _thread, _nt, *getarg(1) ) ;
 ret(_r);
}
 
double betab ( _p, _ppvar, _thread, _nt, _lv ) double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt; 
	double _lv ;
 {
   double _lbetab;
 _lbetab = logistic ( _threadargscomma_ 1.0 , - 0.1 , _lv , 29.79 ) ;
   
return _lbetab;
 }
 
static int _hoc_betab() {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  betab ( _p, _ppvar, _thread, _nt, *getarg(1) ) ;
 ret(_r);
}
 
double alphac ( _p, _ppvar, _thread, _nt, _lv ) double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt; 
	double _lv ;
 {
   double _lalphac;
 _lalphac = f ( _threadargscomma_ 1.9 , 0.1 , _lv , 19.88 ) ;
   
return _lalphac;
 }
 
static int _hoc_alphac() {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  alphac ( _p, _ppvar, _thread, _nt, *getarg(1) ) ;
 ret(_r);
}
 
double betac ( _p, _ppvar, _thread, _nt, _lv ) double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt; 
	double _lv ;
 {
   double _lbetac;
 _lbetac = exponential ( _threadargscomma_ 0.046 , - 0.048239 , _lv , 0.0 ) ;
   
return _lbetac;
 }
 
static int _hoc_betac() {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  betac ( _p, _ppvar, _thread, _nt, *getarg(1) ) ;
 ret(_r);
}
 
double alphad ( _p, _ppvar, _thread, _nt, _lv ) double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt; 
	double _lv ;
 {
   double _lalphad;
 _lalphad = exponential ( _threadargscomma_ 1.6e-4 , - 0.020661 , _lv , 0.0 ) ;
   
return _lalphad;
 }
 
static int _hoc_alphad() {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  alphad ( _p, _ppvar, _thread, _nt, *getarg(1) ) ;
 ret(_r);
}
 
double betad ( _p, _ppvar, _thread, _nt, _lv ) double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt; 
	double _lv ;
 {
   double _lbetad;
 _lbetad = logistic ( _threadargscomma_ 1.0 , - 0.1 , _lv , 39.0 ) ;
   
return _lbetad;
 }
 
static int _hoc_betad() {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  betad ( _p, _ppvar, _thread, _nt, *getarg(1) ) ;
 ret(_r);
}
 
double alphae ( _p, _ppvar, _thread, _nt, _lv ) double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt; 
	double _lv ;
 {
   double _lalphae;
 _lalphae = f ( _threadargscomma_ 156.9 , 0.1 , _lv , 81.5 ) ;
   
return _lalphae;
 }
 
static int _hoc_alphae() {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  alphae ( _p, _ppvar, _thread, _nt, *getarg(1) ) ;
 ret(_r);
}
 
double betae ( _p, _ppvar, _thread, _nt, _lv ) double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt; 
	double _lv ;
 {
   double _lbetae;
 _lbetae = exponential ( _threadargscomma_ 0.29 , - 0.092081 , _lv , 0.0 ) ;
   
return _lbetae;
 }
 
static int _hoc_betae() {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  betae ( _p, _ppvar, _thread, _nt, *getarg(1) ) ;
 ret(_r);
}
 
double f ( _p, _ppvar, _thread, _nt, _lA , _lk , _lv , _lD ) double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt; 
	double _lA , _lk , _lv , _lD ;
 {
   double _lf;
 double _lx ;
  _lx = _lk * ( _lv - _lD ) ;
   if ( fabs ( _lx ) > 1e-6 ) {
     _lf = _lA * _lx / ( 1.0 - exp ( - _lx ) ) ;
     }
   else {
     _lf = _lA / ( 1.0 - 0.5 * _lx ) ;
     }
    
return _lf;
 }
 
static int _hoc_f() {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  f ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) ) ;
 ret(_r);
}
 
double logistic ( _p, _ppvar, _thread, _nt, _lA , _lk , _lv , _lD ) double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt; 
	double _lA , _lk , _lv , _lD ;
 {
   double _llogistic;
  _llogistic = _lA / ( 1.0 + exp ( _lk * ( _lv - _lD ) ) ) ;
    
return _llogistic;
 }
 
static int _hoc_logistic() {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  logistic ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) ) ;
 ret(_r);
}
 
double exponential ( _p, _ppvar, _thread, _nt, _lA , _lk , _lv , _lD ) double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt; 
	double _lA , _lk , _lv , _lD ;
 {
   double _lexponential;
  _lexponential = _lA * exp ( _lk * ( _lv - _lD ) ) ;
    
return _lexponential;
 }
 
static int _hoc_exponential() {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  exponential ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) ) ;
 ret(_r);
}
 
static int _ode_count(_type) int _type;{ return 6;}
 
static int _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
     _ode_spec1 (_p, _ppvar, _thread, _nt);
  }}
 
static int _ode_map(_ieq, _pv, _pvdot, _pp, _ppd, _atol, _type) int _ieq, _type; double** _pv, **_pvdot, *_pp, *_atol; Datum* _ppd; { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 6; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static int _ode_matsol(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
 _ode_matsol1 (_p, _ppvar, _thread, _nt);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_ca_sym, _ppvar, 0, 3);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 1, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
  a = a0;
  b = b0;
  c = c0;
  ca_i = ca_i0;
  d = d0;
  e = e0;
 {
   ca_i = ca0 ;
   a = alphaa ( _threadargscomma_ v ) / ( alphaa ( _threadargscomma_ v ) + betaa ( _threadargscomma_ v ) ) ;
   b = alphab ( _threadargscomma_ v ) / ( alphab ( _threadargscomma_ v ) + betab ( _threadargscomma_ v ) ) ;
   c = alphac ( _threadargscomma_ v ) / ( alphac ( _threadargscomma_ v ) + betac ( _threadargscomma_ v ) ) ;
   d = alphad ( _threadargscomma_ v ) / ( alphad ( _threadargscomma_ v ) + betad ( _threadargscomma_ v ) ) ;
   e = alphae ( _threadargscomma_ v ) / ( alphae ( _threadargscomma_ v ) + betae ( _threadargscomma_ v ) ) ;
   }
 
}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
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
 initmodel(_p, _ppvar, _thread, _nt);
 }}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   e_ca = ( 1000.0 ) * ( TEMP + 273.15 ) * R / ( 2.0 * F ) * log ( cao / ca_i ) ;
   gtca = gtcabar * a * a * b ;
   gnca = gncabar * c * c * d ;
   glca = glcabar * e * e ;
   ica = ( gtca + gnca + glca ) * ( v - e_ca ) ;
   }
 _current += ica;

} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
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
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dica;
  _dica = ica;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dicadv += (_dica - ica)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
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

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
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

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type) {
 double _break, _save;
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
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
 { {
 for (; t < _break; t += dt) {
   state(_p, _ppvar, _thread, _nt);
  
}}
 t = _save;
 } }}

}

static terminal(){}

static _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(ca_i) - _p;  _dlist1[0] = &(Dca_i) - _p;
 _slist1[1] = &(a) - _p;  _dlist1[1] = &(Da) - _p;
 _slist1[2] = &(b) - _p;  _dlist1[2] = &(Db) - _p;
 _slist1[3] = &(c) - _p;  _dlist1[3] = &(Dc) - _p;
 _slist1[4] = &(d) - _p;  _dlist1[4] = &(Dd) - _p;
 _slist1[5] = &(e) - _p;  _dlist1[5] = &(De) - _p;
_first = 0;
}
