// #include <signal.h> // sigaction
#include <stdbool.h>
#include "libft.h"
#include "error.h"
#include "server.h"

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (get_g_signal().signum == 0)
		set_g_client_pid(info->si_pid);
	if (get_g_signal().client_pid == info->si_pid)
		set_g_signum(signum);
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
	sigaddset(&sa->sa_mask, SIGUSR2);
	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = signal_handler;
	if (sigaction(SIGUSR1, sa, NULL) == ERROR)
	{
		*error_code = ERROR_SIGACTION;
		return (false);
	}
	if (sigaction(SIGUSR2, sa, NULL) == ERROR)
	{
		*error_code = ERROR_SIGACTION;
		return (false);
	}
	return (true);
}
