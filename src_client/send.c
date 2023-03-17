// #include <signal.h> // kill
#include <unistd.h> // usleep, pause
#include <limits.h> // CHAR_BIT
#include "client.h"
#include "error.h"

extern t_pid	g_pid;

static void	wait_correct_signal(void)
{
	while (true)
	{
		pause();
		if (g_pid.is_correct_server_pid == 1)
		{
			g_pid.is_correct_server_pid = 0;
			return ;
		}
	}
}

static bool	send_char(\
			const pid_t pid, const unsigned char byte, t_error_code *error_code)
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
		{
			*error_code = ERROR_KILL;
			return (false);
		}
		wait_correct_signal();
		bit_shift++;
		usleep(10000); // to do
	}
	return (true);
}

static bool	send_message_to_server(\
		const pid_t server_pid, const char *message, t_error_code *error_code)
{
	size_t	i;

	i = 0;
	while (message[i])
	{
		if (!send_char(server_pid, message[i], error_code))
			return (false);
		i++;
	}
	if (!send_char(server_pid, '\0', error_code))
		return (false);
	return (true);
}

bool	send_message(\
		const pid_t server_pid, const char *message, t_error_code *error_code)
{
	if (!put_server_pid(server_pid, error_code))
		return (false);
	if (!send_message_to_server(server_pid, message, error_code))
		return (false);
	return (true);
}
