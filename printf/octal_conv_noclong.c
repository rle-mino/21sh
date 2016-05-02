/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal_conv_noclong.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 14:52:32 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/08 06:45:11 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			octal_prec(t_struct data, unsigned int nbr, int i)
{
	int		k;

	k = 0;
	k += put_prec_nbr(data.prec - i);
	if (data.flag & 1)
		k += pf_putchar('0');
	if (data.prec != -1)
		pf_putoctal_noflag(nbr);
	return (k);
}

static int			octal_min(t_struct data, unsigned int nbr, int i)
{
	int		j;
	int		k;

	k = 0;
	j = i;
	if (data.flag & 1 && data.min != 0 && data.flag & 2)
	{
		if (data.flag & 1 && nbr != 0)
			k += pf_putchar('0');
		while (k < data.min - (data.prec < j ? 0 : data.prec))
			k += pf_putchar(data.flag & 2 ? '0' : ' ');
	}
	else
	{
		while (k < data.min - (data.prec < j ? j : data.prec))
			k += pf_putchar(data.flag & 2 ? '0' : ' ');
		if (data.flag & 1 && nbr != 0)
			k += pf_putchar('0');
	}
	k += put_prec_nbr(data.prec - j);
	if (data.prec != -1 || nbr != 0 || data.flag & 1)
		pf_putoctal_noflag(nbr);
	return (k);
}

static int			octal_hash(t_struct data, unsigned int nbr, int i)
{
	int		j;
	int		k;

	k = 0;
	j = i;
	if (data.flag & 1 && nbr != 0)
		k += pf_putchar('0');
	k += put_prec_nbr(data.prec - j);
	if (data.prec != -1)
		pf_putoctal_noflag(nbr);
	while (k < data.min + (data.flag & 1 ? 1 : 0) - j)
		k += pf_putchar(' ');
	return (k);
}

int					octal_conv_noclong(t_struct data, unsigned int nbr)
{
	int		i;
	int		k;

	k = 0;
	i = pf_retoctal_noclong(nbr, 2);
	if (nbr == 0 && data.min != 0)
		i = 0;
	data.min = data.flag & 1 ? data.min - 1 : data.min;
	if (data.flag & 4 && data.min != 0)
		k = octal_hash(data, nbr, i);
	else if (data.min != 0)
		k = octal_min(data, nbr, i);
	else
		k = octal_prec(data, nbr, i);
	if ((data.prec != -1 || nbr != 0) || data.flag & 1)
		return (k + i);
	return (k);
}
