#include <MLUtils.h>

#include <stdlib.h>
#include <string.h>

int main(void)
{
	char string[] = "Hello World!\n";

	full_print(string, strlen(string) + 1);

	return 0;
}

