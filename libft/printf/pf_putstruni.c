/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putstruni.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 22:19:50 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/08 06:03:34 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			pf_putstruni(wchar_t *str)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (str == NULL)
		return (pf_putstr("(null)"));
	while (str[i])
	{
		k += pf_putcharuni(str[i]);
		i++;
	}
	return (k);
}

int			ft_strwlen(wchar_t *str)
{
	int		i;
	int		k;

	k = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < 128)
			k += 1;
		else if (str[i] < 2048)
			k += 2;
		else if (str[i] < 65536)
			k += 3;
		else
			k += 4;
		i++;
	}
	return (k);
}
