TITLE K-DR channel
: Jose Ambros-Ingerson jose@kiubo.net 2006

NEURON {
  SUFFIX 	KDR_b0
  USEION 	k READ ek WRITE ik
  RANGE		gbar, g, i

  GLOBAL 	inf_n, tau_n
}

PARAMETER {
  ek 			(mV)
  gbar		= 30 	(pS/um2)

  gates_n	= 1
  K_n		= 5.9 	(ms)
  vhalf_n	= -5	(mV)
  zeta_n	= 3	
  gamma_n	= 0.8
  tau0_n	= 0.8	(ms)
}

STATE {
  n
}

ASSIGNED {
  v		(mV)
  celsius	(degC)
  ik 		(mA/cm2)
  g		(pS/um2)
  i		(mA/cm2)
  inf_n
  tau_n		(ms)
}

BREAKPOINT {
  SOLVE states METHOD cnexp
  g 	= gbar * n^gates_n
  i	= g * ( v - ek ) * (1e-4)
  ik	= i
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
  LOCAL a, b, FoRT

  FoRT = 9.652e1 / 8.3145 / ( 273.16 (degC) + celsius ) * 1 (degC/mV)

  a = alpha_p( v, K_n, zeta_n, gamma_n, vhalf_n, FoRT )
  b = alpha_p( v, K_n, -zeta_n, (1-gamma_n), vhalf_n, FoRT )

  inf_n = a / ( a + b )
  tau_n = 1 / ( a + b ) + tau0_n
}

FUNCTION alpha_p( v(mV), K (ms), z, g, v5 (mV), FoRT (1/mV) )(1/ms) {
  alpha_p = exp( z * g *( v - v5 )* FoRT ) / K
}





