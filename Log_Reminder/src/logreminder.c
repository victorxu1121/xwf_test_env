#include "header_logreminder.h"

int lr_get_start_time()
{
	 gettimeofday(&lr_tv_start, NULL);
}

int lr_get_current_time()
{
	 gettimeofday(&lr_tv_current, NULL);
}

int lr_get_time_diff()
{
	lr_tv_diff.tv_sec = lr_tv_current.tv_sec - lr_tv_start.tv_sec;
	lr_tv_diff.tv_usec = (lr_tv_current.tv_sec - lr_tv_start.tv_sec) * 1000000 + (lr_tv_current.tv_usec - lr_tv_start.tv_usec);
}

int lr_init_get_datetime()
{
	time(&lr_timep);
	lr_p_tm=localtime(&lr_timep);
	printf("Test Time is:%d-%d-%d %d:%d:%d\n",lr_p_tm->tm_year + 1900,lr_p_tm->tm_mon + 1,lr_p_tm->tm_mday,lr_p_tm->tm_hour,lr_p_tm->tm_min,lr_p_tm->tm_sec);
}

int lr_init_get_file_name(char *file_type)
{
	//char file_type_temp[8];
    //file_type_temp = *file_type;
    printf("file_type = %s\n", file_type);
    if (file_type == "txt")
        printf("Type is txt\n");
    if (1)//file_type_temp == "txt")
	{
		printf("%04d%02d%02d_%02d%02d%02d.txt\n",lr_p_tm->tm_year + 1900,lr_p_tm->tm_mon + 1,lr_p_tm->tm_mday,lr_p_tm->tm_hour,lr_p_tm->tm_min,lr_p_tm->tm_sec);
		sprintf(lr_file_name, "%04d%02d%02d_%02d%02d%02d.txt",lr_p_tm->tm_year + 1900,lr_p_tm->tm_mon + 1,lr_p_tm->tm_mday,lr_p_tm->tm_hour,lr_p_tm->tm_min,lr_p_tm->tm_sec);
		printf("lr_file_name = %s\n", lr_file_name);
		//sprintf(lr_file_name, "Test file.txt");
        return 0;
	}
	else 
	{
		return 1;
	}
}

int lr_init_create_log(char *file_path, char *file_name, char *file_type)
{
	if (access(file_path,0)<0)
    {
        mkdir(file_path,777);
    }
    chdir(file_path);
    printf("Test:Changed the file path\n");
    lr_err = lr_init_get_file_name(lr_file_type);
    if (lr_err)
    {
    	printf("Error: The file create failed: The unsupported file type!\n");
    	return 1;
    }
    else 
    {
        printf("Test: The file name is got: %s\n",lr_file_name);
    }

    if( (lr_file_id = fopen(lr_file_name, "w+")) == NULL)
	{
		printf("Error: Can not open file!\n");
		return 1;
	}

	fprintf(lr_file_id, "Test %04d%02d%02d %02d%02d%02d\n",lr_p_tm->tm_year + 1900,lr_p_tm->tm_mon + 1,lr_p_tm->tm_mday,lr_p_tm->tm_hour,lr_p_tm->tm_min,lr_p_tm->tm_sec);
	fclose(lr_file_id);
	return 0;
}

int lr_record_event(char *record_content)//, char *file_name)
{
	lr_get_current_time();
	lr_get_time_diff();
	if( (lr_file_id = fopen(lr_file_name, "a+")) == NULL)
	{
		printf("Error: Can not open file!\n");
		return 1;
	}
	fprintf(lr_file_id, "[% 15ld.%06ld]", lr_tv_diff.tv_sec,lr_tv_diff.tv_usec);
	fprintf(lr_file_id, "%s\n",record_content);
	fclose(lr_file_id);
    return 0;
}

int lr_init()
{
	lr_init_get_datetime();
	printf("Test:Got the date time\n");
    lr_get_start_time();
	printf("Test:Got the start time\n");
    lr_err = lr_init_create_log(lr_file_path, lr_file_name, lr_file_type);
    if (lr_err)
    {
        printf("Error:Create log file failed!\n");
        return 1;
    }
	printf("Test:Created the log file\n");
	lr_record_event("Create the log file.");//, lr_file_name);
	printf("Test:Recorded the first message\n");
	return 0;
}



