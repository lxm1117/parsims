COMMENT

Two exponential synapse ampa and nmda with block

ENDCOMMENT

NEURON {
	POINT_PROCESS expsyn2c_col3
	RANGE e, g 
	RANGE ampar_bound, ampar_unbound, ampar_active, ampar_tot, gampar, scca, iampar
	RANGE nmdar_bound, nmdar_unbound, nmdar_active, nmdar_tot, gnmdar, sccn, inmdar 
	RANGE nmdar_Mg
	RANGE num, tot_num, del, interval_s, interval_l
	NONSPECIFIC_CURRENT i
	GLOBAL k_ampar, alpha_ampar, beta_ampar, k_nmdar, alpha_nmdar,beta_nmdar :, stimon
}

UNITS {
	(nA) = (nanoamp)
	(mV) = (millivolt)
	(uS) = (microsiemens)
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
	alpha_nmdar=0.34 (1/ms)
	beta_nmdar=0.6(1/ms)
	tmp
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
	ampar_unbound   (1)
	nmdar_unbound   (1)

	stim_index
	rlpr[85]
	pr1
	pr2
	num
	tot_num
	del  (ms)
	interval_s (ms)
	interval_l (ms)
	:stimon
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
}

DERIVATIVE state {
	ampar_bound'=-k_ampar*ampar_bound - beta_ampar*ampar_bound + alpha_ampar*ampar_active:+syn_weight*0.4*ampar_unbound
	ampar_active'=beta_ampar*ampar_bound - alpha_ampar*ampar_active
	nmdar_bound'=-k_nmdar*nmdar_bound - beta_nmdar*nmdar_bound + alpha_nmdar*nmdar_active:+syn_weight*0.4*nmdar_unbound
	nmdar_active'=beta_nmdar*nmdar_bound - alpha_nmdar*nmdar_active	
}

NET_RECEIVE(weighti (uS)) { 
	if(flag==1){
		tmp=fmod(stim_index,num)	
		pr1=rlpr[tmp]
		pr2=scop_random()
				
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
			nmdar_bound=nmdar_bound+0.6*nmdar_unbound
			printf("%s %f %s %f %s %f %s %f %s %f\n", "pr1: ", pr1, "pr2: ", pr2, "stim_index: ", stim_index, "ampar_unbound: ", ampar_unbound, "nmdar_unbound: ", nmdar_unbound)
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

	file=fopen("relpr_smooth_col3.dat", "r");
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


