#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

bool	ft_atoi_with_bool(const char *str, int *num);
bool	ft_isdigit(int c);
size_t	ft_max(const size_t x, const size_t y);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *s, int c);
int		ft_toupper(int c);

#endif
