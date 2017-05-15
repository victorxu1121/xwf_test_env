#include "../lib/logreminder.h"
#include "../lib/cmdline.h"

#include <pthread.h>
#include <errno.h>
#include <unistd.h>

#define PRODUCTION_MAX 10

int cnt_temp_1;
int cnt_temp_2;
int cnt_temp_3;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_quit = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_not_empty = PTHREAD_COND_INITIALIZER;

int flag_full;
int flag_empty;
int production_cnt;

void *thread1(void *);
void *thread2(void *);
void *thread3(void *);
void *thread_producer(void *);
void *thread_consumer(void *);

void lock_thread(const char *s);
void unlock_thread(const char *s);

int main(int argc, char * argv[])
{
	printf("==========\nTest Start\n==========\n");
	printf("Date: %s %s\n",__DATE__, __TIME__);
	
	//===log recorder init ==start===//
	//lr_err = lr_init();
	//if (lr_err)
	//{
	//	lr_err_printf("log recorder initialize failed!");
	//	return 1;
	//}
	//lr_record_event("Test Start");
	//===log recorder init ==end====//

	//===cmd line init ==start======//
	cl_cmd_debug_print = 0;
	cl_cmd_init();	
	cl_clr();
	cl_cmd_set(0,"reset");
	cl_cmd_explain[0] = "Rest the test";
	cl_cmd_set(1,"start");
	cl_cmd_explain[1] = "Start the test";
	cl_cmd_set(2,"run");
	cl_cmd_explain[2] = "Run the test";
	cl_cmd_set(3,"stop");
	cl_cmd_explain[3] = "Stop the test";
	cl_cmd_set(4,"list");
	cl_cmd_explain[4] = "list the command";
	cl_cmd_set(5,"print");
	cl_cmd_explain[5] = "Debug print / No print";
	cl_cmd_set(6,"quit");
	cl_cmd_explain[6] = "Quit the test!";
	//===cmd line init ==end=======//

	//===pthread init ==start======//
	pthread_t tid1,tid2,tid3,tid4,tid5;
	int err_t1 = 0, err_t2 = 0, err_t3 = 0;
	void **rval1;
	void **rval2;
    void **rval3;
    void *rval1_t;
    void *rval2_t;
    void *rval3_t;
	
	cnt_temp_1 = 0;
	cnt_temp_2 = 0;
	cnt_temp_3 = 0;

	//===pthread init ==end========//
	flag_full = 0;
	flag_empty = 1;
	production_cnt = 0;
	int producer_id, consumer_id;
	
	cl_cmd_menu_print();
	while(1)
	{
		cl_clr();
        cl_cmd_get();

		cl_cmd_id = cl_cmd_id_translate();
		switch(cl_cmd_id)
		{
		case 0: 
			{
				cl_printf("reset cmd got!");
				production_cnt = 0;
				break;
			}
		case 1: 
			{
				cl_printf("start cmd got!");
				err_t1 = pthread_create(&tid1, NULL , thread1, NULL);
				if (err_t1 != 0)
					{printf("Thread1 create failed!!\n");}///%s: %d\n", __func__, strerror(err_t1));}
				printf("Thread 1 created.\n");
				break;
			}
		case 2: 
			{
				cl_printf("run cmd got!");
				/*
				err_t2 = pthread_create(&tid2, NULL , thread2, NULL);
				if (err_t2 != 0)
					{printf("Thread1 create failed!!\n");}///%s: %d\n", __func__, strerror(err_t2));}
				printf("Thread 2 created.\n");
				*/
				producer_id = 1;
				err_t2 = pthread_create(&tid2, NULL, thread_producer, (void*)&producer_id);
				if (err_t2 != 0)
					{printf("Thread producer create failed!!\n");}///%s: %d\n", __func__, strerror(err_t1));}
				else 
					{printf("Thread producer created.\n");}

				consumer_id = 1;
				err_t3 = pthread_create(&tid3, NULL, thread_consumer, (void*)&consumer_id);
				if (err_t3 != 0)
					{printf("Thread consumer create failed!!\n");}///%s: %d\n", __func__, strerror(err_t1));}
				else 
					{printf("Thread consumer created.\n");}

				consumer_id = 2;
				err_t3 = pthread_create(&tid4, NULL, thread_consumer, (void*)&consumer_id);
				if (err_t3 != 0)
					{printf("Thread consumer create failed!!\n");}///%s: %d\n", __func__, strerror(err_t1));}
				else 
					{printf("Thread consumer created.\n");}
				break;
			}
		case 3: 
			{
				cl_printf("stop cmd got!");
				break;
			}
		case 4: 
			{
				cl_printf("list cmd got!");
				cl_cmd_menu_print();
				break;
			}
		case 6: 
			{
				cl_printf("Quit!");
				pthread_cond_signal(&cond_quit);
				sleep(1);
				return 0;
			}
		case 5:
			{
				if (cl_cmd_debug_print)
				{
					cl_cmd_debug_print = 0;
					cl_printf("No debug print");
				}
				else 
				{
					cl_cmd_debug_print = 1;
					cl_printf("Debug print");
				}
				break;
			}
		default:
			{
				cl_printf("Invalid Command!!");
				break;
			}
		}

	}


	
	lr_record_event("Test Start");
	printf("==========\nTest End\n==========\n");
	return 0;
}

void *thread1(void *arg)
{
	while (1)
	{
		lock_thread("Thread1");
		if (cl_cmd_id == 6)
		{
			printf("Thread1 end\n");
			break;
		}
		else if (cl_cmd_id == 0) 
		{
		    cnt_temp_1 = 0;
	        cnt_temp_2 = 0;
	        cnt_temp_3 = 0;
			printf("Thread1 reset...\n");
		}
		else 
		{
			cnt_temp_1 ++;
			if (cnt_temp_1%100 == 0)
			{
				cnt_temp_2 ++;
				if (cnt_temp_2%100 == 0)
				{
					cnt_temp_3 ++;
					if (cnt_temp_3%10 == 0)
					{
						printf("Thread1: %d-%d-%d\n", cnt_temp_3, cnt_temp_2, cnt_temp_1);
						pthread_cond_signal(&cond);
					}
				}
			}
		}
		unlock_thread("Thread1");
		pthread_cond_broadcast(&cond);
	}
	return;
}

void *thread2(void *arg)
{
	int temp = 0;
	while (1)
	{
		lock_thread("Thread2");
		if(cl_cmd_id == 6)
		{
			printf("Thread2 end\n");
			//break;
			return;
		}
		else if (cl_cmd_id == 0)
		{
			temp = 0;
			printf("Thread2 reset...\n");
		}
		else 
		{
			pthread_cond_wait(&cond, &mutex);
			if (cnt_temp_1%100 == 0)
			{
				if (cnt_temp_2%100 == 0)
				{
					if (cnt_temp_3%20 == 0)
					{
						temp++;
						printf("Thread2: %d-%d-%d --- %d\n", cnt_temp_3, cnt_temp_2, cnt_temp_1, temp);
					}
				}
			}
		}	
		unlock_thread("Thread2");
	}
	return;
}

void lock_thread(const char *s)
{
    if(pthread_mutex_lock(&mutex) != 0)
    {
        printf("%s has lock error!", s);
        exit(0);
    }
}

void unlock_thread(const char *s)
{
    if(pthread_mutex_unlock(&mutex) != 0)
    {
        printf("%s has unlock error!", s);
        exit(0);
    }
}

void *thread_producer(void *arg)
{
	int *producer_id_thread = (int*) arg;
	while(1)
	{
		if (cl_cmd_id == 6)
		{
			break;
		}
		
		lock_thread("Thread producer");
		if (flag_full == 1)
		{
			printf("Producer[%d]: waiting for consumer...\n", *producer_id_thread);
			pthread_cond_wait(&cond_not_full,&mutex);
		}
		else 
		{
			production_cnt ++;
			flag_empty = 0;
			if (production_cnt == PRODUCTION_MAX)
			{
				flag_full = 1;
				printf("Producer[%d]: Buffer is Full!(NUM = %d)\n",*producer_id_thread,production_cnt);
			}
			else 
			{
				flag_full = 0;
				pthread_cond_signal(&cond_not_empty);
				printf("Producer[%d]: Buffer is not Full!(NUM = %d flag_full = %d)\n",*producer_id_thread,production_cnt);

			}
		}
		unlock_thread("Thread producer");
		sleep(1);
	}
	return;
}

void *thread_consumer(void *arg)
{
	int *consumer_id_thread = (int*) arg;
	while (1)
	{
		if (cl_cmd_id == 6)
		{
			break;
		}

		lock_thread("Thread consumer");
		if (flag_empty == 1)
		{
			printf("Consumer[%d]: waiting for producer...\n", *consumer_id_thread);
			pthread_cond_wait(&cond_not_empty, &mutex);
		}
		else
		{
			production_cnt --;
			flag_full = 0;
			if (production_cnt == 0)
			{
				flag_empty = 1;
				printf("Consumer[%d]: Buffer is empty!(NUM = %d)\n",*consumer_id_thread,production_cnt);
			}
			else 
			{
				flag_empty = 0;
				pthread_cond_signal(&cond_not_full);
				printf("Consumer[%d]: Buffer is not empty!(NUM = %d)\n",*consumer_id_thread,production_cnt);
			}
		}
		unlock_thread("Thread consumer");
		sleep(3);
	}
	return;
}





