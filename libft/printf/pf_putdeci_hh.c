/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putdeci_hh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:36:58 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/05 00:42:23 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			pf_retdeci_hh(char n, int flag)
{
	int		k;
	char	n2;

	n2 = n;
	k = 0;
	if (n == -128)
	{
		if (flag != 2)
			ft_putnbr_hh(n, flag);
		return (4);
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
		ft_putnbr_hh(n, flag);
	return (k);
}

void		ft_putnbr_hh(char n, int flag)
{
	if (n == -128)
	{
		ft_putstr("-128");
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
		ft_putnbr_hh(n / 10, flag);
		ft_putchar(n % 10 + '0');
	}
	else
		ft_putchar(n + '0');
}
