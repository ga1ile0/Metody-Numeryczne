#!/usr/bin/gnuplot -persist

set terminal pngcairo size 800,600
red = "#FF0000"; green = "#00FF00"; blue = "#0000FF"; skyblue = "#87CEEB";
set output "n_iterations.png"
set yrange [0:2300000]
set style data histogram
set xtics format ""
set boxwidth 0.5
set ylabel "Liczba iteracji"
set xlabel "Metoda"
set xtics rotate
set grid
set title "Liczba iteracji"
set style fill solid

plot "iterations.dat" using 3:xtic(2) linecolor rgb green

