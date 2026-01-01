/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:46:09 by mbonsdor          #+#    #+#             */
/*   Updated: 2024/11/24 15:47:40 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*out;
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	out = malloc(len + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		out[i] = s[i + start];
		i++;
	}
	out[i] = '\0';
	return (out);
}
