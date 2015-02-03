TITLE ca1c.mod Conductances for CA1 cells
 
COMMENT
 
ENDCOMMENT
 
UNITS {
        (/ms) = (1/millisecond)
        (mA) = (milliamp)
        (mV) = (millivolt)
        (molar) = (1/liter)
        (mM) = (millimolar)
}
 
NEURON {
        SUFFIX ca1N
        USEION ca READ eca, cai WRITE ica
	RANGE  gcaNbar
	RANGE icaN
	RANGE itot
	RANGE gcaN
	RANGE gca, gtot
	GLOBAL nainf, niinf
	GLOBAL natau, nitau
}
 
PARAMETER {
	gcaNbar = 1.5e-3 	(mho/cm2)
        eca = 80 (mV)

}
 
STATE {
	   nna nni
	   }
 
ASSIGNED {
        v (mV)
        celsius  (degC)
        ica (mA/cm2)
        icaN (mA/cm2)
	itot (mA/cm2)
	gcaN (mho/cm2)
	gca (mho/cm2)
        gtot (mho/cm2)
	nainf niinf 
	   natau nitau 
        cai  (mM)
}
 
BREAKPOINT {
        SOLVE states METHOD cnexp 
        gcaN = gcaNbar*nna*nna*nni
        icaN = gcaN*(v - eca)
	gca = gcaN
	ica = icaN
        gtot =  gca  
        itot =  ica 
}

INITIAL {
	rates(v)
	nna = nainf
	nni = niinf

}
UNITSOFF

DERIVATIVE states {
        rates(v)
	  nna' = (nainf - nna) / natau	: Ca-N act
	  nni' = (niinf - nni) / nitau	: Ca-N inact
}
 
PROCEDURE rates(v (mV)) {  :Computes rate and other constants at current v.
                      :Call once from HOC to initialize inf at resting v.
        LOCAL  q10, alpha, beta

	  q10 = 3^((celsius - 6.3)/10)

			:"na" calcium (N) activation system
			:  as in Jaffe and A&H
			:  m^2 h

	  alpha = -0.19 * vtrap((v - 19.88), -10)
			: -0.19*(v-19.88)/(exp((v-19.88)/-10)-1)
	  beta = 0.046 * exp(-v/20.73)
	  natau = 1 / (alpha + beta)
	  nainf = alpha * natau

			:"ni" calcium (N) inactivation system
			:  from Tsien (Fox et al?)  Jaffee used wrong
			:  inact (used Fox's L inact)

	  alpha = 1e-4 * (v + 150)/(1 + exp((v + 70)/12.5))
	  beta =  1e-4 * (v + 150)/(1 + exp(-(v + 70)/12.5))
	  nitau = 1 / (alpha + beta)
	  niinf = alpha * nitau

}

FUNCTION vtrap(x,y) {  :Traps for 0 in denominator of rate eqns.
        if (fabs(x/y) < 1e-6) {
                vtrap = y*(1 - x/y/2)
        }else{
                vtrap = x/(exp(x/y) - 1)
        }
}
 
UNITSON

