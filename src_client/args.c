#include "ft_printf.h"
#include "error.h"

bool	is_valid_args(const int argc, t_error_code *error_code)
{
	if (argc != 3)
	{
		if (ft_printf("%s\n", MSG_USAGE) == ERROR)
		{
			*error_code = ERROR_WRITE_M;
			return (false);
		}
		*error_code = INVALID_ARGS;
		return (false);
	}
	return (true);
}