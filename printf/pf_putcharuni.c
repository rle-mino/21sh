/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putcharuni.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 17:35:44 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/08 06:07:26 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			pf_putcharuni(wchar_t c)
{
	int		k;

	k = 0;
	if (c < 128)
		k += pf_putchar(c);
	else if (c < 2048)
	{
		k += pf_putchar(192 | (c >> 6));
		k += pf_putchar(128 | (c & 63));
	}
	else if (c < 65536)
	{
		k += pf_putchar(224 | (c >> 12));
		k += pf_putchar(128 | ((c >> 6) & 63));
		k += pf_putchar(128 | (c & 63));
	}
	else if (c < 1114112)
	{
		k += pf_putchar(240 | (c >> 18));
		k += pf_putchar(128 | ((c >> 12) & 63));
		k += pf_putchar(128 | ((c >> 6) & 63));
		k += pf_putchar(128 | (c & 63));
	}
	return (k);
}
