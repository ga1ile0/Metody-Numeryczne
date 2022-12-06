#!/usr/bin/gnuplot -persist

set grid
set title "Wykres dla x = pi/2"
set logscale xy
set xlabel "h"
set ylabel "blad"
plot 'data.dat' using 1:5 with lines, 'data.dat' using 1:6 with lines, 'data.dat' using 1:7 with lines