/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:27:30 by mbonsdor          #+#    #+#             */
/*   Updated: 2024/12/03 11:55:33 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	parse_specifiers(char specifier, va_list *args)
{
	if (specifier == 'c')
		return (print_char(va_arg(*args, int)));
	else if (specifier == 's')
		return (print_str(va_arg(*args, char *)));
	else if (specifier == 'p')
		return (print_ptr(va_arg(*args, void *)));
	else if (specifier == 'i' || specifier == 'd')
		return (print_int(va_arg(*args, int)));
	else if (specifier == 'u')
		return (print_uint(va_arg(*args, unsigned int)));
	else if (specifier == 'x')
		return (print_hex(va_arg(*args, unsigned int), 'a'));
	else if (specifier == 'X')
		return (print_hex(va_arg(*args, unsigned int), 'A'));
	else
		return (write(1, "%", 1));
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		counter;
	int		error_check;

	if (!str)
		return (-1);
	counter = 0;
	va_start (args, str);
	while (*str)
	{
		error_check = 0;
		if (*str == '%')
		{
			error_check = parse_specifiers(*(++str), &args);
			if (error_check < 0)
				return (va_end(args), -1);
			counter += error_check;
		}
		else
			counter += write(1, str, 1);
		str++;
	}
	va_end(args);
	return (counter);
}
