TITLE Potassium A channel

COMMENT
  Jose Ambros-Ingerson 2005
ENDCOMMENT

UNITS {
  (mA)	= (milliamp)
  (mV)	= (millivolt)
  (pS)	= (picosiemens)
  (um)	= (micrometer)
}

NEURON {
  SUFFIX	KA_n1
  USEION	k READ ek WRITE ik
  RANGE		gbar, g, i

  GLOBAL	m_inf, m_tau
  GLOBAL	h_inf, h_tau
  RANGE		prx_dst_flag
}

PARAMETER {
  prx_dst_flag	=	1		: >0 => prx else => dst; Proximal by default
  gbar		= 20	(pS/um2)	: 
  ek			(mV)		: NEURON uses Nerst to initialize, override in hoc
  q10		= 3			: ???
  q10ref	= 22	(degC)		: Hoffman used 22oC

  : v5=-29.8 s=-23.5 ^4 ~ v5=11 s=-18 (for proximal)
  : v5=-34.6 s=-19.3 ^4 ~ v5=-1 s=-15 (for distal)

  needAdj	= 1			: Flag to indicate need to call ngate_adjust()
  m_ngate	= 4

  : Boltzmann for inf = 1 / (1 +exp( v-(vhalf+vhalfAdj))/(slope+slopeAdj) )
  m_vhalf	= 11	(mV)		: Proximal values
  m_slope	= -18	(mV)

  m_vhalf_Ddst	= -12	(mV)		: Differential for distal values
  m_slope_Ddst	= 3	(mV)

  m_vhalfAdj_prx= 0 (mV)		: adjustments for ngate power; Set in ngate_adjust()
  m_slopeAdj_prx= 0 (mV)
  m_vhalfAdj_dst= 0 (mV)
  m_slopeAdj_dst= 0 (mV)

  : Cauchy for tau(v) = tauA / ( 1 + (( v-vhalf-tauDV)/ tauS )^2 )
  m_tauA	= 20	(ms)		: peak tau amplitude
  m_tauDV	= 0	(mV)		: tau peaks at vhalf + tauDV
  m_tauS	= 80	(mV)		: tau slope

  h_vhalf	= -56.0	(mV)
  h_slope	= 8	(mV)
  h_tauF	= 1			: tau factor
}

STATE {
  m					: activation gate
  h					: inactivation gate
}

ASSIGNED {
  v			(mV)
  celsius		(degC)
  ik			(mA/cm2)
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
  if( h >=0 ){	: make sure no domain error for pow. Cvode may test it
    g 	= gbar * m^m_ngate * h
  }
  i	= (0.0001) * g * ( v - ek ) 
  ik	= i
}

INITIAL {
  ngate_adjust()
  rates( v, prx_dst_flag )
  m	= m_inf
  h	= h_inf
}

DERIVATIVE states {
  rates( v, prx_dst_flag )
  m'	= ( m_inf - m )/ m_tau
  h'	= ( h_inf - h )/ h_tau
}

PROCEDURE rates( v (mV), pd_flag ) {
  LOCAL q10f, v5, s
 
  q10f	= 1 / q10^( (celsius - q10ref )/10 (degC) )
  if( needAdj ){
    ngate_adjust()
    needAdj = 0
  }

  if( pd_flag > 0 ){
    v5 = m_vhalf + m_vhalfAdj_prx
    s  = m_slope + m_slopeAdj_prx 
  }
  else {
    v5 = m_vhalf + m_vhalfAdj_dst
    s  = m_slope + m_slopeAdj_dst
  }
  m_inf = Boltzmann( v, v5, s )
  m_tau = Cauchy( v, m_tauA, v5 + m_tauDV, m_tauS )
  m_tau = q10f * m_tau

  h_inf = Boltzmann( v, h_vhalf, h_slope )
  : Follow fig 2c from Hoffman 97
  h_tau = 5.0
  if( v > -20.0 ){
    h_tau = 5 (ms) + 0.26 (ms/mV) *( v + 20 (mV) )
  }
  h_tau = h_tau * q10f * h_tauF
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

  m_vhalfAdj_prx = aV5 - m_vhalf
  m_slopeAdj_prx = aS - m_slope

  v1 = Boltz_m1( x1, m_vhalf + m_vhalf_Ddst, m_slope + m_slope_Ddst )
  v2 = Boltz_m1( x2, m_vhalf + m_vhalf_Ddst, m_slope + m_slope_Ddst )
  aS = (v2 - v1)/( log( (1/x2)^(1/m_ngate) - 1 ) - log( (1/x1)^(1/m_ngate) - 1 ) )
  aV5 = v1 - aS * log( 1 / x1^(1/m_ngate) - 1 )

  m_vhalfAdj_dst = aV5 - m_vhalf
  m_slopeAdj_dst = aS - m_slope

}

