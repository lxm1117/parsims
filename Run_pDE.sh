mpirun -np $LAMN \
    ~/Projects/ParSims/pDEdir/pDE $SPEC $LOG > $LOGE 2>&1 &

# rm ~/MyTemp/pDE-*; rm kk.log; mpiexec -machinefile ~/Projects/ParSims/lam-axon+psd+spike+spine+dentate+axon2.def -ssi rpi tcp -n 29 ~/Projects/ParSims/pDE/pDE ~/Projects/ParSims/Runs_pDE/thin-1stspike/1spk-th-102406a-n420+Fix-h+Naf+KDR-v7-is2.pDE > kk.logE 2>&1 &

# rm ~/MyTemp/pDE-*; rm kk.log; mpiexec -machinefile ~/Projects/ParSims/lam-axon.def -ssi rpi tcp -n 9 ~/Projects/ParSims/pDE/pDE ~/Projects/ParSims/Runs_pDE/thin-1stspike/1spk-th-102406a-n420+Fix-h+Naf+KDR-v7-is2.pDE kk.log

# rm kk.log; mpiexec -machinefile ~/Projects/ParSims/lam-bhost.def -ssi rpi tcp -n 5 ~/Projects/ParSims/pDE/pDE ~/Projects/ParSims/Runs_pDE/HS3T/hs3t-3.pDE > hs3t-3.logE 2>&1 &
