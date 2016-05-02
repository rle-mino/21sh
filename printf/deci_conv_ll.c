/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deci_conv_ll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:34:46 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/08 06:14:42 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			deci_prec_ll(t_struct data, long long nbr, int i)
{
	int		k;

	k = 0;
	k += put_prec_nbr(data.prec - i + (nbr < 0 ? 1 : 0));
	if ((data.flag & 16 || data.flag & 8) && nbr >= 0)
		k += pf_putchar(data.flag & 8 ? '+' : ' ');
	ft_putnbr_ll(nbr, 2);
	return (k);
}

static int			deci_min_ll(t_struct data, long long nbr, int i)
{
	int		j;
	int		k;

	k = 0;
	j = i;
	i = (data.flag & 8 || data.flag & 16) && !(data.flag & 2) ? 1 : 0;
	i += nbr < 0 && data.prec == j ? 1 : 0;
	i += nbr < 0 && data.prec > 0 && !(data.flag & 2) && j < data.prec ? 1 : 0;
	if (data.prec > 0 && data.flag & 2)
		data.flag -= 2;
	if (nbr < 0 && data.flag & 2)
		ft_putchar('-');
	if ((data.flag & 16 || data.flag & 8) && nbr >= 0 && data.flag & 2)
		k += pf_putchar(data.flag & 8 ? '+' : ' ');
	while (k < data.min - (data.prec > j ? data.prec : j) - i)
		k += pf_putchar(data.flag & 2 ? '0' : ' ');
	if (nbr >= 0 && !(data.flag & 2) && (data.flag & 16 || data.flag & 8))
		k += pf_putchar(data.flag & 8 ? '+' : ' ');
	if (nbr < 0 && data.min > 0 && !(data.flag & 2) && !(data.flag & 8))
		ft_putchar('-');
	k += put_prec_nbr(data.prec - j + (data.prec >= j && nbr < 0 ? 1 : 0));
	if (data.prec != -1)
		ft_putnbr_ll(nbr, 2);
	return (k);
}

static int			deci_hash_ll(t_struct data, long long nbr, int i)
{
	int		j;
	int		k;

	k = 0;
	j = i;
	if ((data.flag & 16 || data.flag & 8) && nbr >= 0)
		k += pf_putchar(data.flag & 8 ? '+' : ' ');
	k += put_prec_nbr(data.prec - j);
	if (nbr < 0 && data.prec != -1)
		ft_putchar('-');
	if (data.prec != -1)
		ft_putnbr_ll(nbr, 2);
	while (k < data.min + (data.flag & 1 ? 2 : 0) - j)
		k += pf_putchar(' ');
	return (k);
}

int					deci_conv_ll(t_struct data, long long nbr)
{
	int		i;
	int		k;

	k = 0;
	i = pf_retdeci_ll(nbr, 2);
	if (data.prec == -1 && nbr == 0)
		i = 0;
	data.min = data.flag & 1 ? data.min - 2 : data.min;
	if (data.flag & 4 && data.min != 0)
		k = deci_hash_ll(data, nbr, i);
	else if (data.min != 0)
		k = deci_min_ll(data, nbr, i);
	else
		k = deci_prec_ll(data, nbr, i);
	return (k + i);
}
