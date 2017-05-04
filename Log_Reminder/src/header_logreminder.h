#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_PATH "LogFile/"
#define FILE_TYPE "txt"

///===Variable===////

time_t lr_timep;     /* time local */
struct tm *lr_p_tm;     /* time */

struct timeval lr_tv_current;
struct timeval lr_tv_start;
struct timeval lr_tv_diff;

FILE *lr_file_id;
char lr_file_name[32];
char *lr_file_path;// = FILE_PATH;
char *lr_file_type;// = FILE_TYPE;
char lr_p_content[256];


int lr_err;

///===Function===///

int lr_init(void);

int lr_init_get_datetime(void);
int lr_get_start_time(void);
int lr_get_current_time(void);
int lr_get_time_diff(void);

int lr_init_create_log(char *file_path, char *file_name, char *file_type);
int lr_init_get_file_name(char *file_type);

int lr_record_event(char *record_content);//, char *file_name);

