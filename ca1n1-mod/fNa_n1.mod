TITLE Fast sodium Channel

COMMENT
  Jose Ambros-Ingerson jose@kiub.net c2005
ENDCOMMENT

UNITS {
  (mA)	= (milliamp)
  (mV)	= (millivolt)
  (pS)	= (picosiemens)
  (um)	= (micrometer)
}

NEURON {
  SUFFIX	fNa_n1
  USEION	na READ ena WRITE ina
  RANGE		gbar, g, i

  GLOBAL	m_inf, m_tau
  GLOBAL	h_inf, h_tau
}

PARAMETER {
  gbar		= 40	(pS/um2)	: 10S/cm2 = 1 pS/um2
  ena			(mV)		: NEURON uses Nerst to initialize, override in hoc
  q10		= 3				: 
  q10ref	= 22	(degC)		: 

  needAdj	= 1			: Flag to indicate need to call ngate_adjust()
  m_ngate	= 3

  : Boltzmann for inf(v) = 1 / (1 +exp( v - (vhalf+vhalfAdj)) / (slope+slopeAdj) )
  m_vhalf	= -30	(mV)
  m_slope	= -7	(mV)
  m_vhalfAdj	= 0 	(mV)		: adjustment for inf^ngate; Set by ngate_adjust()
  m_slopeAdj	= 0	(mV)

  : Cauchy for tau(v) = tauA / ( 1 + ( ( v - (vhalf+tauDV)) / tauS )^2 )
  m_tauA	= 0.4	(ms)		: peak tau amplitude
  m_tauDV	= -10	(mV)		: tau peaks at vhalf + tauDV
  m_tauS	= 50	(mV)		: tau slope

  h_vhalf	= -70	(mV)
  h_slope	= 8	(mV)

  : Cauchy for tau(v) = tauA / ( 1 + ( ( v - (vhalf+tauDV)) / tauS )^2 )
  h_tauA	= 20	(ms)		: peak tau amplitude
  h_tauDV	= 0	(mV)		: tau peaks at vhalf + tauDV
  h_tauS	= 30	(mV)		: tau slope

}

STATE {
  m					: activation gate
  h					: inactivation gate
}

ASSIGNED {
  v			(mV)
  celsius		(degC)
  ina			(mA/cm2)
  g			(pS/um2)
  i			(mA/cm2)
  m_inf 
  m_tau			(ms)
  h_inf 
  h_tau			(ms)
}

BREAKPOINT {
  SOLVE states METHOD cnexp
  g = 0
  if( m >=0 ){	: make sure no domain error for pow. Cvode may test it
    g 	= gbar * m^m_ngate * h
  }
  i	= g * ( v - ena ) * (1e-4)
  ina	= i
}

INITIAL {
  ngate_adjust()
  rates( v )
  m	= m_inf
  h	= h_inf
}

DERIVATIVE states {
  rates( v )
  m'	= ( m_inf - m )/ m_tau
  h'	= ( h_inf - h )/ h_tau
}

PROCEDURE rates( v (mV)) {
  LOCAL q10f
 
  q10f	= 1 / q10^( (celsius - q10ref )/10 (degC) )
  if( needAdj ){
    ngate_adjust()
    needAdj = 0
  }
  m_inf = Boltzmann( v, m_vhalf+m_vhalfAdj, m_slope+m_slopeAdj )
  m_tau = Cauchy( v, m_tauA, m_vhalf+m_tauDV, m_tauS )
  m_tau = q10f * m_tau

  h_inf = Boltzmann( v, h_vhalf, h_slope )
  h_tau = Cauchy( v, h_tauA, h_vhalf+h_tauDV, h_tauS )
  h_tau = q10f * h_tau

}

FUNCTION Boltzmann( v (mV), v5 (mV), s (mV) ){
  Boltzmann = 1 / (1 + exp((v - v5)/ s ))
}
FUNCTION Cauchy( v (mV), a (ms), v5 (mV), s (mV) ) (ms) {
  Cauchy = a / ( 1 + ((v - v5)/s)^2 )
}
: Boltzmann's inverse
FUNCTION Boltz_m1( x, v5 (mV), s (mV) ) (mV) {
  Boltz_m1 = s * log( 1/x - 1 ) + v5
}

: Find parameters for a Boltzmann eq that to the ngate power matches one with a single power
: We solve for exact match on two points
PROCEDURE ngate_adjust( ) {
  LOCAL x1, x2, v1, v2, aS, aV5
  x1 = 0.3
  x2 = 0.7
  v1 = Boltz_m1( x1, m_vhalf, m_slope )
  v2 = Boltz_m1( x2, m_vhalf, m_slope )
  aS = (v2 - v1)/( log( (1/x2)^(1/m_ngate) - 1 ) - log( (1/x1)^(1/m_ngate) - 1 ) )
  aV5 = v1 - aS * log( 1 / x1^(1/m_ngate) - 1 )

  m_vhalfAdj = aV5 - m_vhalf
  m_slopeAdj = aS - m_slope
}
