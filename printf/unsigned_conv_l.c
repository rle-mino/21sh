/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_conv_l.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 10:53:38 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/08 06:47:27 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			unsigned_prec_l(t_struct data, unsigned long nbr, int i)
{
	int		k;

	k = 0;
	k += put_prec_nbr(data.prec - i);
	ft_putunsigned_l(nbr, 2);
	return (k);
}

static int			unsigned_min_l(t_struct data, unsigned long nbr, int i)
{
	int		j;
	int		k;

	k = 0;
	j = i;
	i = (data.flag & 8 || data.flag & 16) && !(data.flag & 2) ? 1 : 0;
	i += data.prec == j ? 1 : 0;
	if (data.prec > 0 && data.flag & 2)
		data.flag -= 2;
	while (k < data.min - (data.prec > j ? data.prec : j) - i)
		k += pf_putchar(data.flag & 2 ? '0' : ' ');
	k += put_prec_nbr(data.prec - j);
	if (data.prec != -1)
		ft_putunsigned_l(nbr, 2);
	return (k);
}

static int			unsigned_hash_l(t_struct data, unsigned long nbr, int i)
{
	int		j;
	int		k;

	k = 0;
	j = i;
	k += put_prec_nbr(data.prec - j);
	if (data.prec != -1)
		ft_putunsigned_l(nbr, 2);
	while (k < data.min + (data.flag & 1 ? 2 : 0) - j)
		k += pf_putchar(' ');
	return (k);
}

int					unsigned_conv_l(t_struct data, unsigned long nbr)
{
	int		i;
	int		k;

	k = 0;
	i = pf_retunsigned_l(nbr, 2);
	if (data.prec == -1 && nbr == 0)
		i = 0;
	data.min = data.flag & 1 ? data.min - 2 : data.min;
	if (data.flag & 4 && data.min != 0)
		k = unsigned_hash_l(data, nbr, i);
	else if (data.min != 0)
		k = unsigned_min_l(data, nbr, i);
	else
		k = unsigned_prec_l(data, nbr, i);
	return (k + i);
}
