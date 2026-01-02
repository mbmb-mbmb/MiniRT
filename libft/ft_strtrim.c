/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:46:01 by mbonsdor          #+#    #+#             */
/*   Updated: 2024/11/18 11:09:46 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*out;
	int		start;
	int		end;
	int		i;

	start = 0;
	i = 0;
	end = ft_strlen(s1);
	while (start < end)
	{
		if (ft_strchr(set, s1[start]))
			start++;
		else if (ft_strchr(set, s1[end - 1]))
			end--;
		else
			break ;
	}
	out = malloc((end - start) + 1);
	if (!out)
		return (NULL);
	while (start < end)
		out[i++] = s1[start++];
	out[i] = '\0';
	return (out);
}
