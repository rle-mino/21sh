/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putdeci_ll.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:37:09 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/05 01:18:54 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			pf_retdeci_ll(long long n, int flag)
{
	int			k;
	long long	n2;

	n2 = n;
	k = 0;
	if (n == LLONG_MIN)
	{
		if (flag != 2)
			ft_putnbr_ll(n, flag);
		return (20);
	}
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
		ft_putnbr_ll(n, flag);
	return (k);
}

void		ft_putnbr_ll(long long n, int flag)
{
	if (n == LLONG_MIN)
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
		ft_putnbr_ll(n / 10, flag);
		ft_putchar(n % 10 + '0');
	}
	else
		ft_putchar(n + '0');
}
