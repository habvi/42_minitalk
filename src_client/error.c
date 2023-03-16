#include "ft_printf.h"
#include "minitalk.h"

int	error_exit(const char *error_message)
{
	ft_printf("%s\n", error_message);
	return (EXIT_FAILURE);
}
