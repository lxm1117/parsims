#!/bin/bash

# Run pDE 
LAMDEF=~/Projects/ParSims/lam-axon7.def
LAMN=16

unset DISPLAY

SPEC=$1

LOG=`basename $SPEC`

iRun=1

while [ -e $LOG-$iRun.log ] || [ -e $LOG-$iRun.logE ]; do
    let ++iRun
done

LOG=$LOG-$iRun.log
LOGE=${LOG}E
echo "LOGS " $LOG " " $LOGE

#mpiexec -machinefile $LAMDEF -ssi rpi tcp -n $LAMN \
#    /Volumes/d1/Users/ximing/Projects/ParSims/pDE/pDE $SPEC $LOG > $LOGE 2>&1 &

#mpirun -np <number of processes> <program name and arguments>
mpirun -np $LAMN \
    ~/Projects/ParSims/pDEdir/pDE $SPEC $LOG > $LOGE 2>&1 &

# rm ~/MyTemp/pDE-*; rm kk.log; mpiexec -machinefile ~/Projects/ParSims/lam-axon+psd+spike+spine+dentate+axon2.def -ssi rpi tcp -n 29 ~/Projects/ParSims/pDE/pDE ~/Projects/ParSims/Runs_pDE/thin-1stspike/1spk-th-102406a-n420+Fix-h+Naf+KDR-v7-is2.pDE > kk.logE 2>&1 &

# rm ~/MyTemp/pDE-*; rm kk.log; mpiexec -machinefile ~/Projects/ParSims/lam-axon.def -ssi rpi tcp -n 9 ~/Projects/ParSims/pDE/pDE ~/Projects/ParSims/Runs_pDE/thin-1stspike/1spk-th-102406a-n420+Fix-h+Naf+KDR-v7-is2.pDE kk.log

# rm kk.log; mpiexec -machinefile ~/Projects/ParSims/lam-bhost.def -ssi rpi tcp -n 5 ~/Projects/ParSims/pDE/pDE ~/Projects/ParSims/Runs_pDE/HS3T/hs3t-3.pDE > hs3t-3.logE 2>&1 &
