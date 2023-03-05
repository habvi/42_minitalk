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

volatile sig_atomic_t	g_char = 0;

void	signal_handler(int signum)
{
	static uint8_t	len = 0;
	char			c;

	if (signum == SIGUSR1)
	{
		// if (write(STDOUT_FILENO, "0 dayo\n", 8) == ERROR)
		// 	exit(EXIT_FAILURE);
		g_char <<= 1;
	}
	else if (signum == SIGUSR2)
	{
		// if (write(STDOUT_FILENO, "1 dayo\n", 8) == ERROR)
		// 	exit(EXIT_FAILURE);
		g_char = (g_char << 1) | 1;
	}
	len++;
	if (len == CHAR_BIT)
	{
		c = g_char & ((1 << CHAR_BIT) - 1);
		if (c == '\0')
		{
			// if (write(STDOUT_FILENO, "end\n", 5) == ERROR)
			// 	exit(EXIT_FAILURE);
			g_char = 0;
			len = 0;
			return ;
		}
		if (write(STDOUT_FILENO, &c, 1) == ERROR)
			exit(EXIT_FAILURE);
		g_char = 0;
		len = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	printf("pid %d\n", getpid());
	memset(&sa, 0, sizeof(sa)); // いる？
	// success: 0, error: -1
	if (sigemptyset(&sa.sa_mask) == ERROR)
		exit(EXIT_FAILURE);
	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == ERROR)
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR2, &sa, NULL) == ERROR)
		exit(EXIT_FAILURE);

	while (true)
		pause();
	printf("finish!!");
	return (0);
}
