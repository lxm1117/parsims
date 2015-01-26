#self defined linetype 3. To use, specify as "ls 3"
set style line 3 lt -1 lw 3 pt 6
plot"relpr_smooth_col4.dat" ls 3 w linespoints title " "
set xrange [0:80]
set yrange [0:1]
set xlabel "stimulations"
set ylabel "release probability"
set border lw 3
set output 'release.png'
set terminal pngcairo size 1024, 343 enhanced font 'Verdana,15'
replot
