/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_puthexa_j.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 15:31:40 by rle-mino          #+#    #+#             */
/*   Updated: 2016/01/30 17:57:29 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_rethexa_j(uintmax_t nbr, int lower)
{
	int					i;
	uintmax_t			nbr2;

	nbr2 = nbr;
	i = 0;
	while (nbr2 >= 16)
	{
		nbr2 /= 16;
		i++;
	}
	if (lower == 0 || lower == 1)
		pf_puthexa_noflag_j(nbr, lower);
	return (i + 1);
}

void	pf_puthexa_noflag_j(uintmax_t nbr, int lower)
{
	char		c;

	c = lower == 1 ? 'a' : 'A';
	if (nbr >= 16)
	{
		pf_puthexa_noflag_j(nbr / 16, lower);
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
