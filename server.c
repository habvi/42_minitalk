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

void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
		g_signum = SIGUSR1;
	else if (signum == SIGUSR2)
		g_signum = SIGUSR2;
}

static bool	put_message(void)
{
	static uint8_t	len = 0;
	static char		c = 0;

	if (g_signum == SIGUSR1)
		c <<= 1;
	else if (g_signum == SIGUSR2)
		c = (c << 1) | 1;
	len++;
	if (len == CHAR_BIT)
	{
		if (c == '\0')
		{
			// to do
			g_signum = 0;
			len = 0;
			c = 0;
			return (true);
		}
		if (write(STDOUT_FILENO, &c, 1) == ERROR)
			return (false);
		// to do
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
	memset(&sa, 0, sizeof(sa)); // いる？
	if (sigemptyset(&sa.sa_mask) == ERROR)
		return (EXIT_FAILURE);
	sa.sa_handler = signal_handler;
	// to do: set
	sa.sa_flags = 0;
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
