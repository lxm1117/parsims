/* Created by Language version: 6.2.0 */
/* NOT VECTORIZED */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scoplib_ansi.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define _threadargscomma_ /**/
#define _threadargs_ /**/
 
#define _threadargsprotocomma_ /**/
#define _threadargsproto_ /**/
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
#define m _p[3]
#define h _p[4]
#define ena _p[5]
#define Dm _p[6]
#define Dh _p[7]
#define ina _p[8]
#define _g _p[9]
#define _ion_ena	*_ppvar[0]._pval
#define _ion_ina	*_ppvar[1]._pval
#define _ion_dinadv	*_ppvar[2]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_Boltz_m1(void);
 static void _hoc_Boltzmann(void);
 static void _hoc_Cauchy(void);
 static void _hoc_ngate_adjust(void);
 static void _hoc_rates(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_fNa_n1", _hoc_setdata,
 "Boltz_m1_fNa_n1", _hoc_Boltz_m1,
 "Boltzmann_fNa_n1", _hoc_Boltzmann,
 "Cauchy_fNa_n1", _hoc_Cauchy,
 "ngate_adjust_fNa_n1", _hoc_ngate_adjust,
 "rates_fNa_n1", _hoc_rates,
 0, 0
};
#define Boltz_m1 Boltz_m1_fNa_n1
#define Boltzmann Boltzmann_fNa_n1
#define Cauchy Cauchy_fNa_n1
 extern double Boltz_m1( double , double , double );
 extern double Boltzmann( double , double , double );
 extern double Cauchy( double , double , double , double );
 /* declare global and static user variables */
#define h_tauS h_tauS_fNa_n1
 double h_tauS = 30;
#define h_tauDV h_tauDV_fNa_n1
 double h_tauDV = 0;
#define h_tauA h_tauA_fNa_n1
 double h_tauA = 20;
#define h_slope h_slope_fNa_n1
 double h_slope = 8;
#define h_vhalf h_vhalf_fNa_n1
 double h_vhalf = -70;
#define h_tau h_tau_fNa_n1
 double h_tau = 0;
#define h_inf h_inf_fNa_n1
 double h_inf = 0;
#define m_tauS m_tauS_fNa_n1
 double m_tauS = 50;
#define m_tauDV m_tauDV_fNa_n1
 double m_tauDV = -10;
#define m_tauA m_tauA_fNa_n1
 double m_tauA = 0.4;
#define m_slopeAdj m_slopeAdj_fNa_n1
 double m_slopeAdj = 0;
#define m_vhalfAdj m_vhalfAdj_fNa_n1
 double m_vhalfAdj = 0;
#define m_slope m_slope_fNa_n1
 double m_slope = -7;
#define m_vhalf m_vhalf_fNa_n1
 double m_vhalf = -30;
#define m_ngate m_ngate_fNa_n1
 double m_ngate = 3;
#define m_tau m_tau_fNa_n1
 double m_tau = 0;
#define m_inf m_inf_fNa_n1
 double m_inf = 0;
#define needAdj needAdj_fNa_n1
 double needAdj = 1;
#define q10ref q10ref_fNa_n1
 double q10ref = 22;
#define q10 q10_fNa_n1
 double q10 = 3;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "q10ref_fNa_n1", "degC",
 "m_vhalf_fNa_n1", "mV",
 "m_slope_fNa_n1", "mV",
 "m_vhalfAdj_fNa_n1", "mV",
 "m_slopeAdj_fNa_n1", "mV",
 "m_tauA_fNa_n1", "ms",
 "m_tauDV_fNa_n1", "mV",
 "m_tauS_fNa_n1", "mV",
 "h_vhalf_fNa_n1", "mV",
 "h_slope_fNa_n1", "mV",
 "h_tauA_fNa_n1", "ms",
 "h_tauDV_fNa_n1", "mV",
 "h_tauS_fNa_n1", "mV",
 "m_tau_fNa_n1", "ms",
 "h_tau_fNa_n1", "ms",
 "gbar_fNa_n1", "pS/um2",
 "g_fNa_n1", "pS/um2",
 "i_fNa_n1", "mA/cm2",
 0,0
};
 static double delta_t = 0.01;
 static double h0 = 0;
 static double m0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "q10_fNa_n1", &q10_fNa_n1,
 "q10ref_fNa_n1", &q10ref_fNa_n1,
 "needAdj_fNa_n1", &needAdj_fNa_n1,
 "m_ngate_fNa_n1", &m_ngate_fNa_n1,
 "m_vhalf_fNa_n1", &m_vhalf_fNa_n1,
 "m_slope_fNa_n1", &m_slope_fNa_n1,
 "m_vhalfAdj_fNa_n1", &m_vhalfAdj_fNa_n1,
 "m_slopeAdj_fNa_n1", &m_slopeAdj_fNa_n1,
 "m_tauA_fNa_n1", &m_tauA_fNa_n1,
 "m_tauDV_fNa_n1", &m_tauDV_fNa_n1,
 "m_tauS_fNa_n1", &m_tauS_fNa_n1,
 "h_vhalf_fNa_n1", &h_vhalf_fNa_n1,
 "h_slope_fNa_n1", &h_slope_fNa_n1,
 "h_tauA_fNa_n1", &h_tauA_fNa_n1,
 "h_tauDV_fNa_n1", &h_tauDV_fNa_n1,
 "h_tauS_fNa_n1", &h_tauS_fNa_n1,
 "m_inf_fNa_n1", &m_inf_fNa_n1,
 "m_tau_fNa_n1", &m_tau_fNa_n1,
 "h_inf_fNa_n1", &h_inf_fNa_n1,
 "h_tau_fNa_n1", &h_tau_fNa_n1,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(_NrnThread*, _Memb_list*, int);
static void nrn_state(_NrnThread*, _Memb_list*, int);
 static void nrn_cur(_NrnThread*, _Memb_list*, int);
static void  nrn_jacob(_NrnThread*, _Memb_list*, int);
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(_NrnThread*, _Memb_list*, int);
static void _ode_matsol(_NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[3]._i
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "6.2.0",
"fNa_n1",
 "gbar_fNa_n1",
 0,
 "g_fNa_n1",
 "i_fNa_n1",
 0,
 "m_fNa_n1",
 "h_fNa_n1",
 0,
 0};
 static Symbol* _na_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 10, _prop);
 	/*initialize range parameters*/
 	gbar = 40;
 	_prop->param = _p;
 	_prop->param_size = 10;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_na_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0]._pval = &prop_ion->param[0]; /* ena */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ina */
 	_ppvar[2]._pval = &prop_ion->param[4]; /* _ion_dinadv */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*f)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _fNa_n1_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("na", -10000.);
 	_na_sym = hoc_lookup("na_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
  hoc_register_prop_size(_mechtype, 10, 4);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 fNa_n1 /home/ximi/Projects/ParSims/from_axon/ca1n1-mod/x86_64/fNa_n1.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "Fast sodium Channel";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int ngate_adjust();
static int rates(double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[2], _dlist1[2];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   rates ( _threadargscomma_ v ) ;
   Dm = ( m_inf - m ) / m_tau ;
   Dh = ( h_inf - h ) / h_tau ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 rates ( _threadargscomma_ v ) ;
 Dm = Dm  / (1. - dt*( ( ( ( - 1.0 ) ) ) / m_tau )) ;
 Dh = Dh  / (1. - dt*( ( ( ( - 1.0 ) ) ) / h_tau )) ;
 return 0;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   rates ( _threadargscomma_ v ) ;
    m = m + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / m_tau)))*(- ( ( ( m_inf ) ) / m_tau ) / ( ( ( ( - 1.0) ) ) / m_tau ) - m) ;
    h = h + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / h_tau)))*(- ( ( ( h_inf ) ) / h_tau ) / ( ( ( ( - 1.0) ) ) / h_tau ) - h) ;
   }
  return 0;
}
 
static int  rates (  double _lv ) {
   double _lq10f ;
 _lq10f = 1.0 / pow( q10 , ( ( celsius - q10ref ) / 10.0 ) ) ;
   if ( needAdj ) {
     ngate_adjust ( _threadargs_ ) ;
     needAdj = 0.0 ;
     }
   m_inf = Boltzmann ( _threadargscomma_ _lv , m_vhalf + m_vhalfAdj , m_slope + m_slopeAdj ) ;
   m_tau = Cauchy ( _threadargscomma_ _lv , m_tauA , m_vhalf + m_tauDV , m_tauS ) ;
   m_tau = _lq10f * m_tau ;
   h_inf = Boltzmann ( _threadargscomma_ _lv , h_vhalf , h_slope ) ;
   h_tau = Cauchy ( _threadargscomma_ _lv , h_tauA , h_vhalf + h_tauDV , h_tauS ) ;
   h_tau = _lq10f * h_tau ;
    return 0; }
 
static void _hoc_rates(void) {
  double _r;
   _r = 1.;
 rates (  *getarg(1) );
 hoc_retpushx(_r);
}
 
double Boltzmann (  double _lv , double _lv5 , double _ls ) {
   double _lBoltzmann;
 _lBoltzmann = 1.0 / ( 1.0 + exp ( ( _lv - _lv5 ) / _ls ) ) ;
   
return _lBoltzmann;
 }
 
static void _hoc_Boltzmann(void) {
  double _r;
   _r =  Boltzmann (  *getarg(1) , *getarg(2) , *getarg(3) );
 hoc_retpushx(_r);
}
 
double Cauchy (  double _lv , double _la , double _lv5 , double _ls ) {
   double _lCauchy;
 _lCauchy = _la / ( 1.0 + pow( ( ( _lv - _lv5 ) / _ls ) , 2.0 ) ) ;
   
return _lCauchy;
 }
 
static void _hoc_Cauchy(void) {
  double _r;
   _r =  Cauchy (  *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) );
 hoc_retpushx(_r);
}
 
double Boltz_m1 (  double _lx , double _lv5 , double _ls ) {
   double _lBoltz_m1;
 _lBoltz_m1 = _ls * log ( 1.0 / _lx - 1.0 ) + _lv5 ;
   
return _lBoltz_m1;
 }
 
static void _hoc_Boltz_m1(void) {
  double _r;
   _r =  Boltz_m1 (  *getarg(1) , *getarg(2) , *getarg(3) );
 hoc_retpushx(_r);
}
 
static int  ngate_adjust (  ) {
   double _lx1 , _lx2 , _lv1 , _lv2 , _laS , _laV5 ;
 _lx1 = 0.3 ;
   _lx2 = 0.7 ;
   _lv1 = Boltz_m1 ( _threadargscomma_ _lx1 , m_vhalf , m_slope ) ;
   _lv2 = Boltz_m1 ( _threadargscomma_ _lx2 , m_vhalf , m_slope ) ;
   _laS = ( _lv2 - _lv1 ) / ( log ( pow( ( 1.0 / _lx2 ) , ( 1.0 / m_ngate ) ) - 1.0 ) - log ( pow( ( 1.0 / _lx1 ) , ( 1.0 / m_ngate ) ) - 1.0 ) ) ;
   _laV5 = _lv1 - _laS * log ( 1.0 / pow( _lx1 , ( 1.0 / m_ngate ) ) - 1.0 ) ;
   m_vhalfAdj = _laV5 - m_vhalf ;
   m_slopeAdj = _laS - m_slope ;
    return 0; }
 
static void _hoc_ngate_adjust(void) {
  double _r;
   _r = 1.;
 ngate_adjust (  );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 2;}
 
static void _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ena = _ion_ena;
     _ode_spec1 ();
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 2; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ena = _ion_ena;
 _ode_matsol1 ();
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_na_sym, _ppvar, 0, 0);
   nrn_update_ion_pointer(_na_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_na_sym, _ppvar, 2, 4);
 }

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  h = h0;
  m = m0;
 {
   ngate_adjust ( _threadargs_ ) ;
   rates ( _threadargscomma_ v ) ;
   m = m_inf ;
   h = h_inf ;
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
  ena = _ion_ena;
 initmodel();
 }}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   g = 0.0 ;
   if ( m >= 0.0 ) {
     g = gbar * pow( m , m_ngate ) * h ;
     }
   i = g * ( v - ena ) * ( 1e-4 ) ;
   ina = i ;
   }
 _current += ina;

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
  ena = _ion_ena;
 _g = _nrn_current(_v + .001);
 	{ double _dina;
  _dina = ina;
 _rhs = _nrn_current(_v);
  _ion_dinadv += (_dina - ina)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ina += ina ;
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
  ena = _ion_ena;
 { {
 for (; t < _break; t += dt) {
 error =  states();
 if(error){fprintf(stderr,"at line 71 in file fNa_n1.mod:\n  SOLVE states METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
 } }}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(m) - _p;  _dlist1[0] = &(Dm) - _p;
 _slist1[1] = &(h) - _p;  _dlist1[1] = &(Dh) - _p;
_first = 0;
}
