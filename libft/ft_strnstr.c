/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:46:17 by mbonsdor          #+#    #+#             */
/*   Updated: 2024/11/24 14:21:05 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	if (!big && n == 0)
		return (NULL);
	if (!little[0])
		return ((char *)(big));
	i = 0;
	little_len = ft_strlen(little);
	while (big[i] && i + little_len <= n)
	{
		j = 0;
		while (j < little_len && big[i + j] == little[j])
			j++;
		if (j == little_len)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
