/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putunsigned_j.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 10:52:47 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/05 11:08:17 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			pf_retunsigned_j(uintmax_t n, int flag)
{
	int				k;
	uintmax_t		n2;

	n2 = n;
	k = 0;
	while (n2 > 9)
	{
		n2 /= 10;
		k++;
	}
	k++;
	if (flag != 2)
		ft_putunsigned_j(n, flag);
	return (k);
}

void		ft_putunsigned_j(uintmax_t n, int flag)
{
	if (n > 9)
	{
		ft_putnbr_z(n / 10, flag);
		ft_putchar(n % 10 + '0');
	}
	else
		ft_putchar(n + '0');
}
