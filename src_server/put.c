#include <unistd.h> // getpid
#include <stdbool.h>
#include "libft.h"
#include "ft_dprintf.h"
#include "error.h"

bool	put_server_pid(t_error_code *error_code)
{
	if (ft_dprintf("%s %d\n", MSG_SERVER_PID, getpid()) == ERROR)
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
