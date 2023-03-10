#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include "minitalk.h"

// int sigaction(int sig, const struct sigaction *__restrict__ new, struct sigaction *__restrict__ old);

// struct sigaction {
// 	void		(*sa_handler)(int);
// 	void		(*sa_sigaction)(int, siginfo_t *, void *);
// 	sigset_t	sa_mask;
// 	int			sa_flags;
// 	void		(*sa_restorer)(void);
// };

volatile sig_atomic_t	g_signum = 0;

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	g_signum = signum;
}

static bool	put_message(void)
{
	static uint8_t	len = 0;
	static int		c = 0;

	if (g_signum == SIGUSR1)
		c <<= 1;
	else if (g_signum == SIGUSR2)
		c = (c << 1) | 1;
	len++;
	if (len == CHAR_BIT)
	{
		if (write(STDOUT_FILENO, &c, 1) == ERROR)
			return (false);
		g_signum = 0;
		len = 0;
		c = 0;
	}
	return (true);
}

int	main(void)
{
	struct sigaction	sa;

	printf("pid %d\n", getpid());
	memset(&sa, 0, sizeof(sa));
	if (sigemptyset(&sa.sa_mask) == ERROR)
		return (EXIT_FAILURE);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == ERROR)
		return (EXIT_FAILURE);
	if (sigaction(SIGUSR2, &sa, NULL) == ERROR)
		return (EXIT_FAILURE);
	while (true)
	{
		pause();
		if (!put_message())
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
