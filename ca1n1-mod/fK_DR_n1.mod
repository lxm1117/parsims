TITLE Potassium DR Channel

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
  SUFFIX	fK_DR_n1
  USEION	k READ ek WRITE ik
  RANGE		gbar, g, i

  GLOBAL	m_inf, m_tau
}

PARAMETER {
  gbar		= 40	(pS/um2)	: 10S/cm2 = 1 pS/um2
  ek			(mV)		: NEURON uses Nerst to initialize, override in hoc
  q10		= 3				:
  q10ref	= 22	(degC)		: 

  needAdj	= 1			: Flag to indicate need to call ngate_adjust()
  m_ngate		= 4

  : Boltzmann for inf(v) = 1 / (1 +exp( v - (vhalf+vhalfAdj)) / (slope+slopeAdj) )
  m_vhalf	= 10	(mV)
  m_slope	= -10	(mV)
  m_vhalfAdj	= -22 	(mV)		: adjustments for ngate power; Set in ngate_adjust()
  m_slopeAdj	= -3 	(mV)

  : Cauchy for tau(v) = tauA / ( 1 + ( ( v - (vhalf+tauDV)) / tauS )^2 )
  m_tauA	= 30 	(ms)		: peak tau amplitude
  m_tauDV	= -60	(mV)		: tau peaks at vhalf + tauDV
  m_tauS	= 25	(mV)		: tau slope

}

STATE {
  m					: activation gate
}

ASSIGNED {
  v			(mV)
  celsius		(degC)
  ik			(mA/cm2)
  g			(pS/um2)
  i			(mA/cm2)
  m_inf 
  m_tau			(ms)
}

BREAKPOINT {
  SOLVE states METHOD cnexp
  g = 0
  if( m >=0 ){	: make sure no domain error for pow. Cvode may test it
    g 	= gbar * m^m_ngate
  }
  i	= g * ( v - ek ) * (1e-4)
  ik	= i
}

INITIAL {
  ngate_adjust()
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
  if( needAdj ){
    ngate_adjust()
    needAdj = 0
  }

  m_inf = Boltzmann( v, m_vhalf+m_vhalfAdj, m_slope+m_slopeAdj )
  m_tau = Cauchy( v, m_tauA, m_vhalf+m_tauDV, m_tauS )
  m_tau = q10f * m_tau

}

FUNCTION Boltzmann( v (mV), v5 (mV), s (mV) ){
  Boltzmann = 1 / (1 + exp((v - v5)/ s ))
}
FUNCTION Cauchy( v (mV), a (ms), v5 (mV), s (mV) ) (ms){
  Cauchy = a / ( 1 + ((v - v5)/s)^2 )
}

: Boltzmann's inverse
FUNCTION Boltz_m1( x, v5 (mV), s (mV) ) (mV) {
  Boltz_m1 = s * log( 1/x - 1 ) + v5
}

: Find parameters for a Boltzmann eq that when taken to the ngate power matches one with a single power
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
