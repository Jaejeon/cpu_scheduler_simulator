#include "process.h"
#include <stdlib.h>
#include <time.h>

queue* create_queue(){
	queue* new_queue = (queue*)malloc(sizeof(queue));
	(*new_queue).count = 0;
	(*new_queue).front = NULL;
	(*new_queue).rear = NULL;
	return new_queue;
}

void destroy_queue(queue* qptr){
	while((*qptr).count != 0){
		dequeue(qptr);
	}
	free(qptr);
}

void enqueue(queue* qptr, Process p){
	node* new_node = (node*)malloc(sizeof(node));
	new_node->process = p;
	new_node->next = NULL;

	if((*qptr).count == 0){
		(*qptr).front = new_node;
		(*qptr).rear = new_node;
	}
	else{
		qptr->rear->next = new_node;
		qptr->rear = new_node;
	}

	qptr->count++;
}

Process dequeue(queue* qptr){
	if(qptr->count == 0){
		Process error;
		error.pid = -1;	
		return error;
	}
	else{
		node* temp = qptr->front;
		qptr->front = temp->next;
		Process temp_process = temp->process;
		free(temp);
		qptr->count--;
		return temp_process;
	}	
}
bool is_there_same_pid(queue* q, int pid){
	bool result = false;
	node* temp;
	if(q->front == NULL){ return false; } // queue is empty. 
	else{
		temp = q->front;
	}
	while(temp->next != NULL){
		if((temp->process).pid == pid) result = true;
		temp = temp->next;	
	}

	return result;	
}
void create_process(queue* q, int num){
	srand(time(NULL));
	int i;
	int pid;
	for(i = 0; i < num; i++){
		do {
			pid = rand() % 32768 + 1; //on most linux machines, pid max is 32768	
		} while(is_there_same_pid(q, pid));
		Process p;
		p.pid = pid;
		p.cpuBurst = rand() % 19 + 2; // cpuBurst 2~20
		p.ioBurst = rand() % 20 + 1; // ioBurst 1~20
		p.arvTime = rand() % 31; // arival time 0~30;
		p.priority = rand() % 100 + 1; // priority 1~100
		p.ioTime = 0; // how long it is in waiting queue
		p.ioPeriod = rand() % (p.cpuBurst+1) + 1; // period 
		p.executedTime = 0; // how long it is executed
		p.terminatedTime = 0;
		p.waitingTime = 0;	
		enqueue(q, p);	
	}		
}


	








