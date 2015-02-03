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
#define gkAbarp _p[0]
#define gkAbard _p[1]
#define ghbarf _p[2]
#define ghbars _p[3]
#define gl _p[4]
#define el _p[5]
#define eh _p[6]
#define qvh _p[7]
#define qslo _p[8]
#define qsinc _p[9]
#define qfinc _p[10]
#define q10s _p[11]
#define ikA _p[12]
#define ih _p[13]
#define il _p[14]
#define itot _p[15]
#define gkA _p[16]
#define gh _p[17]
#define gtot _p[18]
#define ap _p[19]
#define ad _p[20]
#define b _p[21]
#define qf _p[22]
#define qs _p[23]
#define ek _p[24]
#define Dap _p[25]
#define Dad _p[26]
#define Db _p[27]
#define Dqf _p[28]
#define Dqs _p[29]
#define ik _p[30]
#define gk _p[31]
#define cai _p[32]
#define _g _p[33]
#define _ion_ek	*_ppvar[0]._pval
#define _ion_ik	*_ppvar[1]._pval
#define _ion_dikdv	*_ppvar[2]._pval
 
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
 static void _hoc_rates(void);
 static void _hoc_vtrap(void);
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
 "setdata_ca1AH", _hoc_setdata,
 "rates_ca1AH", _hoc_rates,
 "vtrap_ca1AH", _hoc_vtrap,
 0, 0
};
#define vtrap vtrap_ca1AH
 extern double vtrap( double , double );
 /* declare global and static user variables */
#define adtau adtau_ca1AH
 double adtau = 0;
#define aptau aptau_ca1AH
 double aptau = 0;
#define adinf adinf_ca1AH
 double adinf = 0;
#define apinf apinf_ca1AH
 double apinf = 0;
#define btau btau_ca1AH
 double btau = 0;
#define binf binf_ca1AH
 double binf = 0;
#define q10f q10f_ca1AH
 double q10f = 1;
#define qftau qftau_ca1AH
 double qftau = 0;
#define qstau qstau_ca1AH
 double qstau = 0;
#define qfinf qfinf_ca1AH
 double qfinf = 0;
#define qsinf qsinf_ca1AH
 double qsinf = 0;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gkAbarp_ca1AH", "mho/cm2",
 "gkAbard_ca1AH", "mho/cm2",
 "ghbarf_ca1AH", "mho/cm2",
 "ghbars_ca1AH", "mho/cm2",
 "gl_ca1AH", "mho/cm2",
 "el_ca1AH", "mV",
 "eh_ca1AH", "mV",
 "qvh_ca1AH", "mV",
 "ikA_ca1AH", "mA/cm2",
 "ih_ca1AH", "mA/cm2",
 "il_ca1AH", "mA/cm2",
 "itot_ca1AH", "mA/cm2",
 "gkA_ca1AH", "mho/cm2",
 "gh_ca1AH", "mho/cm2",
 "gtot_ca1AH", "mho/cm2",
 0,0
};
 static double ad0 = 0;
 static double ap0 = 0;
 static double b0 = 0;
 static double delta_t = 0.01;
 static double qs0 = 0;
 static double qf0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "q10f_ca1AH", &q10f_ca1AH,
 "apinf_ca1AH", &apinf_ca1AH,
 "adinf_ca1AH", &adinf_ca1AH,
 "binf_ca1AH", &binf_ca1AH,
 "qsinf_ca1AH", &qsinf_ca1AH,
 "qfinf_ca1AH", &qfinf_ca1AH,
 "aptau_ca1AH", &aptau_ca1AH,
 "adtau_ca1AH", &adtau_ca1AH,
 "btau_ca1AH", &btau_ca1AH,
 "qstau_ca1AH", &qstau_ca1AH,
 "qftau_ca1AH", &qftau_ca1AH,
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
"ca1AH",
 "gkAbarp_ca1AH",
 "gkAbard_ca1AH",
 "ghbarf_ca1AH",
 "ghbars_ca1AH",
 "gl_ca1AH",
 "el_ca1AH",
 "eh_ca1AH",
 "qvh_ca1AH",
 "qslo_ca1AH",
 "qsinc_ca1AH",
 "qfinc_ca1AH",
 "q10s_ca1AH",
 0,
 "ikA_ca1AH",
 "ih_ca1AH",
 "il_ca1AH",
 "itot_ca1AH",
 "gkA_ca1AH",
 "gh_ca1AH",
 "gtot_ca1AH",
 0,
 "ap_ca1AH",
 "ad_ca1AH",
 "b_ca1AH",
 "qf_ca1AH",
 "qs_ca1AH",
 0,
 0};
 static Symbol* _k_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 34, _prop);
 	/*initialize range parameters*/
 	gkAbarp = 0.001;
 	gkAbard = 0.001;
 	ghbarf = 2.5e-05;
 	ghbars = 2.5e-05;
 	gl = 2.5e-05;
 	el = -90;
 	eh = -20;
 	qvh = -92;
 	qslo = 10.4;
 	qsinc = 0;
 	qfinc = 0;
 	q10s = 1;
 	_prop->param = _p;
 	_prop->param_size = 34;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_k_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0]._pval = &prop_ion->param[0]; /* ek */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ik */
 	_ppvar[2]._pval = &prop_ion->param[4]; /* _ion_dikdv */
 
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

 void _ca1AH_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("k", -10000.);
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
  hoc_register_prop_size(_mechtype, 34, 4);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 ca1AH /home/ximi/Projects/ParSims/from_axon/ca1n1-mod/x86_64/ca1AH.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "ca1AH.mod Conductances for CA1 cells";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rates(double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[5], _dlist1[5];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   rates ( _threadargscomma_ v ) ;
   Dap = ( apinf - ap ) / aptau ;
   Dad = ( adinf - ad ) / adtau ;
   Db = ( binf - b ) / btau ;
   Dqs = ( qsinf - qs ) / qstau ;
   Dqf = ( qfinf - qf ) / qftau ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 rates ( _threadargscomma_ v ) ;
 Dap = Dap  / (1. - dt*( ( ( ( - 1.0 ) ) ) / aptau )) ;
 Dad = Dad  / (1. - dt*( ( ( ( - 1.0 ) ) ) / adtau )) ;
 Db = Db  / (1. - dt*( ( ( ( - 1.0 ) ) ) / btau )) ;
 Dqs = Dqs  / (1. - dt*( ( ( ( - 1.0 ) ) ) / qstau )) ;
 Dqf = Dqf  / (1. - dt*( ( ( ( - 1.0 ) ) ) / qftau )) ;
 return 0;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   rates ( _threadargscomma_ v ) ;
    ap = ap + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / aptau)))*(- ( ( ( apinf ) ) / aptau ) / ( ( ( ( - 1.0) ) ) / aptau ) - ap) ;
    ad = ad + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / adtau)))*(- ( ( ( adinf ) ) / adtau ) / ( ( ( ( - 1.0) ) ) / adtau ) - ad) ;
    b = b + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / btau)))*(- ( ( ( binf ) ) / btau ) / ( ( ( ( - 1.0) ) ) / btau ) - b) ;
    qs = qs + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / qstau)))*(- ( ( ( qsinf ) ) / qstau ) / ( ( ( ( - 1.0) ) ) / qstau ) - qs) ;
    qf = qf + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / qftau)))*(- ( ( ( qfinf ) ) / qftau ) / ( ( ( ( - 1.0) ) ) / qftau ) - qf) ;
   }
  return 0;
}
 
static int  rates (  double _lv ) {
   double _lq10 , _lalpha , _lbeta ;
 _lq10 = pow( 3.0 , ( ( celsius - 6.3 ) / 10.0 ) ) ;
   _lalpha = - 0.1 * vtrap ( _threadargscomma_ ( _lv + 31.3 ) , - 25.0 ) ;
   _lbeta = 0.1 * vtrap ( _threadargscomma_ ( _lv + 31.3 ) , 25.0 ) ;
   aptau = 1.0 / ( _lalpha + _lbeta ) ;
   apinf = _lalpha / ( _lalpha + _lbeta ) ;
   _lalpha = - 0.1 * vtrap ( _threadargscomma_ ( _lv + 34.4 ) , - 21.0 ) ;
   _lbeta = 0.1 * vtrap ( _threadargscomma_ ( _lv + 34.4 ) , 21.0 ) ;
   adtau = 1.0 / ( _lalpha + _lbeta ) ;
   adinf = _lalpha / ( _lalpha + _lbeta ) ;
   _lalpha = 0.01 * vtrap ( _threadargscomma_ ( _lv + 58.0 ) , 8.2 ) ;
   _lbeta = - 0.01 * vtrap ( _threadargscomma_ ( _lv + 58.0 ) , - 8.2 ) ;
   binf = _lalpha / ( _lalpha + _lbeta ) ;
   btau = 5.0 ;
   if ( _lv > - 20.0 ) {
     btau = 5.0 + 2.6 * ( _lv + 20.0 ) / 10.0 ;
     }
   qsinf = 1.0 / ( 1.0 + exp ( ( _lv - qvh ) / qslo ) ) ;
   qfinf = 1.0 / ( 1.0 + exp ( ( _lv - qvh ) / qslo ) ) ;
   if ( _lv < - 83.0 ) {
     qstau = ( 177.0 + qsinc + 67.0 * exp ( ( _lv + 159.0 ) / 35.5 ) ) / q10s ;
     }
   else {
     qstau = ( 267.0 + qsinc + 542.0 * exp ( - ( _lv + 85.0 ) / 20.0 ) ) / q10s ;
     }
   if ( _lv < - 87.0 ) {
     qftau = ( 17.0 + qfinc + 7.2 * exp ( ( _lv + 124.0 ) / 22.5 ) ) / q10f ;
     }
   else {
     qftau = ( 27.0 + qfinc + 24.0 * exp ( - ( _lv + 85.0 ) / 20.0 ) ) / q10f ;
     }
    return 0; }
 
static void _hoc_rates(void) {
  double _r;
   _r = 1.;
 rates (  *getarg(1) );
 hoc_retpushx(_r);
}
 
double vtrap (  double _lx , double _ly ) {
   double _lvtrap;
 if ( fabs ( _lx / _ly ) < 1e-6 ) {
     _lvtrap = _ly * ( 1.0 - _lx / _ly / 2.0 ) ;
     }
   else {
     _lvtrap = _lx / ( exp ( _lx / _ly ) - 1.0 ) ;
     }
   
return _lvtrap;
 }
 
static void _hoc_vtrap(void) {
  double _r;
   _r =  vtrap (  *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 5;}
 
static void _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ek = _ion_ek;
     _ode_spec1 ();
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 5; ++_i) {
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
  ek = _ion_ek;
 _ode_matsol1 ();
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_k_sym, _ppvar, 0, 0);
   nrn_update_ion_pointer(_k_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 2, 4);
 }

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  ad = ad0;
  ap = ap0;
  b = b0;
  qs = qs0;
  qf = qf0;
 {
   rates ( _threadargscomma_ v ) ;
   ap = apinf ;
   ad = adinf ;
   b = binf ;
   qs = qsinf ;
   qf = qfinf ;
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
  ek = _ion_ek;
 initmodel();
 }}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   gkA = gkAbarp * ap * ap * ap * ap * b + gkAbard * ad * ad * ad * ad * b ;
   ikA = gkA * ( v - ek ) ;
   gh = ghbars * qs * qs + ghbarf * qf * qf ;
   ih = gh * ( v - eh ) ;
   gk = gkA ;
   ik = ikA ;
   il = gl * ( v - el ) ;
   gtot = gk + gh + gl ;
   itot = ik + ih + il ;
   }
 _current += ik;
 _current += ih;
 _current += il;

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
  ek = _ion_ek;
 _g = _nrn_current(_v + .001);
 	{ double _dik;
  _dik = ik;
 _rhs = _nrn_current(_v);
  _ion_dikdv += (_dik - ik)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ik += ik ;
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
  ek = _ion_ek;
 { {
 for (; t < _break; t += dt) {
 error =  states();
 if(error){fprintf(stderr,"at line 74 in file ca1AH.mod:\n        SOLVE states METHOD cnexp \n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
 } }}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(ap) - _p;  _dlist1[0] = &(Dap) - _p;
 _slist1[1] = &(ad) - _p;  _dlist1[1] = &(Dad) - _p;
 _slist1[2] = &(b) - _p;  _dlist1[2] = &(Db) - _p;
 _slist1[3] = &(qs) - _p;  _dlist1[3] = &(Dqs) - _p;
 _slist1[4] = &(qf) - _p;  _dlist1[4] = &(Dqf) - _p;
_first = 0;
}
