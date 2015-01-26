
 
UNITS {
	(molar) = (1/liter)
	(mA) = (milliamp)
	(S)  = (siemens)
        (mV) = (millivolt)
	(mM) = (millimolar)
	FARADAY = (faraday) (coulombs)
	R = (k-mole) (joule/degC)
	
}
 
NEURON {
        SUFFIX epasn
	NONSPECIFIC_CURRENT i
	USEION k READ ki, ko
	USEION na READ nai,nao
	GLOBAL pna, pk, pcl, cli, clo
	RANGE g
} 

PARAMETER {
	 g=2.1786e-5 (S/cm2)  <0,1e9>
	 pna=0.05
	 pk=1
	 pcl=0.45
	 cli=6 (mM)
	 clo=131.4 (mM)
}

ASSIGNED {
	celsius (degC)
	v (mV)
	i (mA/cm2)
	ko (mM)
	ki (mM)
	nao (mM)
	nai (mM)
}
 

STATE {
       Epas (mV)
}
BREAKPOINT { 

 	Epas=(1000)*R*(celsius+273.15)/FARADAY* log((pk*ko+pna*nao+pcl*cli)/(pk*ki+pna*nai+pcl*clo))
	i=g*(v-Epas)
}

