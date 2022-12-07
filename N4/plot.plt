#!/usr/bin/gnuplot -persist

set grid
set xlabel "Wartości xk"
set ylabel "Wartosci uk"
set title Wykres (xk, uk) dla N=1000
plot 'data2.txt' using 1:2 with lines