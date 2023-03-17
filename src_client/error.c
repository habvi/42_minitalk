#include <stdlib.h>
#include <unistd.h>
#include "ft_dprintf.h"
#include "error.h"
#include "client.h"

void	error_exit(const t_error_code error_code)
{
	static const char	*msgs[] = {NULL, \
									ERROR_MSG_ARGS, \
									ERROR_MSG_PID, \
									ERROR_MSG_SIGACTION, \
									ERROR_MSG_KILL, \
									ERROR_MSG_WRITE};

	ft_dprintf("Error: %s\n", msgs[error_code]);
	exit(EXIT_FAILURE);
}
