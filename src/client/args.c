#include "libft.h"
#include "put.h"
#include "error.h"
#include "client.h"

bool	is_valid_args(const int argc, t_error_code *error_code)
{
	if (argc != 3)
	{
		if (!put_usage(error_code))
			return (false);
		*error_code = INVALID_ARGS;
		return (false);
	}
	return (true);
}

bool	is_valid_pid(const char *arg, t_error_code *error_code)
{
	int	server_pid;

	if (!ft_atoi_strictly(arg, &server_pid))
	{
		*error_code = INVALID_PID;
		return (false);
	}
	if (server_pid <= 0)
	{
		*error_code = INVALID_PID;
		return (false);
	}
	set_g_server_pid(server_pid);
	return (true);
}
