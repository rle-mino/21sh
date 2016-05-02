/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putoctal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 13:56:09 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/02 15:37:26 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_retoctal_noclong(unsigned int nbr, int lower)
{
	int					i;
	unsigned int		nbr2;

	nbr2 = nbr;
	i = 0;
	while (nbr2 >= 8)
	{
		nbr2 /= 8;
		i++;
	}
	if (lower != 2)
		pf_putoctal_noflag(nbr);
	return (i + 1);
}

void	pf_putoctal_noflag(unsigned int nbr)
{
	if (nbr >= 8)
	{
		pf_putoctal_noflag(nbr / 8);
		ft_putchar((nbr % 8) + '0');
	}
	else
		ft_putchar((nbr % 8) + '0');
}
