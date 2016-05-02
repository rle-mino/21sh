/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_percent_conv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 10:54:54 by rle-mino          #+#    #+#             */
/*   Updated: 2016/01/30 17:56:57 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		percent_conv(t_struct data)
{
	int		i;
	int		k;

	k = 0;
	i = 0;
	if (data.flag & 0b00000100)
	{
		ft_putchar('%');
		k = 1;
	}
	if (data.flag & 0b00000010)
		while (data.min-- > 1)
			i += pf_putchar('0');
	else
	{
		while (data.min-- > 1)
			i += pf_putchar(' ');
	}
	if (k == 0)
		ft_putchar('%');
	return (i + 1);
}
