# Supercapacitor Analysis Tool
# Overview
This repository provides a simulation and analysis tool for studying the optimal capacitance and rate of charging of a supercapacitor used in pacemaker batteries. The primary goal is to analyze the relationship between the maximum charge the supercapacitor can hold, the rate of charging, and the probability of the supercapacitor not being available to pace the heart.

# Requirements
To run the simulation, ensure you have the following:

- A UNIX-based system
- A C compiler installed
- Either gnuplot or Python with Matplotlib for graph generation
# Usage Instructions
1. Compile the Code:

   - Use the C compiler to compile the provided code (pacemaker_battery.c).
   - This compilation will generate a CSV file named Mydata.csv containing the probability values for different supercapacitor capacitance and charging rates.
2. Graph Generation:

   - If you have gnuplot, execute the plot_3d.gp file using the command gnuplot plot_3d.gp to visualize 3D results. Additionally, use plot_2d.plt using the command gnuplot plot_2d.plt to analyze results for a specific capacitance value.
   - If you have Python along with Matplotlib, directly run the plot.py file to visualize and analyze the simulation results.
# File Descriptions
- pacemaker_battery.c: C code for the simulation.
- gen_cardiac_signal_trace.c: C code for generating cardiac trace
- plot_3d.gp: Gnuplot script for 3D graph visualization.
- plot_2d.plt: Gnuplot script for 2D graph visualization (specific capacitance).
- plot.py: Python script for graph generation using Matplotlib.
# Results
The generated graphs provide insights into the relationship between supercapacitor parameters and the probability of non-availability for pacing the heart. Analyzing these results can guide the selection of optimal capacitance and charging rates for reliable pacemaker performance.
