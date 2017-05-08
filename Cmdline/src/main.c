#include <stdio.h>
//#include <string.h>
#include "cmdline.h"

/*
char cl_cmd_s[16];
int  cmd_id;
int  cl_cmd_n;
*/
int main(int argc, char const *argv[])
{
	printf("==========\nTest Start\n==========\n");
 	cl_cmd_init();	
	cl_cmd_debug_print = 1;
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


	cl_cmd_menu_print();
	while(1)
	{
		cl_clr();
        cl_cmd_get();
		
	/*	
		if (cl_cmd_check("test"))
			{printf("test ok\n");}
		else 
			{printf("test not ok\n");}

		if (strcmp(cl_cmd_s, "quit") == 0)
		{printf("quit yes\n");break;}
	    else 
		{printf("quit no\n");}
	*/
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
				break;
			}
		case 2: 
			{
				cl_printf("run cmd got!");
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
	printf("==========\nTest End\n==========\n");
	return 0;
}
/*
int cl_clr()
{
    cl_cmd_n = 0;
    while (cl_cmd_n <16)
    {
        cl_cmd_s[cl_cmd_n] = '\0';
        cl_cmd_n++;
    }
	cl_cmd_n = 0;
	return 0;
}

int cl_cmd_get()
{
	scanf("%s",cl_cmd_s);
	return 0;
}

int cl_cmd_check(char *cmd)
{
	char cmd_temp[16];
	sprintf(cmd_temp, "%s", cmd);
	if (strcmp(cl_cmd_s, cmd_temp) == 0)
		{return	1;}
	else
		{return	0;}
}
*/
