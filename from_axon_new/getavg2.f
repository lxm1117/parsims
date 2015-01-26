      IMPLICIT DOUBLE PRECISION (A-H, O-Z)
       CHARACTER*40  label, filein, filout
       ir=40
       iw=41
       write(6,*) ' enter input file name '
       read (5,*) filein
       write(6,*) ' enter output file name '
       read(5,*) filout
       write(6,*) ' enter first time point'
       read(5,*) first
c
       open(file=filein, unit=ir, status='old')
       open(file=filout, unit=iw, status='unknown')
c
       read(ir,*) label
       read(ir,*) points
       write(6,*) ' points = ', points
       ave=0
       tot=0
       de=1
       do 100 i=1,points-1 
          read(ir,*, end=999) time, value
          if (time .ge. first) then
             tot=tot+value
             ave = tot/de
             de=de+1
             write(iw,*) time, ave, value
          endif
 100   continue
c
 999   continue
       stop
       end
