#include "libft.h"
#include "ft_printf.h"
#include "error.h"

void	put_str_to_stderr(const char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
}

void	put_stderr(const char *str, const int num)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putnbr_fd(num, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

bool	put_usage(t_error_code *error_code)
{
	if (ft_printf("%s\n", MSG_USAGE) == ERROR)
	{
		*error_code = ERROR_WRITE_M;
		return (false);
	}
	return (true);
}

bool	put_server_pid(const pid_t server_pid, t_error_code *error_code)
{
	if (ft_printf("%s %d\n", MSG_SEND_PID, server_pid) == ERROR)
	{
		*error_code = ERROR_WRITE_M;
		return (false);
	}
	return (true);
}

bool	put_recieved_message(t_error_code *error_code)
{
	if (ft_printf("%s\n", MSG_RECIEVED) == ERROR)
	{
		*error_code = ERROR_WRITE_M;
		return (false);
	}
	return (true);
}
