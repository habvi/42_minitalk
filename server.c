#include <signal.h> // sigaction
#include <unistd.h> // getpid, pause, write
#include <stdbool.h>
#include <stdint.h>
#include "libft.h"
#include "ft_printf.h"
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

static bool	put_server_pid(void)
{
	if (ft_printf("%s %d\n", "server pid:", getpid()) == ERROR)
		return (false);
	return (true);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	g_signum = signum;
}

static bool	set_sigaction(struct sigaction *sa)
{
	ft_memset(sa, 0, sizeof(*sa));
	if (sigemptyset(&sa->sa_mask) == ERROR)
		return (false);
	sigaddset(&sa->sa_mask, SIGUSR1);
	sigaddset(&sa->sa_mask, SIGUSR2);
	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = signal_handler;
	return (true);
}

static bool	put_message(void)
{
	static size_t			len = 0;
	static unsigned char	c = 0;

	if (g_signum == SIGUSR1)
	{
		// c |= (1U << n);
		c <<= 1;
	}
	else if (g_signum == SIGUSR2)
		c = (c << 1) | 1;
	len++;
	if (len == CHAR_BIT)
	{
		if (ft_printf("%c", c) == ERROR)
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

	if (!put_server_pid())
		return (error_exit(ERROR_MSG_WRITE));
	if (!set_sigaction(&sa))
		return (error_exit(ERROR_MSG_SIGACTION));
	if (sigaction(SIGUSR1, &sa, NULL) == ERROR)
		return (error_exit(ERROR_MSG_SIGACTION));
	if (sigaction(SIGUSR2, &sa, NULL) == ERROR)
		return (error_exit(ERROR_MSG_SIGACTION));
	while (true)
	{
		pause();
		if (!put_message())
			return (error_exit(ERROR_MSG_WRITE));
	}
	return (EXIT_SUCCESS);
}
