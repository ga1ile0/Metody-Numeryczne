#!/usr/bin/gnuplot -persist

set grid
set logscale xy
set title "Wykres dla x = 1"
set xlabel "h"
set ylabel "blad"
plot 'data.dat' using 1:2 with lines