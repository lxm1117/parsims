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
#define scca _p[0]
#define sccn _p[1]
#define e _p[2]
#define ampar_tot _p[3]
#define nmdar_tot _p[4]
#define i _p[5]
#define g _p[6]
#define gampar _p[7]
#define gnmdar _p[8]
#define iampar _p[9]
#define inmdar _p[10]
#define ampar_unbound _p[11]
#define nmdar_unbound _p[12]
#define num _p[13]
#define tot_num _p[14]
#define del _p[15]
#define interval_s _p[16]
#define interval_l _p[17]
#define ampar_bound _p[18]
#define ampar_active _p[19]
#define nmdar_bound _p[20]
#define nmdar_active _p[21]
#define block _p[22]
#define stim_index _p[23]
#define rlpr (_p + 24)
#define pr1 _p[109]
#define pr2 _p[110]
#define Dampar_bound _p[111]
#define Dampar_active _p[112]
#define Dnmdar_bound _p[113]
#define Dnmdar_active _p[114]
#define _g _p[115]
#define _tsav _p[116]
#define _nd_area  *_ppvar[0]._pval
 
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
 /* declaration of user functions */
 static double _hoc_relpr();
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 extern Prop* nrn_point_prop_;
 static int _pointtype;
 static void* _hoc_create_pnt(_ho) Object* _ho; { void* create_point_process();
 return create_point_process(_pointtype, _ho);
}
 static void _hoc_destroy_pnt();
 static double _hoc_loc_pnt(_vptr) void* _vptr; {double loc_point_process();
 return loc_point_process(_pointtype, _vptr);
}
 static double _hoc_has_loc(_vptr) void* _vptr; {double has_loc_point();
 return has_loc_point(_vptr);
}
 static double _hoc_get_loc_pnt(_vptr)void* _vptr; {
 double get_loc_point_process(); return (get_loc_point_process(_vptr));
}
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata(void* _vptr) { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
   _setdata(_prop);
 }
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 0,0
};
 static Member_func _member_func[] = {
 "loc", _hoc_loc_pnt,
 "has_loc", _hoc_has_loc,
 "get_loc", _hoc_get_loc_pnt,
 "relpr", _hoc_relpr,
 0, 0
};
 /* declare global and static user variables */
#define alpha_nmdar alpha_nmdar_expsyn2c_col3
 double alpha_nmdar = 0.34;
#define alpha_ampar alpha_ampar_expsyn2c_col3
 double alpha_ampar = 2;
#define beta_nmdar beta_nmdar_expsyn2c_col3
 double beta_nmdar = 0.6;
#define beta_ampar beta_ampar_expsyn2c_col3
 double beta_ampar = 2;
#define k_nmdar k_nmdar_expsyn2c_col3
 double k_nmdar = 0.02;
#define k_ampar k_ampar_expsyn2c_col3
 double k_ampar = 2;
#define mg mg_expsyn2c_col3
 double mg = 1.2;
#define tmp tmp_expsyn2c_col3
 double tmp = 0;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "k_ampar_expsyn2c_col3", "1/ms",
 "alpha_ampar_expsyn2c_col3", "1/ms",
 "beta_ampar_expsyn2c_col3", "1/ms",
 "k_nmdar_expsyn2c_col3", "1/ms",
 "alpha_nmdar_expsyn2c_col3", "1/ms",
 "beta_nmdar_expsyn2c_col3", "1/ms",
 "scca", "uS",
 "sccn", "uS",
 "e", "mV",
 "i", "nA",
 "g", "uS",
 "gampar", "uS",
 "gnmdar", "uS",
 "iampar", "nA",
 "inmdar", "nA",
 "ampar_unbound", "1",
 "nmdar_unbound", "1",
 "del", "ms",
 "interval_s", "ms",
 "interval_l", "ms",
 0,0
};
 static double ampar_active0 = 0;
 static double ampar_bound0 = 0;
 static double delta_t = 0.01;
 static double nmdar_active0 = 0;
 static double nmdar_bound0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "mg_expsyn2c_col3", &mg_expsyn2c_col3,
 "k_ampar_expsyn2c_col3", &k_ampar_expsyn2c_col3,
 "alpha_ampar_expsyn2c_col3", &alpha_ampar_expsyn2c_col3,
 "beta_ampar_expsyn2c_col3", &beta_ampar_expsyn2c_col3,
 "k_nmdar_expsyn2c_col3", &k_nmdar_expsyn2c_col3,
 "alpha_nmdar_expsyn2c_col3", &alpha_nmdar_expsyn2c_col3,
 "beta_nmdar_expsyn2c_col3", &beta_nmdar_expsyn2c_col3,
 "tmp_expsyn2c_col3", &tmp_expsyn2c_col3,
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
 static void _hoc_destroy_pnt(_vptr) void* _vptr; {
   destroy_point_process(_vptr);
}
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(_NrnThread*, _Memb_list*, int);
static void _ode_matsol(_NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[3]._i
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "6.2.0",
"expsyn2c_col3",
 "scca",
 "sccn",
 "e",
 "ampar_tot",
 "nmdar_tot",
 0,
 "i",
 "g",
 "gampar",
 "gnmdar",
 "iampar",
 "inmdar",
 "ampar_unbound",
 "nmdar_unbound",
 "num",
 "tot_num",
 "del",
 "interval_s",
 "interval_l",
 0,
 "ampar_bound",
 "ampar_active",
 "nmdar_bound",
 "nmdar_active",
 0,
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
  if (nrn_point_prop_) {
	_prop->_alloc_seq = nrn_point_prop_->_alloc_seq;
	_p = nrn_point_prop_->param;
	_ppvar = nrn_point_prop_->dparam;
 }else{
 	_p = nrn_prop_data_alloc(_mechtype, 117, _prop);
 	/*initialize range parameters*/
 	scca = 8e-06;
 	sccn = 5e-05;
 	e = 1.3827;
 	ampar_tot = 80;
 	nmdar_tot = 20;
  }
 	_prop->param = _p;
 	_prop->param_size = 117;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 
#define _tqitem &(_ppvar[2]._pvoid)
 static void _net_receive(Point_process*, double*, double);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*f)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _expsyn2c_col3_reg() {
	int _vectorized = 0;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex, 0,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
  hoc_register_prop_size(_mechtype, 117, 4);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 expsyn2c_col3 /home/ximi/Projects/ParSims/from_axon/ca1n1-mod/x86_64/expsyn2c_col3.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int relpr();
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[4], _dlist1[4];
 static int state(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   Dampar_bound = - k_ampar * ampar_bound - beta_ampar * ampar_bound + alpha_ampar * ampar_active ;
   Dampar_active = beta_ampar * ampar_bound - alpha_ampar * ampar_active ;
   Dnmdar_bound = - k_nmdar * nmdar_bound - beta_nmdar * nmdar_bound + alpha_nmdar * nmdar_active ;
   Dnmdar_active = beta_nmdar * nmdar_bound - alpha_nmdar * nmdar_active ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 Dampar_bound = Dampar_bound  / (1. - dt*( (- k_ampar)*(1.0) - (beta_ampar)*(1.0) )) ;
 Dampar_active = Dampar_active  / (1. - dt*( ( - (alpha_ampar)*(1.0) ) )) ;
 Dnmdar_bound = Dnmdar_bound  / (1. - dt*( (- k_nmdar)*(1.0) - (beta_nmdar)*(1.0) )) ;
 Dnmdar_active = Dnmdar_active  / (1. - dt*( ( - (alpha_nmdar)*(1.0) ) )) ;
 return 0;
}
 /*END CVODE*/
 static int state () {_reset=0;
 {
    ampar_bound = ampar_bound + (1. - exp(dt*((- k_ampar)*(1.0) - (beta_ampar)*(1.0))))*(- ( (alpha_ampar)*(ampar_active) ) / ( (- k_ampar)*(1.0) - (beta_ampar)*(1.0) ) - ampar_bound) ;
    ampar_active = ampar_active + (1. - exp(dt*(( - (alpha_ampar)*(1.0) ))))*(- ( (beta_ampar)*(ampar_bound) ) / ( ( - (alpha_ampar)*(1.0)) ) - ampar_active) ;
    nmdar_bound = nmdar_bound + (1. - exp(dt*((- k_nmdar)*(1.0) - (beta_nmdar)*(1.0))))*(- ( (alpha_nmdar)*(nmdar_active) ) / ( (- k_nmdar)*(1.0) - (beta_nmdar)*(1.0) ) - nmdar_bound) ;
    nmdar_active = nmdar_active + (1. - exp(dt*(( - (alpha_nmdar)*(1.0) ))))*(- ( (beta_nmdar)*(nmdar_bound) ) / ( ( - (alpha_nmdar)*(1.0)) ) - nmdar_active) ;
   }
  return 0;
}
 
static void _net_receive (_pnt, _args, _lflag) Point_process* _pnt; double* _args; double _lflag; 
{    _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t;   if (_lflag == 1. ) {*(_tqitem) = 0;}
 {
   if ( _lflag  == 1.0 ) {
     tmp = fmod ( stim_index , num ) ;
     pr1 = rlpr [ ((int) tmp ) ] ;
     pr2 = scop_random ( ) ;
     if ( pr2 < pr1 ) {
       ampar_bound = ampar_bound + 0.6 * ampar_unbound ;
       nmdar_bound = nmdar_bound + 0.6 * nmdar_unbound ;
       printf ( "%s %f %s %f %s %f %s %f %s %f\n" , "pr1: " , pr1 , "pr2: " , pr2 , "stim_index: " , stim_index , "ampar_unbound: " , ampar_unbound , "nmdar_unbound: " , nmdar_unbound ) ;
       }
     if ( stim_index <= tot_num - 2.0 ) {
       if ( stim_index > 0.0  && fmod ( stim_index + 1.0 , num )  == 0.0 ) {
         net_send ( _tqitem, _args, _pnt, t +  interval_l , 1.0 ) ;
         }
       else {
         net_send ( _tqitem, _args, _pnt, t +  interval_s , 1.0 ) ;
         }
       stim_index = stim_index + 1.0 ;
       }
     }
   } }
 
static int  relpr (  ) {
   
/*VERBATIM*/

	FILE *file;
	int size, ind;  //cannot use the var name i, because it refers to NONPSCIFIC ION
	float f;

	file=fopen("relpr_smooth_col3.dat", "r");
	//fseek(file, 0, SEEK_END);
	//size=ftell(file);
	//rlpr=(float*)calloc(size, sizeof(float));
	
	
	ind=0;
	while(!feof(file)){
		fscanf(file, "%f", &f);
		rlpr[ind]=f;
		//++++printf("%f %lf\n", f, rlpr[ind]);
		
		//fscanf(file, "%f", &rlpr[ind]);  //don't why this doesn't work
		//+++++printf("%f, %d\n", rlpr[ind], ind);		
		ind++;
	
	}
	fclose(file);

  return 0; }
 
static double _hoc_relpr(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r = 1.;
 relpr (  );
 return(_r);
}
 
static int _ode_count(int _type){ return 4;}
 
static void _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
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
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 4; ++_i) {
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
 _ode_matsol1 ();
 }}

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  ampar_active = ampar_active0;
  ampar_bound = ampar_bound0;
  nmdar_active = nmdar_active0;
  nmdar_bound = nmdar_bound0;
 {
   stim_index = 0.0 ;
   ampar_active = 0.0 ;
   ampar_bound = 0.0 ;
   nmdar_active = 0.0 ;
   nmdar_bound = 0.0 ;
   relpr ( _threadargs_ ) ;
   if ( stim_index < tot_num ) {
     net_send ( _tqitem, (double*)0, _ppvar[1]._pvoid, t +  del , 1.0 ) ;
     }
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
 _tsav = -1e20;
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
    block = 8.8 * exp ( v / 12.5 ) / ( mg + 8.8 * exp ( v / 12.5 ) ) ;
    if ( stim_index < tot_num ) {
     }
   ampar_unbound = ampar_tot - ampar_active - ampar_bound ;
   nmdar_unbound = nmdar_tot - nmdar_active - nmdar_bound ;
   if ( ampar_unbound < 0.0 ) {
     ampar_unbound = 0.0 ;
     }
   if ( nmdar_unbound < 0.0 ) {
     nmdar_unbound = 0.0 ;
     }
   gampar = scca * ampar_active ;
   gnmdar = sccn * nmdar_active * block ;
   g = gampar + gnmdar ;
   iampar = gampar * ( v - e ) ;
   inmdar = gnmdar * ( v - e ) ;
   i = iampar + inmdar ;
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
 _g *=  1.e2/(_nd_area);
 _rhs *= 1.e2/(_nd_area);
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
 error =  state();
 if(error){fprintf(stderr,"at line 91 in file expsyn2c_col3.mod:\n		SOLVE state METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
 }}}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(ampar_bound) - _p;  _dlist1[0] = &(Dampar_bound) - _p;
 _slist1[1] = &(ampar_active) - _p;  _dlist1[1] = &(Dampar_active) - _p;
 _slist1[2] = &(nmdar_bound) - _p;  _dlist1[2] = &(Dnmdar_bound) - _p;
 _slist1[3] = &(nmdar_active) - _p;  _dlist1[3] = &(Dnmdar_active) - _p;
_first = 0;
}
