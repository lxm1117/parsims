TITLE passive membrane channel with variable e

UNITS {
	(molar) = (1/liter)
	(mM) = (millimolar)
	(mV) = (millivolt)
	(mA) = (milliamp)
	(S) = (siemens)
}

NEURON {
	SUFFIX pas3
	USEION k READ ko, ki
	USEION na READ nao, nai
	NONSPECIFIC_CURRENT i
	RANGE g
}

PARAMETER {
	g = .001	(S/cm2)	<0,1e9>
	rof = 0.086174 	(mV/degC)    : 8314.5/96485  R/F
        cli = 6 (mM)
	clo = 131.4 (mM)
        pk = 1
        pna = 0.04
	pcl = 0.45
:	e = -70	(mV)
}

ASSIGNED {
	v (mV)  
	i (mA/cm2)
:	ena (mV)
:	ek (mV)
        celsius (degC)
	nai	(mM)
	nao	(mM)
	ki	(mM)
	ko	(mM)
}

STATE { e (mV) }

BREAKPOINT {
:	rtof = rof*(273.15 + celsius)
	e = rof * (273.15 + celsius) * log((pk*ko+pna*nao+pcl*cli)/(pk*ki+pna*nai+pcl*clo))
	i = g*(v - e)
}
