/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 14:00:35 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/26 10:17:40 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			pf_isconver(char c)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' || c == 'i'
			|| c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'x'
			|| c == 'X' || c == 'c' || c == 'C' || c == 'b')
		return (1);
	return (0);
}

int			pf_isclong(char c, char d)
{
	if (c == 'h' && d == 'h')
		return (1);
	if (c == 'l' && d == 'l')
		return (1);
	if (c == 'j' || c == 'h' || c == 'j' || c == 'z' || c == 'l')
		return (1);
	return (0);
}

int			pf_isflag(char c)
{
	if (c == ' ' || c == '#' || c == '0' || c == '-' || c == '+')
		return (1);
	return (0);
}

int			pf_isnum(char c)
{
	if ((c >= '0' && c <= '9') || c == '*')
		return (1);
	return (0);
}
