#include <stdio.h>

int main(int argc, char const *argv[])
{
	printf("==========\nTest Start\n==========\n");
	char cmd_s[16];
	int cmd_id;
	int cmd_n;
	int i;
	while(1)
	{
	cmd_s[16] = '\0';
	cmd_n = 0;
	while( (cmd_s[cmd_n] = getchar()) != '\n' )
	{
	//scanf("%s\n",cmd_s);
	printf("%c-%d| ",cmd_s[cmd_n],cmd_n);
	cmd_n++;
	}
	printf("\n---%s---\n",cmd_s);
	
	cmd_n=0;
	while (cmd_n < 16)
	{
		printf(":%c:",cmd_s[cmd_n]);
		cmd_n++;
	}
	printf("\n");

	if (cmd_s == "quit\r")
		{printf("quit yes\n");break;}
	else 
		{printf("quit no\n");}
	}
	printf("==========\nTest End\n==========\n");
	return 0;
}
