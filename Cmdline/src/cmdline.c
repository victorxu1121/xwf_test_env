#include "cmdline.h"

int cl_cmd_init()
{
	int i;
	for (i = 0; i < 16; i++)
	{
		strcpy(cl_cmd_list[i],"NULL");
	}
	cl_debug_printf("Cmd Init Done -- All NULL");
	return 0;
}

int cl_clr()
{
    /*
	cl_cmd_n = 0;
    while (cl_cmd_n <16) 
	{
        cl_cmd_s[cl_cmd_n] = '\0';
        cl_cmd_n++;
    }
	*/
	bzero(cl_cmd_s, sizeof(cl_cmd_s));
	cl_cmd_n = 0;
	cl_debug_printf("Cmd clear done!");
	return 0;
}

int cl_cmd_get()
{
	scanf("%s",cl_cmd_s);
	cl_debug_printf("Got the command!");
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

int cl_cmd_set(int cmd_id, char *cmd)
{
	sprintf(cl_cmd_list[cmd_id],"%s",cmd);
	cl_debug_printf("Set command done.");
	return 0;
}

int cl_cmd_id_translate()
{
	int i;
	for (i = 0; i < 16; i++)
	{
		if (cl_cmd_check(cl_cmd_list[i]))
		{
			cl_debug_printf("Translation is done.");
			return i;
		}
	}
	return -1;
}

int cl_cmd_menu_print()
{
	printf("-----Command Menu-----\n");
	//printf("");
	int i;
	char temp[128];
	bzero(temp, sizeof(temp));
	for (i = 0; i < 16; i++)
	{
		if (strcmp(cl_cmd_list[i],"NULL") != 0)
		{
			if (cl_cmd_explain[i] != NULL)
			{
				sprintf(temp, "%s", cl_cmd_explain[i]);
			}
			else 
			{
				sprintf(temp, "NULL");
			}
			printf("%s:\t %s \n",cl_cmd_list[i], temp);
		}
		bzero(temp, sizeof(temp));
	}
	printf("----------------------\n");
	return 0;
}

int cl_printf(char *print_content)
{
	printf("CmdLine: %s\n", print_content);
	return 0;
}

int cl_debug_printf(char *print_content)
{
	if (cl_cmd_debug_print)
	{
		printf("CmdLine TEST: %s\n", print_content);
	}
	return 0;
}

int cl_err_printf(char *print_content)
{
	//if (cl_err != 0)
	//{
		printf("CmdLine ERROR: %s\n", print_content);
	//}
	return 0;
}


