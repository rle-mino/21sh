/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 11:58:08 by rle-mino          #+#    #+#             */
/*   Updated: 2016/01/30 17:56:58 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_print_line(va_list ap, char const *str)
{
	size_t		i;
	int			k;

	k = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] == '\0')
			return (k);
		else if (str[i] == '%')
			k += pf_until_conv(&i, ap, str);
		else
			k += pf_putchar(str[i]);
		if (str[i] != '\0')
			i++;
	}
	return (k);
}
