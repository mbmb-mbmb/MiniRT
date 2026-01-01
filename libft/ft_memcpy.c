/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:46:54 by mbonsdor          #+#    #+#             */
/*   Updated: 2024/11/24 13:46:13 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *to, const void *from, size_t n)
{
	const unsigned char	*src;
	unsigned char		*dest;
	size_t				i;

	dest = (unsigned char *) to;
	src = (const unsigned char *) from;
	i = 0;
	if (to == from)
		return (to);
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (to);
}
