#include <signal.h> // kill
#include <unistd.h> // usleep
#include <stdbool.h>
#include <stdint.h>
#include "libft.h"
#include "ft_printf.h"
#include "error.h"
#include "client.h"

static bool	is_valid_pid(char *argv[], pid_t *pid, t_error_code *error_code)
{
	if (!ft_atoi_with_bool(argv[1], pid))
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
		usleep(1000);
		bit_shift++;
	}
	return (true);
}

static bool	send_message(const pid_t pid, const char *message, t_error_code *error_code)
{
	size_t	i;

	i = 0;
	while (message[i])
	{
		if (!send_char(pid, message[i]))
		{
			*error_code = ERROR_KILL;
			return (false);
		}
		i++;
	}
	return (true);
}

int	main(int argc, char *argv[])
{
	pid_t			pid;
	t_error_code	error_code;

	if (!is_valid_args(argc, &error_code))
		error_exit(error_code);
	if (!is_valid_pid(argv, &pid, &error_code))
		error_exit(error_code);
	if (ft_printf("%s %d\n", MSG_SEND_PID, pid) == ERROR)
	{
		error_code = ERROR_WRITE_M;
		error_exit(error_code);
	}
	if (!send_message(pid, argv[2], &error_code))
		error_exit(error_code);
	return (EXIT_SUCCESS);
}
