#include <signal.h> // sigaction, kill
#include <unistd.h> // usleep, pause
#include <stdbool.h>
#include <stdint.h>
#include "libft.h"
#include "ft_printf.h"
#include "client.h"
#include "error.h"

t_pid	g_pid = {.server_pid = 0, .is_correct_server_pid = 0};

static bool	is_valid_args(const int argc, t_error_code *error_code)
{
	if (argc != 3)
	{
		if (ft_printf("%s\n", MSG_USAGE) == ERROR)
		{
			*error_code = ERROR_WRITE_M;
			return (false);
		}
		*error_code = INVALID_ARGS;
		return (false);
	}
	return (true);
}

static bool	is_valid_pid(const char *arg, pid_t *pid, t_error_code *error_code)
{
	if (!ft_atoi_with_bool(arg, pid))
	{
		*error_code = INVALID_PID;
		return (false);
	}
	if (*pid <= 0)
	{
		*error_code = INVALID_PID;
		return (false);
	}
	return (true);
}

static bool	send_char(const pid_t pid, const unsigned char byte)
{
	size_t	bit_shift;
	size_t	bit_mask;
	int		result;

	bit_shift = 0;
	while (bit_shift < CHAR_BIT)
	{
		bit_mask = 1U << bit_shift;
		if ((byte & bit_mask) == 0)
			result = kill(pid, SIGUSR1);
		else
			result = kill(pid, SIGUSR2);
		if (result == ERROR)
			return (false);
		while (true)
		{
			pause();
			if (g_pid.is_correct_server_pid == 1)
			{
				bit_shift++;
				g_pid.is_correct_server_pid = 0;
				break ;
			}
		}
		usleep(10000); // to do
	}
	return (true);
}

static bool	send_message(const pid_t server_pid, const char *message, t_error_code *error_code)
{
	size_t	i;

	if (ft_printf("%s %d\n", MSG_SEND_PID, server_pid) == ERROR)
	{
		*error_code = ERROR_WRITE_M;
		return (false);
	}
	i = 0;
	while (message[i])
	{
		if (!send_char(server_pid, message[i]))
		{
			*error_code = ERROR_KILL;
			return (false);
		}
		i++;
	}
	if (!send_char(server_pid, message[i]))
	{
		*error_code = ERROR_KILL;
		return (false);
	}
	return (true);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)context;
	if (g_pid.server_pid == info->si_pid)
		g_pid.is_correct_server_pid = 1;
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
	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = signal_handler;
	if (sigaction(SIGUSR1, sa, NULL) == ERROR)
	{
		*error_code = ERROR_SIGACTION;
		return (false);
	}
	return (true);
}

int	main(int argc, char *argv[])
{
	pid_t				server_pid;
	struct sigaction	sa;
	t_error_code		error_code;

	error_code = 0;
	if (!is_valid_args(argc, &error_code))
		error_exit(error_code);
	if (!is_valid_pid(argv[1], &server_pid, &error_code))
		error_exit(error_code);
	g_pid.server_pid = server_pid;
	if (!set_sigaction(&sa, &error_code))
		error_exit(error_code);
	if (!send_message(g_pid.server_pid, argv[2], &error_code))
		error_exit(error_code);
	while (true)
	{
		pause();
		if (g_pid.is_correct_server_pid == 1)
		{
			if (ft_printf("%s\n", MSG_RECIEVED) == ERROR)
			{
				error_code = ERROR_WRITE_M;
				error_exit(error_code);
			}
			break ;
		}
	}
	return (EXIT_SUCCESS);
}
