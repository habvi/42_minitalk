#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include "libft.h"
#include "minitalk.h"

static bool	is_valid_args(const int argc)
{
	if (argc != 3)
	{
		// to do
		printf("usage : tell me PID!!\n");
		return (false);
	}
	return (true);
}

static bool	is_valid_pid(char *argv[], pid_t *pid)
{
	*pid = atoi(argv[1]);
	// to do: atoi error or pid <= 0
	if (*pid <= 0)
	{
		printf("invalid pid : %d\n", *pid);
		return (false);
	}
	printf("client pid %d\n", *pid);
	return (true);
}

static bool	send_message(const pid_t pid, const char *message)
{
	uint8_t	i;
	uint8_t	j;
	int		c;
	int		result;

	i = 0;
	while (message[i])
	{
		c = message[i];
		j = 0;
		while (j < CHAR_BIT)
		{
			if (((c >> (CHAR_BIT - j - 1)) & 1) == 0)
				result = kill(pid, SIGUSR1);
			else
				result = kill(pid, SIGUSR2);
			if (result == ERROR)
				return (false);
			usleep(500);
			j++;
		}
		i++;
	}
	// to do: '\0'?
	i = 0;
	while (i < CHAR_BIT)
	{
		if (kill(pid, SIGUSR1) == ERROR)
			return (false);
		usleep(500);
		i++;
	}
	return (true);
}

static void	signal_handler(int signum)
{
	static int	count = 0;

	if (signum == SIGUSR1)
	{
		count++;
		if (write(STDOUT_FILENO, "recieved message from server!", 30) == ERROR)
			exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	pid_t	pid;

	if (!is_valid_args(argc))
		return (EXIT_FAILURE);
	if (!is_valid_pid(argv, &pid))
		return (EXIT_FAILURE);
	// -> sigaction
	if (signal(SIGUSR1, signal_handler) == SIG_ERR)
		exit(EXIT_FAILURE);
	printf("send message from client: %s\n", argv[2]);
	if (!send_message(pid, argv[2]))
		return (EXIT_FAILURE);
	pause();
	exit(EXIT_SUCCESS);
}

// to do
// printf, atoi, memset -> ft