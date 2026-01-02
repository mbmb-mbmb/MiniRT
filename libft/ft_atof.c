/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 11:30:30 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/01 11:30:31 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static float	parse_integer_part(const char *str, int *i)
{
	float	result;

	result = 0.0f;
	while (ft_isdigit(str[*i]))
	{
		result = result * 10.0f + (str[*i] - '0');
		(*i)++;
	}
	return (result);
}

static float	parse_fractional_part(const char *str, int *i)
{
	float	result;
	float	fraction;

	result = 0.0f;
	fraction = 0.1f;
	while (ft_isdigit(str[*i]))
	{
		result = result + (str[*i] - '0') * fraction;
		fraction = fraction * 0.1f;
		(*i)++;
	}
	return (result);
}

float	ft_atof(const char *str)
{
	float	result;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = parse_integer_part(str, &i);
	if (str[i] == '.')
	{
		i++;
		result = result + parse_fractional_part(str, &i);
	}
	return (result * sign);
}
