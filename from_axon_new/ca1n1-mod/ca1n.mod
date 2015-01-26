TITLE ca1n.mod Conductances for CA1 cells (version new)
 
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
        SUFFIX ca1n
        USEION na READ ena WRITE ina
        USEION k READ ek WRITE ik
:        USEION ca READ cai WRITE ica
        USEION ca READ eca, cai WRITE ica
:        NONSPECIFIC_CURRENT ih
        NONSPECIFIC_CURRENT icasp
        RANGE gnafbar, gnapbar, ghbar 
	RANGE gcaLbar, gcaTbar, gcaNbar, gcaRbar
	RANGE gcaLbarsp, gcaTbarsp, gcaNbarsp, gcaRbarsp
	RANGE gkAbar, gBKbar, gSKbar, gkMbar, gkDbar
	RANGE gkDRfbar, gkDRsbar
 	RANGE gkAHPbar
:	RANGE eh
	RANGE ikDRf, ikDRs, ikA, iBK, iSK, ikM, ikAHP, ikD
 	RANGE inaf, inap
	RANGE icaL, icaN, icaT, icaR
	RANGE icaLsp, icaNsp, icaTsp, icaRsp
	RANGE itot
	RANGE gnaf, gnap, gh
	RANGE gkDRf, gkDRs, gkA, gBK, gSK, gkM, gkAHP, gkD
	RANGE gcaL, gcaT, gcaN, gcaR
	RANGE gcaLsp, gcaTsp, gcaNsp, gcaRsp
	RANGE gna, gk, gca, gtot, gcasp
        GLOBAL minf, hinf, ainf, binf
:       GLOBAL qsinf, qfinf
        GLOBAL ninf, nsinf, nshinf
	GLOBAL linf, nainf, niinf, tainf, tiinf, rinf, sinf
	GLOBAL bainf, bbinf, bzinf, sainf, mainf, dainf, dbinf, aainf
	GLOBAL pminf
        GLOBAL mtau, htau, atau, btau
:     GLOBAL qstau, qftau
        GLOBAL ntau, nstau, nshtau
	GLOBAL ltau, natau, nitau, tatau, titau, rtau, stau
	GLOBAL batau, bbtau, bztau, satau, matau, datau, dbtau, aatau
	GLOBAL pmtau
}
 
PARAMETER {
        gnafbar = 0	 	(mho/cm2)
        gkDRfbar = 0		(mho/cm2) 
        gkDRsbar = 0		(mho/cm2) 
        gkAbar = 0 		(mho/cm2)
:	ghbar = 0	 	(mho/cm2)
	gcaLbar = 0	 	(mho/cm2)
	gcaTbar = 0		(mho/cm2)
	gcaNbar = 0 		(mho/cm2)
	gcaRbar = 0		(mho/cm2)
	gBKbar = 0	 	(mho/cm2)
	gSKbar = 0		(mho/cm2)
        gkMbar = 0	 	(mho/cm2)
        gkDbar = 0	 	(mho/cm2)
	gnapbar = 0		(mho/cm2)
        gkAHPbar = 0	 	(mho/cm2)
	gcaLbarsp = 0 		(mho/cm2)
	gcaTbarsp = 0		(mho/cm2)
	gcaNbarsp = 0	 	(mho/cm2)
	gcaRbarsp = 0		(mho/cm2)
:       gl = .0001 		(mho/cm2)
:       el = -70 (mV)
        ena = 45 (mV)
        eca = 80 (mV)
        ek = -85 (mV)
:	eh = -20 (mV)

}
 
STATE {
        m h a b 
:qf qs 
        n ns nsh
	  l ta ti nna nni r s 
	  ba bb bz sa ma aa da db pm}
 
ASSIGNED {
        v (mV)
        celsius  (degC)
	ik (mA/cm2)
        ica (mA/cm2)
        icasp (mA/cm2)
:       il (mA/cm2)
        ina (mA/cm2)
        inaf (mA/cm2)
        inap (mA/cm2)
        ikDRf (mA/cm2)
        ikDRs (mA/cm2)
        ikA (mA/cm2)
:	ih (mA/cm2)
        icaL (mA/cm2)
        icaN (mA/cm2)
        icaT (mA/cm2)
        icaR (mA/cm2)
        icaLsp (mA/cm2)
        icaNsp (mA/cm2)
        icaTsp (mA/cm2)
        icaRsp (mA/cm2)
        iBK (mA/cm2)
        iSK (mA/cm2)
        ikM (mA/cm2)
        ikD (mA/cm2)
        ikAHP (mA/cm2)
	itot (mA/cm2)
	gna (mho/cm2)
	gnaf (mho/cm2)
	gnap (mho/cm2)
	gkDRf (mho/cm2)
	gkDRs (mho/cm2)
	gkA (mho/cm2)
:	gh (mho/cm2)
	gcaL (mho/cm2)
	gcaT (mho/cm2)
	gcaN (mho/cm2)
	gcaR (mho/cm2)
	gcaLsp (mho/cm2)
	gcaTsp (mho/cm2)
	gcaNsp (mho/cm2)
	gcaRsp (mho/cm2)
	gBK (mho/cm2)
	gSK (mho/cm2)
	gkM (mho/cm2)
	gkD (mho/cm2)
	gkAHP (mho/cm2)
        gk (mho/cm2)
	gca (mho/cm2)
	gcasp (mho/cm2)
        gtot (mho/cm2)
	  minf hinf ainf binf 
:         qsinf qfinf 
          ninf nsinf nshinf
	  linf nainf niinf tainf tiinf rinf sinf 
     	  bainf bbinf bzinf sainf mainf
	  dainf dbinf aainf pminf
	  mtau htau atau btau 
:          qstau qftau
          ntau nstau nshtau
	  ltau natau nitau tatau titau rtau stau 
	  batau bbtau bztau satau matau
	  datau dbtau aatau pmtau
        cai  (mM)
}
 
BREAKPOINT {
        SOLVE states METHOD cnexp 
        gnaf = gnafbar*m*m*m*h
        inaf = gnaf*(v - ena)
        gnap = gnapbar*pm
        inap = gnap*(v - ena)
        gkDRf = gkDRfbar*n*n*n*n
        ikDRf= gkDRf*(v - ek)
        gkDRs = gkDRsbar*ns*ns*ns*ns*nsh
        ikDRs= gkDRs*(v - ek)
	gkA = gkAbar*a*a*a*a*b
	ikA = gkA*(v - ek)
:	gh = ghbar*qs*qf
:	ih = gh*(v - eh)
        gcaL = gcaLbar*l*l
        icaL = gcaL*(v - eca)
        gcaN = gcaNbar*nna*nna*nni
        icaN = gcaN*(v - eca)
        gcaT = gcaTbar*ta*ti
        icaT = gcaT*(v - eca)
        gcaR = gcaRbar*r*r*r*r*s
        icaR = gcaR*(v - eca)
        gcaLsp = gcaLbarsp*l*l
        icaLsp = gcaLsp*(v - eca)
        gcaNsp = gcaNbarsp*nna*nna*nni
        icaNsp = gcaNsp*(v - eca)
        gcaTsp = gcaTbarsp*ta*ti
        icaTsp = gcaTsp*(v - eca)
        gcaRsp = gcaRbarsp*r*r*r*r*s
        icaRsp = gcaRsp*(v - eca)
 	gBK = gBKbar*ba*bb*bz
 	iBK = gBK*(v-ek)
	gSK = gSKbar*sa
	iSK = gSK*(v-ek)
	gkAHP = gkAHPbar*aa
	ikAHP = gkAHP*(v-ek)
	gkM = gkMbar*ma*ma
	ikM = gkM*(v-ek)
	gkD = gkDbar*da*da*da*da*db*db*db*db
	ikD = gkD*(v-ek)
        gna = gnaf + gnap
	ina = inaf + inap
        gk = gkDRf + gkDRs + gkA + gBK + gSK + gkM + gkD + gkAHP
	ik = ikDRf + ikDRs + ikA + iBK + iSK + ikM + ikD + ikAHP
	gca = gcaL + gcaN + gcaT + gcaR
	gcasp = gcaLsp + gcaNsp + gcaTsp + gcaRsp
	ica = icaL + icaN + icaT + icaR
	icasp = icaLsp + icaNsp + icaTsp + icaRsp
 :       il = gl*(v - el)
        gtot = gk + gca + gna + gcasp
:          +gh
        itot = ik + ica + ina + icasp
:           +ih
}

INITIAL {
	bbinf = 1
	rates(v)
	m = minf
        h = hinf
	n = ninf
	ns = nsinf
	nsh = nshinf
	a = ainf
	b = binf
:        qs = qsinf
:	qf = qfinf
        l = linf
	ta = tainf
	ti = tiinf
	nna = nainf
	nni = niinf
	r = rinf
        s = sinf
        ba = bainf
	bz = bzinf
	bb = bbinf
	sa = sainf
	ma = mainf
	da = dainf
	db = dbinf
	aa = aainf
	pm = pminf

}
UNITSOFF

DERIVATIVE states {
        rates(v)
	  m' = (minf - m) / mtau		: Na act
	  h' = (hinf - h) / htau		: Na inact
	  pm' = (pminf - pm) / pmtau		: Na-P act
	  n' = (ninf - n) / ntau		: K-DRf act
	  ns' = (nsinf - ns) / nstau		: K-DRs act
	  nsh' = (nshinf - nsh) / nshtau	: K-DRs inact
	  a' = (ainf - a) / atau		: A act
	  b' = (binf - b) / btau		: A inact
:	  qs' = (qsinf - qs) / qstau		: H slow
:	  qf' = (qfinf - qf) / qftau		: H fast
	  l' = (linf - l) / ltau		: Ca-L act
	  ta' = (tainf - ta) / tatau		: Ca-T act
	  ti' = (tiinf - ti) / titau		: Ca-T inact
	  nna' = (nainf - nna) / natau		: Ca-N act
	  nni' = (niinf - nni) / nitau		: Ca-N inact
	  r' = (rinf - r) / rtau		: Ca-R act
	  s' = (sinf - s) / stau		: Ca-R inact
	  ba' = (bainf - ba) / batau		: BK act
	  bb' = (bbinf - bb) / bbtau		: BK inact  
	  bz' = (bzinf - bz) / bztau		: BK calcium
	  sa' = (sainf - sa) / satau		: SK act & calcium
	  ma' = (mainf - ma) / matau		: M act
	  da' = (dainf - da) / datau		: D act
	  db' = (dbinf - db) / dbtau		: D inact
	  aa' = (aainf - aa) / aatau		: AHP act & calcium
}
 
PROCEDURE rates(v (mV)) {  :Computes rate and other constants at current v.
                      :Call once from HOC to initialize inf at resting v.
        LOCAL  q10, alpha, beta
:        TABLE minf, mtau, sinf, stau, ninf, ntau, cinf, ctau, ainf, atau, hinf, htau, rinf, rtau, binf, btau DEPEND celsius FROM -100 TO 100 WITH 400

:	  q10 = 3^((celsius - 6.3)/10)

                        :"m" sodium activation system  m^3 h
                        :  adapted from Aradi and Holmes (1999?)
                        :  like Migliore and Hoffman

        alpha = -0.3 * vtrap((v + 50), -3)
:             -0.3*(v+50)/(exp((v+50)/-3)-1)
        beta =  0.3 * vtrap((v + 22), 3)
:              0.3*(v+22)/(exp((v+22)/3)-1)

:        alpha = -0.3 * vtrap((v + 45), -5)
:             -0.3*(v+45)/(exp((v+45)/-5)-1)
:        beta =  0.3 * vtrap((v + 17), 5)
:              0.3*(v+17)/(exp((v+17)/5)-1)
        mtau = 1/(alpha + beta)
        minf = alpha*mtau

                        :"h" sodium inactivation system
                        :  adapted from Aradi and Holmes (1999?)
                        :  between Hoff and others

:        alpha = 0.23 * exp(-(v + 67)/20)    : - instead of /
:        beta = 3.33 / (1 + exp((v + 14.5)/-10))

:        alpha = 0.23 *1.0 * exp(-(v + 72)/12)    : - instead of /
:        beta = 4.33 * 1.0 / (1 + exp((v + 24.5)/-8 ))  : 19.5?
        alpha = 0.83 *1.6 * exp(-(v + 87)/12)    : - instead of /
        beta = 1.33 * 1.6 / (1 + exp((v + 34.5)/-8 ))
        htau = 1/(alpha + beta)
        hinf = alpha*htau


			:"pm" perisitent sodium activation system
			:  parameters from French (1990)  
			:  slope made steeper

        pmtau = 0.8
        pminf = 1/(1+exp(-(v+50)/3))

			:"n" potassium(DR) activation system n^4
			:  adapted from Kf in Aradi and Holmes (1999?)
                        :  modified from A&H to match Martina et al

:	  alpha = -0.07 * vtrap((v + 23), -6)
:           -0.07*(v+23)/(exp((v+23)/-6)-1)
:  	 beta = .264 * exp(-(v + 48)/40)    : - instead of /
        alpha = -0.07*vtrap((v+16),-7)
:       alpha= -0.07*(v+16)/(exp(-(v+16)/7)-1)
        beta=0.264*exp(-(v+41)/30)   :  - instead of /

        ntau = 1/(alpha + beta)
        ninf = alpha*ntau

                        :"ns" slow potassium DR
                        :  highly modified A&H to match Martina et al.

        alpha= -0.056*0.1*vtrap((v-4), -20)   : was 9  0.1 was 0.5
:       alpha= -0.056*(v-4)/(exp(-(v-4)/20)-1
        beta=0.2112*0.1*exp(-(v+11)/30)    : - instead of / was 16
        nstau = 1/(alpha+beta)
        nsinf = alpha*nstau

                        :"nsh" slow potassium inactivation
                        :  using data from Martina et al and Shi et al.

        alpha=.00014*(exp(-(v+40)/20)+.3)
        beta=.00025/(1+exp(-(v+16)/30))
        nshtau=1/(alpha+beta)
        nshinf=alpha*nshtau


			:"a" potassium(A) activation system
			:  from Aradi and Holmes (1999?)
			:  act shifted +10 mV

:	  alpha = -0.05 * vtrap((v + 10), -15)
:			-.05*(v+10)/(exp((v+10)/-15)-1)
:	  beta = 0.1* vtrap((v + 0), 8)
:			0.1*(v+0)/(exp((v+0)/8)-1)

:	  alpha = -0.05 * vtrap((v + 15), -15)
:			-.05*(v+15)/(exp((v+15)/-15)-1)
:	  beta = 0.1* vtrap((v + 5), 8)
:			0.1*(v+5)/(exp((v+5)/8)-1)


			:"a" potassium(A) activation system
			:  from Borg-Graham

:	alpha = .08*exp(2.8*0.85*(v+41)/26.73)
:	beta =  .08*exp(-2.8*0.15*(v+41)/26.73)
:        atau = 1/(alpha + beta)
:        ainf = alpha*atau
:	atau=atau+1


                        :"a" potassium(A) activation system
                        :  corrected from Hoffman et al (1997)
                        :  proximal
                        :  .05 instead of mult tau by .2  slope was 25

        alpha = -.05 * vtrap((v + 31.3), -20)
:       alpha = -.05*(v+31.3)/(exp(-(v+31.3)/20)-1)
        beta = .05 * vtrap((v + 31.3), 20)
:       beta = .05*(v+31.3)/(exp((v+31.3)/20)-1)
        atau = 1/(alpha+beta)
        ainf = alpha*atau



			:"b" potassium(A) inactivation system
			:  from Aradi and Holmes (1999?)
			:  inact act shifted +15 mV

:	  alpha = 0.00015 * exp(-(v - 12)/15)
:	  beta = 0.06/(exp(-(v + 43)/12) + 1)

:	  alpha = 0.00015 * exp(-(v - 2)/18)
:	  beta = 0.06/(exp(-(v + 53)/12) + 1)

			:"b" potassium(A) inactivation system
			:  from Borg-Graham

:	alpha=.04*exp(-3*(v+49)/26.73)
:	beta=.04
:        btau = 1/(alpha + beta)
:        binf = alpha*btau
:	btau=btau+2

                        :"b" potassium(A) inactivation system
                        :  corrected from Hoffman et al (1997)

        alpha = .01 * vtrap((v + 58), 8.2)
:       alpha = .01*(v+58)/(exp((v+58)/8.2)-1)
        beta = -.01 * vtrap((v + 58), -8.2)
:       beta = -.01*(v+58)/exp(-(v+58)/8.2)-1)
        binf = alpha/(alpha+beta)
        btau = 10         : was 5
        if ( v > -20) { btau = 10+2.6*(v+20)/10 }



			:"q" mixed (H) inactivation system
			:  from Destexhe  qs*qf 

:	  qsinf = 1 / (1 + exp((v + 74.9)/6.5))
:	  qfinf = 1 / (1 + exp((v + 74.9)/6.5)) 
:	  qstau = 0.05*exp((v + 183.6)/15.24)
:	  qftau = 0.05*exp((v+158.6)/11.2)/(1 + exp((v+75)/5.5))

:	  qsinf = 1 / (1 + exp((v + 68.9)/6.5))
:	  qfinf = 1 / (1 + exp((v + 68.9)/6.5)) 
:	  qstau = exp((v + 183.6)/15.24)
:	  qftau = exp((v+158.6)/11.2)/(1 + exp((v+75)/5.5))

			:"l" calcium (L) activation system
			:  from Jaffee, used in A&H  m^2

	  alpha = -15.69 * vtrap((v - 81.5), -10)
			: -15.69*(v-81.5)/(exp((v-81.5)/-10)-1)
	  beta = 0.29*exp(-v/10.86)
	  ltau = 1/(alpha + beta)
	  linf = alpha*ltau

			:"ta" calcium (T) activation system
			:  average of Magee & Johnston and Avery and Johnston
			:  mh

	  alpha = -0.026 * vtrap((v + 29), -4.1)
			: -0.026*(v+29)/(exp((v+29)/-4.1)-1)
	  beta = alpha * exp(-(v + 31)/6.5) + 0.9*exp(-(v + 120)/18.4)
	  tatau = 1 / (alpha + beta)
	  tainf = alpha * tatau

			:"ti" calcium (T) inactivation system
			:  average of Magee & Johnston and Avery and Johnston
			:  mh

	  alpha = 7e-5 * vtrap((v + 45), 3)
			: 7e-5*(v+45)/(exp((v+45)/3)-1)
	  beta = 0.034/(1 + exp(-(v + 52)/8.6))
	  titau = 1 / (alpha + beta)
	  tiinf = alpha * titau

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

               	:"r" calcium (R) activation system
			:  closest to Freking, Foerking?sp

:        rtau = 1000 * exp(-(v + 120)/30)
:        rinf = 0.55/(1+exp(-(v + 55)/21)) + 0.45/(1+exp(-(v+25)/8))
        rtau = 100 * exp(-(v + 120)/30)
:        rinf = 0.55/(1+exp(-(v + 35)/21)) + 0.45/(1+exp(-(v+ 5)/8))

			:"r" calcium (R) activation system
			:  Sochivko 2003

	  rinf = 1/(1+exp(-(v+17.2)/6.8))

			:"s" calcium (R) inactivation system

		
	  
        alpha = 0.0098 / (1 + exp((v + 59)/12.2)) 
        beta = alpha * exp((v+60)/11)
        stau = 1/(alpha + beta)
:        sinf = alpha*stau

			: Sochivko 2003
	  sinf = 1/(1+exp((v+70.3)/12.9))

			: "ba" BK potassium activation system
			:   DeSchutter  m z^2

:	  alpha= 7.5
:	  beta= 0.11/exp((v - 35)/14.9)
:	  batau = 1/(alpha + beta)
:	  bainf = alpha * batau

			: "bz" BK calcium dependence
			:   DeSchutter

:	  bzinf = 1/(1 + 4.0/(cai*1e3))
:	  bztau = 10

			: "ba" BK potassium activation system
			:   based on Gong 2001
	 
	 bainf = 1./(1+exp(-(v+7.3)/17))  :shifted 10 mV hyper
	 batau = .5

			: "bb" BK potassium inactivation system
			:   based on Hicks JPL 1998

	bbinf = 1./(1+exp((v+50)/17))
	bbtau = 10

			: "bz" BK calcium dependence
			:   based on Gong 2001

	bzinf = cai*cai*1e6/(4 + cai*cai*1e6)
	bztau = 10         : might try 1/(0.1+cai*1e3)

			: "sa" SK activation  
			:   based on Hirschberg et al J. Gen Physiol. 1998

:	  satau = 30/(0.01+cai*1e3)
:	  sainf = cai*cai*1e6/(0.75*0.75+cai*cai*1e6)

			: "sa" SK activation
			:  based on Hirschberg et al 1999

	  satau = 30/(0.01+cai*1e3)
	  sainf = (cai*1e3)^4/((cai*1e3)^4+(.56)^4)

			: "aa" AHP activation  same as SK but slower tau
			:   based on Hirschberg et al J. Gen Physiol. 

	  aatau = 500/(0.01+cai*1e3)
:	  aainf = cai*cai*1e6/(0.75*0.75+cai*cai*1e6)
	  aainf = (cai*1e3)^4/((cai*1e3)^4+(.56)^4)

			: "ma" Potassium (M)
			:   based on Borg-Graham with q10=5
 			:   slope multiplied by 0.7
	
	  alpha = .015 * exp(0.7*3.6*(v+45)/26.73)
	  beta = 0.015 * exp(-0.7*2.4*(v+45)/26.73)
	  matau = 1 / (alpha + beta)
	  mainf = alpha * matau
	  matau=matau+8

			: "da" Potassium (D) activation
			:   based on Borg-Graham 
	
	  alpha =  1.0
	  beta =  exp(-3*(v+58)/26.73)  : was 63
	  datau = 1 / (alpha + beta)
	  dainf = alpha * datau
	  datau=datau+1

			: "db" Potassium (D) inactivation
			:   based on Borg-Graham 
	
	  alpha =  .0002
	  beta =  .0002*exp(2.5*(v+73)/26.73)
	  dbtau = 1 / (alpha + beta)
	  dbinf = alpha * dbtau
	  dbtau=dbtau+500
}

FUNCTION vtrap(x,y) {  :Traps for 0 in denominator of rate eqns.
        if (fabs(x/y) < 1e-6) {
                vtrap = y*(1 - x/y/2)
        }else{
                vtrap = x/(exp(x/y) - 1)
        }
}
 
UNITSON

