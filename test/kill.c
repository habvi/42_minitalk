#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <stdint.h>

#define ERROR -1

int main(int argc, char *argv[])
{
	pid_t	pid;

	if (argc != 3)
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

	const char	*message = argv[2];
	printf("received message: %s\n", message);
	uint8_t	i;
	uint8_t	j;
	char	c;
	i = 0;
	while (message[i])
	{
		c = message[i];
		j = 0;
		while (j < CHAR_BIT)
		{
			if (((c >> (CHAR_BIT - j - 1)) & 1) == 0)
			{
				if (kill(pid, SIGUSR1) == ERROR)
					exit(EXIT_FAILURE);
			}
			else
			{
				if (kill(pid, SIGUSR2) == ERROR)
					exit(EXIT_FAILURE);
			}
			usleep(500);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < CHAR_BIT)
	{
		if (kill(pid, SIGUSR1) == ERROR)
			exit(EXIT_FAILURE);
		usleep(500);
		i++;
	}

	// success: 0, error: -1
	// int res = kill(pid, SIGUSR1);
	// if (res == ERROR)
	// {
	// 	if (errno == EPERM)
	// 		printf("process exists, but don't have permission to send it a signal\n");
	// 	else if (errno == ESRCH)
	// 		printf("process doesn't exist\n");
	// 	else
	// 	{
	// 		perror("kill");
	// 		exit(EXIT_FAILURE);
	// 	}
	// }
	// else
	// 	printf("process exists, success to send it a signal\n");
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