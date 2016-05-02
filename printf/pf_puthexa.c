/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 15:31:15 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/09 13:03:06 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_rethexa_noclong(unsigned int nbr, int lower)
{
	int					i;
	unsigned int		nbr2;

	nbr2 = nbr;
	i = 0;
	while (nbr2 >= 16)
	{
		nbr2 /= 16;
		i++;
	}
	if (lower != 2)
		pf_puthexa_noflag(nbr, lower);
	return (i + 1);
}

void	pf_puthexa_noflag(unsigned int nbr, int lower)
{
	char		c;

	c = lower == 1 ? 'a' : 'A';
	if (nbr >= 16)
	{
		pf_puthexa_noflag(nbr / 16, lower);
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
