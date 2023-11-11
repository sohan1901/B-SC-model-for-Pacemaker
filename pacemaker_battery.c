#include <string.h>
#include "pacemaker.h"
int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		printf("Assuming that the person is in neutral state\n");
	}
	else if (strcmp(argv[1], "rest") == 0)
	{
		AVI_length = 100;
		VAI_length = 750;
	}
	else if (strcmp(argv[1], "neutral") == 0)
	{
		AVI_length = 150;
		VAI_length = 850;
	}
	else if (strcmp(argv[1], "working") == 0)
	{
		AVI_length = 200;
		VAI_length = 950;
	}
	else
	{
		printf("Assuming that the person is in neutral state\n");
	}
	printf("\nGenerating Cardiac Signal Trace...\n");
	int exit_status = system("gcc -o gen_cardiac_signal_trace gen_cardiac_signal_trace.c");
	if (exit_status != 0)
	{
		printf("Failed to generate cardiac signal trace\n");
		return 1;
	}
	exit_status = system("./gen_cardiac_signal_trace");
	if (exit_status != 0)
	{
		printf("Failed to generate cardiac signal trace\n");
		return 1;
	}
	printf("\nSuccessfully generated Cardiac Signal trace\n\n");
	FILE *fp = fopen("cardiac_signal_trace.txt", "r");
	unsigned int c = 0, pace_atrium_counter = 0, pace_ventricle_counter = 0;
	printf("Initial Battery Capacity: %Lf\n", battery_capacity);
	while (c < max_cycles)
	{
		wait_PVARP(fp);
		switch (sense_atrium(fp)) // sense atrium
		{
		case 0:
			pace_atrium(); // pacing atrium if atrium not sensed
			pace_atrium_counter++;
			break;
		case 1: // no pacing atrium if atrium sensed
			break;
		case 2:
			printf("EOF reached.\n"); // Stop if EOF reached
			c = max_cycles;
		}
		switch (sense_ventricle(fp)) // sense ventricle
		{
		case 0:
			pace_ventricle(); // pacing ventricle if ventricle not sensed
			pace_ventricle_counter++;
			break;
		case 1: // no pacing ventricle if ventricle sensed
			break;
		case 2:
			printf("EOF reached.\n"); // Stop if EOF reached
			c = max_cycles;
		}
		if (is_change_rate()) // check rate change
			update_VAI();
		c++;
	}
	printf("Final Battery Capacity: %Lf\n", battery_capacity);
	printf("pace_atrium_counter = %d\npace_ventricle_counter = %d\n", pace_atrium_counter, pace_ventricle_counter);
	printf("SC was not available for %d times during atrium pace\n", pa_by_battery);
	printf("SC was not available for %d times during ventrium pace\n", pv_by_battery);
	fclose(fp);
	//    getchar();
	return 0;
}
