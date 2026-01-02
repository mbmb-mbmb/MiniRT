/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:15:03 by mbonsdor          #+#    #+#             */
/*   Updated: 2024/11/28 14:40:24 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex(unsigned int num, char base)
{
	char	buffer[9];
	int		i;
	int		counter;
	int		digit;

	i = 0;
	counter = 0;
	if (num == 0)
		return (write(1, "0", 1));
	while (num > 0)
	{
		digit = num % 16;
		if (digit <= 9)
			buffer[i++] = digit + '0';
		else if (digit > 9)
			buffer[i++] = digit - 10 + base;
		num /= 16;
	}
	counter = i;
	while (--i >= 0)
		if (write(1, &buffer[i], 1) < 0)
			return (-1);
	return (counter);
}
