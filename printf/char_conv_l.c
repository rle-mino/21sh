/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_conv_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 23:00:39 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/06 23:02:15 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		char_conv_l(t_struct data, wchar_t c)
{
	int		k;

	k = 0;
	if (data.flag & 4)
	{
		k += pf_putcharuni(c);
		while (k < data.min)
			k += pf_putchar(' ');
	}
	else
	{
		while (k < data.min - 1)
			k += pf_putchar(' ');
		k += pf_putcharuni(c);
	}
	return (k);
}
