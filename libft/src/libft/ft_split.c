#include "libft.h"

static size_t	count_words(char const *head, char c)
{
	char const	*left = head;
	char const	*right = head;
	size_t		words;

	words = 0;
	while (*right != '\0')
	{
		while (*right == c)
		{
			left++;
			right++;
		}
		while (*right != '\0' && *right != c)
			right++;
		if (left != right)
		{
			words++;
			left = right;
		}
	}
	return (words);
}

static bool	set_split_str(char const *head, char c, char **list)
{
	char const	*left = head;
	char const	*right = head;
	size_t		i;

	i = 0;
	while (*right != '\0')
	{
		while (*right == c)
		{
			left++;
			right++;
		}
		while (*right != '\0' && *right != c)
			right++;
		if (left != right)
		{
			list[i] = ft_strndup(left, right - left);
			if (list[i] == NULL)
				return (false);
			i++;
			left = right;
		}
	}
	return (true);
}

static void	*free_all(char **list)
{
	size_t	i;

	i = 0;
	while (list[i] != NULL)
	{
		free(list[i]);
		i++;
	}
	free(list);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	list_size;
	char	**list;

	if (s == NULL)
		return (NULL);
	list_size = count_words(s, c);
	list = (char **)malloc(sizeof(char *) * (list_size + 1));
	if (list == NULL)
		return (NULL);
	if (!set_split_str(s, c, list))
		return (free_all(list));
	list[list_size] = NULL;
	return (list);
}
