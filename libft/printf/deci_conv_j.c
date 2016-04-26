/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deci_conv_j.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:34:52 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/08 06:14:10 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			deci_prec_j(t_struct data, uintmax_t nbr, int i)
{
	int		k;

	k = 0;
	k += put_prec_nbr(data.prec - i);
	if ((data.flag & 16 || data.flag & 8))
		k += pf_putchar(data.flag & 8 ? '+' : ' ');
	ft_putnbr_j(nbr, 2);
	return (k);
}

static int			deci_min_j(t_struct data, uintmax_t nbr, int i)
{
	int		j;
	int		k;

	k = 0;
	j = i;
	i = (data.flag & 8 || data.flag & 16) && !(data.flag & 2) ? 1 : 0;
	i += data.prec == j ? 1 : 0;
	if (data.prec > 0 && data.flag & 2)
		data.flag -= 2;
	if ((data.flag & 16 || data.flag & 8) && data.flag & 2)
		k += pf_putchar(data.flag & 8 ? '+' : ' ');
	while (k < data.min - (data.prec > j ? data.prec : j) - i)
		k += pf_putchar(data.flag & 2 ? '0' : ' ');
	if (!(data.flag & 2) && (data.flag & 16 || data.flag & 8))
		k += pf_putchar(data.flag & 8 ? '+' : ' ');
	k += put_prec_nbr(data.prec - j);
	if (data.prec != -1)
		ft_putnbr_j(nbr, 2);
	return (k);
}

static int			deci_hash_j(t_struct data, uintmax_t nbr, int i)
{
	int		j;
	int		k;

	k = 0;
	j = i;
	if ((data.flag & 16 || data.flag & 8))
		k += pf_putchar(data.flag & 8 ? '+' : ' ');
	k += put_prec_nbr(data.prec - j);
	if (data.prec != -1)
		ft_putnbr_j(nbr, 2);
	while (k < data.min + (data.flag & 1 ? 2 : 0) - j)
		k += pf_putchar(' ');
	return (k);
}

int					deci_conv_j(t_struct data, uintmax_t nbr)
{
	int		i;
	int		k;

	k = 0;
	i = pf_retdeci_j(nbr, 2);
	if (data.prec == -1 && nbr == 0)
		i = 0;
	data.min = data.flag & 1 ? data.min - 2 : data.min;
	if (data.flag & 4 && data.min != 0)
		k = deci_hash_j(data, nbr, i);
	else if (data.min != 0)
		k = deci_min_j(data, nbr, i);
	else
		k = deci_prec_j(data, nbr, i);
	return (k + i);
}
