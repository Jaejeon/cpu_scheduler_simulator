#include <stdio.h>
#include "scheduler.h"

void FCFS(queue* process_pool, double* avg_waiting, double* avg_turnaround){
	queue* ready_queue = create_queue();
	queue* waiting_queue = create_queue();
	queue* terminated_queue = create_queue();
	int time = 0;
	int terminated = 0;
	int runned = 0;
	int total_process = process_pool->count;
	node* temp;
	Process running;

	while(terminated < total_process){
		temp = process_pool->front;
		while(temp != NULL){
			if((temp->process).arvTime == time){
                                Process p = temp->process;
                                enqueue(ready_queue, p);
                        }
                        temp = temp->next;
		}

		if(time == 0) running.pid = 0;	
		if(ready_queue->count != 0 && running.pid == 0){ // running.pid == 0 means there is no process run by the cpu)
			running = dequeue(ready_queue);			
		}

		temp = ready_queue->front;
		printf("(TIME: %d) Ready queue:", time);
		while(temp != NULL){
			printf(" %d", (temp->process).pid);
			temp = temp->next;	
		}
		printf("\n");
		printf("Running: %d\n", running.pid);
		if(running.pid != 0){
			running.executedTime++;
		
			if(running.executedTime >= running.cpuBurst){
                                running.terminatedTime = time;
                                enqueue(terminated_queue, running);
                                terminated++;
                                running.pid = 0;
                        }		
			else if(running.executedTime % (running.ioPeriod) == 0){
				enqueue(waiting_queue, running);
				running.pid = 0;
			}
				
		}

		runned = running.pid;
	
		temp = ready_queue->front;
		while(temp != NULL){
			(temp->process).waitingTime++;
			temp = temp->next;
		}
		temp = waiting_queue->front;
		while(temp != NULL){
			if(runned != (temp->process).pid){ (temp->process).ioTime++;
			}	
			if((temp->process).ioTime >= (temp->process).ioBurst){
				(temp->process).ioTime = 0;
				enqueue(ready_queue,temp->process);
				(temp->process).pid = -2;	
			}
			temp = temp->next;	
		}
		
		queue* temp_waiting_queue = create_queue();
		temp = waiting_queue->front;
		while(temp != NULL){
			if((temp->process).pid != -2){
				enqueue(temp_waiting_queue, (temp->process));
			}	
			temp = temp->next;	
		}
		queue* temp2 = waiting_queue;
		waiting_queue = temp_waiting_queue;
		destroy_queue(temp2);
		time++;
	}
	
	double waiting_result= 0.0;
	double turnaround_result= 0.0;
	
	temp = terminated_queue->front;
	while(temp != NULL){
		printf("********************\n");
		printf("pid : %d\n", (temp->process).pid);
		printf("arvTime: %d\n", (temp->process).arvTime);
		printf("cpuBurst : %d\n", (temp->process).cpuBurst);
		printf("ioBurst : %d\n", (temp->process).ioBurst);
		printf("ioPeriod : %d\n", (temp->process).ioPeriod);
		printf("terminated time: %d\n", (temp->process).terminatedTime);
		printf("********************\n");
		waiting_result += (temp->process).waitingTime;
		turnaround_result += ((temp->process).terminatedTime-(temp->process).arvTime);
		temp = temp->next;
	}
	
	*avg_waiting = waiting_result/total_process;
	*avg_turnaround = turnaround_result/total_process;
	
	destroy_queue(ready_queue);
	destroy_queue(waiting_queue);
	destroy_queue(terminated_queue);
}

void SJF(queue* process_pool, double* avg_waiting, double* avg_turnaround){
	queue* ready_queue = create_queue();
        queue* waiting_queue = create_queue();
        queue* terminated_queue = create_queue();
        int time = 0;
        int terminated = 0;
        int runned = 0;
        int total_process = process_pool->count;
        node* temp;
        Process running;
	int remainedTime = 0;
	int min;
	int min_pid;

        while(terminated < total_process){
                temp = process_pool->front;
                while(temp != NULL){
                        if((temp->process).arvTime == time){
                                Process p = temp->process;
                                enqueue(ready_queue, p);
                        }
                        temp = temp->next;
                }

                if(time == 0) running.pid = 0;
              	if(ready_queue->count != 0 && running.pid != 0){
			remainedTime = (running.cpuBurst - running.executedTime);
			min = remainedTime;
			temp = ready_queue->front;
			while(temp != NULL){
				if(min > (temp->process).cpuBurst - (temp->process).executedTime){
					min = (temp->process).cpuBurst - (temp->process).executedTime;
					min_pid = (temp->process).pid;	
				}	
				temp = temp->next;
			}		

			if(min < remainedTime){
				queue* temp_ready_queue = create_queue();
				enqueue(temp_ready_queue, running);
               			temp = ready_queue->front;
               			while(temp != NULL){
                       			if((temp->process).pid != min_pid){
                               			enqueue(temp_ready_queue, (temp->process));
                        		}
					else{
						running = temp->process;	
					}
                        		temp = temp->next;
                		}
                		queue* temp2 = ready_queue;
                		ready_queue = temp_ready_queue;
                		destroy_queue(temp2);				
			}	
		} 
		if(ready_queue->count != 0 && running.pid == 0){ // running.pid == 0 means there is no process run by the cpu)
			min = 10000;
			temp = ready_queue->front;
                        while(temp != NULL){
                                if(min > (temp->process).cpuBurst - (temp->process).executedTime){
                                        min = (temp->process).cpuBurst - (temp->process).executedTime;
                                        min_pid = (temp->process).pid;
                                }
                                temp = temp->next;
                        }
			queue* temp_ready_queue = create_queue();
                        if(running.pid != 0) enqueue(temp_ready_queue, running);
                        temp = ready_queue->front;
                        while(temp != NULL){
                                if((temp->process).pid != min_pid){
                                        enqueue(temp_ready_queue, (temp->process));
                                }
                                else{
                                        running = temp->process;
                                }
                                temp = temp->next;
                        }
                        queue* temp2 = ready_queue;
                        ready_queue = temp_ready_queue;
                        destroy_queue(temp2);
                }

                temp = ready_queue->front;
                printf("(TIME: %d) Ready queue:", time);
                while(temp != NULL){
                        printf(" %d", (temp->process).pid);
                        temp = temp->next;
                }
                printf("\n");
                printf("Running: %d\n", running.pid);
                if(running.pid != 0){
                        running.executedTime++;

                        if(running.executedTime >= running.cpuBurst){
                                running.terminatedTime = time;
                                enqueue(terminated_queue, running);
                                terminated++;
				running.pid = 0;
                        }
                        else if(running.executedTime % (running.ioPeriod) == 0){
                                enqueue(waiting_queue, running);
                                running.pid = 0;
                        }
                }

                runned = running.pid;

                temp = ready_queue->front;
                while(temp != NULL){
                        (temp->process).waitingTime++;
                        temp = temp->next;
                }
                temp = waiting_queue->front;
                while(temp != NULL){
                        if(runned != (temp->process).pid){ (temp->process).ioTime++;
                        }
                        if((temp->process).ioTime >= (temp->process).ioBurst){
                                (temp->process).ioTime = 0;
                                enqueue(ready_queue,temp->process);
                                (temp->process).pid = -2;
                        }
                        temp = temp->next;
                }

                queue* temp_waiting_queue = create_queue();
                temp = waiting_queue->front;
                while(temp != NULL){
                        if((temp->process).pid != -2){
                                enqueue(temp_waiting_queue, (temp->process));
                        }
                        temp = temp->next;
                }
                queue* temp2 = waiting_queue;
                waiting_queue = temp_waiting_queue;
                destroy_queue(temp2);
                time++;
        }

        double waiting_result= 0.0;
        double turnaround_result= 0.0;
	
	temp = terminated_queue->front;
        while(temp != NULL){
                printf("********************\n");
                printf("pid : %d\n", (temp->process).pid);
                printf("arvTime: %d\n", (temp->process).arvTime);
                printf("cpuBurst : %d\n", (temp->process).cpuBurst);
                printf("ioBurst : %d\n", (temp->process).ioBurst);
                printf("ioPeriod : %d\n", (temp->process).ioPeriod);
                printf("terminated time: %d\n", (temp->process).terminatedTime);
                printf("********************\n");
                waiting_result += (temp->process).waitingTime;
                turnaround_result += ((temp->process).terminatedTime-(temp->process).arvTime);
                temp = temp->next;
        }

        *avg_waiting = waiting_result/total_process;
        *avg_turnaround = turnaround_result/total_process;

        destroy_queue(ready_queue);
        destroy_queue(waiting_queue);
        destroy_queue(terminated_queue);		
}

void Priority(queue* process_pool, double* avg_waiting, double* avg_turnaround){
	queue* ready_queue = create_queue();
        queue* waiting_queue = create_queue();
        queue* terminated_queue = create_queue();
        int time = 0;
        int terminated = 0;
        int runned = 0;
        int total_process = process_pool->count;
        node* temp;
        Process running;
	int runningPriority;
	int min;
	int min_pid;
	// min priority number -> hieghest priority

        while(terminated < total_process){
                temp = process_pool->front;
                while(temp != NULL){
                        if((temp->process).arvTime == time){
                                Process p = temp->process;
                                enqueue(ready_queue, p);
                        }
                        temp = temp->next;
                }

		if(time == 0) running.pid = 0;
                if(ready_queue->count != 0 && running.pid != 0){
                        runningPriority = running.priority;
                        min = runningPriority;
                        temp = ready_queue->front;
                        while(temp != NULL){
                                if(min > (temp->process).priority){
                                        min = (temp->process).priority;
                                        min_pid = (temp->process).pid;
                                }
                                temp = temp->next;
                        }

                        if(min < runningPriority){
                                queue* temp_ready_queue = create_queue();
                                enqueue(temp_ready_queue, running);
                                temp = ready_queue->front;
                                while(temp != NULL){
                                        if((temp->process).pid != min_pid){
                                                enqueue(temp_ready_queue, (temp->process));
                                        }
                                        else{
                                                running = temp->process;
                                        }
                                        temp = temp->next;
                                }
                                queue* temp2 = ready_queue;
                                ready_queue = temp_ready_queue;
                                destroy_queue(temp2);
                        }
                }		

		if(ready_queue->count != 0 && running.pid == 0){ // running.pid == 0 means there is no process run by the cpu)
                        min = 10000;
                        temp = ready_queue->front;
                        while(temp != NULL){
                                if(min > (temp->process).priority){
                                        min = (temp->process).priority;
                                        min_pid = (temp->process).pid;
                                }
                                temp = temp->next;
                        }
                        queue* temp_ready_queue = create_queue();
                        if(running.pid != 0) enqueue(temp_ready_queue, running);
                        temp = ready_queue->front;
                        while(temp != NULL){
                                if((temp->process).pid != min_pid){
                                        enqueue(temp_ready_queue, (temp->process));
                                }
                                else{
                                        running = temp->process;
                                }
                                temp = temp->next;
                        }
                        queue* temp2 = ready_queue;
                        ready_queue = temp_ready_queue;
                        destroy_queue(temp2);
                }

                temp = ready_queue->front;
                printf("(TIME: %d) Ready queue:", time);
                while(temp != NULL){
                        printf(" %d", (temp->process).pid);
                        temp = temp->next;
                }
                printf("\n");
                printf("Running: %d\n", running.pid);
                if(running.pid != 0){
                        running.executedTime++;

                        if(running.executedTime >= running.cpuBurst){
                                running.terminatedTime = time;
                                enqueue(terminated_queue, running);
                                terminated++;
				running.pid = 0;
                        }
                        else if(running.executedTime % (running.ioPeriod) == 0){
                                enqueue(waiting_queue, running);
                                running.pid = 0;
                        }

                }

                runned = running.pid;

                temp = ready_queue->front;
                while(temp != NULL){
                        (temp->process).waitingTime++;
                        temp = temp->next;
                }
                temp = waiting_queue->front;
                while(temp != NULL){
                        if(runned != (temp->process).pid){ (temp->process).ioTime++;
                        }
                        if((temp->process).ioTime >= (temp->process).ioBurst){
                                (temp->process).ioTime = 0;
                                enqueue(ready_queue,temp->process);
                                (temp->process).pid = -2;
                        }
                        temp = temp->next;
                }

                queue* temp_waiting_queue = create_queue();
                temp = waiting_queue->front;
                while(temp != NULL){
                        if((temp->process).pid != -2){
                                enqueue(temp_waiting_queue, (temp->process));
                        }
                        temp = temp->next;
                }
                queue* temp2 = waiting_queue;
                waiting_queue = temp_waiting_queue;
                destroy_queue(temp2);
                time++;
        }

        double waiting_result= 0.0;
        double turnaround_result= 0.0;
	
	temp = terminated_queue->front;
        while(temp != NULL){
                printf("********************\n");
                printf("pid : %d\n", (temp->process).pid);
                printf("arvTime: %d\n", (temp->process).arvTime);
                printf("cpuBurst : %d\n", (temp->process).cpuBurst);
                printf("ioBurst : %d\n", (temp->process).ioBurst);
                printf("ioPeriod : %d\n", (temp->process).ioPeriod);
                printf("terminated time: %d\n", (temp->process).terminatedTime);
		printf("priority : %d\n", (temp->process).priority);
                printf("********************\n");
                waiting_result += (temp->process).waitingTime;
                turnaround_result += ((temp->process).terminatedTime-(temp->process).arvTime);
                temp = temp->next;
        }

        *avg_waiting = waiting_result/total_process;
        *avg_turnaround = turnaround_result/total_process;

        destroy_queue(ready_queue);
        destroy_queue(waiting_queue);
        destroy_queue(terminated_queue);
}

void RR(queue* process_pool, double* avg_waiting, double* avg_turnaround, int quantum){
	queue* ready_queue = create_queue();
        queue* waiting_queue = create_queue();
        queue* terminated_queue = create_queue();
        int time = 0;
        int terminated = 0;
        int runned = 0;
        int total_process = process_pool->count;
        node* temp;
        Process running;
	int j = 0;
	bool event_flag = false;

        while(terminated < total_process){
                temp = process_pool->front;
                while(temp != NULL){
                        if((temp->process).arvTime == time){
                                Process p = temp->process;
                                enqueue(ready_queue, p);
                        }
                        temp = temp->next;
                }

                if(time == 0) running.pid = 0;
                if(ready_queue->count != 0 && running.pid == 0){ // running.pid == 0 means there is no process run by the cpu)
                        running = dequeue(ready_queue);
                }

                temp = ready_queue->front;
                printf("(TIME: %d) Ready queue:", time);
                while(temp != NULL){
                        printf(" %d", (temp->process).pid);
                        temp = temp->next;
                }
                printf("\n");
                printf("Running: %d\n", running.pid);

		if(running.pid != 0){
                        running.executedTime++;
			j++;

                        if(running.executedTime >= running.cpuBurst){
                                running.terminatedTime = time;
                                enqueue(terminated_queue, running);
                                terminated++;
                                running.pid = 0;
				j=0;
                        }
                        else if(running.executedTime % (running.ioPeriod) == 0){
                                enqueue(waiting_queue, running);
                                running.pid = 0;
				j = 0;
                        }
			else if(j>=quantum){
				enqueue(ready_queue, running);
				running.pid = 0;
				j = 0;
			}
                }		

                runned = running.pid;

                temp = ready_queue->front;
                while(temp != NULL){
                        (temp->process).waitingTime++;
                        temp = temp->next;
                }
                temp = waiting_queue->front;
                while(temp != NULL){
                        if(runned != (temp->process).pid){ (temp->process).ioTime++;
                        }
                        if((temp->process).ioTime >= (temp->process).ioBurst){
                                (temp->process).ioTime = 0;
                                enqueue(ready_queue,temp->process);
                                (temp->process).pid = -2;
                        }
                        temp = temp->next;
                }

                queue* temp_waiting_queue = create_queue();
                temp = waiting_queue->front;
                while(temp != NULL){
                        if((temp->process).pid != -2){
                                enqueue(temp_waiting_queue, (temp->process));
                        }
                        temp = temp->next;
                }
                queue* temp2 = waiting_queue;
                waiting_queue = temp_waiting_queue;
                destroy_queue(temp2);
                time++;
        }

        double waiting_result= 0.0;
        double turnaround_result= 0.0;

	temp = terminated_queue->front;
        while(temp != NULL){
                printf("********************\n");
                printf("pid : %d\n", (temp->process).pid);
                printf("arvTime: %d\n", (temp->process).arvTime);
                printf("cpuBurst : %d\n", (temp->process).cpuBurst);
                printf("ioBurst : %d\n", (temp->process).ioBurst);
                printf("ioPeriod : %d\n", (temp->process).ioPeriod);
                printf("terminated time: %d\n", (temp->process).terminatedTime);
                printf("********************\n");
                waiting_result += (temp->process).waitingTime;
                turnaround_result += ((temp->process).terminatedTime-(temp->process).arvTime);
                temp = temp->next;
        }

        *avg_waiting = waiting_result/total_process;
        *avg_turnaround = turnaround_result/total_process;

        destroy_queue(ready_queue);
        destroy_queue(waiting_queue);
        destroy_queue(terminated_queue);		
}
