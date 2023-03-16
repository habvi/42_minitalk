#include <unistd.h> // pause
#include "client.h"
#include "error.h"

t_pid	g_pid;

bool	recieve_end_signal(t_error_code *error_code)
{
	while (true)
	{
		pause();
		if (g_pid.is_correct_server_pid == 1)
		{
			if (!put_recieved_message(error_code))
				return (false);
			break ;
		}
	}
	return (true);
}
