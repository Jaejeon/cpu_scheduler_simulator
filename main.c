/*	Description: CPU Scheduling Algorithm Simulator.
*	Developer: Jaejeon Koo, Korea Univ.
*	Last update: 2016.06.01
*/

#include <stdio.h>
#include <stdlib.h>
#include "process.c"
#include "scheduler.c"

int main(){
	queue* process_pool = create_queue();
	
	create_process(process_pool, 10);
	double waiting_time[4];
	double turnaround_time[4];	
	FCFS(process_pool, &waiting_time[0], &turnaround_time[0]);
	printf("#############Result(FCFS)##############\n");
        printf("avg_waiting: %lf\n", waiting_time[0]);
        printf("avg_turnaround: %lf\n", turnaround_time[0]);
        printf("#######################################\n");
	
	SJF(process_pool, &waiting_time[1], &turnaround_time[1]);
	printf("#############Result(SJF)##############\n");
        printf("avg_waiting: %lf\n", waiting_time[1]);
        printf("avg_turnaround: %lf\n", turnaround_time[1]);
        printf("#######################################\n");
	
	Priority(process_pool, &waiting_time[2], &turnaround_time[2]);
        printf("#############Result(Priority)##############\n");
        printf("avg_waiting: %lf\n", waiting_time[2]);
        printf("avg_turnaround: %lf\n", turnaround_time[2]);
        printf("#######################################\n");

	RR(process_pool, &waiting_time[3], &turnaround_time[3], 4);
        printf("#############Result(RR)##############\n");
        printf("avg_waiting: %lf\n", waiting_time[3]);
        printf("avg_turnaround: %lf\n", turnaround_time[3]);
        printf("#######################################\n");

	destroy_queue(process_pool);
	printf("***************************************\n");
	printf("* Algorithm * avg_waiting * avg_turn  *\n");
	printf("***************************************\n");
	printf("* FCFS      * %11.6lf * %9.6lf *\n", waiting_time[0], turnaround_time[0]);
	printf("***************************************\n");
	printf("* SJF       * %11.6lf * %9.6lf *\n", waiting_time[1], turnaround_time[1]);
	printf("***************************************\n");
	printf("* Priority  * %11.6lf * %9.6lf *\n", waiting_time[2], turnaround_time[2]);
	printf("***************************************\n");
	printf("* RR        * %11.6lf * %9.6lf *\n", waiting_time[3], turnaround_time[3]);
	printf("***************************************\n");

	return 0;
}
