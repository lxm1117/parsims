TITLE ca1ca.mod, calcium handling
 
COMMENT
 
ENDCOMMENT

NEURON {
        SUFFIX ca1ca
        USEION ca READ cai, ica WRITE cai
	  RANGE depth, tau, cai0
}
 
UNITS {
        (mA) = (milliamp)
        (mM) = (milli/liter)
	  F = (faraday) (coulombs)
}
 
PARAMETER {
	depth = 1 (um)
      tau = 10 (ms)
	cai0 = 50e-6 (mM)		: set in hoc
}

ASSIGNED {  ica (mA/cm2) }
  
STATE { cai (mM)}
 
BREAKPOINT {SOLVE scheme METHOD derivimplicit}
 
DERIVATIVE scheme {
     cai' = -ica/depth/F/2 * (1e7) - (cai - cai0)/tau 
}

INITIAL { cai= cai0}

