#include "libft.h"

static bool	is_space(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || \
			c == '\f' || c == '\r' || c == ' ');
}

static bool	is_operator(int c)
{
	return (c == '-' || c == '+');
}

static bool	is_overflow(int *num, int c, int op)
{
	int	ov_div;
	int	ov_mod;

	ov_div = INT_MAX / 10;
	ov_mod = INT_MAX % 10 + (op == -1);
	if (*num > ov_div)
	{
		*num = 0;
		return (true);
	}
	if (*num == ov_div && c - '0' > ov_mod)
	{
		*num = 0;
		return (true);
	}
	return (false);
}

// if "-", return (0) -> fixed
bool	ft_atoi_with_bool(const char *str, int *num)
{
	int		op;
	bool	at_least_one_digit;

	*num = 0;
	op = 1;
	while (is_space(*str))
		str++;
	if (is_operator(*str))
	{
		op = ',' - *str;
		str++;
	}
	at_least_one_digit = false;
	while (ft_isdigit(*str))
	{
		at_least_one_digit = true;
		if (is_overflow(num, *str, op))
			return (false);
		*num = *num * 10 + *str - '0';
		str++;
	}
	if (*str || !at_least_one_digit)
		return (false);
	*num *= op;
	return (true);
}
