/* Created by Language version: 6.2.0 */
/* NOT VECTORIZED */
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
#define gbar _p[0]
#define g _p[1]
#define i _p[2]
#define n _p[3]
#define h _p[4]
#define Dn _p[5]
#define Dh _p[6]
#define _g _p[7]
 
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
 extern double celsius;
 /* declaration of user functions */
 static int _hoc_BorgMod_tau();
 static int _hoc_Boltzmann();
 static int _hoc_exp_trap();
 static int _hoc_rates();
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
 "setdata_h_in", _hoc_setdata,
 "BorgMod_tau_h_in", _hoc_BorgMod_tau,
 "Boltzmann_h_in", _hoc_Boltzmann,
 "exp_trap_h_in", _hoc_exp_trap,
 "rates_h_in", _hoc_rates,
 0, 0
};
#define BorgMod_tau BorgMod_tau_h_in
#define Boltzmann Boltzmann_h_in
#define exp_trap exp_trap_h_in
 extern double BorgMod_tau();
 extern double Boltzmann();
 extern double exp_trap();
 /* declare global and static user variables */
#define e e_h_in
 double e = -30;
#define gates_h gates_h_h_in
 double gates_h = 1;
#define gates_n gates_n_h_in
 double gates_n = 1;
#define inf_h inf_h_h_in
 double inf_h = 0;
#define inf_n inf_n_h_in
 double inf_n = 0;
#define slope_h slope_h_h_in
 double slope_h = -10;
#define slope_n slope_n_h_in
 double slope_n = 10;
#define tau0_h tau0_h_h_in
 double tau0_h = 0.01;
#define tauF_h tauF_h_h_in
 double tauF_h = 0;
#define tauG_h tauG_h_h_in
 double tauG_h = 0.5;
#define tauDv_h tauDv_h_h_in
 double tauDv_h = 0;
#define tauA_h tauA_h_h_in
 double tauA_h = 20;
#define tau0_n tau0_n_h_in
 double tau0_n = 1;
#define tauF_n tauF_n_h_in
 double tauF_n = 0;
#define tauG_n tauG_n_h_in
 double tauG_n = 0.5;
#define tauDv_n tauDv_n_h_in
 double tauDv_n = 0;
#define tauA_n tauA_n_h_in
 double tauA_n = 100;
#define tau_h tau_h_h_in
 double tau_h = 0;
#define tau_n tau_n_h_in
 double tau_n = 0;
#define vhalfD_h vhalfD_h_h_in
 double vhalfD_h = 40;
#define vhalf_n vhalf_n_h_in
 double vhalf_n = -80;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "e_h_in", "mV",
 "vhalf_n_h_in", "mV",
 "slope_n_h_in", "mV",
 "tauA_n_h_in", "ms",
 "tauDv_n_h_in", "mV",
 "tau0_n_h_in", "ms",
 "vhalfD_h_h_in", "mV",
 "slope_h_h_in", "mV",
 "tauA_h_h_in", "ms",
 "tauDv_h_h_in", "mV",
 "tau0_h_h_in", "ms",
 "tau_n_h_in", "ms",
 "tau_h_h_in", "ms",
 "gbar_h_in", "pS/um2",
 "g_h_in", "pS/um2",
 "i_h_in", "mA/cm2",
 0,0
};
 static double delta_t = 0.01;
 static double h0 = 0;
 static double n0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "e_h_in", &e_h_in,
 "gates_n_h_in", &gates_n_h_in,
 "vhalf_n_h_in", &vhalf_n_h_in,
 "slope_n_h_in", &slope_n_h_in,
 "tauA_n_h_in", &tauA_n_h_in,
 "tauDv_n_h_in", &tauDv_n_h_in,
 "tauG_n_h_in", &tauG_n_h_in,
 "tauF_n_h_in", &tauF_n_h_in,
 "tau0_n_h_in", &tau0_n_h_in,
 "gates_h_h_in", &gates_h_h_in,
 "vhalfD_h_h_in", &vhalfD_h_h_in,
 "slope_h_h_in", &slope_h_h_in,
 "tauA_h_h_in", &tauA_h_h_in,
 "tauDv_h_h_in", &tauDv_h_h_in,
 "tauG_h_h_in", &tauG_h_h_in,
 "tauF_h_h_in", &tauF_h_h_in,
 "tau0_h_h_in", &tau0_h_h_in,
 "inf_n_h_in", &inf_n_h_in,
 "tau_n_h_in", &tau_n_h_in,
 "inf_h_h_in", &inf_h_h_in,
 "tau_h_h_in", &tau_h_h_in,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(), nrn_init(), nrn_state();
 static void nrn_cur(), nrn_jacob();
 
static int _ode_count(), _ode_map(), _ode_spec(), _ode_matsol();
 
#define _cvode_ieq _ppvar[0]._i
 /* connect range variables in _p that hoc is supposed to know about */
 static char *_mechanism[] = {
 "6.2.0",
"h_in",
 "gbar_h_in",
 0,
 "g_h_in",
 "i_h_in",
 0,
 "n_h_in",
 "h_h_in",
 0,
 0};
 
static void nrn_alloc(_prop)
	Prop *_prop;
{
	Prop *prop_ion, *need_memb();
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 8, _prop);
 	/*initialize range parameters*/
 	gbar = 1;
 	_prop->param = _p;
 	_prop->param_size = 8;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 1, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 _h_in_reg() {
	int _vectorized = 0;
  _initlists();
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
  hoc_register_dparam_size(_mechtype, 1);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 h_in /home/ximi/Documents/from_axon/ca1n1-mod/x86_64/h_in.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "h channel";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static _modl_cleanup(){ _match_recurse=1;}
static rates();
 
static int _ode_spec1(), _ode_matsol1();
 static int _slist1[2], _dlist1[2];
 static int states();
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   rates ( _threadargscomma_ v ) ;
   Dn = ( inf_n - n ) / tau_n ;
   Dh = ( inf_h - h ) / tau_h ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 rates ( _threadargscomma_ v ) ;
 Dn = Dn  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_n )) ;
 Dh = Dh  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_h )) ;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   rates ( _threadargscomma_ v ) ;
    n = n + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_n)))*(- ( ( ( inf_n ) ) / tau_n ) / ( ( ( ( - 1.0) ) ) / tau_n ) - n) ;
    h = h + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_h)))*(- ( ( ( inf_h ) ) / tau_h ) / ( ( ( ( - 1.0) ) ) / tau_h ) - h) ;
   }
  return 0;
}
 
static int  rates (  _lv )  
	double _lv ;
 {
   inf_n = Boltzmann ( _threadargscomma_ _lv , vhalf_n , slope_n ) ;
   tau_n = BorgMod_tau ( _threadargscomma_ _lv , vhalf_n , slope_n , tau0_n , tauA_n , tauG_n , tauF_n , tauDv_n ) ;
   inf_h = Boltzmann ( _threadargscomma_ _lv , vhalf_n + vhalfD_h , slope_h ) ;
   tau_h = BorgMod_tau ( _threadargscomma_ _lv , vhalf_n + vhalfD_h , slope_h , tau0_h , tauA_h , tauG_h , tauF_h , tauDv_h ) ;
    return 0; }
 
static int _hoc_rates() {
  double _r;
   _r = 1.;
 rates (  *getarg(1) ) ;
 ret(_r);
}
 
double Boltzmann (  _lv , _lv5 , _ls )  
	double _lv , _lv5 , _ls ;
 {
   double _lBoltzmann;
 _lBoltzmann = 1.0 / ( 1.0 + exp_trap ( _threadargscomma_ ( _lv - _lv5 ) / _ls ) ) ;
   
return _lBoltzmann;
 }
 
static int _hoc_Boltzmann() {
  double _r;
   _r =  Boltzmann (  *getarg(1) , *getarg(2) , *getarg(3) ) ;
 ret(_r);
}
 
double BorgMod_tau (  _lv , _lv5 , _ls , _ltau0 , _ltauA , _ltauG , _ltauF , _ltauDv )  
	double _lv , _lv5 , _ls , _ltau0 , _ltauA , _ltauG , _ltauF , _ltauDv ;
 {
   double _lBorgMod_tau;
 double _lkc , _lkr , _lDv , _lwr ;
 _lkr = 1000.0 ;
   _lwr = 1000.0 ;
   _lDv = ( _lv - ( _lv5 + _ltauDv ) ) * 1.0 ;
   _lkc = _lkr * pow( 10.0 , _ltauF ) / _ls * 1.0 ;
   _lBorgMod_tau = _ltau0 + _ltauA * 2.0 * sqrt ( _ltauG * ( 1.0 - _ltauG ) ) * ( exp_trap ( _threadargscomma_ - _lDv * _ltauG / _lwr / _lkc ) + exp_trap ( _threadargscomma_ _lDv * ( 1.0 - _ltauG ) / _lwr / _lkc ) ) / ( exp_trap ( _threadargscomma_ - _lDv * ( 1.0 - _ltauG ) * _lkc / _lkr ) + exp_trap ( _threadargscomma_ _lDv * _lkc * _ltauG / _lkr ) ) ;
   
return _lBorgMod_tau;
 }
 
static int _hoc_BorgMod_tau() {
  double _r;
   _r =  BorgMod_tau (  *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) , *getarg(5) , *getarg(6) , *getarg(7) , *getarg(8) ) ;
 ret(_r);
}
 
double exp_trap (  _lv )  
	double _lv ;
 {
   double _lexp_trap;
 if ( _lv > 700.0 ) {
     _lv = 700.0 ;
     }
   _lexp_trap = exp ( _lv ) ;
   
return _lexp_trap;
 }
 
static int _hoc_exp_trap() {
  double _r;
   _r =  exp_trap (  *getarg(1) ) ;
 ret(_r);
}
 
static int _ode_count(_type) int _type;{ return 2;}
 
static int _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
     _ode_spec1 ();
 }}
 
static int _ode_map(_ieq, _pv, _pvdot, _pp, _ppd, _atol, _type) int _ieq, _type; double** _pv, **_pvdot, *_pp, *_atol; Datum* _ppd; { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 2; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static int _ode_matsol(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
 _ode_matsol1 ();
 }}

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  h = h0;
  n = n0;
 {
   rates ( _threadargscomma_ v ) ;
   n = inf_n ;
   h = inf_h ;
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
 initmodel();
}}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   g = 0.0 ;
   if ( n >= 0.0  && h >= 0.0 ) {
     g = gbar * pow( n , gates_n ) * pow( h , gates_h ) ;
     }
   i = g * ( v - e ) * ( 1e-4 ) ;
   }
 _current += i;

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
 _g = _nrn_current(_v + .001);
 	{ _rhs = _nrn_current(_v);
 	}
 _g = (_g - _rhs)/.001;
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
 { {
 for (; t < _break; t += dt) {
 error =  states();
 if(error){fprintf(stderr,"at line 59 in file h_in.mod:\n  SOLVE states METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
 }}}

}

static terminal(){}

static _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(n) - _p;  _dlist1[0] = &(Dn) - _p;
 _slist1[1] = &(h) - _p;  _dlist1[1] = &(Dh) - _p;
_first = 0;
}
