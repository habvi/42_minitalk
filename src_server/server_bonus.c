#include <signal.h> // sigaction
#include <unistd.h> // getpid, usleep, pause, write
#include <stdbool.h>
#include <stdint.h>
#include "libft.h"
#include "ft_printf.h"
#include "error.h"
#include "server.h"

t_signal	g_signal = {.signum = 0, .client_pid = 0};

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
	(void)context;
	if (g_signal.signum == 0)
		g_signal.client_pid = info->si_pid;
	if (g_signal.client_pid == info->si_pid)
		g_signal.signum = signum;
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

	if (g_signal.signum == SIGUSR2)
		byte |= (1U << bit_shift);
	bit_shift++;
	usleep(5000); // to do
	if (kill(g_signal.client_pid, SIGUSR1) == ERROR)
	{
		*error_code = ERROR_KILL;
		return (false);
	}
	if (bit_shift == CHAR_BIT)
	{
		if (byte == '\0')
		{
			put_str_int_to_stderr("\n> client pid: ", g_signal.client_pid);
			usleep(20000); // to do
			if (kill(g_signal.client_pid, SIGUSR1) == ERROR)
			{
				*error_code = ERROR_KILL;
				return (false);
			}
		}
		else if (ft_printf("%c", byte) == ERROR)
		{
			*error_code = ERROR_WRITE_M;
			return (false);
		}
		g_signal.signum = 0;
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
