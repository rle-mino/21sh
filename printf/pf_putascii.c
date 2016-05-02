/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putascii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 11:10:46 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/18 14:28:24 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_putstr(char const *str)
{
	if (str == NULL)
		return (write(1, "(null)", 6));
	write(1, str, ft_strlen(str));
	return (ft_strlen(str));
}

int		pf_retdeci_noclong(int n, int flag)
{
	int		k;
	int		n2;

	n2 = n;
	k = 0;
	if (n == -2147483648)
	{
		ftp_putnbr(n, flag);
		return (11);
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
		ftp_putnbr(n, flag);
	return (k);
}

int		pf_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}
