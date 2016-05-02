/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putmem_noclong.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 20:03:08 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/08 02:13:04 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_retmem_noclong(size_t nbr, int flag)
{
	int					i;
	size_t				nbr2;

	nbr2 = nbr;
	i = 0;
	while (nbr2 >= 16)
	{
		nbr2 /= 16;
		i++;
	}
	if (flag != 2)
	{
		if (flag == 1)
			ft_putstr("0x");
		pf_putmem_noflag(nbr);
	}
	return (i + 1 + 2);
}

void	pf_putmem_noflag(size_t nbr)
{
	char		c;

	c = 'a';
	if (nbr >= 16)
	{
		pf_putmem_noflag(nbr / 16);
		if (nbr % 16 > 9)
			ft_putchar((nbr % 16 - 10) + c);
		else
			ft_putchar((nbr % 16) + '0');
	}
	else
	{
		if (nbr % 16 > 9)
			ft_putchar((nbr % 16 - 10) + c);
		else
			ft_putchar((nbr % 16) + '0');
	}
}
