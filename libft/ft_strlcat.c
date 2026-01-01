/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:46:46 by mbonsdor          #+#    #+#             */
/*   Updated: 2024/11/24 14:18:59 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	if (!dest && size == 0)
		return (ft_strlen(src));
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = dest_len;
	j = 0;
	if (size == 0)
		return (src_len);
	if (size <= dest_len)
		return (size + src_len);
	while ((i < size - 1) && src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest_len + src_len);
}
