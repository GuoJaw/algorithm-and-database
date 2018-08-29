 


#include "threadpool.h"

void* thread_hander(void* arg);

void threadPool_init(threadPool_t* pool, int maxSize);
void threadPool_destroy(threadPool_t* pool);
void threadPool_add_task(threadPool_t* pool, Fun run, void* arg);


void threadPool_init(threadPool_t* pool, int maxSize){
	pool = (threadPool_t*)malloc(sizeof(threadPool_t));

	condition_init(&pool->ready);

	pool->maxSize = maxSize;
	pool->curSize = 0;
	pool->idleSize = 0;

	pool->head = NULL;
	pool->tail = NULL;

	pool->quitflag = 0;
}
void threadPool_destroy(threadPool_t* pool){
	if (pool->quitflag == 1)
		return;
	condition_lock(&pool->ready);
	pool->quitflag = 1;
	if (pool->curSize > 0){ //线程池中有线程:等待状态的线程/工作中的线程
		if (pool->idleSize > 0)
			condition_broadcast(&pool->ready);
		//处于执行任务状态中的线程，不会收到广播
		//线程池需要等待执行任务中的线程全部退出
		while (pool->curSize > 0)
			condition_wait(&pool->ready);
		 
	}

	condition_unlock(&pool->ready);
	condition_destroy(&pool->ready); //销毁
}
void threadPool_add_task(threadPool_t* pool, Fun run, void* arg){
	//创建新任务
	task_t* newtask = (task_t*)malloc(sizeof(task_t));
	newtask->run = run;
	newtask->arg = arg;
	newtask->next = NULL;
	
	condition_lock(&pool->ready); //加锁
	//将新任务添加到任务队列
	if (pool->head == NULL)
		pool->head = newtask;
	else
		pool->tail->next = newtask;
	pool->tail = newtask;
	
	if (pool->idleSize > 0)
		condition_signal(&pool->ready); //唤醒等待条件的线程
	else{
		if (pool->curSize < pool->maxSize){
			pthread_t tid; 
			pthread_create(&tid, NULL, thread_hander, pool); //注意参数
			pool->curSize++; 
		}
	}
	condition_unlock(&pool->ready); //解锁
}


void* thread_hander(void* arg){ //消费者线程
	printf("线程%d正在启动\n", pthread_self());
	
	threadPool_t* pool = (threadPool_t*)arg;

	while(1){
		condition_lock(&pool->ready);
		pool->idleSize++;
		//等待队列无任务到来 && 线程池没有销毁通知
		while (pool->head == NULL && pool->quitflag == 0)
			condition_wait(&pool->ready);
		//等待到条件，线程处于工作状态
		pool->idleSize--; 
		if (pool->head != NULL){//条件1:等待队列中有任务
			task_t* t = pool->head; pool->head = pool->head->next;//取出任务
			condition_unlock(&pool->ready);
			t->run(t->arg); //处理任务
			condition_lock(&pool->ready);
		}
		if (pool->quitflag == 1 && pool->head == NULL){//条件2:线程池销毁通知&&等待队列无任务
			pool->curSize--; //销毁此线程
			if (pool->curSize == 0)
				condition_signal(&pool->ready);
			condition_unlock(&pool->ready);
			break;
		}
		condition_unlock(&pool->ready);
	}
	printf("线程%d被销毁\n", pthread_self());
	return NULL;
}
