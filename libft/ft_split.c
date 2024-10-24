/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhour <obouhour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:46:21 by obouhour          #+#    #+#             */
/*   Updated: 2024/06/11 11:57:09 by obouhour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_word(const char *s, char c)
{
	size_t	i;
	size_t	count;
	int		is_word;

	count = 0;
	i = 0;
	is_word = 0;
	while (s[i])
	{
		if (s[i] == c)
			is_word = 0;
		else if (is_word == 0)
		{
			is_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

char	*make_word(char *s, size_t len)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	s = s - len;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	free_word(size_t w_idx, char **ptr)
{
	while (w_idx > 0)
	{
		free(ptr[w_idx - 1]);
		w_idx--;
	}
	free(ptr);
}

char	**ft_split(const char *s, char c)
{
	char	**ptr;
	size_t	w_len;
	size_t	w_idx;

	w_len = 0;
	w_idx = 0;
	ptr = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!ptr)
		return (NULL);
	while (*s)
	{
		if (*s != c)
			w_len++;
		if ((*s == c || !s[1]) && w_len != 0)
		{
			ptr[w_idx] = make_word((char *)s + 1 * (!s[1] && *s != c), w_len);
			if (ptr[w_idx] == NULL)
				return (free_word(w_idx, ptr), NULL);
			w_len = 0;
			w_idx++;
		}
		s++;
	}
	ptr[w_idx] = NULL;
	return (ptr);
}

// int main()
// {
// 	char	*s = "split  |d||this|for|me|||||!|p|";
// 	char	c = '|';
// 	char	**a = ft_split(s, c);
// 	int		i = 0;

// 	if (a)
// 	{
// 		while (a[i])
// 		{
// 			printf("%s\n", a[i]);
// 			//free_malloc(a[i]);
// 			i++;
// 		}
// 		free(a);
// 	}
// 	return (0);
// }
