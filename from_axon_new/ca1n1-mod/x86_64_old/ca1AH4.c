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
#define gkAbarp _p[0]
#define gkAbard _p[1]
#define ghbarf _p[2]
#define ghbars _p[3]
#define gl _p[4]
#define el _p[5]
#define eh _p[6]
#define q10 _p[7]
#define ikA _p[8]
#define ih _p[9]
#define il _p[10]
#define itot _p[11]
#define gkA _p[12]
#define gh _p[13]
#define gtot _p[14]
#define ap _p[15]
#define ad _p[16]
#define b _p[17]
#define qs _p[18]
#define qf _p[19]
#define ek _p[20]
#define Dap _p[21]
#define Dad _p[22]
#define Db _p[23]
#define Dqs _p[24]
#define Dqf _p[25]
#define ik _p[26]
#define gk _p[27]
#define cai _p[28]
#define _g _p[29]
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
 static int hoc_nrnpointerindex =  -1;
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static int _hoc_rates();
 static int _hoc_vtrap();
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
 "setdata_ca1AH4", _hoc_setdata,
 "rates_ca1AH4", _hoc_rates,
 "vtrap_ca1AH4", _hoc_vtrap,
 0, 0
};
#define vtrap vtrap_ca1AH4
 extern double vtrap();
 /* declare global and static user variables */
#define adtau adtau_ca1AH4
 double adtau = 0;
#define aptau aptau_ca1AH4
 double aptau = 0;
#define adinf adinf_ca1AH4
 double adinf = 0;
#define apinf apinf_ca1AH4
 double apinf = 0;
#define btau btau_ca1AH4
 double btau = 0;
#define binf binf_ca1AH4
 double binf = 0;
#define qftau qftau_ca1AH4
 double qftau = 0;
#define qstau qstau_ca1AH4
 double qstau = 0;
#define qfinf qfinf_ca1AH4
 double qfinf = 0;
#define qsinf qsinf_ca1AH4
 double qsinf = 0;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gkAbarp_ca1AH4", "mho/cm2",
 "gkAbard_ca1AH4", "mho/cm2",
 "ghbarf_ca1AH4", "mho/cm2",
 "ghbars_ca1AH4", "mho/cm2",
 "gl_ca1AH4", "mho/cm2",
 "el_ca1AH4", "mV",
 "eh_ca1AH4", "mV",
 "ikA_ca1AH4", "mA/cm2",
 "ih_ca1AH4", "mA/cm2",
 "il_ca1AH4", "mA/cm2",
 "itot_ca1AH4", "mA/cm2",
 "gkA_ca1AH4", "mho/cm2",
 "gh_ca1AH4", "mho/cm2",
 "gtot_ca1AH4", "mho/cm2",
 0,0
};
 static double ad0 = 0;
 static double ap0 = 0;
 static double b0 = 0;
 static double delta_t = 0.01;
 static double qf0 = 0;
 static double qs0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "apinf_ca1AH4", &apinf_ca1AH4,
 "adinf_ca1AH4", &adinf_ca1AH4,
 "binf_ca1AH4", &binf_ca1AH4,
 "qsinf_ca1AH4", &qsinf_ca1AH4,
 "qfinf_ca1AH4", &qfinf_ca1AH4,
 "aptau_ca1AH4", &aptau_ca1AH4,
 "adtau_ca1AH4", &adtau_ca1AH4,
 "btau_ca1AH4", &btau_ca1AH4,
 "qstau_ca1AH4", &qstau_ca1AH4,
 "qftau_ca1AH4", &qftau_ca1AH4,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(), nrn_init(), nrn_state();
 static void nrn_cur(), nrn_jacob();
 
static int _ode_count(), _ode_map(), _ode_spec(), _ode_matsol();
 
#define _cvode_ieq _ppvar[3]._i
 /* connect range variables in _p that hoc is supposed to know about */
 static char *_mechanism[] = {
 "6.2.0",
"ca1AH4",
 "gkAbarp_ca1AH4",
 "gkAbard_ca1AH4",
 "ghbarf_ca1AH4",
 "ghbars_ca1AH4",
 "gl_ca1AH4",
 "el_ca1AH4",
 "eh_ca1AH4",
 "q10_ca1AH4",
 0,
 "ikA_ca1AH4",
 "ih_ca1AH4",
 "il_ca1AH4",
 "itot_ca1AH4",
 "gkA_ca1AH4",
 "gh_ca1AH4",
 "gtot_ca1AH4",
 0,
 "ap_ca1AH4",
 "ad_ca1AH4",
 "b_ca1AH4",
 "qs_ca1AH4",
 "qf_ca1AH4",
 0,
 0};
 static Symbol* _k_sym;
 
static void nrn_alloc(_prop)
	Prop *_prop;
{
	Prop *prop_ion, *need_memb();
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 30, _prop);
 	/*initialize range parameters*/
 	gkAbarp = 0.001;
 	gkAbard = 0.001;
 	ghbarf = 2.5e-05;
 	ghbars = 2.5e-05;
 	gl = 0;
 	el = -90;
 	eh = -30;
 	q10 = 1;
 	_prop->param = _p;
 	_prop->param_size = 30;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_k_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0]._pval = &prop_ion->param[0]; /* ek */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ik */
 	_ppvar[2]._pval = &prop_ion->param[4]; /* _ion_dikdv */
 
}
 static _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _update_ion_pointer(Datum*);
 _ca1AH4_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("k", -10000.);
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
  hoc_register_dparam_size(_mechtype, 4);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 ca1AH4 /home/ximi/Documents/from_axon/ca1n1-mod/x86_64/ca1AH4.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "ca1AH3.mod Conductances for CA1 cells";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static _modl_cleanup(){ _match_recurse=1;}
static rates();
 
static int _ode_spec1(), _ode_matsol1();
 static int _slist1[5], _dlist1[5];
 static int states();
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   rates ( _threadargscomma_ v ) ;
   Dap = ( apinf - ap ) / aptau ;
   Dad = ( adinf - ad ) / adtau ;
   Db = ( binf - b ) / btau ;
   Dqf = ( qfinf - qf ) / qftau ;
   Dqs = ( qsinf - qs ) / qstau ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 rates ( _threadargscomma_ v ) ;
 Dap = Dap  / (1. - dt*( ( ( ( - 1.0 ) ) ) / aptau )) ;
 Dad = Dad  / (1. - dt*( ( ( ( - 1.0 ) ) ) / adtau )) ;
 Db = Db  / (1. - dt*( ( ( ( - 1.0 ) ) ) / btau )) ;
 Dqf = Dqf  / (1. - dt*( ( ( ( - 1.0 ) ) ) / qftau )) ;
 Dqs = Dqs  / (1. - dt*( ( ( ( - 1.0 ) ) ) / qstau )) ;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   rates ( _threadargscomma_ v ) ;
    ap = ap + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / aptau)))*(- ( ( ( apinf ) ) / aptau ) / ( ( ( ( - 1.0) ) ) / aptau ) - ap) ;
    ad = ad + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / adtau)))*(- ( ( ( adinf ) ) / adtau ) / ( ( ( ( - 1.0) ) ) / adtau ) - ad) ;
    b = b + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / btau)))*(- ( ( ( binf ) ) / btau ) / ( ( ( ( - 1.0) ) ) / btau ) - b) ;
    qf = qf + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / qftau)))*(- ( ( ( qfinf ) ) / qftau ) / ( ( ( ( - 1.0) ) ) / qftau ) - qf) ;
    qs = qs + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / qstau)))*(- ( ( ( qsinf ) ) / qstau ) / ( ( ( ( - 1.0) ) ) / qstau ) - qs) ;
   }
  return 0;
}
 
static int  rates (  _lv )  
	double _lv ;
 {
   double _lalpha , _lbeta ;
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
   _lalpha = 0.009 * exp ( - ( _lv + 75.0 ) / 26.0 ) * q10 ;
   _lbeta = 0.014 * exp ( ( _lv + 75.0 ) / 20.0 ) * q10 ;
   qftau = 1.0 / ( _lalpha + _lbeta ) ;
   qfinf = _lalpha * qftau ;
   qsinf = qfinf ;
   qstau = 0.1 * qftau ;
    return 0; }
 
static int _hoc_rates() {
  double _r;
   _r = 1.;
 rates (  *getarg(1) ) ;
 ret(_r);
}
 
double vtrap (  _lx , _ly )  
	double _lx , _ly ;
 {
   double _lvtrap;
 if ( fabs ( _lx / _ly ) < 1e-6 ) {
     _lvtrap = _ly * ( 1.0 - _lx / _ly / 2.0 ) ;
     }
   else {
     _lvtrap = _lx / ( exp ( _lx / _ly ) - 1.0 ) ;
     }
   
return _lvtrap;
 }
 
static int _hoc_vtrap() {
  double _r;
   _r =  vtrap (  *getarg(1) , *getarg(2) ) ;
 ret(_r);
}
 
static int _ode_count(_type) int _type;{ return 5;}
 
static int _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
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
 
static int _ode_map(_ieq, _pv, _pvdot, _pp, _ppd, _atol, _type) int _ieq, _type; double** _pv, **_pvdot, *_pp, *_atol; Datum* _ppd; { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 5; ++_i) {
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
  qf = qf0;
  qs = qs0;
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
 if(error){fprintf(stderr,"at line 69 in file ca1AH4.mod:\n        SOLVE states METHOD cnexp \n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
 } }}

}

static terminal(){}

static _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(ap) - _p;  _dlist1[0] = &(Dap) - _p;
 _slist1[1] = &(ad) - _p;  _dlist1[1] = &(Dad) - _p;
 _slist1[2] = &(b) - _p;  _dlist1[2] = &(Db) - _p;
 _slist1[3] = &(qf) - _p;  _dlist1[3] = &(Dqf) - _p;
 _slist1[4] = &(qs) - _p;  _dlist1[4] = &(Dqs) - _p;
_first = 0;
}
