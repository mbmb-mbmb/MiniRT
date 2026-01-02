/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:15:24 by mbonsdor          #+#    #+#             */
/*   Updated: 2024/12/03 11:04:14 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_uint(unsigned int num)
{
	char	buffer[21];
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	if (num == 0)
		return (write(1, "0", 1));
	while (num > 0)
	{
		buffer[i++] = (num % 10) + '0';
		num /= 10;
		counter++;
	}
	while (--i >= 0)
		if (write(1, &buffer[i], 1) < 0)
			return (-1);
	return (counter);
}
