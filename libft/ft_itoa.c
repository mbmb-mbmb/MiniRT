/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:45:49 by mbonsdor          #+#    #+#             */
/*   Updated: 2024/11/24 13:37:10 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_digits(long n)
{
	long	i;

	i = 0;
	if (n <= 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return ((int)(i));
}

char	*ft_itoa(int n)
{
	char	*out;
	int		numd;
	int		negative;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	negative = 0;
	numd = num_digits(n);
	out = malloc((numd + 1) * sizeof(char));
	if (!out)
		return (NULL);
	if (n < 0)
	{
		n = -n;
		negative = 1;
	}
	out[numd] = '\0';
	while (numd > 0)
	{
		out[--numd] = (n % 10) + '0';
		n /= 10;
	}
	if (negative)
		out[0] = '-';
	return (out);
}
