#include "header_logreminder.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    lr_file_path = FILE_PATH;
    lr_file_type = FILE_TYPE;

    lr_err = lr_init();
	if (lr_err)
	{
		printf("log reminder initialize failed!\n");
		return 1;
	}
    else 
    {   
        printf("log reminder initialize successed!\n");
    }
	lr_record_event("Test Start");


	int i;
    //lr_p_content[256];

	for (i = 0; i<10; i++)
	{
		sprintf(lr_p_content, "Loop index %d", i);
		lr_record_event(lr_p_content);
		usleep(10000);///50ms
	}

	lr_record_event("Test End");

	return 0;
}


