: intracellular sodium ion and extracellular potassium accumulation

NEURON {
 SUFFIX kextna1
: USEION k READ ik WRITE ko
 USEION na READ ina WRITE nai
: RANGE fhspace, txfer, kbath, 
 RANGE narest, inspace, naxfer 
}

UNITS {
 (mV) = (millivolt)
 (mA) = (milliamp)
 FARADAY = (faraday) (coulombs)
 (molar) = (1/liter)
 (mM)    = (millimolar)
}

PARAMETER {
: kbath = 3.4 (mM)
 narest= 10.0(mM)
: fhspace=3000 (angstrom)
 inspace=4000 (angstrom)
: txfer=50 (ms)
 naxfer=100 (ms)
}

ASSIGNED {
 diam (micron)
: ik (mA/cm2)
 ina (mA/cm2)
}

STATE {
: ko (mM)
 nai(mM)
}

BREAKPOINT {			
		SOLVE state METHOD derivimplicit 
	   }

DERIVATIVE state {
: ko'=(1e8)*ik/(fhspace*FARADAY)+(kbath-ko)/txfer
:  nai'=-(1e4)*ina*4/(diam*FARADAY)+(narest-nai)/naxfer
  nai'=-(1e8)*ina/(inspace*FARADAY)+(narest-nai)/naxfer
}

