#include <unistd.h> // write, getpid
#include "put.h"
#include "ft_dprintf.h"
#include "error.h"
#include "server.h"

bool	put_server_pid(t_error_code *error_code)
{
	if (ft_dprintf("%s %d\n", MSG_SERVER_PID, getpid()) == ERROR)
	{
		*error_code = ERROR_WRITE_M;
		return (false);
	}
	return (true);
}

bool	put_client_pid(t_error_code *error_code)
{
	if (ft_dprintf("\n%s %d\n", MSG_CLIENT_PID, get_g_signal().client_pid) == ERROR)
	{
		*error_code = ERROR_WRITE_M;
		return (false);
	}
	return (true);
}

bool	put_byte(const unsigned char byte, t_error_code *error_code)
{
	if (write(STDOUT_FILENO, &byte, sizeof(unsigned char)) == ERROR)
	{
		*error_code = ERROR_WRITE_M;
		return (false);
	}
	return (true);
}

void	put_error(const char *message)
{
	ft_dprintf("Error: %s\n", message);
}
