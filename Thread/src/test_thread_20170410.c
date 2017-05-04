#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

#define unsigned int unit;

int g_Flag = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void printids(const char *s);
void lock_thread(const char *s);
void unlock_thread(const char *s);

void *thread1(void *);
void *thread2(void *);
void *thread3(void *);

int main(int argc, char **argv)
{
    printf("Enter main function.\n");

    pthread_t tid1, tid2, tid3;
    int err1 = 0, err2 = 0, err3 = 0;
    void **rval1;
    void **rval2;
    void **rval3;
    void *rval1_t;
    void *rval2_t;
    void *rval3_t;

    err1 = pthread_create(&tid1, NULL, thread1, NULL);
    if(err1 != 0)
        printf("%s: %d\n", __func__, strerror(err1));

    err2 = pthread_create(&tid2, NULL, thread2, NULL);
    if(err2 != 0)
        printf("%s: %d\n", __func__, strerror(err2));

    err3 = pthread_create(&tid3, NULL, thread3, NULL);
    if(err3 != 0)
        printf("%s: %d\n", __func__, strerror(err3));
 
    err1 = pthread_join(tid1, NULL);//rval1);
    rval1_t = &(*rval1);
    if(err1 != 0)
        printf("%s: %d\n", __func__, strerror(err1));
    printf("thread1 exit.\n");
    //printf("thread1 exit code is %d.\n", *(int*)(rval1_t));
  
    err2 = pthread_join(tid2, NULL);//rval2);
    rval2_t = &(*rval2);
    if(err2 != 0)
        printf("%s: %d\n", __func__, strerror(err2));
    printf("thread2 exit.\n");
    //printf("thread2 exit code is %d.\n", *(int*)(rval2_t));
  
    err3 = pthread_join(tid3, NULL);//rval3);
    rval3_t = &(*rval3);
    if(err3 != 0)
        printf("%s: %d\n", __func__, strerror(err3));
    printf("thread3 exit.\n");
    //printf("thread3 exit code is %d.\n", *(int*)(rval3_t));


    printids("This is the main thread");
    printf("Leave main function.\n");
    //sleep(1);
    exit(0);
}

void printids(const char *s)
{
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s, process ID is %u, thread ID is %u, and g_Flag is %d.\n", s, (uint)pid, (uint)tid, g_Flag);
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

void *thread1(void *arg)
{
    while (1)
{
    if (g_Flag == 0)
    {
    lock_thread("Thread1");
    printf("Enter thread1.\n");
    printids("This is thread1");
    int i;
    for (i = 0; i < 1000; i++)
    {
        g_Flag++;
        //usleep(1);
    }
    printids("This is thread1");
    printf("Leave thread1.\n");
    unlock_thread("Thread1");
    //pthread_exit(0);
    //return (void **)1;
    }
    else if (g_Flag >= 6000)
    {
      return (void **)1;
    } 
}
}

void *thread2(void *arg)
{
    while (1)
{
    if (g_Flag == 1000)
    {
    lock_thread("Thread2");
    printf("Enter thread2.\n");
    printids("This is thread2");
    int i;
    for (i = 0; i < 1000; i++)
    {
        g_Flag = g_Flag + 2;  
        //usleep(1);
    }
    printids("This is thread2");
    printf("Leave thread2.\n");
    unlock_thread("Thread2");
    //pthread_exit(0);
    //return (void **)2;
    }
    else if (g_Flag >= 6000)
    {
    return (void **)2;
    }
}
}

void *thread3(void *arg)
{
    while (1)
{
    if (g_Flag == 3000)
    {
    lock_thread("Thread3");
    printf("Enter thread3.\n");
    printids("This is thread3");
    int i;
    for (i = 0; i < 1000; i++)
    {
        g_Flag = g_Flag + 3;
        //usleep(1);
    }
    printids("This is thread3");
    printf("Leave thread3.\n");
    unlock_thread("Thread3");
    //pthread_exit(0);
    //return (void **)3;
    }
    else if (g_Flag >= 6000)
    {
        return (void **)3;
    }
}
}
