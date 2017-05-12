#include "../lib/logreminder.h"
#include "../lib/cmdline.h"

#include <pthread.h>
#include <errno.h>
#include <unistd.h>


int cnt_temp_1;
int cnt_temp_2;
int cnt_temp_3;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
//pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *thread1(void *);
void *thread2(void *);
void *thread3(void *);

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
	pthread_t tid1,tid2,tid3;
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
				break;
			}
		case 1: 
			{
				cl_printf("start cmd got!");
				err_t1 = pthread_create(&tid1, NULL , thread1, NULL);
				if (err_t1 != 0)
					{printf("%s: %d\n", __func__, strerror(err_t1));}
				printf("Thread 1 created.\n");
				break;
			}
		case 2: 
			{
				cl_printf("run cmd got!");
				err_t2 = pthread_create(&tid2, NULL , thread2, NULL);
				if (err_t2 != 0)
					{printf("%s: %d\n", __func__, strerror(err_t2));}
				printf("Thread 2 created.\n");
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
					}
				}
			}
		}
		unlock_thread("Thread1");
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
			break;
		}
		else if (cl_cmd_id == 0)
		{
			temp = 0;
			printf("Thread2 reset...\n");
		}
		else 
		{
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

