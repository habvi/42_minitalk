#include <signal.h> // sigaction, kill
#include <unistd.h> // usleep, pause
#include <stdbool.h>
#include <stdint.h>
#include "libft.h"
#include "ft_printf.h"
#include "client.h"
#include "minitalk.h"

volatile sig_atomic_t	g_server_pid = 0;
volatile sig_atomic_t	g_is_correct_server_pid = 0;

static bool	is_valid_args(const int argc)
{
	if (argc != 3)
	{
		// to do
		if (ft_printf("%s\n", MSG_USAGE) == ERROR)
			return (false);
		return (false);
	}
	return (true);
}

static bool	is_valid_pid(char *argv[], pid_t *pid)
{
	if (!ft_atoi_with_bool(argv[1], pid))
		return (false);
	if (*pid <= 0)
		return (false);
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
			if (g_is_correct_server_pid == 1)
			{
				bit_shift++;
				g_is_correct_server_pid = 0;
				break ;
			}
		}
		usleep(10000); // to do
	}
	return (true);
}

static bool	send_message(const pid_t server_pid, const char *message)
{
	size_t	i;

	if (ft_printf("send message to pid: %d\n", server_pid) == ERROR)
		return (false);
	i = 0;
	while (message[i])
	{
		if (!send_char(server_pid, message[i]))
			return (false);
		i++;
	}
	if (!send_char(server_pid, message[i]))
		return (false);
	return (true);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)context;
	if (g_server_pid == info->si_pid)
		g_is_correct_server_pid = 1;
}

static bool	set_sigaction(struct sigaction *sa)
{
	ft_memset(sa, 0, sizeof(*sa));
	if (sigemptyset(&sa->sa_mask) == ERROR)
		return (false);
	sigaddset(&sa->sa_mask, SIGUSR1);
	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = signal_handler;
	if (sigaction(SIGUSR1, sa, NULL) == ERROR)
		return (false);
	return (true);
}

int	main(int argc, char *argv[])
{
	pid_t				server_pid;
	struct sigaction	sa;

	if (!is_valid_args(argc))
		return (error_exit(ERROR_MSG_ARGS));
	if (!is_valid_pid(argv, &server_pid))
		return (error_exit(ERROR_MSG_PID));
	g_server_pid = server_pid;
	if (!set_sigaction(&sa))
		return (error_exit(ERROR_MSG_SIGACTION));
	if (!send_message(server_pid, argv[2]))
		return (error_exit(ERROR_MSG_KILL)); // to do
	while (true)
	{
		pause();
		if (g_is_correct_server_pid == 1)
		{
			if (ft_printf("recieved message from server!\n") == ERROR)
				return (error_exit(ERROR_MSG_WRITE));
			break ;
		}
	}
	return (EXIT_SUCCESS);
}
