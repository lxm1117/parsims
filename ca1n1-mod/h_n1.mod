TITLE h Conductance for CA1 cells
 
COMMENT
  Based on model by Vasilyev and Barish JNS 2002 (VB).
  NOTE: VB failed to correct their vhalf and slope to account for the squared m in the
	computation of g. After looking at their results I see no need to retain the squared m.
	The taus are very fast (2 3 fold) when compared to the results in the paper.

  adjustments necessary for our normal conditions:
    - temperature. VB used 22oC. Standard is 33oC.
      Used Magee JNS 1998 report for Q10 of 4.5 for activation and deactivation kinetics.
      
    - K+. VB used 10mM K+ to enhance I_h. Standard is 2.5mM K+
      Used data from Surges  etal Neurosci Lett 2002 to adjust to 2.5mM K+
        e_h is affected by K+, -30mV @ 2.5mM, -24mV @ 5mM, -16 @ 7.5mM
          we adjusted e_h from -20 to -30
        m_vhalf is affected by K+, -80 @ 2.5mM to -87 @ 5-7.5 mM
      	  we adjusted m_vhalf from -92 to -80

  Magee JNS 1998 reports 
    gbar increased from soma to dendrite
      2 (pS/um2) @ soma to 8-10 @ 350um (2.5mM K+, 110mM Na+)
    m_vhalf shifted from soma to dendrite
      -82 mV @ soma to 90 @ 350um (120mM K+, 0mM Na+)
     
  Jose Ambros-Ingerson jose@kiubo.net c2004

ENDCOMMENT
 
UNITS {
  (/ms)	  = (1/millisecond)
  (mA) 	  = (milliamp)
  (mV) 	  = (millivolt)
  (pS)	  = (picosiemens)
  (um)	  = (micrometer)
}
 
NEURON {
  SUFFIX h_n1
  NONSPECIFIC_CURRENT i
  RANGE  gbar, gbar_fsq, g

  GLOBAL m_inf_slow, m_inf_fast
  GLOBAL m_tau_slow, m_tau_fast
}
 
PARAMETER {
  mho2pS	= 1e-4 		:(sec-coul2/m4-kg)
  q10 		= 4.5			: from Magee JNS 1998
  q10ref    	= 22	(degC)		: Vasilyev's temp was 22oC
  gbar	 	= 1  	(pS/um2)	: 1 to 2 pS/um2 at soma Magee 1998. (1pS/um2=1e-4 mho/cm2)
  gbar_fsq	= 0.8			: fast to slow quotient slow~fast/4 (Vasilyev 2002) 
  e 	    	= -30	(mV)		: See Surges etal 2002

  m_vhalf   	= -80	(mV)		: For m_inf_slow and m_inf_fast
  m_slope   	= 10.4	(mV)		: For m_inf_slow and m_inf_fast

  m_tauA_fast	= 120	(ms)		: peak tau amplitude
  m_tauDV_fast	= 0	(mV)		: tau peaks at vhalf + tauDV
  m_tauS_fast	= 20	(mV)		: tau slope

  m_tauA_slow	= 2000	(ms)		: peak tau amplitude
  m_tauDV_slow	= 0	(mV)		: tau peaks at vhalf + tauDV
  m_tauS_slow	= 45	(mV)		: tau slope

} 


STATE {
  m_fast m_slow 
}
 
ASSIGNED {
  v		(mV)
  celsius  	(degC)
  i 		(mA/cm2)
  g 		(pS/um2)
  m_inf_slow	(1)
  m_tau_slow 	(ms)
  m_inf_fast 	(1)
  m_tau_fast	(ms)
}
 
BREAKPOINT {
  SOLVE states METHOD cnexp 
  g = gbar * (m_fast * gbar_fsq + m_slow * (1-gbar_fsq) )
  i = g*(v - e) * (1e-4 )
}

INITIAL {
  rates(v)
  m_slow = m_inf_slow
  m_fast = m_inf_fast
}

DERIVATIVE states {
  rates( v )
  m_slow' = (m_inf_slow - m_slow) / m_tau_slow		: H slow
  m_fast' = (m_inf_fast - m_fast) / m_tau_fast		: H fast
}
 
PROCEDURE rates( v (mV)) {
  LOCAL q10f
 
  q10f	= 1 / q10^( (celsius - q10ref )/10 (degC) )

  m_inf_fast = Boltzmann( v, m_vhalf, m_slope )
  m_inf_slow = m_inf_fast
  m_tau_fast = Cauchy( v, m_tauA_fast, m_vhalf+m_tauDV_fast, m_tauS_fast )
  m_tau_slow = Cauchy( v, m_tauA_slow, m_vhalf+m_tauDV_slow, m_tauS_slow )

  m_tau_fast = q10f * m_tau_fast
  m_tau_slow = q10f * m_tau_slow
}

FUNCTION Boltzmann( v (mV), v5 (mV), s (mV) ){
  Boltzmann = 1 / (1 + exp((v - v5)/ s ))
}
FUNCTION Cauchy( v (mV), a (ms), v5 (mV), s (mV) ) (ms){
  Cauchy = a / ( 1 + ((v - v5)/s)^2 )
}

UNITSOFF
PROCEDURE VB_original_rates(v (mV)) { 

  LOCAL alpha, beta, q10f
  q10f	= 1 / q10^( (celsius - q10ref )/10 (degC) )

  m_inf_slow = 1 / (1 + exp((v - m_vhalf)/m_slope))
  m_inf_fast = 1 / (1 + exp((v - m_vhalf)/m_slope))
 
  if(v < -83) {
    m_tau_slow = q10f * ( 177 + 67*exp((v+159)/35.5) )
  } else {
    m_tau_slow = q10f * ( 267 + 542*exp(-(v+85)/20) )
  }
  if(v < -87) {
    m_tau_fast = q10f * ( 17 + 7.2*exp((v+124)/22.5) )
  } else {
    m_tau_fast = q10f * ( 27 + 24*exp(-(v+85)/20) )
  }
}

UNITSON

