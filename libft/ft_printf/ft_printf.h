/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:38:44 by mbonsdor          #+#    #+#             */
/*   Updated: 2024/12/03 11:52:03 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

int		print_hex(unsigned int num, char base);
int		print_int(int num);
int		print_uint(unsigned int num);
int		print_char(int c);
int		print_str(char *str);
int		print_ptr(void *p);
int		ft_printf(const char *str, ...);

#endif
