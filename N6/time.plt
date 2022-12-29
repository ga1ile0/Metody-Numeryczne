#!/usr/bin/gnuplot -persist

set terminal pngcairo size 800,600
red = "#FF0000"; green = "#00FF00"; blue = "#0000FF"; skyblue = "#87CEEB";
set output "time.png"
set yrange [0:7]
set style data histogram
set xtics format ""
set boxwidth 0.5
set ylabel "Czas [s]"
set xlabel "Metoda"
set xtics rotate
set grid
set title "Czas wykonania metod[s]"
set style fill solid

plot "time.dat" using 3:xtic(2) linecolor rgb skyblue

