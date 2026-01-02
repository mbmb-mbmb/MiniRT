/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:14:51 by mbonsdor          #+#    #+#             */
/*   Updated: 2024/12/03 11:55:38 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_larger_hex(uintptr_t num)
{
	char	buffer[17];
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
			buffer[i++] = digit - 10 + 'a';
		num /= 16;
		counter++;
	}
	while (--i >= 0)
		if (write(1, &buffer[i], 1) < 0)
			return (-1);
	return (counter);
}

int	print_ptr(void *p)
{
	int			counter;
	uintptr_t	temp;

	temp = (uintptr_t) p;
	counter = 0;
	if (!temp)
		return (write(1, "(nil)", 5));
	counter += write(1, "0x", 2);
	counter += print_larger_hex(temp);
	return (counter);
}
