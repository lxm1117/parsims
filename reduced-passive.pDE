# 06Apr10
#  Copied from 1spk-th-072006b-n420-Passive-v7c.pDE
#  Modified to have what 1spk-th-10606b-n420+Fix-h+Naf+KDR-3iALpaper-v7.pDE ha
#
#================================================================================
# No sensitivity analysis
Fit-SA 0 0
Tmp-dir MyTemp


#Fit  072006b   311   200     10     3    0.85  1.0 randE Projects/ParSims/Runs_pDE/thin-1stspike/main-n400-Vbtim-simL-v8d-reduced.hoc
#Fit  072006b   199   110     25     3    0.7  1.0 randE Projects/ParSims/Runs_pDE/thin-1stspike/main-n400-Vbtim-simL-v8d-reduced.hoc
#Fit  072006b   713   120     50     3    0.85  1.0 randE Projects/ParSims/Runs_pDE/thin-1stspike/main-n400-Vbtim-simL-v8d-reduced.hoc
Fit  072006b    191   200      10     3    0.85  1.0 randE /home/ximi/Projects/reduced-passive.hoc
#================================================================================
# 10oct08 4:40pm
# Set up traces for 072006b

# 10oct08 4pm
# Stage 0; select traces; time v=0 post spike for +1500 800 400 200
# Stich 800 with 3 4 5 spikes; select v of end trace, stitch at same volt after spike
# Determine bl_avg with 13 traces; BL_avg=-74.3052
# Determine BBF; need closer fit first.

# Run Passive fit with 9 traces
# Use lambda_f_d=0.1

Pop-init uniform noset

# Determined BBF=1.6 from run so far. Resume above

#================================================================================
VERBATIM
cell_file_name="n400td-pc2-sp-axn.hoc"

obfunc dfc_set_stims_etc(){
  print "check pDE dfc_set_stims++++++++++++++++++++"
 /*
  if(vdef("aX_hill_nseg"))\
    execute( "if(axon_hill.nseg<aX_hill_nseg) axon_hill.nseg=aX_hill_nseg" )
  if(vdef("aX_iseg_nseg")) \
    execute( "for i=0,aX_iseg_n-1 {if(axon_iseg[i].nseg<aX_iseg_nseg) axon_iseg[i].nseg= aX_iseg_nseg }" )
  if(vdef("aX_prox_nseg")) \
    execute( "for i=0,aX_prox_n-1 {if(axon_prox[i].nseg<aX_prox_nseg) axon_prox[i].nseg= aX_prox_nseg }" )
  if( vdef("aX_mnode_nseg" )) \
    execute( "forsec \"mnode\" if(nseg<aX_mnode_nseg) nseg= aX_mnode_nseg" )
  */
//  execute( "axon_prox.nseg = aX_prox_nseg" )
//  execute( "for i=0,aX_iseg_n-1 {axon_iseg[i].nseg= aX_iseg_nseg }" )
  stim.amp=$1
  stim.dur=$2
  stim.del=$3
  print "check stim.del +++++++++++++++++++++++++++"
  dfc_options_all( dfc_eD )
  return stim
}

obfunc dfc_set_tgt(){
  print "dfc_set_tgt()+++++++++++++++++++++++++++"
  dfc_tgt.stim_amp=$1
  dfc_tgt.stim_dur=$2
  dfc_tgt.stim_del=$3
  if( numarg()>3 ) dfc_tgt.cut_at2($4,$5)
  return dfc_tgt
}

proc dfc_sim_BBF(){
  dfc_simL_i.o(0).dc_shift(stim.del+BBFdelay,stim.del+stim.dur+BBFdelay,-BBF*stim.amp)
}

//================================================================================
// New stuff for pkbeg posfix

obfunc dfc_seg_look_options(){ local i localobj dI
  dI = new eMatch() if( numarg()>0)dI =$o1
  dI.seg_option	= 1101
  dI.seg_dt	= 0.09
  dI.seg_slp_dt	= 0.09
  dI.seg_slp_th	= 10
  dI.seg_v_th	= 0
  dI.seg_tiny_last	= 0
  if( strcmp(dfc_i.id,"072006b-2ms+1500pA-pkbeg") == 0 ){ dI.seg_dt=dI.seg_slp_dt= 0.02 }
  return dI
}

obfunc dfc_options_all(){ local i localobj eD
  if( numarg()==0 ) eD = dfc_seg_look_options()
  if( numarg()> 0 ) eD = dfc_seg_look_options($o1)

  eD.match_option	= 5.2
  eD.alpha = eD.beta = eD.gamma = eD.delta = eD.eta = eD.mF1 = eD.mF2 = eD.pkP = eD.pkPs = 0

  eD.ilog = 1
  return eD
}

// rough match to train; 
// necessary to avoid traces that don't return to baseline
// also check spikes also appear in axon
func dfc_trim(){ local i, t0_tail, f1, f2, r1, r2, res localobj eD
  f1=$1   f2=$2

  eD = dfc_options_all(dfc_eD)
  eD.eta 		= 1
  eD.mF2		= 200
  eD.pkP		= 1500*5
  eD.pkPs		= 1
  eD.pkPsA		= 1
  
  t0_tail = stim.del + stim.dur		// end of stimulus

  eD.tmin = t0_tail			// compare tails after end stimulus: axon vs tgt
  r2 = eD.m0( dfc_simL_i.o(1), dfc_tgt_i ) 

  eD.tmin = 0
  printf( "\n\t >>dfc_trim: DfpwPkdVa_aXe: " )
  r1 = eD.DfpwPkdVa_aXe(dfc_simL_i,dfc_tgt_i,-1,-1)	// 800=8.90, 400=15.2, 200=30.82, 1500=6.7  
  
  res = r1*f1 + r2*f2
  printf( "\n\t dfc_trim t0_tail %g r1,2 %g %g f1,f2 %g %g ri*fi %g %g\n\t res %g<<\n",\
  t0_tail, r1,r2, f1,f2, r1*f1, r2*f2, res )
  return res
}

//================================================================================
// match first spike (up to tmax)
// gamma and delta to match dV and ddV; largely independent of trace length/stim.amp
// eta scaled by trace length
//================================================================================
func dfc_pkbeg(){ local i, tmax, dV_f, eta_f, r1 localobj eD
  tmax = $1
  
  dV_f = 45*2
  eta_f = 300 + 100/(tmax-stim.del-1.1)	//  A + B/(time from stim.del to base of spike) A=for spike; B for before spike

  eD = dfc_eD //  eD = dfc_options_all(dfc_eD)
  // eD.mF2	= 200*10
  eD.mF2        = 6000 * stim.amp       // peak time error proportional to stimulation amplitude  
  eD.pkP        = 1500*5
  eD.pkPs	= 1
  eD.phi	= 600/116/10 	// range_dV/range_V	old=0.4 * 10
  eD.phi_1 	= 0.5+0.15
  eD.phi_2 	= 0.45-0.02
  eD.chi	= 1000/116/100	// range_ddV/range_V 	old=0.02 * 8
  eD.chi_1  	= 0.5+0.15	
  eD.chi_2 	= 0.15	
  if( numarg()>1) eD.chi_2=$2   // adhoc inserted to override
  eD.phi*=dV_f eD.chi*=dV_f

  eD.eta	= eta_f	
  // eD.mF2=0   eD.pkP=1000*eta_f	// for initial pop for Naf & KDR parms

  eD.tmax	= tmax
  printf( "\n\t >>dfc_pkbeg: DfpwPkdVa: " )
  r1 = eD.DfpwPkdVa(dfc_simL_i.o(0),dfc_tgt_i)	// 800=8.90, 400=15.2, 200=30.82, 1500=6.7  
  printf( "\n\t dfc_pkbeg: r1 %g \n\t<<\n", r1 )
  return r1
}


ENDVERBATIM

#================================================================================
# Fit-case name template func scale hoc_var hoc_before hoc_after tgt_files tgt_before tgt_after
# Active traces 20kHz

# For Naf & KDR initial parm search
#Fit-case 072006b-2ms+1500pA eMatch dfc_eD.DfpwPkdVa(dfc_simL_i.o(0),dfc_tgt_i) 5 soma dfc_set_stims_etc(1500/1000,2,5);dfc_eD.eta=1;dfc_eD.pkP=1500*5;dfc_eD.pkPs=1 dfc_sim_BBF() 2:/Volumes/d1/Users/ximing/cNeuro/Data/Grover-2006/072006b/ACSF/2ms+1500pA.htf blMax=4 dfc_set_tgt(1500/1000,2,21,136,16)

#Fit-case 072006b-100ms+800pA eMatch dfc_eD.DfpwPkdVa(dfc_simL_i.o(0),dfc_tgt_i) 5  soma dfc_set_stims_etc(800/1000,100,5);dfc_eD.eta=1;dfc_eD.pkP=1500*5;dfc_eD.pkPs=1 dfc_sim_BBF() 2:/Volumes/d1/Users/ximing/cNeuro/Data/Grover-2006/072006b/ACSF/100ms+800pA.htf blMax=4 dfc_set_tgt(800/1000,100,21,200,16)

# End for Naf & KDR initial parm search


# Note dfc_eD.seg_dt=dfc_eD.seg_slp_dt=0.02 cause end_stim almost on peak
# 2:active set ================================================================================
#Fit-case 072006b-2ms+1500pA-pkbeg eMatch dfc_pkbeg(7.36) 1 soma dfc_set_stims_etc(1500/1000,2,5);dfc_eD.seg_dt=dfc_eD.seg_slp_dt=0.02;dfc_eD.pkPs=3 dfc_sim_BBF() 2:/Volumes/d1/Users/ximing/cNeuro/Data/Grover-2006/072006b/ACSF_20kHz/2ms+1500pA.htf blMax=4 dfc_set_tgt(1500/1000,2,21,7.36+1+16,16)

# later runs use the following instead

#modified
#Fit-case 2ms+1500pA_chopped.dat eMatch dfc_pkbeg(7.36,0.05) 1 soma dfc_set_stims_etc(1500/1000,2,5);dfc_eD.pkPs=3; dfc_sim_BBF() 2:/Volumes/d1/Users/ximing/cNeuro/Data/Grover-2006/072006b/ACSF_20kHz/2ms+1500pA.htf blMax=4 dfc_set_tgt(1500/1000,2,21,7.36+1+16,16)

#Fit-case 072006b-2ms+1500pA-pkbeg eMatch dfc_pkbeg(7.36,0.05) 1 soma dfc_set_stims_etc(1500/1000,2,5);dfc_eD.pkPs=3; dfc_sim_BBF() 2:/Volumes/d1/Users/ximing/cNeuro/Data/Grover-2006/072006b/ACSF_20kHz/2ms+1500pA.htf blMax=4 dfc_set_tgt(1500/1000,2,21,7.36+1+16,16)

# Note about TRIMMED file. Each trace was cut at a diffent time from same trace 2 of 072006b-100ms+800pA
# So, all trimmed traces should be compared to trace 2:072006b-100ms+800pA
# Trimmed #1; 26.39
#Fit-case 072006b-100ms+800pA-tr-pkbeg eMatch (dfc_trim(1,1)+dfc_pkbeg(10.03)) 1 soma;axon_inode[4] dfc_set_stims_etc(800/1000,26.39-5,5) dfc_sim_BBF() 1:/Volumes/d1/Users/ximing/cNeuro/Data/Grover-2006/072006b/ACSF_20kHz/100ms+800pA-trimmed.htf blMax=4 dfc_set_tgt(800/1000,26.39-5,5)

# Trimmed #2; 37.49
#Fit-case 072006b-100ms+800pA-tr-pkbeg eMatch (dfc_trim(1,1)+dfc_pkbeg(10.03)) 1 soma;axon_inode[4] dfc_set_stims_etc(800/1000,37.49-5,5) dfc_sim_BBF() 2:/Volumes/d1/Users/ximing/cNeuro/Data/Grover-2006/072006b/ACSF_20kHz/100ms+800pA-trimmed.htf blMax=4 dfc_set_tgt(800/1000,37.49-5,5)

#Fit-case 072006b-100ms+400pA-pkbeg eMatch dfc_pkbeg(16.56) 1 soma dfc_set_stims_etc(400/1000,100,5) dfc_sim_BBF() 2:/Volumes/d1/Users/ximing/cNeuro/Data/Grover-2006/072006b/ACSF_20kHz/100ms+400pA.htf blMax=4 dfc_set_tgt(400/1000,100,21,16.56+1+16,16)

#Fit-case 072006b-100ms+200pA-pkbeg eMatch dfc_pkbeg(34.01) 1 soma dfc_set_stims_etc(200/1000,100,5) dfc_sim_BBF() 2:/Volumes/d1/Users/ximing/cNeuro/Data/Grover-2006/072006b/ACSF_20kHz/100ms+200pA.htf blMax=4 dfc_set_tgt(200/1000,100,21,34.01+1+16,16)

#--------------------------------------------------------------------------------
# Passive traces (all 10kHz)
#+750 has no spike; we could use m0; but we want to penalize unwanted spikes
#Fit-case 072006b-2ms+750pA eMatch dfc_eD.DfpwPkdVa(dfc_simL_i.o(0),dfc_tgt_i) 6.4*dfc_PassWgt*100/tstop soma dfc_set_stims_etc(750/1000,2,5);dfc_eD.eta=1 dfc_sim_BBF() 2:/Volumes/d1/Users/ximing/cNeuro/Data/Grover-2006/072006b/ACSF_0kHz/2ms+750pA.htf blMax=4 dfc_set_tgt(750/1000,2,21,136,16)

# m0
Fit-case 072006b-2ms+375pA eMatch dfc_eD.m0(dfc_simL_i.o(0),dfc_tgt_i) 4*dfc_PassWgt*100/tstop soma dfc_set_stims_etc(375/1000,2,5) dfc_sim_BBF() 2:/home/ximi/Projects/ParSims/from_axon_new/htf_files/2ms+375pA.htf blMax=4 dfc_set_tgt(375/1000,2,21,136,16)

# m0 
#Fit-case 072006b-100ms+100pA eMatch dfc_eD.m0(dfc_simL_i.o(0),dfc_tgt_i) 7.9*dfc_PassWgt*100/tstop soma  dfc_set_stims_etc(100/1000,100,5) dfc_sim_BBF() 2:/Volumes/d1/Users/ximing/cNeuro/Data/Grover-2006/072006b/ACSF_20kHz/100ms+100pA.htf blMax=4 dfc_set_tgt(100/1000,100,21,300,16)

#====== 20ms
# m0
Fit-case 072006b-20ms+50pA eMatch dfc_eD.m0(dfc_simL_i.o(0),dfc_tgt_i) 2*dfc_PassWgt*100/tstop soma dfc_set_stims_etc(50/1000,20,5) dfc_sim_BBF() 2:/home/ximi/Projects/ParSims/from_axon_new/htf_files/20ms+50pA.htf blMax=4 dfc_set_tgt(50/1000,20,21,120,16)

# m0
Fit-case 072006b-20ms-50pA eMatch dfc_eD.m0(dfc_simL_i.o(0),dfc_tgt_i) 2*dfc_PassWgt*100/tstop soma dfc_options_all();dfc_set_stims_etc(-50/1000,20,5) dfc_sim_BBF() 2:/home/ximi/Projects/ParSims/from_axon_new/htf_files/20ms-50pA.htf blMax=4 dfc_set_tgt(-50/1000,20,21,120,16)


# m0
Fit-case 072006b-20ms-200pA eMatch dfc_eD.m0(dfc_simL_i.o(0),dfc_tgt_i) 8.3*dfc_PassWgt*100/tstop soma dfc_options_all();dfc_set_stims_etc(-200/1000,20,5) dfc_sim_BBF() 2:/home/ximi/Projects/ParSims/from_axon_new/htf_files/20ms-200pA.htf blMax=4 dfc_set_tgt(-200/1000,20,21,120,16)

#====== 500ms
# m0
#Fit-case 072006b-500ms+50pA eMatch dfc_eD.m0(dfc_simL_i.o(0),dfc_tgt_i) 4.1*dfc_PassWgt*100/tstop soma dfc_set_stims_etc(50/1000,500,21) dfc_sim_BBF() 2:/Volumes/d1/Users/ximing/cNeuro/Data/Grover-2006/072006b/ACSF_0kHz/500ms+50pA.htf blMax=19 dfc_set_tgt(50/1000,500,21,800,0)

# m0
#Fit-case 072006b-500ms-50pA eMatch dfc_eD.m0(dfc_simL_i.o(0),dfc_tgt_i) 3.9*dfc_PassWgt*100/tstop soma dfc_set_stims_etc(-50/1000,500,21) dfc_sim_BBF() 2:/Volumes/d1/Users/ximing/cNeuro/Data/Grover-2006/072006b/ACSF_0kHz/500ms-50pA.htf blMax=19 dfc_set_tgt(-50/1000,500,21,800,0)

# m0
#Fit-case 072006b-500ms-200pA eMatch dfc_eD.m0(dfc_simL_i.o(0),dfc_tgt_i) 12.7*dfc_PassWgt*100/tstop soma dfc_set_stims_etc(-200/1000,500,21) dfc_sim_BBF() 2:/Volumes/d1/Users/ximing/cNeuro/Data/Grover-2006/072006b/ACSF_0kHz/500ms-200pA.htf blMax=19 dfc_set_tgt(-200/1000,500,21,800,0)

# --------------------------------------------------------------------------------
#
# Fit-parm	name			set		fit-lims	

Set-parm	dfc_PassWgt		1		0:1
Set-parm	RmCm_spine_gbar		0		0:1
Set-parm	Spine_number		30000		0:40000
Set-parm 	BL_avg         	   	-74.3052	-80:-60	
Set-parm 	BBF            	         1.60		0:20
Set-parm 	BBFdelay       	         0		0:0.1
Set-parm 	lambda_f_d		0.1		0.1:2
#Set-parm 	G_ena          	      65.4		60:70
#Set-parm 	G_ek           	     -89.5		-95:-85
Set-parm 	G_eh           	       -30		-40:-10
Set-parm 	celsius        	        35		22:37

#Fit-parm	soma_diam_f		1		0.1:3
Fit-parm 	G_Rm           	   	200		10:400
Fit-parm 	G_cm           	  	0.9626	 	0.25:2.5
Fit-parm 	G_Ra           	   	45		2:150
#Set-parm 	G_e_pas        	  	-77.7604	-100:-65

#---------------------------------------------------------------------------
#Set-parm	soma_cm			1.0		0:3
#Set-parm	soma_Rm			40  		1:100
#Set-parm	soma_Ra			100 		1:500
#Set-parm	soma_l			17	 	4:30
#Set-parm	soma_diam		13.5		2:30

#Set-parm	aX_hill_nseg		5	1:100
#Set-parm	aX_hill_l		5	1:50
#Set-parm	aX_hill_d1		4	0.1:50
#Set-parm	aX_hill_d2		1	0.1:50

#Set-parm	aX_iseg_nseg		2	1:100
Set-parm	aX_iseg_n	        2	11:50
#Set-parm	aX_iseg_l		58.30	1:100
#Set-parm	aX_iseg_d		0.5	0.2:1.0

#Set-parm	aX_prox_nseg		11	1:100
#Set-parm	aX_prox_n		3	1:50
#Fit-parm	aX_prox_l		150	10:500
#Fit-parm	aX_prox_d		0.5	0.2:1.0
#Set-parm	aX_prox_l		150	10:500
#Set-parm	aX_prox_d		0.5	0.2:1.0

#Set-parm        aX_inode_n              2       1:50
#Set-parm	aX_inode_d		0.4	0.1:2
#Set-parm	aX_inode_l		1	0.1:5

#Set-parm	aX_mnode_nseg		3	1:100
#Set-parm       aX_mnode_n	        3       1:100 
#Set-parm	aX_mnode_d		0.4	1:100
#Set-parm	aX_mnode_l		100	1:1000

#Set-parm	aX_cm			1.0	0:3
#Set-parm	aX_Rm			40  	1:100
#Set-parm	aX_Ra			100 	1:500

#Set-parm	aXm_cm			0.04	0:1
#Set-parm	aXm_Rm			100	1:500

#--------------------------------------------------------------------------------------
Fit-parm 	Gbar_Naf       	   50			10:300
Set-parm	s0_Gbar_Naf	   500			80:1000
Set-parm	aXh_Gbar_Naf	   500			100:7000
Set-parm        aXi0_Gbar_Naf      2500		        100:8500
Set-parm        aXi1_Gbar_Naf      3500                 100:8000
Set-parm        aXr_Gbar_Naf       3000                 1000:5000
Set-parm        aXm_Gbar_Naf       50                   10:100

Set-parm 	gates_n_Naf_i0 	         1		1:3
Set-parm 	vhalf_n_Naf_i0 	  	-30		-45:-25
Set-parm 	slope_n_Naf_i0 	  	-4.8		-10:-3
Set-parm 	tauA_n_Naf_i0  	   	0.01		0.0001:0.01
Set-parm 	tauG_n_Naf_i0  	  	0.8		0.03:0.97

Set-parm	vhalf_h_Naf_i0		-64		-68:-48
Set-parm	slope_h_Naf_i0		9.06		5:15
Set-parm	tauA_h_Naf_i0		8		5:50
Set-parm	tauG_h_Naf_i0		0.5		0.2:0.8

Set-parm 	gates_n_Naf_i1 	         1		1:3
Set-parm 	vhalf_n_Naf_i1 	  	-35		-58:-35
Set-parm 	slope_n_Naf_i1 	  	-5		-10:-3
Set-parm 	tauA_n_Naf_i1  	   	0.01		0.0001:0.01
Set-parm 	tauG_n_Naf_i1  	  	0.5		0.03:0.97

Set-parm	vhalf_h_Naf_i1		-67		-68:-55
Set-parm	slope_h_Naf_i1		9		3:15
Set-parm	tauA_h_Naf_i1		8		5:50
Set_parm	tauG_h_Naf_i1		0.5		0.2:0.8


#---------------------------------------------------------------------------------
Fit-parm 	Gbar_KDR		28		10:1000
Set-parm	s0_Gbar_KDR	        200	    	80:7000
Set-parm	aXh_Gbar_KDR		200		100:7000
Set-parm 	aXi0_Gbar_KDR      	1500		100:7000
Set-parm 	aXi1_Gbar_KDR   	2000		100:7000
Set-parm 	aXm_Gbar_KDR   	  	5		0.1:100
Set-parm 	aXr_Gbar_KDR   	   	800		10:1000
Set-parm	Gbar_KDR_dslope		0		0:0.008

Set-parm 	gates_n_KDR_i1 	         1		1:4
Set-parm 	vhalf_n_KDR_i1 	   	2		-19:10
Set-parm 	slope_n_KDR_i1 	  	-13		-15:-6
Set-parm 	tauA_n_KDR_i1  	   	8		1:50
Set-parm 	tauG_n_KDR_i1  	  	0.9		0.03:0.97

#---------------------------------------------------------------------------------

Fit-parm        Gbar_KA                2              1:100
Set-parm	vhalf_n_KA_i1         -30	         -35:5
Set-parm        slope_n_KA_i1         -10              -40:-5
Set-parm        tauA_n_KA_i1           1               0.1:30
Set-parm        vhalfD_h_KA_i1	      -35              -60:-20
Set-parm        slope_h_KA_i1          10                3:20
Set-parm        tauA_h_KA_i1           20               31:150
Set-parm        Gbar_KA_dslope         0.008           0.0001:0.03

#---------------------------------------------------------------------------------
Fit-parm 	Gbar_h    	  	0.1058		0.01:4
Set-parm 	Gbar_h_dslope  	     0.008		0.0001:0.03
Set-parm 	gates_n_h_i0   	         1		1:3
Set-parm 	vhalf_n_h_i0   	  	-92.07		-110:-70
Set-parm 	slope_n_h_i0   	   	10		4:12
Set-parm 	tauA_n_h_i0    	   	100		10:100
Set-parm 	tau0_n_h_i0    	     0.001		0.001:0.1
Set-parm 	tauF_n_h_i0    	         0		-3.5:2
Set-parm 	tauG_n_h_i0    	  	0.5		0.05:0.95
Set-parm 	tauDv_n_h_i0   	   	0		-55:55

