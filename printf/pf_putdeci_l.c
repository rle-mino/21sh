/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putdeci_l.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:37:03 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/06 22:56:51 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			pf_retdeci_l(long n, int flag)
{
	int		k;
	long	n2;

	n2 = n;
	if (n == LONG_MIN)
	{
		if (flag != 2)
			ft_putnbr_l(n, flag);
		return (20);
	}
	k = 0;
	if (n2 < 0)
	{
		n2 = -n2;
		k++;
	}
	while (n2 > 9)
	{
		n2 /= 10;
		k++;
	}
	k++;
	if (flag != 2)
		ft_putnbr_l(n, flag);
	return (k);
}

void		ft_putnbr_l(long n, int flag)
{
	if (n == LONG_MIN)
	{
		ft_putstr("-9223372036854775808");
		return ;
	}
	if (n < 0)
	{
		if (flag != 2)
			ft_putchar('-');
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr_l(n / 10, flag);
		ft_putchar(n % 10 + '0');
	}
	else
		ft_putchar(n + '0');
}
