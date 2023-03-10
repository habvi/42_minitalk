#include <signal.h> // sigaction, kill
#include <unistd.h> // usleep
#include <stdbool.h>
#include <stdint.h>
#include "libft.h"
#include "ft_printf.h"
#include "minitalk.h"

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
		usleep(10000); // to do
		bit_shift++;
	}
	return (true);
}

static bool	send_message(const pid_t pid, const char *message)
{
	size_t	i;

	if (ft_printf("send message to pid: %d\n", pid) == ERROR)
		return (false);
	i = 0;
	while (message[i])
	{
		if (!send_char(pid, message[i]))
			return (false);
		i++;
	}
	if (!send_char(pid, message[i]))
		return (false);
	return (true);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
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
	pid_t				pid;
	struct sigaction	sa;

	if (!is_valid_args(argc))
		return (error_exit(ERROR_MSG_ARGS));
	if (!is_valid_pid(argv, &pid))
		return (error_exit(ERROR_MSG_PID));
	if (!set_sigaction(&sa))
		return (error_exit(ERROR_MSG_SIGACTION));
	if (!send_message(pid, argv[2]))
		return (error_exit(ERROR_MSG_KILL)); // to do
	pause();
	if (ft_printf("recieved message from server!\n") == ERROR)
		return (error_exit(ERROR_MSG_WRITE));
	return (EXIT_SUCCESS);
}
