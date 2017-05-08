#include <string.h>
#include <stdio.h>

char cl_cmd_s[16];
int  cl_cmd_n;
int  cl_cmd_id;
char cl_cmd_list[16][16];
char *cl_cmd_explain[16];
int  cl_cmd_debug_print;

int cl_cnd_init();
int cl_cmd_clr();
int cl_cmd_get();
int cl_cmd_check(char *cmd);
int cl_cmd_set(int cmd_id, char *cmd);
int cl_cmd_id_translate();
int cl_cmd_menu_print();
int cl_printf(char *print_content);
int cl_debug_printf(char *print_content);
int cl_err_printf(char *print_content);

