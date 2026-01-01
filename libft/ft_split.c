/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:01:19 by mbonsdor          #+#    #+#             */
/*   Updated: 2024/11/25 10:55:36 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, char c)
{
	int	word_flag;
	int	count;

	word_flag = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && word_flag == 0)
		{
			word_flag = 1;
			count++;
		}
		else if (*s == c)
		{
			word_flag = 0;
		}
		s++;
	}
	return (count);
}

static size_t	get_word_len(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static void	*free_strings(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;
	int		words;
	size_t	word_len;

	strings = malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!strings)
		return (NULL);
	words = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			word_len = get_word_len(s, c);
			strings[words] = ft_substr(s, 0, word_len);
			if (!strings[words])
				return (free_strings(strings, words));
			s += word_len;
			words++;
		}
	}
	strings[words] = NULL;
	return (strings);
}
