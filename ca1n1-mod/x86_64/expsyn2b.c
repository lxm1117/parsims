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
#define delay _p[0]
#define tau1 _p[1]
#define tau2 _p[2]
#define tau3 _p[3]
#define tau4 _p[4]
#define e _p[5]
#define i _p[6]
#define g _p[7]
#define gampa _p[8]
#define gnmda _p[9]
#define block _p[10]
#define iampa _p[11]
#define inmda _p[12]
#define gmax _p[13]
#define gmax2 _p[14]
#define pr1 _p[15]
#define pr2 _p[16]
#define num _p[17]
#define del _p[18]
#define interval _p[19]
#define t0 _p[20]
#define g0_ampa _p[21]
#define g0_nmda _p[22]
#define factor _p[23]
#define factor2 _p[24]
#define index _p[25]
#define rlpr (_p + 26)
#define _g _p[41]
#define _tsav _p[42]
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
 static double _hoc_d();
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
 "d", _hoc_d,
 "relpr", _hoc_relpr,
 0, 0
};
#define d d_expsyn2b
 extern double d( double );
 /* declare global and static user variables */
#define mg mg_expsyn2b
 double mg = 1.2;
#define sccn sccn_expsyn2b
 double sccn = 5e-05;
#define scca scca_expsyn2b
 double scca = 8e-06;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "scca_expsyn2b", "uS",
 "sccn_expsyn2b", "uS",
 "mg_expsyn2b", "1",
 "delay", "ms",
 "tau1", "ms",
 "tau2", "ms",
 "tau3", "ms",
 "tau4", "ms",
 "e", "mV",
 "i", "nA",
 "g", "uS",
 "gampa", "uS",
 "gnmda", "uS",
 "block", "1",
 "iampa", "nA",
 "inmda", "nA",
 "gmax", "uS",
 "gmax2", "uS",
 "del", "ms",
 "interval", "ms",
 "t0", "ms",
 "g0_ampa", "uS",
 "g0_nmda", "uS",
 0,0
};
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "scca_expsyn2b", &scca_expsyn2b,
 "sccn_expsyn2b", &sccn_expsyn2b,
 "mg_expsyn2b", &mg_expsyn2b,
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
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "6.2.0",
"expsyn2b",
 "delay",
 "tau1",
 "tau2",
 "tau3",
 "tau4",
 "e",
 0,
 "i",
 "g",
 "gampa",
 "gnmda",
 "block",
 "iampa",
 "inmda",
 "gmax",
 "gmax2",
 "pr1",
 "pr2",
 "num",
 "del",
 "interval",
 "t0",
 "g0_ampa",
 "g0_nmda",
 0,
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
 	_p = nrn_prop_data_alloc(_mechtype, 43, _prop);
 	/*initialize range parameters*/
 	delay = 0;
 	tau1 = 0.2;
 	tau2 = 10;
 	tau3 = 3.5;
 	tau4 = 40;
 	e = 1.3827;
  }
 	_prop->param = _p;
 	_prop->param_size = 43;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
 
#define _tqitem &(_ppvar[2]._pvoid)
 static void _net_receive(Point_process*, double*, double);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*f)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _expsyn2b_reg() {
	int _vectorized = 0;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex, 0,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
  hoc_register_prop_size(_mechtype, 43, 3);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 expsyn2b /home/ximi/Projects/ParSims/from_axon/ca1n1-mod/x86_64/expsyn2b.mod\n");
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
 
static void _net_receive (_pnt, _args, _lflag) Point_process* _pnt; double* _args; double _lflag; 
{    _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t;   if (_lflag == 1. ) {*(_tqitem) = 0;}
 {
   if ( _lflag  == 1.0 ) {
     pr1 = rlpr [ ((int) index ) ] ;
     pr2 = scop_random ( ) ;
     printf ( "%s %f %s %f %s %f %s %f\n" , "+++++pr1: " , pr1 , "pr2: " , pr2 , "t0: " , t0 , "index: " , index ) ;
     if ( pr2 > pr1 ) {
       gmax = 1.0 ;
       gmax2 = 1.0 ;
       g0_ampa = gampa ;
       g0_nmda = gnmda ;
       t0 = t ;
       }
     if ( index <= num - 2.0 ) {
       index = index + 1.0 ;
       net_send ( _tqitem, _args, _pnt, t +  interval , 1.0 ) ;
       }
     }
   } }
 
double d (  double _lx ) {
   double _ld;
 if ( _lx < 0.0 ) {
     _ld = 0.0 ;
     }
   else {
     _ld = exp ( - _lx ) ;
     }
   
return _ld;
 }
 
static double _hoc_d(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r =  d (  *getarg(1) );
 return(_r);
}
 
static int  relpr (  ) {
   
/*VERBATIM*/

	FILE *file;
	int size, ind;  //cannot use the var name i, because it refers to NONPSCIFIC ION
	float f;

	file=fopen("relpr.dat", "r");
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

static void initmodel() {
  int _i; double _save;_ninits++;
{
 {
   double _ltp , _ltp2 ;
 _ltp = ( tau1 * tau2 ) / ( tau2 - tau1 ) * log ( tau2 / tau1 ) ;
   _ltp2 = ( tau3 * tau4 ) / ( tau4 - tau3 ) * log ( tau4 / tau3 ) ;
   factor = exp ( - _ltp / tau2 ) - exp ( - _ltp / tau1 ) ;
   factor2 = exp ( - _ltp2 / tau4 ) - exp ( - _ltp2 / tau3 ) ;
   factor = 1.0 / factor ;
   factor2 = 1.0 / factor2 ;
   index = 0.0 ;
   gmax = 0.0 ;
   gmax2 = 0.0 ;
   t0 = del ;
   g0_ampa = 0.0 ;
   g0_nmda = 0.0 ;
   relpr ( _threadargs_ ) ;
   if ( index < num ) {
     net_send ( _tqitem, (double*)0, _ppvar[1]._pvoid, t +  del , 1.0 ) ;
     }
   }

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
   if ( gmax ) {
     at_time ( nrn_threads, delay ) ;
     }
    block = 8.8 * exp ( v / 12.5 ) / ( mg + 8.8 * exp ( v / 12.5 ) ) ;
    gampa = gmax * factor * ( d ( _threadargscomma_ ( t - t0 ) / tau2 ) - d ( _threadargscomma_ ( t - t0 ) / tau1 ) ) + g0_ampa ;
   gnmda = gmax2 * block * factor2 * ( d ( _threadargscomma_ ( t - t0 ) / tau4 ) - d ( _threadargscomma_ ( t - t0 ) / tau3 ) ) + g0_nmda ;
   g = gampa + gnmda ;
   iampa = gampa * ( v - e ) ;
   inmda = gnmda * ( v - e ) ;
   i = iampa + inmda ;
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

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}
