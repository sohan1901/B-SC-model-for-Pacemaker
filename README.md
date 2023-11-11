# Battery-Supercapacitor(B-SC) model for Pacemaker
This project contains code to simulate a hybrid battery supercapacitor model for cardiac pacemakers. The code is written in C and can only run on UNIX-based systems.

# Getting Started
To run the simulation, a UNIX-based system and a C compiler must be installed. Once you have these, you can follow these steps:
- Clone the repository to your local machine.
- Compile the code (pacemaker_battery.c file) using your C compiler.
- Run the executable file by giving an additional parameter about whether the person is in rest, neutral, or working mode.

# Usage
The simulation will generate a random cardiac trace (generating_cardiac_signal_trace.c file will do it) which will be stored in cardiac_signal_trace.txt and the outputs of the simulation will be the final voltage battery and the number of times the supercapacitor was not available to pace the heart, after some fixed number of cycles.
