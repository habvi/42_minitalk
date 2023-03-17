#include "put.h"
#include "ft_dprintf.h"
#include "error.h"
#include "client.h"

bool	put_usage(t_error_code *error_code)
{
	if (ft_dprintf("%s\n", MSG_USAGE) == ERROR)
	{
		*error_code = ERROR_WRITE;
		return (false);
	}
	return (true);
}

bool	put_server_pid(t_error_code *error_code)
{
	if (ft_dprintf("%s %d\n", MSG_SEND_PID, get_g_pid().server_pid) == ERROR)
	{
		*error_code = ERROR_WRITE;
		return (false);
	}
	return (true);
}

bool	put_recieved_message(t_error_code *error_code)
{
	if (ft_dprintf("%s\n", MSG_RECIEVED) == ERROR)
	{
		*error_code = ERROR_WRITE;
		return (false);
	}
	return (true);
}

void	put_error(const char *message)
{
	ft_dprintf("Error: %s\n", message);
}
