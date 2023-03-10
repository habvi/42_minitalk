#include "libft.h"
#include "minitalk.h"

int	error_exit(const char *error_message)
{
	ft_putstr_fd(error_message, STDOUT_FILENO);
	return (EXIT_FAILURE);
}
