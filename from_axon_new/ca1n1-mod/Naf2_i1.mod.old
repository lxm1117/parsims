TITLE Naf2 channel
: 05Apr10  modified to add Nav1.6 channel with similar properties to Naf
:
:
: Apr08 Added a third particle s for slow inactivation
:	sfrac is the gbar fraction to assign to s particle
:	ie, g = gbar*n^n_gates*h*(1-sfrac) + gbar*n^n_gates*h*s*sfrac	
:
: Jose Ambros-Ingerson jose@kiubo.net 2006

NEURON {
  SUFFIX 	Naf2_i1
  USEION 	na READ ena WRITE ina
  RANGE		gbar, g, i, sfrac, gbar16, g2, sfrac2

  GLOBAL 	inf_n, tau_n, inf_h, tau_h, inf_s, tau_s
  GLOBAL 	inf_n2, tau_n2, inf_h2, tau_h2, inf_s2, tau_s2
}

PARAMETER {
  ena 			(mV)
  gbar		= 1000 	(pS/um2)
  gbar16	= 2500 	(pS/um2)
  sfrac		= 0		: fraction (0<=x<=1) with slow inactivation; 0=> no s effect
  sfrac2	= 0		: fraction (0<=x<=1) with slow inactivation; 0=> no s effect

  : inf_n parameters
  gates_n	= 3
  vhalf_n	= -30	(mV)	
  slope_n	= -7	(mV)
  needAdj	= 1
  vhalfA_n 	= 0 (mV)		: adjusted for ngate power; Set in ngate_adjust()
  slopeA_n	= 0 (mV)
  v5_adj	= 0			: for return values in ngate_adjust
  slp_adj	= 0

  : inf_n2 parameters
:  gates_n	= 3   			same as for n
  vhalfD_n2	= -10	(mV)		: Vhalf is less depolarized than for n	
:  slope_n	= -7	(mV)		: slope same as for n
:  needAdj	= 1			: defined as for n
  vhalfA_n2 	= 0 (mV)		: adjusted for ngate power; Set in ngate_adjust()
  slopeA_n2	= 0 (mV)
  v5_adj2	= 0			: for return values in ngate_adjust
  slp_adj2	= 0

  : tau_n parameters
  tauA_n	= 0.5 	(ms)
  tauDv_n	= 0	(mV)	: Delta to vhalf_n
  tauG_n	= 0.5		: Left-right bias. range is (0,1)
  tauF_n	= 0		: Up-Down bias. range is ~ -3.5(cup-shape), -3(flat), 0(from k), 1(sharper)
  tau0_n	= 0.001	(ms)	: minimum tau

  : inf_h parameters
  vhalfD_h	= -40   (mV)	:  vhalf_h = vhalf_n + vhalfD_h; 
  slope_h	= 8	(mV)

  : inf_h2 parameters
  vhalfD_h2	= -40   (mV)	:  vhalf_h2 = vhalf_n + vhalfD_n + vhalfD_h2; 
:  slope_h	= 8	(mV)	:  same slope

  : tau_h parameters
  tauA_h	= 20 	(ms)
  tauDv_h	= 0	(mV)	: Delta to vhalf_h
  tauG_h	= 0.5		: Left-right bias. range is (0,1)
  tauF_h	= 0		: Up-Down bias. range is ~ -3.5(cup-shape), -3(flat), 0(from k), 1(sharper)
  tau0_h	= 0.01	(ms)	: minimum tau

  : inf_s parameters
  vhalfD_s	= -40   (mV)	:  vhalf_s = vhalf_n + vhalfD_s; 
  slope_s	= 8	(mV)

  : inf_s parameters
  vhalfD_s2	= -40   (mV)	:  vhalf_s2 = vhalf_n2 + vhalfD_s2; 
:  slope_s	= 8	(mV)

  : tau_s parameters
  tauA_s	= 2000 	(ms)
  tauDv_s	= 0	(mV)	: Delta to vhalf_s
  tauG_s	= 0.5		: Left-right bias. range is (0,1)
  tauF_s	= 0		: Up-Down bias. range is ~ -3.5(cup-shape), -3(flat), 0(from k), 1(sharper)
  tau0_s	= 0.01	(ms)	: minimum tau
}

STATE {
  n	: activation
  h	: inactivation
  s	: slow inactivation
  n2	: activation nav 1.6
  h2	: inacivation nav 1.6
  s2	: slow inactivation
}

ASSIGNED {
  v		(mV)
  celsius	(degC)
  ina 		(mA/cm2)
  g		(pS/um2)
  g2		(pS/um2)
  i		(mA/cm2)
  inf_n
  inf_n2
  tau_n		(ms)
  tau_n2	(ms)
  inf_h
  inf_h2
  tau_h		(ms)
  tau_h2	(ms)
  inf_s
  inf_s2
  tau_s		(ms)
  tau_s2	(ms)
}

BREAKPOINT {
  SOLVE states METHOD cnexp
  g = 0
  g2 = 0
  if( n >=0 ){	: make sure no domain error for pow. Cvode may test it
    : g = gbar*n^n_gates*h*(1-sfrac) + gbar*n^n_gates*h*s*sfrac	
    g 	= gbar*n^gates_n*h*( 1 + sfrac*(s-1) )	
  }
  if( n2 >=0 ){	: make sure no domain error for pow. Cvode may test it
    : g2 = gbar16*n2^n_gates*h2*(1-sfrac2) + gbar*n^n_gates*h2*s2*sfrac2	
    g2 	= gbar16*n2^gates_n*h2*( 1 + sfrac2*(s2-1) )	
  }
  i	= g * ( v - ena ) * (1e-4) + g2 * (v - ena ) * (1e-4)
  ina	= i
}

INITIAL {
  needAdj = 1
  rates( v )
  n = inf_n
  h = inf_h
  s = inf_s
  n2 = inf_n2
  h2 = inf_h2
  s2 = inf_s2
}

UNITS {
  (mA)	= (milliamp)
  (mV)	= (millivolt)
  (pS)	= (picosiemens)
  (um)	= (micrometer)
}

DERIVATIVE states {     : exact when v held constant; integrates over dt step
  rates( v )
  n' = ( inf_n - n )/ tau_n
  h' = ( inf_h - h )/ tau_h
  s' = ( inf_s - s )/ tau_s
  n2' = ( inf_n2 - n2 )/ tau_n2
  h2' = ( inf_h2 - h2 )/ tau_h2
  s2' = ( inf_s2 - s2 )/ tau_s2
}

PROCEDURE rates( v (mV)){
  if( needAdj > 0 ){
    needAdj = 0
    ngate_adjust( gates_n, vhalf_n, slope_n )
    vhalfA_n = v5_adj
    slopeA_n = slp_adj
    vhalfA_n2 = v5_adj+vhalfD_n2
  }
  inf_n = Boltzmann( v, vhalfA_n, slopeA_n )
  tau_n = BorgMod_tau( v, vhalf_n, slope_n, tau0_n, tauA_n, tauG_n, tauF_n, tauDv_n )

  inf_h = Boltzmann( v, vhalf_n + vhalfD_h, slope_h )
  tau_h = BorgMod_tau( v, vhalf_n + vhalfD_h, slope_h, tau0_h, tauA_h, tauG_h, tauF_h, tauDv_h )

  inf_s = Boltzmann( v, vhalf_n + vhalfD_s, slope_s )
  tau_s = BorgMod_tau( v, vhalf_n + vhalfD_s, slope_s, tau0_s, tauA_s, tauG_s, tauF_s, tauDv_s )

  inf_n2 = Boltzmann( v, vhalfA_n2, slopeA_n )
  tau_n2 = BorgMod_tau( v, vhalf_n + vhalfD_n2, slope_n, tau0_n, tauA_n, tauG_n, tauF_n, tauDv_n )

  inf_h2 = Boltzmann( v, vhalf_n + vhalfD_n2 + vhalfD_h, slope_h )
  tau_h2 = BorgMod_tau( v, vhalf_n + vhalfD_n2 + vhalfD_h, slope_h, tau0_h, tauA_h, tauG_h, tauF_h, tauDv_h )

  inf_s2 = Boltzmann( v, vhalf_n + vhalfD_n2 + vhalfD_s, slope_s )
  tau_s2 = BorgMod_tau( v, vhalf_n + vhalfD_n2 + vhalfD_s, slope_s, tau0_s, tauA_s, tauG_s, tauF_s, tauDv_s )
}

FUNCTION Boltzmann( v (mV), v5 (mV), s (mV) ){
  Boltzmann = 1 / (1 + exp( (v - v5) / s ))
}

FUNCTION BorgMod_tau( v (mV), v5 (mV), s (mV), tau0 (ms), tauA (ms), tauG, tauF, tauDv (mV) ) (ms) {
  LOCAL kc, kr, Dv, wr

  kr = 1000
  wr = 1000
  Dv = (v - ( v5 + tauDv )) * 1(1/mV)
  kc = kr * 10^tauF / s * 1(mV)

  BorgMod_tau = tau0 + tauA * 2 * sqrt( tauG * (1-tauG))
		* ( exp( - Dv *tauG/wr/kc ) + exp( Dv *(1-tauG)/wr/kc ))
 	        / ( exp( - Dv *(1-tauG)*kc/kr ) + exp( Dv *kc*tauG/kr ))
}

: Boltzmann's inverse
FUNCTION Boltz_m1( x, v5 (mV), s (mV) ) (mV) {
  Boltz_m1 = s * log( 1/x - 1 ) + v5
}

: Find parameters for a Boltzmann eq that when taken to the ngate power matches one with a single power
: return result in v5_adj and slp_adj
: We solve for exact match on two points
PROCEDURE ngate_adjust( ng, vh, slp ) {
  LOCAL x1, x2, v1, v2
  x1 = 0.3
  x2 = 0.7
  v1 = Boltz_m1( x1, vh, slp )
  v2 = Boltz_m1( x2, vh, slp )
  slp_adj = (v2 - v1)/( log( (1/x2)^(1/ng) - 1 ) - log( (1/x1)^(1/ng) - 1 ) )
  v5_adj = v1 - slp_adj * log( 1 / x1^(1/ng) - 1 )
}






