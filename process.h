#define false 0
#define true 0
typedef int bool;

typedef struct _process{
	int pid;
	int cpuBurst;
	int ioBurst;
	int arvTime;
	int priority;
	int ioTime;
	int ioPeriod;
	int executedTime;
	int waitingTime;
	int terminatedTime;
} Process;

typedef struct _node{
	Process process;
	struct _node* next;
} node;
	
typedef struct _queue{
	int count;
	node* front;
	node* rear;
} queue;

queue* create_queue(void);
void destroy_queue(queue* qptr);
void enqueue(queue* qptr, Process p);
Process dequeue(queue* qptr);
void create_process(queue* q, int num);
bool is_there_same_pid(queue* q, int pid);

