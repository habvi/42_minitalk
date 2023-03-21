#include <unistd.h> // pause
#include "put.h"
#include "error.h"
#include "client.h"

bool	receive_end_signal(t_error_code *error_code)
{
	while (true)
	{
		pause();
		if (get_g_pid().is_correct_server_pid == 1)
		{
			if (!put_received_message(error_code))
				return (false);
			break ;
		}
	}
	return (true);
}
