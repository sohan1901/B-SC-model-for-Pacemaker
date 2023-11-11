#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>
unsigned cpu_clk_freq = 1.5e+9; // cycles per second
unsigned p_wavelength = 110;	//*1.0e-3*cpu_clk_freq// 110 msec, atrium sensing duration
unsigned pulse_duration = 1;	//*1.0e-3*cpu_clk_freq// 1 msec, pacing signal duration
unsigned qrs_complex = 100;		//*1.0e-3*cpu_clk_freq// 100 msec, ventricle sensing duration
unsigned AVI_length = 150;		//*1.0e-3*cpu_clk_freq// 150 msec, time for ventricle fill after atrial contraction
unsigned PVARP_length = 350;	//*1.0e-3*cpu_clk_freq// 350 msec,  ignoring false atrium activity
unsigned VAI_length = 850;		//*1.0e-3*cpu_clk_freq;// 850 msec, time between ventricle activity followed by atrial sense
unsigned MSI = 500;				//*1.0e-3*cpu_clk_freq// 500 msec, time between atrial events to switch mode
unsigned LRI = 1000;			//*1.0e-3*cpu_clk_freq// 1000 msec,  longest interval between two ventricular events
#define max_cycles 10000
// SOHAN
double current_for_sensing_atrium = 22.3;							// 22.3 mA of current is required to sense atrium
double current_for_sensing_ventrium = 82.5;							// 82.5 mA of current is required to sense ventrium
double current_to_pace_atrium = 64.0;								// 64.0 mA of current is required to pace atrium
double current_to_pace_ventrium = 112.8;							// 112.8 mA of current is required to pace ventrium
long double battery_capacity = 5.4e+16;								// Battery capacity = 1500 mAh = 5.4e+16 charge units
double mAh_to_coulomb = 3.6;										// 1 mAh = 3.6 coulombs
long double coulomb_to_charge_units = 10.0e+12;						// 1 Coulomb = 10.0E+12 charge units
long double mAh_to_charge_units = 3.6 * (10.0e+12);					// 1 mAh = 3.6*(10*(10^13)) charge units
double present_charge_in_supercapacitor = 0;						// Present charge in Supercapacitor in terms of Charge units
long long max_charge_in_supercapacitor = 500 * (10.0e+12) * (1e-6); // Maximum Charge that Supercapacitor can hold (Assumed Value)
double rate_at_which_supercapacitor_is_charged = 500000;			// Supercapacitor charging rate (Assumed Value)
int pa_by_battery = 0;												// Counter to hold the number of times supercapacitor is not available to pace atrium
int pv_by_battery = 0;												// Counter to hold the number of times supercapacitor is not available to pace ventrium
// SOHAN
unsigned int sense_atrium(FILE *fp);
void pace_atrium();
unsigned int set_AVI_counter(char);
unsigned int set_VAI_counter(char);
unsigned int sense_ventricle(FILE *fp);
void pace_ventricle();
unsigned int is_change_rate();
void update_VAI();
void wait_PVARP();
unsigned int sense_atrium(FILE *fp)
{
	unsigned int signal = 0;
	for (int i = PVARP_length; i <= VAI_length; i++)
	{
		// Charging Supercapacitor starts
		double charge_sc;
		if (rate_at_which_supercapacitor_is_charged < max_charge_in_supercapacitor - present_charge_in_supercapacitor)
		{
			charge_sc = rate_at_which_supercapacitor_is_charged;
		}
		else
		{
			charge_sc = max_charge_in_supercapacitor - present_charge_in_supercapacitor;
		}
		battery_capacity -= charge_sc;
		present_charge_in_supercapacitor += charge_sc;
		// Charging Supercapacitor ends
		battery_capacity = battery_capacity - current_for_sensing_atrium * coulomb_to_charge_units * 1e-6;
		char c = fgetc(fp);
		if (c == 'P')
		{
			signal = 1;
		}
		else if (c == EOF)
		{
			signal = 2;
		}
	}
	return signal;
}
void pace_atrium()
{
	if (present_charge_in_supercapacitor >= current_to_pace_atrium * pulse_duration * coulomb_to_charge_units * 1e-6)
	{
		present_charge_in_supercapacitor = present_charge_in_supercapacitor - current_to_pace_atrium * pulse_duration * coulomb_to_charge_units * 1e-6;
	}
	else
	{
		pa_by_battery++;
		battery_capacity = battery_capacity - current_to_pace_atrium * pulse_duration * coulomb_to_charge_units * 1e-6;
	}
}
unsigned int sense_ventricle(FILE *fp)
{
	unsigned int signal = 0;
	for (int i = 0; i < AVI_length; i++)
	{
		// Charging Supercapacitor starts
		double charge_sc;
		if (rate_at_which_supercapacitor_is_charged < max_charge_in_supercapacitor - present_charge_in_supercapacitor)
		{
			charge_sc = rate_at_which_supercapacitor_is_charged;
		}
		else
		{
			charge_sc = max_charge_in_supercapacitor - present_charge_in_supercapacitor;
		}
		battery_capacity -= charge_sc;
		present_charge_in_supercapacitor += charge_sc;
		// Charging Supercapacitor ends
		battery_capacity = battery_capacity - current_for_sensing_ventrium * coulomb_to_charge_units * 1e-6;
		char c = fgetc(fp);
		if (c == 'Q')
		{
			signal = 1;
		}
		else if (c == EOF)
		{
			signal = 2;
		}
	}
	return signal;
}
void pace_ventricle()
{
	if (present_charge_in_supercapacitor >= current_to_pace_ventrium * pulse_duration * coulomb_to_charge_units * 1e-6)
	{
		present_charge_in_supercapacitor = present_charge_in_supercapacitor - current_to_pace_ventrium * pulse_duration * coulomb_to_charge_units * 1e-6;
	}
	else
	{
		pv_by_battery++;
		battery_capacity = battery_capacity - current_to_pace_ventrium * pulse_duration * coulomb_to_charge_units * 1e-6;
	}
}
void wait_PVARP(FILE *fp)
{
	unsigned int v;
	for (v = PVARP_length; v <= (VAI_length - p_wavelength); v++)
	{
	}
	// SOHAN
	for (int pvarp_counter = 0; pvarp_counter < PVARP_length; pvarp_counter++) // wait PVARP
	{
		double charge_sc;
		// Charging Supercapacitor starts
		if (rate_at_which_supercapacitor_is_charged < max_charge_in_supercapacitor - present_charge_in_supercapacitor)
		{
			charge_sc = rate_at_which_supercapacitor_is_charged;
		}
		else
		{
			charge_sc = max_charge_in_supercapacitor - present_charge_in_supercapacitor;
		}
		battery_capacity -= charge_sc;
		present_charge_in_supercapacitor += charge_sc;
		// Charging Supercapacitor ends
		fgetc(fp);
	}
	// SOHAN
}
unsigned int is_change_rate()
{
}
void update_VAI()
{
}
