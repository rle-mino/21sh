/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putoctal_j.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 14:46:53 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/02 15:33:49 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_retoctal_j(uintmax_t nbr, int lower)
{
	int					i;
	uintmax_t			nbr2;

	nbr2 = nbr;
	i = 0;
	while (nbr2 >= 8)
	{
		nbr2 /= 8;
		i++;
	}
	if (lower != 2)
		pf_putoctal_noflag_j(nbr);
	return (i + 1);
}

void	pf_putoctal_noflag_j(uintmax_t nbr)
{
	if (nbr >= 8)
	{
		pf_putoctal_noflag_j(nbr / 8);
		ft_putchar((nbr % 8) + '0');
	}
	else
		ft_putchar((nbr % 8) + '0');
}
