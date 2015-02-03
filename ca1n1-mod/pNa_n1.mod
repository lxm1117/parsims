TITLE persistent Sodium channel

COMMENT
  Jose Ambros-Ingerson jose@kiubo.net c2005
ENDCOMMENT

UNITS {
  (mA)	= (milliamp)
  (mV)	= (millivolt)
  (pS)	= (picosiemens)
  (um)	= (micrometer)
}

NEURON {
  SUFFIX	pNa_n1
  USEION	na READ ena WRITE ina
  RANGE		gbar, g, i

  GLOBAL	m_inf, m_tau
}

PARAMETER {
  gbar		= 1	(pS/um2)	: 10S/cm2 = 1 pS/um2
  ena			(mV)		: NEURON uses Nerst to initialize, override in hoc
  q10		= 1				: 
  q10ref	= 22	(degC)		: 

  : Boltzmann for inf(v) = 1 / (1 +exp( v - (vhalf+vhalfAdj)) / (slope+slopeAdj) )
  m_vhalf	= -50	(mV)
  m_slope	= -3	(mV)

  : Cauchy for tau(v) = tauA / ( 1 + ( ( v - (vhalf+tauDV)) / tauS )^2 )
  m_tauA	= 1.0	(ms)		: peak tau amplitude
  m_tauDV	= 0	(mV)		: tau peaks at vhalf + tauDV
  m_tauS	= 50	(mV)		: tau slope

}

STATE {
  m					: activation gate
}

ASSIGNED {
  v			(mV)
  celsius		(degC)
  ina			(mA/cm2)
  g			(pS/um2)
  i			(mA/cm2)
  m_inf 
  m_tau			(ms)
}

BREAKPOINT {
  SOLVE states METHOD cnexp
  g 	= gbar * m
  i	= g * ( v - ena ) * (1e-4)
  ina	= i
}

INITIAL {
  rates( v )
  m	= m_inf
}

DERIVATIVE states {
  rates( v )
  m'	= ( m_inf - m )/ m_tau
}

PROCEDURE rates( v (mV)) {
  LOCAL q10f
 
  q10f	= 1 / q10^( (celsius - q10ref )/10 (degC) )

  m_inf = Boltzmann( v, m_vhalf, m_slope )
  m_tau = Cauchy( v, m_tauA, m_vhalf+m_tauDV, m_tauS )
  m_tau = q10f * m_tau

}

FUNCTION Boltzmann( v (mV), v5 (mV), s (mV) ){
  Boltzmann = 1 / (1 + exp((v - v5)/ s ))
}
FUNCTION Cauchy( v (mV), a (ms), v5 (mV), s (mV) ) (ms) {
  Cauchy = a / ( 1 + ((v - v5)/s)^2 )
}
