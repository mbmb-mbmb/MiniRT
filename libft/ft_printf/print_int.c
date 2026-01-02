/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:15:11 by mbonsdor          #+#    #+#             */
/*   Updated: 2024/12/03 11:03:31 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	checks(int num)
{
	if (num == 0)
		return (write(1, "0", 1));
	if (num == -2147483648)
		return (write(1, "-2147483648", 11));
	return (0);
}

static int	absolute(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

int	print_int(int num)
{
	char	buffer[12];
	int		i;
	int		neg;
	int		counter;

	i = 0;
	neg = 0;
	if (num < 0)
		neg = 1;
	counter = checks(num);
	if (counter > 0)
		return (counter);
	num = absolute(num);
	while (num > 0)
	{
		buffer[i++] = (num % 10) + '0';
		num /= 10;
	}
	if (neg)
		buffer[i++] = '-';
	counter = i;
	while (--i >= 0)
		if (write(1, &buffer[i], 1) < 0)
			return (-1);
	return (counter);
}
