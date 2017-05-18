/*================================================================
*   Copyright (C) 2017 free for learn.
*   
*   filename：1_create.c
*   breif：	  创建线程。主线程和新线程各自打印自己的ID
*   history：2017-05-19 renbin.guo created.
*   note：
*   usage：
*
================================================================*/

#include<stdio.h>
#include<unistd.h>
#incldude<pthread.h>

void  print_id()
{
	printf(" created thread  id = %d\n", pthread_self());
}
int main(int argc, char const *argv[])
{
	pthread_t thid;
	printf("main thead id = %d\n", pthread_self());
	if(pthread_create(&thid,NULL,print_id,NULL)  !=NULL)
	{
		printf("creatd failed");
		exit(1);
	}
	return 0;
}
