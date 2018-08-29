
#include "condition.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef void* (*Fun)(void* arg); //任务回调函数 

typedef struct task{
	Fun run;
	void* arg;
	struct task* next;
}task_t;

typedef struct threadPool_t{
	condition_t ready;
	
	int maxSize;
	int curSize;
	int idleSize;

	struct task* head;
	struct task* tail;

	int quitflag;
}threadPool_t;

void threadPool_init(threadPool_t* pool, int maxSize);
void threadPool_add_task(threadPool_t* pool,Fun run,void* arg);
void threadPool_destroy(threadPool_t* pool);
