#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

int main()
{
	int i;

	fprintf(stdout, "strsignal() :\n");

	for (i = 0; i < NSIG; i++) {
		fprintf(stdout, "%d %s\n", i, strsignal(i));
	}

	fprintf(stdout, "\nsys_siglist[] :\n");

	for (i = 0; i < NSIG; i++) {
		fprintf(stdout, "%d %s\n", i, sys_siglist[i]);
	}

	return EXIT_SUCCESS;
}

