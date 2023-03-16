#include "libft.h"

// void	put_str_to_stderr(const char *str)
// {
// 	ft_putstr_fd(str, STDERR_FILENO);
// 	ft_putchar_fd('\n', STDERR_FILENO);
// }

// void	put_int_to_stderr(const int num)
// {
// 	ft_putnbr_fd(num, STDERR_FILENO);
// 	ft_putchar_fd('\n', STDERR_FILENO);
// }

void	put_str_int_to_stderr(const char *str, const int num)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putnbr_fd(num, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
