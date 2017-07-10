// a simple program
#include <stdio.h>
#include <stdlib.h>
#include "TutorialConfig.h"

int main (int argc, char *argv[])
{
	printf("Hello World\n");
	printf("%s version: %d.%d\n", argv[0], Tutorial_VERSION_MAJOR, Tutorial_VERSION_MINOR);
}
