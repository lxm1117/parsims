TITLE ca1.mod Conductances for CA1 cells
 
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
        SUFFIX ca1L
        USEION ca READ eca, cai WRITE ica
	RANGE gcaLbar
	RANGE icaL, linf, ltau
:	GLOBAL linf
:	GLOBAL ltau
}
 
PARAMETER {
	gcaLbar = 1.2e-3 	(mho/cm2)
        eca = 80 (mV)
}
 
STATE { l }
 
ASSIGNED {
        v (mV)
        celsius  (degC)
        ica (mA/cm2)
        il (mA/cm2)
        icaL (mA/cm2)
 	gcaL (mho/cm2)
	linf ltau
        cai  (mM)
}
 
BREAKPOINT {
        SOLVE states METHOD cnexp 
        gcaL = gcaLbar*l*l
        ica = gcaL*(v - eca)
}

INITIAL {
	rates(v)
	l = linf
}
UNITSOFF

DERIVATIVE states {
        rates(v)
	  l' = (linf - l) / ltau		: Ca-L act
}
 
PROCEDURE rates(v (mV)) {  :Computes rate and other constants at current v.
                      :Call once from HOC to initialize inf at resting v.
        LOCAL  q10, alpha, beta
:        TABLE minf, mtau, sinf, stau, ninf, ntau, cinf, ctau, ainf, atau, hinf, htau, rinf, rtau, binf, btau DEPEND celsius FROM -100 TO 100 WITH 400

	  q10 = 3^((celsius - 6.3)/10)
			:"l" calcium (L) activation system
			:  from Jaffee, used in A&H  m^2

	  alpha = -15.69 * vtrap((v - 81.5), -10)
			: -15.69*(v-81.5)/(exp((v-81.5)/-10)-1)
	  beta = 0.29*exp(-v/10.86)
	  ltau = 1/(alpha + beta)
	  linf = alpha*ltau

}

FUNCTION vtrap(x,y) {  :Traps for 0 in denominator of rate eqns.
        if (fabs(x/y) < 1e-6) {
                vtrap = y*(1 - x/y/2)
        }else{
                vtrap = x/(exp(x/y) - 1)
        }
}
 
UNITSON

