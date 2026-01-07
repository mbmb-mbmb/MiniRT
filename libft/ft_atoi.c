/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:44:11 by mbonsdor          #+#    #+#             */
/*   Updated: 2024/11/24 14:57:45 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	long		out;
	long		sign;

	i = 0;
	out = 0;
	sign = 1;
	while (str[i] == ' ' || (str [i] >= 9 && str [i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		if (sign == 1 && out > (INT_MAX - (str[i] - '0')) / 10)
			return (INT_MAX);
		if (sign == -1 && out > (-(long)INT_MIN - (str[i] - '0')) / 10)
			return (INT_MIN);
		out = out * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(out * sign));
}
