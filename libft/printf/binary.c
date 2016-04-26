/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 10:06:05 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/26 10:46:43 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				pf_retbin(size_t nbr)
{
	size_t	cpy;
	int		i;

	cpy = nbr;
	i = 0;
	while (cpy >= 2)
	{
		cpy /= 2;
		i++;
	}
	ft_putnbr_bin(nbr);
	return (i + 1);
}

void			ft_putnbr_bin(size_t nbr)
{
	if (nbr >= 2)
	{
		ft_putnbr_bin(nbr / 2);
		ft_putchar(nbr % 2 + '0');
	}
	else
		ft_putchar(nbr + '0');
}
