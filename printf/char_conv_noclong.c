/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_conv_noclong.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 20:46:02 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/08 04:26:15 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		char_conv_noclong(t_struct data, char c)
{
	int		k;

	k = 0;
	if (data.flag & 4)
	{
		k += pf_putchar(c);
		while (k < data.min)
			k += pf_putchar(data.flag & 2 ? '0' : ' ');
	}
	else
	{
		while (k < data.min - 1)
			k += pf_putchar(data.flag & 2 ? '0' : ' ');
		k += pf_putchar(c);
	}
	return (k);
}
