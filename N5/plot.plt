#!/usr/bin/gnuplot -persist

set grid
set title "(xn = (n-1)h,un)"
set xlabel "Wartości xn"
set ylabel "Wartości un"
plot "dataN5.txt" using 1:3 with lines