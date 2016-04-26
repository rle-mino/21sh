/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putdeci_h.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:36:53 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/07 19:20:17 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			pf_retdeci_h(short n, int flag)
{
	int		k;
	short	n2;

	n2 = n;
	k = 0;
	if (n == SHRT_MIN)
	{
		if (flag != 2)
			ft_putnbr_h(n, flag);
		return (6);
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
		ft_putnbr_h(n, flag);
	return (k);
}

void		ft_putnbr_h(short n, int flag)
{
	if (n == SHRT_MIN)
	{
		ft_putstr("-32768");
		return ;
	}
	if (n < 0)
	{
		if (flag != 2)
			ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_h(n / 10, flag);
		ft_putchar(n % 10 + '0');
	}
	else
		ft_putchar(n + '0');
}
