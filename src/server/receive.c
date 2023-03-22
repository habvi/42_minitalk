#include <unistd.h> // usleep
#include <limits.h> // CHAR_BIT
#include "put.h"
#include "error.h"
#include "server.h"

static void	set_byte(unsigned char *byte, size_t *bit_index)
{
	if (get_g_signal().signum == SIGUSR1)
		;
	else if (get_g_signal().signum == SIGUSR2)
		*byte |= (1U << *bit_index);
	(*bit_index)++;
}

static bool	send_back_per_bit(t_error_code *error_code)
{
	if (kill(get_g_signal().client_pid, SIGUSR1) == ERROR)
	{
		*error_code = ERROR_KILL;
		return (false);
	}
	return (true);
}

static bool	send_end_signal_to_client(t_error_code *error_code)
{
	if (!put_client_pid(error_code))
		return (false);
	usleep(SLEEP_TIME * 4);
	if (kill(get_g_signal().client_pid, SIGUSR1) == ERROR)
	{
		*error_code = ERROR_KILL;
		return (false);
	}
	return (true);
}

static bool	send_back_per_byte(\
			unsigned char *byte, size_t *bit_index, t_error_code *error_code)
{
	if (*bit_index == CHAR_BIT)
	{
		if (*byte == '\0')
		{
			if (!send_end_signal_to_client(error_code))
				return (false);
		}
		else if (!put_byte(*byte, error_code))
			return (false);
		set_g_signum(0);
		*bit_index = 0;
		*byte = 0;
	}
	return (true);
}

bool	receive_message(t_error_code *error_code)
{
	static size_t			bit_index = 0;
	static unsigned char	byte = 0;

	set_byte(&byte, &bit_index);
	usleep(SLEEP_TIME);
	if (!send_back_per_bit(error_code))
		return (false);
	if (!send_back_per_byte(&byte, &bit_index, error_code))
		return (false);
	return (true);
}
