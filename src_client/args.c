#include "libft.h"
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

bool	is_valid_pid(const char *arg, pid_t *pid, t_error_code *error_code)
{
	if (!ft_atoi_with_bool(arg, pid))
	{
		*error_code = INVALID_PID;
		return (false);
	}
	if (*pid <= 0)
	{
		*error_code = INVALID_PID;
		return (false);
	}
	return (true);
}
