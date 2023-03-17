// #include <signal.h> // kill
#include <unistd.h> // usleep, pause
#include <limits.h> // CHAR_BIT
#include "put.h"
#include "error.h"
#include "client.h"

static void	wait_correct_signal(void)
{
	while (true)
	{
		pause();
		if (get_g_pid().is_correct_server_pid == 1)
		{
			set_g_is_correct_server_pid(0);
			return ;
		}
	}
}

static bool	send_char(const unsigned char byte, t_error_code *error_code)
{
	size_t	bit_shift;
	size_t	bit_mask;
	int		result;

	bit_shift = 0;
	while (bit_shift < CHAR_BIT)
	{
		bit_mask = 1U << bit_shift;
		if ((byte & bit_mask) == 0)
			result = kill(get_g_pid().server_pid, SIGUSR1);
		else
			result = kill(get_g_pid().server_pid, SIGUSR2);
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
					const char *message, t_error_code *error_code)
{
	size_t	i;

	i = 0;
	while (message[i])
	{
		if (!send_char(message[i], error_code))
			return (false);
		i++;
	}
	if (!send_char('\0', error_code))
		return (false);
	return (true);
}

bool	send_message(const char *message, t_error_code *error_code)
{
	if (!put_server_pid(error_code))
		return (false);
	if (!send_message_to_server(message, error_code))
		return (false);
	return (true);
}
