/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:44:30 by mbonsdor          #+#    #+#             */
/*   Updated: 2024/11/24 14:20:04 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*mem;

	if (size == 0 || nitems == 0)
		return (malloc(0));
	if (nitems > ((size_t)-1) / size)
		return (NULL);
	mem = malloc(nitems * size);
	if (mem != NULL)
		ft_memset(mem, 0, nitems * size);
	return (mem);
}
