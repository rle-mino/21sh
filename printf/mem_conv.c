/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 01:53:29 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/08 06:43:28 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			mem_min(t_struct data, int j, size_t nbr)
{
	int		k;

	k = 0;
	ft_putstr("0x");
	k += put_prec_nbr(data.prec > j - 2 ? data.prec - (j - 2) : 0);
	k += pf_retmem_noclong(nbr, 0);
	while (k < data.min)
		k += pf_putchar(data.flag & 2 ? '0' : ' ');
	return (k);
}

static int			mem_conv_prec(t_struct data, size_t nbr, int j, int k)
{
	if (data.flag & 2)
		ft_putstr("0x");
	while (k < data.min - j)
		k += pf_putchar(data.flag & 2 ? '0' : ' ');
	if (!(data.flag & 2))
		ft_putstr("0x");
	k += put_prec_nbr(0);
	if (data.prec == -1)
		k += pf_retmem_noclong(nbr, 2) - 1;
	else
		k += pf_retmem_noclong(nbr, 0);
	return (k);
}

int					mem_conv_noclong(t_struct data, size_t nbr)
{
	int		k;
	int		j;

	k = 0;
	j = pf_retmem_noclong(nbr, 2);
	if (data.flag & 4)
		k += mem_min(data, j, nbr);
	else if (data.prec < 1)
		k += mem_conv_prec(data, nbr, j, k);
	else
	{
		while (k < data.min - (data.prec > j ? data.prec + 2 : j))
			k += pf_putchar(data.flag & 2 ? '0' : ' ');
		ft_putstr("0x");
		k += put_prec_nbr(data.prec > j - 2 ? data.prec - (j - 2) : 0);
		k += pf_retmem_noclong(nbr, 0);
	}
	return (k);
}
