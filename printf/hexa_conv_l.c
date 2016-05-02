/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_conv_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 17:04:04 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/08 06:42:16 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		hexa_prec_l(t_struct data, unsigned long nbr, int i, int lower)
{
	int		k;

	k = 0;
	k += put_prec_nbr(data.prec - i);
	if (data.flag & 0b00000001)
		k += pf_putstr(lower == 1 ? "0x" : "0X");
	pf_puthexa_noflag_l(nbr, lower);
	return (k);
}

static int		hexa_min_l(t_struct data, unsigned long nbr, int i, int lower)
{
	int		j;
	int		k;
	int		l;

	l = data.flag & 1 ? 2 : 0;
	k = 0;
	j = i;
	if (data.flag & 1 && data.min != 0 && data.flag & 2)
	{
		if (data.flag & 0b00000001 && nbr != 0)
			k += pf_putstr(lower == 1 ? "0x" : "0X");
		while (k < data.min - (data.prec < j ? 0 : data.prec))
			k += pf_putchar(data.flag & 0b00000010 ? '0' : ' ');
	}
	else
	{
		while (k < data.min - (data.prec < j ? j : data.prec))
			k += pf_putchar(data.flag & 0b00000010 ? '0' : ' ');
		if (data.flag & 0b00000001 && nbr != 0)
			k += pf_putstr(lower == 1 ? "0x" : "0X");
	}
	k += put_prec_nbr(data.prec - j);
	pf_puthexa_noflag_l(nbr, lower);
	return (k);
}

static int		hexa_hash_l(t_struct data, unsigned long nbr, int i, int lower)
{
	int		j;
	int		k;

	k = 0;
	j = i;
	if (data.flag & 0b00000001 && nbr != 0)
		k += pf_putstr(lower == 1 ? "0x" : "0X");
	k += put_prec_nbr(data.prec - j);
	pf_puthexa_noflag_l(nbr, lower);
	while (k < data.min + (data.flag & 1 ? 2 : 0) - j)
		k += pf_putchar(' ');
	return (k);
}

int				hexa_conv_l(t_struct data, unsigned long nbr, int lower)
{
	int		i;
	int		k;

	k = 0;
	i = pf_rethexa_l(nbr, 2);
	if (nbr == 0 && data.min != 0)
		i = 0;
	data.min = data.flag & 0b00000001 ? data.min - 2 : data.min;
	if (data.flag & 0b00000100 && data.min != 0)
		k = hexa_hash_l(data, nbr, i, lower);
	else if (data.min != 0)
		k = hexa_min_l(data, nbr, i, lower);
	else
		k = hexa_prec_l(data, nbr, i, lower);
	if (data.prec != -1)
		return (k + i);
	return (k);
}
