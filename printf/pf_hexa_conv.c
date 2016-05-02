/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_hexa_conv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:27:51 by rle-mino          #+#    #+#             */
/*   Updated: 2016/01/30 17:57:31 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		hexa_conv(t_struct data, va_list ap, int lower)
{
	if (data.clong == 0)
		return (hexa_conv_noclong(data, va_arg(ap, unsigned int), lower));
	if (data.clong & 1)
		return (hexa_conv_hh(data, va_arg(ap, unsigned int), lower));
	if (data.clong & 2)
		return (hexa_conv_ll(data, va_arg(ap, unsigned long long), lower));
	if (data.clong & 4)
		return (hexa_conv_h(data, va_arg(ap, unsigned int), lower));
	if (data.clong & 8)
		return (hexa_conv_l(data, va_arg(ap, unsigned long), lower));
	if (data.clong & 16)
		return (hexa_conv_j(data, va_arg(ap, uintmax_t), lower));
	if (data.clong & 32)
		return (hexa_conv_z(data, va_arg(ap, size_t), lower));
	return (0);
}
