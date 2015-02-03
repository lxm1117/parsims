COMMENT:

Two exponential synapse ampa and nmda with block

ENDCOMMENT

NEURON {
	POINT_PROCESS expsyn2c_col4
	:USEION ca READ cai, cao :WRITE ica
	:USEION na READ nai, nao
	:USEION k  READ ki, ko
	RANGE e, g 
	RANGE ampar_bound, ampar_unbound, ampar_active, ampar_tot, gampar, scca, iampar
	RANGE nmdar_bound, nmdar_unbound, nmdar_active, nmdar_tot, gnmdar, sccn, inmdar, inmdar_ca, inmdar_k, inmdar_na, itest
	RANGE nmdar_Mg
	RANGE num, tot_num, del, interval_s, interval_l
	
	NONSPECIFIC_CURRENT i
	GLOBAL k_ampar, alpha_ampar, beta_ampar, k_nmdar, alpha_nmdar, beta_nmdar, alpha2_nmdar :, stimon
	POINTER randObjPtr
}

UNITS {
	(nA) = (nanoamp)
	(mV) = (millivolt)
	(uS) = (microsiemens)
	(mM) = (milli/liter)
	FARADAY = (faraday) (coulomb)
	R = (k-mole) (joule/degC)
}

PARAMETER {
        scca = 8e-6     (uS)
        sccn = 50e-6    (uS)
        e = 1.3827              (mV)
        mg = 1.2         :       (mM)    : magnesium concentration (mM)
	ampar_tot=80
	nmdar_tot=20

	k_ampar=2        (1/ms)
	alpha_ampar=2    (1/ms)
	beta_ampar=2     (1/ms)
	k_nmdar=0.02     (1/ms)
	alpha_nmdar=0.2 (1/ms) :0.34 (1/ms)
	alpha2_nmdar=0.14 (1/ms)
	beta_nmdar=0.6(1/ms)
	tmp
	:f=FARADAY/1000		  (coulomb)	
	f=96.48456	 (coulomb)
	rtof=26.73 (mV)
	de1
	de2

	ko_p = 1.875	(mM)
	nao_p=108.75		(mM)
	cao_p=0.38		(mM)
	ki_p=105		(mM)
	nai_p=7.5		(mM)
	cai_p=3.8e-6		(mM)


}

ASSIGNED { 
	v 	(mV) 
	i 	(nA) 
	g 	(uS) 
        gampar           (uS)
        gnmdar           (uS)
        block   (1)
        iampar           (nA)
        inmdar           (nA)
	inmdar_ca	 (nA)
	inmdar_k	 (nA)
	inmdar_na	 (nA)
	itest

	ampar_unbound   (1)
	nmdar_unbound   (1)
	pna	
	c
	d
	ee

	stim_index
	rlpr[85]
	pr1
	pr2
	:pr3
	num
	tot_num
	del  (ms)
	interval_s (ms)
	interval_l (ms)
	:stimon

	randObjPtr
}	

PROCEDURE seed(x){
	set_seed(x)
}

INITIAL { 
	stim_index=0
	:stimon=0
		
	ampar_active=0
	ampar_bound=0
	nmdar_active=0
	nmdar_bound=0

	relpr()
	if(stim_index<tot_num) {
		net_send(del,1)
	}
	:set_seed(5061983)
}

STATE { ampar_bound
	ampar_active
	nmdar_bound
	nmdar_active
}

BREAKPOINT {
        UNITSOFF
        block = 8.8*exp(v/12.5)/(mg + 8.8*exp(v/12.5))
        UNITSON
	if(stim_index<tot_num){
		SOLVE state METHOD cnexp
	}
	ampar_unbound=ampar_tot-ampar_active-ampar_bound
	nmdar_unbound=nmdar_tot-nmdar_active-nmdar_bound
	if(ampar_unbound <0) { ampar_unbound=0}
	if(nmdar_unbound <0) { nmdar_unbound=0}

	gampar=scca*ampar_active
	gnmdar=sccn*nmdar_active*block
	g=gampar+gnmdar
	iampar=gampar*(v-e)
	inmdar=gnmdar*(v-e)
	i=iampar+inmdar
	
	de1=1-exp(-v/rtof)
	de2=1-exp(-2*v/rtof)
	c=f/rtof*v/de1*(nai_p-nao_p*exp(-v/rtof))
	d=f/rtof*v/de1*(ki_p-ko_p*exp(-v/rtof))
	ee=4*f/rtof*v/de2*(cai_p-cao_p*exp(-2*v/rtof))

	pna=inmdar/(c+d+10.6*ee)
	inmdar_ca=ee*10.6*pna
	inmdar_na=c*pna
	inmdar_k=d*pna
	itest=inmdar-(inmdar_k+inmdar_ca+inmdar_na)
}

DERIVATIVE state {
	ampar_bound'=-k_ampar*ampar_bound - beta_ampar*ampar_bound + alpha_ampar*ampar_active:+syn_weight*0.4*ampar_unbound
	ampar_active'=beta_ampar*ampar_bound - alpha_ampar*ampar_active
	nmdar_bound'=-k_nmdar*nmdar_bound - beta_nmdar*nmdar_bound + alpha_nmdar*nmdar_active:+syn_weight*0.4*nmdar_unbound
	nmdar_active'=beta_nmdar*nmdar_bound - alpha_nmdar*nmdar_active - alpha2_nmdar*nmdar_active
}

NET_RECEIVE(weighti (uS)) { 
	if(flag==1){
		tmp=fmod(stim_index,num)	
		pr1=rlpr[tmp]
		pr2=randGen()
		:pr3=scop_random()
	
		printf("%s %f %s %f\n", "pr1: ", pr1, "pr2: ", pr2)		
	
		if(pr2<pr1){
			COMMENT
			if(stimon==0) {
				ampar_bound=ampar_tot
				nmdar_bound=nmdar_tot
				ampar_unbound=ampar_tot-ampar_active-ampar_bound
				nmdar_unbound=nmdar_tot-nmdar_active-nmdar_bound
				stimon=1
			}
			ENDCOMMENT

			ampar_bound=ampar_bound+0.6*ampar_unbound
			:nmdar_bound=nmdar_bound+0.6*nmdar_unbound
			nmdar_bound=nmdar_bound+0.8*nmdar_unbound
			printf("%s %f %s %f %s %f  %s %f %s %f %s %f\n",  "stim_index: ", stim_index, "ampar_unbound: ", ampar_unbound, "nmdar_unbound: ", nmdar_unbound, "ampar_active: ", ampar_active, "nmdar_active: ", nmdar_active, "ampar_bound: ", ampar_bound)
		}
		
		if(stim_index<=tot_num-2){
		   if(stim_index > 0 && fmod(stim_index+1,num)==0) {
			net_send(interval_l,1)
		   } else { net_send(interval_s,1)}
		   stim_index=stim_index+1
		}


		
	}		
}		

PROCEDURE relpr() {
VERBATIM	
	FILE *file;
	int size, ind;  //cannot use the var name i, because it refers to NONPSCIFIC ION
	float f;

	file=fopen("relpr_smooth_col4.dat", "r");
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

VERBATIM
double nrn_random_pick(void* r);
void* nrn_random_arg(int argpos);
ENDVERBATIM

FUNCTION randGen(){
VERBATIM
	if(_p_randObjPtr){
		/*
		:Supports separate independent but reproducible streams for
		: each instance. However, the corresponding hoc Random
		: distribution MUST be set to Random.uniform(0,1)
		*/
		_lrandGen=nrn_random_pick(_p_randObjPtr);

	}else{
		hoc_execerror("Random object ref not set correctly for randObjPtr", "only via hoc Random");
	
	}
ENDVERBATIM
}

PROCEDURE setRandObjRef(){
VERBATIM
	void** pv4 = (void**)(&_p_randObjPtr);
	if(ifarg(1)){
		*pv4 = nrn_random_arg(1);
	}else{
		*pv4 = (void*)0;
	}
ENDVERBATIM
}
