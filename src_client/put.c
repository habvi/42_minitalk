#include "libft.h"
#include "ft_dprintf.h"
#include "error.h"

bool	put_usage(t_error_code *error_code)
{
	if (ft_dprintf("%s\n", MSG_USAGE) == ERROR)
	{
		*error_code = ERROR_WRITE_M;
		return (false);
	}
	return (true);
}

bool	put_server_pid(const pid_t server_pid, t_error_code *error_code)
{
	if (ft_dprintf("%s %d\n", MSG_SEND_PID, server_pid) == ERROR)
	{
		*error_code = ERROR_WRITE_M;
		return (false);
	}
	return (true);
}

bool	put_recieved_message(t_error_code *error_code)
{
	if (ft_dprintf("%s\n", MSG_RECIEVED) == ERROR)
	{
		*error_code = ERROR_WRITE_M;
		return (false);
	}
	return (true);
}
