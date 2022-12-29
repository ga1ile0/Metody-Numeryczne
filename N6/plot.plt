#!/usr/bin/gnuplot -persist

set terminal pngcairo size 800,600
set output "plot.png"
set yrange [0.85:1.05]
set xrange [-0.1:1.1]
set grid
set title "(xn = (n-1)h,un)"
set xlabel "Wartości xn"
set ylabel "Wartości un"
plot "data.txt" using 1:3 with lines