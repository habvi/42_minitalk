#include <signal.h> // kill
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
	size_t	j;
	size_t	bit_shift;
	size_t	bit_mask;
	int		result;

	j = 0;
	while (j < CHAR_BIT)
	{
		bit_shift = CHAR_BIT - j - 1;
		bit_mask = 1U << bit_shift;
		if ((byte & bit_mask) == 0)
			result = kill(pid, SIGUSR1);
		else
			result = kill(pid, SIGUSR2);
		if (result == ERROR)
			return (false);
		usleep(2000);
		j++;
	}
	return (true);
}

static bool	send_message(const pid_t pid, const char *message)
{
	size_t	i;

	i = 0;
	while (message[i])
	{
		if (!send_char(pid, message[i]))
			return (false);
		i++;
	}
	return (true);
}

int	main(int argc, char *argv[])
{
	pid_t	pid;

	if (!is_valid_args(argc))
		return (error_exit(ERROR_MSG_ARGS));
	if (!is_valid_pid(argv, &pid))
		return (error_exit(ERROR_MSG_PID));
	if (ft_printf("%s %d\n", MSG_SEND_PID, pid) == ERROR)
		return (error_exit(ERROR_MSG_WRITE));
	if (!send_message(pid, argv[2]))
		return (error_exit(ERROR_MSG_KILL));
	return (EXIT_SUCCESS);
}
