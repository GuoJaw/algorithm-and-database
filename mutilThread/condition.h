

#include "pthread.h"

typedef struct condition{
	pthread_mutex_t pmutex;
	pthread_cond_t pcond;
}condition_t;

//初始化和销毁
void condition_init(condition_t* cond){
	pthread_mutex_init(&cond->pmutex, NULL);
	pthread_cond_init(&cond->pcond, NULL);
}
void condition_destroy(condition_t* cond){
	pthread_mutex_destroy(&cond->pmutex);
	pthread_cond_destroy(&cond->pcond);
}
//加锁和解锁
void condition_lock(condition_t* cond){
	pthread_mutex_lock(&cond->pmutex);
}
void condition_unlock(condition_t* cond){
	pthread_mutex_unlock(&cond->pmutex);
}
//等待条件到来
void condition_wait(condition_t* cond){
	pthread_cond_wait(&cond->pcond,&cond->pmutex);
}
void condition_time_wait(condition_t* cond, struct timespec* abstime){
	pthread_cond_timedwait(&cond->pcond, &cond->pmutex, abstime);
}
//唤醒等待条件的线程
void condition_signal(condition_t* cond){
	pthread_cond_signal(&cond->pcond);
}
void condition_broadcast(condition_t* cond){
	pthread_cond_broadcast(&cond->pcond);
}
