#include <signal.h> // kill
#include <unistd.h> // usleep
#include <stdbool.h>
#include <stdint.h>
#include "libft.h"
#include "minitalk.h"

static bool	is_valid_args(const int argc)
{
	if (argc != 3)
	{
		// to do: error
		ft_putstr_fd("usage: ./client <PID> <message>\n", STDOUT_FILENO);
		return (false);
	}
	return (true);
}

static bool	is_valid_pid(char *argv[], pid_t *pid)
{
	*pid = ft_atoi(argv[1]);
	// to do: atoi error or pid <= 0, atoi_with_bool
	if (*pid <= 0)
	{
		// to do: error
		ft_putstr_fd("Error: invalid pid\n", STDOUT_FILENO);
		return (false);
	}
	// to do: error
	ft_putstr_fd("send message to pid: ", STDOUT_FILENO);
	ft_putnbr_fd(*pid, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (true);
}

static bool	send_message(const pid_t pid, const char *message)
{
	uint8_t			i;
	uint8_t			j;
	unsigned char	c;
	int				result;

	i = 0;
	while (message[i])
	{
		c = message[i];
		j = 0;
		while (j < CHAR_BIT)
		{
			if (((c >> (CHAR_BIT - j - 1)) & 1) == 0)
				result = kill(pid, SIGUSR1);
			else
				result = kill(pid, SIGUSR2);
			if (result == ERROR)
				return (false);
			usleep(5000);
			j++;
		}
		i++;
	}
	return (true);
}

int	main(int argc, char *argv[])
{
	pid_t	pid;

	if (!is_valid_args(argc))
		return (error_exit(ERROR_ARGS));
	if (!is_valid_pid(argv, &pid))
		return (error_exit(ERROR_WRITE));
	if (!send_message(pid, argv[2]))
		return (error_exit(ERROR_KILL));
	return (EXIT_SUCCESS);
}
