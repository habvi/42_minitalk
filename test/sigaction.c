#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>

#define ERROR -1

// int sigaction(int sig, const struct sigaction *__restrict__ new, struct sigaction *__restrict__ old);

// struct sigaction {
// 	void		(*sa_handler)(int);
// 	void		(*sa_sigaction)(int, siginfo_t *, void *);
// 	sigset_t	sa_mask;
// 	int			sa_flags;
// 	void		(*sa_restorer)(void);
// };

volatile sig_atomic_t	g_finish = 0;

void	signal_handler(int signum)
{
	if (signum == SIGTERM)
		g_finish = 1;
	else
		write(1, "not stop\n", 10);
}

int	main(void)
{
	struct sigaction	sa;
	size_t				i;

	printf("pid %d\n", getpid());
	memset(&sa, 0, sizeof(sa)); // いる？
	// success: 0, error: -1
	if (sigemptyset(&sa.sa_mask) == ERROR)
		exit(EXIT_FAILURE);
	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == ERROR)
		exit(EXIT_FAILURE);
	i = 0;
	while (!g_finish)
	{
		printf("%zu\n", i);
		sleep(1);
		i++;
	}
	printf("finish!!");
	return (0);
}
