#include "put.h"
#include "error.h"

bool	is_valid_args(const int argc, t_error_code *error_code)
{
	if (argc != 1)
	{
		if (!put_usage(error_code))
			return (false);
		*error_code = INVALID_ARGS;
		return (false);
	}
	return (true);
}
