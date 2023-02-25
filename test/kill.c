#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>

#define ERROR -1

int main(int argc, char *argv[])
{
	pid_t	pid;

	if (argc != 2)
	{
		printf("usage : %s pid\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	pid = atoi(argv[1]);
	printf("sender pid %d\n", pid);
	if (pid <= 0)
	{
		printf("invalid pid : %d\n", pid);
		exit(EXIT_FAILURE);
	}

	// success: 0, error: -1
	int res = kill(pid, SIGQUIT);
	if (res == ERROR)
	{
		if (errno == EPERM)
			printf("process exists, but don't have permission to send it a signal\n");
		else if (errno == ESRCH)
			printf("process doesn't exist\n");
		else
		{
			perror("kill");
			exit(EXIT_FAILURE);
		}
	}
	else
		printf("process exists, success to send it a signal\n");
	exit(EXIT_SUCCESS);
}

/*
./receiver
./sender PID
---
./receiver
kill -2 PID   (SIGINT)
kill -INT PID (SIGINT)
kill PID      (SIGQUIT)
---

*/