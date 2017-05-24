/*================================================================
*   Copyright (C) 2017 free for learn.
*   
*   file：5_condition.c
*   breif：条件变量的用法
*   history：renbin.guo created 2017-05-24
*   note：
*   usage：
*
================================================================*/

#include  <stdio.h>
#include  <unistd.h>
#include  <pthread.h>

pthread_mutex_t mutex;	// 互斥锁
pthread_cond_t	cond;	// 条件变量

void* pthread1(void*arg)
{
	/* 解锁 */
	pthread_cleanup_push(pthread_mutex_unlock,&mutex);	

	while(1)
	{
			printf("thread1 is running\n");
			// 加锁
			pthread_mutex_unlock(&mutex);

			// 等待条件变量
			pthread_cond_wait(&cond,&mutex);
			printf("thread1 applied the condition\n");
			pthread_mutex_unlock(&mutex); // 解锁
			sleep(4);
	}
	pthread_cleanup_pop(0);
}

int main(int argc, char *argv[])
{
	pthread_t tid1;
	pthread_t tid2;

	/* 初始化互斥锁 */
	pthread_mutex_init(&mutex,NULL);
	/* 初始化条件变量 */
	pthread_cond_init(&cond,NULL);

	pthread_create(&tid1,NULL,(void*)thread1,NULL);
	pthread_create(&tid2,NULL,(void*)thread2,NULL);

	
	/* 线程被条件变量阻塞后，可通过pthread_cond_signal激活一个等待成立的线程，存在多个等待线程时，按入队顺序激活第一个*/

	do
	{
		pthread_cond_signal(&cond);
	}while(1);

	sleep(50);
	// pthread_eixt只会退出当前线程，而exit则会退出整个进程
	pthread_exit(0);
}




