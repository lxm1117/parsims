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
#define gbar_fsq _p[1]
#define i _p[2]
#define g _p[3]
#define m_fast _p[4]
#define m_slow _p[5]
#define Dm_fast _p[6]
#define Dm_slow _p[7]
#define _g _p[8]
 
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
 static int _hoc_Boltzmann();
 static int _hoc_Cauchy();
 static int _hoc_VB_original_rates();
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
 "setdata_h_n1", _hoc_setdata,
 "Boltzmann_h_n1", _hoc_Boltzmann,
 "Cauchy_h_n1", _hoc_Cauchy,
 "VB_original_rates_h_n1", _hoc_VB_original_rates,
 "rates_h_n1", _hoc_rates,
 0, 0
};
#define Boltzmann Boltzmann_h_n1
#define Cauchy Cauchy_h_n1
 extern double Boltzmann();
 extern double Cauchy();
 /* declare global and static user variables */
#define e e_h_n1
 double e = -30;
#define m_tauS_slow m_tauS_slow_h_n1
 double m_tauS_slow = 45;
#define m_tauDV_slow m_tauDV_slow_h_n1
 double m_tauDV_slow = 0;
#define m_tauA_slow m_tauA_slow_h_n1
 double m_tauA_slow = 2000;
#define m_tauS_fast m_tauS_fast_h_n1
 double m_tauS_fast = 20;
#define m_tauDV_fast m_tauDV_fast_h_n1
 double m_tauDV_fast = 0;
#define m_tauA_fast m_tauA_fast_h_n1
 double m_tauA_fast = 120;
#define m_slope m_slope_h_n1
 double m_slope = 10.4;
#define m_vhalf m_vhalf_h_n1
 double m_vhalf = -80;
#define mho2pS mho2pS_h_n1
 double mho2pS = 0.0001;
#define m_tau_fast m_tau_fast_h_n1
 double m_tau_fast = 0;
#define m_tau_slow m_tau_slow_h_n1
 double m_tau_slow = 0;
#define m_inf_fast m_inf_fast_h_n1
 double m_inf_fast = 0;
#define m_inf_slow m_inf_slow_h_n1
 double m_inf_slow = 0;
#define q10ref q10ref_h_n1
 double q10ref = 22;
#define q10 q10_h_n1
 double q10 = 4.5;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "q10ref_h_n1", "degC",
 "e_h_n1", "mV",
 "m_vhalf_h_n1", "mV",
 "m_slope_h_n1", "mV",
 "m_tauA_fast_h_n1", "ms",
 "m_tauDV_fast_h_n1", "mV",
 "m_tauS_fast_h_n1", "mV",
 "m_tauA_slow_h_n1", "ms",
 "m_tauDV_slow_h_n1", "mV",
 "m_tauS_slow_h_n1", "mV",
 "m_inf_slow_h_n1", "1",
 "m_tau_slow_h_n1", "ms",
 "m_inf_fast_h_n1", "1",
 "m_tau_fast_h_n1", "ms",
 "gbar_h_n1", "pS/um2",
 "i_h_n1", "mA/cm2",
 "g_h_n1", "pS/um2",
 0,0
};
 static double delta_t = 0.01;
 static double m_slow0 = 0;
 static double m_fast0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "mho2pS_h_n1", &mho2pS_h_n1,
 "q10_h_n1", &q10_h_n1,
 "q10ref_h_n1", &q10ref_h_n1,
 "e_h_n1", &e_h_n1,
 "m_vhalf_h_n1", &m_vhalf_h_n1,
 "m_slope_h_n1", &m_slope_h_n1,
 "m_tauA_fast_h_n1", &m_tauA_fast_h_n1,
 "m_tauDV_fast_h_n1", &m_tauDV_fast_h_n1,
 "m_tauS_fast_h_n1", &m_tauS_fast_h_n1,
 "m_tauA_slow_h_n1", &m_tauA_slow_h_n1,
 "m_tauDV_slow_h_n1", &m_tauDV_slow_h_n1,
 "m_tauS_slow_h_n1", &m_tauS_slow_h_n1,
 "m_inf_slow_h_n1", &m_inf_slow_h_n1,
 "m_tau_slow_h_n1", &m_tau_slow_h_n1,
 "m_inf_fast_h_n1", &m_inf_fast_h_n1,
 "m_tau_fast_h_n1", &m_tau_fast_h_n1,
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
"h_n1",
 "gbar_h_n1",
 "gbar_fsq_h_n1",
 0,
 "i_h_n1",
 "g_h_n1",
 0,
 "m_fast_h_n1",
 "m_slow_h_n1",
 0,
 0};
 
static void nrn_alloc(_prop)
	Prop *_prop;
{
	Prop *prop_ion, *need_memb();
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 9, _prop);
 	/*initialize range parameters*/
 	gbar = 1;
 	gbar_fsq = 0.8;
 	_prop->param = _p;
 	_prop->param_size = 9;
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
 _h_n1_reg() {
	int _vectorized = 0;
  _initlists();
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
  hoc_register_dparam_size(_mechtype, 1);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 h_n1 /home/ximi/Documents/from_axon/ca1n1-mod/x86_64/h_n1.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "h Conductance for CA1 cells";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static _modl_cleanup(){ _match_recurse=1;}
static VB_original_rates();
static rates();
 
static int _ode_spec1(), _ode_matsol1();
 static int _slist1[2], _dlist1[2];
 static int states();
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   rates ( _threadargscomma_ v ) ;
   Dm_slow = ( m_inf_slow - m_slow ) / m_tau_slow ;
   Dm_fast = ( m_inf_fast - m_fast ) / m_tau_fast ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 rates ( _threadargscomma_ v ) ;
 Dm_slow = Dm_slow  / (1. - dt*( ( ( ( - 1.0 ) ) ) / m_tau_slow )) ;
 Dm_fast = Dm_fast  / (1. - dt*( ( ( ( - 1.0 ) ) ) / m_tau_fast )) ;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   rates ( _threadargscomma_ v ) ;
    m_slow = m_slow + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / m_tau_slow)))*(- ( ( ( m_inf_slow ) ) / m_tau_slow ) / ( ( ( ( - 1.0) ) ) / m_tau_slow ) - m_slow) ;
    m_fast = m_fast + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / m_tau_fast)))*(- ( ( ( m_inf_fast ) ) / m_tau_fast ) / ( ( ( ( - 1.0) ) ) / m_tau_fast ) - m_fast) ;
   }
  return 0;
}
 
static int  rates (  _lv )  
	double _lv ;
 {
   double _lq10f ;
 _lq10f = 1.0 / pow( q10 , ( ( celsius - q10ref ) / 10.0 ) ) ;
   m_inf_fast = Boltzmann ( _threadargscomma_ _lv , m_vhalf , m_slope ) ;
   m_inf_slow = m_inf_fast ;
   m_tau_fast = Cauchy ( _threadargscomma_ _lv , m_tauA_fast , m_vhalf + m_tauDV_fast , m_tauS_fast ) ;
   m_tau_slow = Cauchy ( _threadargscomma_ _lv , m_tauA_slow , m_vhalf + m_tauDV_slow , m_tauS_slow ) ;
   m_tau_fast = _lq10f * m_tau_fast ;
   m_tau_slow = _lq10f * m_tau_slow ;
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
 _lBoltzmann = 1.0 / ( 1.0 + exp ( ( _lv - _lv5 ) / _ls ) ) ;
   
return _lBoltzmann;
 }
 
static int _hoc_Boltzmann() {
  double _r;
   _r =  Boltzmann (  *getarg(1) , *getarg(2) , *getarg(3) ) ;
 ret(_r);
}
 
double Cauchy (  _lv , _la , _lv5 , _ls )  
	double _lv , _la , _lv5 , _ls ;
 {
   double _lCauchy;
 _lCauchy = _la / ( 1.0 + pow( ( ( _lv - _lv5 ) / _ls ) , 2.0 ) ) ;
   
return _lCauchy;
 }
 
static int _hoc_Cauchy() {
  double _r;
   _r =  Cauchy (  *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) ) ;
 ret(_r);
}
 
static int  VB_original_rates (  _lv )  
	double _lv ;
 {
   double _lalpha , _lbeta , _lq10f ;
 _lq10f = 1.0 / pow( q10 , ( ( celsius - q10ref ) / 10.0 ) ) ;
   m_inf_slow = 1.0 / ( 1.0 + exp ( ( _lv - m_vhalf ) / m_slope ) ) ;
   m_inf_fast = 1.0 / ( 1.0 + exp ( ( _lv - m_vhalf ) / m_slope ) ) ;
   if ( _lv < - 83.0 ) {
     m_tau_slow = _lq10f * ( 177.0 + 67.0 * exp ( ( _lv + 159.0 ) / 35.5 ) ) ;
     }
   else {
     m_tau_slow = _lq10f * ( 267.0 + 542.0 * exp ( - ( _lv + 85.0 ) / 20.0 ) ) ;
     }
   if ( _lv < - 87.0 ) {
     m_tau_fast = _lq10f * ( 17.0 + 7.2 * exp ( ( _lv + 124.0 ) / 22.5 ) ) ;
     }
   else {
     m_tau_fast = _lq10f * ( 27.0 + 24.0 * exp ( - ( _lv + 85.0 ) / 20.0 ) ) ;
     }
    return 0; }
 
static int _hoc_VB_original_rates() {
  double _r;
   _r = 1.;
 VB_original_rates (  *getarg(1) ) ;
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
  m_slow = m_slow0;
  m_fast = m_fast0;
 {
   rates ( _threadargscomma_ v ) ;
   m_slow = m_inf_slow ;
   m_fast = m_inf_fast ;
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
   g = gbar * ( m_fast * gbar_fsq + m_slow * ( 1.0 - gbar_fsq ) ) ;
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
 if(error){fprintf(stderr,"at line 85 in file h_n1.mod:\n  SOLVE states METHOD cnexp \n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
 }}}

}

static terminal(){}

static _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(m_slow) - _p;  _dlist1[0] = &(Dm_slow) - _p;
 _slist1[1] = &(m_fast) - _p;  _dlist1[1] = &(Dm_fast) - _p;
_first = 0;
}
