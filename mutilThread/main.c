
#include "threadpool.h"

void* mytask(void* arg){
	printf("线程%d在执行%d任务\n", pthread_self(), *(int*)(arg));
	sleep(1);
	free(arg);
	return NULL;
}

int main(){
	threadPool_t pool;
	threadPool_init(&pool,3);
	for (int i = 0; i < 10; i++){
		int* tmp = (int*)malloc(sizeof(int));
		*tmp = i;
		threadPool_add_task(&pool, mytask, tmp);
	}
	threadPool_destroy(&pool);
	return 0;
}
