#include <signal.h> // sigaction
#include <unistd.h> // getpid, pause, write
#include <stdbool.h>
#include <stdint.h>
#include "libft.h"
#include "error.h"
#include "ft_printf.h"
#include "server.h"

volatile sig_atomic_t	g_signum = 0;

static bool	put_server_pid(t_error_code *error_code)
{
	if (ft_printf("%s %d\n", "server pid:", getpid()) == ERROR)
	{
		*error_code = ERROR_WRITE_M;
		return (false);
	}
	return (true);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	g_signum = signum;
}

static bool	set_sigaction(struct sigaction *sa, t_error_code *error_code)
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

static bool	put_message(t_error_code *error_code)
{
	static size_t			bit_shift = 0;
	static unsigned char	byte = 0;

	if (g_signum == SIGUSR2)
		byte |= (1U << bit_shift);
	bit_shift++;
	if (bit_shift == CHAR_BIT)
	{
		if (ft_printf("%c", byte) == ERROR)
		{
			*error_code = ERROR_WRITE_M;
			return (false);
		}
		g_signum = 0;
		bit_shift = 0;
		byte = 0;
	}
	return (true);
}

int	main(void)
{
	struct sigaction	sa;
	t_error_code		error_code;

	error_code = 0;
	if (!put_server_pid(&error_code))
		error_exit(error_code);
	if (!set_sigaction(&sa, &error_code))
		error_exit(error_code);
	while (true)
	{
		pause();
		if (!put_message(&error_code))
			error_exit(error_code);
	}
	return (EXIT_SUCCESS);
}
