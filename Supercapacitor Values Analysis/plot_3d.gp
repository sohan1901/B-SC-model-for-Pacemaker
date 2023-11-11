set term png
set output '3d_plot_using_gnuplot.png'

# Choose "Atrium" or "Ventrium"
chamber = "Atrium"

set xlabel "Charge in Supercapacitor\n(in charge units)" rotate parallel offset 0,-1,0
set ylabel "Supercapacitor charging rate\n(in charge units per millisecond)" rotate parallel offset 0,-1.8,0
set zlabel "Probability that Supercapacitor\nis not available to pace ".chamber rotate parallel
set dgrid3d 50,50
set hidden3d
set pm3d
set datafile separator whitespace  # Set the separator if your data file uses a different delimiter

# Plot for "Atrium"
if (chamber eq "Atrium") {
    splot 'Mydata.csv' using 1:2:3 with lines title 'Probability for that Supercapacitor is not available'
}

# Plot for "Ventrium"
if (chamber eq "Ventrium") {
    splot 'Mydata.csv' using 1:2:4 with lines title 'Probability for that Supercapacitor is not available'
}
