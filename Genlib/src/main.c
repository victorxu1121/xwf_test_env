#include <stdio.h>
#include "max.h"

int main(int argc, char *argv[])
{
    int a=10, b=-2, c=100;
	printf("max among 10, -2 and 100 is %d.\n", max(a,b,c));
    
	char *test_s = "Test string 123456!!\n";
	printstring(test_s);
	
	return;
}


