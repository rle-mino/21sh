/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putoctal_z.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 14:47:00 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/02 15:33:47 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_retoctal_z(size_t nbr, int lower)
{
	int					i;
	size_t				nbr2;

	nbr2 = nbr;
	i = 0;
	while (nbr2 >= 8)
	{
		nbr2 /= 8;
		i++;
	}
	if (lower != 2)
		pf_putoctal_noflag_z(nbr);
	return (i + 1);
}

void	pf_putoctal_noflag_z(size_t nbr)
{
	if (nbr >= 8)
	{
		pf_putoctal_noflag_z(nbr / 8);
		ft_putchar((nbr % 8) + '0');
	}
	else
		ft_putchar((nbr % 8) + '0');
}
