#include <unistd.h>
#include "ft_dprintf.h"
#include "put.h"
#include "error.h"
#include "client.h"

bool	put_usage(t_error_code *error_code)
{
	if (ft_dprintf(STDERR_FILENO, "%s\n", MSG_USAGE) == ERROR)
	{
		*error_code = ERROR_WRITE;
		return (false);
	}
	return (true);
}

bool	put_server_pid(t_error_code *error_code)
{
	if (ft_dprintf(STDERR_FILENO, "%s %d\n", MSG_SEND_PID, get_g_pid().server_pid) == ERROR)
	{
		*error_code = ERROR_WRITE;
		return (false);
	}
	return (true);
}

bool	put_received_message(t_error_code *error_code)
{
	if (ft_dprintf(STDERR_FILENO, "%s\n", MSG_RECEIVED) == ERROR)
	{
		*error_code = ERROR_WRITE;
		return (false);
	}
	return (true);
}

void	put_error(const char *message)
{
	ft_dprintf(STDERR_FILENO, "Error: %s\n", message);
}
