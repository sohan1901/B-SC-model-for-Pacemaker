#include <stdio.h>
#include "pacemaker.h"

int main()
{
	FILE *fp = fopen("cardiac_signal_trace.txt", "w");
	unsigned int c, v, p, pvarp_counter, pflag, qflag, atrial_signal, ventricle_signal, a, pace_atrium_counter = 0, pace_ventricle_counter = 0;
	for (c = 0; c < max_cycles; c++)
	{
		for (pvarp_counter = 0; pvarp_counter < PVARP_length; pvarp_counter++) // wait PVARP
			fputc('-', fp);
		for (v = PVARP_length; v <= (VAI_length - p_wavelength); v++)
			fputc('-', fp);
		pflag = 0;
		for (p = 0; p < p_wavelength; p++)
		{
			atrial_signal = rand() % 100;
			if ((!atrial_signal) && (!pflag))
			{
				fputc('P', fp);
				pflag = 1;
			}
			else
				fputc('-', fp);
		}
		if (!pflag)
		{
			// printf("Pace atrium");
			pace_atrium_counter++;
		}
		qflag = 0;
		for (a = 0; a < AVI_length; a++)
		{
			ventricle_signal = rand() % 100;
			if ((!ventricle_signal) && (!qflag))
			{
				fputc('Q', fp);
				qflag = 1;
			}
			else
				fputc('-', fp);
		}
		if (!qflag)
		{
			// printf("Pace ventrium");
			pace_ventricle_counter++;
		}
	}
	printf("#pace_atrium=%u  #pace_ventrium=%u", pace_atrium_counter, pace_ventricle_counter);
	fclose(fp);
	return 0;
}
