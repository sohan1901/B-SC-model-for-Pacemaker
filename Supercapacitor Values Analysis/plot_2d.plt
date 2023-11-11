set terminal png
set output "2d_plot_using_gnuplot.png"

# Choose "Atrium" or "Ventrium"
chamber = "Ventrium"
max_charge_in_supercapacitor = 3500000000 # Change this value to plot "charging rate vs probability of Supercapacitor not available" for different Supercapacitor values

# Check if chamber is "Atrium" or "Ventrium" and set the appropriate y-axis column
y_column = (chamber eq "Atrium") ? 3 : 4

# Convert max_charge_in_supercapacitor to a string
max_charge_str = sprintf("%.0f", max_charge_in_supercapacitor)

set title sprintf("Supercapacitor charging rate vs Probability that Supercapacitor is not\navailable to pace %s when max charge in supercapacitor\nis %s charge units", chamber, max_charge_str)
set xlabel "Supercapacitor charging rate\n(in charge units per millisecond)"
set ylabel sprintf("Probability that Supercapacitor is\nnot available to pace %s", chamber)

# Plot using the chosen y-axis column
plot "Mydata.csv" using ($1 == max_charge_in_supercapacitor ? $2 : 1/0):(column(y_column)) with lines title "Probability that Supercapacitor\nis not available to pace ".chamber lw 1
