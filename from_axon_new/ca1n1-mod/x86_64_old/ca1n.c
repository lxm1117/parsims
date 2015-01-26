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
#define gnafbar _p[0]
#define gkDRfbar _p[1]
#define gkDRsbar _p[2]
#define gkAbar _p[3]
#define gcaLbar _p[4]
#define gcaTbar _p[5]
#define gcaNbar _p[6]
#define gcaRbar _p[7]
#define gBKbar _p[8]
#define gSKbar _p[9]
#define gkMbar _p[10]
#define gkDbar _p[11]
#define gnapbar _p[12]
#define gkAHPbar _p[13]
#define gcaLbarsp _p[14]
#define gcaTbarsp _p[15]
#define gcaNbarsp _p[16]
#define gcaRbarsp _p[17]
#define icasp _p[18]
#define inaf _p[19]
#define inap _p[20]
#define ikDRf _p[21]
#define ikDRs _p[22]
#define ikA _p[23]
#define icaL _p[24]
#define icaN _p[25]
#define icaT _p[26]
#define icaR _p[27]
#define icaLsp _p[28]
#define icaNsp _p[29]
#define icaTsp _p[30]
#define icaRsp _p[31]
#define iBK _p[32]
#define iSK _p[33]
#define ikM _p[34]
#define ikD _p[35]
#define ikAHP _p[36]
#define itot _p[37]
#define gna _p[38]
#define gnaf _p[39]
#define gnap _p[40]
#define gkDRf _p[41]
#define gkDRs _p[42]
#define gkA _p[43]
#define gcaL _p[44]
#define gcaT _p[45]
#define gcaN _p[46]
#define gcaR _p[47]
#define gcaLsp _p[48]
#define gcaTsp _p[49]
#define gcaNsp _p[50]
#define gcaRsp _p[51]
#define gBK _p[52]
#define gSK _p[53]
#define gkM _p[54]
#define gkD _p[55]
#define gkAHP _p[56]
#define gk _p[57]
#define gca _p[58]
#define gcasp _p[59]
#define gtot _p[60]
#define m _p[61]
#define h _p[62]
#define a _p[63]
#define b _p[64]
#define n _p[65]
#define ns _p[66]
#define nsh _p[67]
#define l _p[68]
#define ta _p[69]
#define ti _p[70]
#define nna _p[71]
#define nni _p[72]
#define r _p[73]
#define s _p[74]
#define ba _p[75]
#define bb _p[76]
#define bz _p[77]
#define sa _p[78]
#define ma _p[79]
#define aa _p[80]
#define da _p[81]
#define db _p[82]
#define pm _p[83]
#define ena _p[84]
#define eca _p[85]
#define ek _p[86]
#define Dm _p[87]
#define Dh _p[88]
#define Da _p[89]
#define Db _p[90]
#define Dn _p[91]
#define Dns _p[92]
#define Dnsh _p[93]
#define Dl _p[94]
#define Dta _p[95]
#define Dti _p[96]
#define Dnna _p[97]
#define Dnni _p[98]
#define Dr _p[99]
#define Ds _p[100]
#define Dba _p[101]
#define Dbb _p[102]
#define Dbz _p[103]
#define Dsa _p[104]
#define Dma _p[105]
#define Daa _p[106]
#define Dda _p[107]
#define Ddb _p[108]
#define Dpm _p[109]
#define ik _p[110]
#define ica _p[111]
#define ina _p[112]
#define cai _p[113]
#define _g _p[114]
#define _ion_ena	*_ppvar[0]._pval
#define _ion_ina	*_ppvar[1]._pval
#define _ion_dinadv	*_ppvar[2]._pval
#define _ion_ek	*_ppvar[3]._pval
#define _ion_ik	*_ppvar[4]._pval
#define _ion_dikdv	*_ppvar[5]._pval
#define _ion_eca	*_ppvar[6]._pval
#define _ion_cai	*_ppvar[7]._pval
#define _ion_ica	*_ppvar[8]._pval
#define _ion_dicadv	*_ppvar[9]._pval
 
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
 "setdata_ca1n", _hoc_setdata,
 "rates_ca1n", _hoc_rates,
 "vtrap_ca1n", _hoc_vtrap,
 0, 0
};
#define vtrap vtrap_ca1n
 extern double vtrap();
 /* declare global and static user variables */
#define aatau aatau_ca1n
 double aatau = 0;
#define atau atau_ca1n
 double atau = 0;
#define aainf aainf_ca1n
 double aainf = 0;
#define ainf ainf_ca1n
 double ainf = 0;
#define bztau bztau_ca1n
 double bztau = 0;
#define bbtau bbtau_ca1n
 double bbtau = 0;
#define batau batau_ca1n
 double batau = 0;
#define btau btau_ca1n
 double btau = 0;
#define bzinf bzinf_ca1n
 double bzinf = 0;
#define bbinf bbinf_ca1n
 double bbinf = 0;
#define bainf bainf_ca1n
 double bainf = 0;
#define binf binf_ca1n
 double binf = 0;
#define dbtau dbtau_ca1n
 double dbtau = 0;
#define datau datau_ca1n
 double datau = 0;
#define dbinf dbinf_ca1n
 double dbinf = 0;
#define dainf dainf_ca1n
 double dainf = 0;
#define htau htau_ca1n
 double htau = 0;
#define hinf hinf_ca1n
 double hinf = 0;
#define ltau ltau_ca1n
 double ltau = 0;
#define linf linf_ca1n
 double linf = 0;
#define matau matau_ca1n
 double matau = 0;
#define mtau mtau_ca1n
 double mtau = 0;
#define mainf mainf_ca1n
 double mainf = 0;
#define minf minf_ca1n
 double minf = 0;
#define nitau nitau_ca1n
 double nitau = 0;
#define natau natau_ca1n
 double natau = 0;
#define nshtau nshtau_ca1n
 double nshtau = 0;
#define nstau nstau_ca1n
 double nstau = 0;
#define ntau ntau_ca1n
 double ntau = 0;
#define niinf niinf_ca1n
 double niinf = 0;
#define nainf nainf_ca1n
 double nainf = 0;
#define nshinf nshinf_ca1n
 double nshinf = 0;
#define nsinf nsinf_ca1n
 double nsinf = 0;
#define ninf ninf_ca1n
 double ninf = 0;
#define pmtau pmtau_ca1n
 double pmtau = 0;
#define pminf pminf_ca1n
 double pminf = 0;
#define rtau rtau_ca1n
 double rtau = 0;
#define rinf rinf_ca1n
 double rinf = 0;
#define satau satau_ca1n
 double satau = 0;
#define stau stau_ca1n
 double stau = 0;
#define sainf sainf_ca1n
 double sainf = 0;
#define sinf sinf_ca1n
 double sinf = 0;
#define titau titau_ca1n
 double titau = 0;
#define tatau tatau_ca1n
 double tatau = 0;
#define tiinf tiinf_ca1n
 double tiinf = 0;
#define tainf tainf_ca1n
 double tainf = 0;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gnafbar_ca1n", "mho/cm2",
 "gkDRfbar_ca1n", "mho/cm2",
 "gkDRsbar_ca1n", "mho/cm2",
 "gkAbar_ca1n", "mho/cm2",
 "gcaLbar_ca1n", "mho/cm2",
 "gcaTbar_ca1n", "mho/cm2",
 "gcaNbar_ca1n", "mho/cm2",
 "gcaRbar_ca1n", "mho/cm2",
 "gBKbar_ca1n", "mho/cm2",
 "gSKbar_ca1n", "mho/cm2",
 "gkMbar_ca1n", "mho/cm2",
 "gkDbar_ca1n", "mho/cm2",
 "gnapbar_ca1n", "mho/cm2",
 "gkAHPbar_ca1n", "mho/cm2",
 "gcaLbarsp_ca1n", "mho/cm2",
 "gcaTbarsp_ca1n", "mho/cm2",
 "gcaNbarsp_ca1n", "mho/cm2",
 "gcaRbarsp_ca1n", "mho/cm2",
 "icasp_ca1n", "mA/cm2",
 "inaf_ca1n", "mA/cm2",
 "inap_ca1n", "mA/cm2",
 "ikDRf_ca1n", "mA/cm2",
 "ikDRs_ca1n", "mA/cm2",
 "ikA_ca1n", "mA/cm2",
 "icaL_ca1n", "mA/cm2",
 "icaN_ca1n", "mA/cm2",
 "icaT_ca1n", "mA/cm2",
 "icaR_ca1n", "mA/cm2",
 "icaLsp_ca1n", "mA/cm2",
 "icaNsp_ca1n", "mA/cm2",
 "icaTsp_ca1n", "mA/cm2",
 "icaRsp_ca1n", "mA/cm2",
 "iBK_ca1n", "mA/cm2",
 "iSK_ca1n", "mA/cm2",
 "ikM_ca1n", "mA/cm2",
 "ikD_ca1n", "mA/cm2",
 "ikAHP_ca1n", "mA/cm2",
 "itot_ca1n", "mA/cm2",
 "gna_ca1n", "mho/cm2",
 "gnaf_ca1n", "mho/cm2",
 "gnap_ca1n", "mho/cm2",
 "gkDRf_ca1n", "mho/cm2",
 "gkDRs_ca1n", "mho/cm2",
 "gkA_ca1n", "mho/cm2",
 "gcaL_ca1n", "mho/cm2",
 "gcaT_ca1n", "mho/cm2",
 "gcaN_ca1n", "mho/cm2",
 "gcaR_ca1n", "mho/cm2",
 "gcaLsp_ca1n", "mho/cm2",
 "gcaTsp_ca1n", "mho/cm2",
 "gcaNsp_ca1n", "mho/cm2",
 "gcaRsp_ca1n", "mho/cm2",
 "gBK_ca1n", "mho/cm2",
 "gSK_ca1n", "mho/cm2",
 "gkM_ca1n", "mho/cm2",
 "gkD_ca1n", "mho/cm2",
 "gkAHP_ca1n", "mho/cm2",
 "gk_ca1n", "mho/cm2",
 "gca_ca1n", "mho/cm2",
 "gcasp_ca1n", "mho/cm2",
 "gtot_ca1n", "mho/cm2",
 0,0
};
 static double aa0 = 0;
 static double a0 = 0;
 static double bz0 = 0;
 static double bb0 = 0;
 static double ba0 = 0;
 static double b0 = 0;
 static double delta_t = 0.01;
 static double db0 = 0;
 static double da0 = 0;
 static double h0 = 0;
 static double l0 = 0;
 static double ma0 = 0;
 static double m0 = 0;
 static double nni0 = 0;
 static double nna0 = 0;
 static double nsh0 = 0;
 static double ns0 = 0;
 static double n0 = 0;
 static double pm0 = 0;
 static double r0 = 0;
 static double sa0 = 0;
 static double s0 = 0;
 static double ti0 = 0;
 static double ta0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "minf_ca1n", &minf_ca1n,
 "hinf_ca1n", &hinf_ca1n,
 "ainf_ca1n", &ainf_ca1n,
 "binf_ca1n", &binf_ca1n,
 "ninf_ca1n", &ninf_ca1n,
 "nsinf_ca1n", &nsinf_ca1n,
 "nshinf_ca1n", &nshinf_ca1n,
 "linf_ca1n", &linf_ca1n,
 "nainf_ca1n", &nainf_ca1n,
 "niinf_ca1n", &niinf_ca1n,
 "tainf_ca1n", &tainf_ca1n,
 "tiinf_ca1n", &tiinf_ca1n,
 "rinf_ca1n", &rinf_ca1n,
 "sinf_ca1n", &sinf_ca1n,
 "bainf_ca1n", &bainf_ca1n,
 "bbinf_ca1n", &bbinf_ca1n,
 "bzinf_ca1n", &bzinf_ca1n,
 "sainf_ca1n", &sainf_ca1n,
 "mainf_ca1n", &mainf_ca1n,
 "dainf_ca1n", &dainf_ca1n,
 "dbinf_ca1n", &dbinf_ca1n,
 "aainf_ca1n", &aainf_ca1n,
 "pminf_ca1n", &pminf_ca1n,
 "mtau_ca1n", &mtau_ca1n,
 "htau_ca1n", &htau_ca1n,
 "atau_ca1n", &atau_ca1n,
 "btau_ca1n", &btau_ca1n,
 "ntau_ca1n", &ntau_ca1n,
 "nstau_ca1n", &nstau_ca1n,
 "nshtau_ca1n", &nshtau_ca1n,
 "ltau_ca1n", &ltau_ca1n,
 "natau_ca1n", &natau_ca1n,
 "nitau_ca1n", &nitau_ca1n,
 "tatau_ca1n", &tatau_ca1n,
 "titau_ca1n", &titau_ca1n,
 "rtau_ca1n", &rtau_ca1n,
 "stau_ca1n", &stau_ca1n,
 "batau_ca1n", &batau_ca1n,
 "bbtau_ca1n", &bbtau_ca1n,
 "bztau_ca1n", &bztau_ca1n,
 "satau_ca1n", &satau_ca1n,
 "matau_ca1n", &matau_ca1n,
 "datau_ca1n", &datau_ca1n,
 "dbtau_ca1n", &dbtau_ca1n,
 "aatau_ca1n", &aatau_ca1n,
 "pmtau_ca1n", &pmtau_ca1n,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(), nrn_init(), nrn_state();
 static void nrn_cur(), nrn_jacob();
 
static int _ode_count(), _ode_map(), _ode_spec(), _ode_matsol();
 
#define _cvode_ieq _ppvar[10]._i
 /* connect range variables in _p that hoc is supposed to know about */
 static char *_mechanism[] = {
 "6.2.0",
"ca1n",
 "gnafbar_ca1n",
 "gkDRfbar_ca1n",
 "gkDRsbar_ca1n",
 "gkAbar_ca1n",
 "gcaLbar_ca1n",
 "gcaTbar_ca1n",
 "gcaNbar_ca1n",
 "gcaRbar_ca1n",
 "gBKbar_ca1n",
 "gSKbar_ca1n",
 "gkMbar_ca1n",
 "gkDbar_ca1n",
 "gnapbar_ca1n",
 "gkAHPbar_ca1n",
 "gcaLbarsp_ca1n",
 "gcaTbarsp_ca1n",
 "gcaNbarsp_ca1n",
 "gcaRbarsp_ca1n",
 0,
 "icasp_ca1n",
 "inaf_ca1n",
 "inap_ca1n",
 "ikDRf_ca1n",
 "ikDRs_ca1n",
 "ikA_ca1n",
 "icaL_ca1n",
 "icaN_ca1n",
 "icaT_ca1n",
 "icaR_ca1n",
 "icaLsp_ca1n",
 "icaNsp_ca1n",
 "icaTsp_ca1n",
 "icaRsp_ca1n",
 "iBK_ca1n",
 "iSK_ca1n",
 "ikM_ca1n",
 "ikD_ca1n",
 "ikAHP_ca1n",
 "itot_ca1n",
 "gna_ca1n",
 "gnaf_ca1n",
 "gnap_ca1n",
 "gkDRf_ca1n",
 "gkDRs_ca1n",
 "gkA_ca1n",
 "gcaL_ca1n",
 "gcaT_ca1n",
 "gcaN_ca1n",
 "gcaR_ca1n",
 "gcaLsp_ca1n",
 "gcaTsp_ca1n",
 "gcaNsp_ca1n",
 "gcaRsp_ca1n",
 "gBK_ca1n",
 "gSK_ca1n",
 "gkM_ca1n",
 "gkD_ca1n",
 "gkAHP_ca1n",
 "gk_ca1n",
 "gca_ca1n",
 "gcasp_ca1n",
 "gtot_ca1n",
 0,
 "m_ca1n",
 "h_ca1n",
 "a_ca1n",
 "b_ca1n",
 "n_ca1n",
 "ns_ca1n",
 "nsh_ca1n",
 "l_ca1n",
 "ta_ca1n",
 "ti_ca1n",
 "nna_ca1n",
 "nni_ca1n",
 "r_ca1n",
 "s_ca1n",
 "ba_ca1n",
 "bb_ca1n",
 "bz_ca1n",
 "sa_ca1n",
 "ma_ca1n",
 "aa_ca1n",
 "da_ca1n",
 "db_ca1n",
 "pm_ca1n",
 0,
 0};
 static Symbol* _na_sym;
 static Symbol* _k_sym;
 static Symbol* _ca_sym;
 
static void nrn_alloc(_prop)
	Prop *_prop;
{
	Prop *prop_ion, *need_memb();
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 115, _prop);
 	/*initialize range parameters*/
 	gnafbar = 0;
 	gkDRfbar = 0;
 	gkDRsbar = 0;
 	gkAbar = 0;
 	gcaLbar = 0;
 	gcaTbar = 0;
 	gcaNbar = 0;
 	gcaRbar = 0;
 	gBKbar = 0;
 	gSKbar = 0;
 	gkMbar = 0;
 	gkDbar = 0;
 	gnapbar = 0;
 	gkAHPbar = 0;
 	gcaLbarsp = 0;
 	gcaTbarsp = 0;
 	gcaNbarsp = 0;
 	gcaRbarsp = 0;
 	_prop->param = _p;
 	_prop->param_size = 115;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 11, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_na_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0]._pval = &prop_ion->param[0]; /* ena */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ina */
 	_ppvar[2]._pval = &prop_ion->param[4]; /* _ion_dinadv */
 prop_ion = need_memb(_k_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[3]._pval = &prop_ion->param[0]; /* ek */
 	_ppvar[4]._pval = &prop_ion->param[3]; /* ik */
 	_ppvar[5]._pval = &prop_ion->param[4]; /* _ion_dikdv */
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 1, 1);
 	_ppvar[6]._pval = &prop_ion->param[0]; /* eca */
 	_ppvar[7]._pval = &prop_ion->param[1]; /* cai */
 	_ppvar[8]._pval = &prop_ion->param[3]; /* ica */
 	_ppvar[9]._pval = &prop_ion->param[4]; /* _ion_dicadv */
 
}
 static _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _update_ion_pointer(Datum*);
 _ca1n_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("na", -10000.);
 	ion_reg("k", -10000.);
 	ion_reg("ca", -10000.);
 	_na_sym = hoc_lookup("na_ion");
 	_k_sym = hoc_lookup("k_ion");
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
  hoc_register_dparam_size(_mechtype, 11);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 ca1n /home/ximi/Documents/from_axon/ca1n1-mod/x86_64/ca1n.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "ca1n.mod Conductances for CA1 cells (version new)";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static _modl_cleanup(){ _match_recurse=1;}
static rates();
 
static int _ode_spec1(), _ode_matsol1();
 static int _slist1[23], _dlist1[23];
 static int states();
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   rates ( _threadargscomma_ v ) ;
   Dm = ( minf - m ) / mtau ;
   Dh = ( hinf - h ) / htau ;
   Dpm = ( pminf - pm ) / pmtau ;
   Dn = ( ninf - n ) / ntau ;
   Dns = ( nsinf - ns ) / nstau ;
   Dnsh = ( nshinf - nsh ) / nshtau ;
   Da = ( ainf - a ) / atau ;
   Db = ( binf - b ) / btau ;
   Dl = ( linf - l ) / ltau ;
   Dta = ( tainf - ta ) / tatau ;
   Dti = ( tiinf - ti ) / titau ;
   Dnna = ( nainf - nna ) / natau ;
   Dnni = ( niinf - nni ) / nitau ;
   Dr = ( rinf - r ) / rtau ;
   Ds = ( sinf - s ) / stau ;
   Dba = ( bainf - ba ) / batau ;
   Dbb = ( bbinf - bb ) / bbtau ;
   Dbz = ( bzinf - bz ) / bztau ;
   Dsa = ( sainf - sa ) / satau ;
   Dma = ( mainf - ma ) / matau ;
   Dda = ( dainf - da ) / datau ;
   Ddb = ( dbinf - db ) / dbtau ;
   Daa = ( aainf - aa ) / aatau ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 rates ( _threadargscomma_ v ) ;
 Dm = Dm  / (1. - dt*( ( ( ( - 1.0 ) ) ) / mtau )) ;
 Dh = Dh  / (1. - dt*( ( ( ( - 1.0 ) ) ) / htau )) ;
 Dpm = Dpm  / (1. - dt*( ( ( ( - 1.0 ) ) ) / pmtau )) ;
 Dn = Dn  / (1. - dt*( ( ( ( - 1.0 ) ) ) / ntau )) ;
 Dns = Dns  / (1. - dt*( ( ( ( - 1.0 ) ) ) / nstau )) ;
 Dnsh = Dnsh  / (1. - dt*( ( ( ( - 1.0 ) ) ) / nshtau )) ;
 Da = Da  / (1. - dt*( ( ( ( - 1.0 ) ) ) / atau )) ;
 Db = Db  / (1. - dt*( ( ( ( - 1.0 ) ) ) / btau )) ;
 Dl = Dl  / (1. - dt*( ( ( ( - 1.0 ) ) ) / ltau )) ;
 Dta = Dta  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tatau )) ;
 Dti = Dti  / (1. - dt*( ( ( ( - 1.0 ) ) ) / titau )) ;
 Dnna = Dnna  / (1. - dt*( ( ( ( - 1.0 ) ) ) / natau )) ;
 Dnni = Dnni  / (1. - dt*( ( ( ( - 1.0 ) ) ) / nitau )) ;
 Dr = Dr  / (1. - dt*( ( ( ( - 1.0 ) ) ) / rtau )) ;
 Ds = Ds  / (1. - dt*( ( ( ( - 1.0 ) ) ) / stau )) ;
 Dba = Dba  / (1. - dt*( ( ( ( - 1.0 ) ) ) / batau )) ;
 Dbb = Dbb  / (1. - dt*( ( ( ( - 1.0 ) ) ) / bbtau )) ;
 Dbz = Dbz  / (1. - dt*( ( ( ( - 1.0 ) ) ) / bztau )) ;
 Dsa = Dsa  / (1. - dt*( ( ( ( - 1.0 ) ) ) / satau )) ;
 Dma = Dma  / (1. - dt*( ( ( ( - 1.0 ) ) ) / matau )) ;
 Dda = Dda  / (1. - dt*( ( ( ( - 1.0 ) ) ) / datau )) ;
 Ddb = Ddb  / (1. - dt*( ( ( ( - 1.0 ) ) ) / dbtau )) ;
 Daa = Daa  / (1. - dt*( ( ( ( - 1.0 ) ) ) / aatau )) ;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   rates ( _threadargscomma_ v ) ;
    m = m + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / mtau)))*(- ( ( ( minf ) ) / mtau ) / ( ( ( ( - 1.0) ) ) / mtau ) - m) ;
    h = h + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / htau)))*(- ( ( ( hinf ) ) / htau ) / ( ( ( ( - 1.0) ) ) / htau ) - h) ;
    pm = pm + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / pmtau)))*(- ( ( ( pminf ) ) / pmtau ) / ( ( ( ( - 1.0) ) ) / pmtau ) - pm) ;
    n = n + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / ntau)))*(- ( ( ( ninf ) ) / ntau ) / ( ( ( ( - 1.0) ) ) / ntau ) - n) ;
    ns = ns + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / nstau)))*(- ( ( ( nsinf ) ) / nstau ) / ( ( ( ( - 1.0) ) ) / nstau ) - ns) ;
    nsh = nsh + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / nshtau)))*(- ( ( ( nshinf ) ) / nshtau ) / ( ( ( ( - 1.0) ) ) / nshtau ) - nsh) ;
    a = a + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / atau)))*(- ( ( ( ainf ) ) / atau ) / ( ( ( ( - 1.0) ) ) / atau ) - a) ;
    b = b + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / btau)))*(- ( ( ( binf ) ) / btau ) / ( ( ( ( - 1.0) ) ) / btau ) - b) ;
    l = l + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / ltau)))*(- ( ( ( linf ) ) / ltau ) / ( ( ( ( - 1.0) ) ) / ltau ) - l) ;
    ta = ta + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tatau)))*(- ( ( ( tainf ) ) / tatau ) / ( ( ( ( - 1.0) ) ) / tatau ) - ta) ;
    ti = ti + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / titau)))*(- ( ( ( tiinf ) ) / titau ) / ( ( ( ( - 1.0) ) ) / titau ) - ti) ;
    nna = nna + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / natau)))*(- ( ( ( nainf ) ) / natau ) / ( ( ( ( - 1.0) ) ) / natau ) - nna) ;
    nni = nni + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / nitau)))*(- ( ( ( niinf ) ) / nitau ) / ( ( ( ( - 1.0) ) ) / nitau ) - nni) ;
    r = r + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / rtau)))*(- ( ( ( rinf ) ) / rtau ) / ( ( ( ( - 1.0) ) ) / rtau ) - r) ;
    s = s + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / stau)))*(- ( ( ( sinf ) ) / stau ) / ( ( ( ( - 1.0) ) ) / stau ) - s) ;
    ba = ba + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / batau)))*(- ( ( ( bainf ) ) / batau ) / ( ( ( ( - 1.0) ) ) / batau ) - ba) ;
    bb = bb + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / bbtau)))*(- ( ( ( bbinf ) ) / bbtau ) / ( ( ( ( - 1.0) ) ) / bbtau ) - bb) ;
    bz = bz + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / bztau)))*(- ( ( ( bzinf ) ) / bztau ) / ( ( ( ( - 1.0) ) ) / bztau ) - bz) ;
    sa = sa + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / satau)))*(- ( ( ( sainf ) ) / satau ) / ( ( ( ( - 1.0) ) ) / satau ) - sa) ;
    ma = ma + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / matau)))*(- ( ( ( mainf ) ) / matau ) / ( ( ( ( - 1.0) ) ) / matau ) - ma) ;
    da = da + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / datau)))*(- ( ( ( dainf ) ) / datau ) / ( ( ( ( - 1.0) ) ) / datau ) - da) ;
    db = db + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / dbtau)))*(- ( ( ( dbinf ) ) / dbtau ) / ( ( ( ( - 1.0) ) ) / dbtau ) - db) ;
    aa = aa + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / aatau)))*(- ( ( ( aainf ) ) / aatau ) / ( ( ( ( - 1.0) ) ) / aatau ) - aa) ;
   }
  return 0;
}
 
static int  rates (  _lv )  
	double _lv ;
 {
   double _lq10 , _lalpha , _lbeta ;
 _lalpha = - 0.3 * vtrap ( _threadargscomma_ ( _lv + 50.0 ) , - 3.0 ) ;
   _lbeta = 0.3 * vtrap ( _threadargscomma_ ( _lv + 22.0 ) , 3.0 ) ;
   mtau = 1.0 / ( _lalpha + _lbeta ) ;
   minf = _lalpha * mtau ;
   _lalpha = 0.83 * 1.6 * exp ( - ( _lv + 87.0 ) / 12.0 ) ;
   _lbeta = 1.33 * 1.6 / ( 1.0 + exp ( ( _lv + 34.5 ) / - 8.0 ) ) ;
   htau = 1.0 / ( _lalpha + _lbeta ) ;
   hinf = _lalpha * htau ;
   pmtau = 0.8 ;
   pminf = 1.0 / ( 1.0 + exp ( - ( _lv + 50.0 ) / 3.0 ) ) ;
   _lalpha = - 0.07 * vtrap ( _threadargscomma_ ( _lv + 16.0 ) , - 7.0 ) ;
   _lbeta = 0.264 * exp ( - ( _lv + 41.0 ) / 30.0 ) ;
   ntau = 1.0 / ( _lalpha + _lbeta ) ;
   ninf = _lalpha * ntau ;
   _lalpha = - 0.056 * 0.1 * vtrap ( _threadargscomma_ ( _lv - 4.0 ) , - 20.0 ) ;
   _lbeta = 0.2112 * 0.1 * exp ( - ( _lv + 11.0 ) / 30.0 ) ;
   nstau = 1.0 / ( _lalpha + _lbeta ) ;
   nsinf = _lalpha * nstau ;
   _lalpha = .00014 * ( exp ( - ( _lv + 40.0 ) / 20.0 ) + .3 ) ;
   _lbeta = .00025 / ( 1.0 + exp ( - ( _lv + 16.0 ) / 30.0 ) ) ;
   nshtau = 1.0 / ( _lalpha + _lbeta ) ;
   nshinf = _lalpha * nshtau ;
   _lalpha = - .05 * vtrap ( _threadargscomma_ ( _lv + 31.3 ) , - 20.0 ) ;
   _lbeta = .05 * vtrap ( _threadargscomma_ ( _lv + 31.3 ) , 20.0 ) ;
   atau = 1.0 / ( _lalpha + _lbeta ) ;
   ainf = _lalpha * atau ;
   _lalpha = .01 * vtrap ( _threadargscomma_ ( _lv + 58.0 ) , 8.2 ) ;
   _lbeta = - .01 * vtrap ( _threadargscomma_ ( _lv + 58.0 ) , - 8.2 ) ;
   binf = _lalpha / ( _lalpha + _lbeta ) ;
   btau = 10.0 ;
   if ( _lv > - 20.0 ) {
     btau = 10.0 + 2.6 * ( _lv + 20.0 ) / 10.0 ;
     }
   _lalpha = - 15.69 * vtrap ( _threadargscomma_ ( _lv - 81.5 ) , - 10.0 ) ;
   _lbeta = 0.29 * exp ( - _lv / 10.86 ) ;
   ltau = 1.0 / ( _lalpha + _lbeta ) ;
   linf = _lalpha * ltau ;
   _lalpha = - 0.026 * vtrap ( _threadargscomma_ ( _lv + 29.0 ) , - 4.1 ) ;
   _lbeta = _lalpha * exp ( - ( _lv + 31.0 ) / 6.5 ) + 0.9 * exp ( - ( _lv + 120.0 ) / 18.4 ) ;
   tatau = 1.0 / ( _lalpha + _lbeta ) ;
   tainf = _lalpha * tatau ;
   _lalpha = 7e-5 * vtrap ( _threadargscomma_ ( _lv + 45.0 ) , 3.0 ) ;
   _lbeta = 0.034 / ( 1.0 + exp ( - ( _lv + 52.0 ) / 8.6 ) ) ;
   titau = 1.0 / ( _lalpha + _lbeta ) ;
   tiinf = _lalpha * titau ;
   _lalpha = - 0.19 * vtrap ( _threadargscomma_ ( _lv - 19.88 ) , - 10.0 ) ;
   _lbeta = 0.046 * exp ( - _lv / 20.73 ) ;
   natau = 1.0 / ( _lalpha + _lbeta ) ;
   nainf = _lalpha * natau ;
   _lalpha = 1e-4 * ( _lv + 150.0 ) / ( 1.0 + exp ( ( _lv + 70.0 ) / 12.5 ) ) ;
   _lbeta = 1e-4 * ( _lv + 150.0 ) / ( 1.0 + exp ( - ( _lv + 70.0 ) / 12.5 ) ) ;
   nitau = 1.0 / ( _lalpha + _lbeta ) ;
   niinf = _lalpha * nitau ;
   rtau = 100.0 * exp ( - ( _lv + 120.0 ) / 30.0 ) ;
   rinf = 1.0 / ( 1.0 + exp ( - ( _lv + 17.2 ) / 6.8 ) ) ;
   _lalpha = 0.0098 / ( 1.0 + exp ( ( _lv + 59.0 ) / 12.2 ) ) ;
   _lbeta = _lalpha * exp ( ( _lv + 60.0 ) / 11.0 ) ;
   stau = 1.0 / ( _lalpha + _lbeta ) ;
   sinf = 1.0 / ( 1.0 + exp ( ( _lv + 70.3 ) / 12.9 ) ) ;
   bainf = 1. / ( 1.0 + exp ( - ( _lv + 7.3 ) / 17.0 ) ) ;
   batau = .5 ;
   bbinf = 1. / ( 1.0 + exp ( ( _lv + 50.0 ) / 17.0 ) ) ;
   bbtau = 10.0 ;
   bzinf = cai * cai * 1e6 / ( 4.0 + cai * cai * 1e6 ) ;
   bztau = 10.0 ;
   satau = 30.0 / ( 0.01 + cai * 1e3 ) ;
   sainf = pow( ( cai * 1e3 ) , 4.0 ) / ( pow( ( cai * 1e3 ) , 4.0 ) + pow( ( .56 ) , 4.0 ) ) ;
   aatau = 500.0 / ( 0.01 + cai * 1e3 ) ;
   aainf = pow( ( cai * 1e3 ) , 4.0 ) / ( pow( ( cai * 1e3 ) , 4.0 ) + pow( ( .56 ) , 4.0 ) ) ;
   _lalpha = .015 * exp ( 0.7 * 3.6 * ( _lv + 45.0 ) / 26.73 ) ;
   _lbeta = 0.015 * exp ( - 0.7 * 2.4 * ( _lv + 45.0 ) / 26.73 ) ;
   matau = 1.0 / ( _lalpha + _lbeta ) ;
   mainf = _lalpha * matau ;
   matau = matau + 8.0 ;
   _lalpha = 1.0 ;
   _lbeta = exp ( - 3.0 * ( _lv + 58.0 ) / 26.73 ) ;
   datau = 1.0 / ( _lalpha + _lbeta ) ;
   dainf = _lalpha * datau ;
   datau = datau + 1.0 ;
   _lalpha = .0002 ;
   _lbeta = .0002 * exp ( 2.5 * ( _lv + 73.0 ) / 26.73 ) ;
   dbtau = 1.0 / ( _lalpha + _lbeta ) ;
   dbinf = _lalpha * dbtau ;
   dbtau = dbtau + 500.0 ;
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
 
static int _ode_count(_type) int _type;{ return 23;}
 
static int _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ena = _ion_ena;
  ek = _ion_ek;
  eca = _ion_eca;
  cai = _ion_cai;
     _ode_spec1 ();
    }}
 
static int _ode_map(_ieq, _pv, _pvdot, _pp, _ppd, _atol, _type) int _ieq, _type; double** _pv, **_pvdot, *_pp, *_atol; Datum* _ppd; { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 23; ++_i) {
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
  ena = _ion_ena;
  ek = _ion_ek;
  eca = _ion_eca;
  cai = _ion_cai;
 _ode_matsol1 ();
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_na_sym, _ppvar, 0, 0);
   nrn_update_ion_pointer(_na_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_na_sym, _ppvar, 2, 4);
   nrn_update_ion_pointer(_k_sym, _ppvar, 3, 0);
   nrn_update_ion_pointer(_k_sym, _ppvar, 4, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 5, 4);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 6, 0);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 7, 1);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 8, 3);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 9, 4);
 }

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  aa = aa0;
  a = a0;
  bz = bz0;
  bb = bb0;
  ba = ba0;
  b = b0;
  db = db0;
  da = da0;
  h = h0;
  l = l0;
  ma = ma0;
  m = m0;
  nni = nni0;
  nna = nna0;
  nsh = nsh0;
  ns = ns0;
  n = n0;
  pm = pm0;
  r = r0;
  sa = sa0;
  s = s0;
  ti = ti0;
  ta = ta0;
 {
   bbinf = 1.0 ;
   rates ( _threadargscomma_ v ) ;
   m = minf ;
   h = hinf ;
   n = ninf ;
   ns = nsinf ;
   nsh = nshinf ;
   a = ainf ;
   b = binf ;
   l = linf ;
   ta = tainf ;
   ti = tiinf ;
   nna = nainf ;
   nni = niinf ;
   r = rinf ;
   s = sinf ;
   ba = bainf ;
   bz = bzinf ;
   bb = bbinf ;
   sa = sainf ;
   ma = mainf ;
   da = dainf ;
   db = dbinf ;
   aa = aainf ;
   pm = pminf ;
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
  ek = _ion_ek;
  eca = _ion_eca;
  cai = _ion_cai;
 initmodel();
   }}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   gnaf = gnafbar * m * m * m * h ;
   inaf = gnaf * ( v - ena ) ;
   gnap = gnapbar * pm ;
   inap = gnap * ( v - ena ) ;
   gkDRf = gkDRfbar * n * n * n * n ;
   ikDRf = gkDRf * ( v - ek ) ;
   gkDRs = gkDRsbar * ns * ns * ns * ns * nsh ;
   ikDRs = gkDRs * ( v - ek ) ;
   gkA = gkAbar * a * a * a * a * b ;
   ikA = gkA * ( v - ek ) ;
   gcaL = gcaLbar * l * l ;
   icaL = gcaL * ( v - eca ) ;
   gcaN = gcaNbar * nna * nna * nni ;
   icaN = gcaN * ( v - eca ) ;
   gcaT = gcaTbar * ta * ti ;
   icaT = gcaT * ( v - eca ) ;
   gcaR = gcaRbar * r * r * r * r * s ;
   icaR = gcaR * ( v - eca ) ;
   gcaLsp = gcaLbarsp * l * l ;
   icaLsp = gcaLsp * ( v - eca ) ;
   gcaNsp = gcaNbarsp * nna * nna * nni ;
   icaNsp = gcaNsp * ( v - eca ) ;
   gcaTsp = gcaTbarsp * ta * ti ;
   icaTsp = gcaTsp * ( v - eca ) ;
   gcaRsp = gcaRbarsp * r * r * r * r * s ;
   icaRsp = gcaRsp * ( v - eca ) ;
   gBK = gBKbar * ba * bb * bz ;
   iBK = gBK * ( v - ek ) ;
   gSK = gSKbar * sa ;
   iSK = gSK * ( v - ek ) ;
   gkAHP = gkAHPbar * aa ;
   ikAHP = gkAHP * ( v - ek ) ;
   gkM = gkMbar * ma * ma ;
   ikM = gkM * ( v - ek ) ;
   gkD = gkDbar * da * da * da * da * db * db * db * db ;
   ikD = gkD * ( v - ek ) ;
   gna = gnaf + gnap ;
   ina = inaf + inap ;
   gk = gkDRf + gkDRs + gkA + gBK + gSK + gkM + gkD + gkAHP ;
   ik = ikDRf + ikDRs + ikA + iBK + iSK + ikM + ikD + ikAHP ;
   gca = gcaL + gcaN + gcaT + gcaR ;
   gcasp = gcaLsp + gcaNsp + gcaTsp + gcaRsp ;
   ica = icaL + icaN + icaT + icaR ;
   icasp = icaLsp + icaNsp + icaTsp + icaRsp ;
   gtot = gk + gca + gna + gcasp ;
   itot = ik + ica + ina + icasp ;
   }
 _current += ina;
 _current += ik;
 _current += ica;
 _current += icasp;

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
  ek = _ion_ek;
  eca = _ion_eca;
  cai = _ion_cai;
 _g = _nrn_current(_v + .001);
 	{ double _dica;
 double _dik;
 double _dina;
  _dina = ina;
  _dik = ik;
  _dica = ica;
 _rhs = _nrn_current(_v);
  _ion_dinadv += (_dina - ina)/.001 ;
  _ion_dikdv += (_dik - ik)/.001 ;
  _ion_dicadv += (_dica - ica)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ina += ina ;
  _ion_ik += ik ;
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
  ena = _ion_ena;
  ek = _ion_ek;
  eca = _ion_eca;
  cai = _ion_cai;
 { {
 for (; t < _break; t += dt) {
 error =  states();
 if(error){fprintf(stderr,"at line 158 in file ca1n.mod:\n        SOLVE states METHOD cnexp \n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
 }   }}

}

static terminal(){}

static _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(m) - _p;  _dlist1[0] = &(Dm) - _p;
 _slist1[1] = &(h) - _p;  _dlist1[1] = &(Dh) - _p;
 _slist1[2] = &(pm) - _p;  _dlist1[2] = &(Dpm) - _p;
 _slist1[3] = &(n) - _p;  _dlist1[3] = &(Dn) - _p;
 _slist1[4] = &(ns) - _p;  _dlist1[4] = &(Dns) - _p;
 _slist1[5] = &(nsh) - _p;  _dlist1[5] = &(Dnsh) - _p;
 _slist1[6] = &(a) - _p;  _dlist1[6] = &(Da) - _p;
 _slist1[7] = &(b) - _p;  _dlist1[7] = &(Db) - _p;
 _slist1[8] = &(l) - _p;  _dlist1[8] = &(Dl) - _p;
 _slist1[9] = &(ta) - _p;  _dlist1[9] = &(Dta) - _p;
 _slist1[10] = &(ti) - _p;  _dlist1[10] = &(Dti) - _p;
 _slist1[11] = &(nna) - _p;  _dlist1[11] = &(Dnna) - _p;
 _slist1[12] = &(nni) - _p;  _dlist1[12] = &(Dnni) - _p;
 _slist1[13] = &(r) - _p;  _dlist1[13] = &(Dr) - _p;
 _slist1[14] = &(s) - _p;  _dlist1[14] = &(Ds) - _p;
 _slist1[15] = &(ba) - _p;  _dlist1[15] = &(Dba) - _p;
 _slist1[16] = &(bb) - _p;  _dlist1[16] = &(Dbb) - _p;
 _slist1[17] = &(bz) - _p;  _dlist1[17] = &(Dbz) - _p;
 _slist1[18] = &(sa) - _p;  _dlist1[18] = &(Dsa) - _p;
 _slist1[19] = &(ma) - _p;  _dlist1[19] = &(Dma) - _p;
 _slist1[20] = &(da) - _p;  _dlist1[20] = &(Dda) - _p;
 _slist1[21] = &(db) - _p;  _dlist1[21] = &(Ddb) - _p;
 _slist1[22] = &(aa) - _p;  _dlist1[22] = &(Daa) - _p;
_first = 0;
}
