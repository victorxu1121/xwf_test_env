#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

time_t timep;     /* time local */
struct tm *p;     /* time */
// struct ref_time
// {
// 	int sec_ref;
// 	int min_ref;
// 	int hour_ref;
// 	int mday_ref;
// 	int mon_ref;
// 	int year_ref;
// }REF_TIME;
/*
struct timeval 
{
    int tv_sec;
    int tv_usec;
};
*/
struct timeval tv_current;
struct timeval tv_start;
struct timeval tv_temp;

FILE *file_log=NULL;
char txt_name[32];

struct str
{
    int a;
    int b;
    int c;
};

struct str change(struct str s)
{
    s.a ++;
    s.b ++;
    s.c ++;
    return s;
}



// struct timeval lr_get_current_time()
// {
//     struct timeval p_temp;
//     gettimeofday(&p_temp);
//     return p_temp;
// }



// struct timeval lr_get_running_time(struct timeval current, struct timeval start)
// {
//     struct timeval p_temp;
//     return p_temp;
// }

void lr_get_time_diff()//struct timeval current, struct timeval start)
{
// 	current = tv_current;
// 	start = tv_start;
	tv_temp.tv_sec = tv_current.tv_sec - tv_start.tv_sec;
	tv_temp.tv_usec = (tv_current.tv_sec - tv_start.tv_sec) * 1000000 + (tv_current.tv_usec -tv_start.tv_usec);
}

int main(int argc, char const *argv[])
{
	time(&timep);
	p=localtime(&timep);
	gettimeofday(&tv_start,NULL);

	// REF_TIME.sec_ref  = p->tm_sec;
	// REF_TIME.min_ref  = p->tm_min;
	// REF_TIME.hour_ref = p->tm_hour;
	// REF_TIME.mday_ref = p->tm_mday;
	// REF_TIME.mon_ref  = p->tm_mon+1;
	// REF_TIME.year_ref = 1900+p->tm_year;

	// printf("Start Time is:%d-%d-%d %d:%d:%d\n",REF_TIME.year_ref,REF_TIME.mon_ref,REF_TIME.mday_ref,REF_TIME.hour_ref,REF_TIME.min_ref,REF_TIME.sec_ref);
	// printf("Start Time is:%04d%02d%02d %02d%02d%02d\n",REF_TIME.year_ref,REF_TIME.mon_ref,REF_TIME.mday_ref,REF_TIME.hour_ref,REF_TIME.min_ref,REF_TIME.sec_ref);

	// sprintf(txt_name, "%04d%02d%02d_%02d%02d%02d.txt",REF_TIME.year_ref,REF_TIME.mon_ref,REF_TIME.mday_ref,REF_TIME.hour_ref,REF_TIME.min_ref,REF_TIME.sec_ref);

	printf("Start Time is:%d-%d-%d %d:%d:%d\n",p->tm_year + 1900,p->tm_mon + 1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
	printf("Start Time is:%04d%02d%02d %02d%02d%02d\n",p->tm_year + 1900,p->tm_mon + 1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);

	sprintf(txt_name, "%04d%02d%02d_%02d%02d%02d.txt",p->tm_year + 1900,p->tm_mon + 1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);

	
    if (access("LogFile/",0)<0)
    {
        mkdir("LogFile/",777);
    }
    chdir("LogFile/");

    if( (file_log = fopen(txt_name, "w+")) == NULL)
	{
		printf("Can not open file!\n");
	}
	gettimeofday(&tv_current,NULL);	
	// fprintf(file_log, "Test begin at %04d%02d%02d %02d%02d%02d\n",REF_TIME.year_ref,REF_TIME.mon_ref,REF_TIME.mday_ref,REF_TIME.hour_ref,REF_TIME.min_ref,REF_TIME.sec_ref);
	fprintf(file_log, "Test begin at %04d%02d%02d %02d%02d%02d\n",p->tm_year + 1900,p->tm_mon + 1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
	lr_get_time_diff();//(tv_current,tv_start);
	fprintf(file_log, "[% 15ld.%06ld]", tv_temp.tv_sec,tv_temp.tv_usec);
	// fprintf(file_log, "[% 15ld.%06ld]", tv_current.tv_sec,tv_current.tv_usec);
	fprintf(file_log, "Create the file\n");
	fclose(file_log);

    struct str s1,s2;
    s1.a=1;
    s1.b=2;
    s1.c=3;
    printf("a=%d; b=%d; c=%d\n",s1.a,s1.b,s1.c);
    
    s2 = change(s1);
    printf("a=%d; b=%d; c=%d\n",s2.a,s2.b,s2.c);


	int i;
	for (i = 0; i<100; i++)
	{
		gettimeofday(&tv_current,NULL);
		
		file_log = fopen(txt_name, "a+");
		lr_get_time_diff();//(tv_current,tv_start);
		fprintf(file_log, "[% 15ld.%06ld]", tv_temp.tv_sec,tv_temp.tv_usec);
		// fprintf(file_log, "[% 15ld.%06ld]", tv_current.tv_sec,tv_current.tv_usec);
		fprintf(file_log, "The loop index is %d\n", i);
		fclose(file_log);
		usleep(10000);///50ms
        
        s2 = change(s2);
        //printf("a=%d; b=%d; c=%d\n",s2.a,s2.b,s2.c);

  //       tv_temp = lr_get_current_time();
		// printf("[% 15ld.%06ld]", tv_temp.tv_sec,tv_temp.tv_usec);
		
	}


	gettimeofday(&tv_current,NULL);	
	file_log = fopen(txt_name, "a+");
	lr_get_time_diff();//(tv_current,tv_start);
	fprintf(file_log, "[% 15ld.%06ld]", tv_temp.tv_sec,tv_temp.tv_usec);
	//fprintf(file_log, "[% 15ld.%06ld]", tv_current.tv_sec,tv_current.tv_usec);
	fprintf(file_log, "End the test\n");
	fclose(file_log);

	return 0;
}

