#include <signal.h> // sigaction
#include "libft.h"
#include "error.h"
#include "client.h"

t_pid	g_pid;

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)context;
	if (g_pid.server_pid == info->si_pid)
		g_pid.is_correct_server_pid = 1;
}

bool	set_sigaction(struct sigaction *sa, t_error_code *error_code)
{
	ft_memset(sa, 0, sizeof(*sa));
	if (sigemptyset(&sa->sa_mask) == ERROR)
	{
		*error_code = ERROR_SIGACTION;
		return (false);
	}
	sigaddset(&sa->sa_mask, SIGUSR1);
	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = signal_handler;
	if (sigaction(SIGUSR1, sa, NULL) == ERROR)
	{
		*error_code = ERROR_SIGACTION;
		return (false);
	}
	return (true);
}
