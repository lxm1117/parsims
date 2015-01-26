TITLE h channel
: Jose Ambros-Ingerson jose@kiubo.net 2006

NEURON {
  SUFFIX 		h_2t	: h channel with two time constants
  NONSPECIFIC_CURRENT 	i
  RANGE			gbar, g, i

  GLOBAL 		inf_n, tau_n
}

PARAMETER {
  e 		= -30	(mV)
  gbar		= 1 	(pS/um2)

  : inf_n parameters
  gates_n	= 1
  vhalf_n	= -80	(mV)	
  slope_n	= 10	(mV)
  w12f_n	= 0.5		: weight factor for tau1 vs tau2 

  : tau_n parameters
  tau1A_n	= 1000 	(ms)
  tau1Dv_n	= 0	(mV)	: Delta to vhalf_n
  tau1G_n	= 0.5		: Left-right bias. range is (0,1)
  tau1F_n	= 0		: Up-Down bias. range is ~ -3.5(cup-shape), -3(flat), 0(from k), 1(sharper)
  tau10_n	= 1	(ms)	: minimum tau

  tau2A_n	= 100 	(ms)
  tau2Dv_n	= 0	(mV)	: Delta to vhalf_n
  tau2G_n	= 0.5		: Left-right bias. range is (0,1)
  tau2F_n	= 0		: Up-Down bias. range is ~ -3.5(cup-shape), -3(flat), 0(from k), 1(sharper)
  tau20_n	= 1	(ms)	: minimum tau
}

STATE {
  n
}

ASSIGNED {
  v		(mV)
  celsius	(degC)
  g		(pS/um2)
  i		(mA/cm2)
  inf_n
  tau_n		(ms)
}

BREAKPOINT {
  SOLVE states METHOD cnexp
  g = 0
  if( n >=0 ){	: make sure no domain error for pow. Cvode may test it
    g 	= gbar * n^gates_n
  }
  i	= g * ( v - e ) * (1e-4)
}

INITIAL {
  rates( v )
  n = inf_n
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
}

PROCEDURE rates( v (mV)){

  inf_n = Boltzmann( v, vhalf_n, slope_n )

  tau_n = w12f_n * BorgMod_tau( v, vhalf_n, slope_n, tau10_n, tau1A_n, tau1G_n, tau1F_n, tau1Dv_n )
	  *(1 - w12f_n) * BorgMod_tau( v, vhalf_n, slope_n, tau20_n, tau2A_n, tau2G_n, tau2F_n, tau2Dv_n )

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







