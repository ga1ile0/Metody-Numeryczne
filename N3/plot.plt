#!/usr/bin/gnuplot -persist

set grid
set xlabel "Wartości uk"
set ylabel "Wartści xk"
set title "Wykres (xk, uk) dla N=1000"
plot 'data.txt' using 1:2 with lines