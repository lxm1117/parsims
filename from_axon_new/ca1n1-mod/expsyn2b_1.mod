COMMENT

Two exponential synapse ampa and nmda with block;
modified without probabilistic release;
tested on full dendritic tree of a full CA1 cell

ENDCOMMENT

NEURON {
	POINT_PROCESS expsyn2b_1
	RANGE delay 
	RANGE tau1, tau2, tau3, tau4, g, gmax, gmax2
        RANGE e, i, scc, block, iampa, inmda, gampa, gnmda, t0, g0_ampa, g0_nmda, scca, sccn
	RANGE num, pr1, pr2, del, interval
	NONSPECIFIC_CURRENT i
}

UNITS {
	(nA) = (nanoamp)
	(mV) = (millivolt)
	(uS) = (microsiemens)
}

PARAMETER {
	delay=0 (ms)
	tau1=.2 (ms)
	tau2=10 (ms)
	tau3=3.5 (ms)
	tau4=40 (ms)
	
        :scca = 8e-6     (uS)
        :sccn = 50e-6    (uS)
        e = 1.3827              (mV)
        mg = 1.2                (1)     : magnesium concentration (mM)
}

ASSIGNED { 
	v 	(mV) 
	i 	(nA) 
	g 	(uS) 
        gampa           (uS)
        gnmda           (uS)
        block   (1)
        iampa           (nA)
        inmda           (nA)
	gmax (uS)
	gmax2 (uS)

	factor 
	factor2 
	index
	rlpr[15]

	pr1
	pr2
	num
	del  (ms)
	interval (ms)
	
	t0 (ms)
	g0_ampa (uS)
	g0_nmda (uS)
	scca	(uS)
	sccn	(uS)
}	

INITIAL { LOCAL tp, tp2
	tp = (tau1*tau2)/(tau2-tau1) * log(tau2/tau1)
	tp2 = (tau3*tau4)/(tau4-tau3) * log(tau4/tau3)
	factor = exp(-tp/tau2) - exp(-tp/tau1)
	factor2 = exp(-tp2/tau4) - exp(-tp2/tau3)
	factor=1/factor
	factor2=1/factor2
	
	index=0	
	:gmax=0
	:gmax2=0	
		
	t0=del
	g0_ampa=0
	g0_nmda=0

	:relpr()
	:++++printf("%f\n", rlpr[0])
	if(index<num) {
		net_send(del,1)
	}
}


BREAKPOINT {
	if  (gmax) { at_time(delay) } :+++++why?
        UNITSOFF
        block = 8.8*exp(v/12.5)/(mg + 8.8*exp(v/12.5))
        UNITSON
	:gampa = gmax * factor*(d((t-delay)/tau2) -d((t-delay)/tau1)) 
	:gnmda = gmax2 * block * factor2*(d((t-delay)/tau4) -d((t-delay)/tau3))
	gampa = gmax * factor*(d((t-t0)/tau2) -d((t-t0)/tau1))+g0_ampa
	gnmda = gmax2 * block * factor2*(d((t-t0)/tau4) -d((t-t0)/tau3))+g0_nmda

        g = gampa + gnmda 
        iampa = gampa*(v - e)
        inmda = gnmda*(v - e)
        :i = iampa + inmda
	i=g*(v-e)
	:printf("%s, %f, %s, %f, %s, %f\n", "gampa: ", gampa, "gnmda: ", gnmda, "i: ", i )
}

NET_RECEIVE( weight (uS)) { :not sure how to write the arguments here, weight or t0 
	if(flag==1){
		:pr1=rlpr[index]
		pr1=0
		:++++pr1=0.1
		:pr2=scop_random()
		pr2=1		

		:printf("%s %f %s %f %s %f %s %f\n", "+++++pr1: ", pr1, "pr2: ", pr2, "t0: ", t0, "index: ", index)
		

		if(pr2>pr1){
			:gmax=1
			:gmax2=1			
			:gmax=gmax+0.5
			:gmax2=gmax2+0.5
			:gampa = gmax * factor*(d((t-t0)/tau2) -d((t-delay)/tau1)) 
			:gnmda = gmax2 * block * factor2*(d((t-delay)/tau4) -d((t-delay)/tau3))
			g0_ampa=gampa
			g0_nmda=gnmda			
			t0=t		
			:++++printf("%s, %f, %s, %f\n", "******gampa: ", gampa, "gnmda: ", gnmda)
			:++++printf("%f\n", weight)
		} 
		if(index<=num-2){
		   index=index+1
		   net_send(interval,1)
		   :printf("%s\n", "hello!")	
		}
		
	}		
}		

: why write four functions?
FUNCTION  d(x) {
	if(x < 0) {
		d = 0
	}else{
		d= exp(-x)
	}
}

PROCEDURE relpr() {
VERBATIM	
	FILE *file;
	int size, ind;  //cannot use the var name i, because it refers to NONPSCIFIC ION
	float f;

	file=fopen("relpr.dat", "r");
	//fseek(file, 0, SEEK_END);
	//size=ftell(file);
	//rlpr=(float*)calloc(size, sizeof(float));
	
	
	ind=0;
	while(!feof(file)){
		fscanf(file, "%f", &f);
		rlpr[ind]=f;
		//++++printf("%f %lf\n", f, rlpr[ind]);
		
		//fscanf(file, "%f", &rlpr[ind]);  //don't why this doesn't work
		//+++++printf("%f, %d\n", rlpr[ind], ind);		
		ind++;
	
	}
	fclose(file);

ENDVERBATIM
}
